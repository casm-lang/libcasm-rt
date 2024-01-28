//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-rt/graphs/contributors>
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

#include "Update.h"

using namespace libcasm_rt;

// libcsel_ir::CallableUnit* HashImplementation::create( void )
// {
//     static libcsel_ir::CallableUnit* obj = 0;
//     if( obj )
//     {
//         return obj;
//     }

//     obj = new libcsel_ir::Intrinsic( "casmrt_hash" );
//     assert( obj );

//     libcsel_ir::Value* v = obj->in( "value", &libcsel_ir::TypeId );
//     libcsel_ir::Value* s = obj->in( "size", &libcsel_ir::TypeB16 );
//     libcsel_ir::Value* r = obj->out( "res", &libcsel_ir::TypeB16 );

//     libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope( obj
//     );
//     libcsel_ir::TrivialStatement* blk
//         = new libcsel_ir::TrivialStatement( scope );

//     // libcsel_ir::StreamInstruction* output = new
//     // libcsel_ir::StreamInstruction(
//     // libcsel_ir::StreamInstruction::OUTPUT );
//     // assert( output );
//     // output->add( libcsel_ir::StringConstant::create( "hash" ) );
//     // output->add( &libcsel_ir::StringConstant::LF );
//     // blk->add( output );

//     libcsel_ir::Instruction* s_
//         = new libcsel_ir::ZeroExtendInstruction( s, v->getType() );
//     libcsel_ir::Instruction* p_
//         = new libcsel_ir::ModUnsignedInstruction( v, s_ );
//     libcsel_ir::Instruction* t_
//         = new libcsel_ir::TruncationInstruction( p_, r->getType() );
//     libcsel_ir::Instruction* r_ = new libcsel_ir::StoreInstruction( t_, r );
//     blk->add( r_ );

//     return obj;
// }

// libcsel_ir::CallableUnit* UpdateImplementation::create(
//     libcasm_ir::UpdateInstruction& value, libcsel_ir::Module* module )
// {
//     static std::unordered_map< libcsel_ir::Structure*,
//         libcsel_ir::CallableUnit* >
//         cache;

//     libcsel_ir::Structure* key
//         = libcasm_rt::Type::create( *( value.getRHS() ) );
//     if( cache.count( key ) > 0 )
//     {
//         return cache[ key ];
//     }

//     const char* name = libstdhl::Allocator::string(
//         "casmrt_update_" + std::string( key->getName() ) );

//     libcsel_ir::CallableUnit* obj = new libcsel_ir::Intrinsic( name );
//     assert( obj );
//     cache[ key ] = obj;
//     if( module )
//     {
//         module->add( obj );
//     }

//     libcsel_ir::Memory* uset_mem = libcasm_rt::UpdateSet::create();

//     libcsel_ir::Value* uset = obj->in( "uset", uset_mem->getType() );
//     libcsel_ir::Value* loc = obj->in(
//         "loc", &libcsel_ir::TypeId ); // ASSUMTION: PPA: addresses stay
//                                       // in the 48-bit range!
//     libcsel_ir::Value* val = obj->in( "value", key->getType() );

//     libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope( obj
//     );
//     libcsel_ir::TrivialStatement* blk
//         = new libcsel_ir::TrivialStatement( scope );
//     // libcsel_ir::StreamInstruction* output = new
//     // libcsel_ir::StreamInstruction(
//     // libcsel_ir::StreamInstruction::OUTPUT );
//     // assert( output );
//     // output->add( libcsel_ir::StringConstant::create( "update" ) );
//     // output->add( &libcsel_ir::StringConstant::LF );
//     // blk->add( output );

//     libcsel_ir::CallableUnit* hash = HashImplementation::create();
//     libcsel_ir::Instruction* hash_call
//         = new libcsel_ir::CallInstruction( hash );

//     u16 size = hash->getReference( "size" )->getType()->getBitsize();
//     libcsel_ir::Value* size_bc
//         = libcsel_ir::BitConstant::create( uset_mem->getSize(), size );
//     if( module )
//     {
//         module->add( size_bc );
//     }

