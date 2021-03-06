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
#include <ostream>
#include "dogen.modeling/io/meta_model/element_io.hpp"
#include "dogen.generation.cpp/io/fabric/odb_targets_io.hpp"
#include "dogen.generation.cpp/types/fabric/element_visitor.hpp"
#include "dogen.generation.cpp/types/fabric/msbuild_targets.hpp"

namespace dogen {
namespace generation {
namespace cpp {
namespace fabric {

msbuild_targets::msbuild_targets(
    const dogen::modeling::meta_model::name& name,
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::modeling::meta_model::origin_types origin_type,
    const boost::optional<dogen::modeling::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<dogen::modeling::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::modeling::meta_model::name& meta_name,
    const bool is_element_extension,
    const dogen::formatting::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& opaque_properties,
    const dogen::generation::cpp::fabric::odb_targets& odb_targets)
    : dogen::modeling::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties,
      opaque_properties),
      odb_targets_(odb_targets) { }

void msbuild_targets::accept(const dogen::modeling::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void msbuild_targets::accept(dogen::modeling::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void msbuild_targets::accept(const dogen::modeling::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void msbuild_targets::accept(dogen::modeling::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void msbuild_targets::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::generation::cpp::fabric::msbuild_targets\"" << ", "
      << "\"__parent_0__\": ";
    dogen::modeling::meta_model::element::to_stream(s);
    s << ", "
      << "\"odb_targets\": " << odb_targets_
      << " }";
}

void msbuild_targets::swap(msbuild_targets& other) noexcept {
    dogen::modeling::meta_model::element::swap(other);

    using std::swap;
    swap(odb_targets_, other.odb_targets_);
}

bool msbuild_targets::equals(const dogen::modeling::meta_model::element& other) const {
    const msbuild_targets* const p(dynamic_cast<const msbuild_targets* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool msbuild_targets::operator==(const msbuild_targets& rhs) const {
    return dogen::modeling::meta_model::element::compare(rhs) &&
        odb_targets_ == rhs.odb_targets_;
}

msbuild_targets& msbuild_targets::operator=(msbuild_targets other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::generation::cpp::fabric::odb_targets& msbuild_targets::odb_targets() const {
    return odb_targets_;
}

dogen::generation::cpp::fabric::odb_targets& msbuild_targets::odb_targets() {
    return odb_targets_;
}

void msbuild_targets::odb_targets(const dogen::generation::cpp::fabric::odb_targets& v) {
    odb_targets_ = v;
}

void msbuild_targets::odb_targets(const dogen::generation::cpp::fabric::odb_targets&& v) {
    odb_targets_ = std::move(v);
}

} } } }
