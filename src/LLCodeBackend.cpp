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


const char* LLCodeBackend::getRegister( Value* value, u1 let_flag )
{
	if( register_cache.size() == 0 )
	{
		register_count = 0;
	    label_count = 0;
	}
	
	auto result = register_cache.find( value );
	if( result != register_cache.end() )
	{
		return result->second.c_str();
	}
	
	std::string cnt = std::to_string( register_count );
    if( Value::isa< ConstantValue >( value ) and not Value::isa< Identifier >( value ) )
	{
    	register_cache[ value ] = std::string( "@.c" + cnt );
	}
    else if( Value::isa< Function >( value ) )
	{
    	register_cache[ value ] = std::string( "@" + std::string( value->getName() ) );
		return register_cache[ value ].c_str();
	}
    else if( Value::isa< Block >( value ) or Value::isa< Statement >( value ) )
	{
		std::string lbl = std::to_string( label_count );
		label_count++;
    	register_cache[ value ] = std::string( "blk" + lbl );
		return register_cache[ value ].c_str();
	}
    else if( let_flag == true )
	{
		register_cache[ value ] = std::string( "%_r" + cnt );
	}
	else
	{
		register_cache[ value ] = std::string( "%.r" + cnt );
	}
	
	register_count++;	
	return register_cache[ value ].c_str();
}



const char* getType( Value* value )
{
	Type* t = value->getType();
	assert( t );
	
	if( Value::isa< Function >( value ) )
	{
		t = t->getResultType();
	}
	
	u64 uid = t->getID();
	
	if( uid == AgentType.getID() )
	{
		return "Agent";
	}
	else if( uid == RulePointerType.getID() )
	{
		return "Rule";
	}
	else if( uid == BooleanType.getID() )
	{
		return "Bool";
	}
	else if( uid == IntegerType.getID() )
	{
		return "Int";
	}
	else if( uid == StringType.getID() )
	{
		return "Str";
	}
	else
	{
		assert( 0 && "unimplemented type to emit!" );
		return 0;
	}
}

#define INDENT "  "
static void getIndent( std::stringstream& indent, ExecutionSemanticsBlock* ir )
{
	assert( Value::isa< ExecutionSemanticsBlock >( ir ) );
	
	indent << INDENT;
	for( u32 i = 0; i < ir->getPseudoState(); i++ )
	{
		indent << INDENT;
	}
}

static void getIndent( std::stringstream& indent, Statement* ir )
{
	assert( Value::isa< Statement >( ir ) );
	
	indent << INDENT;
	getIndent( indent, ((ExecutionSemanticsBlock*)ir->getScope()) );
}

static void getIndent( std::stringstream& indent, Instruction* ir )
{
	assert( Value::isa< Instruction >( ir ) );
	
	// indent << INDENT;
	getIndent( indent, ((Statement*)ir->getStatement()) );
}


void LLCodeBackend::lifetime_start( FILE* f, Instruction* ir )
{
	return;
	
	std::stringstream indent;	
	getIndent( indent, ir );

	if( Value::isa< LocationInstruction >( ir ) )
	{
		fprintf
		( f
		, "%scall void @llvm.lifetime.start( i64 -1, i8* %s )\n"
		  "%s%s.inv = call {}* @llvm.invariant.start( i64 -1, i8* %s )\n"
		, indent.str().c_str()
		, getRegister( ir )
		, indent.str().c_str()
		, getRegister( ir )
		, getRegister( ir )
		);
		
		return;
	}
	
	fprintf
	( f
	, "%s%s.ptr = bitcast %%libcasm-rt.%s* %s to i8*\n"
	  "%scall void @llvm.lifetime.start( i64 -1, i8* %s.ptr )\n"
	  "%s%s.inv = call {}* @llvm.invariant.start( i64 -1, i8* %s.ptr )\n"
	, indent.str().c_str()
	, getRegister( ir )
	, getType( ir )
	, getRegister( ir )
    , indent.str().c_str()
	, getRegister( ir )
    , indent.str().c_str()
	, getRegister( ir )
	, getRegister( ir )
	);
}

