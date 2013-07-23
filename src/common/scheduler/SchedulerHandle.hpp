/**
 * @file SchedulerHandle.hpp
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

#ifndef COMMON_SCHEDULER_SCHEDULER_HAMDLE_HPP
#define COMMON_SCHEDULER_SCHEDULER_HANDLE_HPP 1

namespace paradevs { namespace common { namespace scheduler {

struct NoSchedulerHandle
{
    NoSchedulerHandle()
    { }

    const NoSchedulerHandle& handle() const
    { return *this; }

    void handle(const NoSchedulerHandle& /* handle */)
    { }
};

} } } // namespace paradevs common scheduler

#endif
