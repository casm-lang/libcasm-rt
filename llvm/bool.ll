
;
; Copyright (c) 2015 Philipp Paulweber
;
; This file is part of the 'libcasm-rt' project which is released under a NCSA
; open source software license. For more information, see the LICENSE.txt 
; file in the project root directory.
;


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


define void @libcasm-rt.clr.Bool
( %libcasm-rt.Bool* %rt
) #0
{
begin:
  %pu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  
  store i1 false, i1* %pu
  
  ret void
}


define void @libcasm-rt.set.Bool.i1
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


define void @libcasm-rt.mov.Bool.Bool
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


define void @libcasm-rt.not.Bool.Bool
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


define void @libcasm-rt.and.Bool.Bool.Bool
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


define void @libcasm-rt.or.Bool.Bool.Bool
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


define void @libcasm-rt.xor.Bool.Bool.Bool
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


define void @libcasm-rt.equ.Bool.Bool.Bool
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


define void @libcasm-rt.neq.Bool.Bool.Bool
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

