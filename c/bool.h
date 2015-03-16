
/*
  Copyright (c) 2015 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#ifndef _LIB_CASM_RT_BOOL_H_
#define _LIB_CASM_RT_BOOL_H_

#include "stdll/c/stdll.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct libcasmrt_Bool
    {
        u1 value;
        u1 isdef;
    };
    
    void libcasmrt_clr_Bool( libcasmrt_Bool* rt );	
    void libcasmrt_set_Bool_i64( libcasmrt_Bool* rt, i64 imm );
    void libcasmrt_mov_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra );
    
    void libcasmrt_not_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra );
    void libcasmrt_and_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
    void libcasmrt_or_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
    void libcasmrt_xor_Bool_Bool_Bool( libcasmrt_Bool* rt, libcasmrt_Bool* ra, libcasmrt_Bool* rb );
    
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
