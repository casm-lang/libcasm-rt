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

/**
   @brief    TODO

   TODO
*/

#ifndef _LIB_CASMRT_INSTRUCTION_H_
#define _LIB_CASMRT_INSTRUCTION_H_

// #include "libcasm-ir.h"
// #include "libcasm-rt.h"
// #include "libcsel-ir.h"

#include "CasmRT.h"

namespace libcasm_ir
{
    class Value;
    class Instruction;
    class CallInstruction;
    class EquInstruction;
}

namespace libcsel_ir
{
    class Value;
    class Module;
    class Instruction;
    class CallInstruction;
    class CallableUnit;
}

namespace libcasm_rt
{
    class Instruction : public CasmRT
    {
      public:
        static libcasm_ir::Value* execute( libcasm_ir::Instruction& value,
            libcsel_ir::Module* module = nullptr );

        static libcsel_ir::Value* get( libcasm_ir::Instruction& value,
            libcsel_ir::Module* module = nullptr );

        static libcsel_ir::CallInstruction* getCall(
            libcasm_ir::CallInstruction& value,
            libcsel_ir::Module* module = nullptr );

        static libcsel_ir::CallableUnit* Equ( libcasm_ir::EquInstruction& value,
            libcsel_ir::Module* module = nullptr );

        // old
        static libcsel_ir::CallableUnit* create(
            libcasm_ir::Value& value, libcsel_ir::Module* module = 0 );
    };

    template < class INSTR >
    class ArithmeticInstruction //: public CasmRT
    {
      public:
        static libcsel_ir::CallableUnit* create(
            libcasm_ir::Value& value, libcsel_ir::Module* module = 0 );
    };

    // class AddInstruction //: public CasmRT
    // {
    // public:
    //     static libcsel_ir::CallableUnit* create( libcasm_ir::AddInstruction&
    //     value, libcsel_ir::Module* module = 0 );
    // };

    // class DivInstruction //: public CasmRT
    // {
    // public:
    //     static libcsel_ir::CallableUnit* create( libcasm_ir::DivInstruction&
    //     value, libcsel_ir::Module* module = 0 );
    // };

    class EquInstruction //: public CasmRT
    {
      public:
        static libcsel_ir::CallableUnit* create(
            libcasm_ir::Value& value, libcsel_ir::Module* module = 0 );
    };
}

#endif /* _LIB_CASMRT_INSTRUCTION_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
