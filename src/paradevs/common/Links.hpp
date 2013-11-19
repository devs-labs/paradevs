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

#include <paradevs/common/Node.hpp>
#include <paradevs/common/utils/String.hpp>

#include <map>
#include <sstream>

namespace paradevs { namespace common {

template < class Time, class SchedulerHandle >
class Node;

template < class Time, class SchedulerHandle >
class Links : public std::multimap < Node < Time, SchedulerHandle >,
                                     Node < Time, SchedulerHandle > >
{
public:

    typedef std::pair <
        typename Links < Time, SchedulerHandle >::const_iterator,
        typename Links < Time, SchedulerHandle >::const_iterator
    > Result;

    Links()
    { }
    virtual ~Links()
    { }

    void add(Model < Time, SchedulerHandle >* out_model,
             const std::string& out_port_name,
             Model < Time, SchedulerHandle >* in_model,
             const std::string& in_port_name)
    {
        std::multimap < Node < Time, SchedulerHandle >,
                        Node < Time, SchedulerHandle > >::insert(
                            std::pair < Node < Time, SchedulerHandle >,
                                        Node < Time, SchedulerHandle > >(
                                            Node < Time, SchedulerHandle >(
                                                out_model, out_port_name),
                                            Node < Time, SchedulerHandle >(
                                                in_model, in_port_name)));
    }

    bool exist(Model < Time, SchedulerHandle >* out_model,
               const std::string& out_port_name,
               Model < Time, SchedulerHandle >* in_model,
               const std::string& in_port_name) const
    {
        typename Links < Time, SchedulerHandle >::const_iterator it =
            std::multimap < Node < Time, SchedulerHandle >,
                            Node < Time, SchedulerHandle > >::find(
                                Node < Time, SchedulerHandle >(out_model,
                                                               out_port_name));
        bool found = false;

        while (not found and it != Links < Time, SchedulerHandle >::end()) {
            found = it->second == Node < Time, SchedulerHandle >(
                in_model, in_port_name);
            ++it;
        }
        return found;
    }

    Links::Result find(Model < Time, SchedulerHandle >* out_model,
                       const std::string& out_port_name) const
    {
        return std::multimap < Node < Time, SchedulerHandle >,
                               Node < Time, SchedulerHandle > >::equal_range(
                                   common::Node < Time, SchedulerHandle >(
                                       out_model, out_port_name));
    }

    std::string to_string(int level = 0) const
    {
        std::stringstream ss;

        ss << common::spaces(level * 2) << "Links:" << std::endl;
        for (typename Links < Time, SchedulerHandle >::const_iterator it =
                 Links < Time, SchedulerHandle >::begin();
             it != Links < Time, SchedulerHandle >::end(); ++it) {
            ss << common::spaces((level + 1) * 2)
               << it->first.get_model()->get_name() << "::"
               << it->first.get_port_name()
               << " -> "
               << it->second.get_model()->get_name() << "::"
               << it->second.get_port_name() << std::endl;
        }
        return ss.str();
    }
};

} } // namespace paradevs common

#endif
