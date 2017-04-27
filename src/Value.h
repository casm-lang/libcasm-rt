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

#ifndef _LIB_CASMRT_VALUE_H_
#define _LIB_CASMRT_VALUE_H_

#include "CasmRT.h"

#include "../casm-ir/src/Constant.h"
#include "../casm-ir/src/Value.h"

namespace libcasm_rt
{
    /**
       @extends CasmRT
     */
    namespace Value
    {
        libcasm_ir::Constant execute( const libcasm_ir::Value::ID id,
            const libcasm_ir::Type::Ptr& type,
            const std::vector< libcasm_ir::Constant >& operands );

        template < typename... Args >
        libcasm_ir::Constant execute( libcasm_ir::Value::ID ID,
            const libcasm_ir::Type& type,
            Args&&... args )
        {
            const auto t = libstdhl::wrap( (libcasm_ir::Type&)type );
            return execute( ID, t, { std::forward< Args >( args )... } );
        }

        template < typename... Args >
        libcasm_ir::Constant execute( libcasm_ir::Value::ID ID,
            const libcasm_ir::Type::Ptr& type,
            Args&&... args )
        {
            return execute( ID, type, { std::forward< Args >( args )... } );
        }
    };
}

#endif // _LIB_CASMRT_VALUE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//