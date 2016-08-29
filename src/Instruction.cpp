//  
//  Copyright (c) 2014-2016 CASM Organization
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

#include "Instruction.h"

using namespace libcasm_rt;

libnovel::CallableUnit* Instruction::create( libcasm_ir::Value& value, libnovel::Module* module )
{
	if( libcasm_ir::Value::isa< libcasm_ir::AddInstruction >( &value ) )
	{
		return ArithmeticInstruction< libnovel::AddSignedInstruction >::create( value, module ); 
	}
	else if( libcasm_ir::Value::isa< libcasm_ir::DivInstruction >( &value ) )
	{
		return ArithmeticInstruction< libnovel::DivSignedInstruction >::create( value, module );
	}
	else if( libcasm_ir::Value::isa< libcasm_ir::AndInstruction >( &value ) )
	{
		assert(0);
		return 0;
	}
	else if( libcasm_ir::Value::isa< libcasm_ir::EquInstruction >( &value ) )
	{
		return EquInstruction::create( value, module );
	}
    else
	{
		assert( !" unsupported/unimplemented instruction to create run-time implementation! " );
    }
	
	return 0;
}

template< class INSTR >
libnovel::CallableUnit* ArithmeticInstruction< INSTR >::create( libcasm_ir::Value& value, libnovel::Module* module )
{
	assert( libcasm_ir::Value::isa< libcasm_ir::BinaryInstruction >( &value ) );
	libcasm_ir::BinaryInstruction* instr = (libcasm_ir::BinaryInstruction*)&value;
	
	static std::unordered_map< std::string, libnovel::CallableUnit* > cache;
	
	libnovel::Structure* ta = libcasm_rt::Type::create( *instr->getLHS() );
	libnovel::Structure* tb = libcasm_rt::Type::create( *instr->getRHS() );
	libnovel::Structure* tt = libcasm_rt::Type::create( *instr );
	
	std::string key = std::string
	( "casmrt_"
	+ std::string( &value.getName()[1] )
	+ "_"
	+ std::string( ta->getName() )
	+ "_"
	+ std::string( tb->getName() )
	+ "_"
	+ std::string( tt->getName() )
	);
	
	if( cache.count( key ) > 0 )
	{
		return cache[ key ];
	}
	
	const char* name = libstdhl::Allocator::string( key );
	
	libnovel::CallableUnit* obj = new libnovel::Intrinsic( name );
	assert( obj );
	cache[ key ] = obj;
	if( module )
	{
		module->add( obj );
	}
	
	
	libnovel::Reference* ra = obj->in(  "a", ta->getType() );
	libnovel::Reference* rb = obj->in(  "b", tb->getType() );
	libnovel::Reference* rt = obj->out( "t", tt->getType() );
	
	libnovel::Scope* scope = 0; //new libnovel::ParallelScope( obj );
	if( strcmp( &value.getName()[1], "div" ) == 0 ) // TODO: EXPERIMENTIAL: DEMO ONLY!!!
	{
		scope = new libnovel::SequentialScope( obj );
	}
	else
	{
		scope = new libnovel::ParallelScope( obj );
	}
	
	libnovel::Value* rav = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(0) );
	libnovel::Value* rad = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(1) );
	libnovel::Value* rbv = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(0) );
	libnovel::Value* rbd = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(1) );
		
	libnovel::Value* lav  = new libnovel::LoadInstruction( rav );
	libnovel::Value* lad  = new libnovel::LoadInstruction( rad );
	libnovel::Value* lbv  = new libnovel::LoadInstruction( rbv );
	libnovel::Value* lbd  = new libnovel::LoadInstruction( rbd );
	
	libnovel::Value* icv = new INSTR( lav, lbv );
	libnovel::Value* icd = new libnovel::AndInstruction( lad, lbd );

	libnovel::Value* rtv = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(0) );
	libnovel::Value* rtd = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(1) );
		
	libnovel::Value* scv = new libnovel::StoreInstruction( icv, rtv );
	libnovel::Value* scd = new libnovel::StoreInstruction( icd, rtd );
		
	libnovel::Statement* stmt_v = new libnovel::TrivialStatement( scope );
	libnovel::Statement* stmt_d = new libnovel::TrivialStatement( scope );
	stmt_v->add( scv );
	stmt_d->add( scd );

	return obj;
}



