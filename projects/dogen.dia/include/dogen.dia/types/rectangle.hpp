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
#ifndef DOGEN_DIA_TYPES_RECTANGLE_HPP
#define DOGEN_DIA_TYPES_RECTANGLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.dia/serialization/rectangle_fwd_ser.hpp"

namespace dogen {
namespace dia {

/**
 * @brief Represents a rectangle in a diagram.
 */
class rectangle final {
public:
    rectangle() = default;
    rectangle(const rectangle&) = default;
    rectangle(rectangle&&) = default;
    ~rectangle() = default;

public:
    explicit rectangle(const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::dia::rectangle& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::dia::rectangle& v, unsigned int version);

public:
    /**
     * @brief Text representation of a rectangle with a pair of X/Y coordinates.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const rectangle& rhs) const;
    bool operator!=(const rectangle& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(rectangle& other) noexcept;
    rectangle& operator=(rectangle other);

private:
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia::rectangle& lhs,
    dogen::dia::rectangle& rhs) {
    lhs.swap(rhs);
}

}

#endif
