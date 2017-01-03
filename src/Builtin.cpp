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

#include "Builtin.h"

using namespace libcasm_rt;


libcsel_ir::CallableUnit* AsBooleanBuiltin::create(
    libcasm_ir::Value& value, libcsel_ir::Module* module )
{
    assert( libcasm_ir::Value::isa< libcasm_ir::AsBooleanBuiltin >( &value ) );
    libcasm_ir::AsBooleanBuiltin& instr = static_cast< libcasm_ir::AsBooleanBuiltin& >( value );
    
    static std::unordered_map< std::string, libcsel_ir::CallableUnit* > cache;
    
    // libcsel_ir::Structure* ta = libcasm_rt::Type::create( *instr->getLHS() );
    // libcsel_ir::Structure* tb = libcasm_rt::Type::create( *instr->getRHS() );
    // libcsel_ir::Structure* tt = libcasm_rt::Type::create( *instr );
    
    std::string key
        = std::string( "casmrt_" + std::string( value.getName() ) + "_TODO_ARGS" );
                       // + std::string( ta->getName() )
                       // + "_"
                       // + std::string( tb->getName() )
                       // + "_"
                       // + std::string( tt->getName() ) );

    if( cache.count( key ) > 0 )
    {
        return cache[ key ];
    }
    
    const char* name = libstdhl::Allocator::string( key );

    libcsel_ir::CallableUnit* obj = new libcsel_ir::Intrinsic( name );
    assert( obj );
    
    cache[ key ] = obj;

    if( module )
    {
        module->add( obj );
    }
    
    libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( obj );

    libcsel_ir::Statement* stmt_d = new libcsel_ir::TrivialStatement( scope );
    libcsel_ir::Value* def = libcsel_ir::BitConstant::create( 1, 1 );
    if( module )
    {
        module->add( def );
    }
    
    stmt_d->add( new libcsel_ir::NopInstruction() );
    
    return obj;
}
