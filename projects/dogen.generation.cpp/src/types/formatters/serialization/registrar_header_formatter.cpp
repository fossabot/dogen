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
#include "dogen.generation.cpp/types/formatters/serialization/registrar_header_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/fabric/registrar.hpp"
#include "dogen.formatting/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen.formatting/types/cpp/scoped_boilerplate_formatter.hpp"

namespace dogen {
namespace generation {
namespace cpp {
namespace formatters {
namespace serialization {

std::string registrar_header_formatter::static_id() {
    return traits::registrar_header_archetype();
}

std::string registrar_header_formatter::id() const {
    return static_id();
}

annotations::archetype_location
registrar_header_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          registrar_header_formatter::static_id());
    return r;
}

const modeling::meta_model::name& registrar_header_formatter::meta_name() const {
    using fabric::meta_name_factory;
    static auto r(meta_name_factory::make_registrar_name());
    return r;
}

std::string registrar_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types registrar_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path registrar_header_formatter::inclusion_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path registrar_header_formatter::full_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> registrar_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const modeling::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

modeling::meta_model::artefact registrar_header_formatter::
format(const context& ctx, const modeling::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& rg(a.as<fabric::registrar>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(rg.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void register_types(Archive& ar);" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;

    } // sbf
    return a.make_artefact();
}

} } } } }
