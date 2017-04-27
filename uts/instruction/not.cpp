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

// | NOT | undef | false | true  | sym  |
// |-----+-------+-------+-------+------|
// | -   | undef | true  | false | sym' |

TEST( libcasm_rt__instruction_not, NotInstruction_123_to_false )
{
    auto a = libstdhl::get< IntegerConstant >( 123 );

    auto i = NotInstruction( a );
    auto r = libcasm_rt::Value::execute( i );

    ASSERT_TRUE( r == BooleanConstant( false ) );
}

TEST( libcasm_rt__instruction_not, NotInstruction_1_to_false )
{
    auto a = libstdhl::get< IntegerConstant >( 1 );

    auto i = NotInstruction( a );
    auto r = libcasm_rt::Value::execute( i );

    ASSERT_TRUE( r == BooleanConstant( false ) );
}

TEST( libcasm_rt__instruction_not, NotInstruction_0_to_true )
{
    auto a = libstdhl::get< IntegerConstant >( 0 );

    auto i = NotInstruction( a );
    auto r = libcasm_rt::Value::execute( i );

    ASSERT_TRUE( r == BooleanConstant( true ) );
}

TEST( libcasm_rt__instruction_not, NotInstruction_undef_to_undef )
{
    auto a = libstdhl::get< IntegerConstant >();

    auto i = NotInstruction( a );
    auto r = libcasm_rt::Value::execute( i );

    ASSERT_TRUE( r == BooleanConstant() );
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
