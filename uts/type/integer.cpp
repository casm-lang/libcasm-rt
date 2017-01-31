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

TEST( libcasm_rt__type, integer )
{
    libcasm_ir::Type* ir_ty = libcasm_ir::Type::Integer();
    libcsel_ir::Type& el_ty = libcasm_rt::Type::get( *ir_ty );

    ASSERT_TRUE( el_ty.isStructure() );
    ASSERT_EQ( el_ty.results().size(), 2 );

    ASSERT_TRUE( el_ty.results()[ 0 ]->isBit() );
    ASSERT_TRUE( el_ty.results()[ 1 ]->isBit() );
}
