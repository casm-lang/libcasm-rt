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

#include "Constant.h"
#include "Type.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Constant.h"

#include "../csel-ir/src/Constant.h"

using namespace libcasm_rt;

libcsel_ir::Value& Constant::get( libcasm_ir::Value& value )
{
    assert( libcasm_ir::isa< libcasm_ir::Constant >( value ) );

    switch( value.id() )
    {
        case libcasm_ir::Value::BOOLEAN_CONSTANT:
        {
            libcasm_ir::BooleanConstant& ir_cv
                = libcasm_ir::cast< libcasm_ir::BooleanConstant >( value );

            libcsel_ir::Type& el_ty = libcasm_rt::Type::get( value.type() );

            return *libcsel_ir::Constant::getStructure( &el_ty,
                { libcsel_ir::Constant::getBit(
                      el_ty.getResults()[ 0 ], ir_cv.value() ),
                    libcsel_ir::Constant::getBit(
                        el_ty.getResults()[ 1 ], ir_cv.isDefined() ) } );
        }
        case libcasm_ir::Value::INTEGER_CONSTANT:
        {
            libcasm_ir::IntegerConstant& ir_cv
                = libcasm_ir::cast< libcasm_ir::IntegerConstant >( value );

            libcsel_ir::Type& el_ty = libcasm_rt::Type::get( value.type() );

            return *libcsel_ir::Constant::getStructure( &el_ty,
                { libcsel_ir::Constant::getBit(
                      el_ty.getResults()[ 0 ], ir_cv.value() ),
                    libcsel_ir::Constant::getBit(
                        el_ty.getResults()[ 1 ], ir_cv.isDefined() ) } );
        }
        case libcasm_ir::Value::BIT_CONSTANT:
        {
            libcasm_ir::BitConstant& ir_cv
                = libcasm_ir::cast< libcasm_ir::BitConstant >( value );

            libcsel_ir::Type& el_ty = libcasm_rt::Type::get( value.type() );

            return *libcsel_ir::Constant::getStructure( &el_ty,
                { libcsel_ir::Constant::getBit(
                      el_ty.getResults()[ 0 ], ir_cv.value() ),
                    libcsel_ir::Constant::getBit(
                        el_ty.getResults()[ 1 ], ir_cv.isDefined() ) } );
        }
        default:
            break;
    }

    libstdhl::Log::error(
        " unimplemented constant transformation for '%s' with type '%s'",
        value.name(), value.type().description() );

    assert( 0 );
    return *libcsel_ir::Constant::NIL();
}

// libcsel_ir::Value* Constant::create( libcsel_ir::Type& type )
// {
//     libcsel_ir::Value* c = 0;

//     // if( type.getIDKind() == libcsel_ir::Type::STRUCTURE )
//     // {
//     //     libcsel_ir::Value* b = type.getBound();
//     //     assert( b and libcsel_ir::Value::isa< libcsel_ir::Structure >( b )
//     );
//     //     libcsel_ir::Structure* s = (libcsel_ir::Structure*)b;
//     //     c = libcsel_ir::StructureConstant::create( s );
//     // }
//     // else
//     // {
//     //     assert( !"unsupported type to create constant found!" );
//     // }

//     assert( c );
//     return c;
// }

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
