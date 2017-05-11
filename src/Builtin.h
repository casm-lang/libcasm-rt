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

#ifndef _LIB_CASMRT_BUILTIN_H_
#define _LIB_CASMRT_BUILTIN_H_

#include "CasmRT.h"

#include "Instruction.h"

#include "../casm-ir/src/Builtin.h"

namespace libcasm_rt
{
    namespace Builtin
    {
        libcasm_ir::Constant execute(
            const libcasm_ir::IsSymbolicBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::AbortBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::AssertBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::PrintBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::PrintLnBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute(
            const libcasm_ir::AsBooleanBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute(
            const libcasm_ir::AsIntegerBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::AsBitBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute(
            const libcasm_ir::AsStringBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute(
            const libcasm_ir::AsFloatingBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute(
            const libcasm_ir::AsRationalBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute(
            const libcasm_ir::AsEnumerationBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::DecBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::HexBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::OctBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::BinBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::AdduBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::AddsBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::SubuBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::SubsBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::MuluBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::MulsBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::LesuBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::LessBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::LequBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::LeqsBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::GreuBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::GresBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::GequBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::GeqsBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::ZextBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::SextBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::TruncBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::ShlBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::ShrBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::AshrBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::ClzBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::CloBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        libcasm_ir::Constant execute( const libcasm_ir::ClsBuiltin& builtin,
            const libcasm_ir::Constant* operands, const std::size_t size );

        // libcasm_ir::Constant execute( const libcasm_ir::PowBuiltin& builtin
        // );

        // libcasm_ir::Constant execute( const libcasm_ir::RandBuiltin& builtin
        // );

        template < typename T >
        inline libcasm_ir::Constant execute( const libcasm_ir::Type::Ptr& type,
            const libcasm_ir::Constant* operands, const std::size_t size )
        {
            const T builtin( type );
            assert( builtin.type().arguments().size() == size );
            const auto result = execute( builtin, operands, size );
            assert( builtin.type().result() == result.type() );
            return result;
        }

        template < typename T >
        inline libcasm_ir::Constant execute( const libcasm_ir::Type& type,
            const libcasm_ir::Constant* operands, const std::size_t size )
        {
            const auto t = libstdhl::wrap( (libcasm_ir::Type&)type );
            return execute< T >( t, operands, size );
        }
    }
}

#endif // _LIB_CASMRT_BUILTIN_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
