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
#ifndef DOGEN_YARN_TYPES_META_MODEL_EXOGENOUS_MODEL_HPP
#define DOGEN_YARN_TYPES_META_MODEL_EXOGENOUS_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <utility>
#include <algorithm>
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/concept.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"
#include "dogen/annotations/types/scribble_group.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"
#include "dogen/yarn/serialization/meta_model/exogenous_model_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

class exogenous_model final {
public:
    exogenous_model() = default;
    exogenous_model(const exogenous_model&) = default;
    exogenous_model(exogenous_model&&) = default;
    ~exogenous_model() = default;

public:
    exogenous_model(
        const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module> >& modules,
        const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept> >& concepts,
        const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin> >& builtins,
        const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration> >& enumerations,
        const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive> >& primitives,
        const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object> >& objects,
        const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception> >& exceptions);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::exogenous_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::exogenous_model& v, unsigned int version);

public:
    const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module> >& modules() const;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module> >& modules();
    void modules(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module> >& v);
    void modules(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module> >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept> >& concepts() const;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept> >& concepts();
    void concepts(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept> >& v);
    void concepts(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept> >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin> >& builtins() const;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin> >& builtins();
    void builtins(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin> >& v);
    void builtins(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin> >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration> >& enumerations() const;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration> >& enumerations();
    void enumerations(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration> >& v);
    void enumerations(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration> >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive> >& primitives() const;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive> >& primitives();
    void primitives(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive> >& v);
    void primitives(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive> >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object> >& objects() const;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object> >& objects();
    void objects(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object> >& v);
    void objects(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object> >&& v);

    const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception> >& exceptions() const;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception> >& exceptions();
    void exceptions(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception> >& v);
    void exceptions(const std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception> >&& v);

public:
    bool operator==(const exogenous_model& rhs) const;
    bool operator!=(const exogenous_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(exogenous_model& other) noexcept;
    exogenous_model& operator=(exogenous_model other);

private:
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::module> > modules_;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::concept> > concepts_;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::builtin> > builtins_;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::enumeration> > enumerations_;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::primitive> > primitives_;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::object> > objects_;
    std::list<std::pair<dogen::annotations::scribble_group, dogen::yarn::meta_model::exception> > exceptions_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::exogenous_model& lhs,
    dogen::yarn::meta_model::exogenous_model& rhs) {
    lhs.swap(rhs);
}

}

#endif