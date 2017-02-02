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

#include "Instruction.h"

#include "Builtin.h"
#include "Constant.h"
#include "Type.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Constant.h"
#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Value.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Constant.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Intrinsic.h"
#include "../csel-ir/src/Scope.h"
#include "../csel-ir/src/Value.h"

#include "../csel-rt/src/CallableUnit.h"
#include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

libcasm_ir::Value* Instruction::execute(
    libcasm_ir::Instruction& value, libcsel_ir::Module* module )
{
    libcsel_ir::Value* el_obj = get( value );

    libstdhl::Log::info( "%s: %s %s aka. %s", __FUNCTION__, el_obj->name(),
        el_obj->type().description(), el_obj->type().name() );

    libcsel_ir::Value* result = 0;

    if( libcsel_ir::isa< libcsel_ir::Instruction >( el_obj ) )
    {
        result = libcsel_rt::Instruction::execute(
            static_cast< libcsel_ir::Instruction& >( *el_obj ) );
    }
    else if( libcsel_ir::isa< libcsel_ir::CallableUnit >( el_obj ) )
    {
        result = libcsel_rt::CallableUnit::execute(
            static_cast< libcsel_ir::CallableUnit& >( *el_obj ) );
    }
    else
    {
        libstdhl::Log::error(
            " unsupported instr '%s' to execute ", el_obj->name() );
        assert( 0 );
        return 0;
    }

    switch( result->id() )
    {
        case libcsel_ir::Value::STRUCTURE_CONSTANT:
        {
            auto& str_val
                = static_cast< libcsel_ir::StructureConstant& >( *result );

            auto& ty_res = result->type().results();
            assert( ty_res.size() == 2 );

            if( ty_res[ 0 ]->isBit() and ty_res[ 0 ]->bitsize() == 1
                and ty_res[ 1 ]->isBit()
                and ty_res[ 1 ]->bitsize() == 1 )
            {
                // we found a boolean!
                libcsel_ir::BitConstant& v
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 0 ] );
                libcsel_ir::BitConstant& d
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 1 ] );

                if( d.value() )
                {
                    return libcasm_ir::Constant::Boolean( v.value() );
                }
                else
                {
                    return libcasm_ir::Constant::Undef(
                        libcasm_ir::Type::Boolean() );
                }
            }
            else if( ty_res[ 0 ]->isBit() and ty_res[ 0 ]->bitsize() == 64
                     and ty_res[ 1 ]->isBit()
                     and ty_res[ 1 ]->bitsize() == 1 )
            {
                // we found an integer!
                libcsel_ir::BitConstant& v
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 0 ] );
                libcsel_ir::BitConstant& d
                    = static_cast< libcsel_ir::BitConstant& >(
                        *str_val.value()[ 1 ] );

                if( d.value() )
                {
                    return libcasm_ir::Constant::Integer( v.value() );
                }
                else
                {
                    return libcasm_ir::Constant::Undef(
                        libcasm_ir::Type::Integer() );
                }
            }
            else
            {
                libstdhl::Log::error(
                    " unsupported result value '%s' of type '%s' ",
                    result->name(), result->type().name() );
            }
            break;
        }
        default:
        {
            libstdhl::Log::error(
                " unsupported result value '%s' of type '%s' ", result->name(),
                result->type().name() );
            break;
        }
    }

    assert( 0 );
    return 0;
}

libcsel_ir::Value* Instruction::get(
    libcasm_ir::Instruction& value, libcsel_ir::Module* module )
{
    switch( value.id() )
    {
        case libcasm_ir::Value::CALL_INSTRUCTION:
        {
            return getCall(
                static_cast< libcasm_ir::CallInstruction& >( value ), module );
        }
        case libcasm_ir::Value::EQU_INSTRUCTION:
        {
            return Equ(
                static_cast< libcasm_ir::EquInstruction& >( value ), module );
        }
        default:
        {
            break;
        }
    }

    libstdhl::Log::error(
        " unimplemented instruction transformation for '%s' with type "
        "'%s'",
        value.name(), value.type().description() );

    assert( 0 );
    return 0;
}

