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
#ifndef DOGEN_ANNOTATIONS_TYPES_KEY_VALUE_PAIR_HPP
#define DOGEN_ANNOTATIONS_TYPES_KEY_VALUE_PAIR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.annotations/types/value.hpp"
#include "dogen.annotations/serialization/key_value_pair_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class key_value_pair final : public dogen::annotations::value {
public:
    key_value_pair() = default;
    key_value_pair(const key_value_pair&) = default;
    key_value_pair(key_value_pair&&) = default;

    virtual ~key_value_pair() noexcept { }

public:
    explicit key_value_pair(const std::unordered_map<std::string, std::string>& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::key_value_pair& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::key_value_pair& v, unsigned int version);

public:
    using value::accept;

    virtual void accept(const value_visitor& v) const override;
    virtual void accept(value_visitor& v) const override;
    virtual void accept(const value_visitor& v) override;
    virtual void accept(value_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::unordered_map<std::string, std::string>& content() const;
    std::unordered_map<std::string, std::string>& content();
    void content(const std::unordered_map<std::string, std::string>& v);
    void content(const std::unordered_map<std::string, std::string>&& v);

public:
    bool operator==(const key_value_pair& rhs) const;
    bool operator!=(const key_value_pair& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::annotations::value& other) const override;

public:
    void swap(key_value_pair& other) noexcept;
    key_value_pair& operator=(key_value_pair other);

private:
    std::unordered_map<std::string, std::string> content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::key_value_pair& lhs,
    dogen::annotations::key_value_pair& rhs) {
    lhs.swap(rhs);
}

}

#endif
