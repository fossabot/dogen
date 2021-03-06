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
#include "dogen.utility/io/unordered_set_io.hpp"
#include "dogen.utility/io/unordered_map_io.hpp"
#include "dogen.probing/types/scoped_prober.hpp"
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.modeling/io/meta_model/model_io.hpp"
#include "dogen.modeling/io/meta_model/facet_properties_io.hpp"
#include "dogen.modeling/types/transforms/transformation_error.hpp"
#include "dogen.modeling/types/transforms/enablement_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.enablement_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string global_configuration_not_found(
    "Could not find global enablement configuration for formatter: ");
const std::string duplicate_archetype_name("Duplicate archetype name: ");
const std::string duplicate_element_archetype("Duplicate element archetype: ");
const std::string meta_name_not_found("Meta-name not found: ");

}

namespace dogen {
namespace modeling {
namespace transforms {

bool enablement_transform::
is_element_disabled(const modeling::meta_model::element& e) {
    /*
     * We're only interested in modules as these are the only elements
     * that can be enabled/disabled based on their state.
     */
    const auto ptr(dynamic_cast<const modeling::meta_model::module*>(&e));
    if (!ptr)
        return false;

    const auto& m(*ptr);

    /*
     * Ignore the global module. This is just a pseudo module that is
     * used as a top-level container and has no expression in code.
     */
    if (m.is_global_module())
        return true;

    /*
     * Modules are only generatable for the purposes of
     * documentation. Set them to disabled if there is no
     * documentation.
     */
    if (m.documentation().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Module does not have documentation. "
                                 << "Disabling it. Id: " << m.name().id();
        return true;
    }
    return false;
}

void enablement_transform::compute_enablement_for_artefact_properties(
    const std::unordered_map<std::string,
    meta_model::denormalised_archetype_properties>&
    global_archetype_location_properties,
    const std::unordered_map<std::string,
    meta_model::local_archetype_location_properties>&
    local_archetype_location_properties,
    const std::string& archetype,
    meta_model::artefact_properties& ap) {

    const auto& galp(global_archetype_location_properties);
    const auto& lalp(local_archetype_location_properties);

    /*
     * As we may be processing a segmented entity, not all formatting
     * need to be present in the local configuration. For example, an
     * entity may be segmented into an object and a forward
     * declaration; in this case, when we are processing the object,
     * we will still see the forward declaration formatting in the
     * formattable configuration since the transformer merged all
     * segments of the element together. However, these are not
     * present in the local configuration container because we are
     * only processing one segment at a time. So, we need to ignore
     * the formatting for the segments we are not processing.
     */
    const auto j(lalp.find(archetype));
    if (j == lalp.end()) {
        BOOST_LOG_SEV(lg, debug) << "Ignoring formatter: " << archetype;
        return;
    }
    const auto& lc(j->second);

    /*
     * Global configuration must always be present for all archetypes.
     */
    const auto i(galp.find(archetype));
    if (i == galp.end()) {
        BOOST_LOG_SEV(lg, error) << global_configuration_not_found << archetype;
        BOOST_THROW_EXCEPTION(
            transformation_error(global_configuration_not_found + archetype));
    }
    const auto gc(i->second);

    /*
     * If the overwrite flag is set locally at the archetype or facet
     * level, then that takes priority. If not, first check to see if
     * its set globally at the archetype level; if so, it takes
     * priority. Finally, if nothing else is set, use the global facet
     * default.
     *
     * The rationale here is as follows: users can set facets to
     * overwrite locally on a model element (either directly of via
     * profiles); for example, for an handcrafted class, we want to
     * set overwrite to false at the element level. This is normally
     * done via a profile, but can be conceivable be done directly for
     * less common configurations - for example adding manual support
     * for IO for a handcrafted type. The global archetype overwrite
     * flag is a bit less useful - we haven't got a use case for it
     * just yet but it is added for (foolish) consistency. Finally,
     * the global facet level overwrite flag is useful for the general
     * case of code generated code. Having said that, it does not make
     * a lot of sense to set overwrite globally to false.
     *
     * Note that the overwrite flag is only relevant if enabled is
     * true. It is not used otherwise. We set it up before enablement
     * just so we don't have to worry about handling the ""continue""
     * statements.
     */

    if (lc.archetype_overwrite())
        ap.overwrite(*lc.archetype_overwrite());
    else if (lc.facet_overwrite())
        ap.overwrite(*lc.facet_overwrite());
    else if (gc.archetype_overwrite())
        ap.overwrite(*gc.archetype_overwrite());
    else
        ap.overwrite(gc.facet_overwrite());

    /*
     * If either the entire backend or facet have been disabled
     * globally, the formatter will be disabled too.
     */
    if (!gc.backend_enabled() || !gc.facet_enabled()) {
        ap.enabled(false);
        return;
    }

    /*
     * Check to see if the formatter enablement field has been set
     * locally. If so, it takes precedence over the facet
     * configuration.
     */
    if (lc.archetype_enabled()) {
        ap.enabled(*lc.archetype_enabled());
        return;
    }

    /*
     * Check to see if the facet enablement field has been set
     * locally. If so, it takes precedence over global
     * configuration.
     */
    if (lc.facet_enabled()) {
        ap.enabled(*lc.facet_enabled());
        return;
    }

    /*
     * If nothing else has been set, use the global enablement
     * flag for the formatter.
     */
    ap.enabled(gc.archetype_enabled());
    BOOST_LOG_SEV(lg, debug) << "Enablement for: " << archetype
                             << " value: " << ap.enabled();
}

void enablement_transform::compute_enablement_for_element(
    const std::unordered_map<std::string,
    annotations::archetype_locations_group>& archetype_locations_by_meta_name,
    const std::unordered_map<std::string,
    meta_model::denormalised_archetype_properties>&
    global_archetype_location_properties,
    std::unordered_set<meta_model::element_archetype>&
    enabled_archetype_for_element, meta_model::element& e) {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Started computing enablement: " << id;

    /*
     * On some very special cases we may disable an element based on
     * its state. If so, there is nothing to do.
     */
    if (is_element_disabled(e))
        return;

    const auto mt(e.meta_name().id());
    BOOST_LOG_SEV(lg, debug) << "Meta-type: " << mt;

    /*
     * Not all elements have formatting. For example, object templates
     * do not have any at present. This manifests itself as an absence
     * of archetype locations mapped against this element. If it is
     * so, skip the element.
     */
    if (e.archetype_location_properties().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Element has no formatting, "
                                 << " so nothing enable.";
        return;
    }

    const auto& mn(e.meta_name());
    const auto j(archetype_locations_by_meta_name.find(mn.id()));
    if (j == archetype_locations_by_meta_name.end()) {
        BOOST_LOG_SEV(lg, error) << meta_name_not_found << mn.id();
        BOOST_THROW_EXCEPTION(
            transformation_error(meta_name_not_found + mn.id()));
    }
    const auto& cal(j->second.canonical_archetype_locations());

    /*
     * Now, for each element, obtain the local configuration.
     */
    const auto& galp(global_archetype_location_properties);
    const auto lalp(e.archetype_location_properties());

    /*
     * Once we got both the global and the local configuration, we can
     * then compute the enablement values for this formattable, across
     * all the supported formatting.
     */
    auto& eafe(enabled_archetype_for_element);
    for (auto& pair : e.artefact_properties()) {
        const auto arch(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Processing archetype: " << arch;

        auto& art_props(pair.second);
        compute_enablement_for_artefact_properties(galp, lalp, arch, art_props);

        if (!art_props.enabled()) {
            BOOST_LOG_SEV(lg, debug) << "Archetype not enabled.";
            continue;
        }

        BOOST_LOG_SEV(lg, debug) << "Archetype is enabled.";

        /*
         * If we are enabled, we need to update the enablement
         * index. First, we update it with the concrete archetype.
         */
        using meta_model::element_archetype;
        auto inserted(eafe.insert(element_archetype(id, arch)).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_archetype << arch
                                     << " " << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype_name
                    + arch + " " + id));
        }

        /*
         * Then, if this archetype maps to a canonical archetype, we
         * create an entry for the canonical archetype as well.
         */
        const auto k(cal.find(arch));
        if (k == cal.end())
            continue;

        inserted = eafe.insert(element_archetype(id, k->second)).second;
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_element_archetype << arch
                                     << " " << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_archetype_name
                    + arch + " " + id));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished computing enablement.";
}

void enablement_transform::
transform(const context& ctx, meta_model::model& m) {
    probing::scoped_transform_prober stp(lg, "enablement new_transform",
        transform_id, m.name().id(), ctx.prober(), m);

    const auto& alrp(ctx.archetype_location_repository());
    const auto& albmn(alrp.archetype_locations_by_meta_name());
    const auto& galp(m.global_archetype_location_properties()
        .denormalised_archetype_properties());
    std::unordered_set<meta_model::element_archetype> eafe;
    for(auto& ptr : m.elements()) {
        auto& e(*ptr);
        compute_enablement_for_element(albmn, galp, eafe, e);
    }

    m.enabled_archetype_for_element(eafe);
    stp.end_transform(m);
}

} } }
