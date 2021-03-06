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
#ifndef DOGEN_TEMPLATING_TYPES_STITCH_PROPERTIES_HPP
#define DOGEN_TEMPLATING_TYPES_STITCH_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.formatting/types/decoration_properties.hpp"
#include "dogen.templating/types/stitch/stitching_properties.hpp"
#include "dogen.templating/serialization/stitch/properties_fwd_ser.hpp"

namespace dogen {
namespace templating {
namespace stitch {

class properties final {
public:
    properties() = default;
    properties(const properties&) = default;
    ~properties() = default;

public:
    properties(properties&& rhs);

public:
    properties(
        const boost::optional<dogen::formatting::decoration_properties>& decoration_properties,
        const dogen::templating::stitch::stitching_properties& stitching_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::templating::stitch::properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::templating::stitch::properties& v, unsigned int version);

public:
    const boost::optional<dogen::formatting::decoration_properties>& decoration_properties() const;
    boost::optional<dogen::formatting::decoration_properties>& decoration_properties();
    void decoration_properties(const boost::optional<dogen::formatting::decoration_properties>& v);
    void decoration_properties(const boost::optional<dogen::formatting::decoration_properties>&& v);

    const dogen::templating::stitch::stitching_properties& stitching_properties() const;
    dogen::templating::stitch::stitching_properties& stitching_properties();
    void stitching_properties(const dogen::templating::stitch::stitching_properties& v);
    void stitching_properties(const dogen::templating::stitch::stitching_properties&& v);

public:
    bool operator==(const properties& rhs) const;
    bool operator!=(const properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(properties& other) noexcept;
    properties& operator=(properties other);

private:
    boost::optional<dogen::formatting::decoration_properties> decoration_properties_;
    dogen::templating::stitch::stitching_properties stitching_properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::templating::stitch::properties& lhs,
    dogen::templating::stitch::properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
