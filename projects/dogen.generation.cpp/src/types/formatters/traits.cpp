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
#include "dogen.generation.cpp/types/formatters/traits.hpp"

namespace {

const std::string master_header_postfix(".master_header");
const std::string canonical_archetype_postfix(".canonical_archetype");

}

namespace dogen {
namespace generation {
namespace cpp {
namespace formatters {

std::string traits::
master_header_archetype(const std::string& facet) {
    return facet + master_header_postfix;
}

std::string traits::cmake_facet() {
    static std::string r("quilt.cpp.cmake");
    return r;
}

std::string traits::include_cmakelists_archetype() {
    static std::string r("quilt.cpp.cmake.include_cmakelists");
    return r;
}

std::string traits::source_cmakelists_archetype() {
    static std::string r("quilt.cpp.cmake.source_cmakelists");
    return r;
}

std::string traits::msbuild_facet() {
    static std::string r("quilt.cpp.msbuild");
    return r;
}

std::string traits::msbuild_targets_archetype() {
    static std::string r("quilt.cpp.msbuild.targets");
    return r;
}

std::string traits::visual_studio_facet() {
    static std::string r("quilt.cpp.visual_studio");
    return r;
}

std::string traits::visual_studio_project_archetype() {
    static std::string r("quilt.cpp.visual_studio.project");
    return r;
}

std::string traits::visual_studio_solution_archetype() {
    static std::string r("quilt.cpp.visual_studio.solution");
    return r;
}

std::string traits::canonical_archetype(const std::string& facet) {
    return facet + canonical_archetype_postfix;
}

std::string traits::visual_studio_project_solution_guid() {
    static std::string r("quilt.cpp.visual_studio.project_solution_guid");
    return r;
}

std::string traits::visual_studio_project_guid() {
    static std::string r("quilt.cpp.visual_studio.project_guid");
    return r;
}

} } } }
