//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
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

#ifndef _LIB_CASM_RT_BOOL_H_
#define _LIB_CASM_RT_BOOL_H_

#include "casm-rt.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    struct libcasmrt_Bool
    {
        i1 value;
        i1 isdef;
    };
    
    void libcasmrt_clr_Bool( libcasmrt_Bool* rt );	
    void libcasmrt_set_Bool_i1( libcasmrt_Bool* rt, i1 imm );
    void libcasmrt_mov_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra );
    
    void libcasmrt_not_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra );
    void libcasmrt_and_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
    void libcasmrt_or_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
    void libcasmrt_xor_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
    
    void libcasmrt_equ_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
    void libcasmrt_neq_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
        
#ifdef __cplusplus   
}
#endif

#endif /* _LIB_CASM_RT_INT_H_ */

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  