; P6 Assignment
; Author: Brenton Grundman
; Date:   10/18/2015
; Email:  grundman@rams.colostate.edu
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

; A jump table defined as an array of addresses
Functions       .FILL intAdd         ; (option 0)
                .FILL intSub         ; (option 1)
                .FILL intMul         ; (option 2)
                .FILL binaryOr       ; (option 3)
                .FILL leftShift      ; (option 4)
                .FILL rightShift     ; (option 5)

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

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.
One		.FILL #1
Sixteen		.FILL #16
;------------------------------------------------------------------------------
intAdd                               ; Result is Param1 + Param2
                                     ; your code goes here (~4 lines)
                ld r0,Param1
                ld r1,Param2
                add r0,r0,r1
                st r0,Result
                RET
;------------------------------------------------------------------------------
intSub                               ; Result is Param1 - Param2
                                     ; your code goes here (~6 lines)
                ld r0,Param1
                ld r1,Param2
                not r1,r1
                add r1,r1,#1
                add r0,r0,r1
                st r0,Result
                RET
;------------------------------------------------------------------------------
intMul                               ; Result is Param1 * Param2
                                     ; your code goes here (~9 lines)
                and r0,r0,#0
                ld r1,Param1
                brz exit
                ld r2,Param2
                brz exit
mult            add r0,r0,r1
                add r2,r2,#-1
                brp mult
exit            st r0,Result                
                RET
;------------------------------------------------------------------------------
binaryOr                             ; Result is Param1 | Param2
                                     ; your code goes here (~7 lines)
                ld r0,Param1
                ld r1,Param2
                ld r2,One
                ld r4,Sixteen
over            and r3,r2,r1
                brz noadd
                and r3,r2,r0
                brnp noadd
                add r0,r0,r2
noadd           add r2,r2,r2
		add r4,r4,#-1
		brp over
		st r0,Result
                RET
;------------------------------------------------------------------------------
leftShift                            ; Result is Param1 << Param2
                                     ; your code goes here (~7 lines)
                ld r0,Param1
                ld r1,Param2
                brz end
shift           add r0,r0,r0
                add r1,r1,#-1
                brp shift
                st r0,Result
                RET
;------------------------------------------------------------------------------
rightShift                           ; Result is Param1 >> Param2
                                     ; your code goes here (~16 lines)
                ld r0,Param1
                ld r1,Param2
                brz end
                and r4,r4,#0
shifter         and r5,r5,#0
                ld r6,Sixteen
                ld r2,One
                ld r3,One
		add r3,r3,r3
shift1          and r4,r0,r3
                brz next
                add r5,r2,r5
next            add r2,r2,r2
		add r3,r3,r3
		add r6,r6,#-1
		brp shift1
		and r0,r0,#0
		add r0,r0,r5
		add r1,r1,#-1
		brp shifter
end		st r0,Result
                RET
;------------------------------------------------------------------------------
                .END
