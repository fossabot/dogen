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
#include <boost/throw_exception.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.annotations/types/annotation.hpp"
#include "dogen.annotations/types/entry_selector.hpp"
#include "dogen.annotations/types/type_repository_selector.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/exception.hpp"
#include "dogen.modeling/types/meta_model/builtin.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/element_visitor.hpp"
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.generation.csharp/types/formattables/aspect_properties.hpp"
#include "dogen.generation.csharp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen.generation.csharp/types/formattables/expansion_error.hpp"
#include "dogen.generation.csharp/types/formattables/aspect_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.csharp.formattables.aspect_expander"));

}

namespace dogen {
namespace generation {
namespace csharp {
namespace formattables {

class aspect_properties_generator : public modeling::meta_model::element_visitor {
private:
    struct type_group {
        annotations::type requires_static_reference_equals;
    };

    type_group make_type_group(const annotations::type_repository& atrp) const;

public:
    explicit
    aspect_properties_generator(const annotations::type_repository& atrp);

private:
    void handle_aspect_properties(const annotations::annotation& a,
        const std::string& id, const bool is_floating_point = false);

public:
    using modeling::meta_model::element_visitor::visit;
    void visit(const modeling::meta_model::enumeration& e);
    void visit(const modeling::meta_model::exception& e);
    void visit(const modeling::meta_model::object& o);
    void visit(const modeling::meta_model::builtin& p);

public:
    const std::unordered_map<std::string, formattables::aspect_properties>&
    result() const;

private:
    type_group type_group_;
    std::unordered_map<std::string, formattables::aspect_properties> result_;
};


aspect_properties_generator::
aspect_properties_generator(const annotations::type_repository& atrp)
    : type_group_(make_type_group(atrp)) {}

aspect_properties_generator::type_group aspect_properties_generator::
make_type_group(const annotations::type_repository& atrp) const {

    type_group r;
    const annotations::type_repository_selector s(atrp);

    const auto rsrq(traits::csharp::aspect::requires_static_reference_equals());
    r.requires_static_reference_equals = s.select_type_by_name(rsrq);

    return r;
}

void aspect_properties_generator::handle_aspect_properties(
    const annotations::annotation& a, const std::string& id,
    const bool is_floating_point) {
    const annotations::entry_selector s(a);

    /*
     * FIXME: It would be nice to make this container sparse rather
     * than dense. However, because we now default "require static
     * reference equals" to true, sparseness becomes a bit
     * confusing. This needs some rethinking.
     */
    aspect_properties ap;
    const auto& rsrq(type_group_.requires_static_reference_equals);
    ap.requires_static_reference_equals(s.get_boolean_content_or_default(rsrq));
    ap.is_floating_point(is_floating_point);

    result_[id] = ap;
}

void aspect_properties_generator::visit(const modeling::meta_model::enumeration& e) {
    handle_aspect_properties(e.annotation(), e.name().id());
}

void aspect_properties_generator::visit(const modeling::meta_model::exception& e) {
    handle_aspect_properties(e.annotation(), e.name().id());
}

void aspect_properties_generator::visit(const modeling::meta_model::object& o) {
    handle_aspect_properties(o.annotation(), o.name().id());
}

void aspect_properties_generator::visit(const modeling::meta_model::builtin& p) {
    handle_aspect_properties(p.annotation(), p.name().id());
}

const std::unordered_map<std::string, formattables::aspect_properties>&
aspect_properties_generator::result() const {
    return result_;
}

void aspect_expander::
expand(const annotations::type_repository& atrp, model& fm) const {
    aspect_properties_generator g(atrp);
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());

        e.accept(g);
    }
    fm.aspect_properties(g.result());
}

} } } }
