//
//  Copyright (c) 2014-2016 CASM Organization
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

#include "Update.h"

using namespace libcasm_rt;

libnovel::CallableUnit* HashImplementation::create( void )
{
    static libnovel::CallableUnit* obj = 0;
    if( obj )
    {
        return obj;
    }

    obj = new libnovel::Intrinsic( "casmrt_hash" );
    assert( obj );

    libnovel::Value* v = obj->in( "value", &libnovel::TypeId );
    libnovel::Value* s = obj->in( "size", &libnovel::TypeB16 );
    libnovel::Value* r = obj->out( "res", &libnovel::TypeB16 );

    libnovel::SequentialScope* scope = new libnovel::SequentialScope( obj );
    libnovel::TrivialStatement* blk = new libnovel::TrivialStatement( scope );

    // libnovel::StreamInstruction* output = new libnovel::StreamInstruction(
    // libnovel::StreamInstruction::OUTPUT );
    // assert( output );
    // output->add( libnovel::StringConstant::create( "hash" ) );
    // output->add( &libnovel::StringConstant::LF );
    // blk->add( output );

    libnovel::Instruction* s_
        = new libnovel::ZeroExtendInstruction( s, v->getType() );
    libnovel::Instruction* p_ = new libnovel::ModUnsignedInstruction( v, s_ );
    libnovel::Instruction* t_
        = new libnovel::TruncationInstruction( p_, r->getType() );
    libnovel::Instruction* r_ = new libnovel::StoreInstruction( t_, r );
    blk->add( r_ );

    return obj;
}

libnovel::CallableUnit* UpdateImplementation::create(
    libcasm_ir::UpdateInstruction& value, libnovel::Module* module )
{
    static std::unordered_map< libnovel::Structure*, libnovel::CallableUnit* >
        cache;

    libnovel::Structure* key = libcasm_rt::Type::create( *( value.getRHS() ) );
    if( cache.count( key ) > 0 )
    {
        return cache[ key ];
    }

    const char* name = libstdhl::Allocator::string(
        "casmrt_update_" + std::string( key->getName() ) );

    libnovel::CallableUnit* obj = new libnovel::Intrinsic( name );
    assert( obj );
    cache[ key ] = obj;
    if( module )
    {
        module->add( obj );
    }

    libnovel::Memory* uset_mem = libcasm_rt::UpdateSet::create();

    libnovel::Value* uset = obj->in( "uset", uset_mem->getType() );
    libnovel::Value* loc
        = obj->in( "loc", &libnovel::TypeId ); // ASSUMTION: PPA: addresses stay
                                               // in the 48-bit range!
    libnovel::Value* val = obj->in( "value", key->getType() );

    libnovel::SequentialScope* scope = new libnovel::SequentialScope( obj );
    libnovel::TrivialStatement* blk = new libnovel::TrivialStatement( scope );
    // libnovel::StreamInstruction* output = new libnovel::StreamInstruction(
    // libnovel::StreamInstruction::OUTPUT );
    // assert( output );
    // output->add( libnovel::StringConstant::create( "update" ) );
    // output->add( &libnovel::StringConstant::LF );
    // blk->add( output );

    libnovel::CallableUnit* hash = HashImplementation::create();
    libnovel::Instruction* hash_call = new libnovel::CallInstruction( hash );

    u16 size = hash->getReference( "size" )->getType()->getBitsize();
    libnovel::Value* size_bc
        = libnovel::BitConstant::create( uset_mem->getSize(), size );
    if( module )
    {
        module->add( size_bc );
    }

    libnovel::Instruction* pos = new libnovel::AllocInstruction(
        hash->getReference( "res" )->getType() );
    hash_call->add( loc );
    hash_call->add( size_bc );
    hash_call->add( pos );
    blk->add( hash_call );

    libnovel::Instruction* pos_
        = new libnovel::ZeroExtendInstruction( pos, &libnovel::TypeId );

    libnovel::Instruction* el = new libnovel::ExtractInstruction( uset, pos_ );
    libnovel::Structure* update_type = libcasm_rt::Update::create();
    libnovel::Instruction* ca
        = new libnovel::CastInstruction( update_type, el );

    libnovel::Instruction* u_bra
        = new libnovel::ExtractInstruction( ca, update_type->get( 0 ) );
    libnovel::Instruction* u_loc
        = new libnovel::ExtractInstruction( ca, update_type->get( 1 ) );
    libnovel::Instruction* u_val
        = new libnovel::ExtractInstruction( ca, update_type->get( 2 ) );
    libnovel::Instruction* u_def
        = new libnovel::ExtractInstruction( ca, update_type->get( 3 ) );

    libnovel::Instruction* v_val
        = new libnovel::ExtractInstruction( val, key->get( 0 ) );
    libnovel::Instruction* v_def
        = new libnovel::ExtractInstruction( val, key->get( 1 ) );

    libnovel::Value* u_c = libnovel::BitConstant::create( 1, 1 );
    if( module )
    {
        module->add( u_c );
    }
    libnovel::Instruction* s_bra = new libnovel::StoreInstruction( u_c, u_bra );
    blk->add( s_bra );
    libnovel::Instruction* s_loc = new libnovel::StoreInstruction( loc, u_loc );
    blk->add( s_loc );

    if( v_val->getType()->getBitsize() < u_val->getType()->getBitsize() )
    {
        v_val = new libnovel::ZeroExtendInstruction( v_val, u_val->getType() );
    }

    libnovel::Instruction* s_val
        = new libnovel::StoreInstruction( v_val, u_val );
    blk->add( s_val );
    libnovel::Instruction* s_def
        = new libnovel::StoreInstruction( v_def, u_def );
    blk->add( s_def );

    return obj;
}