// libnovel::CallableUnit* AddInstruction::create( libcasm_ir::Value& value, libnovel::Module* module )
// {
// 	return ArithmeticInstruction< libnovel::AddSignedInstruction >::create( value, module );
// }

// libnovel::CallableUnit* DivInstruction::create( libcasm_ir::Value& value, libnovel::Module* module )
// {
// 	return ArithmeticInstruction< libnovel::DivSignedInstruction >::create( value, module );
// }

libnovel::CallableUnit* EquInstruction::create( libcasm_ir::Value& value, libnovel::Module* module )
{
	assert( libcasm_ir::Value::isa< libcasm_ir::EquInstruction >( &value ) );
	libcasm_ir::EquInstruction* instr = (libcasm_ir::EquInstruction*)&value;
	
	static std::unordered_map< std::string, libnovel::CallableUnit* > cache;
	
	libnovel::Structure* ta = libcasm_rt::Type::create( *instr->getLHS() );
	libnovel::Structure* tb = libcasm_rt::Type::create( *instr->getRHS() );
	libnovel::Structure* tt = libcasm_rt::Type::create( *instr );
	
	std::string key = std::string
	( "casmrt_"
	+ std::string( &value.getName()[1] )
	+ "_"
	+ std::string( ta->getName() )
	+ "_"
	+ std::string( tb->getName() )
	+ "_"
	+ std::string( tt->getName() )
	);
	
	if( cache.count( key ) > 0 )
	{
		return cache[ key ];
	}
	
	const char* name = libstdhl::Allocator::string( key );
	
	libnovel::CallableUnit* obj = new libnovel::Intrinsic( name );
	assert( obj );
	cache[ key ] = obj;
	if( module )
	{
		module->add( obj );
	}
	
	libnovel::Reference* ra = obj->in(  "a", ta->getType() );
	libnovel::Reference* rb = obj->in(  "b", tb->getType() );
	libnovel::Reference* rt = obj->out( "t", tt->getType() );
	
	libnovel::Scope* scope = new libnovel::ParallelScope( obj );
	
	libnovel::Value* rav = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(0) );
	libnovel::Value* rad = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(1) );
	libnovel::Value* rbv = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(0) );
	libnovel::Value* rbd = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(1) );
    libnovel::Value* rtv = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(0) );
	libnovel::Value* rtd = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(1) );
	
	libnovel::Value* lav  = new libnovel::LoadInstruction( rav );
	libnovel::Value* lad  = new libnovel::LoadInstruction( rad );
	libnovel::Value* lbv  = new libnovel::LoadInstruction( rbv );
	libnovel::Value* lbd  = new libnovel::LoadInstruction( rbd );
	
	
	libnovel::Statement* stmt_d = new libnovel::TrivialStatement( scope );
	libnovel::Value* def = libnovel::BitConstant::create( 1, 1 );
	if( module )
	{
		module->add( def );
	}
	libnovel::Value* scd = new libnovel::StoreInstruction( def, rtd );
	stmt_d->add( scd );
	
	
	libnovel::Value* check = new libnovel::AndInstruction( lad, lbd );
	libnovel::Statement* br = new libnovel::BranchStatement( scope );
	br->add( rtv );
	br->add( check );
	
	libnovel::Scope* br_true = new libnovel::ParallelScope();
    br->addScope( br_true );
    libnovel::Value* equ_v = new libnovel::EquUnsignedInstruction( lav, lbv );
	libnovel::Value* equ_s = new libnovel::StoreInstruction( equ_v, rtv );
	libnovel::Statement* st_true = new libnovel::TrivialStatement( br_true );
	st_true->add( equ_s );

	libnovel::Scope* br_false = new libnovel::ParallelScope();
    br->addScope( br_false );
    libnovel::Value* equ_x = new libnovel::XorInstruction( lad, lbd );
	libnovel::Value* equ_y = new libnovel::NotInstruction( equ_x );
	libnovel::Value* equ_u = new libnovel::StoreInstruction( equ_y, rtv );
	libnovel::Statement* st_false = new libnovel::TrivialStatement( br_false );
	st_false->add( equ_u );
	
	return obj;	
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
