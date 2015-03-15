
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


declare void @llvm.memcpy.p0i8.p0i8.i64( i8*, i8*, i64, i32, i1 )


; import Bool component
%libcasm-rt.Bool = type ; opaque
<{ i1  ; 0 value
 , i1  ; 1 isdef
 }>


%libcasm-rt.Int = type
<{ i64 ; 0 value
 , i1  ; 1 isdef
 }>


define fastcc void @libcasm-rt.clr.Int
( %libcasm-rt.Int* %rt
) #0
{
begin:
  %pu = getelementptr %libcasm-rt.Int* %rt, i32 0, i32 1
  
  store i1 false, i1* %pu
  
  ret void
}


define fastcc void @libcasm-rt.set.Int.i64
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


define fastcc void @libcasm-rt.mov.Int.Int
( %libcasm-rt.Int* %rt
, %libcasm-rt.Int* %ra
) #0
{
begin:
  %pt = bitcast %libcasm-rt.Int* %rt to i8*
  %pa = bitcast %libcasm-rt.Int* %ra to i8*
  
  call void @llvm.memcpy.p0i8.p0i8.i64
  ( i8* %pt
  , i8* %pa
  , i64 ptrtoint( %libcasm-rt.Int* getelementptr ( %libcasm-rt.Int* null, i32 1 ) to i64 )
  , i32 1
  , i1 false
  )
  
  ret void
}


define fastcc void @libcasm-rt.add.Int.Int.Int
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


define fastcc void @libcasm-rt.sub.Int.Int.Int
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


define fastcc void @libcasm-rt.mul.Int.Int.Int
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


define fastcc void @libcasm-rt.div.Int.Int.Int
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


define fastcc void @libcasm-rt.rem.Int.Int.Int
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


define fastcc void @libcasm-rt.lth.Bool.Int.Int
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


define fastcc void @libcasm-rt.leq.Bool.Int.Int
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
  
  %tv  = icmp sle i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define fastcc void @libcasm-rt.gth.Bool.Int.Int
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


define fastcc void @libcasm-rt.geq.Bool.Int.Int
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
  
  %tv  = icmp sge i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define fastcc void @libcasm-rt.equ.Bool.Int.Int
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
  
  %tv  = icmp eq i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


define fastcc void @libcasm-rt.neq.Bool.Int.Int
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
  
  %tv  = icmp ne i64 %av, %bv
  %tu  = and  i1  %au, %bu
  
  store i1 %tv, i1* %ptv
  store i1 %tu, i1* %ptu
  
  ret void
}


attributes #0 = { alwaysinline nounwind }

