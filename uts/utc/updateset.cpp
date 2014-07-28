
/*
  Copyright (c) 2014 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#include "gtest/gtest.h"

#include "stdll.h"
#include "updateset.h"

casmrt_updateset* uset = 0;


TEST( updateset, create )
{
	stdll_mem mem;
	
	// create a 32 MB memory pool
	ASSERT_EQ( 0, stdll_mem_new( &mem, 1024*1024*32 ) );
	
	// create a uset of 511 start elements
    uset = casmrt_updateset_new( &mem, 12345 );
	
	ASSERT_NE( (void*)0, uset );	
}


TEST( updateset, insert )
{
	ASSERT_EQ( 0, casmrt_updateset_insert( uset, 0xfeed, ~0xfeed ) );
	ASSERT_EQ( 0, casmrt_updateset_insert( uset, 0xdead, ~0xdead ) );
}

TEST( updateset, fork )
{
	ASSERT_EQ( 0, casmrt_updateset_fork( uset ) );
}

TEST( updateset, insert1000 )
{
	uint64_t c;
	
	for( c = 0; c < 1000; c++ )
	{
		uint64_t loc = 0xbeef0000 + c;
		
		ASSERT_EQ( 0, casmrt_updateset_insert( uset, loc, ~loc ) );
	}
}

TEST( updateset, merge )
{
	ASSERT_EQ( 0, casmrt_updateset_merge( uset ) );
}




/*
  Local variables:
  mode: c++
  indent-tabs-mode: t
  c-basic-offset: 4
  tab-width: 4
  End:
  vim:noexpandtab:sw=4:ts=4:
*/
