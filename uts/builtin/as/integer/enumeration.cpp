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

static const auto id = Value::ID::AS_INTEGER_BUILTIN;

static const auto type
    = libstdhl::get< RelationType >( libstdhl::get< IntegerType >(),
        Types( { libstdhl::make< EnumerationType >( definition ) } ) );

TEST( libcasm_rt__builtin_as_integer_enumeration, invalid_constant )
{
    EXPECT_THROW( EnumerationConstant asdf( definition, "X" );
                  , std::domain_error );
}

#define TEST_( NAME, TO, FROM )                                                \
    TEST( libcasm_rt__builtin_as_integer_enumeration, NAME )                   \
    {                                                                          \
        const auto arg = EnumerationConstant FROM;                             \
        Constant res;                                                          \
        libcasm_rt::Value::execute( id, *type, res, arg );                     \
        EXPECT_STREQ( res.description().c_str(),                               \
            IntegerConstant( TO ).description().c_str() );                     \
    }

TEST_( undef_at_undef, , ( definition ) );
TEST_( zero_at_enumA, 0, ( definition, "A" ) );
TEST_( one__at_enumB, 1, ( definition, "B" ) );
TEST_( two__at_enumC, 2, ( definition, "C" ) );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
