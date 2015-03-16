
;
; Copyright (c) 2015 Philipp Paulweber
;
; This file is part of the 'libcasm-rt' project which is released under a NCSA
; open source software license. For more information, see the LICENSE.txt 
; file in the project root directory.
;

; C wrapper
%struct.casmrt_updateset  = type %casm-rt.updateset

@casmrt_updateset_new     = alias %casm-rt.updateset*( %stdll.mem*, i32 )* @casm-rt.updateset.new
@casmrt_updateset_del     = alias i8( %casm-rt.updateset* )*               @casm-rt.updateset.del
@casmrt_updateset_insert  = alias i8*( %casm-rt.updateset*, i64, i64 )*    @casm-rt.updateset.insert
@casmrt_updateset_fork    = alias i8( %casm-rt.updateset* )*               @casm-rt.updateset.fork
@casmrt_updateset_merge   = alias i8( %casm-rt.updateset* )*               @casm-rt.updateset.merge
@casmrt_updateset_dump    = alias i8( %casm-rt.updateset* )*               @casm-rt.updateset.dump


; import memory component
%stdll.mem = type opaque
declare i8* @stdll.malloc( %stdll.mem* %mem, i64 %size )


; import dict component
%stdll.dict = type opaque
declare %stdll.dict* @stdll.dict.new( %stdll.mem*, i32 )
declare i8* @stdll.dict.set( %stdll.dict*, i64, i8* )
declare i8 @stdll.dict.pop( %stdll.dict*, i64*, i8** )
declare i8 @stdll.dict.stash( %stdll.dict* %dict, i64 %key, i8* %val )
declare i8 @stdll.dict.resolve( %stdll.dict* %dict )
declare void @stdll.dict.dump( %stdll.dict* )
declare void @stdll.dict.dump.buckets( %stdll.dict* )


; import verbose component
declare void @stdll.verbose.i64( i64 )
declare void @stdll.verbose.i32( i32 )
declare void @stdll.verbose.i16( i16 )
declare void @stdll.verbose.i8( i8 )
declare void @stdll.verbose.i1( i1 )
declare void @stdll.verbose.p( i8* )
declare void @stdll.verbose.ln()



%casm-rt.updateset = type <{ %stdll.dict*   ; 0 update set
                           , i16            ; 1 pseudo state
                           }>


define %casm-rt.updateset* @casm-rt.updateset.new( %stdll.mem* %mem, i32 %size )
{
begin:
  ; get size of uset
  %_sz = getelementptr %casm-rt.updateset* null, i32 1
  %sz  = ptrtoint %casm-rt.updateset* %_sz to i64
  
  %_uset = call i8* @stdll.malloc( %stdll.mem* %mem, i64 %sz )
  %uset  = bitcast i8* %_uset to %casm-rt.updateset*
  
  %check_uset = icmp ne %casm-rt.updateset* %uset, null              
  br i1 %check_uset, label %fetch, label %error_alloc_null
  
fetch:
  %dict  = getelementptr %casm-rt.updateset* %uset, i32 0, i32 0
  %ps    = getelementptr %casm-rt.updateset* %uset, i32 0, i32 1
  
  %_dict = call %stdll.dict* @stdll.dict.new( %stdll.mem* %mem, i32 %size )
  %check_dict = icmp ne %stdll.dict* %_dict, null
  br i1 %check_dict, label %init, label %error_alloc_null

init:
  store %stdll.dict* %_dict, %stdll.dict** %dict
  store i16 0, i16* %ps
  
  ret %casm-rt.updateset* %uset
  
error_alloc_null:
  ret %casm-rt.updateset* null
}


define i8 @casm-rt.updateset.del( %casm-rt.updateset* %uset )
{
begin:
  ret i8 -1
}


