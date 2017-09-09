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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_EXOMODEL_TO_EXOMODEL_CHAIN_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_EXOMODEL_TO_EXOMODEL_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <utility>
#include <boost/tuple/tuple.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/types/transforms/exomodel_transform_interface.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class exomodel_to_exomodel_chain final {
public:
    static boost::tuple<exomodel_transform_interface&,
                        exomodel_transform_interface&>
    obtain_transforms(const boost::filesystem::path& src_path,
        const boost::filesystem::path& dst_path);

public:
    static void transform(const boost::filesystem::path& src_path,
        const boost::filesystem::path& dst_path);
};

} } }

#endif