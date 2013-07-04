/**
 * @file Simulator.cpp
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

#include <devs/Coordinator.hpp>
#include <devs/Simulator.hpp>

#include <cassert>
#include <stdexcept>

namespace paradevs {

Simulator::Simulator(Dynamics* dynamics) :
    Model(dynamics->get_name()), _dynamics(dynamics)
{ }

Simulator::~Simulator()
{ delete _dynamics; }

Time Simulator::i_message(Time t)
{
    _tl = t;
    _tn = _tl + _dynamics->start();
    return _tn;
}

Time Simulator::s_message(Time t)
{

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - s_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    assert(t == _tn);

    Messages msgs = _dynamics->lambda();

    if (not msgs.empty()) {
        for (Messages::iterator it = msgs.begin(); it != msgs.end(); ++it) {
            it->set_model(this);
        }
        dynamic_cast < Coordinator* >(get_parent())->y_message(msgs, t);
    }

    _dynamics->dint(t);
    _tl = t;
    _tn = t + _dynamics->ta();

    std::cout << "[" << get_name() << "] at " << t << ": AFTER - s_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    return _tn;
}

Time Simulator::x_message(const Message& msg, Time t)
{

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - x_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    assert(_tl <= t and t <= _tn);

    Time e = t - _tl;

    _dynamics->dext(e, msg);
    _tl = t;
    _tn = _tl + _dynamics->ta();

    std::cout << "[" << get_name() << "] at " << t << ": AFTER - x_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    return _tn;
}

void Simulator::observation(std::ostream &file) const
{ _dynamics->observation(file); }

} // namespace paradevs
