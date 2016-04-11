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
