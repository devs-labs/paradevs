/**
 * @file Simulator.hpp
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

#ifndef DEVS_SIMULATOR
#define DEVS_SIMULATOR 1

#include <devs/Model.hpp>
#include <devs/Dynamics.hpp>
#include <devs/Links.hpp>
#include <devs/Node.hpp>

namespace paradevs {

class Simulator : public Model
{
public :
    Simulator(Dynamics* dynamics);
    virtual ~Simulator();

    virtual Time i_message(Time /* t */);
    virtual Time s_message(Time /* t */);
    virtual Time x_message(const Message& /* message */, Time /* t */);
    virtual void observation(std::ostream& file) const;

    virtual Dynamics* get_dynamics() const
    { return _dynamics; }

private :
    Dynamics* _dynamics;
};

} // namespace paradevs

#endif
