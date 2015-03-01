
/*
  Copyright (c) 2014 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#include "gtest/gtest.h"

#include "stdll.h"
#include "updateset.h"

static casmrt_updateset* uset = 0;

static stdll_mem mem;

TEST( updateset, create )
{
	
	// create a 32 MB memory pool
	ASSERT_EQ( 0, stdll_mem_new( &mem, 1024*1024*32 ) );
	
	// create a uset of 12345 start elements
	ASSERT_NE( (void*)0, uset = casmrt_updateset_new( &mem, 20/*12345*/ ) );	
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

TEST( updateset, insert2 )
{
	uint64_t c;
	
	for( c = 0; c < 5; c++ )
	{
		uint64_t loc = 0xbeef0000 + c;
		
		ASSERT_EQ( 0, casmrt_updateset_insert( uset, loc, ~loc ) );
	}

	casmrt_updateset_dump( uset );
}

TEST( updateset, merge )
{
	ASSERT_EQ( 0, casmrt_updateset_merge( uset ) );
	
	casmrt_updateset_dump( uset );
}

TEST( updateset, destroy )
{
	ASSERT_EQ( 0, casmrt_updateset_del( uset ) );
}

TEST( updateset, scenario_fork_insert_fork_insert_merge_insert_merge )
{
	uint64_t c;
	uint64_t loc;
	
	ASSERT_NE( (void*)0, uset = casmrt_updateset_new( &mem, 50 ) );	

	printf( "pre-fork\n" );
	casmrt_updateset_dump( uset );

	ASSERT_EQ( 0, casmrt_updateset_fork( uset ) );

	for( c = 0; c < 2; c++ )
	{
		loc = 0xaaaa + c;
		ASSERT_EQ( 0, casmrt_updateset_insert( uset, loc, ~loc ) );
	}

	printf( "fork+insert\n" );
	casmrt_updateset_dump( uset );

	ASSERT_EQ( 0, casmrt_updateset_fork( uset ) );

	for( c = 0; c < 2; c++ )
	{
		loc = 0xbbbb + c;
		ASSERT_EQ( 0, casmrt_updateset_insert( uset, loc, ~loc ) );
	}

	printf( "fork+insert, pre-merge\n" );
	casmrt_updateset_dump( uset );

	ASSERT_EQ( 0, casmrt_updateset_merge( uset ) );

	printf( "post-merge\n" );
	casmrt_updateset_dump( uset );

	for( c = 0; c < 2; c++ )
	{
		loc = 0xcccc + c;
		ASSERT_EQ( 0, casmrt_updateset_insert( uset, loc, ~loc ) );
	}

	printf( "insert, pre-merge\n" );
	casmrt_updateset_dump( uset );
	
	ASSERT_EQ( 0, casmrt_updateset_merge( uset ) );
	
	printf( "post-merge\n" );
	casmrt_updateset_dump( uset );

	ASSERT_EQ( 0, casmrt_updateset_del( uset ) );
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
