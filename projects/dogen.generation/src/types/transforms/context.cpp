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
#include "dogen.generation/types/transforms/context.hpp"

namespace dogen {
namespace generation {
namespace transforms {

context::context(
    const std::vector<boost::filesystem::path>& data_directories,
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const dogen::formatting::repository& frp,
    const probing::prober& prober,
    const std::unordered_map<std::string,
    meta_model::intra_backend_segment_properties>&
    intra_backend_segment_properties,
    const boost::shared_ptr<helpers::artefact_writer_interface> writer) :
    archetype_location_repository_(alrp), type_repository_(atrp),
    annotation_factory_(data_directories, archetype_location_repository_,
        type_repository_, false/*options.compatibility_mode()*/),
    formatting_repository_(frp), prober_(prober),
    intra_backend_segment_properties_(intra_backend_segment_properties),
    writer_(writer) {}

context::~context() {
    prober_.end_probing();
}

const annotations::archetype_location_repository&
context::archetype_location_repository() const {
    return archetype_location_repository_;
}

const annotations::type_repository& context::type_repository() const {
    return type_repository_;
}

const annotations::annotation_factory& context::annotation_factory() const {
    return annotation_factory_;
}

const dogen::formatting::repository& context::formatting_repository() const {
    return formatting_repository_;
}

const probing::prober& context::prober() const {
    return prober_;
}

const std::unordered_map<std::string,
                         meta_model::intra_backend_segment_properties>&
context::intra_backend_segment_properties() const {
    return intra_backend_segment_properties_;
}

const helpers::artefact_writer_interface& context::artefact_writer() const {
    return *writer_;
}

} } }
