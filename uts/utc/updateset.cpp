//  
//  Copyright (c) 2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
//  
//  This software is licensed under the Open Software License v. 3.0 (OSL-3.0).
//  You either find the license text below or in the root directory of this 
//  project in the LICENSE.txt file. If you cannot find the LICENSE.txt file,
//  please refer to https://opensource.org/licenses/OSL-3.0.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
//  WITH THE SOFTWARE.
//  

#include "gtest/gtest.h"
#include "casm-rt.h"


static libcasm_rt_updateset* uset = 0;

static stdll_mem mem;

TEST( updateset, create )
{
	
	// create a 32 MB memory pool
	ASSERT_EQ( 0, stdll_mem_new( &mem, 1024*1024*32 ) );
	
	// create a uset of 12345 start elements
	ASSERT_NE( (void*)0, uset = libcasm_rt_updateset_new( &mem, 20/*12345*/ ) );	
}


TEST( updateset, insert )
{
	ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, 0xfeed, ~0xfeed ) );
	ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, 0xdead, ~0xdead ) );

	libcasm_rt_updateset_dump( uset );
}

TEST( updateset, iterate )
{
	ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, 0xfeed, ~0xfeed ) );
	ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, 0xdead, ~0xdead ) );

	// libcasm_rt_updateset_iterator* it =
	// 	libcasm_rt_updateset_get_iterator( uset );

	
	// u8 libcasm_rt_updateset_iterator_next( libcasm_rt_updateset_iterator* iter, uint64_t* location, uint64_t* value );

	
	libcasm_rt_updateset_dump( uset );
}

TEST( updateset, fork )
{
	ASSERT_EQ( 0, libcasm_rt_updateset_fork( uset ) );
}

TEST( updateset, insert2 )
{
	uint64_t c;
	
	for( c = 0; c < 5; c++ )
	{
		uint64_t loc = 0xbeef0000 + c;
		
		ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, loc, ~loc ) );
	}

	// libcasm_rt_updateset_dump( uset );
}

TEST( updateset, merge )
{
	ASSERT_EQ( 0, libcasm_rt_updateset_merge( uset ) );
	
	// libcasm_rt_updateset_dump( uset );
}

TEST( updateset, destroy )
{
	ASSERT_EQ( 0, libcasm_rt_updateset_del( uset ) );
}

TEST( updateset, scenario_fork_insert_fork_insert_merge_insert_merge )
{
	uint64_t c;
	uint64_t loc;
	
	ASSERT_NE( (void*)0, uset = libcasm_rt_updateset_new( &mem, 50 ) );	

	// printf( "pre-fork\n" );
	// libcasm_rt_updateset_dump( uset );

	ASSERT_EQ( 0, libcasm_rt_updateset_fork( uset ) );

	for( c = 0; c < 2; c++ )
	{
		loc = 0xaaaa + c;
		ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, loc, ~loc ) );
	}

	// printf( "fork+insert\n" );
	// libcasm_rt_updateset_dump( uset );

	ASSERT_EQ( 0, libcasm_rt_updateset_fork( uset ) );

	for( c = 0; c < 2; c++ )
	{
		loc = 0xbbbb + c;
		ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, loc, ~loc ) );
	}

	// printf( "fork+insert, pre-merge\n" );
	// libcasm_rt_updateset_dump( uset );

	ASSERT_EQ( 0, libcasm_rt_updateset_merge( uset ) );

	// printf( "post-merge\n" );
	// libcasm_rt_updateset_dump( uset );

	for( c = 0; c < 2; c++ )
	{
		loc = 0xcccc + c;
		ASSERT_EQ( 0, libcasm_rt_updateset_insert( uset, loc, ~loc ) );
	}

	// printf( "insert, pre-merge\n" );
	// libcasm_rt_updateset_dump( uset );
	
	ASSERT_EQ( 0, libcasm_rt_updateset_merge( uset ) );
	
	// printf( "post-merge\n" );
	// libcasm_rt_updateset_dump( uset );

	ASSERT_EQ( 0, libcasm_rt_updateset_del( uset ) );
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
