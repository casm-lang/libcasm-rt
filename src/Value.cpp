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
#include "Instruction.h"
#include "Type.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Type.h"
#include "../casm-ir/src/Value.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Constant.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Module.h"

using namespace libcasm_rt;

libcsel_ir::Value& Value::get(
    libcasm_ir::Value& value, libcsel_ir::Module* context )
{
    switch( value.id() )
    {
        case libcasm_ir::Value::AS_BOOLEAN_BUILTIN:
        {
            return Builtin::asBoolean( value, context );
        }

        // AS_INTEGER_BUILTIN,
        // AS_BIT_BUILTIN,
        // AS_STRING_BUILTIN,
        // AS_FLOATING_BUILTIN,
        // AS_RATIONAL_BUILTIN,
        // AS_ENUMERATION_BUILTIN,

        case libcasm_ir::Value::EQU_INSTRUCTION:
        {
            return Instruction::Equ(
                static_cast< libcasm_ir::EquInstruction& >( value ), context );
        }

        default:
        {
            libstdhl::Log::error(
                " unsupported value '%s' of type '%s' to create RT instance",
                value.name(), value.type().name() );
            assert( 0 );
            return *libcsel_ir::Constant::NIL();
        }
    }
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
