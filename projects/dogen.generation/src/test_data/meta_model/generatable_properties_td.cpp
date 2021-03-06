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
#include "dogen.formatting/test_data/decoration_properties_td.hpp"
#include "dogen.modeling/test_data/meta_model/opaque_properties_td.hpp"
#include "dogen.generation/test_data/meta_model/artefact_properties_td.hpp"
#include "dogen.generation/test_data/meta_model/generatable_properties_td.hpp"
#include "dogen.generation/test_data/meta_model/local_archetype_location_properties_td.hpp"

namespace {

dogen::formatting::decoration_properties
create_dogen_formatting_decoration_properties(const unsigned int position) {
    return dogen::formatting::decoration_properties_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::generation::meta_model::artefact_properties
create_dogen_generation_meta_model_artefact_properties(const unsigned int position) {
    return dogen::generation::meta_model::artefact_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties> create_std_unordered_map_std_string_dogen_generation_meta_model_artefact_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::generation::meta_model::artefact_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_generation_meta_model_artefact_properties(position + i)));
    }
    return r;
}

dogen::generation::meta_model::local_archetype_location_properties
create_dogen_generation_meta_model_local_archetype_location_properties(const unsigned int position) {
    return dogen::generation::meta_model::local_archetype_location_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties> create_std_unordered_map_std_string_dogen_generation_meta_model_local_archetype_location_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::generation::meta_model::local_archetype_location_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_generation_meta_model_local_archetype_location_properties(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace generation {
namespace meta_model {

generatable_properties_generator::generatable_properties_generator() : position_(0) { }

void generatable_properties_generator::
populate(const unsigned int position, result_type& v) {
    dogen::modeling::meta_model::opaque_properties_generator::populate(position, v);
    v.decoration_properties(create_dogen_formatting_decoration_properties(position + 0));
    v.artefact_properties(create_std_unordered_map_std_string_dogen_generation_meta_model_artefact_properties(position + 1));
    v.archetype_location_properties(create_std_unordered_map_std_string_dogen_generation_meta_model_local_archetype_location_properties(position + 2));
}

generatable_properties_generator::result_type
generatable_properties_generator::create(const unsigned int position) {
    generatable_properties r;
    generatable_properties_generator::populate(position, r);
    return r;
}

generatable_properties_generator::result_type*
generatable_properties_generator::create_ptr(const unsigned int position) {
    generatable_properties* p = new generatable_properties();
    generatable_properties_generator::populate(position, *p);
    return p;
}

generatable_properties_generator::result_type
generatable_properties_generator::operator()() {
    return create(position_++);
}

} } }
