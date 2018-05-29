//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                <https://github.com/casm-lang/libcasm-rt>
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

#include "Value.h"

#include "Builtin.h"
#include "Constant.h"
#include "Instruction.h"
#include "Type.h"

#include <libstdhl/Log>

#include <libcasm-ir/Builtin>
#include <libcasm-ir/Constant>
#include <libcasm-ir/Instruction>
#include <libcasm-ir/Type>
#include <libcasm-ir/Value>

// #include "../csel-ir/src/CallableUnit.h"
// #include "../csel-ir/src/Constant.h"
// #include "../csel-ir/src/Instruction.h"
// #include "../csel-ir/src/Module.h"

// #include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

void Value::execute(
    const libcasm_ir::Value::ID id,
    const libcasm_ir::Type::Ptr& type,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant& lhs )
{
    switch( id )
    {
            //
            // General Instruction
            //

        case libcasm_ir::Value::ID::CALL_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::CallInstruction >( type, res, &lhs, 1 );
            break;
        }

            //
            // Arithmethic Instruction
            //

        case libcasm_ir::Value::ID::INV_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::InvInstruction >( type, res, lhs );
            break;
        }

            //
            // Logical Instruction
            //

        case libcasm_ir::Value::ID::NOT_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::NotInstruction >( type, res, lhs );
            break;
        }

            //
            // General Builtins
            //

        case libcasm_ir::Value::ID::IS_SYMBOLIC_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::IsSymbolicBuiltin >( type, res, &lhs, 1 );
            break;
        }

        case libcasm_ir::Value::ID::ASSERT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AssertBuiltin >( type, res, &lhs, 1 );
            break;
        }

        case libcasm_ir::Value::ID::ASSURE_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AssureBuiltin >( type, res, &lhs, 1 );
            break;
        }

        case libcasm_ir::Value::ID::SIZE_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::SizeBuiltin >( type, res, &lhs, 1 );
            break;
        }

            //
            // Output Builtins
            //

        case libcasm_ir::Value::ID::PRINT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::PrintBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::PRINTLN_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::PrintLnBuiltin >( type, res, &lhs, 1 );
            break;
        }

            //
            // Casting Builtins
            //

        case libcasm_ir::Value::ID::AS_BOOLEAN_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsBooleanBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::AS_INTEGER_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsIntegerBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::AS_BINARY_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsBinaryBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::AS_STRING_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsStringBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::AS_DECIMAL_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsDecimalBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::AS_RATIONAL_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsRationalBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::AS_ENUMERATION_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsEnumerationBuiltin >( type, res, &lhs, 1 );
            break;
        }

            //
            // Stringify Builtins
            //

        case libcasm_ir::Value::ID::DEC_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::DecBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::HEX_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::HexBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::OCT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::OctBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::BIN_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::BinBuiltin >( type, res, &lhs, 1 );
            break;
        }

            //
            // Binary Builtins
            //

        case libcasm_ir::Value::ID::CLZ_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::ClzBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::CLO_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::CloBuiltin >( type, res, &lhs, 1 );
            break;
        }
        case libcasm_ir::Value::ID::CLS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::ClsBuiltin >( type, res, &lhs, 1 );
            break;
        }

        default:
        {
            // invalid for constant instruction evaluation
            assert( !" invalid ID to 'execute( res, lhs )' found! " );
            break;
        }
    }
}

void Value::execute(
    const libcasm_ir::Value::ID id,
    const libcasm_ir::Type::Ptr& type,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    switch( id )
    {
        case libcasm_ir::Value::ID::CALL_INSTRUCTION:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Instruction::execute< libcasm_ir::CallInstruction >( type, res, reg, 2 );
            break;
        }

            //
            // Arithmetic Instruction
            //

        case libcasm_ir::Value::ID::ADD_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::AddInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::SUB_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::SubInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::MUL_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::MulInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::DIV_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::DivInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::POW_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::PowInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::MOD_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::ModInstruction >( type, res, lhs, rhs );
            break;
        }

            //
            // Compare Instruction
            //

        case libcasm_ir::Value::ID::EQU_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::EquInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::NEQ_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::NeqInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::LTH_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::LthInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::LEQ_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::LeqInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::GTH_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::GthInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::GEQ_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::GeqInstruction >( type, res, lhs, rhs );
            break;
        }

            //
            // Logical Instruction
            //

        case libcasm_ir::Value::ID::OR_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::OrInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::IMP_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::ImpInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::XOR_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::XorInstruction >( type, res, lhs, rhs );
            break;
        }
        case libcasm_ir::Value::ID::AND_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::AndInstruction >( type, res, lhs, rhs );
            break;
        }

            //
            // General Builtins
            //

            //
            // Arithmetic Builtins
            //

        case libcasm_ir::Value::ID::ADDU_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::AdduBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::ADDS_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::AddsBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::SUBU_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::SubuBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::SUBS_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::SubsBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::MULU_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::MuluBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::MULS_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::MulsBuiltin >( type, res, reg, 2 );
            break;
        }

            //
            // Compare Builtins
            //

        case libcasm_ir::Value::ID::LESU_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::LesuBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::LESS_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::LessBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::LEQU_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::LequBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::LEQS_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::LeqsBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::GREU_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::GreuBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::GRES_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::GresBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::GEQU_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::GequBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::GEQS_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::GeqsBuiltin >( type, res, reg, 2 );
            break;
        }

            //
            // Binary Builtins
            //

        case libcasm_ir::Value::ID::ZEXT_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::ZextBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::SEXT_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::SextBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::TRUNC_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::TruncBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::SHL_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::ShlBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::SHR_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::ShrBuiltin >( type, res, reg, 2 );
            break;
        }
        case libcasm_ir::Value::ID::ASHR_BUILTIN:
        {
            const libcasm_ir::Constant reg[] = { lhs, rhs };
            libcasm_rt::Builtin::execute< libcasm_ir::AshrBuiltin >( type, res, reg, 2 );
            break;
        }

        default:
        {
            // invalid for constant instruction evaluation
            assert( !" invalid ID to 'execute( res, lhs, rhs )' found! " );
            break;
        }
    }
}

