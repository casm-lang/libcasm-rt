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

#include "../casm-ir/src/Exception.h"

using namespace libcasm_ir;

static const auto id = Value::ID::ASSERT_BUILTIN;

static const auto type = libstdhl::get< RelationType >(
    libstdhl::get< VoidType >(), Types( { libstdhl::get< BooleanType >() } ) );

TEST( libcasm_rt__builtin_assert, undef )
{
    const auto arg = BooleanConstant();
    Constant res;
    EXPECT_THROW( libcasm_rt::Value::execute( id, *type, res, arg );
                  , UndefinedConstantException );
}

TEST( libcasm_rt__builtin_assert, false )
{
    const auto arg = BooleanConstant( false );
    Constant res;
    EXPECT_THROW( libcasm_rt::Value::execute( id, *type, res, arg );
                  , AssertionException );
}

TEST( libcasm_rt__builtin_assert, true )
{
    const auto arg = BooleanConstant( true );
    Constant res;
    libcasm_rt::Value::execute( id, *type, res, arg );
    EXPECT_TRUE( res == VoidConstant() );
}

static const auto type2 = libstdhl::get< RelationType >(
    libstdhl::get< VoidType >(), Types( { libstdhl::get< BooleanType >(),
                                     libstdhl::get< StringType >() } ) );

TEST( libcasm_rt__builtin_assert, undef_with_msg_undef )
{
    const auto arg = BooleanConstant();
    const auto msg = StringConstant();
    Constant res;
    EXPECT_THROW( libcasm_rt::Value::execute( id, *type2, res, arg, msg );
                  , UndefinedConstantException );
}

TEST( libcasm_rt__builtin_assert, false_with_msg_undef )
{
    const auto arg = BooleanConstant( false );
    const auto msg = StringConstant();
    Constant res;
    EXPECT_THROW( libcasm_rt::Value::execute( id, *type2, res, arg, msg );
                  , AssertionException );
}

TEST( libcasm_rt__builtin_assert, true_with_msg_undef )
{
    const auto arg = BooleanConstant( true );
    const auto msg = StringConstant();
    Constant res;
    libcasm_rt::Value::execute( id, *type2, res, arg, msg );
    EXPECT_TRUE( res == VoidConstant() );
}

TEST( libcasm_rt__builtin_assert, undef_with_msg_txt )
{
    const auto arg = BooleanConstant();
    const auto msg = StringConstant( "foo bar baz qux" );
    Constant res;
    EXPECT_THROW( libcasm_rt::Value::execute( id, *type2, res, arg, msg );
                  , UndefinedConstantException );
}

TEST( libcasm_rt__builtin_assert, false_with_msg_txt )
{
    const auto arg = BooleanConstant( false );
    const auto msg = StringConstant( "foo bar baz qux" );
    Constant res;
    EXPECT_THROW( libcasm_rt::Value::execute( id, *type2, res, arg, msg );
                  , AssertionException );
}

TEST( libcasm_rt__builtin_assert, true_with_msg_txt )
{
    const auto arg = BooleanConstant( true );
    const auto msg = StringConstant( "foo bar baz qux" );
    Constant res;
    libcasm_rt::Value::execute( id, *type2, res, arg, msg );
    EXPECT_TRUE( res == VoidConstant() );
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
