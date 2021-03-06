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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.options/serialization/registrar_ser.hpp"
#include "dogen.probing/serialization/registrar_ser.hpp"
#include "dogen.modeling/serialization/registrar_ser.hpp"
#include "dogen.formatting/serialization/registrar_ser.hpp"
#include "dogen.annotations/serialization/registrar_ser.hpp"
#include "dogen.generation.cpp/serialization/registrar_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/registrar_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/cmakelists_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/master_header_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/msbuild_targets_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/common_odb_options_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/object_odb_options_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/forward_declarations_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/visual_studio_project_ser.hpp"
#include "dogen.generation.cpp/serialization/fabric/visual_studio_solution_ser.hpp"

namespace dogen {
namespace generation {
namespace cpp {

template<typename Archive>
void register_types(Archive& ar) {
    dogen::annotations::register_types(ar);
    dogen::probing::register_types(ar);
    dogen::formatting::register_types(ar);
    dogen::options::register_types(ar);
    dogen::modeling::register_types(ar);

    ar.template register_type<dogen::generation::cpp::fabric::cmakelists>();
    ar.template register_type<dogen::generation::cpp::fabric::common_odb_options>();
    ar.template register_type<dogen::generation::cpp::fabric::forward_declarations>();
    ar.template register_type<dogen::generation::cpp::fabric::master_header>();
    ar.template register_type<dogen::generation::cpp::fabric::msbuild_targets>();
    ar.template register_type<dogen::generation::cpp::fabric::object_odb_options>();
    ar.template register_type<dogen::generation::cpp::fabric::registrar>();
    ar.template register_type<dogen::generation::cpp::fabric::visual_studio_project>();
    ar.template register_type<dogen::generation::cpp::fabric::visual_studio_solution>();
}

template void register_types(boost::archive::polymorphic_oarchive& ar);
template void register_types(boost::archive::polymorphic_iarchive& ar);

template void register_types(boost::archive::text_oarchive& ar);
template void register_types(boost::archive::text_iarchive& ar);

template void register_types(boost::archive::binary_oarchive& ar);
template void register_types(boost::archive::binary_iarchive& ar);

template void register_types(boost::archive::xml_oarchive& ar);
template void register_types(boost::archive::xml_iarchive& ar);

} } }
