//
//  Copyright (c) 2014-2016 CASM Organization
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

#include "Constant.h"

using namespace libcasm_rt;

libcsel_ir::Value* Constant::create( libcsel_ir::Type& type )
{
    libcsel_ir::Value* c = 0;

    if( type.getIDKind() == libcsel_ir::Type::STRUCTURE )
    {
        libcsel_ir::Value* b = type.getBound();
        assert( b and libcsel_ir::Value::isa< libcsel_ir::Structure >( b ) );
        libcsel_ir::Structure* s = (libcsel_ir::Structure*)b;
        c = libcsel_ir::StructureConstant::create( s );
    }
    else
    {
        assert( !"unsupported type to create constant found!" );
    }

    assert( c );
    return c;
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
