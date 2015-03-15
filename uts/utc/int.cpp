
/*
  Copyright (c) 2015 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#include "gtest/gtest.h"
#include "stdll/c/stdll.h"

#include "int.h"

static libcasmrt_Int t;

static libcasmrt_Int a;
static libcasmrt_Int b;
static libcasmrt_Int c;

TEST( Int, test )
{

	libcasmrt_clr_Int( &a );
	
	libcasmrt_set_Int_i64( &a, 10 );
	
	libcasmrt_clr_Int( &a );

	libcasmrt_set_Int_i64( &a, 20 );
	
	ASSERT_NE( b.value, a.value );
	ASSERT_NE( b.isdef, a.isdef );
	
	libcasmrt_mov_Int_Int( &b, &a );
	
	ASSERT_EQ( b.value, a.value );
	ASSERT_EQ( b.isdef, a.isdef );
	
	libcasmrt_add_Int_Int_Int( &c, &a, &b );
	
	ASSERT_EQ( c.value, a.value +  b.value );
	ASSERT_EQ( c.isdef, a.isdef && b.isdef );	
}

TEST( Int, clr )
{
	libcasmrt_clr_Int( &t );
	
	ASSERT_EQ( t.isdef, false );
}

TEST( Int, set )
{	
	libcasmrt_clr_Int( &t );
	
	ASSERT_NE( t.isdef, true );
	ASSERT_NE( t.value, 0xc0de );
	
	libcasmrt_set_Int_i64( &t, 0xc0de );
	
	ASSERT_EQ( t.isdef, true );
	ASSERT_EQ( t.value, 0xc0de );
}

TEST( Int, add )
{
	struct libcasmrt_Int t;
	struct libcasmrt_Int a;
	struct libcasmrt_Int b;
	
	libcasmrt_set_Int_i64( &a, 12 );
	libcasmrt_set_Int_i64( &b, 34 );
	
	libcasmrt_add_Int_Int_Int( &t, &a, &b );
	
	ASSERT_EQ( t.isdef, true );
	ASSERT_EQ( t.value, 12 + 34 );
}

static const libcasmrt_Int test_vector[][3] =
{ { { 20, true }, { 10, true } }
, { { 0, 0 }, { 0, 0 } }
};




#define TEST_LIBCASMRT_INT( CASE, RET, OPSTR, TV, TD, LV, LD, RV, RD )	\
	TEST( Int, OPSTR##_##case##_##CASE )								\
	{																	\
		struct libcasmrt_##RET t;										\
		struct libcasmrt_Int a;											\
		struct libcasmrt_Int b;											\
																		\
	    if( LD )														\
		{																\
			libcasmrt_set_Int_i64( &a, LV );							\
		}																\
		else															\
		{																\
			libcasmrt_clr_Int( &a );									\
		}																\
																		\
		if( RD )														\
		{																\
			libcasmrt_set_Int_i64( &b, RV );							\
		}																\
		else															\
		{																\
			libcasmrt_clr_Int( &b );									\
		}																\
																		\
		libcasmrt_##OPSTR##_##RET##_Int_Int( &t, &a, &b );				\
																		\
		ASSERT_EQ( t.isdef, TD );										\
		ASSERT_EQ( t.value, TV );										\
	}

#define TEST_LIBCASMRT_INT_C( CASE, RET, OPSTR, OP, LV, RV )			\
	TEST_LIBCASMRT_INT( CASE, RET, OPSTR, LV OP RV, true, LV, true, RV, true )

#define TEST_LIBCASMRT_INT_V( RET, OPSTR, OP )			\
	TEST_LIBCASMRT_INT_C( t0, RET, OPSTR, OP, 10, 20 )	\
	TEST_LIBCASMRT_INT_C( t1, RET, OPSTR, OP,  1, 10 )	\
	TEST_LIBCASMRT_INT_C( t2, RET, OPSTR, OP, 33, 99 )	\
	TEST_LIBCASMRT_INT_C( t3, RET, OPSTR, OP,  1,  1 )


TEST_LIBCASMRT_INT_V( Int, add, + )
TEST_LIBCASMRT_INT_V( Int, sub, - )
TEST_LIBCASMRT_INT_V( Int, mul, * )
TEST_LIBCASMRT_INT_V( Int, div, / )
TEST_LIBCASMRT_INT_V( Int, rem, % )

TEST_LIBCASMRT_INT_V( Bool, lth, <  )
TEST_LIBCASMRT_INT_V( Bool, leq, <= )
TEST_LIBCASMRT_INT_V( Bool, gth, >  )
TEST_LIBCASMRT_INT_V( Bool, geq, >= )
TEST_LIBCASMRT_INT_V( Bool, equ, == )
TEST_LIBCASMRT_INT_V( Bool, neq, != )

TEST_LIBCASMRT_INT( f0, Bool, equ, 4 == 4, false, 4, true, 4, false )







/*
  Local variables:
  mode: c++
  indent-tabs-mode: t
  c-basic-offset: 4
  tab-width: 4
  End:
  vim:noexpandtab:sw=4:ts=4:
*/
