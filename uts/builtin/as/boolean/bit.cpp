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

#define TEST_( NAME, SIZE, FROM, TO )                                          \
    TEST( libcasm_rt__builtin_as_boolean_bit, SIZE##NAME )                     \
    {                                                                          \
        const auto arg = BitConstant FROM;                                     \
                                                                               \
        const auto type                                                        \
            = libstdhl::get< RelationType >( libstdhl::get< BooleanType >(),   \
                Types( { libstdhl::get< BitType >( SIZE ) } ) );               \
                                                                               \
        const auto res = libcasm_rt::Value::execute(                           \
            Value::AS_BOOLEAN_BUILTIN, *type, arg );                           \
                                                                               \
        EXPECT_TRUE( res == BooleanConstant( TO ) );                           \
    }

TEST_( undef_at_undef, 1, ( 1 ), );
TEST_( false_at_zero, 1, ( 1, 0 ), false );
TEST_( true__at_one, 1, ( 1, 1 ), true );

TEST_( undef_at_undef, 8, ( 8 ), );
TEST_( false_at_zero, 8, ( 8, 0 ), false );
TEST_( true__at_one, 8, ( 8, 1 ), true );
TEST_( true__at_large, 8, ( 8, 0xee ), true );

TEST_( undef_at_undef, 23, ( 23 ), );
TEST_( false_at_zero, 23, ( 23, 0 ), false );
TEST_( true__at_one, 23, ( 23, 1 ), true );
TEST_( true__at_large, 23, ( 23, 0xfeed ), true );

TEST_( undef_at_undef, 48, ( 48 ), );
TEST_( false_at_zero, 48, ( 48, 0 ), false );
TEST_( true__at_one, 48, ( 48, 1 ), true );
TEST_( true__at_large, 48, ( 48, 0xfeedbeef ), true );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
