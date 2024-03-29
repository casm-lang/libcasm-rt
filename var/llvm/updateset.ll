;;
;;  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
;;  All rights reserved.
;;
;;  Developed by: Philipp Paulweber et al.
;;  <https://github.com/casm-lang/libcasm-rt/graphs/contributors>
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

@libcasm_rt_updateset_new     = alias %libcasm-rt.updateset*( %stdll.mem*, i32 )* @libcasm-rt.updateset.new
@libcasm_rt_updateset_del     = alias i8( %libcasm-rt.updateset* )*               @libcasm-rt.updateset.del
@libcasm_rt_updateset_insert  = alias i8*( %libcasm-rt.updateset*, i8*, %libcasm-rt.update* )*    @libcasm-rt.updateset.insert
@libcasm_rt_updateset_fork    = alias i8( %libcasm-rt.updateset* )*               @libcasm-rt.updateset.fork
@libcasm_rt_updateset_merge   = alias i8( %libcasm-rt.updateset* )*               @libcasm-rt.updateset.merge
@libcasm_rt_updateset_apply   = alias i8( %libcasm-rt.updateset* )*               @libcasm-rt.updateset.apply
@libcasm_rt_updateset_dump    = alias i8( %libcasm-rt.updateset* )*               @libcasm-rt.updateset.dump


define linkonce_odr %libcasm-rt.updateset* @libcasm-rt.updateset.new( %stdll.mem* %mem, i32 %size )
#0
{
begin:
  ; get size of uset
  %_sz = getelementptr %libcasm-rt.updateset* null, i32 1
  %sz  = ptrtoint %libcasm-rt.updateset* %_sz to i64
  
  %_uset = call i8* @stdll.malloc( %stdll.mem* %mem, i64 %sz )
  %uset  = bitcast i8* %_uset to %libcasm-rt.updateset*
  
  %check_uset = icmp ne %libcasm-rt.updateset* %uset, null              
  br i1 %check_uset, label %fetch, label %error_alloc_null
  
fetch:
  %dict  = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %ps    = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1
  
  %_dict = call %stdll.dict* @stdll.dict.new( %stdll.mem* %mem, i32 %size )
  %check_dict = icmp ne %stdll.dict* %_dict, null
  br i1 %check_dict, label %init, label %error_alloc_null

init:
  store %stdll.dict* %_dict, %stdll.dict** %dict
  store i16 0, i16* %ps
  
  ret %libcasm-rt.updateset* %uset
  
error_alloc_null:
  ret %libcasm-rt.updateset* null
}


define linkonce_odr i8 @libcasm-rt.updateset.del( %libcasm-rt.updateset* %uset )
#0
{
begin:
  ret i8 -1
}


; %libcasm-rt.update = type <{ i64 ; 0 value
;                            , i1  ; 1 defined
;                            }>

define linkonce_odr i8* @libcasm-rt.updateset.insert( %libcasm-rt.updateset* %uset, i8* %location, %libcasm-rt.update* %update )
#0
{
; check:
;   %check_uset = icmp ne %libcasm-rt.updateset* %uset, null
;   br i1 %check_uset, label %begin, label %error_uset_null

begin:
  %_dict = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %_ps   = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1
  
  %dict  = load %stdll.dict** %_dict        
  %ps    = load i16* %_ps

  %loc = ptrtoint i8* %location to i64
  %key_high = shl i64 %loc, 16
  %key_low  = zext i16 %ps to i64
  %key = or i64 %key_high, %key_low
  
  %value = bitcast %libcasm-rt.update* %update to i8*
  %result = call i8* @stdll.dict.set( %stdll.dict* %dict, i64 %key, i8* %value )
  
  %psmod  = srem i16 %ps, 2
  %parseq = icmp eq i16 %psmod, 0
  br i1 %parseq, label %par, label %seq
  
par:
  ret i8* %result
  
seq:
  ret i8* null
  
; error_uset_null:
;   ret i8* null
}


define linkonce_odr i8 @libcasm-rt.updateset.fork( %libcasm-rt.updateset* %uset )
#0
{
; check:
;   %check_uset = icmp ne %libcasm-rt.updateset* %uset, null
;   br i1 %check_uset, label %begin, label %error_uset_null
  
begin:
  %_ps   = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1
  %ps    = load i16* %_ps
  
  %new_ps = add i16 %ps, 1
  
  ; insert check here to catch overflows!!!
  
  store i16 %new_ps, i16* %_ps
  
  ret i8 0
  
; error_uset_null:
;   ret i8 -1
}


