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

#include "Instruction.h"

#include "Builtin.h"
#include "Constant.h"
#include "Type.h"
#include "Value.h"

#include <libstdhl/Log>

#include <libcasm-ir/Constant>
#include <libcasm-ir/Exception>
#include <libcasm-ir/Instruction>
#include <libcasm-ir/Value>

// #include "../csel-ir/src/CallableUnit.h"
// #include "../csel-ir/src/Constant.h"
// #include "../csel-ir/src/Instruction.h"
// #include "../csel-ir/src/Intrinsic.h"
// #include "../csel-ir/src/Reference.h"
// #include "../csel-ir/src/Scope.h"
// #include "../csel-ir/src/Value.h"

// #include "../csel-rt/src/CallableUnit.h"
// #include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

void Instruction::execute( const libcasm_ir::InvInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs )
{
    if( not lhs.defined() )
    {
        res = libcasm_ir::Constant::undef( lhs.type().ptr_type() );
        return;
    }

    switch( lhs.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& val
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();

            res = libcasm_ir::IntegerConstant( -val );
            break;
        }
        case libcasm_ir::Type::Kind::FLOATING:
        {
            const auto& val
                = static_cast< const libcasm_ir::FloatingConstant& >( lhs )
                      .value();

            res = libcasm_ir::FloatingConstant( -val );
            break;
        }
        case libcasm_ir::Type::Kind::RATIONAL:
        {
            const auto& val
                = static_cast< const libcasm_ir::RationalConstant& >( lhs )
                      .value();

            res = libcasm_ir::RationalConstant( -val );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            res = libcasm_ir::VoidConstant();
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::AddInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::Constant::undef( instr.type().ptr_type() );
        return;
    }

    switch( instr.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            res = libcasm_ir::IntegerConstant( lval + rval );
            break;
        }
        case libcasm_ir::Type::Kind::STRING:
        {
            auto& lval = static_cast< const libcasm_ir::StringConstant& >( lhs )
                             .value();
            auto& rval = static_cast< const libcasm_ir::StringConstant& >( rhs )
                             .value();

            res = libcasm_ir::StringConstant(
                lval.toString() + rval.toString() );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::SubInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::Constant::undef( instr.type().ptr_type() );
        return;
    }

    switch( instr.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            const auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            res = libcasm_ir::IntegerConstant( lval - rval );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::MulInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::Constant::undef( instr.type().ptr_type() );
        return;
    }

    switch( instr.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            const auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            res = libcasm_ir::IntegerConstant( lval * rval );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::ModInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::Constant::undef( instr.type().ptr_type() );
        return;
    }

    switch( instr.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            const auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            if( rval == 0 )
            {
                res = libcasm_ir::IntegerConstant();
            }
            else
            {
                res = libcasm_ir::IntegerConstant( lval % rval );
            }
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::DivInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::Constant::undef( instr.type().ptr_type() );
        return;
    }

    switch( instr.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            const auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            if( rval == 0 )
            {
                res = libcasm_ir::IntegerConstant();
            }
            else
            {
                res = libcasm_ir::IntegerConstant( lval / rval );
            }
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::PowInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    throw libcasm_ir::InternalException(
        "unimplemented '" + instr.description() + "'" );
}

void Instruction::execute( const libcasm_ir::AndInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    const auto& lval
        = static_cast< const libcasm_ir::BooleanConstant& >( lhs ).value();
    const auto& rval
        = static_cast< const libcasm_ir::BooleanConstant& >( rhs ).value();

    if( lhs.defined() and rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( lval.value() and rval.value() );
    }
    else
    {
        if( ( lhs.defined() and ( not lval.value() ) )
            or ( rhs.defined() and ( not rval.value() ) ) )
        {
            res = libcasm_ir::BooleanConstant( false );
        }
        else
        {
            res = libcasm_ir::BooleanConstant();
        }
    }
}

void Instruction::execute( const libcasm_ir::XorInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    const auto& lval
        = static_cast< const libcasm_ir::BooleanConstant& >( lhs ).value();
    const auto& rval
        = static_cast< const libcasm_ir::BooleanConstant& >( rhs ).value();

    if( lhs.defined() and rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( lval.value() xor rval.value() );
    }
    else
    {
        res = libcasm_ir::BooleanConstant();
    }
}

void Instruction::execute( const libcasm_ir::OrInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    const auto& lval
        = static_cast< const libcasm_ir::BooleanConstant& >( lhs ).value();
    const auto& rval
        = static_cast< const libcasm_ir::BooleanConstant& >( rhs ).value();

    if( lhs.defined() and rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( lval.value() or rval.value() );
    }
    else
    {
        if( ( lhs.defined() and lval.value() )
            or ( rhs.defined() and rval.value() ) )
        {
            res = libcasm_ir::BooleanConstant( true );
        }
        else
        {
            res = libcasm_ir::BooleanConstant();
        }
    }
}

void Instruction::execute( const libcasm_ir::ImpInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    const auto& lval
        = static_cast< const libcasm_ir::BooleanConstant& >( lhs ).value();
    const auto& rval
        = static_cast< const libcasm_ir::BooleanConstant& >( rhs ).value();

    if( lhs.defined() and rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant(
            ( not lval.value() ) or rval.value() );
    }
    else
    {
        if( ( lhs.defined() and ( not lval.value() ) )
            or ( rhs.defined() and rval.value() ) )
        {
            res = libcasm_ir::BooleanConstant( true );
        }
        else
        {
            res = libcasm_ir::BooleanConstant();
        }
    }
}

void Instruction::execute( const libcasm_ir::NotInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs )
{
    if( not lhs.defined() )
    {
        res = libcasm_ir::Constant::undef( instr.type().ptr_type() );
        return;
    }

    switch( lhs.type().kind() )
    {
        case libcasm_ir::Type::Kind::BOOLEAN:
        {
            const auto& val
                = static_cast< const libcasm_ir::BooleanConstant& >( lhs )
                      .value();

            res = libcasm_ir::BooleanConstant( not val.value() );
            break;
        }
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& val
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();

            res = libcasm_ir::BooleanConstant( val == 0 );
            break;
        }
        case libcasm_ir::Type::Kind::BIT:
        {
            const auto& val
                = static_cast< const libcasm_ir::BitConstant& >( lhs ).value();

            res = libcasm_ir::BitConstant( lhs.type().ptr_type(), ~val );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::EquInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    if( lhs.defined() and rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( lhs == rhs );
    }
    else if( lhs.defined() or rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( false );
    }
    else
    {
        res = libcasm_ir::BooleanConstant( true );
    }
}

void Instruction::execute( const libcasm_ir::NeqInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    if( lhs.defined() and rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( lhs != rhs );
    }
    else if( lhs.defined() or rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( true );
    }
    else
    {
        res = libcasm_ir::BooleanConstant( false );
    }
}

void Instruction::execute( const libcasm_ir::LthInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    assert( lhs.type() == rhs.type() );

    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant();
        return;
    }

    switch( lhs.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            const auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            res = libcasm_ir::BooleanConstant( lval < rval );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::LeqInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    assert( lhs.type() == rhs.type() );

    if( lhs.defined() and rhs.defined() )
    {
        switch( lhs.type().kind() )
        {
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& lval
                    = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                          .value();
                const auto& rval
                    = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                          .value();

                res = libcasm_ir::BooleanConstant( lval <= rval );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + instr.description() + "'" );
                break;
            }
        }
    }
    else if( not lhs.defined() and not rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( true );
    }
    else
    {
        res = libcasm_ir::BooleanConstant();
    }
}

