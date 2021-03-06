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
#include "dogen.modeling/test_data/meta_model/orm_database_systems_td.hpp"
#include "dogen.modeling/test_data/meta_model/orm_attribute_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

boost::optional<bool>
create_boost_optional_bool(unsigned int position) {
    boost::optional<bool> r(
        create_bool(position));
    return r;
}

dogen::modeling::meta_model::orm_database_systems
create_dogen_modeling_meta_model_orm_database_systems(const unsigned int position) {
    return dogen::modeling::meta_model::orm_database_systems_generator::create(position);
}

std::unordered_map<dogen::modeling::meta_model::orm_database_systems, std::string> create_std_unordered_map_dogen_modeling_meta_model_orm_database_systems_std_string(unsigned int position) {
    std::unordered_map<dogen::modeling::meta_model::orm_database_systems, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_modeling_meta_model_orm_database_systems(position + i), create_std_string(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

orm_attribute_properties_generator::orm_attribute_properties_generator() : position_(0) { }

void orm_attribute_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.column_name(create_std_string(position + 0));
    v.is_primary_key(create_bool(position + 1));
    v.is_nullable(create_boost_optional_bool(position + 2));
    v.type_overrides(create_std_unordered_map_dogen_modeling_meta_model_orm_database_systems_std_string(position + 3));
    v.is_composite(create_bool(position + 4));
}

orm_attribute_properties_generator::result_type
orm_attribute_properties_generator::create(const unsigned int position) {
    orm_attribute_properties r;
    orm_attribute_properties_generator::populate(position, r);
    return r;
}

orm_attribute_properties_generator::result_type*
orm_attribute_properties_generator::create_ptr(const unsigned int position) {
    orm_attribute_properties* p = new orm_attribute_properties();
    orm_attribute_properties_generator::populate(position, *p);
    return p;
}

orm_attribute_properties_generator::result_type
orm_attribute_properties_generator::operator()() {
    return create(position_++);
}

} } }
