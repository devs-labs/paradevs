/**
 * @file Coordinator.cpp
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

#include <dtss/Coordinator.hpp>
#include <dtss/Simulator.hpp>

#include <algorithm>
#include <cassert>

namespace paradevs { namespace dtss {

Coordinator::Coordinator(const std::string& name, common::Time time_step) :
    common::Coordinator(name), _time_step(time_step)
{ }

Coordinator::~Coordinator()
{
    for (unsigned int i = 0; i < _child_list.size(); i++)
    { delete _child_list[i]; }
}

common::Time Coordinator::start(common::Time t)
{
    assert(_child_list.size() > 0);

    for (auto & child : _child_list) {
        child->start(_tn);
    }
    _tn = t;
    return _tn;
}

common::Time Coordinator::dispatch_events(common::Bag bag, common::Time t)
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

void Coordinator::observation(std::ostream& file) const
{
    for (unsigned i = 0; i < _child_list.size(); i++) {
        _child_list[i]->observation(file);
    }
}

void Coordinator::output(common::Time t)
{
    assert(t == _tn);

    for (auto & model : _child_list) {
        model->output(t);
    }
}

void Coordinator::post_message(common::Time t,
                               const common::ExternalEvent& message)
{
    std::pair < common::Links::iterator, common::Links::iterator > result =
        _link_list.equal_range(common::Node(message.get_port_name(), this));

    for (common::Links::iterator it_r = result.first;
         it_r != result.second; ++it_r) {
        Model* model = dynamic_cast < Model* >((*it_r).second.get_model());

        model->post_message(t,
                            common::ExternalEvent(it_r->second.get_port_name(),
                                                  model,
                                                  message.get_content()));
    }
}

common::Time Coordinator::transition(common::Time t)
{
    assert(t >= _tl and t <= _tn);

    for (auto & model : _child_list) {
        model->transition(t);
    }
    _tn = t + _time_step;
    return _tn;
}

void Coordinator::add_child(Model* child)
{
    _child_list.push_back(child);
    child->set_parent(this);
}

void Coordinator::add_link(const common::Node& source,
                           const common::Node& destination)
{ _link_list.insert(std::pair < common::Node, common::Node >(source,
                                                             destination)); }

} } // namespace paradevs dtss
