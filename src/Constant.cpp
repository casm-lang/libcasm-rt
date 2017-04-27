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

libcsel_ir::Constant Constant::get( const libcasm_ir::Value& value )
{
    assert( libcasm_ir::isa< libcasm_ir::Constant >( value ) );

    const auto ty = Type::get( value.type() );

    switch( value.id() )
    {
        case libcasm_ir::Value::BOOLEAN_CONSTANT:
        {
            const auto c
                = static_cast< const libcasm_ir::BooleanConstant& >( value );

            return libcsel_ir::StructureConstant( ty,
                std::initializer_list< libcsel_ir::Constant >{
                    libcsel_ir::BitConstant( ty->results()[ 0 ], c.value() ),
                    libcsel_ir::BitConstant(
                        ty->results()[ 1 ], c.defined() ) } );
        }
        case libcasm_ir::Value::INTEGER_CONSTANT:
        {
            const auto c
                = static_cast< const libcasm_ir::IntegerConstant& >( value );

            return libcsel_ir::StructureConstant( ty,
                std::initializer_list< libcsel_ir::Constant >{
                    libcsel_ir::BitConstant( ty->results()[ 0 ], c.value_i64() ),
                    libcsel_ir::BitConstant(
                        ty->results()[ 1 ], c.defined() ) } );
        }
        case libcasm_ir::Value::BIT_CONSTANT:
        {
            const auto c
                = static_cast< const libcasm_ir::BitConstant& >( value );

            return libcsel_ir::StructureConstant( ty,
                std::initializer_list< libcsel_ir::Constant >{
                    libcsel_ir::BitConstant( ty->results()[ 0 ], c.value() ),
                    libcsel_ir::BitConstant(
                        ty->results()[ 1 ], c.defined() ) } );
        }
        default:
        {
            libstdhl::Log::error(
                " unimplemented constant transformation for '%s' with type "
                "'%s'",
                value.name().c_str(), value.type().description().c_str() );

            assert( 0 );
            return libcsel_ir::VoidConstant();
        }
    }
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
