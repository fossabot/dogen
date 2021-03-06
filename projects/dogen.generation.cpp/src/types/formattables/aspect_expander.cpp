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
#include "dogen.utility/io/unordered_map_io.hpp"
#include "dogen.annotations/types/entry_selector.hpp"
#include "dogen.annotations/types/type_repository_selector.hpp"
#include "dogen.annotations/io/type_io.hpp"
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/io/formattables/aspect_properties_io.hpp"
#include "dogen.generation.cpp/types/formattables/aspect_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formattables.aspect_expander"));

}

namespace dogen {
namespace generation {
namespace cpp {
namespace formattables {

std::ostream&
operator<<(std::ostream& s, const aspect_expander::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::generation::cpp::formattables::"
      << "aspect_expander::type_group\"" << ", "
      << "\"requires_manual_default_constructor\": "
      << v.requires_manual_default_constructor << ", "
      << "\"requires_manual_move_constructor\": "
      << v.requires_manual_move_constructor << ", "
      << "\"requires_stream_manipulators\": "
      << v.requires_stream_manipulators
      << " }";

    return s;
}

aspect_expander::type_group aspect_expander::
make_type_group(const annotations::type_repository& atrp) const {
    type_group r;

    const annotations::type_repository_selector rs(atrp);
    typedef traits::cpp::aspect aspect;

    const auto& rmdc(aspect::requires_manual_default_constructor());
    r.requires_manual_default_constructor = rs.select_type_by_name(rmdc);

    const auto& rmmc(aspect::requires_manual_move_constructor());
    r.requires_manual_move_constructor = rs.select_type_by_name(rmmc);

    const auto& rsm(aspect::requires_stream_manipulators());
    r.requires_stream_manipulators = rs.select_type_by_name(rsm);

    return r;
}

boost::optional<aspect_properties> aspect_expander::
make_aspect_properties(const type_group& tg,
    const annotations::annotation& a) const {
    aspect_properties r;

    const annotations::entry_selector s(a);
    bool found_any(false);

    if (s.has_entry(tg.requires_manual_default_constructor))
        found_any = true;

    r.requires_manual_default_constructor(
        s.get_boolean_content_or_default(
            tg.requires_manual_default_constructor));

    if (s.has_entry(tg.requires_manual_move_constructor))
        found_any = true;

    r.requires_manual_move_constructor(
        s.get_boolean_content_or_default(
            tg.requires_manual_move_constructor));

    if (s.has_entry(tg.requires_stream_manipulators))
        found_any = true;

    r.requires_stream_manipulators(
        s.get_boolean_content_or_default(
            tg.requires_stream_manipulators));

    if (found_any)
        return r;

    return boost::optional<aspect_properties>();
}

aspect_expander::aspect_properties_type aspect_expander::
obtain_aspect_properties(const annotations::type_repository& atrp,
    const std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating aspect configuration.";

    const auto tg(make_type_group(atrp));
    aspect_properties_type r;
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        const auto& segment(*formattable.master_segment());
        const auto ap(make_aspect_properties(tg, segment.annotation()));
        if (ap)
            r[id] = *ap;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating aspect properties. "
                             << "Result: " << r;
    return r;
}

void aspect_expander::walk_name_tree(const modeling::meta_model::name_tree& nt,
    const bool is_top_level, const aspect_properties_type& element_aps,
    aspect_properties& ap) const {

    for (const auto& c : nt.children())
        walk_name_tree(c, false/*is_top_level*/, element_aps, ap);

    if (is_top_level && nt.is_current_simple_type())
        ap.requires_manual_default_constructor(true);

    const auto i(element_aps.find(nt.current().id()));
    if (i == element_aps.end())
        return;

    const auto element_ap(i->second);
    if (element_ap.requires_stream_manipulators())
        ap.requires_stream_manipulators(true);

    if (!is_top_level)
        return;

    if (element_ap.requires_manual_default_constructor())
        ap.requires_manual_default_constructor(true);

    if (element_ap.requires_manual_move_constructor())
        ap.requires_manual_move_constructor(true);
}

aspect_properties aspect_expander::compute_aspect_properties(
    const aspect_properties_type& element_aps,
    const std::list<modeling::meta_model::attribute>& attrs) const {

    aspect_properties r;
    for (const auto attr : attrs) {
        const auto& nt(attr.parsed_type());
        walk_name_tree(nt, true/*is_top_level*/, element_aps, r);
    }
    return r;
}

void aspect_expander::populate_aspect_properties(const std::string& element_id,
    const aspect_properties_type& element_aps,
    formattable& formattable) const {

    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << element_id;
    auto& eprops(formattable.element_properties());

    /*
     * We only want to process the master segment; extensions can
     * be ignored.
     */
    const auto& ms(formattable.master_segment());

    /*
     * We only need to generate the aspect configuration for
     * elements of the target model. However, we can't perform
     * this after reduction because the aspect configurations must
     * be build prior to reduction or else we will not get aspects
     * for referenced models.
     */
    if (ms->origin_type() != modeling::meta_model::origin_types::target)
        return;

    /*
     * We are only interested in yarn objects; all other element
     * types do not need helpers.
     */
    const auto ptr(dynamic_cast<const modeling::meta_model::object*>(ms.get()));
    if (ptr == nullptr)
        return;

    const auto& o(*ptr) ;

    /*
     * Update the aspect properties.
     */
    const auto& attrs(o.local_attributes());
    const auto element_ap(compute_aspect_properties(element_aps, attrs));
    eprops.aspect_properties(element_ap);
}

void aspect_expander::
populate_aspect_properties(const aspect_properties_type& element_aps,
    std::unordered_map<std::string, formattable>& formattables) const {

    for (auto& pair : formattables) {
        const auto id(pair.first);
        auto& formattable(pair.second);
        populate_aspect_properties(id, element_aps, formattable);
    }
}

void aspect_expander::
expand(const annotations::type_repository& atrp, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expansion.";
    const auto element_aps(obtain_aspect_properties(atrp, fm.formattables()));
    populate_aspect_properties(element_aps, fm.formattables());
    BOOST_LOG_SEV(lg, debug) << "Finished expansion.";
}

} } } }
