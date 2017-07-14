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

using namespace libcasm_ir;

// | LEQ         | undef | x : Integer | sym  |
// |-------------+-------+-------------+------|
// | undef       | true  | undef       | sym' |
// | y : Integer | undef | x >= y      | sym' |
// | sym         | sym'  | sym'        | sym' |

static const auto targ = libstdhl::List< Type >{
    { libstdhl::get< IntegerType >(), libstdhl::get< IntegerType >() }
};
static const auto tres = libstdhl::get< BooleanType >();
static const auto type = libstdhl::get< RelationType >( tres, targ );

TEST( libcasm_rt__instruction_leq, LeqInstruction_true )
{
    const auto a = IntegerConstant( -123 );
    const auto b = IntegerConstant( 123 );

    Constant r;
    libcasm_rt::Value::execute(
        Value::LEQ_INSTRUCTION, type->result(), r, a, b );

    EXPECT_TRUE( r.type().isBoolean() );
    EXPECT_TRUE( r == BooleanConstant( true ) );
}

TEST( libcasm_rt__instruction_leq, LeqInstruction_false )
{
    const auto a = IntegerConstant( 123 );
    const auto b = IntegerConstant( -123 );

    Constant r;
    libcasm_rt::Value::execute(
        Value::LEQ_INSTRUCTION, type->result(), r, a, b );

    EXPECT_TRUE( r.type().isBoolean() );
    EXPECT_TRUE( r == BooleanConstant( false ) );
}

TEST( libcasm_rt__instruction_leq, LeqInstruction_undef_lhs )
{
    const auto a = IntegerConstant( 123 );
    const auto b = IntegerConstant();

    Constant r;
    libcasm_rt::Value::execute(
        Value::LEQ_INSTRUCTION, type->result(), r, a, b );

    EXPECT_TRUE( r.type().isBoolean() );
    EXPECT_TRUE( r == BooleanConstant() );
}

TEST( libcasm_rt__instruction_leq, LeqInstruction_undef_rhs )
{
    const auto a = IntegerConstant();
    const auto b = IntegerConstant( 123 );

    Constant r;
    libcasm_rt::Value::execute(
        Value::LEQ_INSTRUCTION, type->result(), r, a, b );

    EXPECT_TRUE( r.type().isBoolean() );
    EXPECT_TRUE( r == BooleanConstant() );
}

TEST( libcasm_rt__instruction_leq, LeqInstruction_undef_both )
{
    const auto a = IntegerConstant();
    const auto b = IntegerConstant();

    Constant r;
    libcasm_rt::Value::execute(
        Value::LEQ_INSTRUCTION, type->result(), r, a, b );

    EXPECT_TRUE( r.type().isBoolean() );
    EXPECT_TRUE( r == BooleanConstant( true ) );
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
