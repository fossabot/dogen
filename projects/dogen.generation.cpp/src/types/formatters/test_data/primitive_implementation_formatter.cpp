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
#include "dogen.generation.cpp/types/formatters/test_data/primitive_implementation_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/test_data/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.formatting/types/sequence_formatter.hpp"
#include "dogen.modeling/types/helpers/meta_name_factory.hpp"
#include "dogen.modeling/types/meta_model/primitive.hpp"
#include "dogen.utility/log/logger.hpp"
#include <boost/throw_exception.hpp>

namespace dogen {
namespace generation {
namespace cpp {
namespace formatters {
namespace test_data {

std::string primitive_implementation_formatter::static_id() {
    return traits::primitive_implementation_archetype();
}

std::string primitive_implementation_formatter::id() const {
    return static_id();
}

annotations::archetype_location
primitive_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          primitive_implementation_formatter::static_id());
    return r;
}

const modeling::meta_model::name& primitive_implementation_formatter::meta_name() const {
    using modeling::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

std::string primitive_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types primitive_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const modeling::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(primitive_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path primitive_implementation_formatter::full_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> primitive_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const modeling::meta_model::element& e) const {

    const auto& p(assistant::as<modeling::meta_model::primitive>(e));
    auto builder(f.make());
    builder.add(p.name(), traits::primitive_header_archetype());

    const auto carch(traits::canonical_archetype());
    builder.add(p.value_attribute().parsed_type().current(), carch);

    return builder.build();
}

modeling::meta_model::artefact primitive_implementation_formatter::
format(const context& ctx, const modeling::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& p(a.as<modeling::meta_model::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(a.get_qualified_name(p.name()));
    {

        auto sbf(a.make_scoped_boilerplate_formatter(e));
a.stream() << "namespace {" << std::endl;
        a.add_helper_methods(p.name().id());
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        {
            const auto attr(p.value_attribute());
            const auto ns(a.make_namespaces(p.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
a.stream() << std::endl;
a.stream() << sn << "_generator::" << sn << "_generator() : position_(0) { }" << std::endl;
            /*
             * Populate method.
             */
            if (!p.is_immutable()) {
a.stream() << std::endl;
a.stream() << "void " << sn << "_generator::" << std::endl;
a.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
a.stream() << "    v." << attr.name().simple() << "(create_" << attr.parsed_type().identifiable() << "(position + 1));" << std::endl;
a.stream() << "}" << std::endl;
            }

            /*
             * Create method.
             */
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type" << std::endl;
a.stream() << sn << "_generator::create(const unsigned int position) {" << std::endl;
            if (p.is_immutable()) {
a.stream() << "    return " << sn << "(create_" << attr.parsed_type().identifiable() << "(position + 1));" << std::endl;
            } else {
a.stream() << "    " << sn << " r;" << std::endl;
a.stream() << "    " << sn << "_generator::populate(position, r);" << std::endl;
a.stream() << "    return r;" << std::endl;
            }
a.stream() << "}" << std::endl;
            /*
             * Create method ptr.
             */
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type*" << std::endl;
a.stream() << sn << "_generator::create_ptr(const unsigned int position) {" << std::endl;
            if (p.is_immutable())
a.stream() << "    return new " << sn << "(create(position));" << std::endl;
            else {
a.stream() << "    " << sn << "* r = new " << sn << "();" << std::endl;
a.stream() << "    " << sn << "_generator::populate(position, *r);" << std::endl;
a.stream() << "    return r;" << std::endl;
            }
a.stream() << "}" << std::endl;
            /*
             * Function operator
             */
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type" << std::endl;
a.stream() << sn << "_generator::operator()() {" << std::endl;
a.stream() << "    return create(position_++);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
} } } } }
