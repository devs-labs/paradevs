/**
 * @file Coordinator.hpp
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

#ifndef DTSS_COORDINATOR
#define DTSS_COORDINATOR 1

#include <common/Coordinator.hpp>

#include <cassert>
#include <iostream>

namespace paradevs { namespace dtss {

class Parameters
{
public:
    Parameters(paradevs::common::Time time_step) : _time_step(time_step)
    { }

    paradevs::common::Time _time_step;
};

template < class Policy, class GraphManager >
class Coordinator : public common::Coordinator
{
public:
    typedef Parameters parameters_type;

    Coordinator(const std::string& name, const Parameters& parameters) :
        common::Coordinator(name), _graph_manager(this),
        _time_step(parameters._time_step)
    { }

    virtual ~Coordinator()
    { }

    common::Time start(common::Time t)
    {
        assert(_graph_manager.children().size() > 0);

        for (auto & child : _graph_manager.children()) {
            child->start(_tn);
        }
        _tl = t;
        _tn = t;
        return _tn;
    }

    common::Time dispatch_events(common::Bag bag, common::Time t)
    {
        _graph_manager.dispatch_events(bag, t);
        return _tn;
    }

    void observation(std::ostream& file) const
    {
        for (auto & child : _graph_manager.children()) {
            child->observation(file);
        }
    }

    void output(common::Time t)
    {
        if (t == _tn) {
            for (auto & model : _graph_manager.children()) {
                model->output(t);
            }
        }
    }

    void post_event(common::Time t,
                    const common::ExternalEvent& event)
    {
        if (t == _tn) {
            _graph_manager.post_event(t, event);
        } else {
            _policy(t, event, _tl, _tn);
        }
    }

    common::Time transition(common::Time t)
    {
        if (t == _tn) {
            for (auto & event : _policy.bag()) {
                post_event(t, event);
            }
            for (auto & model : _graph_manager.children()) {
                model->transition(t);
            }
            _tl = t;
            _tn = t + _time_step;
        }
        clear_bag();
        return _tn;
    }

private:
    GraphManager   _graph_manager;
    common::Time   _time_step;
    Policy         _policy;
};

} } // namespace paradevs dtss

#endif
