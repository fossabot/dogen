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
#include "dogen.utility/log/logger.hpp"
#include "dogen.probing/types/scoped_prober.hpp"
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/builtin.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/exception.hpp"
#include "dogen.modeling/types/meta_model/primitive.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"
#include "dogen.modeling/io/meta_model/model_io.hpp"
#include "dogen.modeling/types/transforms/generability_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.generability_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen {
namespace modeling {
namespace transforms {

bool generability_transform::is_generatable(const meta_model::element& e) {
    const auto ot(e.origin_type());
    return ot == meta_model::origin_types::target;
}

bool generability_transform::
has_generatable_types(const meta_model::model& m) {
    for (const auto ptr : m.elements()) {
        if (is_generatable(*ptr))
            return true;
    }

    return false;
}

void generability_transform::
transform(const context& ctx, meta_model::model& m) {
    probing::scoped_transform_prober stp(lg, "generability transform",
        transform_id, m.name().id(), ctx.prober(), m);
    m.has_generatable_types(has_generatable_types(m));
    stp.end_transform(m);
}

} } }
