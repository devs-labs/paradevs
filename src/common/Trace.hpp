/**
 * @file Trace.hpp
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

#ifndef COMMON_TRACE
#define COMMON_TRACE 1

#include <common/Time.hpp>

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace paradevs { namespace common {

enum TraceType { NONE = 0, I_MESSAGE, POST_EVENT, S_MESSAGE, Y_MESSAGE,
                 DELTA_INT, DELTA_EXT, DELTA_CONF, TA, LAMBDA, START, OUTPUT };

class TraceElement
{
public:
    TraceElement() : _time(0), _type(NONE)
    { }
    TraceElement(const std::string& model_name, Time time, TraceType type) :
        _model_name(model_name), _time(time), _type(type)
    { }
    virtual ~TraceElement()
    { }

    const std::string& get_comment() const
    { return _comment; }

    const std::string& get_model_name() const
    { return _model_name; }

    Time get_time() const
    { return _time; }

    TraceType get_type() const
    { return _type; }

    void set_comment(const std::string& comment)
    { _comment = comment; }

private:
    std::string _model_name;
    Time        _time;
    TraceType   _type;
    std::string _comment;
};

class TraceElements : public std::vector < TraceElement >
{
public:
    TraceElements()
    { }
    virtual ~TraceElements()
    { }

    TraceElements filter_model_name(
        const std::string& model_name) const
    {
        TraceElements result;

        std::copy_if(begin(), end(), std::back_inserter(result),
                     [model_name](TraceElement const & x)
                     { return x.get_model_name() == model_name; });
        return result;
    }

    TraceElements filter_time(Time time) const
    {
        TraceElements result;

        std::copy_if(begin(), end(), std::back_inserter(result),
                     [time](TraceElement const & x)
                     { return x.get_time() == time; });
        return result;
    }

    TraceElements filter_type(TraceType type) const
    {
        TraceElements result;

        std::copy_if(begin(), end(), std::back_inserter(result),
                     [type](TraceElement const & x)
                     { return x.get_type() == type; });
        return result;
    }

    std::string to_string() const;
};

class Trace
{
public:
    static Trace& trace();

    void clear()
    { _trace.clear(); }

    const TraceElements& elements() const
    { return _trace; }

    void flush();

    void set_element(const TraceElement& element)
    { _element = element; }

    std::ostringstream& sstream();

private:
    Trace()
    { _sstream = 0; }
    virtual ~Trace()
    {
        delete _instance;
        if (_sstream) {
            delete _sstream;
        }
    }

    static Trace* _instance;

    TraceElements       _trace;
    TraceElement        _element;
    std::ostringstream* _sstream;
};

} } // namespace paradevs common

paradevs::common::Trace& operator<<(paradevs::common::Trace& trace,
                                    const paradevs::common::TraceElement& e);
paradevs::common::Trace& operator<<(paradevs::common::Trace& trace,
                                    const std::string& str);
paradevs::common::Trace& operator<<(paradevs::common::Trace& trace,
                                    paradevs::common::Time t);

#endif