define i8* @casm-rt.updateset.insert( %casm-rt.updateset* %uset, i64 %location, i64 %value )
{
check:
  %check_uset = icmp ne %casm-rt.updateset* %uset, null
  br i1 %check_uset, label %begin, label %error_uset_null

begin:
  %_dict = getelementptr %casm-rt.updateset* %uset, i32 0, i32 0
  %_ps   = getelementptr %casm-rt.updateset* %uset, i32 0, i32 1
  
  %dict  = load %stdll.dict** %_dict        
  %ps    = load i16* %_ps
  
  %key_high = shl i64 %location, 16
  %key_low  = zext i16 %ps to i64
  %key = or i64 %key_high, %key_low
  
  %val = inttoptr i64 %value to i8*
  
  %result = call i8* @stdll.dict.set( %stdll.dict* %dict, i64 %key, i8* %val )
  
  %psmod  = srem i16 %ps, 2
  %parseq = icmp eq i16 %psmod, 0
  br i1 %parseq, label %par, label %seq
  
par:
  ret i8* %result
  
seq:
  ret i8* null
  
error_uset_null:
  ret i8* null
}


define i8 @casm-rt.updateset.fork( %casm-rt.updateset* %uset )
{
check:
  %check_uset = icmp ne %casm-rt.updateset* %uset, null
  br i1 %check_uset, label %begin, label %error_uset_null
  
begin:
  %_ps   = getelementptr %casm-rt.updateset* %uset, i32 0, i32 1
  %ps    = load i16* %_ps
  
  %new_ps = add i16 %ps, 1
  
  ; insert check here to catch overflows!!!
  
  store i16 %new_ps, i16* %_ps
  
  ret i8 0
  
error_uset_null:
  ret i8 -1
}


define i8 @casm-rt.updateset.merge( %casm-rt.updateset* %uset )
{
check:
  %check_uset = icmp ne %casm-rt.updateset* %uset, null
  br i1 %check_uset, label %begin, label %error_uset_null
  
begin:
  %_dict = getelementptr %casm-rt.updateset* %uset, i32 0, i32 0
  %_ps   = getelementptr %casm-rt.updateset* %uset, i32 0, i32 1

  %dict   = load %stdll.dict** %_dict
  %ps_old = load i16* %_ps
  
  ; check if merge is valid or pseudostate is already zero then return
  %c_no_merge = icmp eq i16 %ps_old, 0
  br i1 %c_no_merge, label %return, label %prepare_merge

prepare_merge:
  %ps = sub i16 %ps_old, 1
  store i16 %ps, i16* %_ps
  
  %_key = alloca i64
  %_val = alloca i8*
  br label %fetch_element

fetch_element:
  %res = call i8 @stdll.dict.pop( %stdll.dict* %dict, i64* %_key, i8** %_val )  
  %check_empty = icmp eq i8 %res, 0
  br i1 %check_empty, label %process_element, label %handle_result
  
process_element:
  %key_old = load i64* %_key
  %val     = load i8** %_val
  %key_low = trunc i64 %key_old to i16
  
  %check_ps = icmp ule i16 %key_low, %ps
  br i1 %check_ps, label %merge_done, label %merge_element
  
merge_element:
  %key = sub i64 %key_old, 1  
  call i8 @stdll.dict.stash( %stdll.dict* %dict, i64 %key, i8* %val )

  br label %fetch_element

handle_result:
;  ret i8 -2
  br label %return

merge_done:
  call i8 @stdll.dict.stash( %stdll.dict* %dict, i64 %key_old, i8* %val )
  br label %return

return:
  call i8 @stdll.dict.resolve( %stdll.dict* %dict )
  ret i8 0

uset_empty:
  ret i8 1

error_uset_null:
  ret i8 -1
}

define i8 @casm-rt.updateset.dump( %casm-rt.updateset* %uset )
{
check:
  %check_uset = icmp ne %casm-rt.updateset* %uset, null
  br i1 %check_uset, label %begin, label %error_uset_null
  
begin:
  %_dict  = getelementptr %casm-rt.updateset* %uset, i32 0, i32 0
  %_ps    = getelementptr %casm-rt.updateset* %uset, i32 0, i32 1
  
  %dict = load %stdll.dict** %_dict
  %ps   = load i16* %_ps
  
  call void @stdll.verbose.i16( i16 %ps )
  call void @stdll.verbose.ln()
  call void @stdll.dict.dump( %stdll.dict* %dict )
  ;call void @stdll.dict.dump.buckets( %stdll.dict* %dict )
  
  ret i8 0

error_uset_null:
  ret i8 -1
}




; define private hidden i32 @.nop() #0
; {
; begin:  
;   ret i32 0
; }

attributes #0 = { alwaysinline }







