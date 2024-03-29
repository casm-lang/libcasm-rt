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

#include "Type.h"

#include <libstdhl/Log>

#include <libcasm-ir/Type>

// #include "../csel-ir/src/Type.h"

using namespace libcasm_rt;

// libcsel_ir::Type Type::get( const libcasm_ir::Type& type )
// {
//     return libcsel_ir::VoidType();

//     // switch( type.id() )
//     // {
//     case libcasm_ir::Type::BOOLEAN:
//     {
//         return *libcsel_ir::Type::Structure( {
//             { libcsel_ir::Type::Bit( 1 ), "value" },
//             { libcsel_ir::Type::Bit( 1 ), "isdef" },
//         } );
//     }
//     case libcasm_ir::Type::INTEGER:
//     {
//         return *libcsel_ir::Type::Structure( {
//             { libcsel_ir::Type::Bit( 64 ), "value" },
//             { libcsel_ir::Type::Bit( 1 ), "isdef" },
//         } );
//     }
//     case libcasm_ir::Type::BIT:
//     {
//         libcasm_ir::BitType& bit_ty
//             = static_cast< libcasm_ir::BitType& >( type );

//         return *libcsel_ir::Type::Structure( {
//             { libcsel_ir::Type::Bit( bit_ty.bitsize() ), "value" },
//             { libcsel_ir::Type::Bit( 1 ), "isdef" },
//         } );
//     }
// }

//     case libcasm_ir::Type::RELATION:
//     {
//         std::vector< libcsel_ir::Type* > tmp;

//         for( auto argument : type.arguments() )
//         {
//             assert( argument );
//             tmp.push_back( &get( *argument ) );
//         }

//         assert( type.result() );
//         return *libcsel_ir::Type::Relation(
//             { &get( *type.result() ) }, tmp );
//     }
//     // fall through!
//     case libcasm_ir::Type::_BOTTOM_:
//     case libcasm_ir::Type::_TOP_:
//     case libcasm_ir::Type::LABEL:
//     {
//         libstdhl::Log::error( " unsupported type transformation for
//         '%s'",
//             type.description() );
//         assert( 0 );
//     }
// }

// libstdhl::Log::error(
//     " unimplemented type transformation for '%s'", type.description() );
// assert( 0 );

// return *libcsel_ir::Type::Label();
// }

// libcsel_ir::Structure* Type::create( libcasm_ir::Value& value )
// {
//     // libcasm_ir::Type* type = value.getType()->getResult();
//     // assert( type and " invalid type pointer! " );

//     // libcasm_ir::Type::ID tid = type->getID();

//     // if( tid == libcasm_ir::Type::Boolean()->getID() )
//     // {
//     //     return Boolean::create();
//     // }
//     // else if( tid == libcasm_ir::Type::Integer()->getID() )
//     // {
//     //     return Integer::create();
//     // }
//     // else if( tid == libcasm_ir::Type::RuleReference()->getID() )
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

// libcsel_ir::Structure* String::create( libcasm_ir::StringConstant& value )
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
