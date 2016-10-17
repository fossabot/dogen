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
#ifndef DOGEN_ANNOTATIONS_TYPES_TYPE_HPP
#define DOGEN_ANNOTATIONS_TYPES_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/name.hpp"
#include "dogen/annotations/types/value_fwd.hpp"
#include "dogen/annotations/types/scope_types.hpp"
#include "dogen/annotations/types/value_types.hpp"
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/annotations/serialization/type_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Defines the domain of values.
 */
class type final {
public:
    type(const type&) = default;
    type(type&&) = default;
    ~type() = default;

public:
    type();

public:
    type(
        const dogen::annotations::name& name,
        const dogen::annotations::value_types value_type,
        const dogen::annotations::scope_types scope,
        const dogen::annotations::archetype_location& archetype_location,
        const boost::shared_ptr<dogen::annotations::value>& default_value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::type& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::type& v, unsigned int version);

public:
    /**
     * @brief Name of the field to which this definition applies.
     */
    /**@{*/
    const dogen::annotations::name& name() const;
    dogen::annotations::name& name();
    void name(const dogen::annotations::name& v);
    void name(const dogen::annotations::name&& v);
    /**@}*/

    /**
     * @brief Type of the field.
     */
    /**@{*/
    dogen::annotations::value_types value_type() const;
    void value_type(const dogen::annotations::value_types v);
    /**@}*/

    /**
     * @brief Valid scopes where the field may be present.
     */
    /**@{*/
    dogen::annotations::scope_types scope() const;
    void scope(const dogen::annotations::scope_types v);
    /**@}*/

    /**
     * @brief The ownership hierarchy information for this field.
     */
    /**@{*/
    const dogen::annotations::archetype_location& archetype_location() const;
    dogen::annotations::archetype_location& archetype_location();
    void archetype_location(const dogen::annotations::archetype_location& v);
    void archetype_location(const dogen::annotations::archetype_location&& v);
    /**@}*/

    /**
     * @brief Default value for the field, if any.
     */
    /**@{*/
    const boost::shared_ptr<dogen::annotations::value>& default_value() const;
    boost::shared_ptr<dogen::annotations::value>& default_value();
    void default_value(const boost::shared_ptr<dogen::annotations::value>& v);
    void default_value(const boost::shared_ptr<dogen::annotations::value>&& v);
    /**@}*/

public:
    bool operator==(const type& rhs) const;
    bool operator!=(const type& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type& other) noexcept;
    type& operator=(type other);

private:
    dogen::annotations::name name_;
    dogen::annotations::value_types value_type_;
    dogen::annotations::scope_types scope_;
    dogen::annotations::archetype_location archetype_location_;
    boost::shared_ptr<dogen::annotations::value> default_value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::type& lhs,
    dogen::annotations::type& rhs) {
    lhs.swap(rhs);
}

}

#endif
