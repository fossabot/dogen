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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.modeling/types/meta_model/element_fwd.hpp"
#include "dogen.generation.cpp/types/formattables/element_properties.hpp"
#include "dogen.generation.cpp/serialization/formattables/formattable_fwd_ser.hpp"

namespace dogen {
namespace generation {
namespace cpp {
namespace formattables {

class formattable final {
public:
    formattable() = default;
    formattable(const formattable&) = default;
    formattable(formattable&&) = default;
    ~formattable() = default;

public:
    formattable(
        const boost::shared_ptr<dogen::modeling::meta_model::element>& master_segment,
        const std::list<boost::shared_ptr<dogen::modeling::meta_model::element> >& all_segments,
        const dogen::generation::cpp::formattables::element_properties& element_properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::generation::cpp::formattables::formattable& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::generation::cpp::formattables::formattable& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::modeling::meta_model::element>& master_segment() const;
    boost::shared_ptr<dogen::modeling::meta_model::element>& master_segment();
    void master_segment(const boost::shared_ptr<dogen::modeling::meta_model::element>& v);
    void master_segment(const boost::shared_ptr<dogen::modeling::meta_model::element>&& v);

    const std::list<boost::shared_ptr<dogen::modeling::meta_model::element> >& all_segments() const;
    std::list<boost::shared_ptr<dogen::modeling::meta_model::element> >& all_segments();
    void all_segments(const std::list<boost::shared_ptr<dogen::modeling::meta_model::element> >& v);
    void all_segments(const std::list<boost::shared_ptr<dogen::modeling::meta_model::element> >&& v);

    const dogen::generation::cpp::formattables::element_properties& element_properties() const;
    dogen::generation::cpp::formattables::element_properties& element_properties();
    void element_properties(const dogen::generation::cpp::formattables::element_properties& v);
    void element_properties(const dogen::generation::cpp::formattables::element_properties&& v);

public:
    bool operator==(const formattable& rhs) const;
    bool operator!=(const formattable& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formattable& other) noexcept;
    formattable& operator=(formattable other);

private:
    boost::shared_ptr<dogen::modeling::meta_model::element> master_segment_;
    std::list<boost::shared_ptr<dogen::modeling::meta_model::element> > all_segments_;
    dogen::generation::cpp::formattables::element_properties element_properties_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::generation::cpp::formattables::formattable& lhs,
    dogen::generation::cpp::formattables::formattable& rhs) {
    lhs.swap(rhs);
}

}

#endif
