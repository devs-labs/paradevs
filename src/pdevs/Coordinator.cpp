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
    for (auto & child : _child_list) {
        delete child;
    }
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
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; scheduler = " << _event_table.to_string();
    common::Trace::trace().flush();

    assert(t == _tn);

    common::Models IMM = _event_table.get_current_models(t);

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::OUTPUT)
                           << ": IMM = " << IMM.to_string();
    common::Trace::trace().flush();

    for (auto & model : IMM) {
        model->output(t);
    }

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::OUTPUT)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; scheduler = " << _event_table.to_string();
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

    add_models_with_inputs(receivers);

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": receivers = " << receivers.to_string();
    common::Trace::trace().flush();

    for (auto & model : receivers) {
        _event_table.put(model->transition(t), model);
    }
    update_event_table(t);
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

void Coordinator::post_event(common::Time t,
                             const common::ExternalEvent& event)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_EVENT)
                           << ": BEFORE => " << event.to_string();
    common::Trace::trace().flush();

    add_event(event);

    common::Links::Result result =
        _link_list.find(this, event.get_port_name());

    for (common::Links::iterator it_r = result.first;
         it_r != result.second; ++it_r) {
        it_r->second.get_model()->post_event(
            t, common::ExternalEvent(it_r->second, event.get_content()));
    }
    update_event_table(t);
    _tn = _event_table.get_current_time();

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_EVENT)
                           << ": AFTER => " << event.to_string();
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
            common::Links::Result result_model =
                _link_list.find(ymsg.get_model(), ymsg.get_port_name());

        for (common::Links::iterator it = result_model.first;
             it != result_model.second; ++it) {
            // event on output port of coupled model
            if (it->second.get_model() == this) {
                common::Bag ymessages;

                ymessages.push_back(
                    common::ExternalEvent(it->second, ymsg.get_content()));
                dynamic_cast < Coordinator* >(get_parent())->dispatch_events(
                    ymessages, t);
            } else { // event on input port of internal model
                    it->second.get_model()->post_event(
                        t, common::ExternalEvent(it->second,
                                                 ymsg.get_content()));
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
    for (auto & child : _child_list) {
        child->observation(file);
    }
}

void Coordinator::add_child(Model* child)
{
    _child_list.push_back(child);
    child->set_parent(this);
}

void Coordinator::add_link(Model* out_model, const std::string& out_port_name,
                           Model* in_model, const std::string& in_port_name)
{
    _link_list.add(out_model, out_port_name, in_model, in_port_name);
}

void Coordinator::add_models_with_inputs(common::Models& receivers)
{
    for (auto & model : _child_list) {
        if (model->event_number() > 0) {
            if (std::find(receivers.begin(), receivers.end(), model) ==
                receivers.end()) {
                receivers.push_back(model);
            }
        }
    }
}

void Coordinator::update_event_table(common::Time t)
{
    for (auto & model : _child_list) {
        if (model->event_number() > 0) {
            _event_table.put(t, model);
        }
    }
}

} } // namespace paradevs pdevs
