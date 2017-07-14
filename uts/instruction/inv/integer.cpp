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

static const auto id = Value::ID::INV_INSTRUCTION;

static const auto type
    = libstdhl::get< RelationType >( libstdhl::get< IntegerType >(),
        Types( { libstdhl::get< IntegerType >() } ) );

#define CALC_( ARG )                                                           \
    const auto arg = IntegerConstant( ARG );                                   \
    Constant res;                                                              \
    libcasm_rt::Value::execute( id, *type, res, arg );

#define TEST_( NAME, RES, ARG )                                                \
    TEST( libcasm_rt__instruction_inv_integer, NAME )                          \
    {                                                                          \
        CALC_( ARG );                                                          \
        EXPECT_TRUE( res == IntegerConstant( RES ) );                          \
        EXPECT_STREQ( res.description().c_str(),                               \
            IntegerConstant( RES ).description().c_str() );                    \
    }

BENCHMARK( libcasm_rt__instruction_inv_integer, example, 10, 10 )
{
    CALC_( 123 );
}

TEST_( undef__at__undef, , );
TEST_( zero___at__zero_, 0, 0 );
TEST_( neg1___at__pos1_, -1, 1 );
TEST_( pos1___at__neg1_, 1, -1 );
TEST_( short__at__short, -123, 123 );
TEST_( long___at__long_, 123456789, -123456789 );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
