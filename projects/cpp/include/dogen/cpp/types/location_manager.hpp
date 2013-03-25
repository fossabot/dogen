/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_LOCATION_MANAGER_HPP
#define DOGEN_CPP_LOCATION_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/cpp/types/location_request.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/aspect_types.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Manages the file names for all generated files and all the
 * pre-processor includes.
 */
class location_manager {
public:
    location_manager() = delete;
    location_manager(const location_manager&) = default;
    ~location_manager() = default;
    location_manager& operator=(const location_manager&) = delete;

public:
    location_manager(location_manager&& rhs)
    : model_name_(std::move(rhs.model_name_)),
      settings_(std::move(rhs.settings_)),
      source_directory_(std::move(rhs.source_directory_)),
      include_directory_(std::move(rhs.include_directory_)) { }

    location_manager(const std::string& model_name,
        const config::cpp_settings& settings);

private:
    std::string facet_directory(config::cpp_facet_types facet) const;
    std::string facet_postfix(config::cpp_facet_types facet) const;
    std::string aspect_postfix(aspect_types aspect) const;
    boost::filesystem::path file_type_directory(file_types file_type) const;
    std::string extension(file_types file_type) const;

public:
    typedef boost::filesystem::path path;

    /**
     * @brief Returns the path to the requested location taking into
     * account the external package path.
     *
     * Logical relative paths are used for include files; they need to
     * take into account existing namespaces the user may have already
     * defined.
     */
    path relative_logical_path(const location_request& request) const;

    /**
     * @brief Returns the path to the requested location, excluding
     * the external package path.
     *
     * When combined with the source or include directories, the
     * physical path matches the location on the hard drive for the
     * artefact in question.
     */
    path relative_physical_path(const location_request& request) const;

    /**
     * @brief Returns the absolute path for the request, taking into
     * account source and include directories, etc.
     */
    path absolute_path(const location_request& request) const;

    /**
     * @brief Returns an absolute path into the source directory for
     * the current model.
     *
     * @param name name of the item we're getting the path for.
     */
    path absolute_path_to_src(const std::string& name) const;

    /**
     * @brief Returns an absolute path into the include directory for
     * the current model.
     *
     * @param name name of the item we're getting the path for.
     */
    path absolute_path_to_include(const std::string& name) const;

    /**
     * @brief Returns an absolute path into the top level directory,
     * if split projects is not on.
     *
     * @param name name of the item we're getting the path for.
     */
    path absolute_path(const std::string& name) const;

    /**
     * @brief Returns the list of directories this location manager is
     * managing.
     */
    std::vector<boost::filesystem::path> managed_directories() const;

private:
    const std::string model_name_;
    const config::cpp_settings settings_;
    boost::filesystem::path source_directory_;
    boost::filesystem::path include_directory_;
};

} }

#endif
