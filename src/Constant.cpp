//
//  Copyright (C) 2014-2023 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-rt/graphs/contributors>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-rt is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-rt
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-rt. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-rt give you permission to link libcasm-rt
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-rt. If you modify libcasm-rt, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "Constant.h"
#include "Type.h"

#include <libstdhl/Log>

#include <libcasm-ir/Constant>

// #include "../csel-ir/src/Constant.h"

using namespace libcasm_rt;

// libcsel_ir::Value::Ptr Constant::get( libcasm_ir::Value& value )
// {
//     assert( libcasm_ir::isa< libcasm_ir::Constant >( value ) );

//     return libstdhl::make< libcsel_ir::VoidConstant >();
//     // switch( value.id() )
//     // {
//     //     case libcasm_ir::Value::BOOLEAN_CONSTANT:
//     //     {
//     //         auto ir_cv
//     //             = libcasm_ir::cast< libcasm_ir::BooleanConstant >( value
//     );

//     //         libstdhl::Log::info( "RT:Constant: %s", ir_cv->dump().c_str()
//     );

//     //         libcsel_ir::Type& el_ty = libcasm_rt::Type::get( value.type()
//     );

//     //         const std::vector< libcsel_ir::Constant::Ptr > el_args
//     //             = { libstdhl::make< libcsel_ir::BitConstant >(
//     //                     el_ty.results()[ 0 ], ir_cv->value() ),
//     //                 libstdhl::make< libcsel_ir::BitConstant >(
//     //                     el_ty.results()[ 1 ], ir_cv->defined() ) };

//     //         return std::static_pointer_cast< libcsel_ir::Value >(
//     //             libstdhl::make< libcsel_ir::StructureConstant >(
//     //                 el_ty, el_args ) );
//     //     }
//     //     case libcasm_ir::Value::INTEGER_CONSTANT:
//     //     {
//     //         auto ir_cv
//     //             = libcasm_ir::cast< libcasm_ir::IntegerConstant >( value
//     );

//     //         libstdhl::Log::info( "RT:Constant: %s", ir_cv->c_str() );

//     //         libcsel_ir::Type& el_ty = libcasm_rt::Type::get( value.type()
//     );

//     //         const std::vector< libcsel_ir::Constant::Ptr > el_args
//     //             = { libstdhl::make< libcsel_ir::BitConstant >(
//     //                     el_ty.results()[ 0 ], ir_cv->value() ),
//     //                 libstdhl::make< libcsel_ir::BitConstant >(
//     //                     el_ty.results()[ 1 ], ir_cv->defined() ) };

//     //         return std::static_pointer_cast< libcsel_ir::Value >(
//     //             libstdhl::make< libcsel_ir::StructureConstant >(
//     //                 el_ty, el_args ) );
//     //     }
//     //     case libcasm_ir::Value::BIT_CONSTANT:
//     //     {
//     //         auto ir_cv = libcasm_ir::cast< libcasm_ir::BitConstant >(
//     value
//     //         );

//     //         libstdhl::Log::info( "RT:Constant: %s", ir_cv->c_str() );

//     //         libcsel_ir::Type& el_ty = libcasm_rt::Type::get( value.type()
//     );

//     //         const std::vector< libcsel_ir::Constant::Ptr > el_args
//     //             = { libstdhl::make< libcsel_ir::BitConstant >(
//     //                     el_ty.results()[ 0 ], ir_cv->value() ),
//     //                 libstdhl::make< libcsel_ir::BitConstant >(
//     //                     el_ty.results()[ 1 ], ir_cv->defined() ) };

//     //         return std::static_pointer_cast< libcsel_ir::Value >(
//     //             libstdhl::make< libcsel_ir::StructureConstant >(
//     //                 el_ty, el_args ) );
//     //     }
//     //     default:
//     //     {
//     //         libstdhl::Log::error(
//     //             " unimplemented constant transformation for '%s' with type
//     "
//     //             "'%s'",
//     //             value.name(), value.type().description() );

//     //         assert( 0 );
//     //         return libstdhl::make< libcsel_ir::VoidConstant >();
//     //     }
//     // }
// }

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
