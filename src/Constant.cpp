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

#include "Constant.h"

using namespace libcasm_rt;


libnovel::Value* Constant::create( libnovel::Type& type )
{
	libnovel::Value* c = 0;
	
	if( type.getIDKind() == libnovel::Type::STRUCTURE )
	{
		libnovel::Value* b = type.getBound();
		assert( b and libnovel::Value::isa< libnovel::Structure >( b ) );
		libnovel::Structure* s = (libnovel::Structure*)b;
		c = libnovel::StructureConstant::create( s );
	}
	else
	{
		assert( !"unsupported type to create constant found!" );
	}
	
	assert( c );
	return c;
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