void LLCodeBackend::lifetime_end( FILE* f, Instruction* ir )
{
	return;
	
	std::stringstream indent;	
	getIndent( indent, ir );

	const char* postfix = ".ptr";

	if( Value::isa< LocationInstruction >( ir ) )
	{
		return;
		postfix = "";
	}
	
	fprintf
	( f
	, "%scall void @llvm.invariant.end( {}* %s.inv, i64 -1, i8* %s%s )\n"
	  "%scall void @llvm.lifetime.end( i64 -1, i8* %s%s )\n"
	, indent.str().c_str()
	, getRegister( ir )
	, getRegister( ir )
	, postfix
	, indent.str().c_str()
	, getRegister( ir )
	, postfix
	);
}



void LLCodeBackend::emit_instruction( FILE* f, Instruction* ir, const char* alias = 0 )
{
	std::vector< const char* > reg_type;
	std::vector< const char* > reg_name;
	
	assert( Value::isa< Instruction >( ir ) );

	std::stringstream indent;	
	getIndent( indent, ir );
	
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
	
	fprintf
	( f
	, "%s%s = alloca %%libcasm-rt.%s\n"
	, indent.str().c_str()
	, getRegister( ir )
	, getType( ir )
	);
	
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

	i32 cnt = 0;
    for( auto value : ir->getValues() )
	{
		if( Value::isa< Instruction >( value ) )
		{
			if( reg_name[ cnt ][ 0 ] == '%' && reg_name[ cnt ][ 1 ] == '.' )
			{
				lifetime_end( f, (Instruction*)value );
			}
		}
		cnt++;
	}
	
	lifetime_start( f, ir );
}


void LLCodeBackend::emit_scope( FILE* f, ExecutionSemanticsBlock* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );
	
	const char* kind = ir->isParallel() ? "par" : "seq";
	u64 ps = ir->getPseudoState();
	
	fprintf( f, "%s; %s @ %lu\n", indent.str().c_str(), kind, ps );
	
	if( ir->getParent() )
	{
		if( ir->getParent()->isParallel() != ir->isParallel() )
		{
			fprintf
			( f
			, "%scall i8 @libcasm-rt.updateset.fork( %%libcasm-rt.updateset* %%.uset )\n"
			, indent.str().c_str()
			);
		}
	}
	
	Backend::emit( f, ir );
	
	if( ir->getParent() )
	{
		if( ir->getParent()->isParallel() != ir->isParallel() )
		{
			// fprintf
			// ( f
			// , "%scall i8 @libcasm-rt.updateset.dump( %%libcasm-rt.updateset* %%.uset )\n"
			// , indent.str().c_str()
			// );
			fprintf
			( f
			, "%scall i8 @libcasm-rt.updateset.merge( %%libcasm-rt.updateset* %%.uset )\n"
			, indent.str().c_str()
			);
		}
	}
    
	fprintf( f, "%s; end%s @ %lu\n", indent.str().c_str(), kind, ps );	
}

void LLCodeBackend::emit_statement( FILE* f, Statement* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );
	
	fprintf( f, "%s; stmt\n", indent.str().c_str() );	
	Backend::emit( f, ir );	
	fprintf( f, "%s;\n", indent.str().c_str() );
}

void LLCodeBackend::emit_constant( FILE* f, Value* ir, const char* ty, const char* val, u1 def )
{
    fprintf
	( f 
	, "%s = "
	  "private unnamed_addr "
	  "constant %%libcasm-rt.%s { %s %s, i1 %u }\n"
	, getRegister( ir )
	, getType( ir )
	, ty
	, val
	, def
	);
}

void LLCodeBackend::emit( FILE* f, AgentConstant* ir )
{
    emit_constant( f, ir, "i8*", "null", ir->isDefined() );
}

void LLCodeBackend::emit( FILE* f, RulePointerConstant* ir )
{
	Rule* rule = ir->getValue();
	std::string val = "null";
		
	if( rule )
	{
		val = std::string( "@" );
		val.append( rule->getName() );
	}
	
	emit_constant( f, ir, "%libcasm-rt.RuleAddr", val.c_str(), ir->isDefined() );
}

