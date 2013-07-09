/**
 * @file Trace.cpp
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

#include <common/Trace.hpp>

namespace paradevs { namespace common {

Trace* Trace::_instance = 0;

std::string TraceElements::to_string() const
{
    std::ostringstream ss;

    for (const_iterator it = begin(); it != end(); ++it) {
        ss << "TRACE: " << it->get_model_name() << " at "
           << it->get_time() << " <";
        switch (it->get_type())
        {
        case NONE: ss << "none"; break;
        case I_MESSAGE: ss << "i_message"; break;
        case POST_MESSAGE:  ss << "post_message"; break;
        case S_MESSAGE: ss << "s_message"; break;
        case Y_MESSAGE: ss << "y_message"; break;
        case DELTA_INT: ss << "delta_int"; break;
        case DELTA_EXT: ss << "delta_ext"; break;
        case DELTA_CONF:  ss << "delta_conf"; break;
        case TA: ss << "ta"; break;
        case LAMBDA: ss << "lambda"; break;
        case START: ss << "start"; break;
        };
        ss << ">";
        if (not it->get_comment().empty()) {
            ss << " => " << it->get_comment();
        }
        ss << std::endl;
    }
    return ss.str();
}

void Trace::flush()
{
    if (_sstream) {
        _element.set_comment(_sstream->str());
        delete _sstream;
        _sstream = 0;
    }
    _trace.push_back(_element);
}

std::ostringstream& Trace::sstream()
{
    if (_sstream == 0) {
        _sstream = new std::ostringstream();
    }
    return *_sstream;
}

Trace& Trace::trace()
{
    if (_instance == 0) {
        _instance = new Trace();
    }
    return *_instance;
}

} } // namespace paradevs common

paradevs::common::Trace& operator<<(paradevs::common::Trace& trace,
                                    const paradevs::common::TraceElement& e)
{
    trace.set_element(e);
    return trace;
}

paradevs::common::Trace& operator<<(paradevs::common::Trace& trace,
                                    const std::string& str)
{
    trace.sstream() << str;
    return trace;
}

paradevs::common::Trace& operator<<(paradevs::common::Trace& trace,
                                    paradevs::common::Time t)
{
    trace.sstream() << t;
    return trace;
}
