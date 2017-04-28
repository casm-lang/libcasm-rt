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

static const auto id = Value::ID::PRINT_BUILTIN;

static const auto type = libstdhl::get< RelationType >(
    libstdhl::get< VoidType >(), Types( { libstdhl::get< StringType >() } ) );

#define TEST_( NAME, TO, FROM )                                                \
    TEST( libcasm_rt__builtin_print, NAME )                                    \
    {                                                                          \
        const auto arg = StringConstant( FROM );                               \
        testing::internal::CaptureStdout();                                    \
        const auto res = libcasm_rt::Value::execute( id, *type, arg );         \
        const auto output = testing::internal::GetCapturedStdout();            \
        EXPECT_TRUE( res == VoidConstant() );                                  \
        EXPECT_STREQ( output.c_str(), TO );                                    \
        /*printf( "%s\n", output.c_str() );*/                                  \
    }

TEST_( undef, "undef", );
TEST_( short, "foo", "foo" );
TEST_( large, "This is a very very long string!",
    "This is a very very long string!" );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
