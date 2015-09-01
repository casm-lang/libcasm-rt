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

; declare %libcasm-rt.updateset* @libcasm-rt.updateset.new( %stdll.mem*, i32 )
; declare i8 @libcasm-rt.updateset.apply( %libcasm-rt.updateset* )
; declare i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* )
; declare i8 @stdll.mem.drain( %stdll.mem* %mem )



define linkonce_odr void @libcasm-rt.clr.Rule
( %libcasm-rt.Rule* %rt
) #0
{
begin:
  %pu = getelementptr %libcasm-rt.Rule* %rt, i32 0, i32 1
  store i1 false, i1* %pu
  ret void
}


define linkonce_odr void @libcasm-rt.set.Rule.ptr
( %libcasm-rt.Rule* %rt
, %libcasm-rt.RuleAddr %ptr
) #0
{
begin:
  %pv = getelementptr %libcasm-rt.Rule* %rt, i32 0, i32 0
  %pu = getelementptr %libcasm-rt.Rule* %rt, i32 0, i32 1
  
  store %libcasm-rt.RuleAddr %ptr, %libcasm-rt.RuleAddr* %pv
  store i1  true, i1*  %pu
  
  ret void
}






@program = global %libcasm-rt.Rule zeroinitializer
define i8* @program.location( i8* %agent )
{
begin:
  %ptr = getelementptr %libcasm-rt.Rule* @program, i64 0
  %loc = bitcast %libcasm-rt.Rule* %ptr to i8*
  ret i8* %loc
}



define void @libcasm-rt.main( %stdll.mem* %mem )
{
loop:
  
  %.program = call i8* @program.location( i8* null )
  %.prog = bitcast i8* %.program to %libcasm-rt.Rule*
  %.rule = getelementptr %libcasm-rt.Rule* %.prog, i32 0, i32 0
  %.rdef = getelementptr %libcasm-rt.Rule* %.prog, i32 0, i32 1
  %rule = load void( %libcasm-rt.updateset* )** %.rule
  %rdef = load i1* %.rdef
;  br i1 %rdef, label %run, label %endloop
;run:

  %uset = call %libcasm-rt.updateset* @libcasm-rt.updateset.new( %stdll.mem* %mem, i32 100 )
  call void %rule( %libcasm-rt.updateset* %uset )
  call i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
  call i8 @libcasm-rt.updateset.apply( %libcasm-rt.updateset* %uset )
  
  call i8 @stdll.mem.drain( %stdll.mem* %mem )
;  br label %loop
;   ; %.x = call i8* @x.location()
;   ; %.y = call i8* @y.location()
;   ; %.z = call i8* @z.location()
  
;   ; %x = bitcast i8* %.x to %libcasm-rt.Int*
;   ; %y = bitcast i8* %.y to %libcasm-rt.Int*
;   ; %z = bitcast i8* %.z to %libcasm-rt.Int*
  
;   ; call void @libcasm-rt.dump.Int( %libcasm-rt.Int* %x )
;   ; call void @libcasm-rt.dump.Int( %libcasm-rt.Int* %y )
;   ; call void @libcasm-rt.dump.Int( %libcasm-rt.Int* %z )
  
;endloop:
  ret void
}