; define linkonce_odr i8 @libcasm-rt.updateset.merge( %libcasm-rt.updateset* %uset )
; #0
; {
; begin:
;   %_dict = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
;   %_ps   = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1
;   %dict   = load %stdll.dict** %_dict
;   %ps_old = load i16* %_ps
  
;   ; check if merge is valid or pseudostate is already zero then return
;   %c_no_merge = icmp eq i16 %ps_old, 0
;   br i1 %c_no_merge, label %return, label %prepare_merge

; prepare_merge:
;   %ps = sub i16 %ps_old, 1
;   store i16 %ps, i16* %_ps

;   call void @stdll.verbose.i16( i16 %ps_old )
;   call i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
  
;   %_last = call %stdll.dict.bucket* @stdll.dict.peek( %stdll.dict* %dict )
;   br label %fetch_element

; fetch_element:
;   %res  = phi %stdll.dict.bucket* [ %_last, %prepare_merge ], [ %_previous, %merge_element ]
;   %check_empty = icmp ne %stdll.dict.bucket* %res, null
;   br i1 %check_empty, label %process_element, label %return
  
; process_element:
;   %_key    = getelementptr %stdll.dict.bucket* %res, i32 0, i32 0
;   %key     = load i64* %_key
;   %key_low = trunc i64 %key to i16
  
;   %key_ptr = inttoptr i64 %key to i8*
;   call void @stdll.verbose.p( i8* %key_ptr )
;   call void @stdll.verbose.i16( i16 %key_low )
;   %_val    = getelementptr %stdll.dict.bucket* %res, i32 0, i32 1
;   %val     = load i8** %_val
;   call void @stdll.verbose.p( i8* %val )
;   call void @stdll.verbose.ln()
  
;   %check_ps = icmp ule i16 %key_low, %ps
;   br i1 %check_ps, label %return, label %merge_element
  
; merge_element:
;   %key_new = sub nsw i64 %key, 1
;   store i64 %key_new, i64* %_key
;   %_previous = call %stdll.dict.bucket* @stdll.dict.previous( %stdll.dict.bucket* %res )
;   br label %fetch_element

; return:
;   call void @stdll.verbose.i16( i16 %ps_old )
;   call i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
  
;   ret i8 0
  
; uset_empty:
;   ret i8 1

; ; error_uset_null:
; ;   ret i8 -1
; }


define linkonce_odr i8 @libcasm-rt.updateset.merge( %libcasm-rt.updateset* %uset )
#0
{
; check:
;   %check_uset = icmp ne %libcasm-rt.updateset* %uset, null
;   br i1 %check_uset, label %begin, label %error_uset_null
  
begin:
  %_dict = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %_ps   = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1

  %dict   = load %stdll.dict** %_dict
  %ps_old = load i16* %_ps
  
  ; check if merge is valid or pseudostate is already zero then return
  %c_no_merge = icmp eq i16 %ps_old, 0
  br i1 %c_no_merge, label %return, label %prepare_merge

prepare_merge:
  %ps = sub i16 %ps_old, 1
  store i16 %ps, i16* %_ps

  ; call void @stdll.verbose.i16( i16 %ps_old )
  ; call i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
  
  %_key = alloca i64
  %_val = alloca i8*
  br label %fetch_element

fetch_element:
  %res = call i8 @stdll.dict.pop( %stdll.dict* %dict, i64* %_key, i8** %_val )  
  %key_old = load i64* %_key
  %val     = load i8** %_val
  %check_empty = icmp eq i8 %res, 0
  br i1 %check_empty, label %process_element, label %at_top
  
process_element:
  %key_low = trunc i64 %key_old to i16

  ; %key_ptr = inttoptr i64 %key_old to i8*
  ; call void @stdll.verbose.p( i8* %key_ptr )
  ; call void @stdll.verbose.i16( i16 %key_low )
  ; call void @stdll.verbose.p( i8* %val )
  ; call void @stdll.verbose.ln()
  
  %check_ps = icmp ule i16 %key_low, %ps
  br i1 %check_ps, label %merge_done, label %merge_element
  
merge_element:
  %key = sub i64 %key_old, 1  
  call i8 @stdll.dict.stash( %stdll.dict* %dict, i64 %key, i8* %val )
  br label %fetch_element
  
merge_done:
  call i8* @stdll.dict.set( %stdll.dict* %dict, i64 %key_old, i8* %val )
  call i8 @stdll.dict.resolve( %stdll.dict* %dict )
  ret i8 0

at_top:
  call i8 @stdll.dict.resolve( %stdll.dict* %dict )
  ret i8 0

return:
  ret i8 0
  
uset_empty:
  ret i8 1

; error_uset_null:
;   ret i8 -1
}








