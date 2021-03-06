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
#ifndef DOGEN_GENERATION_CSHARP_TYPES_FABRIC_DYNAMIC_TRANSFORM_HPP
#define DOGEN_GENERATION_CSHARP_TYPES_FABRIC_DYNAMIC_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.modeling/types/transforms/context_fwd.hpp"
#include "dogen.modeling/types/transforms/dynamic_transform_interface.hpp"

namespace dogen {
namespace generation {
namespace csharp {
namespace fabric {

class dynamic_transform final :
        public modeling::transforms::dynamic_transform_interface {
private:
    bool requires_expansion(
        const modeling::meta_model::model& m) const;

    void expand_injection(const annotations::type_repository& atrp,
        modeling::meta_model::model& m) const;

    void expand_decoration(
        const dogen::formatting::decoration_properties_factory& dpf,
        modeling::meta_model::model& m) const;

public:
    std::string id() const override;
    void transform(const modeling::transforms::context& ctx,
        const dogen::formatting::decoration_properties_factory& dpf,
        modeling::meta_model::model& m) const override;
};

} } } }

#endif
