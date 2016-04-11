;;  
;;  Copyright (c) 2016 Philipp Paulweber
;;  All rights reserved.
;;  
;;  Developed by: Philipp Paulweber
;;                https://github.com/ppaulweber/libcasm-rt
;;  
;;  This software is licensed under the Open Software License v. 3.0 (OSL-3.0).
;;  You either find the license text below or in the root directory of this 
;;  project in the LICENSE.txt file. If you cannot find the LICENSE.txt file,
;;  please refer to https://opensource.org/licenses/OSL-3.0.
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







