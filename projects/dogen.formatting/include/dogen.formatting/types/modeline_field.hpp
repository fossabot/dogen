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
#ifndef DOGEN_FORMATTING_TYPES_MODELINE_FIELD_HPP
#define DOGEN_FORMATTING_TYPES_MODELINE_FIELD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.formatting/serialization/modeline_field_fwd_ser.hpp"

namespace dogen {
namespace formatting {

/**
 * @brief Entry in a modeline.
 */
class modeline_field final {
public:
    modeline_field() = default;
    modeline_field(const modeline_field&) = default;
    modeline_field(modeline_field&&) = default;
    ~modeline_field() = default;

public:
    modeline_field(
        const std::string& name,
        const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::formatting::modeline_field& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::formatting::modeline_field& v, unsigned int version);

public:
    /**
     * @brief Name of the field.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Value for the field. Can be empty.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const modeline_field& rhs) const;
    bool operator!=(const modeline_field& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(modeline_field& other) noexcept;
    modeline_field& operator=(modeline_field other);

private:
    std::string name_;
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::formatting::modeline_field& lhs,
    dogen::formatting::modeline_field& rhs) {
    lhs.swap(rhs);
}

}

#endif
