/**
 * @file pdevs_examples.hpp
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

#include <common/Builder.hpp>
#include <pdevs/Dynamics.hpp>
#include <pdevs/Simulator.hpp>

namespace paradevs { namespace pdevs {

class A : public Dynamics
{
public:
    A(const std::string& name) : Dynamics(name)
    { }
    virtual ~A()
    { }

    virtual void dint(const common::Time& t);
    virtual void dext(const common::Time& /* e */,
                      const common::Messages& /* msgs */);
    virtual common::Time start();
    virtual common::Time ta() const;
    virtual common::Messages lambda() const;
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

    virtual void dint(const common::Time& t);
    virtual void dext(const common::Time& /* e */,
                      const common::Messages& /* msgs */);
    virtual common::Time start();
    virtual common::Time ta() const;
    virtual common::Messages lambda() const;
    virtual void observation(std::ostream& /* file */) const;

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class HierachicalBuilder : public common::Builder
{
public:
    HierachicalBuilder()
    { }
    virtual ~HierachicalBuilder()
    { }

    virtual common::Model* build() const;
};

class OnlyOneBuilder : public common::Builder
{
public:
    OnlyOneBuilder()
    { }
    virtual ~OnlyOneBuilder()
    { }

    virtual common::Model* build() const;
};

class FlatBuilder : public common::Builder
{
public:
    FlatBuilder()
    { }
    virtual ~FlatBuilder()
    { }

    virtual common::Model* build() const;
};

} } // namespace paradevs pdevs
