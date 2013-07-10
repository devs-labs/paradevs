/**
 * @file ExternalEvent.cpp
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

#include <common/ExternalEvent.hpp>
#include <common/Node.hpp>

#include <sstream>

namespace paradevs { namespace common {

ExternalEvent::ExternalEvent(const std::string& port_name, double content) :
    _port_name(port_name), _model(0), _content(content)
{ }

ExternalEvent::ExternalEvent(const std::string& port_name, Model* model,
                             double content) :
    _port_name(port_name), _model(model), _content(content)
{ }

ExternalEvent::ExternalEvent()
{ }

ExternalEvent::~ExternalEvent()
{ }

const std::string& ExternalEvent::get_port_name() const
{ return _port_name; }

double ExternalEvent::get_content() const
{ return _content; }

void ExternalEvent::set_content(double content)
{ _content = content; }

Model* ExternalEvent::get_model() const
{ return _model; }

void ExternalEvent::set_model(Model* model)
{ _model = model; }

std::string ExternalEvent::to_string() const
{
    std::ostringstream ss;

    ss << "( " << _port_name << " , " << (_model?_model->get_name():"<>")
       << ")";
    return ss.str();
}

} } // namespace paradevs common
