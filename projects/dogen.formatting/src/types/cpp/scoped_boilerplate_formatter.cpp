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
#include "dogen.formatting/types/cpp/scoped_boilerplate_formatter.hpp"

namespace dogen {
namespace formatting {
namespace cpp {

scoped_boilerplate_formatter::scoped_boilerplate_formatter(std::ostream& s,
    const boost::optional<decoration_properties>& odp,
    const std::list<std::string>& includes, const std::string& header_guard)
    : stream_(s), decoration_properties_(odp), includes_(includes),
      header_guard_(header_guard) {

    if (!decoration_properties_)
        return;

    const auto& dc(*decoration_properties_);
    formatter_.format_begin(stream_, dc, includes, header_guard);
}

scoped_boilerplate_formatter::~scoped_boilerplate_formatter() {
    if (!decoration_properties_)
        return;

    const auto& dc(*decoration_properties_);
    formatter_.format_end(stream_, dc, header_guard_);
}

} } }
