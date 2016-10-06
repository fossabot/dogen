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
#ifndef DOGEN_YARN_DIA_TYPES_BUILDER_HPP
#define DOGEN_YARN_DIA_TYPES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn.dia/types/context.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"
#include "dogen/yarn.dia/types/profiled_object.hpp"

namespace dogen {
namespace yarn {
namespace dia {

class builder {
public:
    builder(const std::string& model_name, const std::string& external_modules,
        const bool is_target, const dynamic::workflow& w,
        const std::unordered_map<std::string, std::list<std::string>>&
        child_id_to_parent_ids);

private:
    yarn::module create_module_for_model(const yarn::name& n,
        const yarn::origin_types ot) const;

    yarn::intermediate_model initialise_model(const std::string& model_name,
        const std::string& external_modules, bool is_target) const;

    yarn::module& module_for_name(const yarn::name& n);
    yarn::module& module_for_id(const std::string& id);

    void update_documentation(const processed_object& o);

public:
    void add(const profiled_object& o);
    yarn::intermediate_model build();

private:
    const dynamic::workflow& dynamic_workflow_;
    context context_;
};

} } }

#endif
