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

#include <pdevs/Coordinator.hpp>
#include <pdevs/Simulator.hpp>

#include <cassert>
#include <stdexcept>

namespace paradevs { namespace pdevs {

Simulator::Simulator(Dynamics* dynamics) :
    Model(dynamics->get_name()), _dynamics(dynamics)
{ }

Simulator::~Simulator()
{ delete _dynamics; }

common::Time Simulator::i_message(common::Time t)
{
    _tl = t;
    _tn = _tl + _dynamics->start();
    return _tn;
}

/*************************************************
 * when *-message(t)
 *   if (t = tn) then
 *     y = lambda(s)
 *     send #-message(y,t) to parent
 *     if (???) then
 *       s = delta_int(s)
 *     else
 *       s = delta_conf(s,x)
 *  else
 *    s = delta_ext(s,t-tl,x)
 *  tn = t + ta(s)
 *  tl = t
 *  empty x
 *  send done to parent
 *************************************************/
common::Time Simulator::s_message(common::Time t)
{

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - s_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    if(t == _tn) {
        common::Messages msgs = _dynamics->lambda();

        if (not msgs.empty()) {
            for (common::Messages::iterator it = msgs.begin(); it != msgs.end();
                 ++it) {
                it->set_model(this);
            }
            dynamic_cast < Coordinator* >(get_parent())->y_message(msgs, t);
        }
        if (message_number() == 0) {
            _dynamics->dint(t);
        } else {
            _dynamics->dconf(t - _tl, _x_messages);
        }
    } else {
        _dynamics->dext(t - _tl, _x_messages);
    }
    _tn = t + _dynamics->ta();
    _tl = t;
    clear_messages();

    std::cout << "[" << get_name() << "] at " << t << ": AFTER - s_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    return _tn;
}

void Simulator::observation(std::ostream &file) const
{
    _dynamics->observation(file);
}

void Simulator::clear_messages()
{
    _x_messages.clear();
}

void Simulator::post_message(const common::Message& message)
{

    std::cout << "[" << get_name() << "]: [BEFORE] post_message => "
              << message.to_string() << std::endl;

    _x_messages.push_back(message);

    std::cout << "[" << get_name() << "]: [AFTER] post_message => "
              << _x_messages.to_string() << std::endl;

}

} } // namespace paradevs pdevs
