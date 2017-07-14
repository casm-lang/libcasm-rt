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

#include "Builtin.h"
#include "Type.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Builtin.h"
#include "../casm-ir/src/Exception.h"
#include "../casm-ir/src/Type.h"
#include "../casm-ir/src/Value.h"

// #include "../csel-ir/src/CallableUnit.h"
// #include "../csel-ir/src/Instruction.h"
// #include "../csel-ir/src/Intrinsic.h"
// #include "../csel-ir/src/Reference.h"
// #include "../csel-ir/src/Scope.h"
// #include "../csel-ir/src/Statement.h"

using namespace libcasm_rt;

static inline libcasm_ir::Constant evaluate_through_instr_call(
    const libcasm_ir::Builtin& builtin, const libcasm_ir::Constant* operands,
    const std::size_t size )
{
    assert( 0 );
    // const auto symbol = libstdhl::wrap( (libcasm_ir::Value&)builtin );
    // libcasm_ir::CallInstruction instr( symbol, arguments );
    // return Instruction::execute( instr );
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::IsSymbolicBuiltin& value,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];
    return libcasm_ir::BooleanConstant( arg.symbolic() );
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AbortBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    throw libcasm_ir::AbortException( "aborting" );
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AssertBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& cond = operands[ 0 ];
    assert( cond.type().isBoolean() );
    const auto c = static_cast< const libcasm_ir::BooleanConstant& >( cond );

    if( not c.defined() )
    {
        throw libcasm_ir::UndefinedConstantException(
            "assertion on undefined value" );
    }
    else
    {
        if( not c.value() )
        {
            std::string msg = "assertion failed";

            if( size == 2 )
            {
                const auto& txt = operands[ 1 ];
                assert( txt.type().isString() );
                const auto str
                    = static_cast< const libcasm_ir::StringConstant& >( txt );
                msg += ": " + str.value();
            }

            throw libcasm_ir::AssertionException( msg );
        }
    }

    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::PrintBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& txt = operands[ 0 ];
    assert( txt.type().isString() );
    const auto str = static_cast< const libcasm_ir::StringConstant& >( txt );

    std::cout << str.value();

    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::PrintLnBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& txt = operands[ 0 ];
    assert( txt.type().isString() );
    const auto str = static_cast< const libcasm_ir::StringConstant& >( txt );

    std::cout << str.value() << "\n";

    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsBooleanBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().id() )
        {
            case libcasm_ir::Type::BOOLEAN:
            {
                return arg;
            }
            case libcasm_ir::Type::INTEGER:
            {
                const auto c
                    = static_cast< const libcasm_ir::IntegerConstant& >( arg );

                if( c.value().trivial() )
                {
                    return libcasm_ir::BooleanConstant(
                        c.value().value() > 0 and not c.value().sign() );
                }
                else
                {
                    return libcasm_ir::BooleanConstant( true );
                }
            }
            case libcasm_ir::Type::BIT:
            {
                const auto c
                    = static_cast< const libcasm_ir::BitConstant& >( arg );

                if( c.value().trivial() )
                {
                    return libcasm_ir::BooleanConstant( c.value().value() > 0 );
                }
                else
                {
                    return libcasm_ir::BooleanConstant( true );
                }
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }

    return libcasm_ir::BooleanConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsIntegerBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().id() )
        {
            case libcasm_ir::Type::INTEGER:
            {
                return arg;
            }
            case libcasm_ir::Type::BOOLEAN:
            {
                const auto c
                    = static_cast< const libcasm_ir::BooleanConstant& >( arg );
                return libcasm_ir::IntegerConstant( c.value() ? 1 : 0 );
            }
            case libcasm_ir::Type::BIT:
            {
                const auto c
                    = static_cast< const libcasm_ir::BitConstant& >( arg );
                return libcasm_ir::IntegerConstant( c );
            }
            case libcasm_ir::Type::ENUMERATION:
            {
                const auto c
                    = static_cast< const libcasm_ir::EnumerationConstant& >(
                        arg );

                return libcasm_ir::IntegerConstant(
                    static_cast< const libstdhl::Type::Integer& >(
                        c.value().value() ) );
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }

    return libcasm_ir::IntegerConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AsBitBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsStringBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        return libcasm_ir::StringConstant( arg.name() );
    }

    return libcasm_ir::StringConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsFloatingBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsRationalBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsEnumerationBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::DecBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().id() )
        {
            case libcasm_ir::Type::BOOLEAN:
            {
                const auto& c
                    = static_cast< const libcasm_ir::BooleanConstant& >( arg );
                return libcasm_ir::StringConstant( c.value() ? "1" : "0" );
            }
            case libcasm_ir::Type::INTEGER:
            {
                const auto& c
                    = static_cast< const libcasm_ir::IntegerConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL >() );
            }
            case libcasm_ir::Type::BIT:
            {
                const auto& c = static_cast< const libcasm_ir::BitConstant& >(
                    arg ).value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL >() );
            }
            case libcasm_ir::Type::FLOATING:
            {
                const auto& c
                    = static_cast< const libcasm_ir::FloatingConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL >() );
            }
            case libcasm_ir::Type::RATIONAL:
            {
                const auto& c
                    = static_cast< const libcasm_ir::RationalConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL >() );
            }
            case libcasm_ir::Type::ENUMERATION:
            {
                const auto& c
                    = static_cast< const libcasm_ir::EnumerationConstant& >(
                        arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::DECIMAL >() );
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }

    return libcasm_ir::StringConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::HexBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().id() )
        {
            case libcasm_ir::Type::BOOLEAN:
            {
                const auto& c
                    = static_cast< const libcasm_ir::BooleanConstant& >( arg );
                return libcasm_ir::StringConstant( c.value() ? "1" : "0" );
            }
            case libcasm_ir::Type::INTEGER:
            {
                const auto& c
                    = static_cast< const libcasm_ir::IntegerConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL >() );
            }
            case libcasm_ir::Type::BIT:
            {
                const auto& c = static_cast< const libcasm_ir::BitConstant& >(
                    arg ).value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL >() );
            }
            case libcasm_ir::Type::FLOATING:
            {
                const auto& c
                    = static_cast< const libcasm_ir::FloatingConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL >() );
            }
            case libcasm_ir::Type::RATIONAL:
            {
                const auto& c
                    = static_cast< const libcasm_ir::RationalConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL >() );
            }
            case libcasm_ir::Type::ENUMERATION:
            {
                const auto& c
                    = static_cast< const libcasm_ir::EnumerationConstant& >(
                        arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::HEXADECIMAL >() );
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }

    return libcasm_ir::StringConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::OctBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().id() )
        {
            case libcasm_ir::Type::BOOLEAN:
            {
                const auto& c
                    = static_cast< const libcasm_ir::BooleanConstant& >( arg );
                return libcasm_ir::StringConstant( c.value() ? "1" : "0" );
            }
            case libcasm_ir::Type::INTEGER:
            {
                const auto& c
                    = static_cast< const libcasm_ir::IntegerConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL >() );
            }
            case libcasm_ir::Type::BIT:
            {
                const auto& c = static_cast< const libcasm_ir::BitConstant& >(
                    arg ).value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL >() );
            }
            case libcasm_ir::Type::FLOATING:
            {
                const auto& c
                    = static_cast< const libcasm_ir::FloatingConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL >() );
            }
            case libcasm_ir::Type::RATIONAL:
            {
                const auto& c
                    = static_cast< const libcasm_ir::RationalConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL >() );
            }
            case libcasm_ir::Type::ENUMERATION:
            {
                const auto& c
                    = static_cast< const libcasm_ir::EnumerationConstant& >(
                        arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::OCTAL >() );
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }

    return libcasm_ir::StringConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::BinBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& arg = operands[ 0 ];

    if( arg.defined() )
    {
        switch( arg.type().id() )
        {
            case libcasm_ir::Type::BOOLEAN:
            {
                const auto& c
                    = static_cast< const libcasm_ir::BooleanConstant& >( arg );
                return libcasm_ir::StringConstant( c.value() ? "1" : "0" );
            }
            case libcasm_ir::Type::INTEGER:
            {
                const auto& c
                    = static_cast< const libcasm_ir::IntegerConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY >() );
            }
            case libcasm_ir::Type::BIT:
            {
                const auto& c = static_cast< const libcasm_ir::BitConstant& >(
                    arg ).value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY >() );
            }
            case libcasm_ir::Type::FLOATING:
            {
                const auto& c
                    = static_cast< const libcasm_ir::FloatingConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY >() );
            }
            case libcasm_ir::Type::RATIONAL:
            {
                const auto& c
                    = static_cast< const libcasm_ir::RationalConstant& >( arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY >() );
            }
            case libcasm_ir::Type::ENUMERATION:
            {
                const auto& c
                    = static_cast< const libcasm_ir::EnumerationConstant& >(
                        arg )
                          .value();
                return libcasm_ir::StringConstant(
                    c.to< libstdhl::Type::Radix::BINARY >() );
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + builtin.description() + "'" );
            }
        }
    }

    return libcasm_ir::StringConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AdduBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    const auto& lhs = operands[ 0 ];
    const auto& rhs = operands[ 1 ];

    if( not lhs.defined() or not rhs.defined() )
    {
        return libcasm_ir::Constant::undef( lhs.type().ptr_type() );
    }

    switch( lhs.type().id() )
    {
        case libcasm_ir::Type::INTEGER:
        {
            const auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            const auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            return libcasm_ir::IntegerConstant( lval + rval );
        }
        case libcasm_ir::Type::BIT:
        {
            const auto& lval = static_cast< const libcasm_ir::StringConstant& >(
                lhs ).value();
            const auto& rval = static_cast< const libcasm_ir::StringConstant& >(
                rhs ).value();

            return libcasm_ir::StringConstant( lval + rval );
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + builtin.description() + "'" );
            return libcasm_ir::VoidConstant();
        }
    }
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AddsBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::SubuBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::SubsBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::MuluBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::MulsBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::LesuBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::LessBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::LequBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::LeqsBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::GreuBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::GresBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::GequBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::GeqsBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::ZextBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::SextBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::TruncBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::ShlBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::ShrBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AshrBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::ClzBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::CloBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::ClsBuiltin& builtin,
    const libcasm_ir::Constant* operands, const std::size_t size )
{
    return libcasm_ir::VoidConstant();
}

// libcasm_ir::Constant Builtin::execute( const libcasm_ir::PowBuiltin& builtin,
// const libcasm_ir::Constant* operands, const std::size_t size )
// {
// }

// libcasm_ir::Constant Builtin::execute( const libcasm_ir::RandBuiltin&
// builtin, const libcasm_ir::Constant* operands, const std::size_t size )
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
