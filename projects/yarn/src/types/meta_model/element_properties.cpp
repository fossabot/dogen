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
#include "dogen/yarn/types/meta_model/element_properties.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

element_properties::element_properties(
    const dogen::formatters::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& artefact_properties)
    : decoration_properties_(decoration_properties),
      artefact_properties_(artefact_properties) { }

void element_properties::swap(element_properties& other) noexcept {
    using std::swap;
    swap(decoration_properties_, other.decoration_properties_);
    swap(artefact_properties_, other.artefact_properties_);
}

bool element_properties::operator==(const element_properties& rhs) const {
    return decoration_properties_ == rhs.decoration_properties_ &&
        artefact_properties_ == rhs.artefact_properties_;
}

element_properties& element_properties::operator=(element_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::formatters::decoration_properties& element_properties::decoration_properties() const {
    return decoration_properties_;
}

dogen::formatters::decoration_properties& element_properties::decoration_properties() {
    return decoration_properties_;
}

void element_properties::decoration_properties(const dogen::formatters::decoration_properties& v) {
    decoration_properties_ = v;
}

void element_properties::decoration_properties(const dogen::formatters::decoration_properties&& v) {
    decoration_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& element_properties::artefact_properties() const {
    return artefact_properties_;
}

std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& element_properties::artefact_properties() {
    return artefact_properties_;
}

void element_properties::artefact_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& v) {
    artefact_properties_ = v;
}

void element_properties::artefact_properties(const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>&& v) {
    artefact_properties_ = std::move(v);
}

} } }