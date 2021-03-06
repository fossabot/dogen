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
#ifndef DOGEN_GENERATION_CPP_IO_ALL_IO_HPP
#define DOGEN_GENERATION_CPP_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.generation.cpp/io/fabric/registrar_io.hpp"
#include "dogen.generation.cpp/io/fabric/cmakelists_io.hpp"
#include "dogen.generation.cpp/io/fabric/odb_target_io.hpp"
#include "dogen.generation.cpp/io/fabric/odb_targets_io.hpp"
#include "dogen.generation.cpp/io/formattables/model_io.hpp"
#include "dogen.generation.cpp/io/fabric/master_header_io.hpp"
#include "dogen.generation.cpp/io/formatters/repository_io.hpp"
#include "dogen.generation.cpp/io/fabric/msbuild_targets_io.hpp"
#include "dogen.generation.cpp/io/formattables/formattable_io.hpp"
#include "dogen.generation.cpp/io/fabric/common_odb_options_io.hpp"
#include "dogen.generation.cpp/io/fabric/object_odb_options_io.hpp"
#include "dogen.generation.cpp/io/formattables/cpp_standards_io.hpp"
#include "dogen.generation.cpp/io/fabric/forward_declarations_io.hpp"
#include "dogen.generation.cpp/io/formattables/odb_properties_io.hpp"
#include "dogen.generation.cpp/io/fabric/visual_studio_project_io.hpp"
#include "dogen.generation.cpp/io/formattables/directive_group_io.hpp"
#include "dogen.generation.cpp/io/fabric/visual_studio_solution_io.hpp"
#include "dogen.generation.cpp/io/formattables/facet_properties_io.hpp"
#include "dogen.generation.cpp/io/formattables/aspect_properties_io.hpp"
#include "dogen.generation.cpp/io/formattables/helper_descriptor_io.hpp"
#include "dogen.generation.cpp/io/formattables/helper_properties_io.hpp"
#include "dogen.generation.cpp/io/formattables/element_properties_io.hpp"
#include "dogen.generation.cpp/io/formattables/artefact_properties_io.hpp"
#include "dogen.generation.cpp/io/formattables/helper_configuration_io.hpp"
#include "dogen.generation.cpp/io/formattables/streaming_properties_io.hpp"
#include "dogen.generation.cpp/io/formattables/test_data_properties_io.hpp"
#include "dogen.generation.cpp/io/fabric/visual_studio_configuration_io.hpp"
#include "dogen.generation.cpp/io/formattables/locator_configuration_io.hpp"
#include "dogen.generation.cpp/io/formatters/inclusion_support_types_io.hpp"
#include "dogen.generation.cpp/io/formattables/directive_group_repository_io.hpp"
#include "dogen.generation.cpp/io/formattables/locator_facet_configuration_io.hpp"
#include "dogen.generation.cpp/io/formattables/locator_archetype_configuration_io.hpp"

#endif
