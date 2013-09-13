/**
 * @file tests/boost_graph/models.hpp
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

#ifndef TESTS_BOOST_GRAPH_MODELS_HPP
#define TESTS_BOOST_GRAPH_MODELS_HPP 1

#include <common/time/DoubleTime.hpp>

#include <kernel/pdevs/Dynamics.hpp>

namespace paradevs { namespace tests { namespace boost_graph {

int N;

struct TopPixelParameters
{ };

template < class SchedulerHandle>
class TopPixel :
    public paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                       TopPixelParameters >
{
public:
    TopPixel(const std::string& name,
             const TopPixelParameters& parameters) :
        paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                    TopPixelParameters >(name, parameters)
    { }

    virtual ~TopPixel()
    { }

    virtual void dint(typename common::DoubleTime::type /* t */)
    {

        // std::cout << TopPixel < SchedulerHandle >::get_name() << " at "
        //           << t << ": dint" << std::endl;

        N++;

    }

    virtual typename common::DoubleTime::type start(
        typename common::DoubleTime::type /* t */)
    { return 0; }

    virtual typename common::DoubleTime::type ta(
        typename common::DoubleTime::type /* t */) const
    { return 1; }

    virtual common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        typename common::DoubleTime::type /* t */) const
    {

        // std::cout << TopPixel < SchedulerHandle >::get_name() << " at "
        //           << t << ": lambda" << std::endl;

        common::Bag < common::DoubleTime, SchedulerHandle > bag;

        bag.push_back(common::ExternalEvent < common::DoubleTime,
                                              SchedulerHandle >("out", 0.));
        return bag;
    }
};

struct NormalPixelParameters
{
    NormalPixelParameters(unsigned int n) : _neighbour_number(n)
    { }

    unsigned int _neighbour_number;
};

template < class SchedulerHandle>
class NormalPixel :
    public paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                       NormalPixelParameters >
{
public:
    NormalPixel(const std::string& name,
             const NormalPixelParameters& parameters) :
        paradevs::pdevs::Dynamics < common::DoubleTime, SchedulerHandle,
                                    NormalPixelParameters >(name, parameters),
        _neighbour_number(parameters._neighbour_number)
    { }

    virtual ~NormalPixel()
    { }

    virtual void dint(typename common::DoubleTime::type t)
    {

        // std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
        //           << t << ": dint" << std::endl;

        if (_phase == SEND) {
            _phase = WAIT;
            _received = 0;
            _last_time = t;
        }
    }

    virtual void dext(typename common::DoubleTime::type t,
                      typename common::DoubleTime::type /* e */,
                      const common::Bag < common::DoubleTime,
                                          SchedulerHandle >& bag)
    {

        // std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
        //           << t << ": dext -> "
        //           << bag.to_string() << std::endl;

        for (typename common::Bag < common::DoubleTime,
                                    SchedulerHandle >::const_iterator it =
                 bag.begin(); it != bag.end(); ++it) {
            if (it->on_port("in")) {
                if (_last_time == t) {
                    std::cout << "oups !" << std::endl;
                }
                ++_received;
                if (_received == _neighbour_number) {

                    N++;

                    _phase = SEND;
                }
            }
        }

        // std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
        //           << t << ": dext -> "
        //           << _received << "/" << _neighbour_number
        //           << std::endl;

    }

    virtual typename common::DoubleTime::type start(
        typename common::DoubleTime::type /* t */)
    {

        // std::cout << NormalPixel < SchedulerHandle >::get_name()
        //           << " = " <<_neighbour_number << std::endl;

        _phase = WAIT;
        _received = 0;
        _last_time = common::DoubleTime::negative_infinity;
        return common::DoubleTime::infinity;
    }

    virtual typename common::DoubleTime::type ta(
        typename common::DoubleTime::type /* t */) const
    {

        // std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
        //           << t << ": ta" << std::endl;

        if (_phase == WAIT) {
            return common::DoubleTime::infinity;
        } else {
            return 0;
        }
    }

    virtual common::Bag < common::DoubleTime, SchedulerHandle > lambda(
        typename common::DoubleTime::type /* t */) const
    {

        // std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
        //           << t << ": lambda" << std::endl;

        common::Bag < common::DoubleTime, SchedulerHandle > bag;

        if (_phase == SEND) {
            bag.push_back(common::ExternalEvent < common::DoubleTime,
                                                  SchedulerHandle >("out", 0.));
        }
        return bag;
    }

private:
    enum Phase { WAIT, SEND };

    unsigned int _neighbour_number;

    Phase                             _phase;
    unsigned int                      _received;
    typename common::DoubleTime::type _last_time;
};

} } } // namespace paradevs tests boost_graph

#endif
