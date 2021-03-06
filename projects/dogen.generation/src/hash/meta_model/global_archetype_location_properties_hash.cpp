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
#include "dogen.generation/hash/meta_model/facet_properties_hash.hpp"
#include "dogen.generation/hash/meta_model/backend_properties_hash.hpp"
#include "dogen.generation/hash/meta_model/archetype_properties_hash.hpp"
#include "dogen.generation/hash/meta_model/denormalised_archetype_properties_hash.hpp"
#include "dogen.generation/hash/meta_model/global_archetype_location_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_unordered_map_std_string_dogen_generation_meta_model_backend_properties(const std::unordered_map<std::string, dogen::generation::meta_model::backend_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_generation_meta_model_facet_properties(const std::unordered_map<std::string, dogen::generation::meta_model::facet_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_generation_meta_model_archetype_properties(const std::unordered_map<std::string, dogen::generation::meta_model::archetype_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_std_string_dogen_generation_meta_model_denormalised_archetype_properties(const std::unordered_map<std::string, dogen::generation::meta_model::denormalised_archetype_properties>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace dogen {
namespace generation {
namespace meta_model {

std::size_t global_archetype_location_properties_hasher::hash(const global_archetype_location_properties& v) {
    std::size_t seed(0);

    combine(seed, hash_std_unordered_map_std_string_dogen_generation_meta_model_backend_properties(v.backend_properties()));
    combine(seed, hash_std_unordered_map_std_string_dogen_generation_meta_model_facet_properties(v.facet_properties()));
    combine(seed, hash_std_unordered_map_std_string_dogen_generation_meta_model_archetype_properties(v.archetype_properties()));
    combine(seed, hash_std_unordered_map_std_string_dogen_generation_meta_model_denormalised_archetype_properties(v.denormalised_archetype_properties()));

    return seed;
}

} } }
