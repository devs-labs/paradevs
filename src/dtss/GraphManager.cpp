/**
 * @file GraphManager.cpp
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

#include <dtss/GraphManager.hpp>

namespace paradevs { namespace dtss {

GraphManager::GraphManager(common::Coordinator* coordinator) :
    _coordinator(coordinator)
{ }

GraphManager::~GraphManager()
{
    for (auto & child : _child_list) {
        delete child;
    }
}

void GraphManager::add_child(common::Model* child)
{
    _child_list.push_back(child);
    child->set_parent(_coordinator);
}

void GraphManager::add_link(common::Model* out_model,
                            const std::string& out_port_name,
                            common::Model* in_model,
                            const std::string& in_port_name)
{
    _link_list.add(out_model, out_port_name, in_model, in_port_name);
}

void GraphManager::dispatch_events(common::Bag bag, common::Time t)
{
    for (auto & ymsg : bag) {
        common::Links::Result result_model =
            _link_list.find(ymsg.get_model(),
                            ymsg.get_port_name());

        for (common::Links::const_iterator it = result_model.first;
             it != result_model.second; ++it) {
            // event on output port of coupled model
            if (it->second.get_model() == _coordinator) {
                common::Bag ymessages;

                ymessages.push_back(
                    common::ExternalEvent(it->second, ymsg.get_content()));
                dynamic_cast < common::Coordinator* >(
                    _coordinator->get_parent())->dispatch_events(ymessages, t);
            } else { // event on input port of internal model
                it->second.get_model()->post_event(
                    t, common::ExternalEvent(it->second,
                                             ymsg.get_content()));
            }
        }
    }
}

void GraphManager::post_event(common::Time t,
                              const common::ExternalEvent& event)
{
    common::Links::Result result =
        _link_list.find(_coordinator, event.get_port_name());

    for (common::Links::const_iterator it_r = result.first;
         it_r != result.second; ++it_r) {
        it_r->second.get_model()->post_event(
            t, common::ExternalEvent(it_r->second,
                                     event.get_content()));
    }
}

} } // namespace paradevs dtss
