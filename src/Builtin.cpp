//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                <https://github.com/casm-lang/libcasm-rt>
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

#include "Instruction.h"
#include "Type.h"

#include "Utility.h"

#include <libcasm-ir/Builtin>
#include <libcasm-ir/Exception>
#include <libcasm-ir/Type>
#include <libcasm-ir/Value>

#include <libstdhl/Log>

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
    const libcasm_ir::AssureBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& cond = operands[ 0 ];
    assert( cond.type().isBoolean() );
    const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( cond ).value();

    if( not c.defined() )
    {
        throw libcasm_ir::UndefinedConstantException( "assurance on undefined value" );
    }
    else
    {
        if( not c.value() )
        {
            throw libcasm_ir::AssuranceException( "assurance failed" );
        }
    }

    res = libcasm_ir::VoidConstant();
}

void Builtin::execute(
    const libcasm_ir::SizeBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& object = operands[ 0 ];
    assert( object.type().isEnumeration() or object.type().isList() or object.type().isRange() );

    if( not object.defined() )
    {
        res = libcasm_ir::IntegerConstant();
        return;
    }

    if( object.type().isEnumeration() )
    {
        const auto enumeration = static_cast< const libcasm_ir::EnumerationType& >( object.type() );
        res = libcasm_ir::IntegerConstant( enumeration.kind().elements().size() );
    }
    else if( object.type().isList() )
    {
        const auto list = static_cast< const libcasm_ir::ListConstant& >( object ).value();
        res = libcasm_ir::IntegerConstant( list->elements().size() );
    }
    else
    {
        assert( object.type().isRange() );
        const auto& range = static_cast< const libcasm_ir::RangeConstant& >( object ).value();

        const auto& a = static_cast< libcasm_ir::IntegerConstant& >( *range->from() ).value();
        const auto& b = static_cast< libcasm_ir::IntegerConstant& >( *range->to() ).value();

        if( a >= b )
        {
            res = libcasm_ir::IntegerConstant( a - b );
        }
        else
        {
            res = libcasm_ir::IntegerConstant( b - a );
        }
    }
}

