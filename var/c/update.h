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

#ifndef _LIB_CASM_RT_UPDATE_H_
#define _LIB_CASM_RT_UPDATE_H_

#include "casm-rt.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct libcasm_rt_update
    {
        i64 value;
        i1  isdef;
    };
    
    libcasm_rt_update* libcasm_rt_update_new( stdll_mem* mem, u64 value, u1 defined );
    
#ifdef __cplusplus   
}
#endif

#endif /* _LIB_CASM_RT_UPDATE_H_ */

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
