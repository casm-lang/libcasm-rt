//  
//  Copyright (c) 2015 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
//  
//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal with the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//  
//  * Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimers.
//  
//  * Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimers in the 
//    documentation and/or other materials provided with the distribution.
//  
//  * Neither the names of the copyright holders, nor the names of its 
//    contributors may be used to endorse or promote products derived from 
//    this Software without specific prior written permission.
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


TEST( Int, clr )
{
	static libcasmrt_Int t;
	
	libcasmrt_clr_Int( &t );
	
	ASSERT_EQ( t.isdef, false );
}

TEST( Int, set )
{	
	static libcasmrt_Int t;

	libcasmrt_clr_Int( &t );
	
	ASSERT_NE( t.isdef, true );
	ASSERT_NE( t.value, 0xc0de );
	
	libcasmrt_set_Int_i64( &t, 0xc0de );
	
	ASSERT_EQ( t.isdef, true );
	ASSERT_EQ( t.value, 0xc0de );
}

TEST( Int, mov )
{	
	static libcasmrt_Int t;
	static libcasmrt_Int a;

	libcasmrt_clr_Int( &t );
	libcasmrt_clr_Int( &a );
	
	ASSERT_NE( t.isdef, true );
	ASSERT_NE( t.value, 0xc0de );
	ASSERT_NE( a.isdef, true );
	ASSERT_NE( a.value, 0xc0de );
    
	libcasmrt_set_Int_i64( &a, 0xc0de );
	libcasmrt_mov_Int_Int( &t, &a );
	
	ASSERT_EQ( t.isdef, true );
	ASSERT_EQ( t.value, 0xc0de );
	ASSERT_EQ( a.isdef, true );
	ASSERT_EQ( a.value, 0xc0de );
}

