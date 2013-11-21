/**
 * @file ExternalEvent.hpp
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

#ifndef COMMON_EXTERNAL_EVENT
#define COMMON_EXTERNAL_EVENT 1

#include <paradevs/common/Model.hpp>
#include <paradevs/common/Node.hpp>

#include <sstream>
#include <string>
#include <vector>

namespace paradevs { namespace common {

template < class Time, class SchedulerHandle >
class Node;
template < class Time, class SchedulerHandle >
class Model;

template < class Time, class SchedulerHandle >
class ExternalEvent
{
public:
    ExternalEvent(const std::string& port_name, void* content) :
        _port_name(port_name), _model(0), _content(content)
    { }

    ExternalEvent(const Node < Time, SchedulerHandle >& node, void* content) :
        _port_name(node.get_port_name()),
        _model(node.get_model()),
        _content(content)
    { }

    ExternalEvent()
    { }

    virtual ~ExternalEvent()
    { }

    void* get_content() const
    { return _content; }

    const std::string& get_port_name() const
    { return _port_name; }

    void set_content(void* content)
    { _content = content; }

    Model < Time, SchedulerHandle >* get_model() const
    { return _model; }

    bool on_port(const std::string& port_name) const
    { return _port_name == port_name; }

    void set_model(Model < Time, SchedulerHandle >* model)
    { _model = model; }

    std::string to_string() const
    {
        std::ostringstream ss;

        ss << "( " << _port_name << " , " << (_model?_model->get_name():"<>")
           << " , " << *(double*)_content << ")";
        return ss.str();
    }

private :
    std::string                      _port_name;
    Model < Time, SchedulerHandle >* _model;
    void*                            _content;
};

} } // namespace paradevs common

#endif
