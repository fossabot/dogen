#ifndef DOGEN_TEST_MODELS_CPP_98_IO_NO_DEFAULT_CTOR_IO_HPP
#define DOGEN_TEST_MODELS_CPP_98_IO_NO_DEFAULT_CTOR_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include "dogen/test_models/cpp_98/types/no_default_ctor.hpp"

namespace dogen {
namespace test_models {
namespace cpp_98 {

std::ostream&
operator<<(std::ostream& s,
     const dogen::test_models::cpp_98::no_default_ctor& v);

} } }

#endif
