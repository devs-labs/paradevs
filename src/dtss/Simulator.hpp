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

#ifndef DTSS_SIMULATOR
#define DTSS_SIMULATOR 1

#include <common/Coordinator.hpp>
#include <common/Simulator.hpp>
#include <common/Trace.hpp>

#include <cassert>

namespace paradevs { namespace dtss {

template < class Dynamics >
class Simulator : public common::Simulator
{
public :
    Simulator(const std::string& name, common::Time time_step) :
        common::Simulator(name), _dynamics(name), _time_step(time_step)
    { }

    ~Simulator()
    {  }

    common::Time start(common::Time t)
    {
        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::I_MESSAGE)
                               << ": BEFORE => "
                               << "tl = " << _tl << " ; tn = " << _tn;
        common::Trace::trace().flush();

        _dynamics.start(t);
        _tl = t;
        _tn = t;

        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::I_MESSAGE)
                               << ": AFTER => "
                               << "tl = " << _tl << " ; tn = " << _tn;
        common::Trace::trace().flush();

        return _tn;
    }

    void observation(std::ostream &file) const
    {
        _dynamics.observation(file);
    }

    void output(common::Time t)
    {
        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::OUTPUT)
                               << ": BEFORE";
        common::Trace::trace().flush();

        if(t == _tn) {
            common::Bag bag = _dynamics.lambda(t);

            if (not bag.empty()) {
                for (auto & event : bag) {
                    event.set_model(this);
                }
                dynamic_cast < common::Coordinator* >(get_parent())
                    ->dispatch_events(bag, t);
            }
        }

        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::OUTPUT)
                               << ": AFTER";
        common::Trace::trace().flush();

    }

    void post_event(common::Time t,
                    const common::ExternalEvent& event)
    {

        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::POST_EVENT)
                               << ": BEFORE => " << event.to_string();
        common::Trace::trace().flush();

        add_event(event);

        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::POST_EVENT)
                               << ": AFTER => " << event.to_string();
        common::Trace::trace().flush();

    }

    common::Time transition(common::Time t)
    {

        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::S_MESSAGE)
                               << ": BEFORE => "
                               << "tl = " << _tl << " ; tn = " << _tn;
        common::Trace::trace().flush();

        assert(t == _tn);

        _dynamics.transition(get_bag(), t);
        _tl = t;
        _tn = t + _time_step;
        clear_bag();

        common::Trace::trace() << common::TraceElement(get_name(), t,
                                                       common::S_MESSAGE)
                               << ": AFTER => "
                               << "tl = " << _tl << " ; tn = " << _tn;
        common::Trace::trace().flush();

        return _tn;
    }

private :
    Dynamics     _dynamics;
    common::Time _time_step;
};

} } // namespace paradevs dtss

#endif
