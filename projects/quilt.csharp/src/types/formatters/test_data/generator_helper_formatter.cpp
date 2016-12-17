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
#include "dogen/quilt.csharp/types/formatters/test_data/generator_helper_formatter.hpp"
#include "dogen/quilt.csharp/types/fabric/generator_helper.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace test_data {

std::string generator_helper_formatter::static_artefact() {
    return traits::generator_helper_archetype();
}

std::string generator_helper_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location generator_helper_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::family(), csharp::traits::kernel(),
          traits::facet(),
          generator_helper_formatter::static_artefact());
    return r;
}

std::type_index generator_helper_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::generator_helper)));
    return r;
}

boost::filesystem::path generator_helper_formatter::
full_path(const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path(n, static_artefact());
}

std::list<std::string> generator_helper_formatter::
inclusion_dependencies(const yarn::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact
generator_helper_formatter::format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    {
        const auto sn(e.name().simple());
        // const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
a.stream() << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
} } } } }
