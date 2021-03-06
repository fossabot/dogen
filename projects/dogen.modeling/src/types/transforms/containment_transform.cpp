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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.probing/types/scoped_prober.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/builtin.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/visitor.hpp"
#include "dogen.modeling/types/meta_model/exception.hpp"
#include "dogen.modeling/types/meta_model/primitive.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"
#include "dogen.modeling/io/meta_model/endomodel_io.hpp"
#include "dogen.modeling/types/helpers/name_builder.hpp"
#include "dogen.modeling/types/transforms/transformation_error.hpp"
#include "dogen.modeling/types/transforms/containment_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.containment_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string global_module_doc("Module that represents the global scope.");
const std::string model_already_has_global_module(
    "Found a global module in model: ");

}

namespace dogen {
namespace modeling {
namespace transforms {

template<typename AssociativeContainerOfContainable>
inline void add_containing_module_to_non_contained_entities(
    const meta_model::name& container_name,
    AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(*pair.second);
        if (!s.contained_by())
            s.contained_by(container_name);
    }
}

boost::shared_ptr<meta_model::module>
containment_transform::create_global_module(const meta_model::origin_types ot) {
    auto r(boost::make_shared<meta_model::module>());
    r->name().id("<global module>");
    r->origin_type(ot);
    r->documentation(global_module_doc);
    r->is_global_module(true);
    return r;
}

void containment_transform::
inject_global_module(meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Injecting global module for: "
                             << em.name().id();

    const auto gm(create_global_module(em.origin_type()));
    const auto gmn(gm->name());
    const auto i(em.modules().find(gmn.id()));
    if (i != em.modules().end()) {
        const auto id(em.name().id());
        BOOST_LOG_SEV(lg, error) << model_already_has_global_module << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(model_already_has_global_module + id));
    }
    em.modules().insert(std::make_pair(gmn.id(), gm));

    add_containing_module_to_non_contained_entities(gmn, em.modules());
    add_containing_module_to_non_contained_entities(gmn, em.object_templates());
    add_containing_module_to_non_contained_entities(gmn, em.builtins());
    add_containing_module_to_non_contained_entities(gmn, em.enumerations());
    add_containing_module_to_non_contained_entities(gmn, em.objects());
    add_containing_module_to_non_contained_entities(gmn, em.exceptions());
    add_containing_module_to_non_contained_entities(gmn, em.visitors());
    add_containing_module_to_non_contained_entities(gmn, em.primitives());

    BOOST_LOG_SEV(lg, debug) << "Done injecting global module";
}

void containment_transform::
transform(const context& ctx, meta_model::endomodel& em) {
    probing::scoped_transform_prober stp(lg, "containment transform",
        transform_id, em.name().id(), ctx.prober(), em);

    inject_global_module(em);

    stp.end_transform(em);
}

} } }
