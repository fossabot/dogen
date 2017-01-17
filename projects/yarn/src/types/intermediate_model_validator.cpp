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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/validation_error.hpp"
#include "dogen/yarn/types/intermediate_model_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.intermediate_model_validator"));

const std::string multiple_inheritance_not_supported(
    "Multiple inheritance is not supported on target models: ");

}

namespace dogen {
namespace yarn {

class validator {
public:
    validator(const name& model_name, const bool check_names,
        const bool is_proxy_reference);

private:
    void validate_name(const std::string& id, const bool in_global_namespace,
        const name& n) const;

public:
    void validate(const std::string& id, const yarn::concept& c) const;
    void validate(const std::string& id, const yarn::primitive& p) const;
    void validate(const std::string& id, const dogen::yarn::visitor& v) const;
    void validate(const std::string& id, const yarn::enumeration& e) const;
    void validate(const std::string& id, const yarn::object& o) const;
    void validate(const std::string& id, const yarn::exception& e) const;
    void validate(const std::string& id, const yarn::module& m) const;

private:
    const name model_name_;
    const bool check_names_;
    const bool is_proxy_reference_;
};

validator::validator(const name& model_name, const bool check_names,
    const bool is_proxy_reference) : model_name_(model_name),
                                     check_names_(check_names),
                                     is_proxy_reference_(is_proxy_reference) {}

void validator::
validate_name(const std::string& id, const bool in_global_namespace,
    const name& n) const {
    /*
     * Types in global namespace are known to have a mismatch between
     * their name and model name, so we need to ignore those.
     */
    if (!check_names_ || in_global_namespace)
        return;

    const auto nl(n.location());
    const auto ml(model_name_.location());
    if (nl.external_modules() != ml.external_modules() &&
        nl.model_modules() != ml.model_modules()) {
        std::ostringstream s;
        s << "Type does not belong to this model. Model name: '"
          << model_name_.id() << "'. Type name: " << n.id();
        BOOST_LOG_SEV(lg, warn) << s.str();
        BOOST_THROW_EXCEPTION(validation_error(s.str()));
    }

    if (id != n.id()) {
        std::ostringstream s;
        s << "Inconsistency between key and value ids: "
          << " key: " << id << " value: " << n.id();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(validation_error(s.str()));
    }
}

void validator::validate(const std::string& id, const yarn::concept& c) const {
    validate_name(id, c.in_global_module(), c.name());
}

void validator::
validate(const std::string& id, const yarn::primitive& p) const {
    validate_name(id, p.in_global_module(), p.name());
}

void validator::
validate(const std::string& id, const dogen::yarn::visitor& v) const {
    validate_name(id, v.in_global_module(), v.name());
}

void validator::
validate(const std::string& id, const yarn::enumeration& e) const {
    validate_name(id, e.in_global_module(), e.name());
}

void validator::validate(const std::string& id, const yarn::object& o) const {
    validate_name(id, o.in_global_module(), o.name());

    /*
     * Only proxy reference models can have multiple inheritance.
     */
    if (o.parents().size() > 1 && !is_proxy_reference_) {
        const auto id(o.name().id());
        BOOST_LOG_SEV(lg, error) << multiple_inheritance_not_supported << id;
        BOOST_THROW_EXCEPTION(validation_error(
                multiple_inheritance_not_supported + id));
    }
}

void validator::
validate(const std::string& id, const yarn::exception& e) const {
    validate_name(id, e.in_global_module(), e.name());
}

void validator::validate(const std::string& id, const yarn::module& m) const {
    validate_name(id, m.in_global_module(), m.name());
}

void intermediate_model_validator::
validate(const intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: " << im.name().id();

    const bool ipr(im.origin_type() == origin_types::proxy_reference);
    const bool check_names(im.language() != languages::upsilon);
    validator v(im.name(), check_names, ipr/*is_proxy_reference*/);

    for (const auto& pair : im.modules())
        v.validate(pair.first, pair.second);

    for (const auto& pair : im.concepts())
        v.validate(pair.first, pair.second);

    for (const auto& pair : im.primitives())
        v.validate(pair.first, pair.second);

    for (const auto& pair : im.enumerations())
        v.validate(pair.first, pair.second);

    for (const auto& pair : im.objects())
        v.validate(pair.first, pair.second);

    for (const auto& pair : im.exceptions())
        v.validate(pair.first, pair.second);

    for (const auto& pair : im.visitors())
        v.validate(pair.first, pair.second);

    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

} }
