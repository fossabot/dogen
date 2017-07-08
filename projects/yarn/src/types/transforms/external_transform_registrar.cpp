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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/transforms/registrar_error.hpp"
#include "dogen/yarn/types/transforms/external_transform_registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("yarn.transforms.external_transform_registrar"));

const std::string no_transforms("No transforms provided.");
const std::string null_frontend("Frontend supplied is null.");

}

namespace dogen {
namespace yarn {
namespace transforms {

void external_transform_registrar::register_external_transform(
    std::shared_ptr<const external_transform_interface> ee) {
    // note: not logging by design
    if (!ee)
        BOOST_THROW_EXCEPTION(registrar_error(null_frontend));

    external_transforms_.push_back(ee);
}

void external_transform_registrar::validate() const {
    if (external_transforms_.empty()) {
        BOOST_LOG_SEV(lg, debug) << no_transforms;
        BOOST_THROW_EXCEPTION(registrar_error(no_transforms));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";

    BOOST_LOG_SEV(lg, debug) << "Found "
                             << external_transforms_.size()
                             << " registered external transforms. Details: ";

    for (const auto& ee : external_transforms_)
        BOOST_LOG_SEV(lg, debug) << "id: '" << ee->id() << "'";
}

std::list<std::shared_ptr<const external_transform_interface>>
external_transform_registrar::external_transforms() const {
    return external_transforms_;
}

} } }
