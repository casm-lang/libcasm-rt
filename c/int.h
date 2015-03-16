
/*
  Copyright (c) 2015 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#ifndef _LIB_CASM_RT_INT_H_
#define _LIB_CASM_RT_INT_H_

#include "stdll/c/stdll.h"

#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

	// struct libcasmrt_Bool
	// {
	// 	u1 value;
	// 	u1 isdef;
	// };
	
	struct libcasmrt_Int
	{
		i64 value;
		u1  isdef;
	};

	void libcasmrt_clr_Int( libcasmrt_Int* rt );	
	void libcasmrt_set_Int_i64( libcasmrt_Int* rt, i64 imm );
	void libcasmrt_mov_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra );
	
	void libcasmrt_add_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_sub_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_mul_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_div_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_rem_Int_Int_Int( libcasmrt_Int* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );

	void libcasmrt_lth_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_leq_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_gth_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_geq_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_equ_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	void libcasmrt_neq_Bool_Int_Int( libcasmrt_Bool* rt, libcasmrt_Int* ra, libcasmrt_Int* rb );
	

#ifdef __cplusplus   
}
#endif

#endif /* _LIB_CASM_RT_INT_H_ */

/*
  Local variables:
  mode: c++
  indent-tabs-mode: t
  c-basic-offset: 4
  tab-width: 4
  End:
  vim:noexpandtab:sw=4:ts=4:
*/
