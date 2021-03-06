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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen.generation/io/meta_model/denormalised_archetype_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<bool>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen {
namespace generation {
namespace meta_model {

std::ostream& operator<<(std::ostream& s, const denormalised_archetype_properties& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::generation::meta_model::denormalised_archetype_properties\"" << ", "
      << "\"backend_enabled\": " << v.backend_enabled() << ", "
      << "\"backend_directory\": " << "\"" << tidy_up_string(v.backend_directory()) << "\"" << ", "
      << "\"facet_enabled\": " << v.facet_enabled() << ", "
      << "\"facet_overwrite\": " << v.facet_overwrite() << ", "
      << "\"facet_directory\": " << "\"" << tidy_up_string(v.facet_directory()) << "\"" << ", "
      << "\"facet_postfix\": " << "\"" << tidy_up_string(v.facet_postfix()) << "\"" << ", "
      << "\"archetype_enabled\": " << v.archetype_enabled() << ", "
      << "\"archetype_overwrite\": " << v.archetype_overwrite() << ", "
      << "\"archetype_postfix\": " << "\"" << tidy_up_string(v.archetype_postfix()) << "\""
      << " }";
    return(s);
}

} } }