void Instruction::execute( const libcasm_ir::GthInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    assert( lhs.type() == rhs.type() );

    if( not lhs.defined() or not rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant();
        return;
    }

    switch( lhs.type().kind() )
    {
        case libcasm_ir::Type::Kind::INTEGER:
        {
            const auto& lval
                = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                      .value();
            const auto& rval
                = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                      .value();

            res = libcasm_ir::BooleanConstant( lval > rval );
            break;
        }
        default:
        {
            throw libcasm_ir::InternalException(
                "unimplemented '" + instr.description() + "'" );
            break;
        }
    }
}

void Instruction::execute( const libcasm_ir::GeqInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant& lhs,
    const libcasm_ir::Constant& rhs )
{
    assert( lhs.type() == rhs.type() );

    if( lhs.defined() and rhs.defined() )
    {
        switch( lhs.type().kind() )
        {
            case libcasm_ir::Type::Kind::INTEGER:
            {
                const auto& lval
                    = static_cast< const libcasm_ir::IntegerConstant& >( lhs )
                          .value();
                const auto& rval
                    = static_cast< const libcasm_ir::IntegerConstant& >( rhs )
                          .value();

                res = libcasm_ir::BooleanConstant( lval >= rval );
                break;
            }
            default:
            {
                throw libcasm_ir::InternalException(
                    "unimplemented '" + instr.description() + "'" );
                break;
            }
        }
    }
    else if( not lhs.defined() and not rhs.defined() )
    {
        res = libcasm_ir::BooleanConstant( true );
    }
    else
    {
        res = libcasm_ir::BooleanConstant();
    }
}

