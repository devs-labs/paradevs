/**
 * @file InternalEvent.hpp
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

#ifndef COMMON_INTERNAL_EVENT
#define COMMON_INTERNAL_EVENT 1

#include <common/Model.hpp>
#include <common/Time.hpp>

namespace paradevs { namespace common {

class InternalEvent
{
public:
    InternalEvent(const common::Time& time, common::Model* model);
    virtual ~InternalEvent();

    common::Model* get_model() const
    { return _model; }

    common::Time get_time() const
    { return _time; }

    bool operator<(InternalEvent const& e) const;

private:
    common::Time   _time;
    common::Model* _model;
};

} } // namespace paradevs common

#endif
