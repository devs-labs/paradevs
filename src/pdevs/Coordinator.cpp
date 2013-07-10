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

#include <pdevs/Coordinator.hpp>
#include <pdevs/Simulator.hpp>

#include <algorithm>
#include <cassert>

namespace paradevs { namespace pdevs {

Coordinator::Coordinator(const std::string& name) : common::Coordinator(name)
{ }

Coordinator::~Coordinator()
{
    for (unsigned int i = 0; i < _child_list.size(); i++)
    { delete _child_list[i]; }
}

common::Time Coordinator::start(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::I_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    assert(_child_list.size() > 0);

    for (auto & child : _child_list) {
        _event_table.init(child->start(_tn), child);
    }
    _tl = t;
    _tn = _event_table.get_current_time();

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::I_MESSAGE)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    return _tn;
}

/**************************************************
 * when *-message(t)
 *   calculate IMM (models with tn = t in scheduler
 *   calculate INF from IMM
 *   for each e in IMM U INF
 *     calculate influencer
 *   ...
 *  send done to parent
 **************************************************/
void Coordinator::output(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::OUTPUT)
                           << ": BEFORE";
    common::Trace::trace().flush();

    assert(t == _tn);

    common::Models IMM = _event_table.get_current_models(t);

    for (auto & model : IMM) {
        model->output(t);
    }

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::OUTPUT)
                           << ": AFTER";
    common::Trace::trace().flush();

}

/*******************************************************************
 * when x-message(t)
 *   receivers = { r | r in children, N in Ir, Z(N,r)(x) isn't empty
 *   for each r in receivers
 *     send x-message(Z(N,r)(x), t) with input value Z(N,r)(x) to r
 *   for each r in IMM and not in receivers
 *     send x-message(empty, t) to r
 *   sort event list acocrding to tn
 *   tl = t
 *   tn = min(tn_d | d in D)
 *******************************************************************/
common::Time Coordinator::transition(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; scheduler = " << _event_table.to_string();
    common::Trace::trace().flush();

    assert(t >= _tl and t <= _tn);

    common::Models receivers = _event_table.get_current_models(t);

    for (common::Models::const_iterator it = _child_list.begin();
         it != _child_list.end(); ++it) {
        Model* model = dynamic_cast < Model* >(*it);

        if (model->event_number() > 0) {
            common::Models::const_iterator itm = std::find(receivers.begin(),
                                                           receivers.end(),
                                                           model);
            if (itm == receivers.end()) {
                receivers.push_back(model);
            }
        }
    }

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": receivers = " << receivers.to_string();
    common::Trace::trace().flush();

    for (common::Models::const_iterator it = receivers.begin();
         it != receivers.end(); ++it) {
        common::Time tn = (*it)->transition(t);

        _event_table.put(tn, *it);
    }

    for (common::Models::const_iterator it = _child_list.begin();
         it != _child_list.end(); ++it) {
        Model* model = dynamic_cast < Model* >(*it);

        if (model->event_number() > 0) {
            _event_table.put(t, model);
        }
    }

    _tl = t;
    _tn = _event_table.get_current_time();
    clear_bag();

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; scheduler = " << _event_table.to_string();
    common::Trace::trace().flush();

    return _tn;
}

void Coordinator::post_message(common::Time t,
                               const common::ExternalEvent& message)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": BEFORE => " << message.to_string();
    common::Trace::trace().flush();

    add_event(message);

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
    for (common::Models::const_iterator it = _child_list.begin();
         it != _child_list.end(); ++it) {
        Model* model = dynamic_cast < Model* >(*it);

        if (model->event_number() > 0) {
            _event_table.put(t, model);
        }
    }
    _tn = _event_table.get_current_time();

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": AFTER => " << message.to_string();
    common::Trace::trace().flush();

}

/*******************************************************************
 * when y-message(y_d, t) with output y_d from d
 *******************************************************************/
common::Time Coordinator::dispatch_events(common::Bag bag, common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::Y_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; bag = " << bag.to_string();
    common::Trace::trace().flush();

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

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::Y_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    return _tn;
}

void Coordinator::observation(std::ostream& file) const
{
    for (unsigned i = 0; i < _child_list.size(); i++) {
        _child_list[i]->observation(file);
    }
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

} } // namespace paradevs pdevs
