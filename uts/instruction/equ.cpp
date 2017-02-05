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
#include "libcsel-rt.h"

TEST( libcasm_rt__instruction_equ, valid )
{
    auto a = libcasm_ir::Constant::Integer( 123 );
    auto b = libcasm_ir::Constant::Integer( 123 );

    // auto i = libstdhl::make< libcasm_ir::EquInstruction >( a, b );
    // auto r = libcasm_rt::Instruction::execute( *i.get() );

    auto i = libcasm_ir::EquInstruction( a, b );
    auto r = libcasm_rt::Instruction::execute( i );

    ASSERT_TRUE( *r == *libcasm_ir::Constant::Boolean( true ) );
}

TEST( libcasm_rt__instruction_equ, invalid )
{
    auto a = libcasm_ir::Constant::Integer( 0 );
    auto b = libcasm_ir::Constant::Integer( 10 );

    printf( "%s, %s\n", a->name(), b->name() );

    // auto i = libstdhl::make< libcasm_ir::EquInstruction >( a, b );
    // libcasm_ir::Value* r = libcasm_rt::Instruction::execute( *i.get() );

    auto i = libcasm_ir::EquInstruction( a, b );
    auto r = libcasm_rt::Instruction::execute( i );

    ASSERT_TRUE( *r == *libcasm_ir::Constant::Boolean( false ) );
}
