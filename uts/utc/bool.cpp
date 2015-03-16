
/*
  Copyright (c) 2015 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#include "gtest/gtest.h"
#include "stdll/c/stdll.h"

#include "bool.h"


TEST( Bool, clr )
{
    static libcasmrt_Bool t;
	
    libcasmrt_clr_Bool( &t );
	
    ASSERT_EQ( t.isdef, false );
}

TEST( Bool, set )
{	
    static libcasmrt_Bool t;
    
    libcasmrt_clr_Bool( &t );
	
    ASSERT_NE( t.isdef, true );
    ASSERT_NE( t.value, true );
	
    libcasmrt_set_Bool_i1( &t, true );
	
    ASSERT_EQ( t.isdef, true );
    ASSERT_EQ( t.value, true );
}

TEST( Bool, mov )
{	
	static libcasmrt_Bool t;
	static libcasmrt_Bool a;

	libcasmrt_clr_Bool( &t );
	libcasmrt_clr_Bool( &a );
	
	ASSERT_NE( t.isdef, true );
	ASSERT_NE( t.value, true );
	ASSERT_NE( a.isdef, true );
	ASSERT_NE( a.value, true );
    
	libcasmrt_set_Bool_i1( &a, true );
	libcasmrt_mov_Bool_Bool( &t, &a );
	
	ASSERT_EQ( t.isdef, true );
	ASSERT_EQ( t.value, true );
	ASSERT_EQ( a.isdef, true );
	ASSERT_EQ( a.value, true );
}

TEST( Bool, not )
{	
	static libcasmrt_Bool t;
	static libcasmrt_Bool a;

	libcasmrt_clr_Bool( &t );
	libcasmrt_clr_Bool( &a );
	
	ASSERT_NE( t.isdef, true );
	ASSERT_NE( t.value, true );
	ASSERT_NE( a.isdef, true );
	ASSERT_NE( a.value, true );
    
	libcasmrt_set_Bool_i1( &a, true );
	libcasmrt_not_Bool_Bool( &t, &a );
	
	ASSERT_EQ( t.isdef, true );
	ASSERT_EQ( t.value, false );
	ASSERT_EQ( a.isdef, true );
	ASSERT_EQ( a.value, true );
}

#define TEST_LIBCASMRT_BOOL( CASE, RET, OPSTR, TV, TD, LV, LD, RV, RD )	\
    TEST( Bool, OPSTR##_##case##_##CASE )                               \
    {                                                                   \
        struct libcasmrt_##RET t;                                       \
        struct libcasmrt_Bool a;                                        \
        struct libcasmrt_Bool b;                                        \
                                                                        \
        libcasmrt_set_Bool_i1( &a, LV );                                \
        a.isdef = LD;                                                   \
                                                                        \
        libcasmrt_set_Bool_i1( &b, RV );                                \
        b.isdef = RD;                                                   \
                                                                        \
        libcasmrt_##OPSTR##_##RET##_Bool_Bool( &t, &a, &b );            \
                                                                        \
        ASSERT_EQ( t.isdef, TD );                                       \
        ASSERT_EQ( t.value, TV );                                       \
    }

#define TEST_LIBCASMRT_BOOL_T( CASE, RET, OPSTR, OP, LV, RV )			\
    TEST_LIBCASMRT_BOOL( tt##CASE, RET, OPSTR, LV OP RV, true, LV, true, RV, true )

#define TEST_LIBCASMRT_BOOL_F( CASE, RET, OPSTR, OP, LV, RV )            \
    TEST_LIBCASMRT_BOOL( ff##CASE, RET, OPSTR, LV OP RV, false, LV, false, RV, false ) \
    TEST_LIBCASMRT_BOOL( ft##CASE, RET, OPSTR, LV OP RV, false, LV, false, RV, true  ) \
    TEST_LIBCASMRT_BOOL( tf##CASE, RET, OPSTR, LV OP RV, false, LV, true,  RV, false )

#define TEST_LIBCASMRT_BOOL_D( RET, OPSTR, OP )                  \
    TEST_LIBCASMRT_BOOL_T( 0, RET, OPSTR, OP, true,  true  )	\
    TEST_LIBCASMRT_BOOL_T( 1, RET, OPSTR, OP, true,  false )	\
    TEST_LIBCASMRT_BOOL_T( 2, RET, OPSTR, OP, false, true  )	\
    TEST_LIBCASMRT_BOOL_T( 3, RET, OPSTR, OP, false, false )

#define TEST_LIBCASMRT_BOOL_U( RET, OPSTR, OP )			\
    TEST_LIBCASMRT_BOOL_F( 0, RET, OPSTR, OP, true,  true  )	\
    TEST_LIBCASMRT_BOOL_F( 1, RET, OPSTR, OP, true,  false )	\
    TEST_LIBCASMRT_BOOL_F( 2, RET, OPSTR, OP, false, true  )	\
    TEST_LIBCASMRT_BOOL_F( 3, RET, OPSTR, OP, false, false )

#define TEST_LIBCASMRT_BOOL_C( RET, OPSTR, OP )          \
    TEST_LIBCASMRT_BOOL_D( RET, OPSTR, OP )		\
    TEST_LIBCASMRT_BOOL_U( RET, OPSTR, OP )

TEST_LIBCASMRT_BOOL_C( Bool, and, && )
TEST_LIBCASMRT_BOOL_C( Bool, or,  || )
TEST_LIBCASMRT_BOOL_C( Bool, xor, ^  )

TEST_LIBCASMRT_BOOL_D( Bool, equ, == )
TEST_LIBCASMRT_BOOL( ff0, Bool, equ, true,  true, true,  false, true,  false )
TEST_LIBCASMRT_BOOL( ff1, Bool, equ, true,  true, true,  false, false, false )
TEST_LIBCASMRT_BOOL( ff2, Bool, equ, true,  true, false, false, true,  false )
TEST_LIBCASMRT_BOOL( ff3, Bool, equ, true,  true, false, false, false, false )
TEST_LIBCASMRT_BOOL( ft0, Bool, equ, false, true, true,  false, true,  true  )
TEST_LIBCASMRT_BOOL( ft1, Bool, equ, false, true, true,  false, false, true  )
TEST_LIBCASMRT_BOOL( ft2, Bool, equ, false, true, false, false, true,  true  )
TEST_LIBCASMRT_BOOL( ft3, Bool, equ, false, true, false, false, false, true  )
TEST_LIBCASMRT_BOOL( tf0, Bool, equ, false, true, true,  true , true,  false )
TEST_LIBCASMRT_BOOL( tf1, Bool, equ, false, true, true,  true , false, false )
TEST_LIBCASMRT_BOOL( tf2, Bool, equ, false, true, false, true , true,  false )
TEST_LIBCASMRT_BOOL( tf3, Bool, equ, false, true, false, true , false, false )

TEST_LIBCASMRT_BOOL_D( Bool, neq, != )
TEST_LIBCASMRT_BOOL( ff0, Bool, neq, false, true, true,  false, true,  false )
TEST_LIBCASMRT_BOOL( ff1, Bool, neq, false, true, true,  false, false, false )
TEST_LIBCASMRT_BOOL( ff2, Bool, neq, false, true, false, false, true,  false )
TEST_LIBCASMRT_BOOL( ff3, Bool, neq, false, true, false, false, false, false )
TEST_LIBCASMRT_BOOL( ft0, Bool, neq, true,  true, true,  false, true,  true  )
TEST_LIBCASMRT_BOOL( ft1, Bool, neq, true,  true, true,  false, false, true  )
TEST_LIBCASMRT_BOOL( ft2, Bool, neq, true,  true, false, false, true,  true  )
TEST_LIBCASMRT_BOOL( ft3, Bool, neq, true,  true, false, false, false, true  )
TEST_LIBCASMRT_BOOL( tf0, Bool, neq, true,  true, true,  true , true,  false )
TEST_LIBCASMRT_BOOL( tf1, Bool, neq, true,  true, true,  true , false, false )
TEST_LIBCASMRT_BOOL( tf2, Bool, neq, true,  true, false, true , true,  false )
TEST_LIBCASMRT_BOOL( tf3, Bool, neq, true,  true, false, true , false, false )


/*
  Local variables:
  mode: c++
  indent-tabs-mode: t
  c-basic-offset: 4
  tab-width: 4
  End:
  vim:noexpandtab:sw=4:ts=4:
*/
