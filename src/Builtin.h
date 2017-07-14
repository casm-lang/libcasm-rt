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
        void execute( const libcasm_ir::IsSymbolicBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AbortBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AssertBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::PrintBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::PrintLnBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AsBooleanBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AsIntegerBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AsBitBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AsStringBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AsFloatingBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AsRationalBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AsEnumerationBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::DecBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::HexBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::OctBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::BinBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AdduBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AddsBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::SubuBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::SubsBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::MuluBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::MulsBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::LesuBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::LessBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::LequBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::LeqsBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::GreuBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::GresBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::GequBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::GeqsBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::ZextBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::SextBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::TruncBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::ShlBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::ShrBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::AshrBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::ClzBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::CloBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        void execute( const libcasm_ir::ClsBuiltin& builtin,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size );

        // void execute( const libcasm_ir::PowBuiltin& builtin
        // );

        // void execute( const libcasm_ir::RandBuiltin& builtin
        // );

        template < typename T >
        inline void execute( const libcasm_ir::Type::Ptr& type,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size )
        {
            const T builtin( type );
            assert( builtin.type().arguments().size() == size );
            execute( builtin, res, operands, size );
            assert( builtin.type().result() == res.type() );
        }

        template < typename T >
        inline void execute( const libcasm_ir::Type& type,
            libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
            const std::size_t size )
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
