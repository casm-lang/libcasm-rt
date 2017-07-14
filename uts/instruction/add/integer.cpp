//
//  Copyright (c) 2014-2017 CASM Organization
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

#include "uts/main.h"

using namespace libcasm_ir;

static const auto id = Value::ID::ADD_INSTRUCTION;

static const auto type = libstdhl::get< RelationType >(
    libstdhl::get< IntegerType >(),
    Types(
        { libstdhl::get< IntegerType >(), libstdhl::get< IntegerType >() } ) );

#define CALC_( LHS, RHS )                                                      \
    const auto lhs = IntegerConstant( LHS );                                   \
    const auto rhs = IntegerConstant( RHS );                                   \
    Constant res;                                                              \
    libcasm_rt::Value::execute( id, *type, res, lhs, rhs );

#define TEST_( NAME, RES, LHS, RHS )                                           \
    TEST( libcasm_rt__instruction_add_integer_integer, NAME )                  \
    {                                                                          \
        CALC_( LHS, RHS );                                                     \
        EXPECT_TRUE( res == IntegerConstant( RES ) );                          \
        EXPECT_STREQ( res.description().c_str(),                               \
            IntegerConstant( RES ).description().c_str() );                    \
    }

BENCHMARK(
    libcasm_rt__instruction_add_integer_integer, one_word_no_wrap, 10, 10 )
{
    CALC_( 123, 456 );
}

TEST_( undef__at__undef__undef, , , );
TEST_( undef__at__zero___undef, , 0, );
TEST_( undef__at__undef__zero_, , , 0 );
TEST_( undef__at__pos1___undef, , 1, );
TEST_( undef__at__undef__pos1_, , , 1 );
TEST_( undef__at__neg1___undef, , -1, );
TEST_( undef__at__undef__neg1_, , , -1 );

TEST_( pos__at_pos__pos, 35, 12, 23 );
TEST_( pos__at_pos__neg, -11, 12, -23 );
TEST_( pos__at_neg__neg, -35, -12, -23 );
TEST_( pos__at_neg__pos, 11, -12, 23 );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
