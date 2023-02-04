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

/**
   @brief    TODO

   TODO
*/

#ifndef _LIBCASM_RT_INSTRUCTION_H_
#define _LIBCASM_RT_INSTRUCTION_H_

#include <libcasm-rt/CasmRT>
#include <libcasm-rt/Value>

#include <libcasm-ir/Instruction>

namespace libcasm_rt
{
    namespace Instruction
    {
        void execute(
            const libcasm_ir::InvInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs );

        void execute(
            const libcasm_ir::AddInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::SubInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::MulInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::ModInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::DivInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::PowInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::AndInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::XorInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::OrInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::ImpInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::NotInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs );

        void execute(
            const libcasm_ir::EquInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::NeqInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::LthInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::LeqInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::GthInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::GeqInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant& lhs,
            const libcasm_ir::Constant& rhs );

        void execute(
            const libcasm_ir::CallInstruction& instr,
            libcasm_ir::Constant& res,
            const libcasm_ir::Constant* reg,
            const std::size_t size );

        template < typename T, typename... Args >
        inline void execute(
            const libcasm_ir::Type::Ptr& type, libcasm_ir::Constant& res, Args&&... args )
        {
            const T instr( type );
            execute( instr, res, std::forward< Args >( args )... );
            assert( instr.type().result() == res.type() );
        }

        libcasm_ir::Constant::Ptr execute( const libcasm_ir::Instruction& instr );
    }
}

#endif  // _LIBCASM_RT_INSTRUCTION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
