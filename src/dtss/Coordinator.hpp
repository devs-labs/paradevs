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
        for (unsigned int i = 0; i < _child_list.size(); i++)
        { delete _child_list[i]; }
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
            std::pair < common::Links::iterator ,
                        common::Links::iterator > result_model =
                _link_list.equal_range(common::Node(ymsg.get_port_name(),
                                                    ymsg.get_model()));

            for (common::Links::iterator it = result_model.first;
                 it != result_model.second; ++it) {
                // event on output port of coupled model
                if (it->second.get_model() == this) {
                    common::Bag ymessages;

                    ymessages.push_back(
                        common::ExternalEvent(it->second.get_port_name(),
                                              it->second.get_model(),
                                              ymsg.get_content()));
                    dynamic_cast < Coordinator* >(get_parent())->dispatch_events(
                        ymessages, t);
                } else { // event on input port of internal model
                    Model* model = dynamic_cast < Model* >(
                        it->second.get_model());
                    common::ExternalEvent message(it->second.get_port_name(),
                                                  model, ymsg.get_content());

                    model->post_message(t, message);
                }
            }
        }
        return _tn;
    }

    void observation(std::ostream& file) const
    {
        for (unsigned i = 0; i < _child_list.size(); i++) {
            _child_list[i]->observation(file);
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

    void post_message(common::Time t,
                      const common::ExternalEvent& event)
    {
        if (t == _tn) {
            std::pair < common::Links::iterator, common::Links::iterator > result =
                _link_list.equal_range(common::Node(event.get_port_name(), this));

            for (common::Links::iterator it_r = result.first;
                 it_r != result.second; ++it_r) {
                Model* model = dynamic_cast < Model* >((*it_r).second.get_model());

                model->post_message(t,
                                    common::ExternalEvent(it_r->second.get_port_name(),
                                                          model, event.get_content()));
            }
        } else {
            _policy(t, event, _tl, _tn);
        }
    }

    common::Time transition(common::Time t)
    {
        if (t == _tn) {
            if (not _policy.bag().empty()) {
                for (common::Bag::const_iterator it = _policy.bag().begin();
                     it != _policy.bag().end(); ++it) {
                    post_message(t, *it);
                }
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

    void add_link(const common::Node& source,
                  const common::Node& destination)
    {
        _link_list.insert(std::pair < common::Node, common::Node >(source,
                                                                   destination));
    }

private:
    common::Links  _link_list;
    common::Models _child_list;
    common::Time   _time_step;
    Policy         _policy;
};

} } // namespace paradevs dtss

#endif
