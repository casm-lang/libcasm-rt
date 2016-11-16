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

/**
   @brief    TODO
   
   TODO
*/

#ifndef _LIB_CASMRT_UPDATE_H_
#define _LIB_CASMRT_UPDATE_H_

#include "libcasm-rt.h"
#include "libcasm-ir.h"
#include "libnovel.h"


namespace libcasm_rt
{
    class HashImplementation //: public CasmRT
    {
    public:
        static libnovel::CallableUnit* create( void );
    };
	
    class UpdateImplementation //: public CasmRT
    {
    public:
        static libnovel::CallableUnit* create( libcasm_ir::UpdateInstruction& value, libnovel::Module* module = 0 );
    };
	
    class LookupImplementation //: public CasmRT
    {
    public:
        static libnovel::CallableUnit* create( libcasm_ir::LookupInstruction& value, libnovel::Module* module = 0 );
    };
	
	class FunctionState
    {
    public:
        static libnovel::Variable* create( libcasm_ir::Function& value );
    };

	class FunctionLocation
    {
    public:
        static libnovel::CallableUnit* create( libcasm_ir::Function& value );
    };
		
	class ProgramFunctionState
    {
    public:
        static libnovel::Variable* create( libnovel::Variable* value = 0 );
    };

	class ProgramRuleSignature
    {
    public:
        static libnovel::CallableUnit* create( void );
    };
	
}

#endif /* _LIB_CASMRT_UPDATE_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
