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
#include "dogen.modeling/hash/meta_model/name_hash.hpp"
#include "dogen.modeling/hash/meta_model/object_hash.hpp"
#include "dogen.modeling/hash/meta_model/element_hash.hpp"
#include "dogen.modeling/hash/meta_model/attribute_hash.hpp"
#include "dogen.modeling/hash/meta_model/type_parameters_hash.hpp"
#include "dogen.modeling/hash/meta_model/orm_object_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_modeling_meta_model_attribute(const std::list<dogen::modeling::meta_model::attribute>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_unordered_map_dogen_modeling_meta_model_name_std_list_dogen_modeling_meta_model_attribute(const std::unordered_map<dogen::modeling::meta_model::name, std::list<dogen::modeling::meta_model::attribute> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, hash_std_list_dogen_modeling_meta_model_attribute(i.second));
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_modeling_meta_model_name(const boost::optional<dogen::modeling::meta_model::name>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_list_dogen_modeling_meta_model_name(const std::list<dogen::modeling::meta_model::name>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_modeling_meta_model_orm_object_properties(const boost::optional<dogen::modeling::meta_model::orm_object_properties>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

std::size_t object_hasher::hash(const object& v) {
    std::size_t seed(0);

    combine(seed, dynamic_cast<const dogen::modeling::meta_model::element&>(v));

    combine(seed, hash_std_list_dogen_modeling_meta_model_attribute(v.all_attributes()));
    combine(seed, hash_std_list_dogen_modeling_meta_model_attribute(v.local_attributes()));
    combine(seed, hash_std_unordered_map_dogen_modeling_meta_model_name_std_list_dogen_modeling_meta_model_attribute(v.inherited_attributes()));
    combine(seed, v.is_immutable());
    combine(seed, v.is_fluent());
    combine(seed, hash_boost_optional_dogen_modeling_meta_model_name(v.base_visitor()));
    combine(seed, hash_boost_optional_dogen_modeling_meta_model_name(v.derived_visitor()));
    combine(seed, v.is_visitation_root());
    combine(seed, v.is_visitation_leaf());
    combine(seed, hash_std_list_dogen_modeling_meta_model_name(v.transparent_associations()));
    combine(seed, hash_std_list_dogen_modeling_meta_model_name(v.opaque_associations()));
    combine(seed, v.is_parent());
    combine(seed, v.is_child());
    combine(seed, v.is_leaf());
    combine(seed, v.is_final());
    combine(seed, v.is_abstract());
    combine(seed, v.in_inheritance_relationship());
    combine(seed, hash_std_list_dogen_modeling_meta_model_name(v.root_parents()));
    combine(seed, hash_std_list_dogen_modeling_meta_model_name(v.parents()));
    combine(seed, hash_std_list_dogen_modeling_meta_model_name(v.leaves()));
    combine(seed, v.type_parameters());
    combine(seed, v.is_associative_container());
    combine(seed, hash_std_list_dogen_modeling_meta_model_name(v.object_templates()));
    combine(seed, hash_std_list_dogen_modeling_meta_model_name(v.associative_container_keys()));
    combine(seed, v.provides_opaqueness());
    combine(seed, v.can_be_primitive_underlier());
    combine(seed, hash_boost_optional_dogen_modeling_meta_model_orm_object_properties(v.orm_properties()));

    return seed;
}

} } }
