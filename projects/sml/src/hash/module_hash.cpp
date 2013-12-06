/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/hash/generation_types_hash.hpp"
#include "dogen/sml/hash/module_hash.hpp"
#include "dogen/sml/hash/origin_types_hash.hpp"
#include "dogen/sml/hash/qname_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_property_tree_ptree(const boost::property_tree::ptree& v) {
    std::size_t seed(0);
    for (const auto& node : v) {
        combine(seed, node.first);
        combine(seed, node.second.data());
        combine(seed, hash_boost_property_tree_ptree(node.second));
    }

    return seed;
}

inline std::size_t hash_std_list_dogen_sml_qname(const std::list<dogen::sml::qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace sml {

std::size_t module_hasher::hash(const module&v) {
    std::size_t seed(0);

    combine(seed, v.origin_type());
    combine(seed, v.documentation());
    combine(seed, hash_boost_property_tree_ptree(v.meta_data()));
    combine(seed, v.name());
    combine(seed, v.generation_type());
    combine(seed, hash_std_list_dogen_sml_qname(v.members()));

    return seed;
}

} }
