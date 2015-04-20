
;
; Copyright (c) 2015 Philipp Paulweber
;
; This file is part of the 'libcasm-rt' project which is released under a NCSA
; open source software license. For more information, see the LICENSE.txt 
; file in the project root directory.
;


; C wrapper
%struct.libcasmrt_Int  = type %libcasm-rt.Int

@libcasmrt_clr_Int          = alias void( %libcasm-rt.Int* )*
                              @libcasm-rt.clr.Int
@libcasmrt_set_Int_i64      = alias void( %libcasm-rt.Int*, i64 )*
                              @libcasm-rt.set.Int.i64
@libcasmrt_mov_Int_Int      = alias void( %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.mov.Int.Int
@libcasmrt_add_Int_Int_Int  = alias void( %libcasm-rt.Int*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.add.Int.Int.Int
@libcasmrt_sub_Int_Int_Int  = alias void( %libcasm-rt.Int*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.sub.Int.Int.Int
@libcasmrt_mul_Int_Int_Int  = alias void( %libcasm-rt.Int*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.mul.Int.Int.Int
@libcasmrt_div_Int_Int_Int  = alias void( %libcasm-rt.Int*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.div.Int.Int.Int
@libcasmrt_rem_Int_Int_Int  = alias void( %libcasm-rt.Int*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.rem.Int.Int.Int
@libcasmrt_lth_Bool_Int_Int = alias void( %libcasm-rt.Bool*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.lth.Bool.Int.Int
@libcasmrt_leq_Bool_Int_Int = alias void( %libcasm-rt.Bool*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.leq.Bool.Int.Int
@libcasmrt_gth_Bool_Int_Int = alias void( %libcasm-rt.Bool*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.gth.Bool.Int.Int
@libcasmrt_geq_Bool_Int_Int = alias void( %libcasm-rt.Bool*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.geq.Bool.Int.Int
@libcasmrt_equ_Bool_Int_Int = alias void( %libcasm-rt.Bool*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.equ.Bool.Int.Int
@libcasmrt_neq_Bool_Int_Int = alias void( %libcasm-rt.Bool*, %libcasm-rt.Int*, %libcasm-rt.Int* )*
                              @libcasm-rt.neq.Bool.Int.Int


; ; import Bool component
%libcasm-rt.Bool = type ; opaque
<{ i1  ; 0 value
 , i1  ; 1 isdef
 }>


%libcasm-rt.Int = type
<{ i64 ; 0 value
 , i1  ; 1 isdef
 }>


define void @libcasm-rt.clr.Int
( %libcasm-rt.Int* %rt
) #0
{
begin:
  %pu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  
  store i1 false, i1* %pu
  
  ret void
}


define void @libcasm-rt.set.Int.i64
( %libcasm-rt.Int* %rt
, i64 %imm
) #0
{
begin:
  %pv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
      
  store i64 %imm, i64* %pv
  store i1  true, i1*  %pu
  
  ret void
}


define void @libcasm-rt.mov.Int.Int
( %libcasm-rt.Int* %rt
, %libcasm-rt.Int* %ra
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 1
  
  %av  = load i64* %pav
  %au  = load i1* %pau
  
  store i64 %av, i64* %ptv
  store i1  %au, i1*  %ptu
  
  ret void
}


define void @libcasm-rt.add.Int.Int.Int
( %libcasm-rt.Int* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = add i64 %av, %bv
  %tu  = and i1  %au, %bu
  
  store i64 %tv, i64* %ptv
  store i1  %tu, i1*  %ptu
  
  ret void
}


define void @libcasm-rt.sub.Int.Int.Int
( %libcasm-rt.Int* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = sub i64 %av, %bv
  %tu  = and i1  %au, %bu
  
  store i64 %tv, i64* %ptv
  store i1  %tu, i1*  %ptu
  
  ret void
}


define void @libcasm-rt.mul.Int.Int.Int
( %libcasm-rt.Int* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = mul i64 %av, %bv
  %tu  = and i1  %au, %bu
  
  store i64 %tv, i64* %ptv
  store i1  %tu, i1*  %ptu
  
  ret void
}


define void @libcasm-rt.div.Int.Int.Int
( %libcasm-rt.Int* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = sdiv i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i64 %tv, i64* %ptv
  store i1  %tu, i1*  %ptu
  
  ret void
}


define void @libcasm-rt.rem.Int.Int.Int
( %libcasm-rt.Int* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int* %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int* %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = srem i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i64 %tv, i64* %ptv
  store i1  %tu, i1*  %ptu
  
  ret void
}


define void @libcasm-rt.lth.Bool.Int.Int
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 1
    
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = icmp slt i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}

; declare void @stdll.verbose.i64( i64 )
; declare void @stdll.verbose.i1( i1 )
; declare void @stdll.verbose.ln()

define void @libcasm-rt.leq.Bool.Int.Int
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 1
    
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %ct =  or i1 %au, %bu
  %c  = xor i1 %ct, true
  
  %tvt = icmp sle i64 %av, %bv
  
  ; call void @stdll.verbose.i64( i64 %av )
  ; call void @stdll.verbose.i64( i64 %bv )
  ; call void @stdll.verbose.i1( i1 %tvt )
  ; call void @stdll.verbose.ln()
  
  %tv  = or i1 %tvt, %c
  
  %tut = xor i1 %au, %bu
  %tu  = xor i1 %tut, true
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define void @libcasm-rt.gth.Bool.Int.Int
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 1
    
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %tv  = icmp sgt i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define void @libcasm-rt.geq.Bool.Int.Int
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  %ct =  or i1 %au, %bu
  %c  = xor i1 %ct, true
  
  %tvt = icmp sge i64 %av, %bv
  %tv  = or i1 %tvt, %c
  
  %tut = xor i1 %au, %bu
  %tu  = xor i1 %tut, true
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define void @libcasm-rt.equ.Bool.Int.Int
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  store i1 true, i1* %ptu
  
  %c = and i1 %au, %bu
  br i1 %c, label %number_number, label %other
  
number_number:
  %tv_n = icmp eq i64 %av, %bv
  store i1 %tv_n, i1* %ptv
  ret void

other:
  %tvt  = xor i1 %au, %bu
  %tv_o = xor i1 %tvt, true
  store i1 %tv_o, i1* %ptv
  ret void
}


define void @libcasm-rt.neq.Bool.Int.Int
( %libcasm-rt.Bool* %rt
, %libcasm-rt.Int* %ra
, %libcasm-rt.Int* %rb
) #0
{
begin:
  %ptv = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 0
  %pav = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 0
  %pbv = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 0
  %ptu = getelementptr %libcasm-rt.Bool* %rt, i32 0, i32 1
  %pau = getelementptr %libcasm-rt.Int*  %ra, i32 0, i32 1
  %pbu = getelementptr %libcasm-rt.Int*  %rb, i32 0, i32 1
  
  %av  = load i64* %pav
  %bv  = load i64* %pbv
  %au  = load i1* %pau
  %bu  = load i1* %pbu
  
  store i1 true, i1* %ptu
    
  %c = and i1 %au, %bu
  br i1 %c, label %number_number, label %other
  
number_number:
  %tv_n = icmp ne i64 %av, %bv
  store i1 %tv_n, i1* %ptv
  ret void

other:
  %tv_o = xor i1 %au, %bu
  store i1 %tv_o, i1* %ptv
  ret void
}


attributes #0 = { alwaysinline nounwind }

