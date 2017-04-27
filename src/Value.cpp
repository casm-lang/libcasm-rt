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
#include "../casm-ir/src/Value.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Constant.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Module.h"

#include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

libcasm_ir::Constant Value::execute( const libcasm_ir::Value::ID id,
    const libcasm_ir::Type::Ptr& type,
    const std::vector< libcasm_ir::Constant >& operands )
{
    switch( id )
    {
        //
        // General Instruction
        //

        case libcasm_ir::Value::ID::SYMBOLIC_INSTRUCTION:
        {
            // TODO
            return libcasm_ir::BooleanConstant( false );
        }

        case libcasm_ir::Value::ID::CALL_INSTRUCTION:
        {
            // TODO
            return libcasm_ir::BooleanConstant( false );
        }

        //
        // Arithmetic Instruction
        //

        case libcasm_ir::Value::ID::INV_INSTRUCTION:
        {
            assert( operands.size() == 1 );

            const auto operand
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::InvInstruction >( operand );
        }

        case libcasm_ir::Value::ID::ADD_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::AddInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::SUB_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::SubInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::MUL_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::MulInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::DIV_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::DivInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::POW_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::PowInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::MOD_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::ModInstruction >( lhs, rhs );
        }

        //
        // Compare Instruction
        //

        case libcasm_ir::Value::ID::EQU_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::EquInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::NEQ_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::NeqInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::LTH_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::LthInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::LEQ_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::LeqInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::GTH_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::GthInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::GEQ_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::GeqInstruction >( lhs, rhs );
        }

        //
        // Logical Instruction
        //

        case libcasm_ir::Value::ID::OR_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::OrInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::IMP_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::ImpInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::XOR_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::XorInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::AND_INSTRUCTION:
        {
            assert( operands.size() == 2 );

            const auto lhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );
            const auto rhs
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 1 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::XorInstruction >( lhs, rhs );
        }

        case libcasm_ir::Value::ID::NOT_INSTRUCTION:
        {
            assert( operands.size() == 1 );

            const auto operand
                = libstdhl::wrap( (libcasm_ir::Value&)operands[ 0 ] );

            return libcasm_rt::Instruction::
                execute< libcasm_ir::NotInstruction >( operand );
        }

        //
        // General Builtins
        //

        case libcasm_ir::Value::ID::ABORT_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AbortBuiltin >(
                type, operands );
        }

        case libcasm_ir::Value::ID::ASSERT_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AssertBuiltin >(
                type, operands );
        }

        //
        // Output Builtins
        //

        case libcasm_ir::Value::ID::PRINT_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::PrintBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::PRINTLN_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::PrintLnBuiltin >(
                type, operands );
        }

        //
        // Casting Builtins
        //

        case libcasm_ir::Value::ID::AS_BOOLEAN_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AsBooleanBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::AS_INTEGER_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AsIntegerBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::AS_BIT_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AsBitBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::AS_STRING_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AsStringBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::AS_FLOATING_BUILTIN:
        {
            return libcasm_rt::Builtin::
                execute< libcasm_ir::AsFloatingBuiltin >( type, operands );
        }
        case libcasm_ir::Value::ID::AS_RATIONAL_BUILTIN:
        {
            return libcasm_rt::Builtin::
                execute< libcasm_ir::AsRationalBuiltin >( type, operands );
        }
        case libcasm_ir::Value::ID::AS_ENUMERATION_BUILTIN:
        {
            return libcasm_rt::Builtin::
                execute< libcasm_ir::AsEnumerationBuiltin >( type, operands );
        }

        //
        // Stringify Builtins
        //

        case libcasm_ir::Value::ID::DEC_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::DecBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::HEX_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::HexBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::OCT_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::OctBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::BIN_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::BinBuiltin >(
                type, operands );
        }

        //
        // Arithmetic Builtins
        //

        case libcasm_ir::Value::ID::ADDU_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AdduBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::ADDS_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AddsBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::SUBU_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::SubuBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::SUBS_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::SubsBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::MULU_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::MuluBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::MULS_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::MulsBuiltin >(
                type, operands );
        }

        //
        // Compare Builtins
        //

        case libcasm_ir::Value::ID::LESU_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::LesuBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::LESS_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::LessBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::LEQU_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::LequBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::LEQS_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::LeqsBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::GREU_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::GreuBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::GRES_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::GresBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::GEQU_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::GequBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::GEQS_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::GeqsBuiltin >(
                type, operands );
        }

        //
        // Bit Builtins
        //

        case libcasm_ir::Value::ID::ZEXT_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::ZextBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::SEXT_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::SextBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::TRUNC_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::TruncBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::SHL_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::ShlBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::SHR_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::ShrBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::ASHR_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::AshrBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::CLZ_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::ClzBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::CLO_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::CloBuiltin >(
                type, operands );
        }
        case libcasm_ir::Value::ID::CLS_BUILTIN:
        {
            return libcasm_rt::Builtin::execute< libcasm_ir::ClsBuiltin >(
                type, operands );
        }

        // //
        // // Math Builtins
        // //

        // case libcasm_ir::Value::ID::POW_BUILTIN:
        // {
        //     return libcasm_rt::Builtin::execute< libcasm_ir::PowBuiltin >(
        //         type, operands );
        // }
        // case libcasm_ir::Value::ID::RAND_BUILTIN:
        // {
        //     return libcasm_rt::Builtin::execute< libcasm_ir::RandBuiltin >(
        //         type, operands );
        // }

        //
        // Invalid Non-Constant Value IDs to execute
        //

        case libcasm_ir::Value::ID::VALUE:
        case libcasm_ir::Value::ID::VALUE_LIST:
        case libcasm_ir::Value::ID::USER:
        case libcasm_ir::Value::ID::SPECIFICATION:
        case libcasm_ir::Value::ID::AGENT:
        case libcasm_ir::Value::ID::RULE:
        case libcasm_ir::Value::ID::DERIVED:
        case libcasm_ir::Value::ID::FUNCTION:
        case libcasm_ir::Value::ID::ENUMERATION:
        case libcasm_ir::Value::ID::BLOCK:
        case libcasm_ir::Value::ID::EXECUTION_SEMANTICS_BLOCK:
        case libcasm_ir::Value::ID::PARALLEL_BLOCK:
        case libcasm_ir::Value::ID::SEQUENTIAL_BLOCK:
        case libcasm_ir::Value::ID::STATEMENT:
        case libcasm_ir::Value::ID::TRIVIAL_STATEMENT:
        case libcasm_ir::Value::ID::BRANCH_STATEMENT:
        case libcasm_ir::Value::ID::CONSTANT:
        case libcasm_ir::Value::ID::VOID_CONSTANT:
        case libcasm_ir::Value::ID::RULE_REFERENCE_CONSTANT:
        case libcasm_ir::Value::ID::BOOLEAN_CONSTANT:
        case libcasm_ir::Value::ID::INTEGER_CONSTANT:
        case libcasm_ir::Value::ID::BIT_CONSTANT:
        case libcasm_ir::Value::ID::STRING_CONSTANT:
        case libcasm_ir::Value::ID::FLOATING_CONSTANT:
        case libcasm_ir::Value::ID::RATIONAL_CONSTANT:
        case libcasm_ir::Value::ID::ENUMERATION_CONSTANT:
        case libcasm_ir::Value::ID::IDENTIFIER:
        case libcasm_ir::Value::ID::INSTRUCTION:
        case libcasm_ir::Value::ID::UNARY_INSTRUCTION:
        case libcasm_ir::Value::ID::BINARY_INSTRUCTION:
        case libcasm_ir::Value::ID::ASSERT_INSTRUCTION:
        case libcasm_ir::Value::ID::SELECT_INSTRUCTION:
        case libcasm_ir::Value::ID::SKIP_INSTRUCTION:
        case libcasm_ir::Value::ID::FORK_INSTRUCTION:
        case libcasm_ir::Value::ID::MERGE_INSTRUCTION:
        case libcasm_ir::Value::ID::LOOKUP_INSTRUCTION:
        case libcasm_ir::Value::ID::UPDATE_INSTRUCTION:
        case libcasm_ir::Value::ID::LOCATION_INSTRUCTION:
        case libcasm_ir::Value::ID::LOCAL_INSTRUCTION:
        case libcasm_ir::Value::ID::OPERATOR_INSTRUCTION:
        case libcasm_ir::Value::ID::ARITHMETIC_INSTRUCTION:
        case libcasm_ir::Value::ID::COMPARE_INSTRUCTION:
        case libcasm_ir::Value::ID::LOGICAL_INSTRUCTION:
        case libcasm_ir::Value::ID::BUILTIN:
        case libcasm_ir::Value::ID::GENERAL_BUILTIN:
        case libcasm_ir::Value::ID::OUTPUT_BUILTIN:
        case libcasm_ir::Value::ID::CASTING_BUILTIN:
        case libcasm_ir::Value::ID::STRINGIFY_BUILTIN:
        case libcasm_ir::Value::ID::OPERATOR_BUILTIN:
        case libcasm_ir::Value::ID::ARITHMETIC_BUILTIN:
        case libcasm_ir::Value::ID::COMPARE_BUILTIN:
        case libcasm_ir::Value::ID::BIT_BUILTIN:
        // case libcasm_ir::Value::ID::MATH_BUILTIN:
        case libcasm_ir::Value::ID::_SIZE_:
        {
            // invalid for constant instruction evaluation
            break;
        }
    }

    assert( !" internal error " );
    return libcasm_ir::VoidConstant();
}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