void Instruction::execute( const libcasm_ir::CallInstruction& instr,
    libcasm_ir::Constant& res, const libcasm_ir::Constant* reg,
    const std::size_t size )
{
    // TODO
    // const auto& symbol = instr.constants()[ 0 ];
    // switch( symbol.kind() )
    // {

    // }

    throw libcasm_ir::InternalException(
        "unimplemented '" + instr.description() + "'" );
}

// libcsel_ir::CallableUnit* Instruction::Not(
//     libcasm_ir::NotInstruction& instr, libcsel_ir::Module* module )
// {
//     return 0;
//     // libcasm_ir::Type& ir_ty = instr.type();
//     // assert( not ir_ty.isRelation() );

//     // libcsel_ir::Type& el_ty = *libcsel_ir::Type::Relation(
//     //     { &libcasm_rt::Type::get( instr.type() ) },
//     //     { &libcasm_rt::Type::get( instr.get()->type() ) } );

//     // assert( el_ty.isRelation() and el_ty.arguments().size() == 1
//     //         and el_ty.results().size() == 1 );

//     // libcsel_ir::CallableUnit* el = new libcsel_ir::Intrinsic(
//     //     instr.name(), &el_ty ); // PPA: TODO: add 'el' to context
//     // assert( el );

//     // auto arg = el->in( "arg", el_ty.arguments()[ 0 ] );
//     // auto ret = el->out( "ret", el_ty.results()[ 0 ] );

//     // libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( el );
//     // libcsel_ir::Statement* stmt = new libcsel_ir::TrivialStatement( scope
//     );

//     // auto idx0 = new libcsel_ir::BitConstant( 8, 0 );
//     // auto idx1 = new libcsel_ir::BitConstant( 8, 1 );

//     // auto arg_v_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx0 ) );
//     // auto arg_d_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx1 ) );

//     // auto ret_v_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx0 ) );
//     // auto ret_d_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx1 ) );

//     // auto arg_v = stmt->add( new libcsel_ir::LoadInstruction( arg_v_ptr )
//     );
//     // auto arg_d = stmt->add( new libcsel_ir::LoadInstruction( arg_d_ptr )
//     );

//     // libcsel_ir::Value* r0 = 0;
//     // if( instr.get()->type().isBit() )
//     // {
//     //     r0 = stmt->add( new libcsel_ir::NotInstruction( arg_v ) );
//     // }
//     // else
//     // {
//     //     r0 = stmt->add( new libcsel_ir::LnotInstruction( arg_v ) );
//     // }

//     // stmt->add( new libcsel_ir::StoreInstruction( r0, ret_v_ptr ) );
//     // stmt->add( new libcsel_ir::StoreInstruction( arg_d, ret_d_ptr ) );

//     // return el;
// }

// libcsel_ir::CallableUnit* Instruction::Equ(
//     libcasm_ir::EquInstruction& instr, libcsel_ir::Module* module )
// {
//     return 0;
//     // libcasm_ir::Type& ir_ty = instr.type();
//     // assert( not ir_ty.isRelation() );

