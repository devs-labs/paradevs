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

#ifndef PDEVS_SIMULATOR
#define PDEVS_SIMULATOR 1

#include <common/Links.hpp>
#include <common/Node.hpp>

#include <pdevs/Model.hpp>
#include <pdevs/Dynamics.hpp>

namespace paradevs { namespace pdevs {

class Simulator : public Model
{
public :
    Simulator(Dynamics* dynamics);
    virtual ~Simulator();

    virtual common::Time i_message(common::Time /* t */);
    virtual common::Time s_message(common::Time /* t */);
    virtual void observation(std::ostream& file) const;

    virtual Dynamics* get_dynamics() const
    { return _dynamics; }

    virtual bool is_atomic() const
    { return true;}

    virtual void post_message(common::Time /* t */,
                              const common::Message& /* message */);

private :
    Dynamics* _dynamics;
};

} } // namespace paradevs pdevs

#endif
