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
#include <boost/algorithm/string.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.utility/filesystem/file.hpp"
#include "dogen.formatting/types/utility_formatter.hpp"
#include "dogen.external.json/types/dehydrator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("external.json.dehydrator"));

const std::string scope("::");
const std::string comma_space(", ");
const std::string invalid_enumerator("invalid");

}

namespace dogen {
namespace external {
namespace json {

std::string dehydrator::tidy_up_string(std::string s) {
    boost::replace_all(s, "\r", "\\r");
    boost::replace_all(s, "\n", "\\n");
    boost::replace_all(s, "\"", "\\\"");
    return s;
}

void dehydrator::insert_documentation(std::ostream& s,  const std::string& d) {
    formatting::utility_formatter uf(s);
    uf.insert_quoted("documentation");
    s << " : ";
    uf.insert_quoted(tidy_up_string(d));
}

void dehydrator::insert_tagged_values(std::ostream& s,
    const std::list<std::pair<std::string, std::string>>& tv) {

    formatting::utility_formatter uf(s);
    uf.insert_quoted("tagged_values");
    s << " : { ";

    bool is_first(true);
    for (const auto& pair : tv) {
        if (!is_first)
            s << ", ";

        uf.insert_quoted(pair.first);
        s << " : ";
        uf.insert_quoted_escaped(pair.second);
        is_first = false;
    }
    s << " }";
}

void dehydrator::insert_stereotypes(std::ostream& s,
    const std::list<std::string>& st) {

    formatting::utility_formatter uf(s);
    uf.insert_quoted("stereotypes");
    s << " : [";

    bool is_first(true);
    for (const auto& stereotype : st) {
        if (!is_first)
            s << ", ";
        uf.insert_quoted(stereotype);
        is_first = false;
    }
    s << " ]";
}

void dehydrator::insert_parents(std::ostream& s,
    const std::list<std::string>& st) {

    formatting::utility_formatter uf(s);
    uf.insert_quoted("parents");
    s << " : [";

    bool is_first(true);
    for (const auto& stereotype : st) {
        if (!is_first)
            s << ", ";
        uf.insert_quoted(stereotype);
        is_first = false;
    }
    s << " ]";
}

void dehydrator::insert_attribute(std::ostream& s,
    const external::meta_model::attribute& a) {

    s << "{ ";

    formatting::utility_formatter uf(s);
    uf.insert_quoted("name");
    s << " : ";
    uf.insert_quoted_escaped(a.name());
    s << comma_space;
    uf.insert_quoted("type");
    s << " : ";
    uf.insert_quoted_escaped(a.type());

    if (!a.documentation().empty()) {
        s << comma_space;
        insert_documentation(s, a.documentation());
    }

    if (!a.stereotypes().empty()) {
        s << comma_space;
        insert_stereotypes(s, a.stereotypes());
    }

    if (!a.tagged_values().empty()) {
        s << comma_space;
        insert_tagged_values(s, a.tagged_values());
    }

    s << " }";
}

void dehydrator::insert_element(std::ostream& s,
    const external::meta_model::element& e) {

    s << "{ ";

    formatting::utility_formatter uf(s);
    uf.insert_quoted("name");
    s << " : ";
    uf.insert_quoted_escaped(e.name());

    if (!e.parents().empty()) {
        s << comma_space;
        insert_parents(s, e.parents());
    }

    if (!e.documentation().empty()) {
        s << comma_space;
        insert_documentation(s, e.documentation());
    }

    if (!e.stereotypes().empty()) {
        s << comma_space;
        insert_stereotypes(s, e.stereotypes());
    }

    if (!e.tagged_values().empty()) {
        s << comma_space;
        insert_tagged_values(s, e.tagged_values());
    }

    if (!e.fallback_element_type().empty()) {
        s << comma_space;
        uf.insert_quoted("fallback_element_type");
        s << " : ";
        uf.insert_quoted_escaped(e.fallback_element_type());
    }

    if (!e.attributes().empty()) {
        s << comma_space;
        uf.insert_quoted("attributes");
        s << " : [ ";
        bool is_first(true);
        for (const auto& a : e.attributes()) {
            if (!is_first)
                s << comma_space;
            insert_attribute(s, a);
            is_first = false;
        }
        s << " ] ";
    }

    s << " }";
}

std::string dehydrator::dehydrate(const external::meta_model::model& m) {
    std::ostringstream s;

    s << "{ ";
    if (!m.documentation().empty())
        insert_documentation(s, m.documentation());

    if (!m.stereotypes().empty()) {
        if (!m.documentation().empty())
            s << ", ";
        insert_stereotypes(s, m.stereotypes());
    }

    if (!m.tagged_values().empty()) {
        if (!m.documentation().empty() || !m.stereotypes().empty())
            s << comma_space;
        insert_tagged_values(s, m.tagged_values());
    }

    if (!m.documentation().empty() || !m.stereotypes().empty() ||
        !m.tagged_values().empty()) {
        s << comma_space;
    }

    formatting::utility_formatter uf(s);
    uf.insert_quoted("elements");
    s << " : [ ";
    bool is_first(true);
    for (const auto& e : m.elements()) {
        if (!is_first)
            s << comma_space;
        insert_element(s, e);
        is_first = false;
    }
    s << " ]";
    s << " }";

    return s.str();
}

void dehydrator::dehydrate(const external::meta_model::model& m,
    const boost::filesystem::path& p) {
    const auto s(dehydrate(m));
    utility::filesystem::write_file_content(p, s);
}

} } }