//     // libcsel_ir::Type& el_ty = *libcsel_ir::Type::Relation(
//     //     { &libcasm_rt::Type::get( instr.type() ) },
//     //     { &libcasm_rt::Type::get( instr.lhs().type() ),
//     //         &libcasm_rt::Type::get( instr.rhs().type() ) } );

//     // assert( el_ty.isRelation() and el_ty.arguments().size() == 2
//     //         and el_ty.results().size() == 1 );

//     // libcsel_ir::CallableUnit* el = new libcsel_ir::Intrinsic(
//     //     instr.name(), &el_ty ); // PPA: TODO: add 'el' to context
//     // assert( el );

//     // auto lhs = el->in( "lhs", el_ty.arguments()[ 0 ] );
//     // auto rhs = el->in( "lhs", el_ty.arguments()[ 1 ] );
//     // auto ret = el->out( "ret", el_ty.results()[ 0 ] );

//     // libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( el );
//     // libcsel_ir::Statement* stmt = new libcsel_ir::TrivialStatement( scope
//     );

//     // auto idx0 = new libcsel_ir::BitConstant( 8, 0 );
//     // auto idx1 = new libcsel_ir::BitConstant( 8, 1 );

//     // auto lhs_v_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( lhs, idx0 ) );
//     // auto lhs_d_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( lhs, idx1 ) );

//     // auto rhs_v_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( rhs, idx0 ) );
//     // auto rhs_d_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( rhs, idx1 ) );

//     // auto ret_v_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx0 ) );
//     // auto ret_d_ptr
//     //     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx1 ) );

//     // auto lhs_v = stmt->add( new libcsel_ir::LoadInstruction( lhs_v_ptr )
//     );
//     // auto lhs_d = stmt->add( new libcsel_ir::LoadInstruction( lhs_d_ptr )
//     );

//     // auto rhs_v = stmt->add( new libcsel_ir::LoadInstruction( rhs_v_ptr )
//     );
//     // auto rhs_d = stmt->add( new libcsel_ir::LoadInstruction( rhs_d_ptr )
//     );

//     // // not(ld or rd) or ( (ld and rd) and (lv == rv) )
//     // // not( r0 ) or ( r1 and r2 )
//     // // r3 or r4
//     // // r5

//     // auto r0 = stmt->add( new libcsel_ir::OrInstruction( lhs_d, rhs_d ) );
//     // auto r1 = stmt->add( new libcsel_ir::AndInstruction( lhs_d, rhs_d ) );
//     // auto r2 = stmt->add( new libcsel_ir::EquInstruction( lhs_v, rhs_v ) );
//     // auto r3 = stmt->add( new libcsel_ir::LnotInstruction( r0 ) );
//     // auto r4 = stmt->add( new libcsel_ir::AndInstruction( r1, r2 ) );
//     // auto r5 = stmt->add( new libcsel_ir::OrInstruction( r3, r4 ) );

//     // stmt->add( new libcsel_ir::StoreInstruction( r5, ret_v_ptr ) );

//     // stmt->add( new libcsel_ir::StoreInstruction(
//     //     new libcsel_ir::BitConstant( 1, 1 ), ret_d_ptr ) );

//     // return el;
// }

// template < class INSTR >
// libcsel_ir::CallableUnit* ArithmeticInstruction< INSTR >::create(
//     libcasm_ir::Value& instr, libcsel_ir::Module* module )
// {
//     assert( libcasm_ir::isa< libcasm_ir::BinaryInstruction >( &value ) );
//     assert( libcasm_ir::isa< libcasm_ir::ArithmeticInstruction >( &value ) );

//     libcasm_ir::ArithmeticInstruction* instr
//         = (libcasm_ir::ArithmeticInstruction*)&value;

//     static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
//     cache;

//     libcsel_ir::Structure* ta
//         = libcasm_rt::Type::create( *instr->value( 0 ) );
//     libcsel_ir::Structure* tb
//         = libcasm_rt::Type::create( *instr->value( 1 ) );
//     libcsel_ir::Structure* tt = libcasm_rt::Type::create( *instr );

//     std::string key
//         = std::string( "casmrt_" + std::string( &instr.name()[ 1 ] ) + "_"
//                        + std::string( ta->name() )
//                        + "_"
//                        + std::string( tb->name() )
//                        + "_"
//                        + std::string( tt->name() ) );

