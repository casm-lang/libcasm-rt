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

#include "LLCodeBackend.h"

using namespace libcasm_ir;
using namespace libcasm_rt;


void LLCodeBackend::emit( FILE* f, BooleanConstant* ir )
{
    fprintf
	( f 
	, "; @.c%p = private unnamed_addr constant %%libcasm-rt.Bool <{ i1 %u, i1 true }>\n"
	, ir
	, ir->getValue()
	);
}

void LLCodeBackend::emit( FILE* f, IntegerConstant* ir )
{
    fprintf
	( f 
	, "; @.c%p = private unnamed_addr constant %%libcasm-rt.Int <{ i64 %li, i1 true }>\n"
	, ir
	, ir->getValue()
	);
}

void LLCodeBackend::emit( FILE* f, Function* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, Derived* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, Rule* ir )
{
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
	
	emit( f, ir->getContext() );
}

void LLCodeBackend::emit( FILE* f, ParallelBlock* ir )
{
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );

	fprintf( f, "; par\n");

	for( auto value : ir->getBlocks() )
	{
		switch( value->getValueID() )
		{
		    case Value::PARALLEL_BLOCK:     emit( f, ((ParallelBlock*)ir) );     break;
		    case Value::SEQUENTIAL_BLOCK:   emit( f, ((SequentialBlock*)ir) );   break;
		    case Value::TRIVIAL_STATEMENT:  emit( f, ((TrivialStatement*)ir) );   break;
	        default:
				assert( 0 );
		}
	}
	
	fprintf( f, "; endpar\n");
}

void LLCodeBackend::emit( FILE* f, SequentialBlock* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }

void LLCodeBackend::emit( FILE* f, TrivialStatement* ir )
{
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
	
	fprintf( f, "; statement\n");

	for( auto value : ir->getInstructions() )
	{
		switch( value->getValueID() )
		{
			assert( Value::isa< Instruction >( value ) );
			Backend::emit( f, ((Instruction*)value) );
		}
	}
	
	fprintf( f, "; endstatement\n");	
}
		
void LLCodeBackend::emit( FILE* f, LocationInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, LookupInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, UpdateInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, CallInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, PrintInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, LetInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }

void LLCodeBackend::emit( FILE* f, AddInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, SubInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, MulInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, DivInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, RivInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, ModInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, EquInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, NeqInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, LthInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, LeqInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, GthInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, GeqInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f,  OrInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, XorInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, AndInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, NotInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, MovInstruction* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }




//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
