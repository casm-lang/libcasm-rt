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

#ifndef _LIB_CASM_RT_INT_H_
#define _LIB_CASM_RT_INT_H_

#include "casm-rt.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
	struct libcasmrt_Int
	{
		i64 value;
		i1  isdef;
	};
	
	void libcasmrt_clr_Int( libcasmrt_Int* rt );	
	void libcasmrt_set_Int_i64( libcasmrt_Int* rt, i64 imm );
	void libcasmrt_mov_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra );
	
	void libcasmrt_add_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_sub_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_mul_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_div_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_mod_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	
	void libcasmrt_equ_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_neq_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );

	void libcasmrt_lth_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_leq_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_gth_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_geq_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	

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
