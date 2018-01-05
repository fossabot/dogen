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
#include <boost/algorithm/string.hpp>
#include "dogen.formatting/io/infix_configuration_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen {
namespace formatting {

std::ostream& operator<<(std::ostream& s, const infix_configuration& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::formatting::infix_configuration\"" << ", "
      << "\"first\": " << "\"" << tidy_up_string(v.first()) << "\"" << ", "
      << "\"not_first\": " << "\"" << tidy_up_string(v.not_first()) << "\"" << ", "
      << "\"not_last\": " << "\"" << tidy_up_string(v.not_last()) << "\"" << ", "
      << "\"last\": " << "\"" << tidy_up_string(v.last()) << "\""
      << " }";
    return(s);
}

} }