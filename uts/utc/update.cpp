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

#include "gtest/gtest.h"
#include "casm-rt.h"

static stdll_mem mem;


TEST( update, prolog )
{
	// create a 32 MB memory pool
	ASSERT_EQ( 0, stdll_mem_new( &mem, 1024*1024*32 ) );
}

TEST( update, new )
{
	libcasm_rt_update* u = 0;
	
	ASSERT_NE( (void*)0, u = libcasm_rt_update_new( &mem, 123, 1 ) );
	ASSERT_EQ( u->value, 123 );	
	ASSERT_EQ( u->isdef, 1 );
}

TEST( update, epilog )
{
	ASSERT_EQ( 0, stdll_mem_del( &mem ) );	
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
