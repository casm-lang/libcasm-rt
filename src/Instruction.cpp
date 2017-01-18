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

using namespace libcasm_rt;

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
//         = libcasm_rt::Type::create( *instr->getValue( 0 ) );
//     libcsel_ir::Structure* tb
//         = libcasm_rt::Type::create( *instr->getValue( 1 ) );
//     libcsel_ir::Structure* tt = libcasm_rt::Type::create( *instr );

//     std::string key
//         = std::string( "casmrt_" + std::string( &value.getName()[ 1 ] ) + "_"
//                        + std::string( ta->getName() )
//                        + "_"
//                        + std::string( tb->getName() )
//                        + "_"
//                        + std::string( tt->getName() ) );

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

//     libcsel_ir::Reference* ra = obj->in( "a", ta->getType() );
//     libcsel_ir::Reference* rb = obj->in( "b", tb->getType() );
//     libcsel_ir::Reference* rt = obj->out( "t", tt->getType() );

//     libcsel_ir::Scope* scope = 0; // new libcsel_ir::ParallelScope( obj );
//     if( strcmp( &value.getName()[ 1 ], "div" )
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
//         = std::string( "casmrt_" + std::string( &value.getName()[ 1 ] ) + "_"
//                        + std::string( ta->getName() )
//                        + "_"
//                        + std::string( tb->getName() )
//                        + "_"
//                        + std::string( tt->getName() ) );

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

//     libcsel_ir::Reference* ra = obj->in( "a", ta->getType() );
//     libcsel_ir::Reference* rb = obj->in( "b", tb->getType() );
//     libcsel_ir::Reference* rt = obj->out( "t", tt->getType() );

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
