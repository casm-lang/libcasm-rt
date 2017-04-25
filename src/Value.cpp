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

#include "Value.h"

#include "Builtin.h"
#include "Constant.h"
#include "Instruction.h"
#include "Type.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Constant.h"
#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Type.h"
#include "../casm-ir/src/Value.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Constant.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Module.h"

#include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

libcasm_ir::Value::Ptr Value::execute(
    libcasm_ir::Instruction& value, libcsel_ir::Module* module )
{
    return libstdhl::get< libcasm_ir::VoidConstant >();

    // libstdhl::Log::info( "%s: %s", __FUNCTION__, value.c_str() );

    // libcsel_ir::Value* ir_instr_impl = 0;

    // u32 operand_pos = 0;

    // if( auto call = libcasm_ir::cast< libcasm_ir::CallInstruction >( value )
    // )
    // {
    //     // PPA: assuming a builtin call for now
    //     ir_instr_impl = Value::get( call->callee() );
    //     operand_pos = 1;
    // }
    // else if( libcasm_ir::isa< libcasm_ir::OperatorInstruction >( value ) )
    // {
    //     ir_instr_impl = Value::get( value );
    // }
    // else
    // {
    //     libstdhl::Log::error(
    //         " unsupported value '%s' with type '%s' to execute",
    //         value.name(),
    //         value.type().description() );
    //     assert( 0 );
    //     return nullptr;
    // }

    // std::vector< libcsel_ir::Value::Ptr > stack;

    // for( ; operand_pos < value.values().size(); operand_pos++ )
    // {
    //     auto v = value.value( operand_pos );
    //     assert( libcasm_ir::isa< libcasm_ir::Constant >( v ) );

    //     stack.push_back( Constant::get( *v ) );

    //     libstdhl::Log::info( "%s: operand %u:\n    %s --> %s", __FUNCTION__,
    //         operand_pos, v->c_str(), stack.back()->c_str() );

    //     // // add constant to instr call
    //     // el_instr_impl.add( &c );
    // }

    // for( auto res : ir_instr_impl->type().results() )
    // {
    //     libstdhl::Log::info(
    //         "%s: alloc result register:\n    %s", __FUNCTION__, res->name()
    //         );
    //     // // alloc result registers
    //     // el_instr_impl.add( new libcsel_ir::AllocInstruction( res ) );

    //     stack.push_back( libstdhl::make< libcsel_ir::Value >(
    //         libcsel_ir::AllocInstruction( res ) ) );
    // }

    // libcsel_ir::CallInstruction el_instr_impl( ir_instr_impl, stack );

    // libstdhl::Log::info( "%s: %s %s", __FUNCTION__, el_instr_impl.c_str() );

    // auto result = libcsel_rt::Instruction::execute( el_instr_impl );

    // switch( result->id() )
    // {
    //     case libcsel_ir::Value::STRUCTURE_CONSTANT:
    //     {
    //         auto res
    //             = static_cast< libcsel_ir::StructureConstant* >( result.get()
    //             );

    //         auto ty_res = result->type().results();
    //         assert( ty_res.size() == 2 );

    //         if( ty_res[ 0 ]->isBit() and ty_res[ 0 ]->bitsize() == 1
    //             and ty_res[ 1 ]->isBit()
    //             and ty_res[ 1 ]->bitsize() == 1 )
    //         {
    //             // we found a boolean!
    //             auto v = static_cast< libcsel_ir::BitConstant* >(
    //                 res->value()[ 0 ].get() );
    //             auto d = static_cast< libcsel_ir::BitConstant* >(
    //                 res->value()[ 1 ].get() );

    //             if( d->value() )
    //             {
    //                 return libstdhl::make< libcasm_ir::BooleanConstant >(
    //                     v->value() );
    //             }
    //             else
    //             {
    //                 return libstdhl::make< libcasm_ir::BooleanConstant >();
    //             }
    //         }
    //         else if( ty_res[ 0 ]->isBit() and ty_res[ 0 ]->bitsize() == 64
    //                  and ty_res[ 1 ]->isBit()
    //                  and ty_res[ 1 ]->bitsize() == 1 )
    //         {
    //             // we found a integer!
    //             auto v = static_cast< libcsel_ir::BitConstant* >(
    //                 res->value()[ 0 ].get() );
    //             auto d = static_cast< libcsel_ir::BitConstant* >(
    //                 res->value()[ 1 ].get() );

    //             if( d->value() )
    //             {
    //                 return libstdhl::make< libcasm_ir::IntegerConstant >(
    //                     v->value() );
    //             }
    //             else
    //             {
    //                 return libstdhl::make< libcasm_ir::IntegerConstant >();
    //             }
    //         }
    //         else
    //         {
    //             libstdhl::Log::error(
    //                 " unsupported result value '%s' of type '%s' ",
    //                 result->name(), result->type().name() );

    //             assert( 0 );
    //             return nullptr;
    //         }
    //         break;
    //     }
    //     default:
    //     {
    //         libstdhl::Log::error(
    //             " unsupported result value '%s' of type '%s' ",
    //             result->name(),
    //             result->type().name() );

    //         assert( 0 );
    //         return nullptr;
    //     }
    // }
}

libcsel_ir::Value* Value::get(
    libcasm_ir::Value& value, libcsel_ir::Module* context )
{
    switch( value.id() )
    {
        case libcasm_ir::Value::AS_BOOLEAN_BUILTIN:
        {
            return Builtin::asBoolean( value, context );
        }

        // AS_INTEGER_BUILTIN,
        // AS_BIT_BUILTIN,
        // AS_STRING_BUILTIN,
        // AS_FLOATING_BUILTIN,
        // AS_RATIONAL_BUILTIN,
        // AS_ENUMERATION_BUILTIN,

        case libcasm_ir::Value::EQU_INSTRUCTION:
        {
            return Instruction::Equ(
                static_cast< libcasm_ir::EquInstruction& >( value ), context );
        }
        case libcasm_ir::Value::NOT_INSTRUCTION:
        {
            return Instruction::Not(
                static_cast< libcasm_ir::NotInstruction& >( value ), context );
        }

        default:
        {
            libstdhl::Log::error(
                " unsupported value '%s' of type '%s' to create RT instance",
                value.name().c_str(), value.type().name().c_str() );
            assert( 0 );
            return 0;
        }
    }
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
