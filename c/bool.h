//  
//  Copyright (c) 2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
//  
//  This software is licensed under the Open Software License v. 3.0 (OSL-3.0).
//  You either find the license text below or in the root directory of this 
//  project in the LICENSE.txt file. If you cannot find the LICENSE.txt file,
//  please refer to https://opensource.org/licenses/OSL-3.0.
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