void Builtin::execute(
    const libcasm_ir::PrintBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& txt = operands[ 0 ];
    assert( txt.type().isString() );
    const auto stringConstant = static_cast< const libcasm_ir::StringConstant& >( txt );

    std::cout << stringConstant.toString();

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
    const auto stringConstant = static_cast< const libcasm_ir::StringConstant& >( txt );

    std::cout << stringConstant.toString() << "\n";

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

    switch( arg.typeId().kind() )
    {
        case libcasm_ir::Type::Kind::BOOLEAN:
        {
            res = arg;
            break;
        }
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
            res = libcasm_ir::BooleanConstant( c != 0 );
            break;
        }
        case libcasm_ir::Type::Kind::BINARY:
        {
            const auto c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
            res = libcasm_ir::BooleanConstant( c != 0 );
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

    switch( arg.typeId().kind() )
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
            const auto& t = static_cast< const libcasm_ir::BinaryType& >( arg.type() );
            const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();

            if( c.isSet( t.bitsize() ) )
            {
                Instruction::execute< libcasm_ir::InvInstruction >( t.ptr_type(), res, arg );
                const auto& r = static_cast< const libcasm_ir::BinaryConstant& >( res ).value();
                res = libcasm_ir::IntegerConstant( r, true );
            }
            else
            {
                res = libcasm_ir::IntegerConstant( c );
            }
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

    assert( builtin.type().result().isBinary() );
    const auto resultType =
        std::static_pointer_cast< libcasm_ir::BinaryType >( builtin.type().result().ptr_type() );

    if( not arg.defined() )
    {
        res = libcasm_ir::BinaryConstant( resultType );
        return;
    }

    switch( arg.typeId().kind() )
    {
        case libcasm_ir::Type::Kind::BOOLEAN:
        {
            const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
            res = libcasm_ir::BinaryConstant(
                resultType, libstdhl::Type::createNatural( c == true ? 1 : 0 ) );
            break;
        }
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();

            try
            {
                const auto mask = Utility::createMask( resultType->bitsize() );

                libstdhl::Type::Natural nat;
                if( c >= 0 )
                {
                    nat = libstdhl::Type::createNatural( c );

                    const auto check = nat & mask;
                    if( nat != check )
                    {
                        res = libcasm_ir::BinaryConstant( resultType );
                        break;
                    }

                    if( nat.isSet( resultType->bitsize() ) )
                    {
                        res = libcasm_ir::BinaryConstant( resultType );
                        break;
                    }
                }
                else
                {
                    nat = libstdhl::Type::createNatural( -c );

                    const auto check = nat & mask;
                    if( nat != check )
                    {
                        res = libcasm_ir::BinaryConstant( resultType );
                        break;
                    }

                    nat = nat ^ mask;
                    nat += 1;
                    if( not nat.isSet( resultType->bitsize() ) )
                    {
                        res = libcasm_ir::BinaryConstant( resultType );
                        break;
                    }

                    nat = nat & mask;
                }

                res = libcasm_ir::BinaryConstant( resultType, nat );
            }
            catch( const std::domain_error& e )
            {
                res = libcasm_ir::BinaryConstant( resultType );
            }
            catch( const std::invalid_argument& e )
            {
                res = libcasm_ir::BinaryConstant( resultType );
            }
            break;
        }
        case libcasm_ir::Type::Kind::BINARY:
        {
            const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg );
            assert( c.type().isBinary() );
            const auto& valueType = static_cast< const libcasm_ir::BinaryType& >( c.type() );

            if( resultType->bitsize() < valueType.bitsize() )
            {
                // perform a truncation of the binary value!
                const auto offset = libcasm_ir::IntegerConstant( c.value() );
                const libcasm_ir::Constant values[ 2 ] = { arg, offset };
                const auto truncType = libstdhl::Memory::get< libcasm_ir::RelationType >(
                    resultType,
                    libcasm_ir::Types( { c.type().ptr_type(), offset.type().ptr_type() } ) );
                Builtin::execute< libcasm_ir::TruncBuiltin >( truncType, res, values, 2 );
            }
            else if( resultType->bitsize() > valueType.bitsize() )
            {
                // perform a zero extension
                res = libcasm_ir::BinaryConstant(
                    resultType, libstdhl::Type::createNatural( c.value() ) );
            }
            else
            {
                res = arg;
            }
            break;
        }
        case libcasm_ir::Type::Kind::DECIMAL:
        {
            const auto& c = static_cast< const libcasm_ir::DecimalConstant& >( arg ).value();

            try
            {
                const auto i = c.toInteger();
                if( i >= 0 )
                {
                    const auto nat = libstdhl::Type::createNatural( i );
                    res = libcasm_ir::BinaryConstant( resultType, nat );
                }
                else
                {
                    const auto mask = Utility::createMask( resultType->bitsize() );
                    auto nat = libstdhl::Type::createNatural( -i );
                    nat = nat ^ mask;
                    nat += 1;
                    res = libcasm_ir::BinaryConstant( resultType, nat );
                }
            }
            catch( const std::domain_error& e )
            {
                res = libcasm_ir::BinaryConstant( resultType );
            }
            catch( const std::invalid_argument& e )
            {
                res = libcasm_ir::BinaryConstant( resultType );
            }
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
        switch( arg.typeId().kind() )
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
    const auto& arg = operands[ 0 ];

    assert( builtin.type().result().isRational() );
    const auto resultType = std::static_pointer_cast< libcasm_ir::EnumerationType >(
        builtin.type().result().ptr_type() );

    if( arg.defined() )
    {
        switch( arg.typeId().kind() )
        {
            case libcasm_ir::Type::Kind::BOOLEAN:
            {
                const auto& c = static_cast< const libcasm_ir::BooleanConstant& >( arg ).value();
                res = libcasm_ir::RationalConstant( libstdhl::Type::createRational(
                    libstdhl::Type::createInteger( ( libstdhl::u64 )( c == true ? 1 : 0 ) ) ) );
                break;
            }
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& c = static_cast< const libcasm_ir::IntegerConstant& >( arg ).value();
                res = libcasm_ir::RationalConstant( libstdhl::Type::createRational( c ) );
                break;
            }
            case libcasm_ir::Type::Kind::BINARY:
            {
                const auto& c = static_cast< const libcasm_ir::BinaryConstant& >( arg ).value();
                res = libcasm_ir::RationalConstant( libstdhl::Type::createRational( c ) );
                break;
            }
            case libcasm_ir::Type::Kind::RATIONAL:
            {
                res = arg;
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
        res = libcasm_ir::RationalConstant();
    }
}

void Builtin::execute(
    const libcasm_ir::AsEnumerationBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    assert( builtin.type().result().isEnumeration() );
    const auto resultType = std::static_pointer_cast< libcasm_ir::EnumerationType >(
        builtin.type().result().ptr_type() );

    if( arg.defined() )
    {
        switch( arg.typeId().kind() )
        {
            case libcasm_ir::Type::Kind::ENUMERATION:
            {
                if( arg.type() == *resultType )
                {
                    res = arg;
                }
                else
                {
                    res = libcasm_ir::EnumerationConstant( resultType );
                }
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
        res = libcasm_ir::EnumerationConstant( resultType );
    }
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
        switch( arg.typeId().kind() )
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
        switch( arg.typeId().kind() )
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
        switch( arg.typeId().kind() )
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
        switch( arg.typeId().kind() )
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

    switch( lhs.typeId().kind() )
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
    const auto& valueConstant = operands[ 0 ];

    assert( builtin.type().result().isBinary() );
    const auto resultType =
        std::static_pointer_cast< libcasm_ir::BinaryType >( builtin.type().result().ptr_type() );

    if( not valueConstant.defined() )
    {
        res = libcasm_ir::BinaryConstant( resultType );
    }
    else
    {
        const auto& value =
            static_cast< const libcasm_ir::BinaryConstant& >( valueConstant ).value();
        const auto zextValue = libstdhl::Type::createNatural( value );
        res = libcasm_ir::BinaryConstant( resultType, zextValue );
    }
}

void Builtin::execute(
    const libcasm_ir::SextBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& valueConstant = operands[ 0 ];

    assert( builtin.type().result().isBinary() );
    const auto resultType =
        std::static_pointer_cast< libcasm_ir::BinaryType >( builtin.type().result().ptr_type() );

    if( not valueConstant.defined() )
    {
        res = libcasm_ir::BinaryConstant( resultType );
    }
    else
    {
        const auto& value = static_cast< const libcasm_ir::BinaryConstant& >( valueConstant );
        assert( value.type().isBinary() );
        const auto& valueType = static_cast< const libcasm_ir::BinaryType& >( value.type() );

        const auto sign = value.value() >> ( valueType.bitsize() - 1 );

        Builtin::execute< libcasm_ir::ZextBuiltin >(
            builtin.type().ptr_type(), res, operands, size );

        if( sign != 0 )
        {
            auto mask = Utility::createMask( resultType->bitsize() - valueType.bitsize() );
            mask <<= valueType.bitsize();

            auto tmp = libcasm_ir::BinaryConstant( resultType, mask );
            Instruction::execute< libcasm_ir::OrInstruction >( resultType, res, res, tmp );
        }
    }
}

void Builtin::execute(
    const libcasm_ir::TruncBuiltin& builtin,
    libcasm_ir::Constant& res,
    const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    const auto& valueConstant = operands[ 0 ];
    const auto& offsetConstant = operands[ 1 ];
    assert( offsetConstant.defined() );
    assert( offsetConstant.typeId().kind() == libcasm_ir::Type::Kind::INTEGER );

    assert( builtin.type().result().isBinary() );
    const auto resultType =
        std::static_pointer_cast< libcasm_ir::BinaryType >( builtin.type().result().ptr_type() );

    if( not valueConstant.defined() )
    {
        res = libcasm_ir::BinaryConstant( resultType );
    }
    else
    {
        const auto& offset =
            static_cast< const libcasm_ir::IntegerConstant& >( offsetConstant ).value();

        auto mask = libstdhl::Type::createNatural( 1 );
        mask <<= libstdhl::Type::createNatural( offset );
        mask -= 1;

        auto tmp = libcasm_ir::BinaryConstant( valueConstant.type().ptr_type(), mask );
        Instruction::execute< libcasm_ir::AndInstruction >(
            valueConstant.type().ptr_type(), tmp, tmp, valueConstant );
        assert( tmp.defined() );
        assert( tmp.typeId().kind() == libcasm_ir::Type::Kind::BINARY );

        const auto& value = static_cast< const libcasm_ir::BinaryConstant& >( tmp ).value();
        res = libcasm_ir::BinaryConstant( resultType, value );
    }
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

        switch( offsetConstant.typeId().kind() )
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

        switch( offsetConstant.typeId().kind() )
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
