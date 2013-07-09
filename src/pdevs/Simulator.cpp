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

#include <common/Trace.hpp>

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

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::I_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    _tl = t;
    _tn = _tl + _dynamics->start(t);

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::I_MESSAGE)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

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

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    if(t == _tn) {
        common::Messages msgs = _dynamics->lambda(t);

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
            _dynamics->dconf(t, t - _tl, _x_messages);
        }
    } else {
        _dynamics->dext(t, t - _tl, _x_messages);
    }
    _tn = t + _dynamics->ta(t);
    _tl = t;
    clear_messages();

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

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

void Simulator::post_message(common::Time t, const common::Message& message)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": BEFORE => " << message.to_string();
    common::Trace::trace().flush();

    _x_messages.push_back(message);

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": AFTER => " << message.to_string();
    common::Trace::trace().flush();

}

} } // namespace paradevs pdevs
