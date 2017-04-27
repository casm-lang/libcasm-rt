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

// template < typename T, typename... TT >
// struct over_all
// {
//     using next = over_all< TT... >;

//     static const constexpr std::size_t size = 1 + next::size;

//     template < typename C >
//     inline constexpr static C for_each( C cbk, T&& tval, TT&&... ttval )
//     {
//         cbk( std::forward< T >( tval ) );
//         next::for_each( cbk, std::forward< TT >( ttval )... );
//         return cbk;
//     }

//     template < typename C >
//     inline constexpr C operator()( C cbk, T&& tval, TT&&... ttval ) const
//     {
//         return for_each(
//             cbk, std::forward< T >( tval ), std::forward< TT >( ttval )... );
//     }
// };

// template < typename T >
// struct over_all< T >
// {
//     static const constexpr std::size_t size = 1;

//     template < typename C >
//     inline constexpr static C for_each( C cbk, T&& tval )
//     {
//         cbk( std::forward< T >( tval ) );
//         return cbk;
//     }

//     template < typename C >
//     inline constexpr C operator()( C cbk, T&& tval ) const
//     {
//         return for_each( cbk, std::forward< T >( tval ) );
//     }
// };
//             constexpr auto size = over_all< Args... >::size;

//             std::vector< libcasm_ir::Value::Ptr > operands;
//             operands.reserve( size );

//             over_all< Args... >::for_each(
//                 [&]( auto&& val ) { operands( libstdhl::wrap( val ) ); },
//                 std::forward< Args >( args )... );

namespace libcasm_rt
{
    namespace Instruction
    {
        libcasm_ir::Constant execute(
            const libcasm_ir::SymbolicInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::InvInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::AddInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::SubInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::MulInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::ModInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::DivInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::PowInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::AndInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::XorInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::OrInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::ImpInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::NotInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::EquInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::NeqInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::LthInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::LeqInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::GthInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::GeqInstruction& value ) noexcept;

        libcasm_ir::Constant execute(
            const libcasm_ir::CallInstruction& value );

        template < typename T, typename... Args >
        inline libcasm_ir::Constant execute( Args&&... args )
        {
            const T instr( std::forward< Args >( args )... );
            return execute( instr );
        }

        libcasm_ir::Constant::Ptr execute(
            const libcasm_ir::Instruction& value );
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
