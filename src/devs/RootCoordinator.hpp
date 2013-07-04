/**
 * @file RootCoordinator.hpp
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

#ifndef DEVS_ROOT_COORDINATOR
#define DEVS_ROOT_COORDINATOR 1

#include <devs/Builder.hpp>
#include <devs/Coordinator.hpp>

namespace paradevs {

class RootCoordinator
{
public :
    RootCoordinator(const Time& t_start, const Time& t_max,
                    const Builder& builder);
    virtual ~RootCoordinator();

    void run();

private :
    Coordinator* _root;
    Time         _t_max;

    Time _tn;
};

} // namespace paradevs

#endif
