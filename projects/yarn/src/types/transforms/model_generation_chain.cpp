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
#include <ostream>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/initial_target_chain.hpp"
#include "dogen/yarn/types/transforms/output_language_transform.hpp"
#include "dogen/yarn/types/transforms/model_generation_chain.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.transforms.model_generation_chain"));

const std::string library_dir("library");

}

namespace dogen {
namespace yarn {
namespace transforms {

std::ostream&
operator<<(std::ostream& s, const model_generation_chain::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::"
      << "descriptor_factory::type_group\"" << ", "
      << "\"references\": " << v.reference
      << " }";

    return s;
}

model_generation_chain::type_group model_generation_chain::
make_type_group(const annotations::type_repository& atrp) {
    BOOST_LOG_SEV(lg, debug) << "Creating type group.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.reference = s.select_type_by_name(traits::reference());

    BOOST_LOG_SEV(lg, debug) << "Created type group. Result: " << r;
    return r;
}

std::list<std::string> model_generation_chain::
make_user_references(const type_group& tg, const annotations::annotation& a) {

    const annotations::entry_selector s(a);
    const auto& ref(tg.reference);
    if (s.has_entry(ref))
        return s.get_text_collection_content(ref);

    return std::list<std::string>{};
}

std::vector<boost::filesystem::path> model_generation_chain::to_library_dirs(
    const std::vector<boost::filesystem::path>& data_dirs) {

    std::vector<boost::filesystem::path> r;
    r.reserve(data_dirs.size());
    for (const auto& dir : data_dirs)
        r.push_back(dir / library_dir);
    return r;
}

std::list<boost::filesystem::path> model_generation_chain::
obtain_paths_to_system_models(const context& ctx) {
    const auto library_dirs(to_library_dirs(ctx.data_directories()));

    BOOST_LOG_SEV(lg, debug) << "Creating descriptors for library models.";
    std::list<boost::filesystem::path> r;
    for (const auto& dir : library_dirs) {
        BOOST_LOG_SEV(lg, trace) << "Directory: " << dir.generic_string();

        using namespace dogen::utility::filesystem;
        const auto files(find_files(dir));
        BOOST_LOG_SEV(lg, trace) << "Found " << files.size()
                                 << " paths to library models.";

        for (const auto& f : files) {
            BOOST_LOG_SEV(lg, trace) << "Library model: " << f.generic_string();
            r.push_back(f);
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Created descriptors for library models: " << r;
    return r;
}

std::list<boost::filesystem::path>
model_generation_chain::obtain_paths_to_user_references(const context& ctx,
    const annotations::annotation& ra) {

    const auto target_dir(ctx.options().target().parent_path());
    const auto tg(make_type_group(ctx.type_repository()));
    const auto refs(make_user_references(tg, ra));
    std::list<boost::filesystem::path> r;
    for (const auto& ref : refs) {
        const auto p(target_dir / ref);
        r.push_back(p);
    }
    return r;
}

std::list<boost::filesystem::path> model_generation_chain::
obtain_paths_to_all_auxiliary_models(const context& ctx,
    const annotations::annotation& ra) {
    auto r(obtain_paths_to_user_references(ctx, ra));
    r.splice(r.end(), obtain_paths_to_system_models(ctx));
    return r;
}

std::list<model>
model_generation_chain::transform(const context& ctx) {
    /*
     * Obtain the initial target, given the user options. The initial
     * target is either a Platform Specific Model (PSM), in which case
     * the input language and the output language are one and the
     * same; or it is a Platform Independent Model (PIM), making use
     * of LAM types (the Language Agnostic Model).
     */
    const auto it(initial_target_chain::transform(ctx));

    /*
     * Obtain the paths to all reference models - system and user.
     */
    const auto& ra(it.root_module().annotation());
    const auto refs(obtain_paths_to_all_auxiliary_models(ctx, ra));

    /*
     * Expand the target according to the requested output languages.
     */
    const auto& ols(it.output_languages());
    const auto et(output_language_transform::transform(ctx, ols, it));

    /*
     * Now, process each target model in each language, and their
     * references.
     */
    for (const auto t : et) {
        BOOST_LOG_SEV(lg, debug) << "Output language: " << t.input_language();
    }

    std::list<model> r;
    return r;
}

} } }
