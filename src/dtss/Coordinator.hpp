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

#include <common/Bag.hpp>
#include <common/Coordinator.hpp>
#include <common/ExternalEvent.hpp>
#include <common/Links.hpp>
#include <common/Node.hpp>
#include <common/Trace.hpp>

#include <dtss/Simulator.hpp>

#include <algorithm>
#include <cassert>
#include <iostream>

namespace paradevs { namespace dtss {

template < class Policy >
class Coordinator : public common::Coordinator
{
public:
    Coordinator(const std::string& name, common::Time time_step) :
        common::Coordinator(name), _time_step(time_step)
    { }

    virtual ~Coordinator()
    {
        for (auto & child : _child_list) {
            delete child;
        }
    }

// DEVS methods
    common::Time start(common::Time t)
    {
        assert(_child_list.size() > 0);

        for (auto & child : _child_list) {
            child->start(_tn);
        }
        _tl = t;
        _tn = t;
        return _tn;
    }

    common::Time dispatch_events(common::Bag bag, common::Time t)
    {
        for (auto & ymsg : bag) {
            common::Links::Result result_model =
                _link_list.find(ymsg.get_model(), ymsg.get_port_name());

            for (common::Links::iterator it = result_model.first;
                 it != result_model.second; ++it) {
                // event on output port of coupled model
                if (it->second.get_model() == this) {
                    common::Bag ymessages;

                    ymessages.push_back(
                        common::ExternalEvent(it->second, ymsg.get_content()));
                    dynamic_cast < common::Coordinator* >(get_parent())
                        ->dispatch_events(ymessages, t);
                } else { // event on input port of internal model
                    it->second.get_model()->post_event(
                        t, common::ExternalEvent(it->second,
                                                 ymsg.get_content()));
                }
            }
        }
        return _tn;
    }

    void observation(std::ostream& file) const
    {
        for (auto & child : _child_list) {
            child->observation(file);
        }
    }

    void output(common::Time t)
    {
        if (t == _tn) {
            for (auto & model : _child_list) {
                model->output(t);
            }
        }
    }

    void post_event(common::Time t,
                    const common::ExternalEvent& event)
    {
        if (t == _tn) {
            common::Links::Result result =
                _link_list.find(this, event.get_port_name());

            for (common::Links::iterator it_r = result.first;
                 it_r != result.second; ++it_r) {
                it_r->second.get_model()->post_event(
                    t, common::ExternalEvent(it_r->second,
                                             event.get_content()));
            }
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
            for (auto & model : _child_list) {
                model->transition(t);
            }
            _tl = t;
            _tn = t + _time_step;
        }
        clear_bag();
        return _tn;
    }

// graph methods
    void add_child(Model* child)
    {
        _child_list.push_back(child);
        child->set_parent(this);
    }

    void add_link(Model* out_model, const std::string& out_port_name,
                  Model* in_model, const std::string& in_port_name)
    {
        _link_list.add(out_model, out_port_name, in_model, in_port_name);
    }

private:
    common::Links  _link_list;
    common::Models _child_list;
    common::Time   _time_step;
    Policy         _policy;
};

} } // namespace paradevs dtss

#endif
