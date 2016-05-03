//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
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
    else
	{
		assert( !" unsupported/unimplemented instruction to create run-time implementation! " );
    }
	
	return 0;
}


// libnovel::CallableUnit* AddInstruction::create( libcasm_ir::Value& value, libnovel::Module* module )
// {
// 	return ArithmeticInstruction< libnovel::AddSignedInstruction >::create( value, module );
// }

// libnovel::CallableUnit* DivInstruction::create( libcasm_ir::Value& value, libnovel::Module* module )
// {
// 	return ArithmeticInstruction< libnovel::DivSignedInstruction >::create( value, module );
// }


template< class INSTR >
libnovel::CallableUnit* ArithmeticInstruction< INSTR >::create( libcasm_ir::Value& value, libnovel::Module* module )
{
	assert( libcasm_ir::Value::isa< libcasm_ir::Instruction >( &value ) );
	
	static std::unordered_map< std::string, std::unordered_map< libnovel::Structure*, libnovel::CallableUnit* > > cache;
	
	libnovel::Structure* key = libcasm_rt::Type::create( value );
	std::string key_name = std::string( &value.getName()[1] );
	if( cache.count( key_name ) > 0 )
	{
		if( cache[ key_name ].count( key ) > 0 )
		{
			return cache[ key_name ][ key ];
		}
	}
	
	const char* name = libstdhl::Allocator::string
	( "casm_rt__instr_"
	+ key_name
	+ "_"
	+ std::string( key->getName() )
	);
	
	libnovel::CallableUnit* obj = new libnovel::Intrinsic( name );
	assert( obj );
	cache[ key_name ][ key ] = obj;
	if( module )
	{
		module->add( obj );
	}
	
	libnovel::Reference* ra = obj->in(  "a", key->getType() );
	libnovel::Reference* rb = obj->in(  "b", key->getType() );
	libnovel::Reference* rt = obj->out( "t", key->getType() );
	
	libnovel::Scope* scope = 0; //new libnovel::ParallelScope( obj );
	if( strcmp( key_name.c_str(), "div" ) == 0 ) // TODO: EXPERIMENTIAL: DEMO ONLY!!!
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





//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
