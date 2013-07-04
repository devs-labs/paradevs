/**
 * @file examples.hpp
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

#include <devs/Builder.hpp>
#include <devs/Dynamics.hpp>
#include <devs/Simulator.hpp>

namespace paradevs {

class A : public Dynamics
{
public:
    A(const std::string& name) : Dynamics(name)
    { }
    virtual ~A()
    { }

    virtual void dint(const Time& t);
    virtual void dext(const Time& /* e */, const Message& msg);
    virtual Time start();
    virtual Time ta() const;
    virtual Messages lambda() const;
    virtual void observation(std::ostream& /* file */) const;

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class B : public Dynamics
{
public:
    B(const std::string& name) : Dynamics(name)
    { }
    virtual ~B()
    { }

    virtual void dint(const Time& t);
    virtual void dext(const Time& /* e */, const Message& msg);
    virtual Time start();
    virtual Time ta() const;
    virtual Messages lambda() const;
    virtual void observation(std::ostream& /* file */) const;

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class MyBuilder : public Builder
{
public:
    MyBuilder()
    { }
    virtual ~MyBuilder()
    { }

    virtual Coordinator* build() const;
};

} // namespace paradevs
