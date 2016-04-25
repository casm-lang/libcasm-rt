//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-rt
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

/**
   @brief    TODO
   
   TODO
*/

#ifndef _LIB_CASMRT_TYPE_H_
#define _LIB_CASMRT_TYPE_H_

#include "libcasm-rt.h"
#include "libcasm-ir.h"
#include "libnovel.h"


namespace libcasm_rt
{
	class Type //: public CasmRT
	{
	public:
		static libnovel::Structure* create( libcasm_ir::Type& type );
	};
	
	
	class Integer : public Type
	{
    public:
		static libnovel::Structure* create( void );
	};
	
	class RulePtr : public Type
	{
    public:
		static libnovel::Structure* create( void );
	};






	class Update : public Type
	{
    public:
		static libnovel::Structure* create( void );
	};
	
	
	class UpdateSet : public Type
	{
    public:
		static libnovel::Memory* create( void );
	};
}

#endif /* _LIB_CASMRT_TYPE_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
