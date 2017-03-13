#ifndef DOGEN_TEST_MODELS_LAM_MODEL_TYPES_PACKAGE1_CLASS_IN_PACKAGE_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_TYPES_PACKAGE1_CLASS_IN_PACKAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/lam_model/serialization/package1/class_in_package_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {
namespace package1 {

class class_in_package final {
public:
    class_in_package(const class_in_package&) = default;
    class_in_package(class_in_package&&) = default;
    ~class_in_package() = default;

public:
    class_in_package();

public:
    explicit class_in_package(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::lam_model::package1::class_in_package& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::lam_model::package1::class_in_package& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

public:
    bool operator==(const class_in_package& rhs) const;
    bool operator!=(const class_in_package& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_in_package& other) noexcept;
    class_in_package& operator=(class_in_package other);

private:
    int prop_0_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::test_models::lam_model::package1::class_in_package& lhs,
    dogen::test_models::lam_model::package1::class_in_package& rhs) {
    lhs.swap(rhs);
}

}

#endif