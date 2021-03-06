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
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.generation/types/meta_model/model.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::modeling::meta_model::element>& lhs,
const boost::shared_ptr<dogen::modeling::meta_model::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::modeling::meta_model::module>& lhs,
const boost::shared_ptr<dogen::modeling::meta_model::module>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace generation {
namespace meta_model {

model::model()
    : has_generatable_types_(static_cast<bool>(0)),
      input_language_(static_cast<dogen::modeling::meta_model::languages>(0)),
      output_language_(static_cast<dogen::modeling::meta_model::languages>(0)) { }

model::model(model&& rhs)
    : name_(std::move(rhs.name_)),
      meta_name_(std::move(rhs.meta_name_)),
      references_(std::move(rhs.references_)),
      leaves_(std::move(rhs.leaves_)),
      elements_(std::move(rhs.elements_)),
      root_module_(std::move(rhs.root_module_)),
      module_ids_(std::move(rhs.module_ids_)),
      has_generatable_types_(std::move(rhs.has_generatable_types_)),
      input_language_(std::move(rhs.input_language_)),
      output_language_(std::move(rhs.output_language_)),
      orm_properties_(std::move(rhs.orm_properties_)),
      enabled_archetype_for_element_(std::move(rhs.enabled_archetype_for_element_)),
      locator_properties_(std::move(rhs.locator_properties_)),
      global_archetype_location_properties_(std::move(rhs.global_archetype_location_properties_)) { }

model::model(
    const dogen::modeling::meta_model::name& name,
    const dogen::modeling::meta_model::name& meta_name,
    const std::unordered_map<dogen::modeling::meta_model::name, dogen::modeling::meta_model::origin_types>& references,
    const std::unordered_set<dogen::modeling::meta_model::name>& leaves,
    const std::vector<boost::shared_ptr<dogen::modeling::meta_model::element> >& elements,
    const boost::shared_ptr<dogen::modeling::meta_model::module>& root_module,
    const std::unordered_set<std::string>& module_ids,
    const bool has_generatable_types,
    const dogen::modeling::meta_model::languages input_language,
    const dogen::modeling::meta_model::languages output_language,
    const boost::optional<dogen::modeling::meta_model::orm_model_properties>& orm_properties,
    const std::unordered_set<dogen::generation::meta_model::element_archetype>& enabled_archetype_for_element,
    const dogen::generation::meta_model::locator_properties& locator_properties,
    const dogen::generation::meta_model::global_archetype_location_properties& global_archetype_location_properties)
    : name_(name),
      meta_name_(meta_name),
      references_(references),
      leaves_(leaves),
      elements_(elements),
      root_module_(root_module),
      module_ids_(module_ids),
      has_generatable_types_(has_generatable_types),
      input_language_(input_language),
      output_language_(output_language),
      orm_properties_(orm_properties),
      enabled_archetype_for_element_(enabled_archetype_for_element),
      locator_properties_(locator_properties),
      global_archetype_location_properties_(global_archetype_location_properties) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(meta_name_, other.meta_name_);
    swap(references_, other.references_);
    swap(leaves_, other.leaves_);
    swap(elements_, other.elements_);
    swap(root_module_, other.root_module_);
    swap(module_ids_, other.module_ids_);
    swap(has_generatable_types_, other.has_generatable_types_);
    swap(input_language_, other.input_language_);
    swap(output_language_, other.output_language_);
    swap(orm_properties_, other.orm_properties_);
    swap(enabled_archetype_for_element_, other.enabled_archetype_for_element_);
    swap(locator_properties_, other.locator_properties_);
    swap(global_archetype_location_properties_, other.global_archetype_location_properties_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        meta_name_ == rhs.meta_name_ &&
        references_ == rhs.references_ &&
        leaves_ == rhs.leaves_ &&
        elements_ == rhs.elements_ &&
        root_module_ == rhs.root_module_ &&
        module_ids_ == rhs.module_ids_ &&
        has_generatable_types_ == rhs.has_generatable_types_ &&
        input_language_ == rhs.input_language_ &&
        output_language_ == rhs.output_language_ &&
        orm_properties_ == rhs.orm_properties_ &&
        enabled_archetype_for_element_ == rhs.enabled_archetype_for_element_ &&
        locator_properties_ == rhs.locator_properties_ &&
        global_archetype_location_properties_ == rhs.global_archetype_location_properties_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::modeling::meta_model::name& model::name() const {
    return name_;
}

dogen::modeling::meta_model::name& model::name() {
    return name_;
}

void model::name(const dogen::modeling::meta_model::name& v) {
    name_ = v;
}

void model::name(const dogen::modeling::meta_model::name&& v) {
    name_ = std::move(v);
}

const dogen::modeling::meta_model::name& model::meta_name() const {
    return meta_name_;
}

dogen::modeling::meta_model::name& model::meta_name() {
    return meta_name_;
}

void model::meta_name(const dogen::modeling::meta_model::name& v) {
    meta_name_ = v;
}

void model::meta_name(const dogen::modeling::meta_model::name&& v) {
    meta_name_ = std::move(v);
}

const std::unordered_map<dogen::modeling::meta_model::name, dogen::modeling::meta_model::origin_types>& model::references() const {
    return references_;
}

std::unordered_map<dogen::modeling::meta_model::name, dogen::modeling::meta_model::origin_types>& model::references() {
    return references_;
}

void model::references(const std::unordered_map<dogen::modeling::meta_model::name, dogen::modeling::meta_model::origin_types>& v) {
    references_ = v;
}

void model::references(const std::unordered_map<dogen::modeling::meta_model::name, dogen::modeling::meta_model::origin_types>&& v) {
    references_ = std::move(v);
}

const std::unordered_set<dogen::modeling::meta_model::name>& model::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::modeling::meta_model::name>& model::leaves() {
    return leaves_;
}

void model::leaves(const std::unordered_set<dogen::modeling::meta_model::name>& v) {
    leaves_ = v;
}

void model::leaves(const std::unordered_set<dogen::modeling::meta_model::name>&& v) {
    leaves_ = std::move(v);
}

const std::vector<boost::shared_ptr<dogen::modeling::meta_model::element> >& model::elements() const {
    return elements_;
}

std::vector<boost::shared_ptr<dogen::modeling::meta_model::element> >& model::elements() {
    return elements_;
}

void model::elements(const std::vector<boost::shared_ptr<dogen::modeling::meta_model::element> >& v) {
    elements_ = v;
}

void model::elements(const std::vector<boost::shared_ptr<dogen::modeling::meta_model::element> >&& v) {
    elements_ = std::move(v);
}

const boost::shared_ptr<dogen::modeling::meta_model::module>& model::root_module() const {
    return root_module_;
}

boost::shared_ptr<dogen::modeling::meta_model::module>& model::root_module() {
    return root_module_;
}

void model::root_module(const boost::shared_ptr<dogen::modeling::meta_model::module>& v) {
    root_module_ = v;
}

void model::root_module(const boost::shared_ptr<dogen::modeling::meta_model::module>&& v) {
    root_module_ = std::move(v);
}

const std::unordered_set<std::string>& model::module_ids() const {
    return module_ids_;
}

std::unordered_set<std::string>& model::module_ids() {
    return module_ids_;
}

void model::module_ids(const std::unordered_set<std::string>& v) {
    module_ids_ = v;
}

void model::module_ids(const std::unordered_set<std::string>&& v) {
    module_ids_ = std::move(v);
}

bool model::has_generatable_types() const {
    return has_generatable_types_;
}

void model::has_generatable_types(const bool v) {
    has_generatable_types_ = v;
}

dogen::modeling::meta_model::languages model::input_language() const {
    return input_language_;
}

void model::input_language(const dogen::modeling::meta_model::languages v) {
    input_language_ = v;
}

dogen::modeling::meta_model::languages model::output_language() const {
    return output_language_;
}

void model::output_language(const dogen::modeling::meta_model::languages v) {
    output_language_ = v;
}

const boost::optional<dogen::modeling::meta_model::orm_model_properties>& model::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::modeling::meta_model::orm_model_properties>& model::orm_properties() {
    return orm_properties_;
}

void model::orm_properties(const boost::optional<dogen::modeling::meta_model::orm_model_properties>& v) {
    orm_properties_ = v;
}

void model::orm_properties(const boost::optional<dogen::modeling::meta_model::orm_model_properties>&& v) {
    orm_properties_ = std::move(v);
}

const std::unordered_set<dogen::generation::meta_model::element_archetype>& model::enabled_archetype_for_element() const {
    return enabled_archetype_for_element_;
}

std::unordered_set<dogen::generation::meta_model::element_archetype>& model::enabled_archetype_for_element() {
    return enabled_archetype_for_element_;
}

void model::enabled_archetype_for_element(const std::unordered_set<dogen::generation::meta_model::element_archetype>& v) {
    enabled_archetype_for_element_ = v;
}

void model::enabled_archetype_for_element(const std::unordered_set<dogen::generation::meta_model::element_archetype>&& v) {
    enabled_archetype_for_element_ = std::move(v);
}

const dogen::generation::meta_model::locator_properties& model::locator_properties() const {
    return locator_properties_;
}

dogen::generation::meta_model::locator_properties& model::locator_properties() {
    return locator_properties_;
}

void model::locator_properties(const dogen::generation::meta_model::locator_properties& v) {
    locator_properties_ = v;
}

void model::locator_properties(const dogen::generation::meta_model::locator_properties&& v) {
    locator_properties_ = std::move(v);
}

const dogen::generation::meta_model::global_archetype_location_properties& model::global_archetype_location_properties() const {
    return global_archetype_location_properties_;
}

dogen::generation::meta_model::global_archetype_location_properties& model::global_archetype_location_properties() {
    return global_archetype_location_properties_;
}

void model::global_archetype_location_properties(const dogen::generation::meta_model::global_archetype_location_properties& v) {
    global_archetype_location_properties_ = v;
}

void model::global_archetype_location_properties(const dogen::generation::meta_model::global_archetype_location_properties&& v) {
    global_archetype_location_properties_ = std::move(v);
}

} } }
