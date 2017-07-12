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
#include <boost/algorithm/string/join.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/quilt.csharp/types/formattables/workflow.hpp"
#include "dogen/quilt.csharp/types/formatters/workflow.hpp"
#include "dogen/quilt.csharp/types/formattables/locator.hpp"
#include "dogen/quilt.csharp/types/kernel.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(dogen::quilt::csharp::traits::kernel()));

const std::string empty;
const std::string dot(".");

}

namespace dogen {
namespace quilt {
namespace csharp {

kernel::~kernel() noexcept { }

formattables::model kernel::create_formattables_model(
    const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const formatters::repository& frp, const formattables::locator& l,
    const yarn::meta_model::model& m) const {
    formattables::workflow fw;
    return fw.execute(atrp, ra, frp, l, m);
}

std::string kernel::id() const {
    return archetype_location().kernel();
}

std::list<dogen::formatters::artefact>
kernel::format(const annotations::type_repository& /*atrp*/,
    const annotations::annotation_groups_factory& /*agf*/,
    const dogen::formatters::repository& /*drp*/,
    const formattables::model& fm) const {
    formatters::workflow wf;
    return wf.execute(fm);
}

annotations::archetype_location kernel::archetype_location() const {
    static annotations::archetype_location r(traits::family(), traits::kernel(),
        empty/*facet*/, empty/*archetype*/);
    return r;
}

std::forward_list<annotations::archetype_location>
kernel::archetype_locations() const {
    return formatters::workflow::registrar().archetype_locations();
}

yarn::meta_model::languages kernel::language() const {
    return yarn::meta_model::languages::csharp;
}

kernel_output kernel::generate(const options::knitting_options& ko,
    const annotations::type_repository& atrp,
    const annotations::annotation_groups_factory& agf,
    const dogen::formatters::repository& drp,
    const bool enable_kernel_directories,
    const yarn::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started kernel.";

    const auto ra(m.root_module().annotation());
    const auto& frp(formatters::workflow::registrar().formatter_repository());

    const auto mn(m.name());
    const auto odp(ko.output_directory_path());
    const bool ekd(enable_kernel_directories);
    const formattables::locator l(odp, atrp, frp, ra, mn, m.module_ids(), ekd);
    const auto fm(create_formattables_model(atrp, ra, frp, l, m));

    kernel_output r;
    r.artefacts(format(atrp, agf, drp, fm));
    r.managed_directories().push_back(l.project_path());

    BOOST_LOG_SEV(lg, debug) << "Finished kernel.";
    return r;
}

} } }
