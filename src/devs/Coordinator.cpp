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

#include <devs/Coordinator.hpp>

#include <cassert>

namespace paradevs {

Coordinator::Coordinator(const std::string& name) : Model(name)
{ }

Coordinator::~Coordinator()
{
    for (unsigned int i = 0; i < _child_list.size(); i++)
    { delete _child_list[i]; }
}

Time Coordinator::i_message(Time t)
{

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - i_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    assert(_child_list.size() > 0);

    for (unsigned int i = 0; i < _child_list.size(); i++) {
        Model* model = _child_list[i];

        _event_table.init(model->i_message(_tn), model);
    }
    _tl = t;
    _tn = _event_table.get_current_time();

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - i_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    return _tn;
}

Time Coordinator::s_message(Time t)
{

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - s_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;
    std::cout << "[" << get_name() << "]: " << _event_table.to_string()
              << std::endl;

    assert(t == _tn);

    Model* current = _event_table.get_current_model();
    Time tn = current->s_message(_tn);

    _event_table.put(tn, current);

    _tl = t;
    _tn = _event_table.get_current_time();

    std::cout << "[" << get_name() << "] at " << t << ": AFTER - s_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;
    std::cout << "[" << get_name() << "]: " << _event_table.to_string()
              << std::endl;
    std::cout << "**************" << std::endl;

    return _tn;
}

Time Coordinator::x_message(const Message& xmsg, Time t)
{

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - x_message on "
              << xmsg.get_port_name() << " => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;
    std::cout << "[" << get_name() << "] " << _link_list.to_string()
              << std::endl;

    assert(tl <= t and t <= tn);

    std::pair < Links::iterator, Links::iterator > result =
        _link_list.equal_range(Node(xmsg.get_port_name(), this));

    for (Links::iterator it_r = result.first; it_r != result.second; ++it_r) {

        std::cout << "[" << get_name() << "] => "
                  << it_r->second.get_port_name()
                  << " / " << it_r->second.get_model()->get_name() << std::endl;

        _tn = (*it_r).second.get_model()->x_message(
            Message(it_r->second.get_port_name(), it_r->second.get_model(),
                    xmsg.get_content()), t);
        _event_table.put(_tn, it_r->second.get_model());
    }

    _tl = t;
    _tn = _event_table.get_current_time();

    std::cout << "[" << get_name() << "] at " << t << ": AFTER - x_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

    return _tn;
}

Time Coordinator::y_message(Messages messages, Time t)
{

    std::cout << "[" << get_name() << "] at " << t << ": BEFORE - y_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;
    std::cout << "[" << get_name() << "] at " << t << ": "
              << messages.to_string() << std::endl;

    if (not messages.empty()) {
        bool internal = false;

        while (not messages.empty()) {
            Message ymsg = messages.back();

            messages.pop_back();

            std::pair <Links::iterator , Links::iterator > result_model =
                _link_list.equal_range(Node(ymsg.get_port_name(), ymsg.get_model()));

            assert(result_model.first != result_model.second);

            for (Links::iterator it = result_model.first;
                 it != result_model.second; ++it) {
                // event on output port of coupled model
                if (it->second.get_model() == this) {
                    Messages ymessages;

                    ymessages.push_back(Message(it->second.get_port_name(),
                                                it->second.get_model(),
                                                ymsg.get_content()));
                    dynamic_cast < Coordinator* >(get_parent())->y_message(ymessages,
                                                                           t);
                } else { // event on input port of internal model
                    Message message(it->second.get_port_name(),
                                    it->second.get_model(),
                                    ymsg.get_content());
                    Time tn = it->second.get_model()->x_message(message, t);

                    _event_table.put(tn, it->second.get_model());
                    internal = true;
                }
            }
        }
        if (internal) {
            _tl = t;
            _tn = _event_table.get_current_time();
        }
    }

    std::cout << "[" << get_name() << "] at " << t << ": AFTER - y_message => "
              << "tl = " << _tl << " ; tn = " << _tn << std::endl;

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

void Coordinator::add_link(const Node& source, const Node& destination)
{ _link_list.insert(std::pair < Node, Node >(source, destination)); }

} // namespace paradevs
