/**
 * @file EventTable.hpp
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

#ifndef COMMON_EVENT_TABLE
#define COMMON_EVENT_TABLE 1

#include <common/InternalEvent.hpp>

namespace paradevs { namespace common {

class EventTable : protected std::vector < InternalEvent >
{
public:
    EventTable()
    { }
    virtual ~EventTable()
    { }

    Model* get_current_model();

    common::Time get_current_time() const
    { return back().get_time(); }

    void init(common::Time time, Model* model);
    void put(common::Time time, Model* model);

    std::string to_string() const;

private:
    void remove(Model* model);

};

} } // namespace paradevs common

#endif
