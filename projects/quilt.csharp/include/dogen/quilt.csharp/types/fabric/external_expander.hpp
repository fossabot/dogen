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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FABRIC_EXTERNAL_EXPANDER_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FABRIC_EXTERNAL_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/external_expander_interface.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

class external_expander final : public yarn::external_expander_interface {
private:
    bool requires_expansion(const yarn::intermediate_model& im) const;

    void expand_injection(const annotations::type_repository& atrp,
        yarn::intermediate_model& im) const;

    void expand_decoration(
        const dogen::formatters::decoration_properties_factory& dpf,
        yarn::intermediate_model& im) const;

public:
    std::string id() const override;
    void expand(const annotations::type_repository& atrp,
        const dogen::formatters::decoration_properties_factory& dpf,
        yarn::intermediate_model& im) const override;
};

} } } }

#endif