libnovel::CallableUnit* LookupImplementation::create(
    libcasm_ir::LookupInstruction& value, libnovel::Module* module )
{
    static std::unordered_map< libnovel::Structure*, libnovel::CallableUnit* >
        cache;

    libnovel::Structure* key = libcasm_rt::Type::create( *( value.get() ) );
    if( cache.count( key ) > 0 )
    {
        return cache[ key ];
    }

    const char* name = libstdhl::Allocator::string(
        "casmrt_lookup_" + std::string( key->getName() ) );

    libnovel::CallableUnit* obj = new libnovel::Intrinsic( name );
    assert( obj );
    cache[ key ] = obj;
    if( module )
    {
        module->add( obj );
    }

    libnovel::Value* refs
        = obj->in( "refs", libcasm_rt::State::create()->getType() );
    /*libnovel::Value* uset = */ obj->in(
        "uset", libcasm_rt::UpdateSet::create()->getType() );
    libnovel::Value* loc
        = obj->in( "loc", &libnovel::TypeId ); // ASSUMTION: PPA: addresses stay
                                               // in the 48-bit range!
    libnovel::Value* val = obj->out( "value", key->getType() );

    libnovel::SequentialScope* scope = new libnovel::SequentialScope( obj );
    libnovel::TrivialStatement* blk = new libnovel::TrivialStatement( scope );

    // libnovel::StreamInstruction* output = new libnovel::StreamInstruction(
    // libnovel::StreamInstruction::OUTPUT );
    // assert( output );
    // output->add( libnovel::StringConstant::create( "lookup" ) );
    // output->add( &libnovel::StringConstant::LF );
    // blk->add( output );

    // PPA: EXPERIMENTAL: needs more attention in the future, because we only
    // support parallel only for now!!!
    libnovel::Instruction* el = new libnovel::ExtractInstruction( refs, loc );
    libnovel::Instruction* ca
        = new libnovel::CastInstruction( libcasm_rt::Integer::create(), el );
    libnovel::Instruction* ld = new libnovel::LoadInstruction( ca );
    libnovel::Instruction* st = new libnovel::StoreInstruction( ld, val );
    blk->add( st );

    return obj;
}

libnovel::Variable* FunctionState::create( libcasm_ir::Function& value )
{
    static std::unordered_map< libcasm_ir::Function*, libnovel::Variable* >
        cache;
    if( cache.count( &value ) > 0 )
    {
        return cache[&value ];
    }

    libnovel::Structure* ty = Type::create( value );
    libnovel::Variable* obj = new libnovel::Variable( ty->getType(),
        libcasm_rt::Constant::create( *ty->getType() ),
        libstdhl::Allocator::string( value.getName() ) );
    assert( obj );

    if( strcmp( value.getName(), "program" ) == 0 )
    {
        ProgramFunctionState::create( obj );
    }

    cache[&value ] = obj;
    return obj;
}

libnovel::CallableUnit* FunctionLocation::create( libcasm_ir::Function& value )
{
    std::string* name = new std::string(
        "casmrt_location_" + std::string( value.getName() ) );
    libnovel::Intrinsic* obj = new libnovel::Intrinsic( name->c_str() );
    assert( obj );

    libnovel::SequentialScope* scope = new libnovel::SequentialScope();
    assert( scope );
    obj->setContext( scope );

    libnovel::TrivialStatement* stmt = new libnovel::TrivialStatement( scope );
    libnovel::IdInstruction* id
        = new libnovel::IdInstruction( FunctionState::create( value ) );
    assert( id );

    // output parameter for intrinsic!
    libnovel::Reference* loc = new libnovel::Reference( "location",
        id->getType() // ASSUMTION: PPA: addresses stay in the 48-bit range!
        ,
        obj, libnovel::Reference::OUTPUT );
    assert( loc );

    libnovel::StoreInstruction* store
        = new libnovel::StoreInstruction( id, loc );
    assert( store );
    stmt->add( store );

    return obj;
}

libnovel::Variable* ProgramFunctionState::create( libnovel::Variable* value )
{
    static libnovel::Variable* obj = 0;

    if( not obj )
    {
        assert( not obj );
        obj = value;
    }

    assert( obj );
    return obj;
}

libnovel::CallableUnit* ProgramRuleSignature::create( void )
{
    static libnovel::CallableUnit* obj = 0;
    if( not obj )
    {
        obj = new libnovel::Function( "casmrt_signature_rule" );
        assert( obj );

        obj->in( "refs", libcasm_rt::State::create()->getType() );
        obj->in( "uset", libcasm_rt::UpdateSet::create()->getType() );
    }
    return obj;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
