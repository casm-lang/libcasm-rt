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
#include "../casm-ir/src/Value.h"

#include "../csel-ir/src/CallableUnit.h"
#include "../csel-ir/src/Instruction.h"
#include "../csel-ir/src/Intrinsic.h"
#include "../csel-ir/src/Reference.h"
#include "../csel-ir/src/Scope.h"
#include "../csel-ir/src/Statement.h"

using namespace libcasm_rt;

static inline libcasm_ir::Constant evaluate_through_instr_call(
    const libcasm_ir::Builtin& builtin, const Builtin::Arguments& operands )
{
    std::vector< libcasm_ir::Value::Ptr > arguments;
    for( auto operand : operands )
    {
        arguments.emplace_back( libstdhl::wrap( (libcasm_ir::Value&)operand ) );
    }

    const auto symbol = libstdhl::wrap( (libcasm_ir::Value&)builtin );
    libcasm_ir::CallInstruction instr( symbol, arguments );

    return Instruction::execute( instr );
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AbortBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AssertBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::PrintBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::PrintLnBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsBooleanBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsIntegerBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::AsBitBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsStringBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsFloatingBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsRationalBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AsEnumerationBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::DecBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::HexBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::OctBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::BinBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AdduBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AddsBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::SubuBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::SubsBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::MuluBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::MulsBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::LesuBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::LessBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::LequBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::LeqsBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::GreuBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::GresBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::GequBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::GeqsBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::ZextBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::SextBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute( const libcasm_ir::TruncBuiltin& builtin,
    const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::ShlBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::ShrBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::AshrBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::ClzBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::CloBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

libcasm_ir::Constant Builtin::execute(
    const libcasm_ir::ClsBuiltin& builtin, const Builtin::Arguments& operands )
{
    return libcasm_ir::VoidConstant();
}

// libcasm_ir::Constant Builtin::execute( const libcasm_ir::PowBuiltin& builtin,
// const Builtin::Arguments& operands )
// {
// }

// libcasm_ir::Constant Builtin::execute( const libcasm_ir::RandBuiltin&
// builtin, const Builtin::Arguments& operands )
// {
// }

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

// libcsel_ir::CallableUnit* Builtin::asBoolean(
//     libcasm_ir::Value& value, libcsel_ir::Module* context )
// {
//     static std::unordered_map< std::string, libcsel_ir::CallableUnit* >
//     cache;

//     libstdhl::Log::info( "%s: %s %s",
//         __FUNCTION__,
//         value.name().c_str(),
//         value.type().description().c_str() );

//     std::string key = "";
//     key += value.name();
//     key += " ";
//     key += value.type().name();

//     auto result = cache.find( key );
//     if( result != cache.end() )
//     {
//         return result->second;
//     }

//     const auto& ir_ty = value.type();
//     assert( ir_ty.isRelation() and ir_ty.arguments().size() == 1 );

//     auto el_ty = libcasm_rt::Type::get( ir_ty );
//     assert( el_ty.isRelation() and el_ty.arguments().size() == 1
//             and el_ty.results().size() == 1 );

//     auto instr = libcasm_ir::cast< libcasm_ir::AsBooleanBuiltin >( value );

//     return 0;

// auto el = new libcsel_ir::Intrinsic(
//     instr->label(), &el_ty ); // PPA: TODO: add 'el' to context
// assert( el );

// auto arg = el->in( "arg", el_ty.arguments()[ 0 ] );
// auto ret = el->out( "ret", el_ty.results()[ 0 ] );

// libcsel_ir::Scope* scope = new libcsel_ir::ParallelScope( el );
// libcsel_ir::Statement* stmt = new libcsel_ir::TrivialStatement( scope );

// auto idx0 = new libcsel_ir::BitConstant( 8, 0 );
// auto idx1 = new libcsel_ir::BitConstant( 8, 1 );

// auto arg_v_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx0 ) );
// auto arg_d_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( arg, idx1 ) );

// auto ret_v_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx0 ) );
// auto ret_d_ptr
//     = stmt->add( new libcsel_ir::ExtractInstruction( ret, idx1 ) );

// auto arg_v = stmt->add( new libcsel_ir::LoadInstruction( arg_v_ptr ) );
// auto arg_d = stmt->add( new libcsel_ir::LoadInstruction( arg_d_ptr ) );

// auto reg_v = stmt->add( new libcsel_ir::NeqInstruction(
//     arg_v, new libcsel_ir::BitConstant( &arg_v->type(), 0 ) ) );

// stmt->add( new libcsel_ir::StoreInstruction( reg_v, ret_v_ptr ) );
// stmt->add( new libcsel_ir::StoreInstruction( arg_d, ret_d_ptr ) );

// cache[ key ] = el;
// return el;
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
