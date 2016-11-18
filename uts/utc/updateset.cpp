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

#include "casm-rt.h"
#include "gtest/gtest.h"

static libcasm_rt_updateset* uset = 0;

static stdll_mem mem;

TEST( updateset, create )
{

    // create a 32 MB memory pool
    ASSERT_EQ( 0, stdll_mem_new( &mem, 1024 * 1024 * 32 ) );

    // create a uset of 12345 start elements
    ASSERT_NE(
        (void*)0, uset = libcasm_rt_updateset_new( &mem, 20 /*12345*/ ) );
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

    // u8 libcasm_rt_updateset_iterator_next( libcasm_rt_updateset_iterator*
    // iter, uint64_t* location, uint64_t* value );

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
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
