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
#ifndef DOGEN_KNIT_TYPES_WORKFLOW_HPP
#define DOGEN_KNIT_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <list>
#include <vector>
#include <string>
#include <ostream>
#include <functional>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/yarn/types/transforms/options.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/artefact_writer_interface.hpp"

namespace dogen {
namespace knit {

/**
 * @brief Main workflow of the Knit library. Responsible for
 * transforming a high-level representation of a domain into code, in
 * one or more programming languages.
 *
 * The model which one intends to transform is known as the @e target
 * model. The workflow starts by invoking the correct front-end to
 * read in the target model and all of its dependencies. There are two
 * types of dependencies:
 *
 * @li @e explicit: specified by the options passed in; these are
 * models created by the user and any models that they, in turn,
 * depend on.
 *
 * @li @e implicit: these are known as the @e system models. They are
 * added automatically. Examples are built-ins, boost, std, etc.
 *
 * Collectively, all implicit and explicit models are referred to as
 * the @e input models. The input models read the front-end are
 * converted into the middle end representation - Yarn. They are then
 * merged it into a single, unified Yarn model, called the @e merged
 * model; all dependencies are resolved and validated.
 *
 * The workflow then instantiates all backends requested by the
 * options passed in. They use the merged model to generate source
 * code, and then outputted it to the desired destination.
 */
class workflow {
public:
    workflow() = delete;
    workflow& operator=(const workflow&) = default;
    workflow(const workflow&) = default;

public:
    typedef std::function<std::ostream& ()> output_fn;

public:
    workflow(workflow&& rhs);
    explicit workflow(const yarn::transforms::options& o);

public: // public section for testing purposes only
    /**
     * @brief Returns true if the housekeeping of generated files is
     * required, false otherwise.
     */
    bool housekeeping_required() const;

private:
    /**
     * @brief Performs a housekeeping run for the supplied directories.
     */
    void perform_housekeeping(
        const std::list<formatters::artefact>& artefacts,
        const std::list<boost::filesystem::path>& dirs) const;

    /**
     * @brief Obtains the file writer, according to configuration.
     */
    std::shared_ptr<dogen::formatters::artefact_writer_interface>
    obtain_file_writer() const;

    /**
     * @brief Outputs the artefacts to its output destination.
     */
    void write_files(
        std::shared_ptr<dogen::formatters::artefact_writer_interface> writer,
        const std::list<formatters::artefact>& artefacts) const;

public:
    /**
     * @brief Perform the entire code generation workflow.
     */
    void execute() const;

private:
    const yarn::transforms::options options_;
};

} }

#endif
