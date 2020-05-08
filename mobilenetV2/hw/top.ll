; ModuleID = 'top.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: norecurse nounwind uwtable
define void @top(i64 %v1_addr, i64 %v2_addr, i64 %v3_addr) #0 {
entry:
  store volatile i64 %v1_addr, i64* inttoptr (i64 804257793 to i64*), align 8
  store volatile i64 789577728, i64* inttoptr (i64 804257801 to i64*), align 8
  store volatile i32 9600, i32* inttoptr (i64 804257809 to i32*), align 4
  store volatile i8 1, i8* inttoptr (i64 804257792 to i8*), align 1048576
  br label %while.cond

while.cond:                                       ; preds = %while.cond, %entry
  %0 = load volatile i8, i8* inttoptr (i64 804257792 to i8*), align 1048576
  %and = and i8 %0, 4
  %cmp = icmp eq i8 %and, 0
  br i1 %cmp, label %while.cond, label %while.end

while.end:                                        ; preds = %while.cond
  store volatile i64 %v2_addr, i64* inttoptr (i64 804257793 to i64*), align 8
  store volatile i64 789587328, i64* inttoptr (i64 804257801 to i64*), align 8
  store volatile i32 9600, i32* inttoptr (i64 804257809 to i32*), align 4
  store volatile i8 1, i8* inttoptr (i64 804257792 to i8*), align 1048576
  br label %while.cond2

while.cond2:                                      ; preds = %while.cond2, %while.end
  %1 = load volatile i8, i8* inttoptr (i64 804257792 to i8*), align 1048576
  %and4 = and i8 %1, 4
  %cmp5 = icmp eq i8 %and4, 0
  br i1 %cmp5, label %while.cond2, label %while.end8

while.end8:                                       ; preds = %while.cond2
  store volatile i8 1, i8* inttoptr (i64 788529177 to i8*), align 1
  br label %while.cond9

while.cond9:                                      ; preds = %while.cond9, %while.end8
  %2 = load volatile i8, i8* inttoptr (i64 788529177 to i8*), align 1
  %and11 = and i8 %2, 4
  %cmp12 = icmp eq i8 %and11, 0
  br i1 %cmp12, label %while.cond9, label %while.end15

while.end15:                                      ; preds = %while.cond9
  store volatile i64 789577776, i64* inttoptr (i64 804257793 to i64*), align 8
  store volatile i64 %v3_addr, i64* inttoptr (i64 804257801 to i64*), align 8
  store volatile i32 9600, i32* inttoptr (i64 804257809 to i32*), align 4
  store volatile i8 1, i8* inttoptr (i64 804257792 to i8*), align 1048576
  br label %while.cond16

while.cond16:                                     ; preds = %while.cond16, %while.end15
  %3 = load volatile i8, i8* inttoptr (i64 804257792 to i8*), align 1048576
  %and18 = and i8 %3, 4
  %cmp19 = icmp eq i8 %and18, 0
  br i1 %cmp19, label %while.cond16, label %while.end22

while.end22:                                      ; preds = %while.cond16
  ret void
}

attributes #0 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
