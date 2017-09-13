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
#include <list>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/annotations/types/type_repository_factory.hpp"
#include "dogen/yarn/types/code_generator.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/workflow.hpp"

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.workflow"));

const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string target_postfix("_target");
const std::string merged("merged_");
const std::string invalid_archive_type("Invalid or unexpected archive type");
const std::string incorrect_stdout_options(
    "Configuration for output to stdout is incorrect");
const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace knit {

workflow::workflow(workflow&& rhs)
    : options_(std::move(rhs.options_)) { }

workflow::
workflow(const yarn::transforms::options& o) : options_(o) {}

bool workflow::housekeeping_required() const {
    return options_.delete_extra_files();
}

void workflow::perform_housekeeping(
    const std::list<formatters::artefact>& artefacts,
    const std::list<boost::filesystem::path>& dirs) const {

    std::set<boost::filesystem::path> expected_files;
    for (const auto a : artefacts) {
        expected_files.insert(a.path().generic_string());
        for (const auto& d : a.dependencies())
            expected_files.insert(d.generic_string());
    }

    const auto& ip(options_.ignore_patterns());
    std::list<std::string> ignore_patterns(ip.begin(), ip.end());
    housekeeper hk(ignore_patterns, dirs, expected_files);
    hk.tidy_up();
}

std::shared_ptr<dogen::formatters::artefact_writer_interface>
workflow::obtain_file_writer() const {
    const auto fw(options_.force_write());

    using dogen::formatters::filesystem_writer;
    return std::make_shared<filesystem_writer>(fw);
}

void workflow::write_files(
    std::shared_ptr<dogen::formatters::artefact_writer_interface> writer,
    const std::list<formatters::artefact>& artefacts) const {

    if (artefacts.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    writer->write(artefacts);
}

void workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Starting.";

    try {
        /*
         * Generate all files.
         */
        const auto cdo(yarn::code_generator::generate(options_));
        if (cdo.artefacts().empty()) {
            BOOST_LOG_SEV(lg, warn) << "No artefacts generated.";
            return;
        }

        /*
         * Write them to the filesystem.
         */
        const auto writer(obtain_file_writer());
        write_files(writer, cdo.artefacts());

        /*
         * Perform any housekeeping if need be.
         */
        if (housekeeping_required()) {
            const auto& md(cdo.managed_directories());
            perform_housekeeping(cdo.artefacts(), md);
        }
    } catch(const dogen::formatters::formatting_error& e) {
        BOOST_THROW_EXCEPTION(workflow_error(e.what()));
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Finished.";
}

} }
