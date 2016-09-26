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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/io/formattables/inclusion_directives_repository_io.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_directives_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.inclusion_directives_repository_factory"));

const std::string double_quote("\"");
const std::string duplicate_name("Duplicate name: ");
const std::string empty_include_directive("Include directive is empty.");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inclusion_directives_repository_factory::formatter_list_type
inclusion_directives_repository_factory::
filter_formatters(const formatter_list_type& formatters) const {
    formatter_list_type r;

    /*
     * We are only interested in formatters that generate
     * header files.
     */
    using formatters::inclusion_support_types;
    static const auto ns(inclusion_support_types::not_supported);
    for (const auto& f : formatters) {
        if (f->inclusion_support_type() != ns)
            r.push_front(f);
    }
    return r;
}

std::unordered_map<std::type_index,
                   inclusion_directives_repository_factory::formatter_list_type>
inclusion_directives_repository_factory::
filter_file_formatters_by_type_index(const formatters::container& fc) const {
    std::unordered_map<std::type_index, formatter_list_type> r;
    for (const auto& pair : fc.file_formatters_by_type_index()) {
        const auto& ti(pair.first);
        const auto& fmts(pair.second);
        r[ti] = filter_formatters(fmts);
    }
    return r;
}

void inclusion_directives_repository_factory::
insert_inclusion_directive(const std::string& id,
    const std::string& formatter_name, const std::string& directive,
    inclusion_directives_repository& idrp) const {

    if (directive.empty()) {
        std::ostringstream s;
        s << empty_include_directive << formatter_name << " for type: " << id;

        const auto msg(s.str());
        BOOST_LOG_SEV(lg, error) << msg;
        BOOST_THROW_EXCEPTION(building_error(msg));
    }

    const auto fn_dir(std::make_pair(formatter_name, directive));
    const auto pair(idrp.by_name()[id].insert(fn_dir));
    if (pair.second)
        return;

    BOOST_LOG_SEV(lg, error) << duplicate_name << id;
    BOOST_THROW_EXCEPTION(building_error(duplicate_name + id));
}

std::string inclusion_directives_repository_factory::
to_inclusion_directive(const boost::filesystem::path& p) const {
    std::ostringstream ss;
    ss << double_quote << p.generic_string() << double_quote;
    return ss.str();
}

void inclusion_directives_repository_factory::populate_repository(
    const yarn::element& e,
    const annotations::inclusion_directive_annotations_factory& factory,
    const formatter_list_type& formatters, const locator& locator,
    inclusion_directives_repository& idrp) const {

    const auto& n(e.name());
    const auto id(n.id());

    /*
     * First we extract the configuration for the generation of
     * include directives for this element. Note that we generate
     * this setting for _all elements_ even if the user did not
     * specify any meta-data (we do so via defaults).
     *
     * The question we are asking is: "does this element require
     * any inclusion directives at all, across all facets?". Not
     * all elements do; for example bool, int and so on don't
     * require any inclusions at all across all facets. If the
     * user did not override this, we default it to true because
     * normally elements require inclusion.
     */
    const auto& o(e.extensions());
    const bool required(factory.make_top_level_inclusion_required(o));
    if (!required) {
        BOOST_LOG_SEV(lg, debug) << "Inclusion not required for element.";
        return;
    }

    if (formatters.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No providers found.";
        return;
    }

    /*
     * Now we start working at the formatter level.
     */
    for (const auto& fmt : formatters) {
        const auto fmtn(fmt->ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatter: " << fmtn;

        /*
         * Does the type require an inclusion directive for this
         * specific formatter? Some types require inclusion
         * directives for some formatters, but not for others. For
         * example, we may need an include for serialising a
         * std::list, but in test data we make use of helpers and
         * thus do not require an include.
         *
         * Again, we default this to true.
         */
        const auto s(factory.make_inclusion_directive_annotations(fmtn, o));
        if (!s.inclusion_required()) {
            BOOST_LOG_SEV(lg, debug) << "Inclusion directive not required "
                                     << " for formatter: " << fmtn;
            continue;
        }

        /*
         * Do the annotations provide a "hard-coded" inclusion directive?
         * That is, the type had an hard-coded incantation for its
         * include. This is the case for system models such as boost, std
         * etc where we can't compute the inclusion directive.
         */
        std::string directive;
        if (s.inclusion_directive())
            directive = *s.inclusion_directive();
        else {
            /*
             * Finally, we have no alternative but to compute the
             * inclusion directive.
             */
            const auto path(fmt->inclusion_path(locator, n));
            directive = to_inclusion_directive(path);
        }

        BOOST_LOG_SEV(lg, debug) << "Inclusion directive: " << directive;
        insert_inclusion_directive(id, fmtn, directive, idrp);

        /*
         * If the provider is also the default for this facet and
         * element, we need to register it against the facet
         * too. Note that, for a given element type on a given
         * facet, there can only be one default - or else we'll
         * throw.
         */
        const auto cs(formatters::inclusion_support_types::canonical_support);
        const auto fctn(fmt->ownership_hierarchy().facet_name());
        if (fmt->inclusion_support_type() == cs) {
            BOOST_LOG_SEV(lg, debug) << "Inserting default for: " << fctn;
            insert_inclusion_directive(id, fctn, directive, idrp);
        }
    }
}

inclusion_directives_repository inclusion_directives_repository_factory::make(
    const dynamic::repository& drp, const formatters::container& fc,
    const locator& l, const yarn::model& m) const {

    BOOST_LOG_SEV(lg, debug) << "Making inclusion directives repository.";

    inclusion_directives_repository r;
    const auto ffti(filter_file_formatters_by_type_index(fc));
    const annotations::inclusion_directive_annotations_factory f(drp, fc);
    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        const auto id(e.name().id());
        const auto ti(std::type_index(typeid(e)));

        const auto i(ffti.find(ti));
        if (i == ffti.end()) {
            BOOST_LOG_SEV(lg, debug) << formatter_not_found_for_type << id;
            continue;
        }
        populate_repository(e, f, i->second, l, r);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished inclusion directives repository:"
                             << r;
    return r;
}

} } } }