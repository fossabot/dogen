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
#include "dogen.modeling/test_data/meta_model/static_stereotypes_td.hpp"
#include "dogen.modeling/test_data/helpers/stereotypes_conversion_result_td.hpp"

namespace {

dogen::modeling::meta_model::static_stereotypes
create_dogen_modeling_meta_model_static_stereotypes(const unsigned int position) {
    return dogen::modeling::meta_model::static_stereotypes_generator::create(position);
}

std::list<dogen::modeling::meta_model::static_stereotypes> create_std_list_dogen_modeling_meta_model_static_stereotypes(unsigned int position) {
    std::list<dogen::modeling::meta_model::static_stereotypes> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_modeling_meta_model_static_stereotypes(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace modeling {
namespace helpers {

stereotypes_conversion_result_generator::stereotypes_conversion_result_generator() : position_(0) { }

void stereotypes_conversion_result_generator::
populate(const unsigned int position, result_type& v) {
    v.static_stereotypes(create_std_list_dogen_modeling_meta_model_static_stereotypes(position + 0));
    v.dynamic_stereotypes(create_std_list_std_string(position + 1));
}

stereotypes_conversion_result_generator::result_type
stereotypes_conversion_result_generator::create(const unsigned int position) {
    stereotypes_conversion_result r;
    stereotypes_conversion_result_generator::populate(position, r);
    return r;
}

stereotypes_conversion_result_generator::result_type*
stereotypes_conversion_result_generator::create_ptr(const unsigned int position) {
    stereotypes_conversion_result* p = new stereotypes_conversion_result();
    stereotypes_conversion_result_generator::populate(position, *p);
    return p;
}

stereotypes_conversion_result_generator::result_type
stereotypes_conversion_result_generator::operator()() {
    return create(position_++);
}

} } }
