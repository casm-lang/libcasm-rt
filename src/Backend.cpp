//  
//  Copyright (c) 2015 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
//  
//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal with the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//  
//  * Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimers.
//  
//  * Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimers in the 
//    documentation and/or other materials provided with the distribution.
//  
//  * Neither the names of the copyright holders, nor the names of its 
//    contributors may be used to endorse or promote products derived from 
//    this Software without specific prior written permission.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
//  WITH THE SOFTWARE.
//  

#include "Backend.h"

using namespace libcasm_ir;
using namespace libcasm_rt;

void Backend::emit( FILE* f, Value* ir )
{
    switch( ir->getValueID() )
    {
	    case Value::PARALLEL_BLOCK:     emit( f, ((ParallelBlock*)ir) );     break;
	    case Value::SEQUENTIAL_BLOCK:   emit( f, ((SequentialBlock*)ir) );   break;
	    case Value::TRIVIAL_STATEMENT:  emit( f, ((TrivialStatement*)ir) );   break;
	    case Value::BRANCH_STATEMENT:   emit( f, ((BranchStatement*)ir) );   break;
			
	    case Value::LOCATION_INSTRUCTION:    emit( f, ((LocationInstruction*)ir) );     break;
        case Value::LOOKUP_INSTRUCTION:    emit( f, ((LookupInstruction*)ir) );     break;
        case Value::UPDATE_INSTRUCTION:    emit( f, ((UpdateInstruction*)ir) );     break;
        case Value::PRINT_INSTRUCTION:    emit( f, ((PrintInstruction*)ir) );     break;
        case Value::CALL_INSTRUCTION:    emit( f, ((CallInstruction*)ir) );     break;
        case Value::LET_INSTRUCTION:    emit( f, ((LetInstruction*)ir) );     break;

	    case Value::BRANCH_INSTRUCTION:    emit( f, ((BranchInstruction*)ir) );     break;
		
        case Value::ADD_INSTRUCTION:    emit( f, ((AddInstruction*)ir) );     break;
        case Value::SUB_INSTRUCTION:    emit( f, ((SubInstruction*)ir) );     break;
        case Value::MUL_INSTRUCTION:    emit( f, ((MulInstruction*)ir) );     break;
        case Value::DIV_INSTRUCTION:    emit( f, ((DivInstruction*)ir) );     break;
        case Value::RIV_INSTRUCTION:    emit( f, ((RivInstruction*)ir) );     break;
        case Value::MOD_INSTRUCTION:    emit( f, ((ModInstruction*)ir) );     break;
        case Value::EQU_INSTRUCTION:    emit( f, ((EquInstruction*)ir) );     break;
        case Value::NEQ_INSTRUCTION:    emit( f, ((NeqInstruction*)ir) );     break;
        case Value::LTH_INSTRUCTION:    emit( f, ((LthInstruction*)ir) );     break;
        case Value::LEQ_INSTRUCTION:    emit( f, ((LeqInstruction*)ir) );     break;
        case Value::GTH_INSTRUCTION:    emit( f, ((GthInstruction*)ir) );     break;
        case Value::GEQ_INSTRUCTION:    emit( f, ((GeqInstruction*)ir) );     break;
        case Value::XOR_INSTRUCTION:    emit( f, ((XorInstruction*)ir) );     break;
        case Value::OR_INSTRUCTION:     emit( f, ((OrInstruction*)ir) );     break;
        case Value::AND_INSTRUCTION:    emit( f, ((AndInstruction*)ir) );     break;
        case Value::NOT_INSTRUCTION:    emit( f, ((NotInstruction*)ir) );     break;
        case Value::MOV_INSTRUCTION:    emit( f, ((MovInstruction*)ir) );     break;
        default:
            assert( 0 && "unimplemented value to distribute an emit!" );
    }
};


void Backend::emit( FILE* f, ExecutionSemanticsBlock* ir )
{
	assert( Value::isa< ExecutionSemanticsBlock >( ir ) );
	
	for( auto value : ir->getBlocks() )
	{
	    emit( f, ((Value*)value) );
	}
}

void Backend::emit( FILE* f, Statement* ir )
{
	assert( Value::isa< Statement >( ir ) );
	
	for( auto value : ir->getInstructions() )
	{
	    emit( f, ((Value*)value) );
	}
}


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
