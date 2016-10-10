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
#include "dogen/quilt.cpp/hash/formattables/locator_configuration_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/locator_facet_configuration_hash.hpp"
#include "dogen/quilt.cpp/hash/formattables/locator_formatter_configuration_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_locator_facet_configuration(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::locator_facet_configuration>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_locator_formatter_configuration(const std::unordered_map<std::string, dogen::quilt::cpp::formattables::locator_formatter_configuration>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::size_t locator_configuration_hasher::hash(const locator_configuration& v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_locator_facet_configuration(v.facet_configurations()));
    combine(seed, hash_std_unordered_map_std_string_dogen_quilt_cpp_formattables_locator_formatter_configuration(v.formatter_configurations()));
    combine(seed, v.include_directory_name());
    combine(seed, v.source_directory_name());
    combine(seed, v.disable_facet_directories());
    combine(seed, v.header_file_extension());
    combine(seed, v.implementation_file_extension());

    return seed;
}

} } } }