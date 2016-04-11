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

#include "gtest/gtest.h"
#include "casm-rt.h"

static stdll_mem mem;


TEST( update, prolog )
{
	// create a 32 MB memory pool
	ASSERT_EQ( 0, stdll_mem_new( &mem, 1024*1024*32 ) );
}

TEST( update, new )
{
	libcasm_rt_update* u = 0;
	
	ASSERT_NE( (void*)0, u = libcasm_rt_update_new( &mem, 123, 1 ) );
	ASSERT_EQ( u->value, 123 );	
	ASSERT_EQ( u->isdef, 1 );
}

TEST( update, epilog )
{
	ASSERT_EQ( 0, stdll_mem_del( &mem ) );	
}



//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
