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

namespace libcasm_ir
{
    class Value;
    class Instruction;
}

namespace libcsel_ir
{
    class Value;
    class Module;
}

namespace libcasm_rt
{
    class Value : public CasmRT
    {
      public:
        static libcasm_ir::Value* execute( libcasm_ir::Instruction& value,
            libcsel_ir::Module* module = nullptr );

        static libcsel_ir::Value& get(
            libcasm_ir::Value& value, libcsel_ir::Module* context = nullptr );
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