static libcasm_ir::Value::Ptr execute(
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

// static libcsel_ir::Value* get(
//     libcasm_ir::Value& value, libcsel_ir::Module* context )
// {
//     switch( value.id() )
//     {
//         case libcasm_ir::Value::AS_BOOLEAN_BUILTIN:
//         {
//             return Builtin::asBoolean( value, context );
//         }

//         // AS_INTEGER_BUILTIN,
//         // AS_BIT_BUILTIN,
//         // AS_STRING_BUILTIN,
//         // AS_FLOATING_BUILTIN,
//         // AS_RATIONAL_BUILTIN,
//         // AS_ENUMERATION_BUILTIN,

//         case libcasm_ir::Value::EQU_INSTRUCTION:
//         {
//             return Instruction::Equ(
//                 static_cast< libcasm_ir::EquInstruction& >( value ), context
//                 );
//         }
//         case libcasm_ir::Value::NOT_INSTRUCTION:
//         {
//             return Instruction::Not(
//                 static_cast< libcasm_ir::NotInstruction& >( value ), context
//                 );
//         }

//         default:
//         {
//             libstdhl::Log::error(
//                 " unsupported value '%s' of type '%s' to create RT instance",
//                 value.name().c_str(), value.type().name().c_str() );
//             assert( 0 );
//             return 0;
//         }
//     }
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
