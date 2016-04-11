;;  
;;  Copyright (c) 2016 Philipp Paulweber
;;  All rights reserved.
;;  
;;  Developed by: Philipp Paulweber
;;                https://github.com/ppaulweber/libcasm-rt
;;  
;;  This software is licensed under the Open Software License v. 3.0 (OSL-3.0).
;;  You either find the license text below or in the root directory of this 
;;  project in the LICENSE.txt file. If you cannot find the LICENSE.txt file,
;;  please refer to https://opensource.org/licenses/OSL-3.0.
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
