;;  
;;  Copyright (c) 2015 Philipp Paulweber
;;  All rights reserved.
;;  
;;  Developed by: Philipp Paulweber
;;                https://github.com/ppaulweber/libcasm-rt
;;  
;;  Permission is hereby granted, free of charge, to any person obtaining a 
;;  copy of this software and associated documentation files (the "Software"), 
;;  to deal with the Software without restriction, including without limitation 
;;  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
;;  and/or sell copies of the Software, and to permit persons to whom the 
;;  Software is furnished to do so, subject to the following conditions:
;;  
;;  * Redistributions of source code must retain the above copyright 
;;    notice, this list of conditions and the following disclaimers.
;;  
;;  * Redistributions in binary form must reproduce the above copyright 
;;    notice, this list of conditions and the following disclaimers in the 
;;    documentation and/or other materials provided with the distribution.
;;  
;;  * Neither the names of the copyright holders, nor the names of its 
;;    contributors may be used to endorse or promote products derived from 
;;    this Software without specific prior written permission.
;;  
;;  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
;;  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
;;  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
;;  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
;;  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
;;  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
;;  WITH THE SOFTWARE.
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







