//  
//  Copyright (c) 2015 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
//  
//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal with the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//  
//  * Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimers.
//  
//  * Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimers in the 
//    documentation and/or other materials provided with the distribution.
//  
//  * Neither the names of the copyright holders, nor the names of its 
//    contributors may be used to endorse or promote products derived from 
//    this Software without specific prior written permission.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
//  WITH THE SOFTWARE.
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