; declare void @libcasm-rt.apply.Int( i8*, i8* )

define linkonce_odr i8 @libcasm-rt.updateset.apply( %libcasm-rt.updateset* %uset )
#0
{
begin:
  %_dict = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %_ps   = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1
  %dict  = load %stdll.dict** %_dict
  %ps    = load i16* %_ps

  %_last = call %stdll.dict.bucket* @stdll.dict.peek( %stdll.dict* %dict )
  
  %check_ps = icmp eq i16 %ps, 0
  br i1 %check_ps, label %apply, label %error_ps_is_not_zero
  
apply:
  %res  = phi %stdll.dict.bucket* [ %_last, %begin ], [ %pre, %process_element ]
  %check_empty = icmp ne %stdll.dict.bucket* %res, null
  br i1 %check_empty, label %process_element, label %return
;   %check_dict = icmp ne %stdll.dict* %dict, null
;   br i1 %check_dict, label %dict_apply, label %error_dict_null

; ; dict_apply:
;   %_d1 = getelementptr %stdll.dict* %dict, i32 0, i32 1
;   %p  = load %stdll.dict.bucket** %_d1
;   %c  = icmp ne %stdll.dict.bucket* %p, null
;   br i1 %c, label %loop, label %error_dict_null
  
process_element:
  ; %ptr  = phi %stdll.dict.bucket* [ %p, %apply ], [ %pre, %loop ]
  %_key = getelementptr %stdll.dict.bucket* %res, i32 0, i32 0
  %_val = getelementptr %stdll.dict.bucket* %res, i32 0, i32 1
  %_pre = getelementptr %stdll.dict.bucket* %res, i32 0, i32 3
  
  %key = load i64*                 %_key
  %val = load i8**                 %_val
  %pre = load %stdll.dict.bucket** %_pre
  
  %key_high = lshr i64 %key, 16
  %key_loc  = inttoptr i64 %key_high to i8*
  
  ; %upp = bitcast i8* %val to %libcasm-rt.update*
  ; %upv = getelementptr %libcasm-rt.update* %upp, i32 0, i32 0
  ; %upd = getelementptr %libcasm-rt.update* %upp, i32 0, i32 1
  ; ;%upt = getelementptr %libcasm-rt.update* %upd, i32 0, i32 2
  
  call void @libcasm-rt.apply.Int( i8* %key_loc, i8* %val )
  br label %apply
  ;%cond = icmp ne %stdll.dict.bucket* %pre, null
  ;br i1 %cond, label %loop, label %error_dict_null

return:
  ret i8 0

error_dict_null:
  ret i8 -3

error_ps_is_not_zero:
  ret i8 -1
}


define linkonce_odr i8 @libcasm-rt.updateset.dump( %libcasm-rt.updateset* %uset )
#0
{
; check:
;   %check_uset = icmp ne %libcasm-rt.updateset* %uset, null
;   br i1 %check_uset, label %begin, label %error_uset_null
  
begin:
  %_dict  = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 0
  %_ps    = getelementptr %libcasm-rt.updateset* %uset, i32 0, i32 1
  
  %dict = load %stdll.dict** %_dict
  %ps   = load i16* %_ps
  %.ps  = zext i16 %ps to i32
  call void @stdll.verbose.i32( i32 %.ps )
  call void @stdll.verbose.ln()
  call void @stdll.dict.dump( %stdll.dict* %dict )
  call void @stdll.verbose.ln()
  ;;call void @stdll.dict.dump.buckets( %stdll.dict* %dict )
  
  ret i8 0

; error_uset_null:
;   ret i8 -1
}




; define private hidden i32 @.nop() #0
; {
; begin:  
;   ret i32 0
; }

; attributes #0 = { alwaysinline }







