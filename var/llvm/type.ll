;;  
;;  Copyright (c) 2014-2016 CASM Organization
;;  All rights reserved.
;;  
;;  Developed by: Philipp Paulweber
;;                https://github.com/casm-lang/libcasm-rt
;;  
;;  This file is part of libcasm-rt.
;;  
;;  libcasm-rt is free software: you can redistribute it and/or modify
;;  it under the terms of the GNU General Public License as published by
;;  the Free Software Foundation, either version 3 of the License, or
;;  (at your option) any later version.
;;  
;;  libcasm-rt is distributed in the hope that it will be useful,
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;;  GNU General Public License for more details.
;;  
;;  You should have received a copy of the GNU General Public License
;;  along with libcasm-rt. If not, see <http://www.gnu.org/licenses/>.
;;  

; update
%struct.libcasm_rt_update = type %libcasm-rt.update
%libcasm-rt.update = type
 { i64 ; 0 value
 , i1  ; 1 isdef
 }


; updateset
%struct.libcasm_rt_updateset  = type %libcasm-rt.updateset
%libcasm-rt.updateset = type
 { %stdll.dict*   ; 0 update set
 , i16            ; 1 pseudo state
 }



; Agent
%struct.libcasmrt_Agent  = type %libcasm-rt.Agent
%libcasm-rt.Agent = type
 { i8*
 , i1
 }

; RulePointer
%libcasm-rt.RuleAddr = type void( %libcasm-rt.updateset* )*
%struct.libcasmrt_Rule  = type %libcasm-rt.Rule
%libcasm-rt.Rule = type
 { %libcasm-rt.RuleAddr
 , i1
 }


; Boolean
%struct.libcasmrt_Bool  = type %libcasm-rt.Bool
%libcasm-rt.Bool = type
 { i1  ; 0 value
 , i1  ; 1 isdef
 }


; Integer
%struct.libcasmrt_Int  = type %libcasm-rt.Int
%libcasm-rt.Int = type
 { i64 ; 0 value
 , i1  ; 1 isdef
 }



; String
%struct.libcasmrt_Str  = type %libcasm-rt.Str
%libcasm-rt.Str = type
 { i8* ; 0 value
 , i1  ; 1 isdef
 }







