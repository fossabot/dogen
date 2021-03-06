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
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen.modeling/serialization/meta_model/name_ser.hpp"
#include "dogen.modeling/serialization/meta_model/object_ser.hpp"
#include "dogen.modeling/serialization/meta_model/element_ser.hpp"
#include "dogen.modeling/serialization/meta_model/attribute_ser.hpp"
#include "dogen.modeling/serialization/meta_model/type_parameters_ser.hpp"
#include "dogen.modeling/serialization/meta_model/orm_object_properties_ser.hpp"

BOOST_CLASS_TRACKING(
    dogen::modeling::meta_model::object,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::modeling::meta_model::object& v,
    const unsigned int /*version*/) {
    ar << make_nvp("element", base_object<dogen::modeling::meta_model::element>(v));

    ar << make_nvp("all_attributes", v.all_attributes_);
    ar << make_nvp("local_attributes", v.local_attributes_);
    ar << make_nvp("inherited_attributes", v.inherited_attributes_);
    ar << make_nvp("is_immutable", v.is_immutable_);
    ar << make_nvp("is_fluent", v.is_fluent_);
    ar << make_nvp("base_visitor", v.base_visitor_);
    ar << make_nvp("derived_visitor", v.derived_visitor_);
    ar << make_nvp("is_visitation_root", v.is_visitation_root_);
    ar << make_nvp("is_visitation_leaf", v.is_visitation_leaf_);
    ar << make_nvp("transparent_associations", v.transparent_associations_);
    ar << make_nvp("opaque_associations", v.opaque_associations_);
    ar << make_nvp("is_parent", v.is_parent_);
    ar << make_nvp("is_child", v.is_child_);
    ar << make_nvp("is_leaf", v.is_leaf_);
    ar << make_nvp("is_final", v.is_final_);
    ar << make_nvp("is_abstract", v.is_abstract_);
    ar << make_nvp("in_inheritance_relationship", v.in_inheritance_relationship_);
    ar << make_nvp("root_parents", v.root_parents_);
    ar << make_nvp("parents", v.parents_);
    ar << make_nvp("leaves", v.leaves_);
    ar << make_nvp("type_parameters", v.type_parameters_);
    ar << make_nvp("is_associative_container", v.is_associative_container_);
    ar << make_nvp("object_templates", v.object_templates_);
    ar << make_nvp("associative_container_keys", v.associative_container_keys_);
    ar << make_nvp("provides_opaqueness", v.provides_opaqueness_);
    ar << make_nvp("can_be_primitive_underlier", v.can_be_primitive_underlier_);
    ar << make_nvp("orm_properties", v.orm_properties_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::modeling::meta_model::object& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("element", base_object<dogen::modeling::meta_model::element>(v));

    ar >> make_nvp("all_attributes", v.all_attributes_);
    ar >> make_nvp("local_attributes", v.local_attributes_);
    ar >> make_nvp("inherited_attributes", v.inherited_attributes_);
    ar >> make_nvp("is_immutable", v.is_immutable_);
    ar >> make_nvp("is_fluent", v.is_fluent_);
    ar >> make_nvp("base_visitor", v.base_visitor_);
    ar >> make_nvp("derived_visitor", v.derived_visitor_);
    ar >> make_nvp("is_visitation_root", v.is_visitation_root_);
    ar >> make_nvp("is_visitation_leaf", v.is_visitation_leaf_);
    ar >> make_nvp("transparent_associations", v.transparent_associations_);
    ar >> make_nvp("opaque_associations", v.opaque_associations_);
    ar >> make_nvp("is_parent", v.is_parent_);
    ar >> make_nvp("is_child", v.is_child_);
    ar >> make_nvp("is_leaf", v.is_leaf_);
    ar >> make_nvp("is_final", v.is_final_);
    ar >> make_nvp("is_abstract", v.is_abstract_);
    ar >> make_nvp("in_inheritance_relationship", v.in_inheritance_relationship_);
    ar >> make_nvp("root_parents", v.root_parents_);
    ar >> make_nvp("parents", v.parents_);
    ar >> make_nvp("leaves", v.leaves_);
    ar >> make_nvp("type_parameters", v.type_parameters_);
    ar >> make_nvp("is_associative_container", v.is_associative_container_);
    ar >> make_nvp("object_templates", v.object_templates_);
    ar >> make_nvp("associative_container_keys", v.associative_container_keys_);
    ar >> make_nvp("provides_opaqueness", v.provides_opaqueness_);
    ar >> make_nvp("can_be_primitive_underlier", v.can_be_primitive_underlier_);
    ar >> make_nvp("orm_properties", v.orm_properties_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::modeling::meta_model::object& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::modeling::meta_model::object& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::modeling::meta_model::object& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::modeling::meta_model::object& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::modeling::meta_model::object& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::modeling::meta_model::object& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::modeling::meta_model::object& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::modeling::meta_model::object& v, unsigned int version);

} }
