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

/**
   @brief    TODO

   TODO
*/

#ifndef _LIB_CASMRT_INSTRUCTION_H_
#define _LIB_CASMRT_INSTRUCTION_H_

#include "CasmRT.h"

#include "Value.h"

#include "../casm-ir/src/Instruction.h"

namespace libcasm_rt
{
    namespace Instruction
    {
        libcasm_ir::Constant execute( const libcasm_ir::InvInstruction& instr,
            const libcasm_ir::Constant& lhs );

        libcasm_ir::Constant execute( const libcasm_ir::AddInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::SubInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::MulInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::ModInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::DivInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::PowInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::AndInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::XorInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::OrInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::ImpInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::NotInstruction& instr,
            const libcasm_ir::Constant& lhs );

        libcasm_ir::Constant execute( const libcasm_ir::EquInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::NeqInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::LthInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::LeqInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::GthInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::GeqInstruction& instr,
            const libcasm_ir::Constant& lhs, const libcasm_ir::Constant& rhs );

        libcasm_ir::Constant execute( const libcasm_ir::CallInstruction& instr,
            const libcasm_ir::Constant* operands, const std::size_t size );

        template < typename T, typename... Args >
        inline libcasm_ir::Constant execute(
            const libcasm_ir::Type::Ptr& type, Args&&... args )
        {
            const T instr( type );
            const auto result
                = execute( instr, std::forward< Args >( args )... );
            assert( instr.type().result() == result.type() );
            return result;
        }

        libcasm_ir::Constant::Ptr execute(
            const libcasm_ir::Instruction& instr );
    };
}

#endif // _LIB_CASMRT_INSTRUCTION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
