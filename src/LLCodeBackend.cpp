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

const char* LLCodeBackend::getRegister( Value* value )
{
	// printf( "%s: %p\n", __FUNCTION__, value );
	
	if( register_cache.size() == 0 )
	{
		register_count = 0;
	}
	
	auto result = register_cache.find( value );
	if( result != register_cache.end() )
	{
		return result->second.c_str();
	}

    if( Value::isa< ConstantValue >( value ) and not Value::isa< Identifier >( value ) )
	{
    	register_cache[ value ] = std::string( "@.c" + std::to_string( register_count ) );
	}
	else
	{
		register_cache[ value ] = std::string( "%r" + std::to_string( register_count ) );
	}
	
	register_count++;	
	return register_cache[ value ].c_str();
}



const char* getType( Value* value )
{
	assert( value->getType() );
	
	u64 uid = value->getType()->getID();
	
	if( uid == BooleanType.getID() )
	{
		return "Bool";
	}
	else if( uid == IntegerType.getID() )
	{
		return "Int";
	}
	else
	{
		assert( 0 && "unimplemented type to emit!" );
		return 0;
	}
}

static void getIndent( std::stringstream& indent, ExecutionSemanticsBlock* ir )
{
	assert( Value::isa< ExecutionSemanticsBlock >( ir ) );
	
	indent << " ";
	for( u32 i = 0; i < ir->getPseudoState(); i++ )
	{
		indent << " ";
	}
}

static void getIndent( std::stringstream& indent, Statement* ir )
{
	assert( Value::isa< Statement >( ir ) );
	
	indent << " ";
	getIndent( indent, ((ExecutionSemanticsBlock*)ir->getScope()) );
}

static void getIndent( std::stringstream& indent, Instruction* ir )
{
	assert( Value::isa< Instruction >( ir ) );
	
	indent << " ";
	getIndent( indent, ((Statement*)ir->getStatement()) );
}


void LLCodeBackend::emit_instruction( FILE* f, Instruction* ir, const char* alias = 0 )
{
	std::stringstream indent;	
	std::vector< const char* > reg_type;
	std::vector< const char* > reg_name;
	
	assert( Value::isa< Instruction >( ir ) );
	
	indent << " ";
	for( u32 i = 0; i < ir->getStatement()->getScope()->getPseudoState(); i++ )
	{
		indent << " ";
	}
	
	if( !alias )
	{
		alias = &(ir->getName()[1]);
	}

	reg_type.push_back( getType( ir ) );
	reg_name.push_back( getRegister( ir ) );
	
	for( auto value : ir->getValues() )
	{
		reg_type.push_back( getType( value ) );
		reg_name.push_back( getRegister( value ) );
	}
	
	fprintf( f, "%scall void @libcasm-rt.%s", indent.str().c_str(), alias );
	for( auto rt : reg_type )
	{
		fprintf( f, ".%s", rt );
	}
	
	fprintf( f, "( " );

	u1 first = true;
	for( u32 i = 0; i < reg_type.size(); i++ )
	{
		if( first )
		{
			first = false;
		}
		else
		{
			fprintf( f, ", " );
		}
		fprintf( f, "%%libcasm-rt.%s* %s", reg_type[i], reg_name[i] );
	}
	
	fprintf( f, " )\n" );
}


void LLCodeBackend::emit_scope( FILE* f, ExecutionSemanticsBlock* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );
	
	const char* kind = ir->isParallel() ? "par" : "seq";
	u64 ps = ir->getPseudoState();
	
	fprintf( f, "%s; %s @ %lu\n", indent.str().c_str(), kind, ps );
	
	Backend::emit( f, ir );
	
	fprintf( f, "%s; end%s @ %lu\n", indent.str().c_str(), kind, ps );	
}

void LLCodeBackend::emit_statement( FILE* f, Statement* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );
	
	fprintf( f, "%s; stmt\n", indent.str().c_str() );	
	Backend::emit( f, ir );	
	fprintf( f, "%s; endstmt\n", indent.str().c_str() );
}

