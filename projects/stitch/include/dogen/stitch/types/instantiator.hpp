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
#ifndef DOGEN_STITCH_TYPES_INSTANTIATOR_HPP
#define DOGEN_STITCH_TYPES_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/formatters/types/repository.hpp"
#include "dogen/stitch/types/properties_factory.hpp"
#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {

/**
 * @brief Provides file name information on errors.
 */
typedef boost::error_info<struct tag_file_name, std::string> error_in_file;

class instantiator final {
public:
    instantiator(const annotations::type_repository& atrp,
        const annotations::annotation_groups_factory& agf,
        const dogen::formatters::repository& formatters_repository);

private:
    /**
     * @brief Computes the output path, given the template input path.
     */
    boost::filesystem::path
    compute_output_path(const boost::filesystem::path& input_path,
        const properties& props) const;

    /**
     * @brief Reads the supplied stitch text template into memory as a
     * raw string.
     */
    std::string read_text_template(const boost::filesystem::path& p) const;

    /**
     * @brief Instantiates the wale template, if configured.
     */
    void handle_wale_template(const std::unordered_map<std::string,
        std::string>& external_kvps, text_template& tt) const;

    /**
     * @brief Creates the text template.
     */
    text_template create_text_template(
        const boost::filesystem::path& input_path,
        const std::string& text_template_as_string,
        const std::unordered_map<std::string, std::string>& wale_kvps) const;

    /**
     * @brief Formats the supplied text template.
     */
    formatters::artefact format_text_template(const text_template& tt) const;

public:
    formatters::artefact
    instantiate(const boost::filesystem::path& input_path,
        const std::unordered_map<std::string, std::string>& wale_kvps =
        std::unordered_map<std::string, std::string>()) const;

private:
    const annotations::annotation_groups_factory& annotation_factory_;
    const properties_factory properties_factory_;
};

} }

#endif