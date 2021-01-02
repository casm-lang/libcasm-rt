;;
;;  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
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

@libcasm_rt_update_new = alias %libcasm-rt.update*( %stdll.mem*, i64, i1 )* @libcasm-rt.update.new
@libcasm_rt_update_Int = alias void( %libcasm-rt.updateset*, i8*, %libcasm-rt.Int* )* @libcasm-rt.update.Int
; @libcasm_rt_lookup_Int = alias %libcasm-rt.Int*( %libcasm-rt.updateset*, i8* )* @libcasm-rt.lookup.Int
@libcasm_rt_apply_Int  = alias void( i8*, i8* )* @libcasm-rt.apply.Int



; ; import memory component
; ; %stdll.mem = type opaque
; declare i8  @stdll.mem.new( %stdll.mem* %mem, i64 %size )
; declare i8  @stdll.mem.del( %stdll.mem* %mem )
; declare i8* @stdll.malloc( %stdll.mem* %mem, i64 %size )

; ; import verbose component
; declare void @stdll.verbose.i64( i64 )
; declare void @stdll.verbose.i32( i32 )
; declare void @stdll.verbose.i16( i16 )
; declare void @stdll.verbose.i8( i8 )
; declare void @stdll.verbose.i1( i1 )
; declare void @stdll.verbose.p( i8* )
; declare void @stdll.verbose.ln()


; declare i8* @libcasm-rt.updateset.insert( %libcasm-rt.updateset*, i8*, %libcasm-rt.update* )



; ; bucket
; %stdll.dict.bucket = type <{ i64                 ; 0 key
;                            , i8*                 ; 1 value
;                            , i1                  ; 2 locked
;                            , %stdll.dict.bucket* ; 3 previous
;                            }>

; ; dict
; %stdll.dict = type <{ %stdll.dict.bucket* ; 0 buckets
;                     , %stdll.dict.bucket* ; 1 last bucket
;                     , %stdll.dict.bucket* ; 2 stash bucket
;                     , %stdll.mem*         ; 3 memory
;                     , i32                 ; 4 dict counter (=size)
;                     , i32                 ; 5 dict length
;                     , i32                 ; 6 dict load factor
;                     , i1                  ; 7 flag (false=normal, true=branding) behavior
;                     }>                    ;   currently ignored, always branding behavior!

; ; ; import uset
; %libcasm-rt.updateset = type <{ %stdll.dict*   ; 0 update set
;                            , i16            ; 1 pseudo state
;                            }>





define linkonce_odr %libcasm-rt.update* @libcasm-rt.update.new
( %stdll.mem* %mem, i64 %value, i1 %isdef ) #0
{
begin:
  ; get size of an update
  %_sz = getelementptr %libcasm-rt.update* null, i32 1
  %sz  = ptrtoint %libcasm-rt.update* %_sz to i64
  
  %_update = call i8* @stdll.malloc( %stdll.mem* %mem, i64 %sz )
  %update  = bitcast i8* %_update to %libcasm-rt.update*
  
  %check = icmp ne %libcasm-rt.update* %update, null              
  br i1 %check, label %init, label %error_alloc_null
  
init:
  %_val = getelementptr %libcasm-rt.update* %update, i32 0, i32 0
  %_def = getelementptr %libcasm-rt.update* %update, i32 0, i32 1
  
  store i64 %value,   i64* %_val
  store i1  %isdef, i1*  %_def
  
  ret %libcasm-rt.update* %update
  
error_alloc_null:
  ret %libcasm-rt.update* null
}


; %libcasm-rt.Int = type
; <{ i64 ; 0 value
;  , i1  ; 1 isdef
;  }>

; declare void @llvm.debugtrap() noreturn nounwind




define linkonce_odr i8* @libcasm-rt.lookup( %libcasm-rt.updateset* %uset, i8* %loc )
#0
{
begin:
  %id = ptrtoint i8* %loc to i64
  %key_high = shl i64 %id, 16
    
  %_di = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %_ps = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1
  %di = load %stdll.dict** %_di
  %ps = load i16* %_ps
  
  ; call void @stdll.verbose.p( i8* null )
  ; call void @stdll.verbose.ln()
  ; call i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
  ; call void @stdll.verbose.p( i8* null )
  ; call void @stdll.verbose.ln()
    
  %cnt = zext i16 %ps to i64
  
  %mod = urem i64 %cnt, 2
  %mod_check = icmp eq i64 %mod, 0
  br i1 %mod_check, label %subtract, label %fetch

subtract:
  %cnt1 = sub i64 %cnt, 1
  br label %fetch

notfound:
  %cnt2 = sub i64 %ps_cnt, 2
  %glchk = icmp sle i64 %cnt2, 0
  br i1 %glchk, label %state, label %fetch

fetch:
  %ps_cnt = phi i64 [ %cnt, %begin ], [ %cnt1, %subtract ], [ %cnt2, %notfound ]
  %key  = or i64 %key_high, %ps_cnt
  %val  = alloca i8*

  %k = inttoptr i64 %key to i8*
  ;call void @stdll.verbose.p( i8* %k )
  
  %resget = call i8 @stdll.dict.get( %stdll.dict* %di, i64 %key, i8** %val )
  %reschk = icmp eq i8 %resget, 0
  br i1 %reschk, label %found, label %notfound

found:
  %arg = load i8** %val
  br label %state    
  
state:  
  %ptr = phi i8* [ %arg, %found ], [ %loc, %notfound ]

  ; %res = bitcast i8* %ptr to %libcasm-rt.Int*
  ; %_dval = getelementptr %libcasm-rt.Int* %res, i32 0, i32 0
  ; %_ddef = getelementptr %libcasm-rt.Int* %res, i32 0, i32 1
  ; %_val = load i64* %_dval
  ; %_def = load i1*  %_ddef
  ; call void @stdll.verbose.p( i8* %loc )
  ; call void @stdll.verbose.p( i8* %ptr )
  ; call void @stdll.verbose.i64( i64 %_val )
  ; call void @stdll.verbose.i1 ( i1  %_def )
  ; call void @stdll.verbose.ln()  
  
  ret i8* %ptr
}




