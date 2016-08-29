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