//     libcsel_ir::Instruction* pos = new libcsel_ir::AllocInstruction(
//         hash->getReference( "res" )->getType() );
//     hash_call->add( loc );
//     hash_call->add( size_bc );
//     hash_call->add( pos );
//     blk->add( hash_call );

//     libcsel_ir::Instruction* pos_
//         = new libcsel_ir::ZeroExtendInstruction( pos, &libcsel_ir::TypeId );

//     libcsel_ir::Instruction* el
//         = new libcsel_ir::ExtractInstruction( uset, pos_ );
//     libcsel_ir::Structure* update_type = libcasm_rt::Update::create();
//     libcsel_ir::Instruction* ca
//         = new libcsel_ir::CastInstruction( update_type, el );

//     libcsel_ir::Instruction* u_bra
//         = new libcsel_ir::ExtractInstruction( ca, update_type->get( 0 ) );
//     libcsel_ir::Instruction* u_loc
//         = new libcsel_ir::ExtractInstruction( ca, update_type->get( 1 ) );
//     libcsel_ir::Instruction* u_val
//         = new libcsel_ir::ExtractInstruction( ca, update_type->get( 2 ) );
//     libcsel_ir::Instruction* u_def
//         = new libcsel_ir::ExtractInstruction( ca, update_type->get( 3 ) );

//     libcsel_ir::Instruction* v_val
//         = new libcsel_ir::ExtractInstruction( val, key->get( 0 ) );
//     libcsel_ir::Instruction* v_def
//         = new libcsel_ir::ExtractInstruction( val, key->get( 1 ) );

//     libcsel_ir::Value* u_c = libcsel_ir::BitConstant::create( 1, 1 );
//     if( module )
//     {
//         module->add( u_c );
//     }
//     libcsel_ir::Instruction* s_bra
//         = new libcsel_ir::StoreInstruction( u_c, u_bra );
//     blk->add( s_bra );
//     libcsel_ir::Instruction* s_loc
//         = new libcsel_ir::StoreInstruction( loc, u_loc );
//     blk->add( s_loc );

//     if( v_val->getType()->getBitsize() < u_val->getType()->getBitsize() )
//     {
//         v_val
//             = new libcsel_ir::ZeroExtendInstruction( v_val, u_val->getType()
//             );
//     }

//     libcsel_ir::Instruction* s_val
//         = new libcsel_ir::StoreInstruction( v_val, u_val );
//     blk->add( s_val );
//     libcsel_ir::Instruction* s_def
//         = new libcsel_ir::StoreInstruction( v_def, u_def );
//     blk->add( s_def );

//     return obj;
// }

// libcsel_ir::CallableUnit* LookupImplementation::create(
//     libcasm_ir::LookupInstruction& value, libcsel_ir::Module* module )
// {
//     static std::unordered_map< libcsel_ir::Structure*,
//         libcsel_ir::CallableUnit* >
//         cache;

//     libcsel_ir::Structure* key = libcasm_rt::Type::create( *( value.get() )
//     );
//     if( cache.count( key ) > 0 )
//     {
//         return cache[ key ];
//     }

//     const char* name = libstdhl::Allocator::string(
//         "casmrt_lookup_" + std::string( key->getName() ) );

//     libcsel_ir::CallableUnit* obj = new libcsel_ir::Intrinsic( name );
//     assert( obj );
//     cache[ key ] = obj;
//     if( module )
//     {
//         module->add( obj );
//     }

//     libcsel_ir::Value* refs
//         = obj->in( "refs", libcasm_rt::State::create()->getType() );
//     /*libcsel_ir::Value* uset = */ obj->in(
//         "uset", libcasm_rt::UpdateSet::create()->getType() );
//     libcsel_ir::Value* loc = obj->in(
//         "loc", &libcsel_ir::TypeId ); // ASSUMTION: PPA: addresses stay
//                                       // in the 48-bit range!
//     libcsel_ir::Value* val = obj->out( "value", key->getType() );

