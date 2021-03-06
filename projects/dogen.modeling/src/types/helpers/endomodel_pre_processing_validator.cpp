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
#include <boost/throw_exception.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/builtin.hpp"
#include "dogen.modeling/types/meta_model/visitor.hpp"
#include "dogen.modeling/types/meta_model/exception.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"
#include "dogen.modeling/types/helpers/validation_error.hpp"
#include "dogen.modeling/types/helpers/endomodel_pre_processing_validator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.endomodel_pre_processing_validator"));

const std::string multiple_inheritance_not_supported(
    "Multiple inheritance is not supported on target models: ");
const std::string generate_mapping_off(
    "Object has generate mapping set to false, but attributes have ORM "
    "mapping properties set: ");
const std::string multiple_primary_keys(
    "Object has more than one attribute marked as primary key: ");
const std::string nullable_primary_key(
    "Primary key cannot be nullable. Object: ");

}

namespace dogen {
namespace modeling {
namespace helpers {

class validator {
public:
    validator(const meta_model::name& model_name,
        const bool is_proxy_reference);

private:
    void validate_name(const std::string& id, const bool in_global_module,
        const meta_model::name& n) const;

public:
    void validate(const std::string& id,
        const meta_model::object_template& ot) const;
    void validate(const std::string& id, const meta_model::builtin& b) const;
    void validate(const std::string& id, const meta_model::visitor& v) const;
    void validate(const std::string& id,
        const meta_model::enumeration& e) const;
    void validate(const std::string& id, const meta_model::object& o) const;
    void validate(const std::string& id, const meta_model::exception& e) const;
    void validate(const std::string& id, const meta_model::module& m) const;

private:
    const meta_model::name model_name_;
    const bool is_proxy_reference_;
};

validator::
validator(const meta_model::name& model_name, const bool is_proxy_reference)
    : model_name_(model_name), is_proxy_reference_(is_proxy_reference) {}

void validator::
validate_name(const std::string& id, const bool in_global_module,
    const meta_model::name& n) const {
    /*
     * Types in global module are known to have a mismatch between
     * their name and model name, so we need to ignore those.
     *
     * FIXME: however we should check that types in global namespace
     * do not have anything filled in location.
     */
    if (in_global_module)
        return;

    const auto nl(n.location());
    const auto ml(model_name_.location());
    if (nl.external_modules() != ml.external_modules() ||
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

void validator::
validate(const std::string& id, const meta_model::object_template& ot) const {
    validate_name(id, ot.in_global_module(), ot.name());
}

void validator::
validate(const std::string& id, const meta_model::builtin& b) const {
    validate_name(id, b.in_global_module(), b.name());
}

void validator::
validate(const std::string& id, const meta_model::visitor& v) const {
    validate_name(id, v.in_global_module(), v.name());
}

void validator::
validate(const std::string& id, const meta_model::enumeration& e) const {
    validate_name(id, e.in_global_module(), e.name());
}

void validator::
validate(const std::string& id, const meta_model::object& o) const {
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

    bool has_primary_key(false);
    const auto& cfg(o.orm_properties());
    const bool generate_mapping(cfg && cfg->generate_mapping());
    for (const auto& attr : o.local_attributes()) {
        if (!attr.orm_properties())
            continue;

        /*
         * If generate mapping is off, we are not expecting any ORM
         * properties to be set; if they are this is likely an error
         * and the user really meant to switch generate mapping on.
         */
        if (!generate_mapping) {
            BOOST_LOG_SEV(lg, error) << generate_mapping_off << id;
            BOOST_THROW_EXCEPTION(validation_error(generate_mapping_off + id));
        }

        const auto& cfg(*attr.orm_properties());
        if (!cfg.is_primary_key())
            continue;

        /*
         * Primary keys cannot be nullable.
         */
        if (cfg.is_nullable() && *cfg.is_nullable()) {
            BOOST_LOG_SEV(lg, error) << nullable_primary_key << id;
            BOOST_THROW_EXCEPTION(validation_error(nullable_primary_key + id));
        }

        /*
         * An object can have at most one attribute marked as a primary
         * key. Composite keys must be generated by creating external
         * classes with all of the properties.
         */
        if (has_primary_key) {
            BOOST_LOG_SEV(lg, error) << multiple_primary_keys << id;
            BOOST_THROW_EXCEPTION(validation_error(multiple_primary_keys + id));
        }
        has_primary_key = true;
    }
}

void validator::
validate(const std::string& id, const meta_model::exception& e) const {
    validate_name(id, e.in_global_module(), e.name());
}

void validator::
validate(const std::string& id, const meta_model::module& m) const {
    validate_name(id, m.in_global_module(), m.name());
}

void endomodel_pre_processing_validator::
validate(const meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: " << im.name().id();

    using meta_model::origin_types;
    const bool ipr(im.origin_type() == origin_types::proxy_reference);

    using meta_model::languages;
    validator v(im.name(), ipr);

    for (const auto& pair : im.modules())
        v.validate(pair.first, *pair.second);

    for (const auto& pair : im.object_templates())
        v.validate(pair.first, *pair.second);

    for (const auto& pair : im.builtins())
        v.validate(pair.first, *pair.second);

    for (const auto& pair : im.enumerations())
        v.validate(pair.first, *pair.second);

    for (const auto& pair : im.objects())
        v.validate(pair.first, *pair.second);

    for (const auto& pair : im.exceptions())
        v.validate(pair.first, *pair.second);

    for (const auto& pair : im.visitors())
        v.validate(pair.first, *pair.second);

    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

} } }
