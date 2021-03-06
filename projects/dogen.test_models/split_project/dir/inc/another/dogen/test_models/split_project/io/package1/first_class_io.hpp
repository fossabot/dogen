#ifndef DOGEN_TEST_MODELS_SPLIT_PROJECT_IO_PACKAGE1_FIRST_CLASS_IO_HPP
#define DOGEN_TEST_MODELS_SPLIT_PROJECT_IO_PACKAGE1_FIRST_CLASS_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/test_models/split_project/types/package1/first_class.hpp"

namespace dogen {
namespace test_models {
namespace split_project {
namespace package1 {

std::ostream&
operator<<(std::ostream& s,
     const dogen::test_models::split_project::package1::first_class& v);

} } } }

#endif
