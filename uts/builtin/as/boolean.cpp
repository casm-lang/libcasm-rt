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

static const auto targ
    = libstdhl::List< Type >{ { libstdhl::get< IntegerType >() } };
static const auto tres = libstdhl::get< BooleanType >();
static const auto type = libstdhl::get< RelationType >( tres, targ );

TEST( libcasm_rt__builtin_as_boolean, AsBoolean_Integer_true )
{
    const auto a = IntegerConstant( 1 );

    const auto r
        = libcasm_rt::Value::execute( Value::AS_BOOLEAN_BUILTIN, *type, a );

    EXPECT_TRUE( r == BooleanConstant( true ) );
}

TEST( libcasm_rt__builtin_as_boolean, AsBoolean_Integer_false )
{
    const auto a = IntegerConstant( 0 );

    const auto r
        = libcasm_rt::Value::execute( Value::AS_BOOLEAN_BUILTIN, *type, a );

    EXPECT_TRUE( r == BooleanConstant( false ) );
}

TEST( libcasm_rt__builtin_as_boolean, AsBoolean_Integer_undef )
{
    const auto a = IntegerConstant();

    const auto r
        = libcasm_rt::Value::execute( Value::AS_BOOLEAN_BUILTIN, *type, a );

    EXPECT_TRUE( r == BooleanConstant() );
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
