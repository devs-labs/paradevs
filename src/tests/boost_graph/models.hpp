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

#ifndef __TESTS_BOOST_GRAPH_MODELS_HPP
#define __TESTS_BOOST_GRAPH_MODELS_HPP 1

#include <common/Time.hpp>

#include <pdevs/Dynamics.hpp>

#include <limits>

namespace paradevs { namespace tests { namespace boost_graph {

template < typename T >
struct Limits
{
    static constexpr T negative_infinity =
        -std::numeric_limits < T >::infinity();
    static constexpr T positive_infinity =
        std::numeric_limits < T >::infinity();
    static constexpr T null = 0;
};

typedef paradevs::common::Time < double, Limits < double > > MyTime;

struct TopPixelParameters
{ };

template < class SchedulerHandle>
class TopPixel :
    public paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                       TopPixelParameters >
{
public:
    TopPixel(const std::string& name,
             const TopPixelParameters& parameters) :
        paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                    TopPixelParameters >(name, parameters)
    { }

    virtual ~TopPixel()
    { }

    virtual void dint(typename MyTime::type t)
    {

        std::cout << TopPixel < SchedulerHandle >::get_name() << " at "
                  << t << ": dint" << std::endl;

    }

    virtual typename MyTime::type start(typename MyTime::type /* t */)
    { return 0; }

    virtual typename MyTime::type ta(typename MyTime::type /* t */) const
    { return 1; }

    virtual common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {

        std::cout << TopPixel < SchedulerHandle >::get_name() << " at "
                  << t << ": lambda" << std::endl;

        common::Bag < MyTime, SchedulerHandle > bag;

        bag.push_back(common::ExternalEvent < MyTime, SchedulerHandle >(
                          "out", 0.));
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
    public paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                       NormalPixelParameters >
{
public:
    NormalPixel(const std::string& name,
             const NormalPixelParameters& parameters) :
        paradevs::pdevs::Dynamics < MyTime, SchedulerHandle,
                                    NormalPixelParameters >(name, parameters),
        _neighbour_number(parameters._neighbour_number)
    { }

    virtual ~NormalPixel()
    { }

    virtual void dint(typename MyTime::type t)
    {

        std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
                  << t << ": dint" << std::endl;

        if (_phase == SEND) {
            _phase = WAIT;
            _received = 0;
        }
    }

    virtual void dext(typename MyTime::type t,
                      typename MyTime::type /* e */,
                      const common::Bag < MyTime, SchedulerHandle >& bag)
    {

        std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
                  << t << ": dext -> "
                  << bag.to_string() << std::endl;

        for (typename common::Bag < MyTime,
                                    SchedulerHandle >::const_iterator it =
                 bag.begin(); it != bag.end(); ++it) {
            if (it->on_port("in")) {
                ++_received;
                if (_received == _neighbour_number) {
                    _phase = SEND;
                }
            }
        }

        std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
                  << t << ": dext -> "
                  << _received << "/" << _neighbour_number
                  << std::endl;

    }

    virtual typename MyTime::type start(typename MyTime::type /* t */)
    {
        _phase = WAIT;
        _received = 0;
        return MyTime::infinity;
    }

    virtual typename MyTime::type ta(typename MyTime::type t) const
    {

        std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
                  << t << ": ta" << std::endl;

        if (_phase == WAIT) {
            return MyTime::infinity;
        } else {
            return 0;
        }
    }

    virtual common::Bag < MyTime, SchedulerHandle > lambda(
        typename MyTime::type t) const
    {

        std::cout << NormalPixel < SchedulerHandle >::get_name() << " at "
                  << t << ": lambda" << std::endl;

        common::Bag < MyTime, SchedulerHandle > bag;

        if (_phase == SEND) {
            bag.push_back(common::ExternalEvent < MyTime,
                                                  SchedulerHandle >("out", 0.));
        }
        return bag;
    }

private:
    enum Phase { WAIT, SEND };

    unsigned int _neighbour_number;

    Phase _phase;
    unsigned int _received;
};

enum DynamicsType {
    TOP_PIXEL = 0, NORMAL_PIXEL
};

} } } // namespace paradevs tests boost_graph

#endif
