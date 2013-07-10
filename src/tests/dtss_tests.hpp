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
#include <dtss/Dynamics.hpp>
#include <dtss/Simulator.hpp>

namespace paradevs { namespace dtss {

class A : public Dynamics
{
public:
    A(const std::string& name) : Dynamics(name)
    { }
    virtual ~A()
    { }

    virtual void transition(const common::Bag& /* x */, common::Time /* t */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Bag lambda(common::Time /* t */) const;
};

class B : public Dynamics
{
public:
    B(const std::string& name) : Dynamics(name)
    { }
    virtual ~B()
    { }

    virtual void transition(const common::Bag& /* x */, common::Time /* t */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Bag lambda(common::Time /* t */) const;
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

class TwoBuilder : public common::Builder
{
public:
    TwoBuilder()
    { }
    virtual ~TwoBuilder()
    { }

    virtual common::Model* build() const;
};

} } // namespace paradevs dtss
