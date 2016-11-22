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

#include "Type.h"

using namespace libcasm_rt;

libcsel_ir::Structure* Type::create( libcasm_ir::Value& value )
{
    libcasm_ir::Type* type = value.getType();
    assert( type and " invalid type pointer! " );

    assert( type->getSubTypes().size() == 0 ); // PPA: LIMITATION for now!

    u64 tid = type->getResultType()->getID();

    if( tid == libcasm_ir::BooleanType.getID() )
    {
        return Boolean::create();
    }
    else if( tid == libcasm_ir::IntegerType.getID() )
    {
        return Integer::create();
    }
    else if( tid == libcasm_ir::RulePointerType.getID() )
    {
        return RulePtr::create();
    }
    else
    {
        assert( !" unsupported/unimplemented type id! " );
        return 0;
    }
}

struct type_factory_argument
{
    const char* name;
    libcsel_ir::Type* type;
};

static libcsel_ir::Structure* type_factory( const std::string& name,
    const std::vector< struct type_factory_argument >& args )
{
    libcsel_ir::Structure* type = new libcsel_ir::Structure(
        libstdhl::Allocator::string( name.c_str() ) );
    assert( type );
    type->getType()->bind( type );

    for( u32 c = 0; c < args.size(); c++ )
    {
        libcsel_ir::Structure* arg
            = new libcsel_ir::Structure( args[ c ].name, args[ c ].type, type );
        assert( arg );
    }

    return type;
}

libcsel_ir::Structure* Boolean::create( void )
{
    static libcsel_ir::Structure* type = 0;
    if( not type )
    {
        type
            = type_factory( "Boolean", { { "value", &libcsel_ir::TypeB1 },
                                           { "isdef", &libcsel_ir::TypeB1 } } );
    }
    return type;
}

libcsel_ir::Structure* Integer::create( void )
{
    static libcsel_ir::Structure* type = 0;
    if( not type )
    {
        type
            = type_factory( "Integer", { { "value", &libcsel_ir::TypeB64 },
                                           { "isdef", &libcsel_ir::TypeB1 } } );
    }
    return type;
}

libcsel_ir::Structure* String::create( libcasm_ir::StringConstant& value )
{
    static std::unordered_map< i16, libcsel_ir::Structure* > cache;

    i16 length = 0;
    if( value.getValue() )
    {
        length = strlen( value.getValue() );
    }

    if( cache.count( length ) > 0 )
    {
        return cache[ length ];
    }

    libcsel_ir::Structure* type = type_factory(
        libstdhl::Allocator::string(
            std::string( "String" + std::to_string( length ) ) ),
        { { "value", new libcsel_ir::Type( libcsel_ir::Type::STRING, length,
                         libcsel_ir::Type::STATE::LOCKED ) },
            { "isdef", &libcsel_ir::TypeB1 } } );

    return type;
}

libcsel_ir::Structure* RulePtr::create( void )
{
    static libcsel_ir::Structure* type = 0;
    if( not type )
    {
        type
            = type_factory( "RulePtr", { { "value", &libcsel_ir::TypeId },
                                           { "isdef", &libcsel_ir::TypeB1 } } );
    }
    return type;
}

libcsel_ir::Structure* Update::create( void )
{
    static libcsel_ir::Structure* type = 0;
    if( not type )
    {
        type = type_factory( "Update", { { "branded", &libcsel_ir::TypeB1 },
                                           { "location", &libcsel_ir::TypeId },
                                           { "value", &libcsel_ir::TypeB64 },
                                           { "isdef", &libcsel_ir::TypeB1 } } );
    }
    return type;
}

libcsel_ir::Memory* UpdateSet::create( void )
{
    static libcsel_ir::Memory* type = 0;
    if( not type )
    {
        type = new libcsel_ir::Memory( Update::create(), 31 );
        assert( type );
        type->getType()->bind( type );
    }
    return type;
}

libcsel_ir::Interconnect* State::create( void )
{
    static libcsel_ir::Interconnect* type = 0;
    if( not type )
    {
        type = new libcsel_ir::Interconnect();
        assert( type );
        type->getType()->bind( type );
    }
    return type;
}

/*

*/

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
