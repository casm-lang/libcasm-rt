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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-rt is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-rt
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-rt. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-rt give you permission to link libcasm-rt
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-rt. If you modify libcasm-rt, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "Builtin.h"
#include "Type.h"

#include <libstdhl/Log>

#include <libcasm-ir/Builtin>
#include <libcasm-ir/Exception>
#include <libcasm-ir/Type>
#include <libcasm-ir/Value>

// #include "../csel-ir/src/CallableUnit.h"
// #include "../csel-ir/src/Instruction.h"
// #include "../csel-ir/src/Intrinsic.h"
// #include "../csel-ir/src/Reference.h"
// #include "../csel-ir/src/Scope.h"
// #include "../csel-ir/src/Statement.h"

using namespace libcasm_rt;

static inline libcasm_ir::Constant evaluate_through_instr_call(
    const libcasm_ir::Builtin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    assert( 0 );
    // const auto symbol = libstdhl::wrap( (libcasm_ir::Value&)builtin );
    // libcasm_ir::CallInstruction instr( symbol, arguments );
    // Instruction::execute( instr );
}

void Builtin::execute(
    const libcasm_ir::IsSymbolicBuiltin& value,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];
    res = libcasm_ir::BooleanConstant( arg.symbolic() );
}

void Builtin::execute(
    const libcasm_ir::AbortBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::AbortException( "aborting" );
}

void Builtin::execute(
    const libcasm_ir::AssertBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& cond = operands[ 0 ];
    assert( cond.type().isBoolean() );
    const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( cond ).value();

    if( not c.defined() )
    {
        throw libcasm_ir::UndefinedConstantException( "assertion on undefined value" );
    }
    else
    {
        if( not c.value() )
        {
            throw libcasm_ir::AssertionException( "assertion failed" );
        }
    }

    res = libcasm_ir::VoidConstant();
}

void Builtin::execute(
    const libcasm_ir::PrintBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& txt = operands[ 0 ];
    assert( txt.type().isString() );
    const auto str = static_cast< const libcasm_ir::StringConstant& >( txt );

    std::cout << str.name();

    res = libcasm_ir::VoidConstant();
}

void Builtin::execute(
    const libcasm_ir::PrintLnBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& txt = operands[ 0 ];
    assert( txt.type().isString() );
    const auto str = static_cast< const libcasm_ir::StringConstant& >( txt );

    std::cout << str.name() << "\n";

    res = libcasm_ir::VoidConstant();
}

void Builtin::execute(
    const libcasm_ir::AsBooleanBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( not arg.defined() )
    {
        res = libcasm_ir::BooleanConstant();
        return;
    }

    switch( arg.type().kind() )
    {
        case libcasm_ir::Type::Kind::BOOLEAN:
        {
            res = arg;
            break;
        }
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();

            res = libcasm_ir::BooleanConstant( c > 0 );
            break;
        }
        case libcasm_ir::Type::Kind::BINARY:
        {
            const auto c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();

            res = libcasm_ir::BooleanConstant( c > 0 );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
        }
    }
}

void Builtin::execute(
    const libcasm_ir::AsIntegerBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( not arg.defined() )
    {
        res = libcasm_ir::IntegerConstant();
        return;
    }

    switch( arg.type().kind() )
    {
        case libcasm_ir::Type::Kind::BOOLEAN:
        {
            const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
            res = libcasm_ir::IntegerConstant( c == true ? 1 : 0 );
            break;
        }
        case libcasm_ir::Type::Kind::INTEGER:
        {
            res = arg;
            break;
        }
        case libcasm_ir::Type::Kind::BINARY:
        {
            const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
            res = libcasm_ir::IntegerConstant( c );
            break;
        }
        case libcasm_ir::Type::Kind::DECIMAL:
        {
            const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg ).value();
            res = libcasm_ir::IntegerConstant( c.toInteger() );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
        }
    }
}

void Builtin::execute(
    const libcasm_ir::AsBinaryBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( not arg.defined() )
    {
        res = arg;
        return;
    }

    switch( arg.type().kind() )
    {
        case libcasm_ir::Type::Kind::BOOLEAN:
        {
            const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
            res = libcasm_ir::BinaryConstant(
                arg.type().ptr_type(), libstdhl::Type::createNatural( c == true ? 1 : 0 ) );
            break;
        }
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
            res = libcasm_ir::BinaryConstant(
                arg.type().ptr_type(), libstdhl::Type::createNatural( c ) );
            break;
        }
        case libcasm_ir::Type::Kind::BINARY:
        {
            res = arg;
            break;
        }
        case libcasm_ir::Type::Kind::DECIMAL:
        {
            const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg ).value();
            res = libcasm_ir::BinaryConstant(
                arg.type().ptr_type(), libstdhl::Type::createNatural( c.toInteger() ) );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
        }
    }
}

