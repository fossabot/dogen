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
#include "dogen.annotations/types/entry_template.hpp"

namespace dogen {
namespace annotations {

entry_template::entry_template()
    : kind_(static_cast<dogen::annotations::template_kinds>(0)) { }

entry_template::entry_template(
    const dogen::annotations::name& name,
    const dogen::annotations::archetype_location& archetype_location,
    const std::list<std::string>& untyped_value,
    const dogen::annotations::template_kinds kind)
    : name_(name),
      archetype_location_(archetype_location),
      untyped_value_(untyped_value),
      kind_(kind) { }

void entry_template::swap(entry_template& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(archetype_location_, other.archetype_location_);
    swap(untyped_value_, other.untyped_value_);
    swap(kind_, other.kind_);
}

bool entry_template::operator==(const entry_template& rhs) const {
    return name_ == rhs.name_ &&
        archetype_location_ == rhs.archetype_location_ &&
        untyped_value_ == rhs.untyped_value_ &&
        kind_ == rhs.kind_;
}

entry_template& entry_template::operator=(entry_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::annotations::name& entry_template::name() const {
    return name_;
}

dogen::annotations::name& entry_template::name() {
    return name_;
}

void entry_template::name(const dogen::annotations::name& v) {
    name_ = v;
}

void entry_template::name(const dogen::annotations::name&& v) {
    name_ = std::move(v);
}

const dogen::annotations::archetype_location& entry_template::archetype_location() const {
    return archetype_location_;
}

dogen::annotations::archetype_location& entry_template::archetype_location() {
    return archetype_location_;
}

void entry_template::archetype_location(const dogen::annotations::archetype_location& v) {
    archetype_location_ = v;
}

void entry_template::archetype_location(const dogen::annotations::archetype_location&& v) {
    archetype_location_ = std::move(v);
}

const std::list<std::string>& entry_template::untyped_value() const {
    return untyped_value_;
}

std::list<std::string>& entry_template::untyped_value() {
    return untyped_value_;
}

void entry_template::untyped_value(const std::list<std::string>& v) {
    untyped_value_ = v;
}

void entry_template::untyped_value(const std::list<std::string>&& v) {
    untyped_value_ = std::move(v);
}

dogen::annotations::template_kinds entry_template::kind() const {
    return kind_;
}

void entry_template::kind(const dogen::annotations::template_kinds v) {
    kind_ = v;
}

} }