void Value::execute(
    const libcasm_ir::Value::ID id,
    const libcasm_ir::Type::Ptr& type,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* reg,
    const std::size_t size )
{
    switch( id )
    {
        case libcasm_ir::Value::ID::CALL_INSTRUCTION:
        {
            libcasm_rt::Instruction::execute< libcasm_ir::CallInstruction >( type, res, reg, size );
            break;
        }

            //
            // General Builtins
            //

        case libcasm_ir::Value::ID::ABORT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AbortBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::IS_SYMBOLIC_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::IsSymbolicBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::ASSERT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AssertBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::ASSURE_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AssureBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::SIZE_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::SizeBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::AT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AtBuiltin >( type, res, reg, size );
            break;
        }

            //
            // Output Builtins
            //

        case libcasm_ir::Value::ID::PRINT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::PrintBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::PRINTLN_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::PrintLnBuiltin >( type, res, reg, size );
            break;
        }

            //
            // Casting Builtins
            //

        case libcasm_ir::Value::ID::AS_BOOLEAN_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsBooleanBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::AS_INTEGER_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsIntegerBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::AS_BINARY_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsBinaryBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::AS_STRING_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsStringBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::AS_DECIMAL_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsDecimalBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::AS_RATIONAL_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsRationalBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::AS_ENUMERATION_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AsEnumerationBuiltin >(
                type, res, reg, size );
            break;
        }

            //
            // Stringify Builtins
            //

        case libcasm_ir::Value::ID::DEC_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::DecBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::HEX_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::HexBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::OCT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::OctBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::BIN_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::BinBuiltin >( type, res, reg, size );
            break;
        }
            //
            // Arithmetic Builtins
            //

        case libcasm_ir::Value::ID::ADDU_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AdduBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::ADDS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AddsBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::SUBU_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::SubuBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::SUBS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::SubsBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::MULU_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::MuluBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::MULS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::MulsBuiltin >( type, res, reg, size );
            break;
        }

            //
            // Compare Builtins
            //

        case libcasm_ir::Value::ID::LESU_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::LesuBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::LESS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::LessBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::LEQU_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::LequBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::LEQS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::LeqsBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::GREU_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::GreuBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::GRES_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::GresBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::GEQU_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::GequBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::GEQS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::GeqsBuiltin >( type, res, reg, size );
            break;
        }

            //
            // Binary Builtins
            //

        case libcasm_ir::Value::ID::ZEXT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::ZextBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::SEXT_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::SextBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::TRUNC_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::TruncBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::SHL_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::ShlBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::SHR_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::ShrBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::ASHR_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::AshrBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::CLZ_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::ClzBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::CLO_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::CloBuiltin >( type, res, reg, size );
            break;
        }
        case libcasm_ir::Value::ID::CLS_BUILTIN:
        {
            libcasm_rt::Builtin::execute< libcasm_ir::ClsBuiltin >( type, res, reg, size );
            break;
        }

            // //
            // // Math Builtins
            // //

            // case libcasm_ir::Value::ID::POW_BUILTIN:
            // {
            //     libcasm_rt::Builtin::execute< libcasm_ir::PowBuiltin
            //     >(
            //         type, res, reg, size );
            // break;
            // }
            // case libcasm_ir::Value::ID::RAND_BUILTIN:
            // {
            //     libcasm_rt::Builtin::execute< libcasm_ir::RandBuiltin
            //     >(
            //         type, res, reg, size );
            // break;
            // }

        default:
        {
            assert( !" invalid ID to 'execute( res, reg*, size )' found! " );
            break;
        }
    }
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

// static libcasm_ir::Value::Ptr execute(
//     libcasm_ir::Instruction& value, libcsel_ir::Module* module )
// {
//     return libstdhl::get< libcasm_ir::VoidConstant >();

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
// }

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
//         // AS_DECIMAL_BUILTIN,
//         // AS_RATIONAL_BUILTIN,
//         // AS_ENUMERATION_BUILTIN,

//         case libcasm_ir::Value::EQU_INSTRUCTION:
//         {
//             return Instruction::Equ(
//                 static_cast< libcasm_ir::EquInstruction& >( value ),
//                 context
//                 );
//         }
//         case libcasm_ir::Value::NOT_INSTRUCTION:
//         {
//             return Instruction::Not(
//                 static_cast< libcasm_ir::NotInstruction& >( value ),
//                 context
//                 );
//         }

//         default:
//         {
//             libstdhl::Log::error(
//                 " unsupported value '%s' of type '%s' to create RT
//                 instance",
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
