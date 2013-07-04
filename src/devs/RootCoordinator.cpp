/**
 * @file RootCoordinator.cpp
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

#include <devs/RootCoordinator.hpp>

namespace paradevs {

RootCoordinator::RootCoordinator(const Time& t_start, const Time& t_max,
                                 const Builder& builder) :
    _root(builder.build()), _t_max(t_max), _tn(t_start)
{ }

RootCoordinator::~RootCoordinator()
{ delete _root; }

void RootCoordinator::run()
{
    _tn = _root->i_message(_tn);
    while (_tn <= _t_max) {
        _tn = _root->s_message(_tn);
    }
}

} // namespace paradevs
