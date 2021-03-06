/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <memory>
#include <forward_list>
#include <boost/make_shared.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.modeling/types/helpers/building_error.hpp"
#include "dogen.modeling/io/meta_model/name_io.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.modeling/types/meta_model/visitor.hpp"
#include "dogen.modeling/types/meta_model/exception.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"
#include "dogen.modeling/types/meta_model/element_visitor.hpp"
#include "dogen.modeling/types/helpers/name_factory.hpp"
#include "dogen.modeling/types/meta_model/elements_traversal.hpp"
#include "dogen.generation.cpp/types/fabric/master_header.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen.generation.cpp/types/fabric/master_header_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("generation.cpp.fabric.master_header_factory"));

const std::string master_header_name("all");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");

}

namespace dogen {
namespace generation {
namespace cpp {
namespace fabric {

namespace {

class generator final : public modeling::meta_model::element_visitor {
public:
    generator(const modeling::meta_model::name& model_name,
        const formatters::repository& rp)
        : result_(create_master_header(model_name)),
          file_formatters_by_meta_name_(
              filter_file_formatters_by_meta_name(rp)) {}

private:
    boost::shared_ptr<master_header>
    create_master_header(const modeling::meta_model::name& model_name);

    std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
    filter_formatters(const std::forward_list<
        std::shared_ptr<formatters::artefact_formatter_interface>>&
        formatters) const;

    std::unordered_map<
        std::string,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>>
    filter_file_formatters_by_meta_name(const formatters::repository& rp) const;

    void process_element(const modeling::meta_model::element& e);

public:
    using modeling::meta_model::element_visitor::visit;
    void visit(const modeling::meta_model::visitor& v) { process_element(v); }
    void visit(const modeling::meta_model::enumeration& e) {
        process_element(e);
    }
    void visit(const modeling::meta_model::primitive& p) {
        process_element(p);
    }
    void visit(const modeling::meta_model::object& o) { process_element(o); }
    void visit(const modeling::meta_model::exception& e) {
        process_element(e);
    }
    void visit(const modeling::meta_model::module& m) { process_element(m); }

public:
    boost::shared_ptr<master_header> result() { return result_; }

private:
    boost::shared_ptr<master_header> result_;
    const std::unordered_map<
        std::string,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>>
    file_formatters_by_meta_name_;

};

boost::shared_ptr<master_header>
generator::create_master_header(const modeling::meta_model::name& model_name) {
    auto r(boost::make_shared<master_header>());
    modeling::helpers::name_factory f;
    r->name(f.build_element_in_model(model_name, master_header_name));
    r->meta_name(meta_name_factory::make_master_header_name());
    r->origin_type(modeling::meta_model::origin_types::target);
    return r;
}

std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
generator::filter_formatters(const std::forward_list<std::shared_ptr<
    formatters::artefact_formatter_interface>>& formatters) const {
    std::forward_list<std::shared_ptr<formatters::artefact_formatter_interface>>
        r;

    /*
     * We are only interested in formatters that generate
     * header files.
     */
    using formatters::inclusion_support_types;
    static const auto ns(inclusion_support_types::not_supported);
    for (const auto& fmt : formatters) {
        if (fmt->inclusion_support_type() != ns)
            r.push_front(fmt);
    }
    return r;
}

std::unordered_map<
    std::string,
    std::forward_list<
        std::shared_ptr<formatters::artefact_formatter_interface>>>
generator::filter_file_formatters_by_meta_name(
    const formatters::repository& rp) const {
    std::unordered_map<
        std::string,
        std::forward_list<
            std::shared_ptr<formatters::artefact_formatter_interface>>> r;

    for (const auto& pair : rp.stock_artefact_formatters_by_meta_name()) {
        const auto& mt(pair.first);
        const auto& fmts(pair.second);
        r[mt] = filter_formatters(fmts);
    }
    return r;
}

void generator::process_element(const modeling::meta_model::element& e) {
    if (e.origin_type() != modeling::meta_model::origin_types::target)
        return;

    BOOST_LOG_SEV(lg, debug) << "Processing element: " << e.name().id();
    const auto mt(e.meta_name().id());
    const auto i(file_formatters_by_meta_name_.find(mt));
    if (i == file_formatters_by_meta_name_.end()) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, error) << formatter_not_found_for_type << id;
        BOOST_THROW_EXCEPTION(
            modeling::helpers::building_error(formatter_not_found_for_type + id));
    }

    for (const auto& fmt : i->second) {
        const auto fct(fmt->archetype_location().facet());
        const auto arch(fmt->archetype_location().archetype());
        result_->inclusion_by_facet()[fct][arch].push_back(e.name());
        BOOST_LOG_SEV(lg, debug) << "Added name. Facet: "
                                 << fct << " Archetype: " << arch;
    }
}

}

boost::shared_ptr<modeling::meta_model::element>
master_header_factory::make(const formatters::repository& frp,
    const modeling::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Generating the master header.";

    generator g(m.name(), frp);
    for(auto& ptr : m.elements()) {
        const auto& e(*ptr);
        e.accept(g);
    }
    const auto r(g.result());

    BOOST_LOG_SEV(lg, debug) << "Generated the master header.";
    return r;
}

} } } }
