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
#include "dogen.modeling/types/helpers/mapping_set_repository.hpp"

namespace dogen {
namespace modeling {
namespace helpers {

mapping_set_repository::mapping_set_repository(
    const dogen::modeling::helpers::mapping_set& default_mapping_set,
    const std::unordered_map<std::string, dogen::modeling::helpers::mapping_set>& by_name)
    : default_mapping_set_(default_mapping_set),
      by_name_(by_name) { }

void mapping_set_repository::swap(mapping_set_repository& other) noexcept {
    using std::swap;
    swap(default_mapping_set_, other.default_mapping_set_);
    swap(by_name_, other.by_name_);
}

bool mapping_set_repository::operator==(const mapping_set_repository& rhs) const {
    return default_mapping_set_ == rhs.default_mapping_set_ &&
        by_name_ == rhs.by_name_;
}

mapping_set_repository& mapping_set_repository::operator=(mapping_set_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::modeling::helpers::mapping_set& mapping_set_repository::default_mapping_set() const {
    return default_mapping_set_;
}

dogen::modeling::helpers::mapping_set& mapping_set_repository::default_mapping_set() {
    return default_mapping_set_;
}

void mapping_set_repository::default_mapping_set(const dogen::modeling::helpers::mapping_set& v) {
    default_mapping_set_ = v;
}

void mapping_set_repository::default_mapping_set(const dogen::modeling::helpers::mapping_set&& v) {
    default_mapping_set_ = std::move(v);
}

const std::unordered_map<std::string, dogen::modeling::helpers::mapping_set>& mapping_set_repository::by_name() const {
    return by_name_;
}

std::unordered_map<std::string, dogen::modeling::helpers::mapping_set>& mapping_set_repository::by_name() {
    return by_name_;
}

void mapping_set_repository::by_name(const std::unordered_map<std::string, dogen::modeling::helpers::mapping_set>& v) {
    by_name_ = v;
}

void mapping_set_repository::by_name(const std::unordered_map<std::string, dogen::modeling::helpers::mapping_set>&& v) {
    by_name_ = std::move(v);
}

} } }
