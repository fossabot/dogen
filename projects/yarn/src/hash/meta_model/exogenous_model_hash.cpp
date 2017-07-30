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
#include "dogen/yarn/hash/meta_model/module_hash.hpp"
#include "dogen/yarn/hash/meta_model/object_hash.hpp"
#include "dogen/yarn/hash/meta_model/builtin_hash.hpp"
#include "dogen/yarn/hash/meta_model/concept_hash.hpp"
#include "dogen/yarn/hash/meta_model/exception_hash.hpp"
#include "dogen/yarn/hash/meta_model/primitive_hash.hpp"
#include "dogen/annotations/hash/scribble_group_hash.hpp"
#include "dogen/yarn/hash/meta_model/enumeration_hash.hpp"
#include "dogen/yarn/hash/meta_model/exogenous_model_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_module(const std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_module(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_module(i));
    }
    return seed;
}

inline std::size_t hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_concept(const std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_concept(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_concept(i));
    }
    return seed;
}

inline std::size_t hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_builtin(const std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_builtin(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_builtin(i));
    }
    return seed;
}

inline std::size_t hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_enumeration(const std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_enumeration(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_enumeration(i));
    }
    return seed;
}

inline std::size_t hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_primitive(const std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_primitive(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_primitive(i));
    }
    return seed;
}

inline std::size_t hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_object(const std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_object(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_object(i));
    }
    return seed;
}

inline std::size_t hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_exception(const std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_exception(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_exception(i));
    }
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

std::size_t exogenous_model_hasher::hash(const exogenous_model& v) {
    std::size_t seed(0);

    combine(seed, hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_module(v.modules()));
    combine(seed, hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_concept(v.concepts()));
    combine(seed, hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_builtin(v.builtins()));
    combine(seed, hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_enumeration(v.enumerations()));
    combine(seed, hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_primitive(v.primitives()));
    combine(seed, hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_object(v.objects()));
    combine(seed, hash_std_list_std_pair_dogen_annotations_scribble_group_dogen_yarn_meta_model_exception(v.exceptions()));

    return seed;
}

} } }