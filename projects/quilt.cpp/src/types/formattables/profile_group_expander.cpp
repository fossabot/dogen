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
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_hydrator.hpp"
#include "dogen/quilt.cpp/types/formattables/profile_group_expander.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("quilt.cpp.formattables.profile_group_expander"));

const std::string invalid_facet_name("Invalid facet name: ");
const std::string invalid_formatter_name("Invalid formatter name: ");
const std::string no_profile_groups("Expected at least one profile group.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

profile_group_expander::profile_group_types
profile_group_expander::
hydrate(const std::forward_list<boost::filesystem::path>&
    data_directories) const {
    profile_group_hydrator h;
    return h.hydrate(data_directories);
}

void profile_group_expander::validate(const formatters::container& fc,
    const profile_group_types& pgs) const {
    BOOST_LOG_SEV(lg, debug) << "Validating profile groups.";

    /*
     * We expect at least one profile group. This is a simple sanity
     * check to avoid dodgy installations, etc.
     */
    if (pgs.empty()) {
        BOOST_LOG_SEV(lg, error) << no_profile_groups;
        BOOST_THROW_EXCEPTION(expansion_error(no_profile_groups));
    }

    /*
     * First we gather all facet and formater names.
     */
    std::unordered_set<std::string> facet_names;
    std::unordered_set<std::string> formatter_names;
    for (const auto ptr : fc.file_formatters()) {
        const auto& f(*ptr);
        const auto& oh(f.ownership_hierarchy());

        const auto fctn(oh.facet_name());
        facet_names.insert(fctn);

        const auto fmtn(oh.formatter_name());
        formatter_names.insert(fmtn);
    }

    /*
     * Then we check to see if the facet and formatter names used in
     * profiles have been defined.
     */
    for (const auto& pair : pgs) {
        const auto& pgn(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Validating: " << pgn;

        const auto& pg(pair.second);
        for (const auto& pair : pg.facet_profiles()) {
            const auto fctn(pair.first);
            const auto i(facet_names.find(fctn));
            if (i == facet_names.end()) {
                BOOST_LOG_SEV(lg, error) << invalid_facet_name << fctn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(invalid_facet_name + fctn));
            }
        }

        for (const auto& pair : pg.formatter_profiles()) {
            const auto fmtn(pair.first);
            const auto i(formatter_names.find(fmtn));
            if (i == formatter_names.end()) {
                BOOST_LOG_SEV(lg, error) << invalid_formatter_name << fmtn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(invalid_formatter_name + fmtn));
            }
        }

        BOOST_LOG_SEV(lg, debug) << "Validated profile group.";
    }
}

profile_group_expander::profile_group_types
profile_group_expander::merge(const profile_group_types& /*pgs*/) const {
    profile_group_expander::profile_group_types r;
    return r;
}

void profile_group_expander::
populate_model(const profile_group_types& /*pgs*/, model& /*fm*/) const {

}

void profile_group_expander::expand(
    const std::forward_list<boost::filesystem::path>& data_directories,
    const formatters::container& fc, model& fm) const {

    const auto original(hydrate(data_directories));
    validate(fc, original);
    const auto merged(merge(original));
    populate_model(merged, fm);
}

} } } }