;declare void @llvm.memcpy.p0i8.p0i8.i32( i8*, i8*, i32, i32, i1 ) nounwind
;@libcasm-rt.Int.size = constant i32 ptrtoint( %libcasm-rt.Int* getelementptr( %libcasm-rt.Int* null, i32 1 ) to i32 )

define linkonce_odr void @libcasm-rt.apply.Int
( i8* %loc, i8* %val )
#0
{
begin:    
  %upp = bitcast i8* %val to %libcasm-rt.update*
  %upv = getelementptr %libcasm-rt.update* %upp, i32 0, i32 0
  %upd = getelementptr %libcasm-rt.update* %upp, i32 0, i32 1
  %v = load i64* %upv
  %d = load i1*  %upd
  
  %ip = bitcast i8* %loc to %libcasm-rt.Int*
  %iv = getelementptr %libcasm-rt.Int* %ip, i32 0, i32 0
  %id = getelementptr %libcasm-rt.Int* %ip, i32 0, i32 1
  
  store i64 %v, i64* %iv
  store i1  %d, i1*  %id
;call void @llvm.memcpy.p0i8.p0i8.i32( i8* %loc, i8* %val, i32 @libcasm-rt.Int.size, i32 1, i1 false)
  ret void  
;  ret %libcasm-rt.Int* %res
}





define void @libcasm-rt.update( %libcasm-rt.updateset* %uset, %stdll.mem* %mem, i8* %loc, i64 %val, i1 %def )
#0
{
begin:
  %upd = call %libcasm-rt.update* @libcasm-rt.update.new( %stdll.mem* %mem, i64 %val, i1 %def )
  %res = call i8* @libcasm-rt.updateset.insert
         ( %libcasm-rt.updateset* %uset, i8* %loc, %libcasm-rt.update* %upd )
  
  ; ; check res ... parallel conflict etc. TODO: FIXME: PPA:
  ; %cond = ptrtoint i8* %res to i32
  ; call void @llvm.debugtrap() ; maybe a solution?


  ; call void @assert( i32 %cond )
  ; unreachable

  ; %udp_ = bitcast %libcasm-rt.update* %upd to i8*
  ; call void @stdll.verbose.i64( i64 -1 )
  ; call void @stdll.verbose.p  ( i8* %loc )
  ; call void @stdll.verbose.i64( i64 %val )
  ; call void @stdll.verbose.i1 ( i1  %def )
  ; call void @stdll.verbose.p  ( i8* %udp_ )
  ; call void @stdll.verbose.p  ( i8* %res )
  ; call void @stdll.verbose.ln()
    
  ret void
}


define linkonce_odr void @libcasm-rt.update.Rule
( %libcasm-rt.updateset* %uset, i8* %loc, %libcasm-rt.Rule* %value )
#0
{
begin:
  %_dic = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %dic  = load %stdll.dict** %_dic
  %_mem = getelementptr %stdll.dict* %dic, i32 0, i32 3
  %mem  = load %stdll.mem** %_mem
  
  %_val = getelementptr %libcasm-rt.Rule* %value, i32 0, i32 0
  %_def = getelementptr %libcasm-rt.Rule* %value, i32 0, i32 1

  %.val = load %libcasm-rt.RuleAddr* %_val
  %val  = ptrtoint %libcasm-rt.RuleAddr %.val to i64
  %def  = load i1* %_def
  
  call void @libcasm-rt.update
  ( %libcasm-rt.updateset* %uset, %stdll.mem* %mem, i8* %loc, i64 %val, i1 %def )
  
  ret void
}


define linkonce_odr void @libcasm-rt.update.Int
( %libcasm-rt.updateset* %uset, i8* %loc, %libcasm-rt.Int* %value )
#0
{
begin:
  %_dic = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %dic  = load %stdll.dict** %_dic
  %_mem = getelementptr %stdll.dict* %dic, i32 0, i32 3
  %mem  = load %stdll.mem** %_mem
  
  %_val = getelementptr %libcasm-rt.Int* %value, i32 0, i32 0
  %_def = getelementptr %libcasm-rt.Int* %value, i32 0, i32 1
  %val  = load i64* %_val
  %def  = load i1* %_def
  
  call void @libcasm-rt.update
  ( %libcasm-rt.updateset* %uset, %stdll.mem* %mem, i8* %loc, i64 %val, i1 %def )
  
  ret void
}


define linkonce_odr void @libcasm-rt.update.Str
( %libcasm-rt.updateset* %uset, i8* %loc, %libcasm-rt.Str* %value )
#0
{
begin:
  %_dic = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %dic  = load %stdll.dict** %_dic
  %_mem = getelementptr %stdll.dict* %dic, i32 0, i32 3
  %mem  = load %stdll.mem** %_mem
  
  %_val = getelementptr %libcasm-rt.Str* %value, i32 0, i32 0
  %_def = getelementptr %libcasm-rt.Str* %value, i32 0, i32 1
  %.val = load i8** %_val
  %val  = ptrtoint i8* %.val to i64
  %def  = load i1* %_def
  
  call void @libcasm-rt.update
  ( %libcasm-rt.updateset* %uset, %stdll.mem* %mem, i8* %loc, i64 %val, i1 %def )

  ret void
}

