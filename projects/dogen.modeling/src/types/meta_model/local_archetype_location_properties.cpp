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
#include "dogen.modeling/types/meta_model/local_archetype_location_properties.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

local_archetype_location_properties::local_archetype_location_properties(local_archetype_location_properties&& rhs)
    : facet_enabled_(std::move(rhs.facet_enabled_)),
      archetype_enabled_(std::move(rhs.archetype_enabled_)),
      facet_overwrite_(std::move(rhs.facet_overwrite_)),
      archetype_overwrite_(std::move(rhs.archetype_overwrite_)) { }

local_archetype_location_properties::local_archetype_location_properties(
    const boost::optional<bool>& facet_enabled,
    const boost::optional<bool>& archetype_enabled,
    const boost::optional<bool>& facet_overwrite,
    const boost::optional<bool>& archetype_overwrite)
    : facet_enabled_(facet_enabled),
      archetype_enabled_(archetype_enabled),
      facet_overwrite_(facet_overwrite),
      archetype_overwrite_(archetype_overwrite) { }

void local_archetype_location_properties::swap(local_archetype_location_properties& other) noexcept {
    using std::swap;
    swap(facet_enabled_, other.facet_enabled_);
    swap(archetype_enabled_, other.archetype_enabled_);
    swap(facet_overwrite_, other.facet_overwrite_);
    swap(archetype_overwrite_, other.archetype_overwrite_);
}

bool local_archetype_location_properties::operator==(const local_archetype_location_properties& rhs) const {
    return facet_enabled_ == rhs.facet_enabled_ &&
        archetype_enabled_ == rhs.archetype_enabled_ &&
        facet_overwrite_ == rhs.facet_overwrite_ &&
        archetype_overwrite_ == rhs.archetype_overwrite_;
}

local_archetype_location_properties& local_archetype_location_properties::operator=(local_archetype_location_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<bool>& local_archetype_location_properties::facet_enabled() const {
    return facet_enabled_;
}

boost::optional<bool>& local_archetype_location_properties::facet_enabled() {
    return facet_enabled_;
}

void local_archetype_location_properties::facet_enabled(const boost::optional<bool>& v) {
    facet_enabled_ = v;
}

void local_archetype_location_properties::facet_enabled(const boost::optional<bool>&& v) {
    facet_enabled_ = std::move(v);
}

const boost::optional<bool>& local_archetype_location_properties::archetype_enabled() const {
    return archetype_enabled_;
}

boost::optional<bool>& local_archetype_location_properties::archetype_enabled() {
    return archetype_enabled_;
}

void local_archetype_location_properties::archetype_enabled(const boost::optional<bool>& v) {
    archetype_enabled_ = v;
}

void local_archetype_location_properties::archetype_enabled(const boost::optional<bool>&& v) {
    archetype_enabled_ = std::move(v);
}

const boost::optional<bool>& local_archetype_location_properties::facet_overwrite() const {
    return facet_overwrite_;
}

boost::optional<bool>& local_archetype_location_properties::facet_overwrite() {
    return facet_overwrite_;
}

void local_archetype_location_properties::facet_overwrite(const boost::optional<bool>& v) {
    facet_overwrite_ = v;
}

void local_archetype_location_properties::facet_overwrite(const boost::optional<bool>&& v) {
    facet_overwrite_ = std::move(v);
}

const boost::optional<bool>& local_archetype_location_properties::archetype_overwrite() const {
    return archetype_overwrite_;
}

boost::optional<bool>& local_archetype_location_properties::archetype_overwrite() {
    return archetype_overwrite_;
}

void local_archetype_location_properties::archetype_overwrite(const boost::optional<bool>& v) {
    archetype_overwrite_ = v;
}

void local_archetype_location_properties::archetype_overwrite(const boost::optional<bool>&& v) {
    archetype_overwrite_ = std::move(v);
}

} } }
