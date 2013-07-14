/**
 * @file Links.hpp
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

#ifndef COMMON_LINKS
#define COMMON_LINKS 1

#include <common/Node.hpp>

#include <map>
#include <sstream>

namespace paradevs { namespace common {

template < class Time >
class Node;

template < class Time >
class Links : public std::multimap < Node < Time >, Node < Time > >
{
public:

    typedef std::pair < typename Links < Time >::const_iterator,
                        typename Links < Time >::const_iterator > Result;

    Links()
    { }
    virtual ~Links()
    { }

    void add(Model < Time >* out_model, const std::string& out_port_name,
             Model < Time >* in_model, const std::string& in_port_name)
    {
        std::multimap < Node < Time >, Node < Time > >::insert(
            std::pair < Node < Time >, Node <Time > >(
                Node < Time >(out_model, out_port_name),
                Node < Time >(in_model, in_port_name)));
    }

    Links::Result find(Model < Time >* out_model,
                       const std::string& out_port_name) const
    {
        return std::multimap < Node < Time >, Node < Time > >::equal_range(
            common::Node < Time >(out_model, out_port_name));
    }

    std::string to_string() const
    {
        std::stringstream ss;

        ss << "Graph = { ";
        for (typename Node < Time >::const_iterator it = Node < Time >::begin();
             it != Node < Time >::end(); ++it) {
            ss << "(" << it->first.get_model()->get_name() << ":"
               << it->first.get_port_name()
               << " -> "
               << it->second.get_model()->get_name() << ":"
               << it->second.get_port_name()
               << ") ";
        }
        ss << "}";
        return ss.str();
    }
};

} } // namespace paradevs common

#endif
