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
#ifndef DOGEN_MODELING_TYPES_HELPERS_ENDOMODEL_POST_PROCESSING_VALIDATOR_HPP
#define DOGEN_MODELING_TYPES_HELPERS_ENDOMODEL_POST_PROCESSING_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <regex>
#include <string>
#include <utility>
#include <unordered_set>
#include "dogen.modeling/types/meta_model/name.hpp"
#include "dogen.modeling/types/meta_model/languages.hpp"
#include "dogen.modeling/types/meta_model/endomodel.hpp"
#include "dogen.modeling/types/helpers/indices.hpp"
#include "dogen.modeling/types/helpers/decomposition_result.hpp"

namespace dogen {
namespace modeling {
namespace helpers {

class endomodel_post_processing_validator final {
private:
    static bool allow_spaces_in_built_in_types(const meta_model::languages l);

private:
    static void validate_string(const std::string& s,
        const std::regex& regex, bool check_not_builtin = true);
    static void validate_strings(const std::list<std::string>& strings,
        const std::regex& regex);
    static void validate_name(const meta_model::name& n,
        const std::regex& regex, const bool allow_spaces_in_built_in_types);
    static void validate_names(
        const std::list<std::pair<std::string, meta_model::name>>& names,
        const meta_model::languages l);
    static void validate_injected_names(
        const std::list<std::pair<std::string, meta_model::name>>& names);
    static void validate_meta_names(
        const std::list<std::pair<std::string, meta_model::name>>& meta_names);

    static void validate_name_tree(const std::unordered_set<std::string>&
        abstract_elements, const meta_model::languages l,
        const meta_model::name_tree& nt,
        const bool inherit_opaqueness_from_parent = false);
    static void validate_name_trees(
        const std::unordered_set<std::string>& abstract_elements,
        const meta_model::languages l,
        const std::list<std::pair<std::string, meta_model::name_tree>>& nts);

public:
    static void validate(const indices& idx, const meta_model::endomodel& im);
};

} } }

#endif