void LLCodeBackend::emit( FILE* f, BooleanConstant* ir )
{
	emit_constant( f, ir, "i1", to_string( ir->getValue() ).c_str(), ir->isDefined() );
}

void LLCodeBackend::emit( FILE* f, IntegerConstant* ir )
{
	emit_constant( f, ir, "i64", to_string( ir->getValue() ).c_str(), ir->isDefined() );
}

void LLCodeBackend::emit( FILE* f, StringConstant* ir )
{
	std::string s( ir->getValue() );
	
    fprintf
	( f 
	, "%s.str = "
	  "private unnamed_addr "
	  "constant [ %lu x i8 ] c\""
	, getRegister( ir )
	, s.size()
	);

	for( i32 i = 0; i < s.size(); i++ )
	{
		fprintf( f, "\\%02x", s.c_str()[i] );
	}
    
	fprintf( f, "\"\n" );
	
	std::string r( "getelementptr inbounds( [ " + to_string( s.size() ) + " x i8 ]* " + getRegister( ir ) + ".str, i32 0, i32 0 )" );
	
	emit_constant( f, ir, "i8*", r.c_str(), ir->isDefined() );
}

void LLCodeBackend::emit( FILE* f, Function* ir )
{
	if( ir->getType()->getParameters().size() == 0 )
	{
		// trivial data-type!
		fprintf
		( f
		, "%s = global %%libcasm-rt.%s zeroinitializer\n"
		, getRegister( ir ), getType( ir )
		);
		
		// location
		fprintf( f, "define linkonce_odr i8* %s.location() #0\n", getRegister( ir ) );
		fprintf( f, "{\n");
		fprintf( f, "begin:\n");
		
		fprintf( f, INDENT "%%ptr = getelementptr %%libcasm-rt.%s* %s, i64 0\n"
		, getType( ir )
		, getRegister( ir )
		);
		
		fprintf( f, INDENT "%%loc = bitcast %%libcasm-rt.%s* %%ptr to i8*\n", getType( ir )	);
		
		fprintf( f, INDENT "ret i8* %%loc\n" );
		fprintf( f, "}\n");

		// // lookup
		// fprintf
		// ( f
		// , "define linkonce_odr %%libcasm-rt.%s* %s.lookup( "
		//   "%%libcasm-rt.updateset* %%uset, i64 %%loc ) alwaysinline\n"
		// , getType( ir )
		// , getRegister( ir )
		// );
		// fprintf( f, "{\n");
	    
		// fprintf( f, "%sret %%libcasm-rt.%s* undef\n", INDENT, getType( ir ) );
		// fprintf( f, "}\n");
		
		// // update
		// fprintf
		// ( f
		// , "define linkonce_odr void %s.update( "
		//   "%%libcasm-rt.updateset* %%uset, i64 %%loc, %%libcasm-rt.%s* %%value ) alwaysinline\n"
		// , getRegister( ir )
		// , getType( ir )
		// );
		// fprintf( f, "{\n");

		// fprintf( f, INDENT "%%dic = getelementptr %%libcasm-rt.updateset* %%uset, i32 0, i32 0\n" );
		// fprintf( f, INDENT "%%mem = getelementptr %%stdll.dict* %%dic, i32 0, i32 3\n" );
		
		// fprintf
		// ( f
		// , INDENT "%%_val = getelementptr %%libcasm-rt.%s* %%value, i32 0, i32 0\n"
		// , getType( ir )
		// );

		// fprintf
		// ( f
		// , INDENT "%%_def = getelementptr %%libcasm-rt.%s* %%value, i32 0, i32 0\n"
		// , getType( ir )
		// );
		
		// fprintf( f, INDENT "%%val = load i64* %%_val\n" );
		// fprintf( f, INDENT "%%def = load i1*  %%_def\n" );

		
		// // alloc an update and insert it to uset
		// fprintf( f, INDENT "%%upd = call %%libcasm-rt.update* %%libcasm-rt.update.new"
		// 		 "( %%stdll.mem* %%mem, i64 %%val, i1 %%def )\n"
		// 	);
		
		// // // fprintf
		// // // ( f
		// // // , "%s; %s = call i8* @libcasm-rt.updateset.insert( "
		// // //   "%%libcasm-rt.updateset* %%.uset, i64 0, i64 0"
		// // //   ")\n"
		// // // , indent.str().c_str()
		// // // , getRegister( ir )
		// // // //, ir->getName()
		// // // );
		
		// fprintf( f, "%sret void\n", INDENT );
		// fprintf( f, "}\n");

	}
	else
	{
		assert( 0 && "n-ary functions not implemented yet!" );
	}
}

