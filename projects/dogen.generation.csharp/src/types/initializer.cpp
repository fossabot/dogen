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
#include "dogen.modeling/types/transforms/model_to_text_model_chain.hpp"
#include "dogen.generation.csharp/types/formatters/workflow.hpp"
#include "dogen.generation.csharp/types/formatters/initializer.hpp"
#include "dogen.generation.csharp/types/fabric/initializer.hpp"
#include "dogen.generation.csharp/types/model_to_text_model_transform.hpp"
#include "dogen.generation.csharp/types/initializer.hpp"

namespace dogen {
namespace generation {
namespace csharp {

void initializer::initialize() {
    formatters::initializer::initialize(formatters::workflow::registrar());
    fabric::initializer::initialize();
    modeling::transforms::register_transform<model_to_text_model_transform>();
}

} } }