#define TEST_LIBCASMRT_INT( CASE, RET, OPSTR, TV, TD, LV, LD, RV, RD )	\
	TEST( Int, OPSTR##_##case##_##CASE )								\
	{																	\
		struct libcasmrt_##RET t;										\
		struct libcasmrt_Int a;											\
		struct libcasmrt_Int b;											\
																		\
		libcasmrt_set_Int_i64( &a, LV );								\
		a.isdef = LD;													\
																		\
		libcasmrt_set_Int_i64( &b, RV );								\
		b.isdef = RD;													\
																		\
		libcasmrt_##OPSTR##_##RET##_Int_Int( &t, &a, &b );				\
																		\
		ASSERT_EQ( t.isdef, TD );										\
		ASSERT_EQ( t.value, TV );										\
	}

#define TEST_LIBCASMRT_INT_T( CASE, RET, OPSTR, OP, LV, RV )			\
	TEST_LIBCASMRT_INT( tt##CASE, RET, OPSTR, LV OP RV, true, LV, true, RV, true )

#define TEST_LIBCASMRT_INT_F( CASE, RET, OPSTR, OP, LV, RV )			\
	TEST_LIBCASMRT_INT( ff##CASE, RET, OPSTR, LV OP RV, false, LV, false, RV, false ) \
	TEST_LIBCASMRT_INT( ft##CASE, RET, OPSTR, LV OP RV, false, LV, false, RV, true  ) \
	TEST_LIBCASMRT_INT( tf##CASE, RET, OPSTR, LV OP RV, false, LV, true,  RV, false )

#define TEST_LIBCASMRT_INT_D( RET, OPSTR, OP )				\
	TEST_LIBCASMRT_INT_T( 0, RET, OPSTR, OP,    10,    20 )	\
	TEST_LIBCASMRT_INT_T( 1, RET, OPSTR, OP,     1,    10 )	\
	TEST_LIBCASMRT_INT_T( 2, RET, OPSTR, OP,    33,    99 )	\
	TEST_LIBCASMRT_INT_T( 3, RET, OPSTR, OP,     1,     1 )	\
	TEST_LIBCASMRT_INT_T( 4, RET, OPSTR, OP, -1234,  9876 )	\
	TEST_LIBCASMRT_INT_T( 5, RET, OPSTR, OP, -9999,  1234 )	\
	TEST_LIBCASMRT_INT_T( 7, RET, OPSTR, OP, -8765, -4321 )	\
	TEST_LIBCASMRT_INT_T( 8, RET, OPSTR, OP,  2015,  2015 )	\
	TEST_LIBCASMRT_INT_T( 9, RET, OPSTR, OP, -1970, -1970 )

#define TEST_LIBCASMRT_INT_U( RET, OPSTR, OP )			\
	TEST_LIBCASMRT_INT_F( 0, RET, OPSTR, OP,  4,  7 )	\
	TEST_LIBCASMRT_INT_F( 1, RET, OPSTR, OP, -4,  7 )	\
	TEST_LIBCASMRT_INT_F( 2, RET, OPSTR, OP, -4, -4 )

#define TEST_LIBCASMRT_INT_C( RET, OPSTR, OP )	\
	TEST_LIBCASMRT_INT_D( RET, OPSTR, OP )		\
	TEST_LIBCASMRT_INT_U( RET, OPSTR, OP )

TEST_LIBCASMRT_INT_C( Int,  add, + )
TEST_LIBCASMRT_INT_C( Int,  sub, - )
TEST_LIBCASMRT_INT_C( Int,  mul, * )
TEST_LIBCASMRT_INT_C( Int,  div, / )
TEST_LIBCASMRT_INT_C( Int,  mod, % )
TEST_LIBCASMRT_INT_C( Bool, lth, <  )
TEST_LIBCASMRT_INT_C( Bool, gth, >  )

TEST_LIBCASMRT_INT_D( Bool, leq, <= )
TEST_LIBCASMRT_INT( ff0, Bool, leq, true,  true,   4, false,  7, false )
TEST_LIBCASMRT_INT( ff1, Bool, leq, true,  true,  -4, false,  7, false )
TEST_LIBCASMRT_INT( ff2, Bool, leq, true,  true,   4, false, -7, false )
TEST_LIBCASMRT_INT( ft0, Bool, leq, true,  false,  4, false,  7, true  )
TEST_LIBCASMRT_INT( ft1, Bool, leq, true,  false, -4, false,  7, true  )
TEST_LIBCASMRT_INT( ft2, Bool, leq, false, false,  4, false, -7, true  )
TEST_LIBCASMRT_INT( tf0, Bool, leq, true , false,  4, true,   7, false )
TEST_LIBCASMRT_INT( tf1, Bool, leq, true,  false, -4, true,   7, false )
TEST_LIBCASMRT_INT( tf2, Bool, leq, false, false,  4, true,  -7, false )

TEST_LIBCASMRT_INT_D( Bool, geq, >= )
TEST_LIBCASMRT_INT( ff0, Bool, geq, true,  true,   4, false,  7, false )
TEST_LIBCASMRT_INT( ff1, Bool, geq, true,  true,  -4, false,  7, false )
TEST_LIBCASMRT_INT( ff2, Bool, geq, true,  true,   4, false, -7, false )
TEST_LIBCASMRT_INT( ft0, Bool, geq, false, false,  4, false,  7, true  )
TEST_LIBCASMRT_INT( ft1, Bool, geq, false, false, -4, false,  7, true  )
TEST_LIBCASMRT_INT( ft2, Bool, geq, true,  false,  4, false, -7, true  )
TEST_LIBCASMRT_INT( tf0, Bool, geq, false, false,  4, true,   7, false )
TEST_LIBCASMRT_INT( tf1, Bool, geq, false, false, -4, true,   7, false )
TEST_LIBCASMRT_INT( tf2, Bool, geq, true,  false,  4, true,  -7, false )

TEST_LIBCASMRT_INT_D( Bool, equ, == )
TEST_LIBCASMRT_INT( ff0, Bool, equ, true,  true,   4, false,  7, false )
TEST_LIBCASMRT_INT( ff1, Bool, equ, true,  true,   7, false,  7, false )
TEST_LIBCASMRT_INT( ff2, Bool, equ, true,  true,  -7, false, -7, false )
TEST_LIBCASMRT_INT( ft0, Bool, equ, false, true,   4, false,  7, true  )
TEST_LIBCASMRT_INT( ft1, Bool, equ, false, true,   7, false,  7, true  )
TEST_LIBCASMRT_INT( ft2, Bool, equ, false, true,  -7, false, -7, true  )
TEST_LIBCASMRT_INT( tf0, Bool, equ, false, true,   4, true,   7, false )
TEST_LIBCASMRT_INT( tf1, Bool, equ, false, true,   7, true,   7, false )
TEST_LIBCASMRT_INT( tf2, Bool, equ, false, true,  -7, true,  -7, false )

TEST_LIBCASMRT_INT_D( Bool, neq, != )
TEST_LIBCASMRT_INT( ff0, Bool, neq, false, true,   4, false,  7, false )
TEST_LIBCASMRT_INT( ff1, Bool, neq, false, true,   7, false,  7, false )
TEST_LIBCASMRT_INT( ff2, Bool, neq, false, true,  -7, false, -7, false )
TEST_LIBCASMRT_INT( ft0, Bool, neq, true,  true,   4, false,  7, true  )
TEST_LIBCASMRT_INT( ft1, Bool, neq, true,  true,   7, false,  7, true  )
TEST_LIBCASMRT_INT( ft2, Bool, neq, true,  true,  -7, false, -7, true  )
TEST_LIBCASMRT_INT( tf0, Bool, neq, true,  true,   4, true,   7, false )
TEST_LIBCASMRT_INT( tf1, Bool, neq, true,  true,   7, true,   7, false )
TEST_LIBCASMRT_INT( tf2, Bool, neq, true,  true,  -7, true,  -7, false )


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  