libcsel_ir::CallInstruction* Instruction::getCall(
    libcasm_ir::CallInstruction& value, libcsel_ir::Module* module )
{
    // static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
    // cache;

    libstdhl::Log::info( "%s: %s %s aka. %s", __FUNCTION__, value.name(),
        value.type().description(), value.type().name() );

    std::string key = "";
    key += value.name();
    key += " ";
    key += value.type().name();

    // auto result = cache.find( key );
    // if( result != cache.end() )
    // {
    //     libstdhl::Log::info( "found!" );
    //     return result->second;
    // }

    libcasm_ir::Type& ir_ty = value.type();
    assert( not ir_ty.isRelation() );

    // // libcsel_ir::Type& el_ty = libcasm_rt::Type::get( ir_ty );
    // // assert( not el_ty.isRelation()
    // //         and el_ty.getArguments().size() == ir_ty.getArguments().size()
    // //         and el_ty.results().size() == 1 );

    libcsel_ir::CallableUnit* callee = 0;
    libcsel_ir::CallInstruction* caller = 0;

    for( auto v : value.values() )
    {
        if( v == value.value( 0 ) )
        {
            assert( libcasm_ir::isa< libcasm_ir::Builtin >( v ) );
            callee = &Builtin::get( *v );

            caller = new libcsel_ir::CallInstruction( callee );
            continue;
        }

        assert( libcasm_ir::isa< libcasm_ir::Constant >( v ) );

        libstdhl::Log::info( "%s: %s %s aka. %s", __FUNCTION__, v->name(),
            v->type().description(), v->type().name() );

        caller->add( &Constant::get( *v ) );
    }

    caller->add(
        new libcsel_ir::AllocInstruction( callee->type().results()[ 0 ] ) );

    return caller;
}

libcsel_ir::CallableUnit* Instruction::Equ(
    libcasm_ir::EquInstruction& value, libcsel_ir::Module* module )
{
    static std::unordered_map< std::string, libcsel_ir::CallableUnit* > cache;

    libstdhl::Log::info( "%s: %s %s aka. %s", __FUNCTION__, value.name(),
        value.type().description(), value.type().name() );

    std::string key = "";
    key += value.name();
    key += " ";
    key += value.type().name();

    auto result = cache.find( key );
    if( result != cache.end() )
    {
        return result->second;
    }

    libcasm_ir::Type& ir_ty = value.type();
    assert( not ir_ty.isRelation() );

    libcsel_ir::Type& el_ty = *libcsel_ir::Type::Relation(
        { &libcasm_rt::Type::get( value.type() ) },
        { &libcasm_rt::Type::get( value.lhs().type() ),
            &libcasm_rt::Type::get( value.rhs().type() ) } );

    assert( el_ty.isRelation() and el_ty.arguments().size() == 2
            and el_ty.results().size() == 1 );

    libcsel_ir::CallableUnit* el = new libcsel_ir::Intrinsic(
        value.label(), &el_ty ); // PPA: TODO: add 'el' to context
    assert( el );

    // libcsel_ir::Value* arg = el->in( "arg", el_ty.arguments()[ 0 ] );
    // libcsel_ir::Value* ret = el->out( "ret", el_ty.results()[ 0 ] );

    libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( el );
    libcsel_ir::Statement* stmt = new libcsel_ir::TrivialStatement( scope );

    stmt->add( new libcsel_ir::NopInstruction() );

    cache[ key ] = el;
    return el;
}

//
//
// old
//
//

libcsel_ir::CallableUnit* Instruction::create(
    libcasm_ir::Value& value, libcsel_ir::Module* module )
{
    // if( libcasm_ir::isa< libcasm_ir::AddInstruction >( &value ) )
    // {
    //     return ArithmeticInstruction< libcsel_ir::AddSignedInstruction >::
    //         create( value, module );
    // }
    // else if( libcasm_ir::isa< libcasm_ir::DivInstruction >( &value ) )
    // {
    //     return ArithmeticInstruction< libcsel_ir::DivSignedInstruction >::
    //         create( value, module );
    // }
    // else if( libcasm_ir::isa< libcasm_ir::AndInstruction >( &value ) )
    // {
    //     assert( 0 );
    //     return 0;
    // }
    // else if( libcasm_ir::isa< libcasm_ir::EquInstruction >( &value ) )
    // {
    //     return EquInstruction::create( value, module );
    // }
    // else
    {
        assert( !" unsupported/unimplemented instruction to create run-time implementation! " );
    }

    return 0;
}

// template < class INSTR >
// libcsel_ir::CallableUnit* ArithmeticInstruction< INSTR >::create(
//     libcasm_ir::Value& value, libcsel_ir::Module* module )
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
//         = std::string( "casmrt_" + std::string( &value.name()[ 1 ] ) + "_"
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
//     if( strcmp( &value.name()[ 1 ], "div" )
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
//     libcasm_ir::Value& value, libcsel_ir::Module* module )
// {
//     assert( libcasm_ir::isa< libcasm_ir::EquInstruction >( &value ) );
//     libcasm_ir::EquInstruction* instr = (libcasm_ir::EquInstruction*)&value;

//     static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
//     cache;

//     libcsel_ir::Structure* ta = libcasm_rt::Type::create( *instr->getLHS() );
//     libcsel_ir::Structure* tb = libcasm_rt::Type::create( *instr->getRHS() );
//     libcsel_ir::Structure* tt = libcasm_rt::Type::create( *instr );

//     std::string key
//         = std::string( "casmrt_" + std::string( &value.name()[ 1 ] ) + "_"
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
