/**
 * @file Message.cpp
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

#include <common/Message.hpp>
#include <common/Node.hpp>

#include <sstream>

namespace paradevs { namespace common {

Message::Message(const std::string& port_name, double content) :
    _port_name(port_name), _model(0), _content(content)
{ }

Message::Message(const std::string& port_name, Model* model, double content) :
    _port_name(port_name), _model(model), _content(content)
{ }

Message::Message()
{ }

Message::~Message()
{ }

const std::string& Message::get_port_name() const
{ return _port_name; }

double Message::get_content() const
{ return _content; }

void Message::set_content(double content)
{ _content = content; }

Model* Message::get_model() const
{ return _model; }

void Message::set_model(Model* model)
{ _model = model; }

std::string Message::to_string() const
{
    std::ostringstream ss;

    ss << "( " << _port_name << " , " << _model->get_name() << ")";
    return ss.str();
}

std::string Messages::to_string() const
{
    std::ostringstream ss;

    ss << "{ ";
    for (const_iterator it = begin(); it != end(); ++it) {
        ss << it->to_string() << " ";
    }
    ss << "}";
    return ss.str();
}

} } // namespace paradevs common
