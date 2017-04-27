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

#include "../casm-ir/src/Builtin.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Intrinsic.h"
#include "../csel-ir/src/Module.h"
#include "../csel-ir/src/Scope.h"
#include "../csel-ir/src/Statement.h"

using namespace libcasm_rt;

libcsel_ir::CallableUnit::Ptr Builtin::asBoolean(
    const libcasm_ir::AsBooleanBuiltin& value, libcsel_ir::Module* context )
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
    assert( ir_ty.isRelation() and ir_ty.arguments().size() == 1 );

    auto el_ty = libcasm_rt::Type::get( ir_ty );

    assert( el_ty->isRelation() and el_ty->arguments().size() == 1
            and el_ty->results().size() == 1 );

    auto implementation = libstdhl::make< libcsel_ir::Intrinsic >( value.name(),
        std::static_pointer_cast< libcsel_ir::RelationType >(
            el_ty ) ); // PPA: TODO: add 'el' to context

    assert( implementation );

    auto arg = implementation->in( "arg", el_ty->arguments()[ 0 ] );
    auto ret = implementation->out( "ret", el_ty->results()[ 0 ] );

    auto scope = libstdhl::make< libcsel_ir::ParallelScope >();
    implementation->setContext( scope );

    auto stmt = libstdhl::make< libcsel_ir::TrivialStatement >();
    stmt->setParent( scope );
    scope->add( stmt );

    auto idx0 = libstdhl::get< libcsel_ir::BitConstant >( 8, 0 );
    auto idx1 = libstdhl::get< libcsel_ir::BitConstant >( 8, 1 );

    auto arg_v_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( arg, idx0 ) );
    auto arg_d_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( arg, idx1 ) );

    auto ret_v_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( ret, idx0 ) );
    auto ret_d_ptr = stmt->add(
        libstdhl::make< libcsel_ir::ExtractInstruction >( ret, idx1 ) );

    auto arg_v = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( arg_v_ptr ) );
    auto arg_d = stmt->add(
        libstdhl::make< libcsel_ir::LoadInstruction >( arg_d_ptr ) );

    assert( arg_v->type().isBit() );

    auto zero = libstdhl::get< libcsel_ir::BitConstant >(
        std::static_pointer_cast< libcsel_ir::BitType >( arg_v->ptr_type() ),
        0 );

    auto reg_v = stmt->add(
        libstdhl::make< libcsel_ir::NeqInstruction >( arg_v, zero ) );

    stmt->add(
        libstdhl::make< libcsel_ir::StoreInstruction >( reg_v, ret_v_ptr ) );
    stmt->add(
        libstdhl::make< libcsel_ir::StoreInstruction >( arg_d, ret_d_ptr ) );

    cache[ key ] = implementation;
    return implementation;
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
