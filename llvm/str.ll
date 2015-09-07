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


@libcasm-rt.Str.undef  = internal constant [5 x i8] c"undef"
;@libcasm-rt.Str.Bool   = internal constant [4 x i8] c"%u"
@libcasm-rt.Str.Int    = internal constant [4 x i8] c"%lli"
;@libcasm-rt.Str.Str    = internal constant [2 x i8] c"%s"
;@libcasm-rt.Str.Str

define linkonce_odr void @libcasm-rt.print.Str
( %libcasm-rt.Str* %rt
) #0
{
begin:
  %pv = getelementptr %libcasm-rt.Str* %rt, i32 0, i32 0
  %pu = getelementptr %libcasm-rt.Str* %rt, i32 0, i32 1
  %u = load i1*  %pu
  br i1 %u, label %print_value, label %print_undef

print_value:
  %v = load i8** %pv
  ;%fmt_v = getelementptr inbounds [2 x i8]* @libcasm-rt.Str.Str, i32 0, i32 0  
  call i32 (i8*, ...)* @printf( i8* %v )
  ret void

print_undef:
  %fmt = getelementptr inbounds [5 x i8]* @libcasm-rt.Str.undef, i32 0, i32 0  
  call i32 (i8*, ...)* @printf( i8* %fmt )
  ret void
}


define linkonce_odr void @libcasm-rt.print.Int
( %libcasm-rt.Int* %rt
) #0
{
begin:
  %pv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  %u = load i1*  %pu
  br i1 %u, label %print_value, label %print_undef

print_value:
  %v = load i64* %pv
  %fmt_v = getelementptr inbounds [4 x i8]* @libcasm-rt.Str.Int, i32 0, i32 0  
  call i32 (i8*, ...)* @printf( i8* %fmt_v, i64 %v )
  ret void

print_undef:
  %fmt = getelementptr inbounds [5 x i8]* @libcasm-rt.Str.undef, i32 0, i32 0  
  call i32 (i8*, ...)* @printf( i8* %fmt )
  ret void
}