//     if( cache.count( key ) > 0 )
//     {
//         return cache[ key ];
//     }

//     const char* name = libstdhl::Allocator::string( key );

//     libcsel_ir::CallableUnit* obj = new libcsel_ir::Intrinsic( name );
//     assert( obj );
//     cache[ key ] = obj;
//     if( module )
//     {
//         module->add( obj );
//     }

//     libcsel_ir::Reference* ra = obj->in( "a", ta->type() );
//     libcsel_ir::Reference* rb = obj->in( "b", tb->type() );
//     libcsel_ir::Reference* rt = obj->out( "t", tt->type() );

//     libcsel_ir::Scope* scope = 0; // new libcsel_ir::ParallelScope( obj );
//     if( strcmp( &instr.name()[ 1 ], "div" )
//         == 0 ) // TODO: EXPERIMENTIAL: DEMO ONLY!!!
//     {
//         scope = new libcsel_ir::SequentialScope( obj );
//     }
//     else
//     {
//         scope = new libcsel_ir::ParallelScope( obj );
//     }

//     libcsel_ir::Value* rav = new libcsel_ir::ExtractInstruction(
//         ra, ra->getStructure()->get( 0 ) );
//     libcsel_ir::Value* rad = new libcsel_ir::ExtractInstruction(
//         ra, ra->getStructure()->get( 1 ) );
//     libcsel_ir::Value* rbv = new libcsel_ir::ExtractInstruction(
//         rb, rb->getStructure()->get( 0 ) );
//     libcsel_ir::Value* rbd = new libcsel_ir::ExtractInstruction(
//         rb, rb->getStructure()->get( 1 ) );

//     libcsel_ir::Value* lav = new libcsel_ir::LoadInstruction( rav );
//     libcsel_ir::Value* lad = new libcsel_ir::LoadInstruction( rad );
//     libcsel_ir::Value* lbv = new libcsel_ir::LoadInstruction( rbv );
//     libcsel_ir::Value* lbd = new libcsel_ir::LoadInstruction( rbd );

//     libcsel_ir::Value* icv = new INSTR( lav, lbv );
//     libcsel_ir::Value* icd = new libcsel_ir::AndInstruction( lad, lbd );

//     libcsel_ir::Value* rtv = new libcsel_ir::ExtractInstruction(
//         rt, rt->getStructure()->get( 0 ) );
//     libcsel_ir::Value* rtd = new libcsel_ir::ExtractInstruction(
//         rt, rt->getStructure()->get( 1 ) );

//     libcsel_ir::Value* scv = new libcsel_ir::StoreInstruction( icv, rtv );
//     libcsel_ir::Value* scd = new libcsel_ir::StoreInstruction( icd, rtd );

//     libcsel_ir::Statement* stmt_v = new libcsel_ir::TrivialStatement( scope
//     );
//     libcsel_ir::Statement* stmt_d = new libcsel_ir::TrivialStatement( scope
//     );
//     stmt_v->add( scv );
//     stmt_d->add( scd );

//     return obj;
// }

// // libcsel_ir::CallableUnit* AddInstruction::create( libcasm_ir::Value&
// value,
// // libcsel_ir::Module* module )
// // {
// // 	return ArithmeticInstruction< libcsel_ir::AddSignedInstruction
// >::create(
// // value, module );
// // }

// // libcsel_ir::CallableUnit* DivInstruction::create( libcasm_ir::Value&
// value,
// // libcsel_ir::Module* module )
// // {
// // 	return ArithmeticInstruction< libcsel_ir::DivSignedInstruction
// >::create(
// // value, module );
// // }

// libcsel_ir::CallableUnit* EquInstruction::create(
//     libcasm_ir::Value& instr, libcsel_ir::Module* module )
// {
//     assert( libcasm_ir::isa< libcasm_ir::EquInstruction >( &value ) );
//     libcasm_ir::EquInstruction* instr = (libcasm_ir::EquInstruction*)&value;

//     static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
//     cache;

