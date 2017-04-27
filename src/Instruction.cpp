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
#include "Value.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Constant.h"
#include "../casm-ir/src/Instruction.h"
#include "../casm-ir/src/Value.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Constant.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Intrinsic.h"
#include "../csel-ir/src/Module.h"
#include "../csel-ir/src/Scope.h"
#include "../csel-ir/src/Statement.h"

// #include "../csel-ir/src/Reference.h"
// #include "../csel-ir/src/Value.h"

#include "../csel-rt/src/CallableUnit.h"
#include "../csel-rt/src/Instruction.h"

using namespace libcasm_rt;

libcsel_ir::CallableUnit::Ptr Instruction::Not(
    const libcasm_ir::NotInstruction& value, libcsel_ir::Module* module )
{
    static std::unordered_map< std::string,
        std::weak_ptr< libcsel_ir::CallableUnit > >
        cache;

    libstdhl::Log::info( "%s: %s %s",
        __FUNCTION__,
        value.name().c_str(),
        value.type().description().c_str() );

    const auto key = value.make_hash();

    auto result = cache.find( key );
    if( result != cache.end() )
    {
        return result->second.lock();
    }

    const auto& ir_ty = value.type();
    assert( not ir_ty.isRelation() );

    const auto el_ty = Type::get( ir_ty );

    assert( el_ty->isRelation() and el_ty->arguments().size() == 1
            and el_ty->results().size() == 1 );

    auto implementation = libstdhl::make< libcsel_ir::Intrinsic >( value.name(),
        el_ty ); // PPA: TODO: add 'el' to context
    assert( implementation );

    auto arg = implementation->in( "arg", el_ty->arguments()[ 0 ] );
    auto ret = implementation->out( "ret", el_ty->results()[ 0 ] );

    auto scope = libstdhl::make< libcsel_ir::ParallelScope >();
    implementation->setContext( scope );

    auto stmt = libstdhl::make< libcsel_ir::TrivialStatement >();
    stmt->setParent( scope );
    scope->add( stmt );

    const auto idx0 = libstdhl::get< libcsel_ir::BitConstant >( 8, 0 );
    const auto idx1 = libstdhl::get< libcsel_ir::BitConstant >( 8, 1 );

    const auto arg_v_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( arg, idx0 ) );
    const auto arg_d_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( arg, idx1 ) );

    const auto ret_v_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( ret, idx0 ) );
    const auto ret_d_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( ret, idx1 ) );

    const auto arg_v = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( arg_v_ptr ) );
    const auto arg_d = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( arg_d_ptr ) );

    libcsel_ir::Instruction::Ptr r0 = nullptr;

    if( value.get()->type().isBit() )
    {
        r0 = stmt->add( libstdhl::make< libcsel_ir::NotInstruction >( arg_v ) );
    }
    else
    {
        r0 = stmt->add(
            libstdhl::make< libcsel_ir::LnotInstruction >( arg_v ) );
    }

    stmt->add(
        libstdhl::make< libcsel_ir::StoreInstruction >( r0, ret_v_ptr ) );
    stmt->add(
        libstdhl::make< libcsel_ir::StoreInstruction >( arg_d, ret_d_ptr ) );

    cache[ key ] = implementation;
    return implementation;
}

libcsel_ir::CallableUnit::Ptr Instruction::Equ(
    const libcasm_ir::EquInstruction& value, libcsel_ir::Module* module )
{
    static std::unordered_map< std::string,
        std::weak_ptr< libcsel_ir::CallableUnit > >
        cache;

    libstdhl::Log::info( "%s: %s %s",
        __FUNCTION__,
        value.name().c_str(),
        value.type().description().c_str() );

    const auto key = value.make_hash();

    auto result = cache.find( key );
    if( result != cache.end() )
    {
        return result->second.lock();
    }

    const auto& ir_ty = value.type();
    assert( not ir_ty.isRelation() );

    const auto el_ty = Type::get( ir_ty );

    assert( el_ty->isRelation() and el_ty->arguments().size() == 2
            and el_ty->results().size() == 1 );

    auto implementation = libstdhl::make< libcsel_ir::Intrinsic >( value.name(),
        el_ty ); // PPA: TODO: add 'el' to context
    assert( implementation );

    auto lhs = implementation->in( "lhs", el_ty->arguments()[ 0 ] );
    auto rhs = implementation->in( "lhs", el_ty->arguments()[ 1 ] );
    auto ret = implementation->out( "ret", el_ty->results()[ 0 ] );

    auto scope = libstdhl::make< libcsel_ir::ParallelScope >();
    implementation->setContext( scope );

    auto stmt = libstdhl::make< libcsel_ir::TrivialStatement >();
    stmt->setParent( scope );
    scope->add( stmt );

    const auto idx0 = libstdhl::get< libcsel_ir::BitConstant >( 8, 0 );
    const auto idx1 = libstdhl::get< libcsel_ir::BitConstant >( 8, 1 );

    const auto lhs_v_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( lhs, idx0 ) );
    const auto lhs_d_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( lhs, idx1 ) );

    const auto rhs_v_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( rhs, idx0 ) );
    const auto rhs_d_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( rhs, idx1 ) );

    const auto ret_v_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( ret, idx0 ) );
    const auto ret_d_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( ret, idx1 ) );

    const auto lhs_v = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( lhs_v_ptr ) );
    const auto lhs_d = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( lhs_d_ptr ) );

    const auto rhs_v = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( rhs_v_ptr ) );
    const auto rhs_d = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( rhs_d_ptr ) );

    // not(ld or rd) or ( (ld and rd) and (lv == rv) )
    // not( r0 ) or ( r1 and r2 )
    // r3 or r4
    // r5

    const auto r0 = stmt->add(
        libstdhl::make< libcsel_ir::OrInstruction >( lhs_d, rhs_d ) );
    const auto r1 = stmt->add(
        libstdhl::make< libcsel_ir::AndInstruction >( lhs_d, rhs_d ) );
    const auto r2 = stmt->add(
        libstdhl::make< libcsel_ir::EquInstruction >( lhs_v, rhs_v ) );
    const auto r3
        = stmt->add( libstdhl::make< libcsel_ir::LnotInstruction >( r0 ) );
    const auto r4
        = stmt->add( libstdhl::make< libcsel_ir::AndInstruction >( r1, r2 ) );
    const auto r5
        = stmt->add( libstdhl::make< libcsel_ir::OrInstruction >( r3, r4 ) );

    stmt->add(
        libstdhl::make< libcsel_ir::StoreInstruction >( r5, ret_v_ptr ) );

    const auto one = libstdhl::get< libcsel_ir::BitConstant >( 1, 1 );
    stmt->add(
        libstdhl::make< libcsel_ir::StoreInstruction >( one, ret_d_ptr ) );

    cache[ key ] = implementation;
    return implementation;
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
