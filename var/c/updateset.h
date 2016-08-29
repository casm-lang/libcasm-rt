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

#ifndef _LIB_CASM_RT_UPDATESET_H_
#define _LIB_CASM_RT_UPDATESET_H_

#include "casm-rt.h"

#ifdef __cplusplus
extern "C"
{
#endif

	struct libcasm_rt_updateset;

	libcasm_rt_updateset* libcasm_rt_updateset_new( stdll_mem* mem, uint32_t size );

	u8 libcasm_rt_updateset_del( libcasm_rt_updateset* uset );

	u8 libcasm_rt_updateset_insert( libcasm_rt_updateset* uset, uint64_t location, uint64_t value );

	u8 libcasm_rt_updateset_fork( libcasm_rt_updateset* uset );

	u8 libcasm_rt_updateset_merge( libcasm_rt_updateset* uset );

	u8 libcasm_rt_updateset_dump( libcasm_rt_updateset* uset );


	struct libcasm_rt_updateset_iterator;
	
	libcasm_rt_updateset_iterator* libcasm_rt_updateset_get_iterator( libcasm_rt_updateset* uset );

	u8 libcasm_rt_updateset_iterator_next( libcasm_rt_updateset_iterator* iter, uint64_t* location, uint64_t* value );

	
#ifdef __cplusplus   
}
#endif

#endif /* _LIB_CASM_RT_UPDATESET_H_ */

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
