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

// | AND   | undef | false | true  | sym   |
// |-------+-------+-------+-------+-------|
// | undef | undef | false | undef | sym'  |
// | false | false | false | false | false |
// | true  | undef | false | true  | sym'  |
// | sym   | sym'  | false | sym'  | sym'  |

static const auto id = Value::ID::AND_INSTRUCTION;

static const auto type = libstdhl::get< RelationType >(
    libstdhl::get< BooleanType >(),
    Types(
        { libstdhl::get< BooleanType >(), libstdhl::get< BooleanType >() } ) );

#define CALC_( LHS, RHS )                                                      \
    const auto lhs = BooleanConstant( LHS );                                   \
    const auto rhs = BooleanConstant( RHS );                                   \
    const auto res = libcasm_rt::Value::execute( id, *type, lhs, rhs );

#define TEST_( NAME, RES, LHS, RHS )                                           \
    TEST( libcasm_rt__instruction_and_boolean_boolean, NAME )                  \
    {                                                                          \
        CALC_( LHS, RHS );                                                     \
        EXPECT_TRUE( res == BooleanConstant( RES ) );                          \
        EXPECT_STREQ( res.description().c_str(),                               \
            BooleanConstant( RES ).description().c_str() );                    \
    }

BENCHMARK(
    libcasm_rt__instruction_and_boolean_boolean, one_word_no_wrap, 10, 10 )
{
    CALC_( true, false );
}

TEST_( undef__at__undef__undef, , , );
TEST_( false__at__false__undef, false, false, );
TEST_( undef__at__true___undef, , true, );

TEST_( false__at__undef__false, false, , false );
TEST_( false__at__false__false, false, false, false );
TEST_( false__at__true___false, false, true, false );

TEST_( undef__at__undef__true_, , , true );
TEST_( false__at__false__true_, false, false, true );
TEST_( true___at__true___true_, true, true, true );

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
