//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                https://github.com/casm-lang/libcasm-rt
//
//  This file is part of libcasm-rt.
//
//  libcasm-rt is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-rt is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-rt. If not, see <http://www.gnu.org/licenses/>.
//

#include "gtest/gtest.h"

#include "libcasm-ir.h"
#include "libcasm-rt.h"
#include "libcsel-ir.h"

TEST( libcasm_rt__constant, integer )
{
    libcasm_ir::Value* ir_cv = libcasm_ir::Constant::Integer( 5 );
    libcsel_ir::Value& el_cv = libcasm_rt::Constant::get( *ir_cv );

    ASSERT_TRUE( el_cv.getType()->isStructure() );
    ASSERT_EQ( el_cv.getType()->getResults().size(), 2 );
}
