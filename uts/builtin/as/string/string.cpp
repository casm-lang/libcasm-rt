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

static const auto type = libstdhl::get< RelationType >(
    libstdhl::get< StringType >(), Types( { libstdhl::get< StringType >() } ) );

#define TEST_( NAME, VALUE )                                                   \
    TEST( libcasm_rt__builtin_as_string_string, NAME )                         \
    {                                                                          \
        const auto arg = StringConstant( VALUE );                              \
        Constant res;                                                          \
        libcasm_rt::Value::execute( id, *type, res, arg );                     \
        EXPECT_STREQ( res.description().c_str(),                               \
            StringConstant( VALUE ).description().c_str() );                   \
    }

TEST_( undef, );
TEST_( empty, "" );
TEST_( short, "foo" );
TEST_( long, "This is a very long text in this unit test case!" );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
