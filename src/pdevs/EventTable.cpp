/**
 * @file EventTable.cpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013 ULCO http://www.univ-litoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <pdevs/EventTable.hpp>

#include <algorithm>
#include <sstream>

namespace paradevs { namespace pdevs {

Models EventTable::get_current_models(common::Time time) const
{
    Models models;
    bool found = true;

    for (const_reverse_iterator it = rbegin(); found and it != rend(); ++it) {
        if (it->get_time() == time) {
            models.push_back(dynamic_cast < Model* >(it->get_model()));
        } else {
            found = false;
        }
    }
    return models;
}

} } // namespace paradevs pdevs
