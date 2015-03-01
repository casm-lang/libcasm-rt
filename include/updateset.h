
/*
  Copyright (c) 2014 Philipp Paulweber
   
  This file is part of the 'libcasm-rt' project which is released under a NCSA
  open source software license. For more information, see the LICENSE.txt 
  file in the project root directory.
*/

#ifndef _LIB_CASM_RT_UPDATESET_H_
#define _LIB_CASM_RT_UPDATESET_H_

#include "stdll.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct casmrt_updateset;

casmrt_updateset* casmrt_updateset_new( stdll_mem* mem, uint32_t size );

uint8_t casmrt_updateset_del( casmrt_updateset* uset );

uint8_t casmrt_updateset_insert( casmrt_updateset* uset, uint64_t location, uint64_t value );

uint8_t casmrt_updateset_fork( casmrt_updateset* uset );

uint8_t casmrt_updateset_merge( casmrt_updateset* uset );

uint8_t casmrt_updateset_dump( casmrt_updateset* uset );


struct casmrt_updateset_iterator;

casmrt_updateset_iterator* casmrt_updateset_get_iterator( casmrt_updateset* uset );

uint8_t casmrt_updateset_iterator_next( casmrt_updateset_iterator* iter, uint64_t* location, uint64_t* value );




#ifdef __cplusplus   
}
#endif

#endif /* _LIB_CASM_RT_UPDATESET_H_ */

/*
  Local variables:
  mode: c++
  indent-tabs-mode: t
  c-basic-offset: 4
  tab-width: 4
  End:
  vim:noexpandtab:sw=4:ts=4:
*/
