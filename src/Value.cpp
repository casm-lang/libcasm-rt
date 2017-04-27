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

#include "../casm-ir/src/Builtin.h"
#include "../casm-ir/src/Constant.h"
#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Type.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Constant.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Module.h"

#include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

libcasm_ir::Constant Value::execute(
    libcasm_ir::Instruction& value, libcsel_ir::Module* module )
{
    libstdhl::Log::info( "%s: %s", __FUNCTION__, value.dump().c_str() );

    u32 operand_pos = 0;
    libcsel_ir::Value::Ptr ir_instr_impl = nullptr;

    if( auto call = libcasm_ir::cast< libcasm_ir::CallInstruction >( value ) )
    {
        // PPA: assuming a builtin call for now
        ir_instr_impl = Value::get( *call->callee().get() );
        operand_pos = 1;
    }
    else if( libcasm_ir::isa< libcasm_ir::OperatorInstruction >( value ) )
    {
        ir_instr_impl = Value::get( value );
    }
    else
    {
        libstdhl::Log::error(
            " unsupported value '%s' with type '%s' to execute",
            value.name().c_str(), value.type().description().c_str() );
        assert( 0 );
        return libcasm_ir::VoidConstant();
    }

    std::vector< libcsel_ir::Constant > stack;
    std::vector< libcsel_ir::Value::Ptr > args;

    for( ; operand_pos < value.operands().size(); operand_pos++ )
    {
        const auto v = value.operand( operand_pos );
        assert( libcasm_ir::isa< libcasm_ir::Constant >( v ) );

        stack.push_back( Constant::get( *v.get() ) );
        args.push_back( libstdhl::wrap( stack.back() ) );

        libstdhl::Log::info( "%s: operand %u:\n    %s --> %s", __FUNCTION__,
            operand_pos, v->dump().c_str(), args.back()->name().c_str() );

        // // add constant to instr call
        // el_instr_impl.add( &c );
    }

    for( auto res : ir_instr_impl->type().results() )
    {
        libstdhl::Log::info( "%s: alloc result register:\n    %s", __FUNCTION__,
            res->name().c_str() );
        // // alloc result registers

        args.push_back( libstdhl::make< libcsel_ir::AllocInstruction >( res ) );
    }

    auto i = libcsel_ir::CallInstruction( ir_instr_impl, args );

    libstdhl::Log::info( "%s: %s %s", __FUNCTION__, i.dump().c_str() );

    const auto result = libcsel_rt::Instruction::execute( i );

    const auto result_types = result.type().results();
    assert( result.type().isStructure() );
    assert( result_types.size() == 2 );

    const auto s
        = static_cast< const libcsel_ir::StructureConstant& >( result );

    const auto t0 = result_types[ 0 ];
    const auto t1 = result_types[ 1 ];

    switch( value.type().id() )
    {
        case libcasm_ir::Type::BOOLEAN:
        {
            assert( t0->isBit() and t0->bitsize() == 1 );
            assert( t1->isBit() and t1->bitsize() == 1 );
            const auto v = static_cast< const libcsel_ir::BitConstant& >(
                s.value()[ 0 ] );
            const auto d = static_cast< const libcsel_ir::BitConstant& >(
                s.value()[ 1 ] );

            if( d.value()[ 0 ] )
            {
                return libcasm_ir::BooleanConstant( v.value()[ 0 ] );
            }
            else
            {
                return libcasm_ir::BooleanConstant();
            }
        }
        case libcasm_ir::Type::INTEGER:
        {
            assert( t0->isBit() and t0->bitsize() == 64 );
            assert( t1->isBit() and t1->bitsize() == 1 );
            const auto v = static_cast< const libcsel_ir::BitConstant& >(
                s.value()[ 0 ] );
            const auto d = static_cast< const libcsel_ir::BitConstant& >(
                s.value()[ 1 ] );

            if( d.value()[ 0 ] )
            {
                return libcasm_ir::IntegerConstant( v.value()[ 0 ] );
            }
            else
            {
                return libcasm_ir::IntegerConstant();
            }
        }
        default:
        {
            libstdhl::Log::error(
                " unsupported result value '%s' of type '%s' ",
                result.name().c_str(), result.type().name().c_str() );
            assert( 0 );
            return libcasm_ir::VoidConstant();
        }
    }
}

libcsel_ir::Value::Ptr Value::get(
    const libcasm_ir::Value& value, libcsel_ir::Module* context )
{
    switch( value.id() )
    {
        case libcasm_ir::Value::AS_BOOLEAN_BUILTIN:
        {
            return Builtin::asBoolean(
                static_cast< const libcasm_ir::AsBooleanBuiltin& >( value ),
                context );
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
                static_cast< const libcasm_ir::EquInstruction& >( value ),
                context );
        }
        case libcasm_ir::Value::NOT_INSTRUCTION:
        {
            return Instruction::Not(
                static_cast< const libcasm_ir::NotInstruction& >( value ),
                context );
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
