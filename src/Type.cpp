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

#include "Type.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/Log.h"

#include "../casm-ir/src/Type.h"

#include "../csel-ir/src/Structure.h"
#include "../csel-ir/src/Type.h"

using namespace libcasm_rt;

static libcsel_ir::Type::Ptr boolean = nullptr;
static libcsel_ir::Type::Ptr integer = nullptr;
static libcsel_ir::Type::Ptr bit = nullptr;

libcsel_ir::Type::Ptr Type::get( const libcasm_ir::Type& type )
{
    switch( type.id() )
    {
        case libcasm_ir::Type::BOOLEAN:
        {
            if( not boolean )
            {
                boolean = libstdhl::get< libcsel_ir::StructureType >(
                    libstdhl::get< libcsel_ir::Structure >(
                        "casm_rt__" + type.name(),
                        std::initializer_list< libcsel_ir::StructureElement >{
                            { libstdhl::get< libcsel_ir::BitType >( 1 ),
                                "value" },
                            { libstdhl::get< libcsel_ir::BitType >( 1 ),
                                "isdef" } } ) );
            }
            return boolean;
        }
        case libcasm_ir::Type::INTEGER:
        {
            if( not integer )
            {
                integer = libstdhl::get< libcsel_ir::StructureType >(
                    libstdhl::get< libcsel_ir::Structure >(
                        "casm_rt__" + type.name(),
                        std::initializer_list< libcsel_ir::StructureElement >{
                            { libstdhl::get< libcsel_ir::BitType >( 64 ),
                                "value" },
                            { libstdhl::get< libcsel_ir::BitType >( 1 ),
                                "isdef" } } ) );
            }
            return integer;
        }
        case libcasm_ir::Type::BIT:
        {
            const auto btype
                = static_cast< const libcasm_ir::BitType& >( type );

            return libstdhl::get< libcsel_ir::StructureType >(
                libstdhl::get< libcsel_ir::Structure >(
                    "casm_rt__" + btype.name(),
                    std::initializer_list< libcsel_ir::StructureElement >{
                        { libstdhl::get< libcsel_ir::BitType >(
                              btype.bitsize() ),
                            "value" },
                        { libstdhl::get< libcsel_ir::BitType >( 1 ),
                            "isdef" } } ) );
        }
        case libcasm_ir::Type::RELATION:
        {
            std::vector< libcsel_ir::Type::Ptr > arguments;
            for( const auto& argument : type.arguments() )
            {
                arguments.push_back( get( *argument.get() ) );
            }

            const std::vector< libcsel_ir::Type::Ptr > results
                = { get( type.result() ) };

            return libstdhl::get< libcsel_ir::RelationType >(
                results, arguments );
        }
        // fall through!
        case libcasm_ir::Type::_BOTTOM_:
        case libcasm_ir::Type::_TOP_:
        case libcasm_ir::Type::LABEL:
        {
            libstdhl::Log::error( " unsupported type transformation for '%s'",
                type.description().c_str() );
            assert( 0 );
        }
    }

    libstdhl::Log::error( " unimplemented type transformation for '%s'",
        type.description().c_str() );
    assert( 0 );

    return libstdhl::get< libcsel_ir::VoidType >();
}

// libcsel_ir::Structure* Type::create( Value& value )
// {
//     // Type* type = value.getType()->getResult();
//     // assert( type and " invalid type pointer! " );

//     // Type::ID tid = type->getID();

//     // if( tid == Type::Boolean()->getID() )
//     // {
//     //     return Boolean::create();
//     // }
//     // else if( tid == Type::Integer()->getID() )
//     // {
//     //     return Integer::create();
//     // }
//     // else if( tid == Type::RuleReference()->getID() )
//     // {
//     //     return RulePtr::create();
//     // }
//     // else
//     {
//         assert( !" unsupported/unimplemented type id! " );
//         return 0;
//     }
// }

// struct type_factory_argument
// {
//     const char* name;
//     libcsel_ir::Type* type;
// };

// static libcsel_ir::Structure* type_factory( const std::string& name,
//     const std::vector< struct type_factory_argument >& args )
// {
//     libcsel_ir::Structure* type = new libcsel_ir::Structure(
//         libstdhl::Allocator::string( name.c_str() ) );
//     assert( type );
//     type->getType()->bind( type );

//     for( u32 c = 0; c < args.size(); c++ )
//     {
//         libcsel_ir::Structure* arg
//             = new libcsel_ir::Structure( args[ c ].name, args[ c ].type, type
//             );
//         assert( arg );
//     }

//     return type;
// }

// libcsel_ir::Structure* Boolean::create( void )
// {
//     static libcsel_ir::Structure* type = 0;
//     if( not type )
//     {
//         type
//             = type_factory( "Boolean", { { "value", &libcsel_ir::TypeB1 },
//                                            { "isdef", &libcsel_ir::TypeB1 } }
//                                            );
//     }
//     return type;
// }

// libcsel_ir::Structure* Integer::create( void )
// {
//     static libcsel_ir::Structure* type = 0;
//     if( not type )
//     {
//         type
//             = type_factory( "Integer", { { "value", &libcsel_ir::TypeB64 },
//                                            { "isdef", &libcsel_ir::TypeB1 } }
//                                            );
//     }
//     return type;
// }

// libcsel_ir::Structure* String::create( StringConstant& value )
// {
//     static std::unordered_map< i16, libcsel_ir::Structure* > cache;

//     i16 length = 0;
//     if( value.getValue() )
//     {
//         length = strlen( value.getValue() );
//     }

//     if( cache.count( length ) > 0 )
//     {
//         return cache[ length ];
//     }

//     libcsel_ir::Structure* type = type_factory(
//         libstdhl::Allocator::string(
//             std::string( "String" + std::to_string( length ) ) ),
//         { { "value", new libcsel_ir::Type( libcsel_ir::Type::STRING, length,
//                          libcsel_ir::Type::STATE::LOCKED ) },
//             { "isdef", &libcsel_ir::TypeB1 } } );

//     return type;
// }

// libcsel_ir::Structure* RulePtr::create( void )
// {
//     static libcsel_ir::Structure* type = 0;
//     if( not type )
//     {
//         type
//             = type_factory( "RulePtr", { { "value", &libcsel_ir::TypeId },
//                                            { "isdef", &libcsel_ir::TypeB1 } }
//                                            );
//     }
//     return type;
// }

// libcsel_ir::Structure* Update::create( void )
// {
//     static libcsel_ir::Structure* type = 0;
//     if( not type )
//     {
//         type = type_factory( "Update", { { "branded", &libcsel_ir::TypeB1 },
//                                            { "location", &libcsel_ir::TypeId
//                                            },
//                                            { "value", &libcsel_ir::TypeB64 },
//                                            { "isdef", &libcsel_ir::TypeB1 } }
//                                            );
//     }
//     return type;
// }

// libcsel_ir::Memory* UpdateSet::create( void )
// {
//     static libcsel_ir::Memory* type = 0;
//     if( not type )
//     {
//         type = new libcsel_ir::Memory( Update::create(), 31 );
//         assert( type );
//         type->getType()->bind( type );
//     }
//     return type;
// }

// libcsel_ir::Interconnect* State::create( void )
// {
//     static libcsel_ir::Interconnect* type = 0;
//     if( not type )
//     {
//         type = new libcsel_ir::Interconnect();
//         assert( type );
//         type->getType()->bind( type );
//     }
//     return type;
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
