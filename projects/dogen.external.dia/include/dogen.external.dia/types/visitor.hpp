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
#ifndef DOGEN_EXTERNAL_DIA_TYPES_VISITOR_HPP
#define DOGEN_EXTERNAL_DIA_TYPES_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <functional>
#include <boost/graph/depth_first_search.hpp>
#include "dogen.external.dia/types/grapher.hpp"
#include "dogen.external.dia/types/builder.hpp"

namespace dogen {
namespace external {
namespace dia {

class visitor : public boost::default_dfs_visitor {
public:
    visitor() = delete;
    visitor& operator=(const visitor&) = default;
    visitor(const visitor&) = default;
    visitor(visitor&&) = default;

public:
    explicit visitor(builder& b);

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        const auto& o(g[u]);
        if (o.id() != grapher::root_id())
            builder_.add(o);
    }

private:
    builder& builder_;
};
} } }

#endif
