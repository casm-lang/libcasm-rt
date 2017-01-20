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
#include "../casm-ir/src/Type.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Intrinsic.h"
#include "../csel-ir/src/Reference.h"
#include "../csel-ir/src/Scope.h"
#include "../csel-ir/src/Statement.h"

// #include "CasmRT.h"
// #include "libcsel-ir.h"

using namespace libcasm_rt;

libcsel_ir::CallableUnit& Builtin::getAsBoolean(
    libcasm_ir::Value& value, libcsel_ir::Module* context )
{
    static std::unordered_map< std::string, libcsel_ir::CallableUnit* > cache;

    libstdhl::Log::info( "%s: %s %s aka. %s", __FUNCTION__, value.getName(),
        value.getType()->getDescription(), value.getType()->getName() );

    std::string key = "";
    key += value.getName();
    key += " ";
    key += value.getType()->getName();

    auto result = cache.find( key );
    if( result != cache.end() )
    {
        return *result->second;
    }

    libcasm_ir::Type& ir_ty = *value.getType();
    assert( ir_ty.isRelation() and ir_ty.getArguments().size() == 1 );

    libcsel_ir::Type& el_ty = libcasm_rt::Type::get( ir_ty );
    assert( el_ty.isRelation() and el_ty.getArguments().size() == 1
            and el_ty.getResults().size() == 1 );

    libcasm_ir::AsBooleanBuiltin& instr
        = libcasm_ir::cast< libcasm_ir::AsBooleanBuiltin >( value );

    libcsel_ir::CallableUnit* el = new libcsel_ir::Intrinsic(
        instr.getLabel(), &el_ty ); // PPA: TODO: add 'el' to context
    assert( el );

    libcsel_ir::Value* arg = el->in( "arg", el_ty.getArguments()[ 0 ] );
    libcsel_ir::Value* ret = el->out( "ret", el_ty.getResults()[ 0 ] );

    libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( el );
    libcsel_ir::Statement* stmt = new libcsel_ir::TrivialStatement( scope );

    libcsel_ir::Value* idx0
        = libcsel_ir::Constant::getBit( libcsel_ir::Type::getBit( 8 ), 0 );
    libcsel_ir::Value* idx1
        = libcsel_ir::Constant::getBit( libcsel_ir::Type::getBit( 8 ), 1 );

    libcsel_ir::Value* arg_v_ptr
        = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx0 ) );
    libcsel_ir::Value* arg_d_ptr
        = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx1 ) );
    
    libcsel_ir::Value* arg_v
        = stmt->add( new libcsel_ir::LoadInstruction( arg_v_ptr ) );
    libcsel_ir::Value* arg_d
        = stmt->add( new libcsel_ir::LoadInstruction( arg_d_ptr ) );
    
    
    libcsel_ir::Value* ret_v_ptr
        = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx0 ) );
    libcsel_ir::Value* ret_d_ptr
        = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx1 ) );
    
    
    
    cache[ key ] = el;
    return *el;
}

// libcsel_ir::CallableUnit* AsBooleanBuiltin::create(
//     libcasm_ir::Value& value, libcsel_ir::Module* module )
// {
//     assert( libcasm_ir::isa< libcasm_ir::AsBooleanBuiltin >( &value ) );
//     libcasm_ir::AsBooleanBuiltin& instr
//         = static_cast< libcasm_ir::AsBooleanBuiltin& >( value );

//     static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
//     cache;

//     libcsel_ir::Structure* ta = libcasm_rt::Type::create( *instr->getLHS() );
//     libcsel_ir::Structure* tb = libcasm_rt::Type::create( *instr->getRHS() );
//     libcsel_ir::Structure* tt = libcasm_rt::Type::create( *instr );

//     std::string key = std::string(
//         "casmrt_" + std::string( value.getName() ) + "_TODO_ARGS" );
//     // + std::string( ta->getName() )
//     // + "_"
//     // + std::string( tb->getName() )
//     // + "_"
//     // + std::string( tt->getName() ) );

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

//     libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( obj );

//     libcsel_ir::Statement* stmt_d = new libcsel_ir::TrivialStatement( scope
//     );
//     libcsel_ir::Value* def = libcsel_ir::BitConstant::create( 1, 1 );
//     if( module )
//     {
//         module->add( def );
//     }

//     stmt_d->add( new libcsel_ir::NopInstruction() );

//     return obj;
// }