void LLCodeBackend::emit( FILE* f, Derived* ir )
{
	fprintf( f, "define linkonce_odr void @%s() #0\n", ir->getName() );
	fprintf( f, "{\n" );
	fprintf( f, "begin:\n");
		
	register_count = 0;	
	label_count = 0;

	emit( f, ir->getContext() );
	
	fprintf( f, "%sret void\n", INDENT );
	fprintf( f, "}\n" );
	fprintf( f, "\n" );
}

void LLCodeBackend::emit( FILE* f, Rule* ir )
{
	fprintf( f, "define linkonce_odr void @%s( %%libcasm-rt.updateset* %%.uset ) #0\n", ir->getName() );
	fprintf( f, "{\n" );
	fprintf( f, "begin:\n");
		
	register_count = 0;
	label_count = 0;
	
	emit( f, ir->getContext() );
	
	fprintf( f, "%sret void\n", INDENT );
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

void LLCodeBackend::emit( FILE* f, BranchStatement* ir )
{
	std::stringstream indent;
	getIndent( indent, ir->getScope() );
	
	fprintf( f, "%s; branch\n", indent.str().c_str() );	
	
	emit_statement( f, ((Statement*)ir) );
	
	for( auto value : ir->getBlocks() )
	{
		fprintf( f, "%s%s:\n", indent.str().c_str(), getRegister( value ) );
		
	    emit( f, ((ParallelBlock*)value) );
		
		fprintf( f, "%s%sbr label %%%s\n", indent.str().c_str(), INDENT, getRegister( ir ) );
	}
	
	fprintf( f, "%s%s:\n", indent.str().c_str(), getRegister( ir ) );
	fprintf( f, "%s; endbranch\n", indent.str().c_str() );
}
		
void LLCodeBackend::emit( FILE* f, BranchInstruction* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );

	
	fprintf
	( f
	, "%s%s = call i1 @libcasm-rt.branch.Bool( %%libcasm-rt.Bool* %s )\n"
	, indent.str().c_str()
	, getRegister( ir )
	, getRegister( ir->get() )
	);
	
	fprintf
	( f
	, "%sbr i1 %s, label %%%s, label %%%s\n"
	, indent.str().c_str()
	, getRegister( ir )
	, getRegister( ir->getTrue() )
	, getRegister( ir->getFalse() )
	);
}


void LLCodeBackend::emit( FILE* f, LocationInstruction* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );
	
	Value* func = ir->getValue( 0 );
	Type* tfunc = func->getType();
	
	if( tfunc->getParameters().size() == 0 )
	{
		fprintf
		( f
		, "%s%s = call i8* @%s.location()\n"
		, indent.str().c_str()
		, getRegister( ir )
		, func->getName()
		);
	}
	else
	{
		if( std::string( func->getName() ).compare( "program" ) == 0 )
		{
			fprintf
			( f
			, "%s%s = call i8* @%s.location( i8* null )\n"
			, indent.str().c_str()
			, getRegister( ir )
			, func->getName()
			);
			return;
		}
		
		assert( 0 && "unimplemented!" );
	}

	lifetime_start( f, ir );
}

