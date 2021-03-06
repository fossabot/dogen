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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/string/splitter.hpp"
#include "dogen.utility/exception/invalid_enum_value.hpp"
#include "dogen.modeling/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.modeling/types/helpers/stereotypes_helper.hpp"

namespace {

const std::string transform_id("yarn.transforms.stereotypes_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stereotype_object("dogen::object");
const std::string stereotype_object_template("dogen::object_template");
const std::string stereotype_exception("dogen::exception");
const std::string stereotype_primitive("dogen::primitive");
const std::string stereotype_enumeration("dogen::enumeration");
const std::string stereotype_module("dogen::module");
const std::string stereotype_builtin("dogen::builtin");
const std::string stereotype_visitable("dogen::visitable");
const std::string stereotype_fluent("dogen::fluent");
const std::string stereotype_immutable("dogen::immutable");
const std::string stereotype_orm_object("dogen::orm::object");
const std::string stereotype_orm_value("dogen::orm::value");

const std::string unsupported_stereotype("Invalid or unsupported stereotype: ");

}

namespace dogen {
namespace modeling {
namespace helpers {

using meta_model::static_stereotypes;

static_stereotypes stereotypes_helper::from_string(const std::string& s) const {
    BOOST_LOG_SEV(lg, error) << "Converting stereotype: " << s;

    if (s == stereotype_object)
        return static_stereotypes::object;
    else if (s == stereotype_object_template)
        return static_stereotypes::object_template;
    else if (s == stereotype_exception)
        return static_stereotypes::exception;
    else if (s == stereotype_primitive)
        return static_stereotypes::primitive;
    else if (s == stereotype_enumeration)
        return static_stereotypes::enumeration;
    else if (s == stereotype_module)
        return static_stereotypes::module;
    else if (s == stereotype_builtin)
        return static_stereotypes::builtin;
    else if (s == stereotype_visitable)
        return static_stereotypes::visitable;
    else if (s == stereotype_fluent)
        return static_stereotypes::fluent;
    else if (s == stereotype_immutable)
        return static_stereotypes::immutable;
    else if (s == stereotype_orm_object)
        return static_stereotypes::orm_object;
    else if (s == stereotype_orm_value)
        return static_stereotypes::orm_value;

    BOOST_LOG_SEV(lg, error) << "Could not convert stereotype.";

    return static_stereotypes::invalid;
}

stereotypes_conversion_result
stereotypes_helper::from_csv_string(const std::string& s) const {
    if (s.empty()) {
        stereotypes_conversion_result r;
        return r;
    }

    using utility::string::splitter;
    const auto stereotypes(splitter::split_csv(s));
    return from_string(stereotypes);
}

stereotypes_conversion_result stereotypes_helper::
from_string(const std::list<std::string>& stereotypes) const {
    stereotypes_conversion_result r;
    if (stereotypes.empty())
        return r;

    for (const auto& stereotype : stereotypes) {
        const auto ss(from_string(stereotype));
        if (ss != static_stereotypes::invalid)
            r.static_stereotypes().push_back(ss);
        else
            r.dynamic_stereotypes().push_back(stereotype);
    }
    return r;
}

std::string stereotypes_helper::
to_string(const static_stereotypes ss) const {
    switch(ss) {
    case static_stereotypes::object: return stereotype_object;
    case static_stereotypes::object_template: return stereotype_object;
    case static_stereotypes::exception: return stereotype_exception;
    case static_stereotypes::primitive: return stereotype_primitive;
    case static_stereotypes::enumeration: return stereotype_enumeration;
    case static_stereotypes::module: return stereotype_module;
    case static_stereotypes::builtin: return stereotype_builtin;
    case static_stereotypes::visitable: return stereotype_visitable;
    case static_stereotypes::fluent: return stereotype_fluent;
    case static_stereotypes::immutable: return stereotype_immutable;
    case static_stereotypes::orm_object: return stereotype_orm_object;
    case static_stereotypes::orm_value: return stereotype_orm_value;
    default: {
        const std::string s(boost::lexical_cast<std::string>(ss));
        BOOST_LOG_SEV(lg, error) << unsupported_stereotype << s;
        using dogen::utility::exception::invalid_enum_value;
        BOOST_THROW_EXCEPTION(invalid_enum_value(unsupported_stereotype + s));
    } }
}

bool stereotypes_helper::
is_element_type(const static_stereotypes ss) const {
    return
        ss == static_stereotypes::object ||
        ss == static_stereotypes::object_template ||
        ss == static_stereotypes::exception ||
        ss == static_stereotypes::primitive ||
        ss == static_stereotypes::enumeration ||
        ss == static_stereotypes::module ||
        ss == static_stereotypes::builtin;
}

std::list<static_stereotypes> stereotypes_helper::extract_element_types(
    const std::list<static_stereotypes>& ss) const {

    std::list<static_stereotypes> r;
    for (const auto st : ss)
        if (is_element_type(st))
            r.push_back(st);

    return r;
}

std::list<static_stereotypes> stereotypes_helper::
extract_non_element_types(const std::list<static_stereotypes>& ss) const {
    std::list<static_stereotypes> r;
    for (const auto st : ss)
        if (!is_element_type(st))
            r.push_back(st);

    return r;
}

} } }
