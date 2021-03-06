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
#include <memory>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <boost/throw_exception.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/io/unordered_set_io.hpp"
#include "dogen.modeling/types/meta_model/builtin.hpp"
#include "dogen.modeling/types/meta_model/primitive.hpp"
#include "dogen.modeling/types/meta_model/enumeration.hpp"
#include "dogen.modeling/io/meta_model/name_io.hpp"
#include "dogen.modeling/io/meta_model/languages_io.hpp"
#include "dogen.modeling/io/meta_model/name_tree_io.hpp"
#include "dogen.modeling/io/meta_model/attribute_io.hpp"
#include "dogen.modeling/io/meta_model/endomodel_io.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/helpers/name_factory.hpp"
#include "dogen.modeling/types/helpers/identifiable_and_qualified_builder.hpp"
#include "dogen.modeling/types/helpers/resolution_error.hpp"
#include "dogen.modeling/types/helpers/resolver.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.resolver"));

const std::string empty;
const std::string orphan_object("Object's parent could not be located: ");
const std::string orphan_object_template(
    "Instantiated object template could not be located: ");
const std::string undefined_type("Object has attribute with undefined type: ");
const std::string invalid_underlying_type("Invalid underlying type: ");

typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

}

namespace dogen {
namespace modeling {
namespace helpers {

bool resolver::
is_floating_point(const meta_model::endomodel& im,
    const meta_model::name& n) {
    auto i(im.builtins().find(n.id()));
    return i != im.builtins().end() && i->second->is_floating_point();
}

bool resolver::is_builtin(const meta_model::endomodel& im,
    const meta_model::name& n) {

    auto i(im.builtins().find(n.id()));
    if (i != im.builtins().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a built-in in model.";
        return true;
    }
    return false;
}

bool resolver::is_primitive(const meta_model::endomodel& im,
    const meta_model::name& n) {

    auto i(im.primitives().find(n.id()));
    if (i != im.primitives().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a primitive in model.";
        return true;
    }
    return false;
}

bool resolver::is_enumeration(const meta_model::endomodel& im,
    const meta_model::name& n) {

    auto i(im.enumerations().find(n.id()));
    if (i != im.enumerations().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an enumeration in model.";
        return true;
    }
    return false;
}

bool resolver::is_object(const meta_model::endomodel& im,
    const meta_model::name& n) {

    auto i(im.objects().find(n.id()));
    if (i != im.objects().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to an object in model.";
        return true;
    }
    return false;
}

bool resolver::is_object_template(const meta_model::endomodel& im,
    const meta_model::name& n) {

    auto i(im.object_templates().find(n.id()));
    if (i != im.object_templates().end()) {
        BOOST_LOG_SEV(lg, debug) << "Name belongs to a object_template in model.";
        return true;
    }
    return false;
}

bool resolver::
is_name_referable(const indices& idx, const meta_model::name& n) {
    BOOST_LOG_SEV(lg, debug) << "Checking to see if name is referable:" << n;

    const auto i(idx.elements_referable_by_attributes().find(n.id()));
    if (i != idx.elements_referable_by_attributes().end())
        return true;

    BOOST_LOG_SEV(lg, debug) << "Name not found in model or its not referable.";
    return false;
}

meta_model::name resolver::resolve_name_with_internal_modules(
    const meta_model::endomodel& im, const indices& idx,
    const meta_model::name& ctx, const meta_model::name& n) {

    /*
     * Since the user has bothered to provide an internal module path,
     * we should just go with what we got and see if it resolves. This
     * caters for the case of the user providing an absolute internal
     * path, either to the current package or to elsewhere in the same
     * model as the context.
     *
     * Very important: we do not support relative paths from the
     * context - e.g. add the user path to the context path. We simply
     * assume all paths provided are absolute. Thus if there is an
     * internal path in the context as well, we simply ignore it. This
     * may be a surprising behaviour for some users so we may need to
     * revisit it in the future.
     */
    name_factory nf;
    auto r(nf.build_combined_element_name(ctx, n,
            true/*populate_model_modules_if_blank*/));
    BOOST_LOG_SEV(lg, debug) << "Resolving with internal modules: " << r;

    if (is_name_referable(idx, r)) {
        BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
        return r;
    }

    /*
     * Now we handle the case where we have mis-classified a model
     * module as an internal path. The problem is that when we are
     * parsing attribute types, we do not know if the user is
     * referring to an internal module or to a model. So at parsing
     * time we classify /everything/ as an internal module. At
     * resolution time, we are now left with the task of trying to
     * figure out the real internal modules from the model
     * modules. The only way to do this is to try it and see if it
     * resolves.
     *
     * Note that we handle correctly cases where there are both an
     * internal module and a model module with the same name; first we
     * check for the internal module, and if that fails (above), we
     * then check for the model module.
     */
    BOOST_LOG_SEV(lg, debug) << "Resolving using internal module promotion.";

    {
        /*
         * We first try to promote the internal module without
         * relying on external modules at all. This catches the
         * classic "std::string" et al. scenarios.
         */
        BOOST_LOG_SEV(lg, debug) << "Trying promotion on its own.";

        auto r(nf.build_promoted_module_name(n));
        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
    }

    {
        /*
         * Then we try using the main model's external modules. This
         * is for cases where the user has made an explicit reference
         * to the current model - it would fail because of the missing
         * external modules.
         */
        BOOST_LOG_SEV(lg, debug) << "Resolving using model: " << im.name();

        auto r(nf.build_promoted_module_name(im.name(), n));
        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
    }

    /*
     * FIXME: major hack to get external modules to model modules
     * conversion to work.
     */
    BOOST_LOG_SEV(lg, debug) << "Resolving using hacked name: " << im.name();
    if (!im.name().location().model_modules().empty()) {
        auto r(nf.build_hacked_combined_element_name(im.name(), n));
        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
    }

    /*
     * Now let's try the same thing but for the references. Note
     * that we do not really need to go through all of this, we
     * could simply slot the references into a set and see if the
     * internal module path maps any of the references.
     */
    for (const auto& pair : im.references()) {
        const auto& ref(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Resolving using reference: "
                                 << ref;

        auto r(nf.build_promoted_module_name(ctx, n));
        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
    }

    /*
     * The name cannot cannot be resolved.
     */
    BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
}

boost::optional<meta_model::name> resolver::
try_resolve_name_with_context_internal_modules(const indices& idx,
    meta_model::name ctx, const meta_model::name& n) {

    BOOST_LOG_SEV(lg, debug) << "Context has internal modules.";

    /*
     * If we do not have an internal module path set but the
     * context does, we need to traverse it all the way up to
     * the model module, and see if anything matches. This
     * allows us to refer to types inside a package without
     * having to fully qualify them.
     *
     * We start at the innermost internal module and make our way
     * upwards.
     */
    name_factory nf;
    auto r(nf.build_combined_element_name(ctx, n,
            true/*populate_model_modules_if_blank*/,
            true/*populate_internal_modules_if_blank*/));

    BOOST_LOG_SEV(lg, debug) << "Internal modules climb: " << r;

    if (is_name_referable(idx, r)) {
        BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
        return r;
    }

    do {
        ctx.location().internal_modules().pop_back();
        r.location().internal_modules().clear();
        r = nf.build_combined_element_name(ctx, r,
            true/*populate_model_modules_if_blank*/,
            true/*populate_internal_modules_if_blank*/);

        BOOST_LOG_SEV(lg, debug) << "Internal modules climb: " << r;

        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
    } while (!ctx.location().internal_modules().empty());

    /*
     * If we didn't find anything, we should not throw as there still
     * are other possibilities left to try.
     */
    return boost::optional<meta_model::name>();
}

meta_model::name resolver::
resolve_name(const meta_model::endomodel& im, const indices& idx,
    const meta_model::name& ctx, const meta_model::name& n) {

    BOOST_LOG_SEV(lg, debug) << "Resolving name: " << n.id();
    BOOST_LOG_SEV(lg, debug) << "Initial state: " << n;
    BOOST_LOG_SEV(lg, debug) << "Context: " << ctx;

    /*
     * If the user has supplied internal modules we must use those, to
     * the exclusion of everything else.
     */
    if (!n.location().internal_modules().empty()) {
        BOOST_LOG_SEV(lg, debug) << "Name has internal modules.";
        return resolve_name_with_internal_modules(im, idx, ctx, n);
    }

    /*
     * If the context has internal modules we should try to use those
     * and see if anything comes up.
     */
    BOOST_LOG_SEV(lg, debug) << "Name does not have internal modules.";
    if (!ctx.location().internal_modules().empty()) {
        auto r(try_resolve_name_with_context_internal_modules(idx, ctx, n));
        if (r)
            return *r;

        BOOST_LOG_SEV(lg, debug) << "Failed to resolve with context's "
                                 << "internal modules.";
    } else
        BOOST_LOG_SEV(lg, debug) << "Context does not have internal modules.";

    /*
     * Perhaps the user just wants to refer to a type in the current
     * model. We use the context to obtain both the module path and
     * the external module path. The scenario is that the user
     * provided a name but said nothing else about it, so we assume it
     * refers to something in the current context.
     */
    name_factory nf;
    {
        auto r(nf.build_combined_element_name(ctx, n,
                true/*populate_model_modules_if_blank*/));

        if (is_name_referable(idx, r)) {
            BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
            return r;
        }
    }

    /*
     * Finally, the only other possibility is that the name is on the
     * global module.
     */
    BOOST_LOG_SEV(lg, debug) << "Trying global module.";
    if (is_name_referable(idx, n)) {
        BOOST_LOG_SEV(lg, debug) << "Resolution succeeded.";
        return n;
    }

    /*
     * The name cannot cannot be resolved.
     */
    BOOST_LOG_SEV(lg, error) << undefined_type << n.id();
    BOOST_THROW_EXCEPTION(resolution_error(undefined_type + n.id()));
}

void resolver::resolve_name_tree(const meta_model::endomodel& im,
    const indices& idx, const meta_model::name& owner,
    meta_model::name_tree& nt) {

    const meta_model::name n(resolve_name(im, idx, owner, nt.current()));

    BOOST_LOG_SEV(lg, debug) << "Resolved name: " << nt.current().id()
                             << " to: " << n.id();
    nt.current(n);
    if (is_builtin(im, n)) {
        nt.is_current_simple_type(true);
        nt.is_floating_point(is_floating_point(im, n));
    } else
        nt.is_current_simple_type(is_enumeration(im, n));

    const auto i(idx.objects_always_in_heap().find(n.id()));
    nt.are_children_opaque(i != idx.objects_always_in_heap().end());

    identifiable_and_qualified_builder iqb;
    iqb.add(n);

    /*
     * Strictly speaking this is not directly related to
     * resolution. However, we can only find circular dependencies
     * after we have resolved all names and since we're already here
     * might as well mark them.
     */
    if (owner == nt.current()) {
        nt.is_circular_dependency(true);
        BOOST_LOG_SEV(lg, debug) << "Found circular dependency. Owner: "
                                 << owner.id();
    }

    for (auto& c : nt.children()) {
        resolve_name_tree(im, idx, owner, c);
        iqb.add(c);
    }

    const auto iq(iqb.build());
    nt.identifiable(iq.first);
    nt.qualified(iq.second);
}

void resolver::resolve_attribute(const meta_model::endomodel& im,
    const indices& idx, const meta_model::name& owner,
    meta_model::attribute& attr) {

    try {
        resolve_name_tree(im, idx, owner, attr.parsed_type());

        /*
         * We must rely on simple names as attribute expansion has not
         * yet been performed.
         */
        BOOST_LOG_SEV(lg, debug) << "Resolved attribute: "
                                 << attr.name().simple();
    } catch (boost::exception& e) {
        std::ostringstream s;
        s << "Owner type name: " << owner.id()
          << " Attribute name: " << attr.name()
          << " Attribute type: " << attr.parsed_type();
        e << errmsg_info(s.str());
        throw;
    }
}

void resolver::resolve_attributes(const meta_model::endomodel& im,
    const indices& idx, const meta_model::name& owner,
    std::list<meta_model::attribute>& attributes) {

    for (auto& attr : attributes)
        resolve_attribute(im, idx, owner, attr);
}

void resolver::
validate_inheritance_graph(const meta_model::endomodel& im,
    const meta_model::object& o) {
    /*
     * Ensure that all parents and original parents exist as objects.
     */
    const auto id(o.name().id());
    for (const auto& pn : o.parents()) {
        if (is_object(im, pn))
            continue;

        std::ostringstream s;
        s << orphan_object << ": " << id << ". Parent: " << pn.id();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(resolution_error(s.str()));
    }

    for (const auto& rp : o.root_parents()) {
        if (is_object(im, rp))
            continue;

        std::ostringstream s;
        s << orphan_object << ": " << id << ". Root parent: " << rp.id();

        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(resolution_error(s.str()));
    }
}

void resolver::validate_object_template_inheritance(
    const meta_model::endomodel& im, const meta_model::object_template& otp) {
    const auto id(otp.name().id());
    for (const auto& n : otp.parents()) {
        if (is_object_template(im, n))
            continue;

        std::ostringstream stream;
        stream << orphan_object_template << ". Object template: " << id
               << ". Inherited object template: " << n.id();

        BOOST_LOG_SEV(lg, error) << stream.str();
        BOOST_THROW_EXCEPTION(resolution_error(stream.str()));
    }
}

void resolver::
resolve_object_templates(const indices& idx, meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Resolving object templates. Size: "
                             << im.object_templates().size();

    for (auto& pair : im.object_templates()) {
        auto& otp(pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving object template: "
                                 << otp->name().id();
        resolve_attributes(im, idx, otp->name(), otp->local_attributes());
        validate_object_template_inheritance(im, *otp);
        BOOST_LOG_SEV(lg, debug) << "Resolved object template.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved object templates.";
}

void resolver::
resolve_objects(const indices& idx, meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Resolving objects. Size: "
                             << im.objects().size();

    for (auto& pair : im.objects()) {
        auto& o(*pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving object: " << o.name().id();
        validate_inheritance_graph(im, o);
        resolve_attributes(im, idx, o.name(), o.local_attributes());
        BOOST_LOG_SEV(lg, debug) << "Resolved object.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved objects.";
}

void resolver::
resolve_enumerations(const indices& idx, meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Resolving enumerations. Size: "
                             << im.enumerations().size();

    for (auto& pair : im.enumerations()) {
        auto& e(*pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving enumeration: " << e.name().id();

        /*
         * If we're not relying on the underlying element, we don't
         * need to worry about resolving it.
         */
        if (e.use_implementation_defined_underlying_element())
            continue;

        const auto ue(e.underlying_element());
        const auto ue_id(ue.id());
        BOOST_LOG_SEV(lg, debug) << "Underlying element: '" << ue_id << "'";

        const auto i(idx.enumeration_underliers().find(ue_id));
        if (i == idx.enumeration_underliers().end()) {
            BOOST_LOG_SEV(lg, error) << invalid_underlying_type << ue_id
                                     << " for enumeration: " << e.name().id();
            BOOST_THROW_EXCEPTION(
                resolution_error(invalid_underlying_type + ue_id));
        }
        BOOST_LOG_SEV(lg, debug) << "Resolved enumeration.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved enumerations.";
}

void resolver::
resolve_primitives(const indices& idx, meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Resolving primitives. Size: "
                             << im.primitives().size();

    for (auto& pair : im.primitives()) {
        auto& p(*pair.second);

        BOOST_LOG_SEV(lg, debug) << "Resolving primitive: " << p.name().id();

        /*
         * We must resolve the attribute as well as validate it
         * because we need to update its properties as part of
         * resolution.
         */
        auto& attr(p.value_attribute());
        resolve_attribute(im, idx, p.name(), attr);

        const auto& ue_id(attr.parsed_type().current().id());
        const auto i(idx.primitive_underliers().find(ue_id));
        if (i == idx.primitive_underliers().end()) {
            BOOST_LOG_SEV(lg, error) << invalid_underlying_type << ue_id
                                     << " for primitive: " << p.name().id();
            BOOST_THROW_EXCEPTION(
                resolution_error(invalid_underlying_type + ue_id));
        }
        BOOST_LOG_SEV(lg, debug) << "Resolved primitive.";
    }

    BOOST_LOG_SEV(lg, debug) << "Resolved primitives.";
}

meta_model::name resolver::
resolve(const meta_model::endomodel& im, const indices& idx,
    const meta_model::name& ctx, const meta_model::name& n) {

    const auto r(resolve_name(im, idx, ctx, n));
    BOOST_LOG_SEV(lg, debug) << "Resolved name: " << n.id()
                             << " to: " << r.id();
    return r;
}

boost::optional<meta_model::name> resolver::
try_resolve_object_template_name(meta_model::name ctx, const std::string& s,
    const meta_model::endomodel& im) {

    BOOST_LOG_SEV(lg, debug) << "Resolving object template name: " << s;

    /*
     * We first start at the same level as the context, including any
     * internal modules.
     */
    meta_model::name n;
    n.simple(s);

    name_factory nf;
    auto r(nf.build_combined_element_name(ctx, n,
            true/*populate_model_modules_if_blank*/,
            true/*populate_internal_modules_if_blank*/));

    BOOST_LOG_SEV(lg, debug) << "Internal modules climb: " << r;

    auto i(im.object_templates().find(r.id()));
    if (i != im.object_templates().end()) {
        BOOST_LOG_SEV(lg, debug) << "Found object template.";
        return r;
    }
    BOOST_LOG_SEV(lg, debug) << "Resolution failed.";

    /*
     * If we did not have any luck and there are internal modules, we
     * start a climb towards the model module and see if that finds us
     * any object templates.
     */
    if (!ctx.location().internal_modules().empty()) {
        do {
            ctx.location().internal_modules().pop_back();
            r.location().internal_modules().clear();
            r = nf.build_combined_element_name(ctx, r,
                true/*populate_model_modules_if_blank*/,
                true/*populate_internal_modules_if_blank*/);

            BOOST_LOG_SEV(lg, debug) << "Internal modules climb: " << r;

            i = im.object_templates().find(r.id());
            if (i != im.object_templates().end()) {
                BOOST_LOG_SEV(lg, debug) << "Found object templates.";
                return r;
            }
        } while (!ctx.location().internal_modules().empty());
    }

    /*
     * There are no object templates in this model which match the
     * stereotype name.
     */
    BOOST_LOG_SEV(lg, debug) << "Could not find a object template with tentative name.";
    return boost::optional<meta_model::name>();
}

boost::optional<meta_model::name>
resolver::try_resolve_object_template_name(const meta_model::name& ctx,
    const meta_model::name& n, const meta_model::endomodel& im) {
    // FIXME: hack for now, just take simple name. Requires a bit more
    // thinking.
    return try_resolve_object_template_name(ctx, n.simple(), im);
}

void resolver::resolve(const indices& idx, meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Resolving model: " << im.name().id();

    resolve_object_templates(idx, im);
    resolve_objects(idx, im);
    resolve_enumerations(idx, im);
    resolve_primitives(idx, im);

    BOOST_LOG_SEV(lg, debug) << "Resolved model.";
}

} } }
