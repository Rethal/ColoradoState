; PA6 Assignment
; Author: Brenton Grundman
; Date:   March 22, 2015
; Email:  grundman@rams.colostate.edu
; Class:  CS270
;
; Description: Implements the manipulation of half precision (16-bit) floating point numbers

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

; A jump table defined as an array of addresses
Functions       .FILL flt16_add      ; (option 0)
                .FILL flt16_sub      ; (option 1)
                .FILL flt16_get_sign ; (option 2)
                .FILL flt16_get_exp  ; (option 3)
                .FILL flt16_get_val  ; (option 4)
                .FILL flt16_abs      ; (option 5)
                .FILL flt16_neg      ; (option 6)
                .FILL left_most1     ; (option 7)
                .FILL left_shift     ; (option 8)
                .FILL right_shift    ; (option 9)
                .FILL binary_or      ; (option 10)

Main            LEA R0,Functions     ; get base of jump table
                LD  R1,Option        ; get option to use, no error checking
                ADD R0,R0,R1         ; add index of array
                LDR R0,R0,#0         ; get address of function
                JSRR R0              ; call selected function
                HALT

; Parameters and return values for all functions
Option          .BLKW 1              ; which function to call
Param1          .BLKW 1              ; space to specify first parameter
Param2          .BLKW 1              ; space to specify second parameter
Result          .BLKW 1              ; space to store result

; You may add variables and functions after here as you see fit. You may use JSR
; within the code of flt16_add or other functions. However, this requires that
; you save and restore return addresses, otherwise a function will not be able
; to use JSR to call another subroutine. See flt16_add for an example of how to
; save and restore a return address. When will this scheme NOT work?

; Here are some useful constants:

SIGN_MASK       .FILL x8000          ; 1 in left most bit 
EXP_MASK        .FILL x001F          ; exactly 5 bits     
VAL_MASK        .FILL x03FF          ; exactly 10 bits    
IMPL1_MASK      .FILL x0400          ; 1 in the 11 bit    
ONE             .FILL #1             ; the number 1       
TEN             .FILL #10            ; the number 10      
SIXTEEN         .FILL #16            ; the value 16

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; Local variables, this is how you will be tested for PA6
; Do not change the names!
signX           .BLKW 1              ; sign of X
expX            .BLKW 1              ; exponent of X
valX            .BLKW 1              ; mantissa of X
signY           .BLKW 1              ; sign of Y
expY            .BLKW 1              ; exponent of Y
valY            .BLKW 1              ; mantissa of Y
signSum         .BLKW 1              ; sign of sum
expSum          .BLKW 1              ; exponent of sum
valSum          .BLKW 1              ; mantissa of sum
expDiff         .BLKW 1              ; save difference
left1           .BLKW 1              ; location of left most 1

flt16_add_RA    .BLKW 1              ; return addess storage

flt16_add       ST R7,flt16_add_RA   ; save return address
                
		LD R7,flt16_add_RA   ; restore return address
                RET
;------------------------------------------------------------------------------
flt16_sub                            ; Result is Param1 minus Param2
                                     ; your code goes here
                RET
;------------------------------------------------------------------------------
flt16_get_sign                       ; Result is 0 if Param1 is positive, 1 otherwise
                AND R0,R0,#0         ; Initialize result
                LD R1,Param1         ; Get first parameter
                BRzp return_sign     ; Sign is 0 (zero or positive)
                ADD  R0,R0,#1        ; Sign is 1 (negative)
return_sign     ST R0,Result         ; Save the result
                RET
;------------------------------------------------------------------------------
flt16_get_exp                        ; Result is biased exponent from Param1
                                     ; your code goes here
                and r0,r0,#0
		ld r1,param1
		ld r2,impl1_mask
		ld r3,one
		ld r5,exp_mask
create_exp	and r4,r1,r2
		brz zero_exp
		not r0,r0
		not r3,r3
		and r0,r0,r3
		not r0,r0
		not r3,r3
zero_exp	add r2,r2,r2
		add r3,r3,r3
		brnp create_exp
return_exp	and r0,r0,r5
		st r0,result
		RET
;------------------------------------------------------------------------------
flt16_get_val                        ; Result is mantissa from Param1 plus implicit 1
                                     ; your code goes here
		and r0,r0,#0
		ld r1,param1
		brz return_val
		ld r2,one
		ld r3,ten
create_val	and r4,r1,r2
		brz zero_val
		not r0,r0
		not r2,r2
		and r0,r0,r2
		not r0,r0
		not r2,r2
zero_val	add r2,r2,r2
		add r3,r3,#-1
		brp create_val
		ld r5,impl1_mask
		add r0,r0,r5
return_val	st r0,result
                RET
;------------------------------------------------------------------------------
flt16_abs                            ; Result is absolute value of Param1
                                     ; your code goes here
		ld r1,param1
		brzp return_abs
		ld r2,sign_mask
		not r2,r2
		and r1,r1,r2
return_abs	st r1,result
                RET
;------------------------------------------------------------------------------
flt16_neg                            ; Result is negative value of Param1
                                     ; your code goes here
				     ; Negative 0.0 is 0.0, not -0.0.
		ld r1,param1
		brz return_neg
		ld r2,sign_mask
		add r1,r1,r2
return_neg	st r1,result
                RET
;------------------------------------------------------------------------------
left_most1                           ; Result is bit position of leftmost 1 in Param1
				     ; 0 is least significant bit
				     ; Return -1 if no bits set.
                                     ; your code goes here
		ld r1,param1
		brz return_no1
		ld r2,sign_mask
		ld r3,sixteen
leftmost	add r3,r3,#-1
		and r0,r1,r2
		brnp return_most1
		add r1,r1,r1
		brnp leftmost
return_no1	add r3,r3,#-1
		st r3,result
		RET
return_most1	st r3,result
                RET
;------------------------------------------------------------------------------
left_shift                           ; Result is Param1 shifted left by Param2 bits
                                     ; your code goes here
		ld r1,param1
		ld r2,param2
		brnz return_left
shift1		add r1,r1,r1
		add r2,r2,#-1
		brp shift1
return_left	st r1,result
                RET
;------------------------------------------------------------------------------
right_shift                          ; Result is Param1 shifted right by Param2 bits
                                     ; your code goes here
		and r0,r0,#0
		ld r1,param1
		ld r2,param2
		brp shift2
		st r1,result
		RET
shift2		ld r3,one
		ld r4,one
		add r4,r4,r4
shift3		and r5,r4,r1
		brz zero_right
		not r0,r0
		not r3,r3
		and r0,r0,r3
		not r0,r0
		not r3,r3
zero_right	add r3,r3,r3
		add r4,r4,r4
		brnp shift3
decrement	st r0,result
		ld r1,result
		and r0,r0,#0
		add r2,r2,#-1
		brp shift2
return_right	RET
;------------------------------------------------------------------------------
binary_or                            ; Result is a bitwise OR of Param1 and Param2
                                     ; your code goes here
		and r0,r0,#0
                ld r1,param1
		ld r2,param2
		not r1,r1
		not r2,r2
		and r0,r1,r2
		not r0,r0
		st r0,result
		RET
;------------------------------------------------------------------------------
                .END


