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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-rt is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-rt
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-rt. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-rt give you permission to link libcasm-rt
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-rt. If you modify libcasm-rt, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "main.h"

using namespace libcasm_ir;

static const auto id = Value::ID::PRINT_BUILTIN;

static const auto type = libstdhl::Memory::get< RelationType >(
    libstdhl::Memory::get< VoidType >(),
    Types( { libstdhl::Memory::get< StringType >() } ) );

#define TEST_( NAME, TO, FROM )                                                \
    TEST( libcasm_rt__builtin_print, NAME )                                    \
    {                                                                          \
        const auto arg = StringConstant( FROM );                               \
        testing::internal::CaptureStdout();                                    \
        Constant res;                                                          \
        libcasm_rt::Value::execute( id, *type, res, arg );                     \
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
