/**
 * @file Trace.hpp
 * @author The PARADEVS Development Team
 * See the AUTHORS or Authors.txt file
 */

/*
 * PARADEVS - the multimodeling and simulation environment
 * This file is a part of the PARADEVS environment
 *
 * Copyright (C) 2013-2015 ULCO http://www.univ-litoral.fr
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

#ifndef COMMON_UTILS_TRACE
#define COMMON_UTILS_TRACE 1

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace paradevs { namespace common {

enum TraceType { NONE = 0, I_MESSAGE, POST_EVENT, S_MESSAGE, Y_MESSAGE,
                 DELTA_INT, DELTA_EXT, DELTA_CONF, TA, LAMBDA, START, OUTPUT };

template < class Time >
class TraceElement
{
public:
    TraceElement() : _time(Time::null), _type(NONE)
    { }

    TraceElement(const std::string& model_name, typename Time::type time,
                 TraceType type) :
        _model_name(model_name), _time(time), _type(type)
    { }

    virtual ~TraceElement()
    { }

    const std::string& get_comment() const
    { return _comment; }

    const std::string& get_model_name() const
    { return _model_name; }

    typename Time::type get_time() const
    { return _time; }

    TraceType get_type() const
    { return _type; }

    void set_comment(const std::string& comment)
    { _comment = comment; }

private:
    std::string         _model_name;
    typename Time::type _time;
    TraceType           _type;
    std::string         _comment;
};

template < class Time >
class TraceElements : public std::vector < TraceElement < Time > >
{
public:
    TraceElements()
    { }
    virtual ~TraceElements()
    { }

    TraceElements filter_model_name(
        const std::string& model_name) const
    {
        TraceElements < Time > result;

        std::copy_if(TraceElements < Time >::begin(),
                     TraceElements < Time >::end(), std::back_inserter(result),
                     [model_name](TraceElement < Time > const & x)
                     { return x.get_model_name() == model_name; });
        return result;
    }

    TraceElements filter_time(typename Time::type time) const
    {
        TraceElements result;

        std::copy_if(TraceElements < Time >::begin(),
                     TraceElements < Time >::end(), std::back_inserter(result),
                     [time](TraceElement < Time > const & x)
                     { return x.get_time() == time; });
        return result;
    }

    TraceElements filter_type(TraceType type) const
    {
        TraceElements result;

        std::copy_if(TraceElements < Time >::begin(),
                     TraceElements < Time >::end(), std::back_inserter(result),
                     [type](TraceElement < Time > const & x)
                     { return x.get_type() == type; });
        return result;
    }

    std::string to_string() const
    {
        std::ostringstream ss;

        for (typename TraceElements < Time >::const_iterator it =
                 TraceElements < Time >::begin();
             it != TraceElements < Time >::end(); ++it) {
            ss << "TRACE: " << it->get_model_name() << " at "
               << it->get_time() << " <";
            switch (it->get_type())
            {
            case NONE: ss << "none"; break;
            case I_MESSAGE: ss << "i_message"; break;
            case POST_EVENT:  ss << "post_event"; break;
            case S_MESSAGE: ss << "s_message"; break;
            case Y_MESSAGE: ss << "y_message"; break;
            case DELTA_INT: ss << "delta_int"; break;
            case DELTA_EXT: ss << "delta_ext"; break;
            case DELTA_CONF:  ss << "delta_conf"; break;
            case TA: ss << "ta"; break;
            case LAMBDA: ss << "lambda"; break;
            case START: ss << "start"; break;
            case OUTPUT: ss << "output"; break;
            };
            ss << ">";
            if (not it->get_comment().empty()) {
                ss << " => " << it->get_comment();
            }
            ss << std::endl;
        }
        return ss.str();
    }
};

template < class Time >
class Trace
{
public:
    static Trace& trace()
    {
        if (_instance == 0) {
            _instance = new Trace();
        }
        return *_instance;
    }

    void clear()
    { _trace.clear(); }

    const TraceElements < Time >& elements() const
    { return _trace; }

    void flush()
    {
        if (_sstream) {
            _element.set_comment(_sstream->str());
            delete _sstream;
            _sstream = 0;
        }
        _trace.push_back(_element);
    }

    void set_element(const TraceElement < Time >& element)
    { _element = element; }

    std::ostringstream& sstream()
    {
        if (_sstream == 0) {
            _sstream = new std::ostringstream();
        }
        return *_sstream;
    }

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

    static Trace < Time >* _instance;

    TraceElements < Time > _trace;
    TraceElement < Time >  _element;
    std::ostringstream*    _sstream;
};

} } // namespace paradevs common

template < class Time >
paradevs::common::Trace < Time >& operator<<(
    paradevs::common::Trace < Time >& trace,
    const paradevs::common::TraceElement < Time >& e)
{
    trace.set_element(e);
    return trace;
}

template < class Time >
paradevs::common::Trace < Time >& operator<<(
    paradevs::common::Trace < Time >& trace,
    const std::string& str)
{
    trace.sstream() << str;
    return trace;
}

template < class Time >
paradevs::common::Trace < Time >& operator<<(
    paradevs::common::Trace < Time >& trace,
    typename Time::type t)
{
    trace.sstream() << t;
    return trace;
}

template < class Time >
paradevs::common::Trace < Time >*
paradevs::common::Trace < Time >::_instance = 0;

#endif
