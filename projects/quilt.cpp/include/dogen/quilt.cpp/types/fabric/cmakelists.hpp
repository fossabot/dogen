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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_CMAKELISTS_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_CMAKELISTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_targets.hpp"
#include "dogen/quilt.cpp/serialization/fabric/cmakelists_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class cmakelists final : public dogen::yarn::meta_model::element {
public:
    cmakelists() = default;
    cmakelists(const cmakelists&) = default;
    cmakelists(cmakelists&&) = default;

    virtual ~cmakelists() noexcept { }

public:
    cmakelists(
        const dogen::yarn::meta_model::name& name,
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::meta_model::origin_types origin_type,
        const boost::optional<dogen::yarn::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::list<dogen::yarn::meta_model::well_known_stereotypes>& well_known_stereotypes,
        const std::list<std::string>& unknown_stereotypes,
        const dogen::yarn::meta_model::name& meta_name,
        const bool is_element_extension,
        const dogen::formatters::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::string& include_directory_path,
        const std::string& source_directory_name,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension,
        const dogen::quilt::cpp::fabric::odb_targets& odb_targets);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::cmakelists& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::cmakelists& v, unsigned int version);

public:
    using dogen::yarn::meta_model::element::accept;

    virtual void accept(const dogen::yarn::meta_model::element_visitor& v) const override;
    virtual void accept(dogen::yarn::meta_model::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::meta_model::element_visitor& v) override;
    virtual void accept(dogen::yarn::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& include_directory_path() const;
    std::string& include_directory_path();
    void include_directory_path(const std::string& v);
    void include_directory_path(const std::string&& v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);

    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);

    const dogen::quilt::cpp::fabric::odb_targets& odb_targets() const;
    dogen::quilt::cpp::fabric::odb_targets& odb_targets();
    void odb_targets(const dogen::quilt::cpp::fabric::odb_targets& v);
    void odb_targets(const dogen::quilt::cpp::fabric::odb_targets&& v);

public:
    bool operator==(const cmakelists& rhs) const;
    bool operator!=(const cmakelists& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::meta_model::element& other) const override;

public:
    void swap(cmakelists& other) noexcept;
    cmakelists& operator=(cmakelists other);

private:
    std::string include_directory_path_;
    std::string source_directory_name_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
    dogen::quilt::cpp::fabric::odb_targets odb_targets_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::cmakelists& lhs,
    dogen::quilt::cpp::fabric::cmakelists& rhs) {
    lhs.swap(rhs);
}

}

#endif
