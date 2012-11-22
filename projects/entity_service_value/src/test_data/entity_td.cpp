/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/entity_service_value/test_data/entity_td.hpp"
#include "dogen/entity_service_value/test_data/entity_versioned_key_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return position;
}

dogen::entity_service_value::entity_versioned_key
create_dogen_entity_service_value_entity_versioned_key(const unsigned int position) {
    return dogen::entity_service_value::entity_versioned_key_generator::create(position);
}

}

namespace dogen {
namespace entity_service_value {

entity_generator::entity_generator() : position_(0) { }

void entity_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
    v.versioned_key(create_dogen_entity_service_value_entity_versioned_key(position + 1));
}

entity_generator::result_type
entity_generator::create(const unsigned int position) {
    entity r;
    entity_generator::populate(position, r);
    return r;
}
entity_generator::result_type*
entity_generator::create_ptr(const unsigned int position) {
    entity* p = new entity();
    entity_generator::populate(position, *p);
    return p;
}

entity_generator::result_type
entity_generator::operator()() {
    return create(position_++);
}

} }
