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

Coordinator::Coordinator(const std::string& name) : Model(name)
{ }

Coordinator::~Coordinator()
{
    for (unsigned int i = 0; i < _child_list.size(); i++)
    { delete _child_list[i]; }
}

common::Time Coordinator::i_message(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::I_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn;
    common::Trace::trace().flush();

    assert(_child_list.size() > 0);

    for (unsigned int i = 0; i < _child_list.size(); i++) {
        Model* model = _child_list[i];

        _event_table.init(model->i_message(_tn), model);
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
common::Time Coordinator::s_message(common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; scheduler = " << _event_table.to_string();
    common::Trace::trace().flush();

    assert(t == _tn);

    Models IMM = _event_table.get_current_models(t);

    for (Models::const_iterator it = _child_list.begin();
         it != _child_list.end(); ++it) {
        Model* model = dynamic_cast < Model* >(*it);

        if (model->is_atomic() and
            dynamic_cast < Simulator* >(model)->message_number() > 0) {
            Models::const_iterator itm = std::find(IMM.begin(), IMM.end(),
                                                   model);
            if (itm == IMM.end()) {
                IMM.push_back(model);
            }
        }
    }

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": IMM = " << IMM.to_string();
    common::Trace::trace().flush();

    for (Models::const_iterator it = IMM.begin(); it != IMM.end(); ++it) {
        common::Time tn = (*it)->s_message(_tn);

        _event_table.put(tn, *it);
    }

    _tl = t;

    bool found = false;

    for (Models::const_iterator it = _child_list.begin();
         not found and it != _child_list.end(); ++it) {
        Model* model = dynamic_cast < Model* >(*it);

        if (model->is_atomic() and
            dynamic_cast < Simulator* >(model)->message_number() > 0) {
            found = true;
        }
    }
    if (not found) {
        _tn = _event_table.get_current_time();
    }

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::S_MESSAGE)
                           << ": AFTER => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; scheduler = " << _event_table.to_string();
    common::Trace::trace().flush();

    return _tn;
}

void Coordinator::post_message(common::Time t, const common::Message& message)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": BEFORE => " << message.to_string();
    common::Trace::trace().flush();

    std::pair < common::Links::iterator, common::Links::iterator > result =
        _link_list.equal_range(common::Node(message.get_port_name(), this));

    for (common::Links::iterator it_r = result.first;
         it_r != result.second; ++it_r) {
        Model* model = dynamic_cast < Model* >((*it_r).second.get_model());

        model->post_message(t, common::Message(it_r->second.get_port_name(),
                                               model, message.get_content()));
    }

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::POST_MESSAGE)
                           << ": AFTER => " << message.to_string();
    common::Trace::trace().flush();

}

common::Time Coordinator::y_message(common::Messages messages, common::Time t)
{

    common::Trace::trace() << common::TraceElement(get_name(), t,
                                                   common::Y_MESSAGE)
                           << ": BEFORE => "
                           << "tl = " << _tl << " ; tn = " << _tn
                           << " ; messages = " << messages.to_string();
    common::Trace::trace().flush();

    if (not messages.empty()) {
        while (not messages.empty()) {
            common::Message ymsg = messages.back();

            messages.pop_back();

            std::pair < common::Links::iterator ,
                        common::Links::iterator > result_model =
                _link_list.equal_range(common::Node(ymsg.get_port_name(),
                                                    ymsg.get_model()));

            for (common::Links::iterator it = result_model.first;
                 it != result_model.second; ++it) {
                // event on output port of coupled model
                if (it->second.get_model() == this) {
                    common::Messages ymessages;

                    ymessages.push_back(
                        common::Message(it->second.get_port_name(),
                                        it->second.get_model(),
                                        ymsg.get_content()));
                    dynamic_cast < Coordinator* >(get_parent())->y_message(
                        ymessages, t);
                } else { // event on input port of internal model
                    Model* model = dynamic_cast < Model* >(
                        it->second.get_model());
                    common::Message message(it->second.get_port_name(),
                                            model, ymsg.get_content());

                    model->post_message(t, message);
                }
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
