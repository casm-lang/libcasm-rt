;;
;;  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
;;  All rights reserved.
;;
;;  Developed by: Philipp Paulweber
;;                <https://github.com/casm-lang/libcasm-rt>
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
;;  Additional permission under GNU GPL version 3 section 7
;;
;;  libcasm-rt is distributed under the terms of the GNU General Public License
;;  with the following clarification and special exception: Linking libcasm-rt
;;  statically or dynamically with other modules is making a combined work
;;  based on libcasm-rt. Thus, the terms and conditions of the GNU General
;;  Public License cover the whole combination. As a special exception,
;;  the copyright holders of libcasm-rt give you permission to link libcasm-rt
;;  with independent modules to produce an executable, regardless of the
;;  license terms of these independent modules, and to copy and distribute
;;  the resulting executable under terms of your choice, provided that you
;;  also meet, for each linked independent module, the terms and conditions
;;  of the license of that module. An independent module is a module which
;;  is not derived from or based on libcasm-rt. If you modify libcasm-rt, you
;;  may extend this exception to your version of the library, but you are
;;  not obliged to do so. If you do not wish to do so, delete this exception
;;  statement from your version.
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
define linkonce_odr i8* @program.location( i8* %agent )
#0
{
begin:
  %ptr = getelementptr %libcasm-rt.Rule* @program, i64 0
  %loc = bitcast %libcasm-rt.Rule* %ptr to i8*
  ret i8* %loc
}

declare void @llvm.lifetime.start( i64 %size, i8* nocapture %ptr )
declare void @llvm.lifetime.end( i64 %size, i8* nocapture %ptr )
declare {}* @llvm.invariant.start( i64 %size, i8* nocapture %ptr )
declare void @llvm.invariant.end( {}* %start, i64 %size, i8* nocapture %ptr )


@fmt_steps = internal constant [20 x i8] c"%i steps later...\0d\0a\00"
@fmt_step  = internal constant [19 x i8] c"%i step later...\0d\0a\00"

define linkonce_odr void @libcasm-rt.main( %stdll.mem* %mem )
#0
{
begin:
  %.program = call i8* @program.location( i8* null )
  %.prog = bitcast i8* %.program to %libcasm-rt.Rule*
  %.rule = getelementptr %libcasm-rt.Rule* %.prog, i32 0, i32 0
  %.rdef = getelementptr %libcasm-rt.Rule* %.prog, i32 0, i32 1
  br label %loop
  
loop:
  %old_step = phi i64 [ 0, %begin ], [ %step, %execute ]
  
  %rule = load void( %libcasm-rt.updateset* )** %.rule
  %rdef = load i1* %.rdef
  br i1 %rdef, label %execute, label %return

execute:
  %uset = call %libcasm-rt.updateset* @libcasm-rt.updateset.new( %stdll.mem* %mem, i32 100 )
  call void %rule( %libcasm-rt.updateset* %uset )
  ; call void @stdll.verbose.ln()
  ; call i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
  call i8 @libcasm-rt.updateset.apply( %libcasm-rt.updateset* %uset )
  call i8 @stdll.mem.drain( %stdll.mem* %mem )
  %step = add nsw i64 %old_step, 1
  br label %loop
  
return:
  %fmt_steps = getelementptr [20 x i8]* @fmt_steps, i32 0, i32 0
  %fmt_step  = getelementptr [19 x i8]* @fmt_step, i32 0, i32 0
  %fmt_check = icmp sle i64 %old_step, 1
  %fmt = select i1 %fmt_check, i8* %fmt_step, i8* %fmt_steps
  call i32 (i8*, ...)* @printf( i8* %fmt, i64 %old_step )
  ;call i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
  ret void
}


; declare linkonce_odr i8* @x.location()
; declare linkonce_odr i8* @y.location()
; declare linkonce_odr i8* @z.location()
; declare lii8* @cnt.location()

; define void @epilog()
; {
; begin:
;   ;; for simple.casm
;   %.x = call i8* @x.location()
;   %.y = call i8* @y.location()
;   %.z = call i8* @z.location()
;   %.cnt = call i8* @cnt.location()
;   %x = bitcast i8* %.x to %libcasm-rt.Int*
;   %y = bitcast i8* %.y to %libcasm-rt.Int*
;   %z = bitcast i8* %.z to %libcasm-rt.Int*
;   %cnt = bitcast i8* %.cnt to %libcasm-rt.Int*
  
;   call void @libcasm-rt.dump.Int( %libcasm-rt.Int* %x )
;   call void @libcasm-rt.dump.Int( %libcasm-rt.Int* %y )
;   call void @libcasm-rt.dump.Int( %libcasm-rt.Int* %z )
;   call void @libcasm-rt.dump.Int( %libcasm-rt.Int* %cnt )
;   ret void
; }
