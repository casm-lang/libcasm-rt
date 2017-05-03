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

static const auto id = Value::ID::ADD_INSTRUCTION;

static const auto type = libstdhl::get< RelationType >(
    libstdhl::get< StringType >(),
    Types( { libstdhl::get< StringType >(), libstdhl::get< StringType >() } ) );

#define TEST_( NAME, RES, LHS, RHS )                                           \
    TEST( libcasm_rt__instruction_add_string_string, NAME )                    \
    {                                                                          \
        const auto lhs = StringConstant( LHS );                                \
        const auto rhs = StringConstant( RHS );                                \
        const auto res = libcasm_rt::Value::execute( id, *type, lhs, rhs );    \
        EXPECT_TRUE( res == StringConstant( RES ) );                           \
        EXPECT_STREQ( res.description().c_str(),                               \
            StringConstant( RES ).description().c_str() );                     \
    }

TEST_( undef__at__undef__undef, , , );
TEST_( undef__at__empty__undef, , "", );
TEST_( undef__at__undef__empty, , , "" );
TEST_( undef__at__text___undef, , "foo", );
TEST_( undef__at__undef__text_, , , "foo" );

TEST_( empty__at__empty__empty, "", "", "" );
TEST_( text2__at__text___text_, "foofoo", "foo", "foo" );
TEST_( long___at__short__short, "foobar;bazqux", "foobar", ";bazqux" );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
