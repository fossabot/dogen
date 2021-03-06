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
#ifndef DOGEN_MODELING_TYPES_META_MODEL_ELEMENT_HPP
#define DOGEN_MODELING_TYPES_META_MODEL_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen.annotations/types/annotation.hpp"
#include "dogen.modeling/types/meta_model/name.hpp"
#include "dogen.formatting/types/decoration_properties.hpp"
#include "dogen.modeling/types/meta_model/origin_types.hpp"
#include "dogen.modeling/types/meta_model/static_stereotypes.hpp"
#include "dogen.modeling/types/meta_model/artefact_properties.hpp"
#include "dogen.modeling/types/meta_model/element_visitor_fwd.hpp"
#include "dogen.modeling/types/meta_model/opaque_properties_fwd.hpp"
#include "dogen.modeling/serialization/meta_model/element_fwd_ser.hpp"
#include "dogen.modeling/types/meta_model/local_archetype_location_properties.hpp"

namespace dogen {
namespace modeling {
namespace meta_model {

/**
 * @brief Represents a generic modeling construct.
 *
 * An element is anything of interest in a problem domain which needs to be
 * expressed in code generation. It covers both types (objects, enumerations, etc),
 * meta-types (object templates) and non-types (modules and backend specific entities).
 */
class element {
public:
    element(const element&) = default;

public:
    element();

    virtual ~element() noexcept = 0;

public:
    element(element&& rhs);

public:
    element(
        const dogen::modeling::meta_model::name& name,
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::modeling::meta_model::origin_types origin_type,
        const boost::optional<dogen::modeling::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::list<dogen::modeling::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::modeling::meta_model::name& meta_name,
        const bool is_element_extension,
        const dogen::formatting::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& opaque_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::modeling::meta_model::element& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::modeling::meta_model::element& v, unsigned int version);

public:
    virtual void accept(const element_visitor& v) const = 0;
    virtual void accept(element_visitor& v) const = 0;
    virtual void accept(const element_visitor& v) = 0;
    virtual void accept(element_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::modeling::meta_model::name& name() const;
    dogen::modeling::meta_model::name& name();
    void name(const dogen::modeling::meta_model::name& v);
    void name(const dogen::modeling::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Annotation for this element.
     */
    /**@{*/
    const dogen::annotations::annotation& annotation() const;
    dogen::annotations::annotation& annotation();
    void annotation(const dogen::annotations::annotation& v);
    void annotation(const dogen::annotations::annotation&& v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::modeling::meta_model::origin_types origin_type() const;
    void origin_type(const dogen::modeling::meta_model::origin_types v);
    /**@}*/

    /**
     * @brief Name of the module in which we are contained.
     */
    /**@{*/
    const boost::optional<dogen::modeling::meta_model::name>& contained_by() const;
    boost::optional<dogen::modeling::meta_model::name>& contained_by();
    void contained_by(const boost::optional<dogen::modeling::meta_model::name>& v);
    void contained_by(const boost::optional<dogen::modeling::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief If true, the element is located in the global module.
     */
    /**@{*/
    bool in_global_module() const;
    void in_global_module(const bool v);
    /**@}*/

    /**
     * @brief Stereotypes that are part of the dogen UML profile, and so are well-known to the
     * model.
     */
    /**@{*/
    const std::list<dogen::modeling::meta_model::static_stereotypes>& static_stereotypes() const;
    std::list<dogen::modeling::meta_model::static_stereotypes>& static_stereotypes();
    void static_stereotypes(const std::list<dogen::modeling::meta_model::static_stereotypes>& v);
    void static_stereotypes(const std::list<dogen::modeling::meta_model::static_stereotypes>&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are not part of the yarn UML profile. These are user defined.
     */
    /**@{*/
    const std::list<std::string>& dynamic_stereotypes() const;
    std::list<std::string>& dynamic_stereotypes();
    void dynamic_stereotypes(const std::list<std::string>& v);
    void dynamic_stereotypes(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Name of the element in the meta-model that this instance conforms to.
     */
    /**@{*/
    const dogen::modeling::meta_model::name& meta_name() const;
    dogen::modeling::meta_model::name& meta_name();
    void meta_name(const dogen::modeling::meta_model::name& v);
    void meta_name(const dogen::modeling::meta_model::name&& v);
    /**@}*/

    /**
     * @brief If true, this element extends another element with the same id.
     */
    /**@{*/
    bool is_element_extension() const;
    void is_element_extension(const bool v);
    /**@}*/

    const dogen::formatting::decoration_properties& decoration_properties() const;
    dogen::formatting::decoration_properties& decoration_properties();
    void decoration_properties(const dogen::formatting::decoration_properties& v);
    void decoration_properties(const dogen::formatting::decoration_properties&& v);

    const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& artefact_properties() const;
    std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& artefact_properties();
    void artefact_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& v);
    void artefact_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>&& v);

    const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties() const;
    std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties();
    void archetype_location_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& v);
    void archetype_location_properties(const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>&& v);

    /**
     * @brief Any opaque properties associated with this element, by key.
     *
     * The key is expected to be namespaced by owning model name, to avoid
     * clashes.
     */
    /**@{*/
    const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& opaque_properties() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& opaque_properties();
    void opaque_properties(const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& v);
    void opaque_properties(const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >&& v);
    /**@}*/

protected:
    bool compare(const element& rhs) const;
public:
    virtual bool equals(const element& other) const = 0;

protected:
    void swap(element& other) noexcept;

private:
    dogen::modeling::meta_model::name name_;
    std::string documentation_;
    dogen::annotations::annotation annotation_;
    dogen::modeling::meta_model::origin_types origin_type_;
    boost::optional<dogen::modeling::meta_model::name> contained_by_;
    bool in_global_module_;
    std::list<dogen::modeling::meta_model::static_stereotypes> static_stereotypes_;
    std::list<std::string> dynamic_stereotypes_;
    dogen::modeling::meta_model::name meta_name_;
    bool is_element_extension_;
    dogen::formatting::decoration_properties decoration_properties_;
    std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties> artefact_properties_;
    std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties> archetype_location_properties_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> > opaque_properties_;
};

inline element::~element() noexcept { }

inline bool operator==(const element& lhs, const element& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
