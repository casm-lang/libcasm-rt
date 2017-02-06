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

TEST( libcasm_rt__instruction_equ, EquInstruction_valid )
{
    auto a = libcasm_ir::Constant::Integer( 123 );
    auto b = libcasm_ir::Constant::Integer( 123 );

    // auto i = libstdhl::make< libcasm_ir::EquInstruction >( a, b );
    // auto r = libcasm_rt::Value::execute( *i.get() );

    auto i = libcasm_ir::EquInstruction( a, b );
    auto r = libcasm_rt::Value::execute( i );

    auto z = libcasm_ir::Constant::Boolean( true );
    ASSERT_TRUE( *r == *z );
}

TEST( libcasm_rt__instruction_equ, EquInstruction_invalid )
{
    auto a = libcasm_ir::Constant::Integer( 0 );
    auto b = libcasm_ir::Constant::Integer( 10 );

    // auto i = libstdhl::make< libcasm_ir::EquInstruction >( a, b );
    // libcasm_ir::Value* r = libcasm_rt::Value::execute( *i.get() );

    auto i = libcasm_ir::EquInstruction( a, b );
    auto r = libcasm_rt::Value::execute( i );

    printf( "equ %s, %s --> %s\n", a->name(), b->name(), r->name() );

    ASSERT_TRUE( *r == *libcasm_ir::Constant::Boolean( false ) );
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
