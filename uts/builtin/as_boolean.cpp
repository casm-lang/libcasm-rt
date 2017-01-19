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

#include "gtest/gtest.h"

#include "libcasm-ir.h"
#include "libcasm-rt.h"

#include "libcsel-ir.h"
#include "libcsel-rt.h"

TEST( libcasm_rt__builtin, as_boolean )
{
    libcasm_ir::Value* a = libcasm_ir::Constant::getInteger( 0 );

    libcasm_ir::Value* b = libcasm_ir::Builtin::getAsBuiltin(
        libcasm_ir::Type::getRelation( libcasm_ir::Type::getBoolean(),
            { libcasm_ir::Type::getInteger() } ) );

    libcsel_ir::CallableUnit& c = libcasm_rt::Builtin::getAsBoolean( *b );

    // c.addParameter( , true );
    // c.addParameter( )

    libcsel_rt::CallableUnit::compile( c );
}