void LLCodeBackend::emit_constant( FILE* f, Value* ir, const char* ty, const char* val, u1 def )
{
    fprintf
	( f 
	, "; %s = private unnamed_addr constant %%libcasm-rt.%s <{ %s %s, i1 %u }>\n"
	, getRegister( ir )
	, getType( ir )
	, ty
	, val
	, def
	);
}

void LLCodeBackend::emit( FILE* f, BooleanConstant* ir )
{
	emit_constant( f, ir, "i1", to_string( ir->getValue() ).c_str(), ir->isDefined() );
	
    // fprintf
	// ( f 
	// , "; %s = private unnamed_addr constant %%libcasm-rt.Bool <{ i1 %u, i1 %u }>\n"
	// , getRegister( ir )
	// , ir->getValue()
	// , ir->isDefined()
	// );
}

void LLCodeBackend::emit( FILE* f, IntegerConstant* ir )
{
	emit_constant( f, ir, "i64", to_string( ir->getValue() ).c_str(), ir->isDefined() );
    // fprintf
	// ( f 
	// , "; %s = private unnamed_addr constant %%libcasm-rt.Int <{ i64 %li, i1 %u }>\n"
	// , getRegister( ir )
	// , ir->getValue()
	// , ir->isDefined()
	// );
}

void LLCodeBackend::emit( FILE* f, Function* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, Derived* ir ) { fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ ); }
void LLCodeBackend::emit( FILE* f, Rule* ir )
{
	fprintf( f, "define void @.%s()\n", ir->getName() );
	fprintf( f, "{\n" );
	
	register_count = 0;	
	emit( f, ir->getContext() );
	
	fprintf( f, "}\n" );
	fprintf( f, "\n" );
}


void LLCodeBackend::emit( FILE* f, ParallelBlock* ir )
{
    emit_scope( f, ((ExecutionSemanticsBlock*)ir) );
}

void LLCodeBackend::emit( FILE* f, SequentialBlock* ir )
{ 
    emit_scope( f, ((ExecutionSemanticsBlock*)ir) );
}

void LLCodeBackend::emit( FILE* f, TrivialStatement* ir )
{
	emit_statement( f, ((Statement*)ir) );
}
		
void LLCodeBackend::emit( FILE* f, LocationInstruction* ir )
{
	//emit_instruction( f, ir );
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
}

void LLCodeBackend::emit( FILE* f, LookupInstruction* ir )
{
	//emit_instruction( f, ir );
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
}

void LLCodeBackend::emit( FILE* f, UpdateInstruction* ir )
{
	//emit_instruction( f, ir );
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
}

void LLCodeBackend::emit( FILE* f, CallInstruction* ir )
{
	//emit_instruction( f, ir );
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
}

void LLCodeBackend::emit( FILE* f, PrintInstruction* ir )
{
	//emit_instruction( f, ir );
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
}

void LLCodeBackend::emit( FILE* f, LetInstruction* ir )
{
	std::stringstream indent;
	getIndent( indent, ir ); 
	
	const char* let_type = getType( ir );
	const char* let_name = getRegister( ir->getLHS() );
	
	const char* expr_type = getType( ir->getRHS() );
	const char* expr_name = getRegister( ir->getRHS() );
	
	fprintf( f, "%s%s = alloca %%libcasm-rt.%s\n", indent.str().c_str(), let_name, let_type );
	
	fprintf
	( f
	, "%scall void %%libcasm-rt.mov.%s.%s( %%libcasm-rt.%s* %s, %%libcasm-rt.%s* %s )\n"
	  , indent.str().c_str(), let_type, expr_type, let_type, let_name, expr_type, expr_name
	);
}

void LLCodeBackend::emit( FILE* f, AddInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, SubInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, MulInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, DivInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, RivInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, ModInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, EquInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, NeqInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, LthInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, LeqInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, GthInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, GeqInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f,  OrInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, XorInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, AndInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, NotInstruction* ir ) { emit_instruction( f, ir ); }
void LLCodeBackend::emit( FILE* f, MovInstruction* ir ) { emit_instruction( f, ir ); }




//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
