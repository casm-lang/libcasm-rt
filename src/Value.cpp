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

#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Type.h"
#include "../casm-ir/src/Value.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Constant.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Module.h"

#include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

libcasm_ir::Value* Value::execute(
    libcasm_ir::Instruction& value, libcsel_ir::Module* module )
{
    libstdhl::Log::info( "%s: %s", __FUNCTION__, value.c_str() );

    // CACHING MECHANISM!!!
    // // static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
    // // cache;

    // std::string key = "";
    // key += value.name();
    // key += " ";
    // key += value.type().name();

    // // auto result = cache.find( key );
    // // if( result != cache.end() )
    // // {
    // //     libstdhl::Log::info( "found!" );
    // //     return result->second;
    // // }

    libcsel_ir::Value* ir_instr_impl = 0;

    u32 operand_pos = 0;

    if( auto call = libcasm_ir::cast< libcasm_ir::CallInstruction >( value ) )
    {
        // PPA: assuming a builtin call for now
        ir_instr_impl = &Value::get( call->callee() );
        operand_pos = 1;
    }
    else if( libcasm_ir::isa< libcasm_ir::OperatorInstruction >( value ) )
    {
        ir_instr_impl = &Value::get( value );
    }
    else
    {
        libstdhl::Log::error(
            " unsupported value '%s' with type '%s' to execute", value.name(),
            value.type().description() );
        assert( 0 );
        return 0;
    }

    libcsel_ir::CallInstruction* el_instr_impl
        = new libcsel_ir::CallInstruction( ir_instr_impl );

    for( ; operand_pos < value.values().size(); operand_pos++ )
    {
        auto v = value.value( operand_pos );
        assert( libcasm_ir::isa< libcasm_ir::Constant >( v ) );
        auto c = &Constant::get( *v );

        libstdhl::Log::info( "%s: operand %u:\n    %s --> %s", __FUNCTION__,
            operand_pos, v->c_str(), c->c_str() );
        // add constant to instr call
        el_instr_impl->add( c );
    }

    for( auto res : ir_instr_impl->type().results() )
    {
        libstdhl::Log::info(
            "%s: alloc result register:\n    %s", __FUNCTION__, res->name() );
        // alloc result registers
        el_instr_impl->add( new libcsel_ir::AllocInstruction( res ) );
    }

    libstdhl::Log::info( "%s: %s %s", __FUNCTION__, el_instr_impl->c_str() );

    libcsel_ir::Value* result
        = libcsel_rt::Instruction::execute( *el_instr_impl );

    switch( result->id() )
    {
        case libcsel_ir::Value::STRUCTURE_CONSTANT:
        {
            auto& str_val
                = static_cast< libcsel_ir::StructureConstant& >( *result );

            auto& ty_res = result->type().results();
            assert( ty_res.size() == 2 );

            if( ty_res[ 0 ]->isBit() and ty_res[ 0 ]->bitsize() == 1
                and ty_res[ 1 ]->isBit()
                and ty_res[ 1 ]->bitsize() == 1 )
            {
                // we found a boolean!
                libcsel_ir::BitConstant& v
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 0 ] );
                libcsel_ir::BitConstant& d
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 1 ] );

                if( d.value() )
                {
                    return libcasm_ir::Constant::Boolean( v.value() );
                }
                else
                {
                    return libcasm_ir::Constant::Undef(
                        libcasm_ir::Type::Boolean() );
                }
            }
            else if( ty_res[ 0 ]->isBit() and ty_res[ 0 ]->bitsize() == 64
                     and ty_res[ 1 ]->isBit()
                     and ty_res[ 1 ]->bitsize() == 1 )
            {
                // we found an integer!
                libcsel_ir::BitConstant& v
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 0 ] );
                libcsel_ir::BitConstant& d
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 1 ] );

                if( d.value() )
                {
                    return libcasm_ir::Constant::Integer( v.value() );
                }
                else
                {
                    return libcasm_ir::Constant::Undef(
                        libcasm_ir::Type::Integer() );
                }
            }
            else
            {
                libstdhl::Log::error(
                    " unsupported result value '%s' of type '%s' ",
                    result->name(), result->type().name() );
            }
            break;
        }
        default:
        {
            libstdhl::Log::error(
                " unsupported result value '%s' of type '%s' ", result->name(),
                result->type().name() );
            break;
        }
    }

    assert( 0 );
    return 0;
}

libcsel_ir::Value& Value::get(
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

        default:
        {
            libstdhl::Log::error(
                " unsupported value '%s' of type '%s' to create RT instance",
                value.name(), value.type().name() );
            assert( 0 );
            return *libcsel_ir::Constant::NIL();
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
