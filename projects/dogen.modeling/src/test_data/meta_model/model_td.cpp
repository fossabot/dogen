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
#include <sstream>
#include "dogen.modeling/test_data/meta_model/name_td.hpp"
#include "dogen.modeling/test_data/meta_model/model_td.hpp"
#include "dogen.modeling/test_data/meta_model/module_td.hpp"
#include "dogen.modeling/test_data/meta_model/element_td.hpp"
#include "dogen.modeling/test_data/meta_model/languages_td.hpp"
#include "dogen.modeling/test_data/meta_model/origin_types_td.hpp"
#include "dogen.modeling/test_data/meta_model/element_archetype_td.hpp"
#include "dogen.modeling/test_data/meta_model/locator_properties_td.hpp"
#include "dogen.modeling/test_data/meta_model/orm_model_properties_td.hpp"
#include "dogen.modeling/test_data/meta_model/global_archetype_location_properties_td.hpp"

namespace {

dogen::modeling::meta_model::name
create_dogen_modeling_meta_model_name(const unsigned int position) {
    return dogen::modeling::meta_model::name_generator::create(position);
}

dogen::modeling::meta_model::origin_types
create_dogen_modeling_meta_model_origin_types(const unsigned int position) {
    return dogen::modeling::meta_model::origin_types_generator::create(position);
}

std::unordered_map<dogen::modeling::meta_model::name, dogen::modeling::meta_model::origin_types> create_std_unordered_map_dogen_modeling_meta_model_name_dogen_modeling_meta_model_origin_types(unsigned int position) {
    std::unordered_map<dogen::modeling::meta_model::name, dogen::modeling::meta_model::origin_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_modeling_meta_model_name(position + i), create_dogen_modeling_meta_model_origin_types(position + i)));
    }
    return r;
}

std::unordered_set<dogen::modeling::meta_model::name> create_std_unordered_set_dogen_modeling_meta_model_name(unsigned int position) {
    std::unordered_set<dogen::modeling::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_modeling_meta_model_name(position + i));
    }
    return r;
}

dogen::modeling::meta_model::element*
create_dogen_modeling_meta_model_element_ptr(const unsigned int position) {
    return dogen::modeling::meta_model::element_generator::create_ptr(position);
}

boost::shared_ptr<dogen::modeling::meta_model::element>
create_boost_shared_ptr_dogen_modeling_meta_model_element(unsigned int position) {
    boost::shared_ptr<dogen::modeling::meta_model::element> r(
        create_dogen_modeling_meta_model_element_ptr(position));
    return r;
}

std::vector<boost::shared_ptr<dogen::modeling::meta_model::element> > create_std_vector_boost_shared_ptr_dogen_modeling_meta_model_element(unsigned int position) {
    std::vector<boost::shared_ptr<dogen::modeling::meta_model::element> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_modeling_meta_model_element(position + i));
    }
    return r;
}

dogen::modeling::meta_model::module*
create_dogen_modeling_meta_model_module_ptr(const unsigned int position) {
    return dogen::modeling::meta_model::module_generator::create_ptr(position);
}

boost::shared_ptr<dogen::modeling::meta_model::module>
create_boost_shared_ptr_dogen_modeling_meta_model_module(unsigned int position) {
    boost::shared_ptr<dogen::modeling::meta_model::module> r(
        create_dogen_modeling_meta_model_module_ptr(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

dogen::modeling::meta_model::languages
create_dogen_modeling_meta_model_languages(const unsigned int position) {
    return dogen::modeling::meta_model::languages_generator::create(position);
}

dogen::modeling::meta_model::orm_model_properties
create_dogen_modeling_meta_model_orm_model_properties(const unsigned int position) {
    return dogen::modeling::meta_model::orm_model_properties_generator::create(position);
}

boost::optional<dogen::modeling::meta_model::orm_model_properties>
create_boost_optional_dogen_modeling_meta_model_orm_model_properties(unsigned int position) {
    boost::optional<dogen::modeling::meta_model::orm_model_properties> r(
        create_dogen_modeling_meta_model_orm_model_properties(position));
    return r;
}

dogen::modeling::meta_model::element_archetype
create_dogen_modeling_meta_model_element_archetype(const unsigned int position) {
    return dogen::modeling::meta_model::element_archetype_generator::create(position);
}

std::unordered_set<dogen::modeling::meta_model::element_archetype> create_std_unordered_set_dogen_modeling_meta_model_element_archetype(unsigned int position) {
    std::unordered_set<dogen::modeling::meta_model::element_archetype> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_modeling_meta_model_element_archetype(position + i));
    }
    return r;
}

dogen::modeling::meta_model::locator_properties
create_dogen_modeling_meta_model_locator_properties(const unsigned int position) {
    return dogen::modeling::meta_model::locator_properties_generator::create(position);
}

dogen::modeling::meta_model::global_archetype_location_properties
create_dogen_modeling_meta_model_global_archetype_location_properties(const unsigned int position) {
    return dogen::modeling::meta_model::global_archetype_location_properties_generator::create(position);
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_modeling_meta_model_name(position + 0));
    v.meta_name(create_dogen_modeling_meta_model_name(position + 1));
    v.references(create_std_unordered_map_dogen_modeling_meta_model_name_dogen_modeling_meta_model_origin_types(position + 2));
    v.leaves(create_std_unordered_set_dogen_modeling_meta_model_name(position + 3));
    v.elements(create_std_vector_boost_shared_ptr_dogen_modeling_meta_model_element(position + 4));
    v.root_module(create_boost_shared_ptr_dogen_modeling_meta_model_module(position + 5));
    v.module_ids(create_std_unordered_set_std_string(position + 6));
    v.has_generatable_types(create_bool(position + 7));
    v.input_language(create_dogen_modeling_meta_model_languages(position + 8));
    v.output_language(create_dogen_modeling_meta_model_languages(position + 9));
    v.orm_properties(create_boost_optional_dogen_modeling_meta_model_orm_model_properties(position + 10));
    v.enabled_archetype_for_element(create_std_unordered_set_dogen_modeling_meta_model_element_archetype(position + 11));
    v.locator_properties(create_dogen_modeling_meta_model_locator_properties(position + 12));
    v.global_archetype_location_properties(create_dogen_modeling_meta_model_global_archetype_location_properties(position + 13));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

} } }
