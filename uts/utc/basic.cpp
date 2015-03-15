
/*
  Copyright (c) 2015 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#include "gtest/gtest.h"

TEST( basic, true_witness  )
{
    ASSERT_EQ( 0, 0 );
}

TEST( basic, false_witness  )
{
    ASSERT_NE( 0, 1 );
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