void LLCodeBackend::emit( FILE* f, LookupInstruction* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );

	Value*  loc = ir->getValue( 0 );
	Value* func = ((LocationInstruction*)loc)->getValue( 0 );
	Type* tfunc = func->getType();
	
	if( tfunc->getParameters().size() == 0 )
	{
		fprintf
		( f
		, "%s%s.lup = call i8* @libcasm-rt.lookup( %%libcasm-rt.updateset* %%.uset, i8* %s )\n"
		, indent.str().c_str()
		, getRegister( ir )
		, getRegister( loc )
		);
		
		lifetime_end( f, (Instruction*)loc );

		fprintf
		( f
		, "%s%s = bitcast i8* %s.lup to %%libcasm-rt.%s*\n"
		, indent.str().c_str()
		, getRegister( ir )
		, getRegister( ir )
		, getType( ir )
		);
		
	}
	else
	{
		assert( 0 && "unimplemented!" );
	}

	lifetime_start( f, ir );
}

void LLCodeBackend::emit( FILE* f, UpdateInstruction* ir )
{
	std::stringstream indent;
	getIndent( indent, ir );

	Value*  loc = ir->getLHS();
	Value* func = ((LocationInstruction*)loc)->getValue( 0 );
	Type* tfunc = func->getType();
    
	if( tfunc->getParameters().size() == 0 )
	{
		fprintf
		( f
		, "%scall void @libcasm-rt.update.%s( "
		  "%%libcasm-rt.updateset* %%.uset, i8* %s, %%libcasm-rt.%s* %s"
		  ")\n"
		, indent.str().c_str()
		, getType( ir )
		, getRegister( ir->getLHS() )
		, getType( ir->getRHS() )
		, getRegister( ir->getRHS() )
		);
	}
	else
	{
		if( std::string( func->getName() ).compare( "program" ) == 0 )
		{
		    fprintf
		    ( f
		    , "%scall void @libcasm-rt.update.%s( "
		      "%%libcasm-rt.updateset* %%.uset, i8* %s, %%libcasm-rt.%s* %s"
		      ")\n"
		    , indent.str().c_str()
		    , getType( ir )
		    , getRegister( ir->getLHS() )
		    , getType( ir->getRHS() )
		    , getRegister( ir->getRHS() )
		    );
			return;
		}
		
		assert( 0 && "unimplemented!" );
	}
	
	if( Value::isa< Instruction >( ir->getLHS() ) )
	{
		lifetime_end( f, ((Instruction*)ir->getLHS()) );
	}
	if( Value::isa< Instruction >( ir->getRHS() ) )
	{
		lifetime_end( f, ((Instruction*)ir->getRHS()) );
	}
}

void LLCodeBackend::emit( FILE* f, CallInstruction* ir )
{
	//emit_instruction( f, ir );
	fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
}

void LLCodeBackend::emit( FILE* f, PrintInstruction* ir )
{
	//emit_instruction( f, ir );
	//fprintf( stderr, "+++ FIXME +++: %s:%i: %s\n", __FILE__, __LINE__, __FUNCTION__ );
	
	std::stringstream indent;
	getIndent( indent, ir ); 
	
	for( auto value : ir->getValues() )
	{
		fprintf
		( f
		, "%scall void @libcasm-rt.print.%s( %%libcasm-rt.%s* %s )\n"
		, indent.str().c_str(), getType( value ), getType( value ), getRegister( value )
		);
	}
}

void LLCodeBackend::emit( FILE* f, LetInstruction* ir )
{
	std::stringstream indent;
	getIndent( indent, ir ); 
	
	const char* let_type = getType( ir );
	const char* let_name = getRegister( ir->getLHS(), true );
	
	const char* expr_type = getType( ir->getRHS() );
	const char* expr_name = getRegister( ir->getRHS() );
	
	fprintf( f, "%s%s = alloca %%libcasm-rt.%s\n", indent.str().c_str(), let_name, let_type );
	
	fprintf
	( f
	, "%scall void @libcasm-rt.mov.%s.%s( %%libcasm-rt.%s* %s, %%libcasm-rt.%s* %s )\n"
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
