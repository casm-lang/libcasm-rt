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

#include "Update.h"

using namespace libcasm_rt;


libnovel::CallableUnit* UpdateImplementation::create( libcasm_ir::UpdateInstruction& value )
{
	static libnovel::Intrinsic* update_implementation = 0;
	
	if( !update_implementation )
	{
		update_implementation = new libnovel::Intrinsic( "casm_rt__update" );
		assert( update_implementation );
		
		libnovel::Reference* uset = new libnovel::Reference
		( "uset"
		, libcasm_rt::UpdateSet::create()->getType()
		, update_implementation
		);
		assert( uset );
		
		libnovel::Reference* loc = new libnovel::Reference
		( "uloc"
		, &libnovel::TypeId // ASSUMTION: PPA: addresses stay in the 48-bit range!
		, update_implementation
		);
		assert( loc );
		
		libnovel::Reference* val = new libnovel::Reference
		( "uval"
		, libcasm_rt::Integer::create()->getType() // ASSUMTION: PPA: values are numbers only for now!
		                                           // later, dyn ptr. too for SW-emit only!
		, update_implementation
		);
		assert( val );
		
		libnovel::SequentialScope* scope = new libnovel::SequentialScope();
		assert( scope );
		update_implementation->setContext( scope );

		libnovel::TrivialStatement* blk = new libnovel::TrivialStatement( scope );
		libnovel::StreamInstruction* output = new libnovel::StreamInstruction( libnovel::StreamInstruction::OUTPUT );
		assert( output );
		output->add( libnovel::StringConstant::create( "update" ) );
		output->add( &libnovel::StringConstant::LF );
	    blk->add( output );
	}
	
	return update_implementation;
}


libnovel::Variable* FunctionState::create( libcasm_ir::Function& value )
{
	static std::unordered_map< libcasm_ir::Function*, libnovel::Variable* > cache;
	if( cache.count( &value ) > 0 )
	{
		return cache[ &value ];
	}
	
	libnovel::Structure* ty = Type::create( *value.getType() );	
	libnovel::Variable* obj = new libnovel::Variable
	( ty->getType()
	, libcasm_rt::Constant::create( *ty->getType() )
	, libstdhl::Allocator::string( value.getName() )
	);
	assert( obj );
	
	if( strcmp( value.getName(), "program" ) == 0 )
	{
		ProgramFunctionState::create( obj );
	}

	cache[ &value ] = obj;
	return obj;
}


libnovel::CallableUnit* FunctionLocation::create( libcasm_ir::Function& value )
{
	std::string* name = new std::string( "casm_rt__location_" + std::string( value.getName() ));
	libnovel::Intrinsic* obj = new libnovel::Intrinsic( name->c_str() );
	assert( obj );
    
	libnovel::SequentialScope* scope = new libnovel::SequentialScope();
	assert( scope );
	obj->setContext( scope );
	
	libnovel::TrivialStatement* stmt = new libnovel::TrivialStatement( scope );
	libnovel::IdInstruction* id = new libnovel::IdInstruction( FunctionState::create( value ) );
	assert( id );
	
	// output parameter for intrinsic!
	libnovel::Reference* loc = new libnovel::Reference
   	( "location"
	, id->getType() // ASSUMTION: PPA: addresses stay in the 48-bit range!
	, obj
	, libnovel::Reference::OUTPUT
	);
    assert( loc );
	
	libnovel::StoreInstruction* store = new libnovel::StoreInstruction( id, loc );
	assert( store );
	stmt->add( store );
	
	return obj;
}	


libnovel::Variable* ProgramFunctionState::create( libnovel::Variable* value )
{
	static libnovel::Variable* obj = 0;
	
	if( not obj )
	{
		assert( not obj );
		obj = value;
	}

	assert( obj );
	return obj;
}


libnovel::CallableUnit* ProgramRuleSignature::create( void )
{
	static libnovel::CallableUnit* obj = 0;
	if( not obj )
	{
		obj = new libnovel::Function( "casm_rt____rule_signature" );
	    assert( obj );
	    libnovel::Reference* ref_mem = new libnovel::Reference
	    ( "ref_mem"
		, libcasm_rt::UpdateSet::create()->getType()
	    , obj
	    );
	    assert( ref_mem );
	}
	return obj;
}

/*

*/

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