//     libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope( obj
//     );
//     libcsel_ir::TrivialStatement* blk
//         = new libcsel_ir::TrivialStatement( scope );

//     // libcsel_ir::StreamInstruction* output = new
//     // libcsel_ir::StreamInstruction(
//     // libcsel_ir::StreamInstruction::OUTPUT );
//     // assert( output );
//     // output->add( libcsel_ir::StringConstant::create( "lookup" ) );
//     // output->add( &libcsel_ir::StringConstant::LF );
//     // blk->add( output );

//     // PPA: EXPERIMENTAL: needs more attention in the future, because we only
//     // support parallel only for now!!!
//     libcsel_ir::Instruction* el
//         = new libcsel_ir::ExtractInstruction( refs, loc );
//     libcsel_ir::Instruction* ca
//         = new libcsel_ir::CastInstruction( libcasm_rt::Integer::create(), el
//         );
//     libcsel_ir::Instruction* ld = new libcsel_ir::LoadInstruction( ca );
//     libcsel_ir::Instruction* st = new libcsel_ir::StoreInstruction( ld, val
//     );
//     blk->add( st );

//     return obj;
// }

// libcsel_ir::Variable* FunctionState::create( libcasm_ir::Function& value )
// {
//     static std::unordered_map< libcasm_ir::Function*, libcsel_ir::Variable* >
//         cache;
//     if( cache.count( &value ) > 0 )
//     {
//         return cache[&value ];
//     }

//     libcsel_ir::Structure* ty = Type::create( value );
//     libcsel_ir::Variable* obj = new libcsel_ir::Variable( ty->getType(),
//         libcasm_rt::Constant::create( *ty->getType() ),
//         libstdhl::Allocator::string( value.getName() ) );
//     assert( obj );

//     if( strcmp( value.getName(), "program" ) == 0 )
//     {
//         ProgramFunctionState::create( obj );
//     }

//     cache[&value ] = obj;
//     return obj;
// }

// libcsel_ir::CallableUnit* FunctionLocation::create(
//     libcasm_ir::Function& value )
// {
//     std::string* name = new std::string(
//         "casmrt_location_" + std::string( value.getName() ) );
//     libcsel_ir::Intrinsic* obj = new libcsel_ir::Intrinsic( name->c_str() );
//     assert( obj );

//     libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope();
//     assert( scope );
//     obj->setContext( scope );

//     libcsel_ir::TrivialStatement* stmt
//         = new libcsel_ir::TrivialStatement( scope );
//     libcsel_ir::IdInstruction* id
//         = new libcsel_ir::IdInstruction( FunctionState::create( value ) );
//     assert( id );

//     // output parameter for intrinsic!
//     libcsel_ir::Reference* loc = new libcsel_ir::Reference( "location",
//         id->getType() // ASSUMTION: PPA: addresses stay in the 48-bit range!
//         ,
//         obj, libcsel_ir::Reference::OUTPUT );
//     assert( loc );

//     libcsel_ir::StoreInstruction* store
//         = new libcsel_ir::StoreInstruction( id, loc );
//     assert( store );
//     stmt->add( store );

//     return obj;
// }

// libcsel_ir::Variable* ProgramFunctionState::create(
//     libcsel_ir::Variable* value )
// {
//     static libcsel_ir::Variable* obj = 0;

//     if( not obj )
//     {
//         assert( not obj );
//         obj = value;
//     }

//     assert( obj );
//     return obj;
// }

// libcsel_ir::CallableUnit* ProgramRuleSignature::create( void )
// {
//     static libcsel_ir::CallableUnit* obj = 0;
//     if( not obj )
//     {
//         obj = new libcsel_ir::Function( "casmrt_signature_rule" );
//         assert( obj );

//         obj->in( "refs", libcasm_rt::State::create()->getType() );
//         obj->in( "uset", libcasm_rt::UpdateSet::create()->getType() );
//     }
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
