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
#include "dogen.annotations/types/annotation.hpp"
#include "dogen.annotations/types/entry_selector.hpp"
#include "dogen.annotations/types/type_repository_selector.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.generation.csharp/types/formattables/assistant_expander.hpp"

namespace dogen {
namespace generation {
namespace csharp {
namespace formattables {

assistant_expander::type_group assistant_expander::
make_type_group(const annotations::type_repository& atrp) const {
    type_group r;
    const annotations::type_repository_selector s(atrp);

    const auto ra(traits::csharp::assistant::requires_assistance());
    r.requires_assistance = s.select_type_by_name(ra);

    const auto amp(traits::csharp::assistant::method_postfix());
    r.method_postfix = s.select_type_by_name(amp);

    return r;
}

boost::optional<assistant_properties>
assistant_expander::make_assistant_properties(const type_group& tg,
    const annotations::annotation& a) const {

    assistant_properties r;
    bool has_properties(false);

    const annotations::entry_selector s(a);
    const auto& ra(tg.requires_assistance);
    if (s.has_entry(ra)) {
        has_properties = true;
        r.requires_assistance(s.get_boolean_content(ra));
    }

    const auto amp(tg.method_postfix);
    if (s.has_entry(amp)) {
        has_properties = true;
        r.method_postfix(s.get_text_content(amp));
    }

    if (has_properties)
        return r;

    return boost::optional<assistant_properties>();
}

void assistant_expander::
expand(const annotations::type_repository& atrp, model& fm) const {
    const auto tg(make_type_group(atrp));

    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());
        const auto a(e.annotation());
        const auto oap(make_assistant_properties(tg, a));
        if (!oap)
            continue;

        const auto id(pair.first);
        const auto& ap(*oap);
        fm.assistant_properties()[id] = ap;
    }
}

} } } }
