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

static const auto id = Value::ID::AS_STRING_BUILTIN;

#define TEST_( NAME, SIZE, TO, FROM )                                          \
    TEST( libcasm_rt__builtin_as_string_bit##SIZE, NAME )                      \
    {                                                                          \
        const auto arg = BitConstant FROM;                                     \
        const auto type                                                        \
            = libstdhl::get< RelationType >( libstdhl::get< StringType >(),    \
                Types( { libstdhl::get< BitType >( SIZE ) } ) );               \
        const auto res = libcasm_rt::Value::execute( id, *type, arg );         \
        EXPECT_STREQ( res.description().c_str(),                               \
            StringConstant( TO ).description().c_str() );                      \
    }

TEST_( undef_at_undef, 1, , ( 1 ) );
TEST_( zero__at_zero, 1, "0", ( 1, 0 ) );
TEST_( one___at_one, 1, "1", ( 1, 1 ) );

TEST_( undef_at_undef, 8, , ( 1 ) );
TEST_( zero__at_zero, 8, "0", ( 8, 0 ) );
TEST_( one___at_one, 8, "1", ( 8, 1 ) );
TEST_( large_at_large, 8, "254", ( 8, 0xfe ) );

TEST_( undef_at_undef, 50, , ( 1 ) );
TEST_( zero__at_zero, 50, "0", ( 50, 0 ) );
TEST_( one___at_one, 50, "1", ( 50, 1 ) );
TEST_( large_at_large, 50, "65261", ( 50, 0xfeed ) );
TEST_( huge__at_huge, 50, "123456789", ( 50, 123456789 ) );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
