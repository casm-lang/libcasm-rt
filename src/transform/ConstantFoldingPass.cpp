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

#include "ConstantFoldingPass.h"

#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Builtin.h"
#include "../casm-ir/src/Constant.h"
#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Specification.h"
#include "../casm-ir/src/Visitor.h"

#include "../casm-rt/src/Value.h"

using namespace libcasm_ir;

char ConstantFoldingPass::id = 0;

static libpass::PassRegistration< ConstantFoldingPass > PASS(
    "Constant Folding Pass", "TBD", "ir-cf", 0 );

bool ConstantFoldingPass::run( libpass::PassResult& pr )
{
    auto data = pr.result< ConsistencyCheckPass >();
    assert( data );

    data->specification()->iterate( Traversal::PREORDER, []( Value& value ) {
        if( auto instr = cast< Instruction >( value ) )
        {
            libstdhl::Log::info( "cf: %s = %s ...", instr->label().c_str(),
                instr->name().c_str() );

            u32 position = 0;

            if( auto call = cast< CallInstruction >( instr ) )
            {
                position = 1;

                if( not isa< Builtin >( call->callee() ) )
                {
                    // call instr does not call a builtin, abort constant
                    // folding
                    return;
                }

                libstdhl::Log::info( "  +--> call instr: %s, %s",
                    call->callee()->name().c_str(),
                    call->callee()->type().name().c_str() );
            }
            else if( isa< OperatorInstruction >( instr ) )
            {
                libstdhl::Log::info( "  +--> operator instr" );
            }
            else
            {
                // instr is not a operator instr nor a call instr, abort
                // constant folding
                return;
            }

            for( ; position < instr->operands().size(); position++ )
            {
                if( not isa< Constant >( instr->operand( position ) ) )
                {
                    // non-constant instr operand found, abort constant
                    // folding
                    return;
                }
            }

            auto result = libcasm_rt::Value::execute( *instr );

            libstdhl::Log::info( "  +==> %s = %s %s", result.label().c_str(),
                result.type().name().c_str(), result.name().c_str() );

            instr->replaceAllUsesWith(
                libstdhl::make< libcasm_ir::Constant >( result ) );
        }
    } );

    return true;
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