void Builtin::execute(
    const libcasm_ir::AsStringBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        res = libcasm_ir::StringConstant( arg.name() );
    }
    else
    {
        res = libcasm_ir::StringConstant();
    }
}

void Builtin::execute(
    const libcasm_ir::AsDecimalBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().kind() )
        {
            case libcasm_ir::Type::Kind::DECIMAL:
            {
                const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg );
                res = c;
                break;
            }
            case libcasm_ir::Type::Kind::BOOLEAN:
            {
                const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
                res = libcasm_ir::DecimalConstant( c == true ? 1.0 : 0.0 );
                break;
            }
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
                res = libcasm_ir::DecimalConstant( c );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
                res = libcasm_ir::DecimalConstant( c );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }
    else
    {
        res = libcasm_ir::DecimalConstant();
    }
}

void Builtin::execute(
    const libcasm_ir::AsRationalBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::AsEnumerationBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::DecBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().kind() )
        {
            case libcasm_ir::Type::Kind::BOOLEAN:
            {
                const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
                res = libcasm_ir::StringConstant( c.value() ? "1" : "0" );
                break;
            }
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::DECIMAL:
            {
                const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::RATIONAL:
            {
                const auto& c = static_cast< const libcasm_ir::RationalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::ENUMERATION:
            {
                const auto& c =
                    static_cast< const libcasm_ir::EnumerationConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }
    else
    {
        res = libcasm_ir::StringConstant();
    }
}

void Builtin::execute(
    const libcasm_ir::HexBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().kind() )
        {
            case libcasm_ir::Type::Kind::BOOLEAN:
            {
                const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
                res = libcasm_ir::StringConstant( c.value() ? "1" : "0" );
                break;
            }
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::DECIMAL:
            {
                const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::RATIONAL:
            {
                const auto& c = static_cast< const libcasm_ir::RationalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::ENUMERATION:
            {
                const auto& c =
                    static_cast< const libcasm_ir::EnumerationConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }
    else
    {
        res = libcasm_ir::StringConstant();
    }
}

void Builtin::execute(
    const libcasm_ir::OctBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().kind() )
        {
            case libcasm_ir::Type::Kind::BOOLEAN:
            {
                const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
                res = libcasm_ir::StringConstant( c.value() ? "1" : "0" );
                break;
            }
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::DECIMAL:
            {
                const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::RATIONAL:
            {
                const auto& c = static_cast< const libcasm_ir::RationalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::ENUMERATION:
            {
                const auto& c =
                    static_cast< const libcasm_ir::EnumerationConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL, libstdhl::Type::Literal::NONE >() );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }
    else
    {
        res = libcasm_ir::StringConstant();
    }
}

void Builtin::execute(
    const libcasm_ir::BinBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().kind() )
        {
            case libcasm_ir::Type::Kind::BOOLEAN:
            {
                const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
                res = libcasm_ir::StringConstant( c.value() ? "1" : "0" );
                break;
            }
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::DECIMAL:
            {
                const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::RATIONAL:
            {
                const auto& c = static_cast< const libcasm_ir::RationalConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY, libstdhl::Type::Literal::NONE >() );
                break;
            }
            case libcasm_ir::Type::Kind::ENUMERATION:
            {
                const auto& c =
                    static_cast< const libcasm_ir::EnumerationConstant& >( arg ).value();
                res = libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY, libstdhl::Type::Literal::NONE >() );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }
    else
    {
        res = libcasm_ir::StringConstant();
    }
}

void Builtin::execute(
    const libcasm_ir::AdduBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& lhs = operands[ 0 ];
    const auto& rhs = operands[ 1 ];

    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::Constant::undef( lhs.type().ptr_type() );
        return;
    }

    switch( lhs.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& lval = static_cast< const libcasm_ir::IntegerConstant& >( lhs ).value();
            const auto& rval = static_cast< const libcasm_ir::IntegerConstant& >( rhs ).value();

            res = libcasm_ir::IntegerConstant( lval + rval );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
        }
    }
}

void Builtin::execute(
    const libcasm_ir::AddsBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::SubuBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::SubsBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::MuluBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::MulsBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::LesuBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::LessBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::LequBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::LeqsBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::GreuBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::GresBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::GequBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::GeqsBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::ZextBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::SextBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::TruncBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::ShlBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& valueConstant = operands[ 0 ];
    const auto& offsetConstant = operands[ 1 ];

    if( not valueConstant.defined() or not offsetConstant.defined() )
    {
        // offset is undef, return the given value
        res = valueConstant;
    }
    else
    {
        assert( builtin.type().result().isBinary() );
        const auto& value =
            static_cast< const libcasm_ir::BinaryConstant& >( valueConstant ).value();

        switch( offsetConstant.type().kind() )
        {
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& offset =
                    static_cast< const libcasm_ir::IntegerConstant& >( offsetConstant ).value();

                const auto shiftedValue = libstdhl::Type::createNatural( value << offset );
                res = libcasm_ir::BinaryConstant( valueConstant.type().ptr_type(), shiftedValue );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& offset =
                    static_cast< const libcasm_ir::BinaryConstant& >( offsetConstant ).value();

                const auto shiftedValue = libstdhl::Type::createNatural( value << offset );
                res = libcasm_ir::BinaryConstant( valueConstant.type().ptr_type(), shiftedValue );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }
}

void Builtin::execute(
    const libcasm_ir::ShrBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& valueConstant = operands[ 0 ];
    const auto& offsetConstant = operands[ 1 ];

    if( not valueConstant.defined() or not offsetConstant.defined() )
    {
        // offset is undef, return the given value
        res = valueConstant;
    }
    else
    {
        assert( builtin.type().result().isBinary() );
        const auto& value =
            static_cast< const libcasm_ir::BinaryConstant& >( valueConstant ).value();

        switch( offsetConstant.type().kind() )
        {
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& offset =
                    static_cast< const libcasm_ir::IntegerConstant& >( offsetConstant ).value();

                const auto shiftedValue = libstdhl::Type::createNatural( value >> offset );
                res = libcasm_ir::BinaryConstant( valueConstant.type().ptr_type(), shiftedValue );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& offset =
                    static_cast< const libcasm_ir::BinaryConstant& >( offsetConstant ).value();

                const auto shiftedValue = libstdhl::Type::createNatural( value >> offset );
                res = libcasm_ir::BinaryConstant( valueConstant.type().ptr_type(), shiftedValue );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }
}

void Builtin::execute(
    const libcasm_ir::AshrBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::ClzBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::CloBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

void Builtin::execute(
    const libcasm_ir::ClsBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    throw libcasm_ir::InternalException( "unimplemented '" + builtin.description() + "'" );
}

// void Builtin::execute( const libcasm_ir::PowBuiltin& builtin,
// libcasm_ir::Constant& res, const libcasm_ir::Constant* operands, const
// std::size_t size )
// {
// }

// void Builtin::execute( const libcasm_ir::RandBuiltin&
// builtin, libcasm_ir::Constant& res, const libcasm_ir::Constant* operands,
// const std::size_t size )
// {
// }

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

// libcsel_ir::CallableUnit* Builtin::asBoolean(
//     libcasm_ir::Value& value, libcsel_ir::Module* context )
// {
//     static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
//     cache;

//     libstdhl::Log::info( "%s: %s %s",
//         __FUNCTION__,
//         value.name().c_str(),
//         value.type().description().c_str() );

//     std::string key = "";
//     key += value.name();
//     key += " ";
//     key += value.type().name();

//     auto result = cache.find( key );
//     if( result != cache.end() )
//     {
//         return result->second;
//     }

//     const auto& ir_ty = value.type();
//     assert( ir_ty.isRelation() and ir_ty.arguments().size() == 1 );

//     auto el_ty = libcasm_rt::Type::get( ir_ty );
//     assert( el_ty.isRelation() and el_ty.arguments().size() == 1
//             and el_ty.results().size() == 1 );

//     auto instr = libcasm_ir::cast< libcasm_ir::AsBooleanBuiltin >( value );

//     return 0;

// auto el = new libcsel_ir::Intrinsic(
//     instr->label(), &el_ty ); // PPA: TODO: add 'el' to context
// assert( el );

// auto arg = el->in( "arg", el_ty.arguments()[ 0 ] );
// auto ret = el->out( "ret", el_ty.results()[ 0 ] );

// libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( el );
// libcsel_ir::Statement* stmt = new libcsel_ir::TrivialStatement( scope );

// auto idx0 = new libcsel_ir::BitConstant( 8, 0 );
// auto idx1 = new libcsel_ir::BitConstant( 8, 1 );

// auto arg_v_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx0 ) );
// auto arg_d_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx1 ) );

// auto ret_v_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx0 ) );
// auto ret_d_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx1 ) );

// auto arg_v = stmt->add( new libcsel_ir::LoadInstruction( arg_v_ptr ) );
// auto arg_d = stmt->add( new libcsel_ir::LoadInstruction( arg_d_ptr ) );

// auto reg_v = stmt->add( new libcsel_ir::NeqInstruction(
//     arg_v, new libcsel_ir::BitConstant( &arg_v->type(), 0 ) ) );

// stmt->add( new libcsel_ir::StoreInstruction( reg_v, ret_v_ptr ) );
// stmt->add( new libcsel_ir::StoreInstruction( arg_d, ret_d_ptr ) );

// cache[ key ] = el;
// return el;
// }

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
