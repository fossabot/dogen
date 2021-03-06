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
#ifndef DOGEN_MODELING_TYPES_META_MODEL_TYPE_PARAMETERS_HPP
#define DOGEN_MODELING_TYPES_META_MODEL_TYPE_PARAMETERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.modeling/serialization/meta_model/type_parameters_fwd_ser.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

class type_parameters final {
public:
    type_parameters(const type_parameters&) = default;
    type_parameters(type_parameters&&) = default;
    ~type_parameters() = default;

public:
    type_parameters();

public:
    type_parameters(
        const bool variable_number_of_parameters,
        const unsigned int count,
        const bool always_in_heap);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::meta_model::type_parameters& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::meta_model::type_parameters& v, unsigned int version);

public:
    bool variable_number_of_parameters() const;
    void variable_number_of_parameters(const bool v);

    unsigned int count() const;
    void count(const unsigned int v);

    bool always_in_heap() const;
    void always_in_heap(const bool v);

public:
    bool operator==(const type_parameters& rhs) const;
    bool operator!=(const type_parameters& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_parameters& other) noexcept;
    type_parameters& operator=(type_parameters other);

private:
    bool variable_number_of_parameters_;
    unsigned int count_;
    bool always_in_heap_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::modeling::meta_model::type_parameters& lhs,
    dogen::modeling::meta_model::type_parameters& rhs) {
    lhs.swap(rhs);
}

}

#endif
