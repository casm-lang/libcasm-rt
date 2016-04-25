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

#include "Type.h"

using namespace libcasm_rt;


libnovel::Structure* Type::create( libcasm_ir::Value& value )
{
	libcasm_ir::Type* type = value.getType();
    assert( type and " invalid type pointer! " );
	
	assert( type->getSubTypes().size() == 0 ); // PPA: LIMITATION for now!
	
	u64 tid = type->getResultType()->getID();
	
	if( tid == libcasm_ir::IntegerType.getID() )
	{
		return Integer::create();
	}
	else if( tid == libcasm_ir::RulePointerType.getID() )
	{
		return RulePtr::create();
	}
	else
	{
		assert( !" unsupported/unimplemented type id! " );
		return 0;
	}
}



static libnovel::Structure* type_factory
( const std::string& name
, const std::vector< const char* >& args
, const std::vector< libnovel::Type* >& argt
)
{
	//assert( args.size() == argv.size() and " invalid argument lists for 'name' and 'type' provided! " );
	
	libnovel::Structure* type = new libnovel::Structure( libstdhl::Allocator::string( name.c_str() ) );
	assert( type );
	type->getType()->bind( type );

	u32 c = 0;
	while( args[ c ] != 0 )
	{
		libnovel::Structure* arg = new libnovel::Structure
		( args[ c ]
		, argt[ c ]
		, type
		);
		assert( arg );
		c++;
	}
	
	return type;
}


libnovel::Structure* Integer::create( void )
{
	libnovel::Structure* type = 0;
	if( not type )
	{
		type = type_factory
		( "Integer"
		, { "value",            "isdef",           0 }
		, { &libnovel::TypeB64, &libnovel::TypeB1, 0 }
		);
	}
	return type;
}

libnovel::Structure* RulePtr::create( void )
{
	libnovel::Structure* type = 0;
	if( not type )
	{
		type = type_factory
		( "RulePtr"
		, { "value",           "isdef",           0 }
		, { &libnovel::TypeId, &libnovel::TypeB1, 0 }
		);
	}
	return type;
}



libnovel::Structure* Update::create( void )
{
	libnovel::Structure* type = 0;
	if( not type )
	{
		type = type_factory
		( "Update"
		, { "isused", "location", "value", "isdef", 0 }
		, { &libnovel::TypeB1, &libnovel::TypeId, &libnovel::TypeB64, &libnovel::TypeB1, 0 }
		);
	}
	return type;
}

libnovel::Memory* UpdateSet::create( void )
{
	libnovel::Memory* type = 0;
	if( not type )
	{
		type = new libnovel::Memory( Update::create(), 32 );
	}
	return type;	
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
