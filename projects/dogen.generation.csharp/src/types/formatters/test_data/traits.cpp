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
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.generation.csharp/types/formatters/test_data/traits.hpp"

namespace dogen {
namespace generation {
namespace csharp {
namespace formatters {
namespace test_data {

std::string traits::facet() {
    static std::string r(csharp::traits::backend() + ".test_data");
    return r;
}

std::string traits::class_archetype() {
    static std::string r(traits::facet() + ".class");
    return r;
}

std::string traits::enum_archetype() {
    static std::string r(traits::facet() + ".enum");
    return r;
}

std::string traits::primitive_archetype() {
    static std::string r(traits::facet() + ".primitive");
    return r;
}

std::string traits::assistant_archetype() {
    static std::string r(traits::facet() + ".assistant");
    return r;
}

} } } } }