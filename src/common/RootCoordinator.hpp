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

#ifndef COMMON_ROOT_COORDINATOR
#define COMMON_ROOT_COORDINATOR 1

#include <common/Time.hpp>

#include <string>

namespace paradevs { namespace common {

template < class Coordinator >
class RootCoordinator
{
public :
    RootCoordinator(const common::Time& t_start, const common::Time& t_max,
                    const std::string& root_name,
                    const typename Coordinator::parameters_type& parameters) :
        _root(root_name, parameters), _t_max(t_max), _tn(t_start)
    { }

    virtual ~RootCoordinator()
    { }

    void run()
    {
        _tn = _root.start(_tn);
        while (_tn <= _t_max) {
            _root.output(_tn);
            _tn = _root.transition(_tn);
        }
    }

private :
    Coordinator  _root;
    common::Time _t_max;

    common::Time _tn;
};

} } // namespace paradevs common

#endif
