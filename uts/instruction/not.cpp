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

// | NOT | undef | false | true  | sym  |
// |-----+-------+-------+-------+------|
// | -   | undef | true  | false | sym' |

TEST( libcasm_rt__instruction_not, NotInstruction_0 )
{
    auto a = libcasm_ir::Constant::Integer( 123 );

    auto i = libcasm_ir::NotInstruction( a );
    auto r = libcasm_rt::Value::execute( i );

    libcasm_ir::BooleanConstant* rr = 0;
    ASSERT_TRUE( rr = libcasm_ir::cast< libcasm_ir::BooleanConstant >( r ) );
    EXPECT_TRUE( *rr == *libcasm_ir::Constant::Boolean( false ) );
    EXPECT_EQ( rr->value(), false );
    EXPECT_EQ( rr->defined(), true );
}

TEST( libcasm_rt__instruction_not, NotInstruction_1 )
{
    auto a = libcasm_ir::Constant::Integer( 0 );

    auto i = libcasm_ir::NotInstruction( a );
    auto r = libcasm_rt::Value::execute( i );

    libcasm_ir::BooleanConstant* rr = 0;
    ASSERT_TRUE( rr = libcasm_ir::cast< libcasm_ir::BooleanConstant >( r ) );
    EXPECT_TRUE( *rr == *libcasm_ir::Constant::Boolean( true ) );
    EXPECT_EQ( rr->value(), true );
    EXPECT_EQ( rr->defined(), true );
}

TEST( libcasm_rt__instruction_not, NotInstruction_2 )
{
    auto a = libcasm_ir::Constant::Undef( libcasm_ir::Type::Integer() );

    auto i = libcasm_ir::NotInstruction( a );
    auto r = libcasm_rt::Value::execute( i );

    libcasm_ir::BooleanConstant* rr = 0;
    ASSERT_TRUE( rr = libcasm_ir::cast< libcasm_ir::BooleanConstant >( r ) );
    EXPECT_TRUE(
        *rr == *libcasm_ir::Constant::Undef( libcasm_ir::Type::Boolean() ) );
    EXPECT_EQ( rr->defined(), false );
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
