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
#include "dogen.probing/test_data/metrics_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

unsigned long create_unsigned_long(const unsigned int position) {
    return static_cast<unsigned long>(position);
}

dogen::probing::metrics*
create_dogen_probing_metrics_ptr(const unsigned int) {
    return nullptr;
}

boost::shared_ptr<dogen::probing::metrics>
create_boost_shared_ptr_dogen_probing_metrics(unsigned int position) {
    boost::shared_ptr<dogen::probing::metrics> r(
        create_dogen_probing_metrics_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::probing::metrics> > create_std_list_boost_shared_ptr_dogen_probing_metrics(unsigned int position) {
    std::list<boost::shared_ptr<dogen::probing::metrics> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_probing_metrics(position + i));
    }
    return r;
}

}

namespace dogen {
namespace probing {

metrics_generator::metrics_generator() : position_(0) { }

void metrics_generator::
populate(const unsigned int position, result_type& v) {
    v.transform_id(create_std_string(position + 0));
    v.model_id(create_std_string(position + 1));
    v.guid(create_std_string(position + 2));
    v.start(create_unsigned_long(position + 3));
    v.end(create_unsigned_long(position + 4));
    v.children(create_std_list_boost_shared_ptr_dogen_probing_metrics(position + 5));
}

metrics_generator::result_type
metrics_generator::create(const unsigned int position) {
    metrics r;
    metrics_generator::populate(position, r);
    return r;
}

metrics_generator::result_type*
metrics_generator::create_ptr(const unsigned int position) {
    metrics* p = new metrics();
    metrics_generator::populate(position, *p);
    return p;
}

metrics_generator::result_type
metrics_generator::operator()() {
    return create(position_++);
}

} }
