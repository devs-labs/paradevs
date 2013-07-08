/**
 * @file Model.hpp
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

#ifndef DEVS_MODEL
#define DEVS_MODEL 1

#include <common/Message.hpp>
#include <common/Model.hpp>
#include <common/Time.hpp>

#include <vector>

namespace paradevs { namespace devs {

class Model : public common::Model
{
public:
    Model(const std::string& name);
    virtual ~Model();

    virtual common::Time i_message(common::Time /* t */) =0;
    virtual common::Time s_message(common::Time /* t */) =0;
    virtual common::Time x_message(const common::Message& /* message */,
                                   common::Time /* t */) =0;
};

typedef std::vector < Model* > Models;

} } // namespace paradevs devs

#endif
