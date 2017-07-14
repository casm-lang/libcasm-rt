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

static const auto definition = libstdhl::make< Enumeration >(
    "ENUM", std::initializer_list< std::string >{ "A", "B", "C" } );

static const auto id = Value::ID::AS_STRING_BUILTIN;

static const auto type
    = libstdhl::get< RelationType >( libstdhl::get< StringType >(),
        Types( { libstdhl::make< EnumerationType >( definition ) } ) );

#define TEST_( NAME, TO, FROM )                                                \
    TEST( libcasm_rt__builtin_as_string_enumeration, NAME )                    \
    {                                                                          \
        const auto arg = EnumerationConstant FROM;                             \
        Constant res;                                                          \
        libcasm_rt::Value::execute( id, *type, res, arg );                     \
        EXPECT_STREQ( res.description().c_str(),                               \
            StringConstant( TO ).description().c_str() );                      \
    }

TEST_( undef_at_undef, , ( definition ) );
TEST_( str_A_at_enumA, "A", ( definition, "A" ) );
TEST_( str_B_at_enumB, "B", ( definition, "B" ) );
TEST_( str_C_at_enumC, "C", ( definition, "C" ) );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
