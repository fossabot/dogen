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
#include "dogen.modeling/types/helpers/name_factory.hpp"
#include "dogen.generation.csharp/types/fabric/assistant.hpp"
#include "dogen.generation.csharp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.csharp/types/fabric/assistant_factory.hpp"

namespace {

const std::string assistant_name("Assistant");

}

namespace dogen {
namespace generation {
namespace csharp {
namespace fabric {

boost::shared_ptr<modeling::meta_model::element>
assistant_factory::make(const modeling::meta_model::model& m) const {
    modeling::helpers::name_factory nf;
    const auto n(nf.build_element_in_model(m.name(), assistant_name));

    auto r(boost::make_shared<assistant>());
    r->name(n);
    r->meta_name(meta_name_factory::make_assistant_name());
    r->origin_type(modeling::meta_model::origin_types::target);

    return r;
}

} } } }
