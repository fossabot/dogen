/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FILE_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FILE_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/types/formattables/includes.hpp"
#include "dogen/cpp/types/formattables/formattable_fwd.hpp"
#include "dogen/cpp/types/formattables/content_descriptor.hpp"
#include "dogen/cpp/serialization/formattables/file_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents a file containing C++ source code.
 */
class file_info final {
public:
    file_info() = default;
    file_info(const file_info&) = default;
    ~file_info() = default;

public:
    file_info(file_info&& rhs);

public:
    file_info(
        const std::string& documentation,
        const dogen::cpp::formattables::includes& includes,
        const dogen::cpp::formattables::content_descriptor& descriptor,
        const std::string& header_guard,
        const boost::filesystem::path& file_path,
        const boost::filesystem::path& relative_path,
        const boost::shared_ptr<dogen::cpp::formattables::formattable>& formattable);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const file_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, file_info& v, unsigned int version);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Headers included by this source file.
     */
    /**@{*/
    const dogen::cpp::formattables::includes& includes() const;
    dogen::cpp::formattables::includes& includes();
    void includes(const dogen::cpp::formattables::includes& v);
    void includes(const dogen::cpp::formattables::includes&& v);
    /**@}*/

    /**
     * @brief Description of the file's content.
     */
    /**@{*/
    const dogen::cpp::formattables::content_descriptor& descriptor() const;
    dogen::cpp::formattables::content_descriptor& descriptor();
    void descriptor(const dogen::cpp::formattables::content_descriptor& v);
    void descriptor(const dogen::cpp::formattables::content_descriptor&& v);
    /**@}*/

    /**
     * @brief If file type is header, name to use for header guards.
     */
    /**@{*/
    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);
    /**@}*/

    /**
     * @brief Path to the file.
     */
    /**@{*/
    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Relative path to file.
     */
    /**@{*/
    const boost::filesystem::path& relative_path() const;
    boost::filesystem::path& relative_path();
    void relative_path(const boost::filesystem::path& v);
    void relative_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Formattable contained in this file, if any.
     */
    /**@{*/
    const boost::shared_ptr<dogen::cpp::formattables::formattable>& formattable() const;
    boost::shared_ptr<dogen::cpp::formattables::formattable>& formattable();
    void formattable(const boost::shared_ptr<dogen::cpp::formattables::formattable>& v);
    void formattable(const boost::shared_ptr<dogen::cpp::formattables::formattable>&& v);
    /**@}*/

public:
    bool operator==(const file_info& rhs) const;
    bool operator!=(const file_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(file_info& other) noexcept;
    file_info& operator=(file_info other);

private:
    std::string documentation_;
    dogen::cpp::formattables::includes includes_;
    dogen::cpp::formattables::content_descriptor descriptor_;
    std::string header_guard_;
    boost::filesystem::path file_path_;
    boost::filesystem::path relative_path_;
    boost::shared_ptr<dogen::cpp::formattables::formattable> formattable_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::file_info& lhs,
    dogen::cpp::formattables::file_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
