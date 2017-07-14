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
        void execute( const libcasm_ir::InvInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs );

        void execute( const libcasm_ir::AddInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::SubInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::MulInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::ModInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::DivInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::PowInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::AndInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::XorInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::OrInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::ImpInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::NotInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs );

        void execute( const libcasm_ir::EquInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::NeqInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::LthInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::LeqInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::GthInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::GeqInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute( const libcasm_ir::CallInstruction& instr,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* reg,
            const std::size_t size );

        template < typename T, typename... Args >
        inline void execute( const libcasm_ir::Type::Ptr& type,
            libcasm_ir::Constant& res, Args&&... args )
        {
            const T instr( type );
            execute( instr, res, std::forward< Args >( args )... );
            assert( instr.type().result() == res.type() );
        }

        libcasm_ir::Constant::Ptr execute(
            const libcasm_ir::Instruction& instr );
    }
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
