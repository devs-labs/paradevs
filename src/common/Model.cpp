/**
 * @file Model.cpp
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

#include <common/Model.hpp>

#include <sstream>

namespace paradevs { namespace common {

Model::Model(const std::string& name) :
    _tl(0), _tn(0), _parent(0), _name(name), _inputs(0)
{ }

Model::~Model()
{
    if (_inputs) {
        delete _inputs;
    }
}

void Model::add_event(const common::ExternalEvent& message)
{
    if (_inputs == 0) {
        _inputs = new Bag;
    }
    _inputs->push_back(message);
}

const common::Bag& Model::get_bag()
{
    if (_inputs == 0) {
        _inputs = new Bag;
    }
    return *_inputs;
}

void Model::clear_bag()
{
    if (_inputs) {
        delete _inputs;
        _inputs = 0;
    }
}

unsigned int Model::event_number() const
{
    if (_inputs) {
        return _inputs->size();
    } else {
        return 0;
    }
}

std::string Models::to_string() const
{
    std::ostringstream ss;

    ss << "{ ";
    for (const_iterator it = begin(); it != end(); ++it) {
        ss << (*it)->get_name() << " ";
    }
    ss << "}";
    return ss.str();
}

} } // namespace paradevs common
