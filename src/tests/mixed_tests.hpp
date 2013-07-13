/**
 * @file mixed_examples.hpp
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

#include <dtss/Dynamics.hpp>
#include <pdevs/Dynamics.hpp>

namespace paradevs {

class A1 : public paradevs::pdevs::Dynamics
{
public:
    A1(const std::string& name) : paradevs::pdevs::Dynamics(name)
    { }
    virtual ~A1()
    { }

    virtual void dint(common::Time /* t */);
    virtual void dext(common::Time /* t */, common::Time /* e */,
                      const common::Bag& /* msgs */);
    virtual void dconf(common::Time /* t */, common::Time /* e */,
                       const common::Bag& /* msgs */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Time ta(common::Time /* t */) const;
    virtual common::Bag lambda(common::Time /* t */) const;

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class B1 : public paradevs::pdevs::Dynamics
{
public:
    B1(const std::string& name) : paradevs::pdevs::Dynamics(name)
    { }
    virtual ~B1()
    { }

    virtual void dint(common::Time /* t */);
    virtual void dext(common::Time /* t */, common::Time /* e */,
                      const common::Bag& /* msgs */);
    virtual void dconf(common::Time /* t */, common::Time /* e */,
                       const common::Bag& /* msgs */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Time ta(common::Time /* t */) const;
    virtual common::Bag lambda(common::Time /* t */) const;

private:
    enum Phase { WAIT, SEND };

    Phase _phase;
};

class A2 : public paradevs::dtss::Dynamics
{
public:
    A2(const std::string& name) : paradevs::dtss::Dynamics(name)
    { }
    virtual ~A2()
    { }

    virtual void transition(const common::Bag& /* x */, common::Time /* t */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Bag lambda(common::Time /* t */) const;
};

class B2 : public paradevs::dtss::Dynamics
{
public:
    B2(const std::string& name) : paradevs::dtss::Dynamics(name)
    { }
    virtual ~B2()
    { }

    virtual void transition(const common::Bag& /* x */, common::Time /* t */);
    virtual common::Time start(common::Time /* t */);
    virtual common::Bag lambda(common::Time /* t */) const;
};

} // namespace paradevs
