;;  
;;  Copyright (c) 2016 Philipp Paulweber
;;  All rights reserved.
;;  
;;  Developed by: Philipp Paulweber
;;                https://github.com/ppaulweber/libcasm-rt
;;  
;;  This program is free software: you can redistribute it and/or modify
;;  it under the terms of the GNU General Public License as published by
;;  the Free Software Foundation, either version 3 of the License, or
;;  (at your option) any later version.
;;  
;;  This program is distributed in the hope that it will be useful,
;;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;  GNU General Public License for more details.
;;  
;;  You should have received a copy of the GNU General Public License
;;  along with this program. If not, see <http://www.gnu.org/licenses/>.
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
