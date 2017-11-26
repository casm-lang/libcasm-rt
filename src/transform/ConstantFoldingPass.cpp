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

#include "ConstantFoldingPass.h"

#include "../Instruction.h"

#include <libstdhl/Log>

#include <libcasm-ir/Instruction>
#include <libcasm-ir/Specification>
#include <libcasm-ir/Visitor>
#include <libcasm-ir/analyze/ConsistencyCheckPass>

using namespace libcasm_ir;

char ConstantFoldingPass::id = 0;

static libpass::PassRegistration< ConstantFoldingPass > PASS(
    "Constant Folding Pass", "TBD", "ir-cf", 0 );

bool ConstantFoldingPass::run( libpass::PassResult& pr )
{
    const auto data = pr.result< ConsistencyCheckPass >();
    const auto specification = data->specification();

    specification->iterate( Traversal::PREORDER, []( Value& value ) {
        if( auto instr = cast< Instruction >( value ) )
        {
            libstdhl::Log::info( "cf: %s = %s ...", instr->label().c_str(), instr->name().c_str() );

            u32 operand_pos = 0;

            if( auto call = cast< CallInstruction >( instr ) )
            {
                operand_pos = 1;

                if( not isa< Builtin >( call->callee() ) )
                {
                    // call instr does not call a builtin, abort constant
                    // folding
                    return;
                }

                libstdhl::Log::info(
                    "  +--> call instr: %s, %s",
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

            for( ; operand_pos < instr->operands().size(); operand_pos++ )
            {
                if( not isa< Constant >( instr->operand( operand_pos ) ) )
                {
                    // non-constant instr operand found, abort constant folding
                    return;
                }
            }

            auto result = libcasm_rt::Instruction::execute( *instr );
            assert( result );

            libstdhl::Log::info(
                "  +==> %s = %s %s",
                result->label().c_str(),
                result->type().name().c_str(),
                result->name().c_str() );

            instr->replaceAllUsesWith( result );
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
