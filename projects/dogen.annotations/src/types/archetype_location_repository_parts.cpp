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
#include "dogen.annotations/types/archetype_location_repository_parts.hpp"

namespace dogen {
namespace annotations {

archetype_location_repository_parts::archetype_location_repository_parts(
    const std::list<dogen::annotations::archetype_location>& archetype_locations,
    const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& archetype_locations_by_meta_name,
    const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_family,
    const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_intra_backend_segment)
    : archetype_locations_(archetype_locations),
      archetype_locations_by_meta_name_(archetype_locations_by_meta_name),
      archetype_locations_by_family_(archetype_locations_by_family),
      archetype_locations_by_intra_backend_segment_(archetype_locations_by_intra_backend_segment) { }

void archetype_location_repository_parts::swap(archetype_location_repository_parts& other) noexcept {
    using std::swap;
    swap(archetype_locations_, other.archetype_locations_);
    swap(archetype_locations_by_meta_name_, other.archetype_locations_by_meta_name_);
    swap(archetype_locations_by_family_, other.archetype_locations_by_family_);
    swap(archetype_locations_by_intra_backend_segment_, other.archetype_locations_by_intra_backend_segment_);
}

bool archetype_location_repository_parts::operator==(const archetype_location_repository_parts& rhs) const {
    return archetype_locations_ == rhs.archetype_locations_ &&
        archetype_locations_by_meta_name_ == rhs.archetype_locations_by_meta_name_ &&
        archetype_locations_by_family_ == rhs.archetype_locations_by_family_ &&
        archetype_locations_by_intra_backend_segment_ == rhs.archetype_locations_by_intra_backend_segment_;
}

archetype_location_repository_parts& archetype_location_repository_parts::operator=(archetype_location_repository_parts other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::annotations::archetype_location>& archetype_location_repository_parts::archetype_locations() const {
    return archetype_locations_;
}

std::list<dogen::annotations::archetype_location>& archetype_location_repository_parts::archetype_locations() {
    return archetype_locations_;
}

void archetype_location_repository_parts::archetype_locations(const std::list<dogen::annotations::archetype_location>& v) {
    archetype_locations_ = v;
}

void archetype_location_repository_parts::archetype_locations(const std::list<dogen::annotations::archetype_location>&& v) {
    archetype_locations_ = std::move(v);
}

const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& archetype_location_repository_parts::archetype_locations_by_meta_name() const {
    return archetype_locations_by_meta_name_;
}

std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& archetype_location_repository_parts::archetype_locations_by_meta_name() {
    return archetype_locations_by_meta_name_;
}

void archetype_location_repository_parts::archetype_locations_by_meta_name(const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& v) {
    archetype_locations_by_meta_name_ = v;
}

void archetype_location_repository_parts::archetype_locations_by_meta_name(const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>&& v) {
    archetype_locations_by_meta_name_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_location_repository_parts::archetype_locations_by_family() const {
    return archetype_locations_by_family_;
}

std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_location_repository_parts::archetype_locations_by_family() {
    return archetype_locations_by_family_;
}

void archetype_location_repository_parts::archetype_locations_by_family(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& v) {
    archetype_locations_by_family_ = v;
}

void archetype_location_repository_parts::archetype_locations_by_family(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >&& v) {
    archetype_locations_by_family_ = std::move(v);
}

const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_location_repository_parts::archetype_locations_by_intra_backend_segment() const {
    return archetype_locations_by_intra_backend_segment_;
}

std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_location_repository_parts::archetype_locations_by_intra_backend_segment() {
    return archetype_locations_by_intra_backend_segment_;
}

void archetype_location_repository_parts::archetype_locations_by_intra_backend_segment(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& v) {
    archetype_locations_by_intra_backend_segment_ = v;
}

void archetype_location_repository_parts::archetype_locations_by_intra_backend_segment(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >&& v) {
    archetype_locations_by_intra_backend_segment_ = std::move(v);
}

} }
