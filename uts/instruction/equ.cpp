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

#include "uts/main.h"

// | EQU      | undef | x : Type | sym  |
// |----------+-------+----------+------|
// | undef    | true  | false    | sym' |
// | y : Type | false | x == y   | sym' |
// | sym      | sym'  | sym'     | sym' |

TEST( libcasm_rt__instruction_equ, EquInstruction_true )
{
    auto a = libcasm_ir::Constant::Integer( 123 );
    auto b = libcasm_ir::Constant::Integer( 123 );

    // auto i = libstdhl::make< libcasm_ir::EquInstruction >( a, b );
    // auto r = libcasm_rt::Value::execute( *i.get() );

    auto i = libcasm_ir::EquInstruction( a, b );
    auto r = libcasm_rt::Value::execute( i );

    libcasm_ir::BooleanConstant* rr = 0;
    ASSERT_TRUE( rr = libcasm_ir::cast< libcasm_ir::BooleanConstant >( r ) );
    EXPECT_TRUE( *rr == *libcasm_ir::Constant::Boolean( true ) );
    EXPECT_EQ( rr->value(), true );
    EXPECT_EQ( rr->defined(), true );
}

TEST( libcasm_rt__instruction_equ, EquInstruction_false )
{
    auto a = libcasm_ir::Constant::Integer( 0 );
    auto b = libcasm_ir::Constant::Integer( 10 );

    // auto i = libstdhl::make< libcasm_ir::EquInstruction >( a, b );
    // libcasm_ir::Value* r = libcasm_rt::Value::execute( *i.get() );

    auto i = libcasm_ir::EquInstruction( a, b );
    auto r = libcasm_rt::Value::execute( i );

    printf( "equ %s, %s --> %s\n", a->name(), b->name(), r->name() );

    libcasm_ir::BooleanConstant* rr = 0;
    ASSERT_TRUE( rr = libcasm_ir::cast< libcasm_ir::BooleanConstant >( r ) );
    EXPECT_TRUE( *rr == *libcasm_ir::Constant::Boolean( false ) );
    EXPECT_EQ( rr->value(), false );
    EXPECT_EQ( rr->defined(), true );
}

TEST( libcasm_rt__instruction_equ, 00 )
{
    auto a = libcasm_ir::Constant::Undef( libcasm_ir::Type::Integer() );
    auto b = libcasm_ir::Constant::Undef( libcasm_ir::Type::Integer() );

    auto i = libcasm_ir::EquInstruction( a, b );
    auto r = libcasm_rt::Value::execute( i );

    libcasm_ir::BooleanConstant* rr = 0;
    ASSERT_TRUE( rr = libcasm_ir::cast< libcasm_ir::BooleanConstant >( r ) );
    EXPECT_TRUE( *rr == *libcasm_ir::Constant::Boolean( true ) );
    EXPECT_EQ( rr->value(), true );
    EXPECT_EQ( rr->defined(), true );
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
