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
#ifndef DOGEN_QUILT_CPP_IO_ALL_IO_HPP
#define DOGEN_QUILT_CPP_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/io/fabric/registrar_io.hpp"
#include "dogen/quilt.cpp/io/fabric/cmakelists_io.hpp"
#include "dogen/quilt.cpp/io/fabric/odb_options_io.hpp"
#include "dogen/quilt.cpp/io/fabric/master_header_io.hpp"
#include "dogen/quilt.cpp/io/formatters/file_types_io.hpp"
#include "dogen/quilt.cpp/io/annotations/odb_annotations_io.hpp"
#include "dogen/quilt.cpp/io/fabric/forward_declarations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/path_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/path_derivatives_io.hpp"
#include "dogen/quilt.cpp/io/annotations/aspect_annotations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/helper_annotations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/opaque_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/aspect_properties_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_descriptor_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_properties_io.hpp"
#include "dogen/quilt.cpp/io/annotations/element_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/element_properties_io.hpp"
#include "dogen/quilt.cpp/io/annotations/streaming_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_properties_io.hpp"
#include "dogen/quilt.cpp/io/formattables/enablement_repository_io.hpp"
#include "dogen/quilt.cpp/io/formatters/inclusion_support_types_io.hpp"
#include "dogen/quilt.cpp/io/formattables/inclusion_path_support_io.hpp"
#include "dogen/quilt.cpp/io/annotations/directory_names_annotations_io.hpp"
#include "dogen/quilt.cpp/io/formattables/path_derivatives_repository_io.hpp"
#include "dogen/quilt.cpp/io/annotations/aspect_annotations_repository_io.hpp"
#include "dogen/quilt.cpp/io/annotations/helper_annotations_repository_io.hpp"
#include "dogen/quilt.cpp/io/formattables/aspect_properties_repository_io.hpp"
#include "dogen/quilt.cpp/io/formattables/global_enablement_properties_io.hpp"
#include "dogen/quilt.cpp/io/formattables/helper_properties_repository_io.hpp"
#include "dogen/quilt.cpp/io/annotations/element_annotations_repository_io.hpp"
#include "dogen/quilt.cpp/io/formattables/element_properties_repository_io.hpp"
#include "dogen/quilt.cpp/io/annotations/inclusion_directive_annotations_io.hpp"
#include "dogen/quilt.cpp/io/annotations/streaming_annotations_repository_io.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_properties_repository_io.hpp"
#include "dogen/quilt.cpp/io/formattables/inclusion_directives_repository_io.hpp"
#include "dogen/quilt.cpp/io/formattables/inclusion_dependencies_repository_io.hpp"

#endif
