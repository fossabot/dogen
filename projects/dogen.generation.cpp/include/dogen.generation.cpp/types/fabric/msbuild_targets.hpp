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
#ifndef DOGEN_GENERATION_CPP_TYPES_FABRIC_MSBUILD_TARGETS_HPP
#define DOGEN_GENERATION_CPP_TYPES_FABRIC_MSBUILD_TARGETS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.modeling/types/meta_model/element.hpp"
#include "dogen.generation.cpp/types/fabric/odb_targets.hpp"
#include "dogen.generation.cpp/serialization/fabric/msbuild_targets_fwd_ser.hpp"

namespace dogen {
namespace generation {
namespace cpp {
namespace fabric {

class msbuild_targets final : public dogen::modeling::meta_model::element {
public:
    msbuild_targets() = default;
    msbuild_targets(const msbuild_targets&) = default;
    msbuild_targets(msbuild_targets&&) = default;

    virtual ~msbuild_targets() noexcept { }

public:
    msbuild_targets(
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
        const std::unordered_map<std::string, boost::shared_ptr<dogen::modeling::meta_model::opaque_properties> >& opaque_properties,
        const dogen::generation::cpp::fabric::odb_targets& odb_targets);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::generation::cpp::fabric::msbuild_targets& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::generation::cpp::fabric::msbuild_targets& v, unsigned int version);

public:
    using dogen::modeling::meta_model::element::accept;

    virtual void accept(const dogen::modeling::meta_model::element_visitor& v) const override;
    virtual void accept(dogen::modeling::meta_model::element_visitor& v) const override;
    virtual void accept(const dogen::modeling::meta_model::element_visitor& v) override;
    virtual void accept(dogen::modeling::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const dogen::generation::cpp::fabric::odb_targets& odb_targets() const;
    dogen::generation::cpp::fabric::odb_targets& odb_targets();
    void odb_targets(const dogen::generation::cpp::fabric::odb_targets& v);
    void odb_targets(const dogen::generation::cpp::fabric::odb_targets&& v);

public:
    bool operator==(const msbuild_targets& rhs) const;
    bool operator!=(const msbuild_targets& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::modeling::meta_model::element& other) const override;

public:
    void swap(msbuild_targets& other) noexcept;
    msbuild_targets& operator=(msbuild_targets other);

private:
    dogen::generation::cpp::fabric::odb_targets odb_targets_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::generation::cpp::fabric::msbuild_targets& lhs,
    dogen::generation::cpp::fabric::msbuild_targets& rhs) {
    lhs.swap(rhs);
}

}

#endif
