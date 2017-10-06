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
#include "dogen/yarn/types/meta_model/archetype_location_properties.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

archetype_location_properties::archetype_location_properties(
    const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& facet_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_properties>& archetype_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::kernel_properties>& kernel_properties)
    : facet_properties_(facet_properties),
      archetype_properties_(archetype_properties),
      kernel_properties_(kernel_properties) { }

void archetype_location_properties::swap(archetype_location_properties& other) noexcept {
    using std::swap;
    swap(facet_properties_, other.facet_properties_);
    swap(archetype_properties_, other.archetype_properties_);
    swap(kernel_properties_, other.kernel_properties_);
}

bool archetype_location_properties::operator==(const archetype_location_properties& rhs) const {
    return facet_properties_ == rhs.facet_properties_ &&
        archetype_properties_ == rhs.archetype_properties_ &&
        kernel_properties_ == rhs.kernel_properties_;
}

archetype_location_properties& archetype_location_properties::operator=(archetype_location_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& archetype_location_properties::facet_properties() const {
    return facet_properties_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& archetype_location_properties::facet_properties() {
    return facet_properties_;
}

void archetype_location_properties::facet_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>& v) {
    facet_properties_ = v;
}

void archetype_location_properties::facet_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties>&& v) {
    facet_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_properties>& archetype_location_properties::archetype_properties() const {
    return archetype_properties_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::archetype_properties>& archetype_location_properties::archetype_properties() {
    return archetype_properties_;
}

void archetype_location_properties::archetype_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_properties>& v) {
    archetype_properties_ = v;
}

void archetype_location_properties::archetype_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::archetype_properties>&& v) {
    archetype_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::meta_model::kernel_properties>& archetype_location_properties::kernel_properties() const {
    return kernel_properties_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::kernel_properties>& archetype_location_properties::kernel_properties() {
    return kernel_properties_;
}

void archetype_location_properties::kernel_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::kernel_properties>& v) {
    kernel_properties_ = v;
}

void archetype_location_properties::kernel_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::kernel_properties>&& v) {
    kernel_properties_ = std::move(v);
}

} } }