//     libcsel_ir::Structure* ta = libcasm_rt::Type::create( *instr->getLHS() );
//     libcsel_ir::Structure* tb = libcasm_rt::Type::create( *instr->getRHS() );
//     libcsel_ir::Structure* tt = libcasm_rt::Type::create( *instr );

//     std::string key
//         = std::string( "casmrt_" + std::string( &instr.name()[ 1 ] ) + "_"
//                        + std::string( ta->name() )
//                        + "_"
//                        + std::string( tb->name() )
//                        + "_"
//                        + std::string( tt->name() ) );

//     if( cache.count( key ) > 0 )
//     {
//         return cache[ key ];
//     }

//     const char* name = libstdhl::Allocator::string( key );

//     libcsel_ir::CallableUnit* obj = new libcsel_ir::Intrinsic( name );
//     assert( obj );
//     cache[ key ] = obj;
//     if( module )
//     {
//         module->add( obj );
//     }

//     libcsel_ir::Reference* ra = obj->in( "a", ta->type() );
//     libcsel_ir::Reference* rb = obj->in( "b", tb->type() );
//     libcsel_ir::Reference* rt = obj->out( "t", tt->type() );

//     libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( obj );

//     libcsel_ir::Value* rav = new libcsel_ir::ExtractInstruction(
//         ra, ra->getStructure()->get( 0 ) );
//     libcsel_ir::Value* rad = new libcsel_ir::ExtractInstruction(
//         ra, ra->getStructure()->get( 1 ) );
//     libcsel_ir::Value* rbv = new libcsel_ir::ExtractInstruction(
//         rb, rb->getStructure()->get( 0 ) );
//     libcsel_ir::Value* rbd = new libcsel_ir::ExtractInstruction(
//         rb, rb->getStructure()->get( 1 ) );
//     libcsel_ir::Value* rtv = new libcsel_ir::ExtractInstruction(
//         rt, rt->getStructure()->get( 0 ) );
//     libcsel_ir::Value* rtd = new libcsel_ir::ExtractInstruction(
//         rt, rt->getStructure()->get( 1 ) );

//     libcsel_ir::Value* lav = new libcsel_ir::LoadInstruction( rav );
//     libcsel_ir::Value* lad = new libcsel_ir::LoadInstruction( rad );
//     libcsel_ir::Value* lbv = new libcsel_ir::LoadInstruction( rbv );
//     libcsel_ir::Value* lbd = new libcsel_ir::LoadInstruction( rbd );

//     libcsel_ir::Statement* stmt_d = new libcsel_ir::TrivialStatement( scope
//     );
//     libcsel_ir::Value* def = libcsel_ir::BitConstant::create( 1, 1 );
//     if( module )
//     {
//         module->add( def );
//     }
//     libcsel_ir::Value* scd = new libcsel_ir::StoreInstruction( def, rtd );
//     stmt_d->add( scd );

//     libcsel_ir::Value* check = new libcsel_ir::AndInstruction( lad, lbd );
//     libcsel_ir::Statement* br = new libcsel_ir::BranchStatement( scope );
//     br->add( rtv );
//     br->add( check );

//     libcsel_ir::Scope* br_true = new libcsel_ir::ParallelScope();
//     br->addScope( br_true );
//     libcsel_ir::Value* equ_v
//         = new libcsel_ir::EquUnsignedInstruction( lav, lbv );
//     libcsel_ir::Value* equ_s = new libcsel_ir::StoreInstruction( equ_v, rtv
//     );
//     libcsel_ir::Statement* st_true
//         = new libcsel_ir::TrivialStatement( br_true );
//     st_true->add( equ_s );

//     libcsel_ir::Scope* br_false = new libcsel_ir::ParallelScope();
//     br->addScope( br_false );
//     libcsel_ir::Value* equ_x = new libcsel_ir::XorInstruction( lad, lbd );
//     libcsel_ir::Value* equ_y = new libcsel_ir::NotInstruction( equ_x );
//     libcsel_ir::Value* equ_u = new libcsel_ir::StoreInstruction( equ_y, rtv
//     );
//     libcsel_ir::Statement* st_false
//         = new libcsel_ir::TrivialStatement( br_false );
//     st_false->add( equ_u );

//     return obj;
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
