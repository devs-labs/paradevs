/**
 * @file Message.hpp
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

#ifndef COMMON_MESSAGE
#define COMMON_MESSAGE 1

#include <common/Model.hpp>

#include <string>
#include <vector>

namespace paradevs { namespace common {

class Model;

class Message
{
public:
    Message(const std::string& port_name, double content);
    Message(const std::string& port_name, Model* model, double content);
    Message();
    virtual ~Message();

    double get_content() const;
    Model* get_model() const;
    const std::string& get_port_name() const;

    void set_content(double content);
    void set_model(Model* model);

    std::string to_string() const;

private :
    std::string _port_name;
    Model*      _model;
    double      _content;
};

class Messages : public std::vector < Message >
{
public:
    Messages()
    { }
    virtual ~Messages()
    { }

    std::string to_string() const;
};

} } // namespace paradevs common

#endif
