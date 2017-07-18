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
#ifndef DOGEN_YARN_TYPES_META_MODEL_ELEMENT_HPP
#define DOGEN_YARN_TYPES_META_MODEL_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/yarn/types/meta_model/origin_types.hpp"
#include "dogen/yarn/types/meta_model/element_properties.hpp"
#include "dogen/yarn/types/meta_model/element_visitor_fwd.hpp"
#include "dogen/yarn/serialization/meta_model/element_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Represents a generic modeling construct.
 *
 * An element is anything of interest in a problem domain which needs to be
 * expressed in code generation. It covers both types (objects, enumerations, etc),
 * meta-types (concepts) and non-types (modules and backend specific entities).
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
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::meta_model::name& name,
        const dogen::yarn::meta_model::origin_types origin_type,
        const boost::optional<dogen::yarn::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const dogen::yarn::meta_model::element_properties& element_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::element& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::element& v, unsigned int version);

public:
    virtual void accept(const element_visitor& v) const = 0;
    virtual void accept(element_visitor& v) const = 0;
    virtual void accept(const element_visitor& v) = 0;
    virtual void accept(element_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
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
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::yarn::meta_model::name& name() const;
    dogen::yarn::meta_model::name& name();
    void name(const dogen::yarn::meta_model::name& v);
    void name(const dogen::yarn::meta_model::name&& v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::yarn::meta_model::origin_types origin_type() const;
    void origin_type(const dogen::yarn::meta_model::origin_types v);
    /**@}*/

    /**
     * @brief Name of the module in which we are contained.
     */
    /**@{*/
    const boost::optional<dogen::yarn::meta_model::name>& contained_by() const;
    boost::optional<dogen::yarn::meta_model::name>& contained_by();
    void contained_by(const boost::optional<dogen::yarn::meta_model::name>& v);
    void contained_by(const boost::optional<dogen::yarn::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief If true, the element is located in the global module.
     */
    /**@{*/
    bool in_global_module() const;
    void in_global_module(const bool v);
    /**@}*/

    const std::vector<std::string>& stereotypes() const;
    std::vector<std::string>& stereotypes();
    void stereotypes(const std::vector<std::string>& v);
    void stereotypes(const std::vector<std::string>&& v);

    /**
     * @brief If true, this element extends another element with the same id.
     */
    /**@{*/
    bool is_element_extension() const;
    void is_element_extension(const bool v);
    /**@}*/

    const dogen::yarn::meta_model::element_properties& element_properties() const;
    dogen::yarn::meta_model::element_properties& element_properties();
    void element_properties(const dogen::yarn::meta_model::element_properties& v);
    void element_properties(const dogen::yarn::meta_model::element_properties&& v);

protected:
    bool compare(const element& rhs) const;
public:
    virtual bool equals(const element& other) const = 0;

protected:
    void swap(element& other) noexcept;

private:
    std::string documentation_;
    dogen::annotations::annotation annotation_;
    dogen::yarn::meta_model::name name_;
    dogen::yarn::meta_model::origin_types origin_type_;
    boost::optional<dogen::yarn::meta_model::name> contained_by_;
    bool in_global_module_;
    std::vector<std::string> stereotypes_;
    bool is_element_extension_;
    dogen::yarn::meta_model::element_properties element_properties_;
};

inline element::~element() noexcept { }

inline bool operator==(const element& lhs, const element& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif