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
#include <array>
#include <boost/test/unit_test.hpp>
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/test/asserter.hpp"
#include "dogen.utility/io/unordered_map_io.hpp"
#include "dogen.utility/test/exception_checkers.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"
#include "dogen.modeling/types/meta_model/endomodel.hpp"
#include "dogen.modeling/io/meta_model/endomodel_io.hpp"
#include "dogen.modeling/io/meta_model/object_io.hpp"
#include "dogen.modeling/types/transforms/transformation_error.hpp"
#include "dogen.modeling/test/mock_context_factory.hpp"
#include "dogen.modeling/test/mock_endomodel_factory.hpp"
#include "dogen.modeling/types/transforms/attributes_transform.hpp"

namespace {

const std::string test_module("yarn");
const std::string test_suite("attributes_transform_tests");

const std::string object_template_not_found("Object template not found");
const std::string object_not_found("Object not found in model");

using dogen::modeling::test::mock_endomodel_factory;

/**
 * @brief We require the object templates to have been indexed or else
 * we won't work.
 */
const mock_endomodel_factory::flags
flags(false/*tagged*/, false/*resolved*/, false/*merged*/,
    true/*object_templates_indexed*/, false/*attributes_indexed*/,
    true/*types parsed*/);
const mock_endomodel_factory factory(flags);

template<typename Stateful>
bool has_duplicate_attribute_names(const Stateful& s,
    dogen::utility::log::logger& lg) {
    std::unordered_map<std::string, unsigned int> count;

    for (const auto& pair : s.inherited_attributes())
        for (const auto& p : pair.second)
            count[p.name().simple()]++;

    for (const auto& p : s.local_attributes())
        count[p.name().simple()]++;

    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "Inherited/local attributes for "
                             << s.name().id() << ": " << count;

    for (const auto& pair : count)
        if (pair.second > 1)
            return true;

    count.clear();
    for (const auto& p : s.all_attributes())
        count[p.name().simple()]++;

    BOOST_LOG_SEV(lg, debug) << "All attributes for "
                             << s.name().id() << ": " << count;

    for (const auto& pair : count)
        if (pair.second > 1)
            return true;

    return false;
}

}

using dogen::utility::test::contains_checker;
using dogen::modeling::transforms::transformation_error;
using dogen::utility::test::asserter;
using dogen::modeling::transforms::attributes_transform;
using dogen::modeling::meta_model::origin_types;
using object_types = dogen::modeling::test::mock_endomodel_factory::
object_types;
using attribute_types = dogen::modeling::test::mock_endomodel_factory::
attribute_types;
using dogen::modeling::test::mock_context_factory;

BOOST_AUTO_TEST_SUITE(attributes_transform_tests)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_attributes_transform) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_attributes_transform");

    auto a(factory.make_empty_model());
    const auto e(factory.make_empty_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    attributes_transform::transform(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_attributes_is_untouched_by_attributes_transform) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_attributes_is_untouched_by_attributes_transform");

    auto a(factory.make_single_type_model());
    const auto e(factory.make_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    attributes_transform::transform(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_attribute_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_attribute_results_in_expected_attributes");

    const auto ot(origin_types::target);
    const auto objt(object_types::value_object);
    const auto at(attribute_types::unsigned_int);
    auto m(factory.object_with_attribute(ot, objt, at));
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.objects().size() == 1);

    const auto& o(*m.objects().begin()->second);
    BOOST_CHECK(o.local_attributes() == o.all_attributes());
    BOOST_CHECK(o.inherited_attributes().empty());
}

BOOST_AUTO_TEST_CASE(model_with_single_object_template_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_single_object_template_results_in_expected_attributes");

    auto m(factory.make_single_object_template_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.object_templates().size() == 1);
    const auto& otp(*(m.object_templates().begin()->second));
    BOOST_CHECK(otp.local_attributes().size() == 1);
    BOOST_CHECK(otp.inherited_attributes().empty());
    BOOST_CHECK(otp.local_attributes() == otp.all_attributes());

    BOOST_REQUIRE(m.objects().size() == 1);
    const auto& o(*(m.objects().begin()->second));
    BOOST_CHECK(o.local_attributes().size() == 2);
    BOOST_CHECK(o.inherited_attributes().empty());
    BOOST_CHECK(o.all_attributes() == o.local_attributes());
    BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
}

BOOST_AUTO_TEST_CASE(model_with_one_level_of_object_templates_inheritance_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_one_level_of_object_templates_inheritance_results_in_expected_attributes");

    auto m(factory.make_first_degree_object_templates_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    for (const auto& pair : m.object_templates()) {
        const auto& ot(*pair.second);
        const auto& n(ot.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(ot.inherited_attributes().empty());
            BOOST_CHECK(ot.all_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes() == ot.local_attributes());
            BOOST_CHECK(ot.parents().empty());
        } else if (factory.is_object_template_name_n(1, n)) {
            BOOST_CHECK(ot.parents().size() == 1);
            BOOST_REQUIRE(ot.inherited_attributes().size() == 1);
            const auto props(ot.inherited_attributes().begin()->second);
            BOOST_REQUIRE(props.size() == 1);

            BOOST_CHECK(ot.all_attributes().size() == 2);
            BOOST_CHECK(ot.local_attributes().size() == 1);
            BOOST_CHECK(!has_duplicate_attribute_names(ot, lg));
        } else
            BOOST_FAIL("Unexpected object template: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 1);
            BOOST_CHECK(o.local_attributes().size() == 1);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 3);
            BOOST_CHECK(o.local_attributes().size() == 3);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_two_levels_of_object_templates_inheritance_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_two_levels_of_object_templates_inheritance_results_in_expected_attributes");

    auto m(factory.make_second_degree_object_templates_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_REQUIRE(m.object_templates().size() == 3);
    for (const auto& pair : m.object_templates()) {
        const auto& ot(*pair.second);
        const auto& n(ot.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(ot.inherited_attributes().empty());
            BOOST_CHECK(ot.all_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes() == ot.local_attributes());
            BOOST_CHECK(ot.parents().empty());
        } else if (factory.is_object_template_name_n(1, n)) {
            BOOST_REQUIRE(ot.inherited_attributes().size() == 1);
            const auto props(ot.inherited_attributes().begin()->second);
            BOOST_REQUIRE(props.size() == 1);

            BOOST_CHECK(ot.local_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes().size() == 2);
            BOOST_CHECK(ot.parents().size() == 1);
            BOOST_CHECK(!has_duplicate_attribute_names(ot, lg));
        } else if (factory.is_object_template_name_n(2, n)) {
            BOOST_CHECK(ot.inherited_attributes().size() == 2);
            for (const auto& pair : ot.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(ot.local_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes().size() == 3);
            BOOST_CHECK(ot.parents().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(ot, lg));
        } else
            BOOST_FAIL("Unexpected object template: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 3);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 1);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_REQUIRE(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 2);
            BOOST_CHECK(o.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_REQUIRE(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 4);
            BOOST_CHECK(o.all_attributes().size() == 4);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_diamond_object_template_inheritance_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_diamond_object_template_inheritance_results_in_expected_attributes");

    auto m(factory.make_diamond_inheritance_object_templates_model());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;
    BOOST_CHECK(m.object_templates().size() == 4);
    for (const auto& pair : m.object_templates()) {
        const auto& ot(*pair.second);
        const auto& n(ot.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(ot.inherited_attributes().empty());
            BOOST_CHECK(ot.local_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes() == ot.local_attributes());
        } else if (factory.is_object_template_name_n(1, n)) {
            BOOST_CHECK(ot.inherited_attributes().size() == 1);
            for (const auto& pair : ot.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(ot.local_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(ot, lg));
        } else if (factory.is_object_template_name_n(2, n)) {
            BOOST_CHECK(ot.inherited_attributes().size() == 1);
            for (const auto& pair : ot.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(ot.local_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(ot, lg));
        } else if (factory.is_object_template_name_n(3, n)) {
            BOOST_CHECK(ot.inherited_attributes().size() == 3);
            for (const auto& pair : ot.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(ot.local_attributes().size() == 1);
            BOOST_CHECK(ot.all_attributes().size() == 4);
            BOOST_CHECK(!has_duplicate_attribute_names(ot, lg));
        } else
            BOOST_FAIL("Unexpected object template: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& o(*(m.objects().begin()->second));
        BOOST_CHECK(o.inherited_attributes().empty());
        BOOST_CHECK(o.local_attributes().size() == 4);
        BOOST_CHECK(o.all_attributes().size() == 4);
        BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
    }
}

BOOST_AUTO_TEST_CASE(model_with_single_parent_that_does_not_instantiate_object_templates_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_single_parent_that_does_not_instantiate_object_templates_results_in_expected_attributes");

    auto a(factory.object_with_parent_in_the_same_model());
    auto e(factory.object_with_parent_in_the_same_model());
    for (auto& pair : e.objects()) {
        auto& o(*pair.second);
        if (!o.parents().empty()) {
            BOOST_REQUIRE(o.parents().size() == 1);
            o.inherited_attributes()[o.parents().front()];
        }
    }

    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_REQUIRE(a.objects().size() == 2);
    BOOST_REQUIRE(a.object_templates().empty());

    attributes_transform::transform(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_third_degree_inheritance_that_does_not_model_object_templates_and_has_no_attributes_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_model_object_templates_and_has_no_attributes_results_in_expected_attributes");

    auto a(factory.object_with_third_degree_parent_in_same_model());
    auto e(factory.object_with_third_degree_parent_in_same_model());
    for (auto& pair : e.objects()) {
        auto& o(*pair.second);
        if (!o.parents().empty()) {
            BOOST_REQUIRE(o.parents().size() == 1);
            o.inherited_attributes()[o.parents().front()];
        }
    }

    BOOST_LOG_SEV(lg, debug) << "before transform: " << a;

    BOOST_REQUIRE(a.objects().size() == 4);
    BOOST_REQUIRE(a.object_templates().empty());

    attributes_transform::transform(mock_context_factory::make(), a);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_third_degree_inheritance_that_does_not_instantiate_object_templates_but_has_attributes_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_instantiate_object_templates_but_has_attributes_results_in_expected_attributes");

    auto m(factory.object_with_third_degree_parent_in_same_model(
            origin_types::target, true/*has_attribute*/));
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    BOOST_REQUIRE(m.objects().size() == 4);
    BOOST_REQUIRE(m.object_templates().empty());

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;
    BOOST_REQUIRE(m.objects().size() == 4);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(3, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes() == o.local_attributes());
        } else if (factory.is_type_name_n(2, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 2);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 2);

            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 3);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 3);

            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 4);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_containing_object_with_parent_that_instantiates_object_template_is_untouched_by_attributes_transform) {
    SETUP_TEST_LOG_SOURCE("model_containing_object_with_parent_that_instantiates_object_template_is_untouched_by_attributes_transform");

    auto m(factory.make_object_with_parent_that_instantiates_object_template());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_CHECK(m.object_templates().size() == 1);
    for (const auto& pair : m.object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(c.inherited_attributes().empty());
            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes() == c.local_attributes());
        } else
            BOOST_FAIL("Unexpected object template: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 1);
            BOOST_CHECK(o.all_attributes().size() == 1);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(o.local_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 1);
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_containing_object_with_parent_that_instantiates_a_child_object_template_results_in_expected_attributes) {
    SETUP_TEST_LOG_SOURCE("model_with_containing_object_with_parent_that_instantiates_a_child_object_template_results_in_expected_attributes");

    auto m(factory.make_object_with_parent_that_instantiates_a_child_object_template());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    attributes_transform::transform(mock_context_factory::make(), m);
    BOOST_LOG_SEV(lg, debug) << "after transform: " << m;

    BOOST_CHECK(m.object_templates().size() == 2);
    for (const auto& pair : m.object_templates()) {
        const auto& c(*pair.second);
        const auto& n(c.name());

        if (factory.is_object_template_name_n(0, n)) {
            BOOST_CHECK(c.inherited_attributes().empty());
            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes() == c.local_attributes());
        } else if (factory.is_object_template_name_n(1, n)) {
            BOOST_CHECK(c.inherited_attributes().size() == 1);
            for (const auto& pair : c.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 1);

            BOOST_CHECK(c.local_attributes().size() == 1);
            BOOST_CHECK(c.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(c, lg));
        } else
            BOOST_FAIL("Unexpected object template: " << n.id());
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& o(*pair.second);
        const auto& n(o.name());

        if (factory.is_type_name_n(0, n)) {
            BOOST_CHECK(o.inherited_attributes().empty());
            BOOST_CHECK(o.local_attributes().size() == 2);
            BOOST_CHECK(o.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_CHECK(o.inherited_attributes().size() == 1);
            for (const auto& pair : o.inherited_attributes())
                BOOST_CHECK(pair.second.size() == 2);

            BOOST_CHECK(o.local_attributes().empty());
            BOOST_CHECK(o.all_attributes().size() == 2);
            BOOST_CHECK(!has_duplicate_attribute_names(o, lg));
        } else
            BOOST_FAIL("Unexpected object: " << n.id());
    }
}

BOOST_AUTO_TEST_CASE(model_with_object_template_that_inhertis_missing_object_template_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_template_that_inhertis_missing_object_template_throws");

    auto m(factory.make_object_template_that_inherits_missing_object_template());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(object_template_not_found);
    BOOST_CHECK_EXCEPTION(attributes_transform::transform(
            mock_context_factory::make(), m), transformation_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_that_instantiates_missing_object_template_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_that_instantiates_missing_object_template_throws");

    auto m(factory.make_object_that_instantiates_missing_object_template());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(object_template_not_found);
    BOOST_CHECK_EXCEPTION(attributes_transform::transform(
            mock_context_factory::make(), m), transformation_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_that_instantiates_object_template_with_missing_parent_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_that_instantiates_object_template_with_missing_parent_throws");

    auto m(factory.make_object_that_instantiates_object_template_with_missing_parent());
    BOOST_LOG_SEV(lg, debug) << "before transform: " << m;

    contains_checker<transformation_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(attributes_transform::transform(
            mock_context_factory::make(), m), transformation_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
