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
#include <boost/throw_exception.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/io/list_io.hpp"
#include "dogen.utility/io/vector_io.hpp"
#include "dogen.external.dia/types/validation_error.hpp"
#include "dogen.external.dia/types/validator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("external.dia.validator"));

const std::string no_uml_type("No UML type.");

}

namespace dogen {
namespace external {
namespace dia {

void validator::validate_uml(const processed_object& po) {
    /*
     * All objects must have a valid UML type.
     */
    if (po.dia_object_type() == dia_object_types::invalid) {
        BOOST_LOG_SEV(lg, error) << no_uml_type;
        BOOST_THROW_EXCEPTION(validation_error(no_uml_type));
    }
}

void validator::validate(const processed_object& po) {
    validate_uml(po);
}

void validator::validate(const std::list<processed_object>& pos) {
    for (const auto& po : pos)
        validate(po);
}

} } }
