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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/mapper.hpp"
#include "dogen/yarn/types/mappings_hydrator.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/output_language_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.output_language_transform"));

}

namespace dogen {
namespace yarn {
namespace transforms {

intermediate_model output_language_transform::transform(
    const context& ctx, const languages ol, const intermediate_model& im) {
    const mapper mp(ctx.mapping_repository());
    return mp.map(im.input_language(), ol, im);
}

std::list<intermediate_model>
output_language_transform::transform(const context& ctx,
    const std::list<languages> ol, const intermediate_model& im) {
    std::list<intermediate_model> r;
    for (const auto l : ol) {
        r.push_back(transform(ctx, l, im));
    }
    return r;
}

} } }