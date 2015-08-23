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


; C wrapper
%struct.libcasmrt_Bool  = type %libcasm-rt.Bool

@libcasmrt_clr_Bool           = alias void( %libcasm-rt.Bool* )*
                                @libcasm-rt.clr.Bool
@libcasmrt_set_Bool_i1        = alias void( %libcasm-rt.Bool*, i1 )*
                                @libcasm-rt.set.Bool.i1
@libcasmrt_mov_Bool_Bool      = alias
                                void( %libcasm-rt.Bool*, %libcasm-rt.Bool* )*
                                @libcasm-rt.mov.Bool.Bool
@libcasmrt_not_Bool_Bool      = alias
                                void( %libcasm-rt.Bool*, %libcasm-rt.Bool* )*
                                @libcasm-rt.not.Bool.Bool
@libcasmrt_and_Bool_Bool_Bool = alias
                                void( %libcasm-rt.Bool*, %libcasm-rt.Bool*, %libcasm-rt.Bool* )*
                                @libcasm-rt.and.Bool.Bool.Bool
@libcasmrt_or_Bool_Bool_Bool  = alias
                                void( %libcasm-rt.Bool*, %libcasm-rt.Bool*, %libcasm-rt.Bool* )*
                                @libcasm-rt.or.Bool.Bool.Bool
@libcasmrt_xor_Bool_Bool_Bool = alias
                                void( %libcasm-rt.Bool*, %libcasm-rt.Bool*, %libcasm-rt.Bool* )*
                                @libcasm-rt.xor.Bool.Bool.Bool
@libcasmrt_equ_Bool_Bool_Bool = alias
                                void( %libcasm-rt.Bool*, %libcasm-rt.Bool*, %libcasm-rt.Bool* )*
                                @libcasm-rt.equ.Bool.Bool.Bool
@libcasmrt_neq_Bool_Bool_Bool = alias
                                void( %libcasm-rt.Bool*, %libcasm-rt.Bool*, %libcasm-rt.Bool* )*
                                @libcasm-rt.neq.Bool.Bool.Bool


%libcasm-rt.Bool = type
<{ i1  ; 0 value
 , i1  ; 1 isdef
 }>


define linkonce_odr void @libcasm-rt.clr.Bool
( %libcasm-rt.Bool* %rt
) #0
{
begin:
  %pu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  
  store i1 false, i1* %pu
  
  ret void
}


define linkonce_odr void @libcasm-rt.set.Bool.i1
( %libcasm-rt.Bool* %rt
, i1 %imm
) #0
{
begin:
  %pv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
      
  store i1 %imm, i1* %pv
  store i1 true, i1* %pu
  
  ret void
}


define linkonce_odr void @libcasm-rt.mov.Bool.Bool
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Bool* %ra
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 1
  
  %av  = load i1* %pav
  %au  = load i1* %pau
  
  store i1 %av, i1* %ptv
  store i1 %au, i1* %ptu
  
  ret void
}


define linkonce_odr void @libcasm-rt.not.Bool.Bool
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Bool* %ra
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 1
  
  %av  = load i1* %pav
  %au  = load i1* %pau
  
  %tv  = xor i1 %av, true
  
  store i1 %tv, i1* %ptv
  store i1 %au, i1* %ptu
  
  ret void
}


define linkonce_odr void @libcasm-rt.and.Bool.Bool.Bool
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Bool* %ra
, %libcasm-rt.Bool* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Bool* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Bool* %rb, i32 0, i32 1
  
  %av  = load i1* %pav
  %bv  = load i1* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = and i1 %av, %bv
  %tu  = and i1 %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define linkonce_odr void @libcasm-rt.or.Bool.Bool.Bool
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Bool* %ra
, %libcasm-rt.Bool* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Bool* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Bool* %rb, i32 0, i32 1
  
  %av  = load i1* %pav
  %bv  = load i1* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = or  i1 %av, %bv
  %tu  = and i1 %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define linkonce_odr void @libcasm-rt.xor.Bool.Bool.Bool
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Bool* %ra
, %libcasm-rt.Bool* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Bool* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Bool* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Bool* %rb, i32 0, i32 1
  
  %av  = load i1* %pav
  %bv  = load i1* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = xor i1 %av, %bv
  %tu  = and i1 %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define linkonce_odr void @libcasm-rt.equ.Bool.Bool.Bool
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Bool* %ra
, %libcasm-rt.Bool* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Bool*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Bool*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Bool*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Bool*  %rb, i32 0, i32 1
  
  %av  = load i1* %pav
  %bv  = load i1* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  store i1 true, i1* %ptu
  
  %c = and i1 %au, %bu
  br i1 %c, label %number_number, label %other
  
number_number:
  %tv_n = icmp eq i1 %av, %bv
  store i1 %tv_n, i1* %ptv
  ret void

other:
  %tvt  = xor i1 %au, %bu
  %tv_o = xor i1 %tvt, true
  store i1 %tv_o, i1* %ptv
  ret void
}


define linkonce_odr void @libcasm-rt.neq.Bool.Bool.Bool
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Bool* %ra
, %libcasm-rt.Bool* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Bool*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Bool*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Bool*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Bool*  %rb, i32 0, i32 1
  
  %av  = load i1* %pav
  %bv  = load i1* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  store i1 true, i1* %ptu
    
  %c = and i1 %au, %bu
  br i1 %c, label %number_number, label %other
  
number_number:
  %tv_n = icmp ne i1 %av, %bv
  store i1 %tv_n, i1* %ptv
  ret void

other:
  %tv_o = xor i1 %au, %bu
  store i1 %tv_o, i1* %ptv
  ret void
}

attributes #0 = { alwaysinline nounwind }

