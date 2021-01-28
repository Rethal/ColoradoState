; Recitation 7
; Author: <name>
; Date:   <date>
; Email:  <email>
; Class:  CS270
;
; Description: Implements integer (16-bit) addition and subtraction
;
;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

; A jump table defined as an array of addresses
Functions       .FILL IntAdd         ; address of add routine      (option 0)
                .FILL IntSub         ; address of subtract routine (option 1)
                .FILL IntMul         ; address of multiply routine (option 2)

Main            LEA R0,Functions     ; get base of jump table
                LD  R1,Option        ; get option to use, no error checking
                ADD R0,R0,R1         ; add index of array
                LDR R0,R0,0          ; get address of function
                JSRR R0              ; call selected function
                HALT

; Parameters and return values for all functions
Option          .BLKW 1              ; which function to call
Param1          .BLKW 1              ; space to specify first parameter
Param2          .BLKW 1              ; space to specify second parameter
Result          .BLKW 1              ; space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------
IntAdd                               ; Your code goes here
                                     ; Solution has ~4 instructions
                LD R0,Param1
                LD R1,Param2
                ADD r0,r1,r0
                ST r0,Result
                RET
;------------------------------------------------------------------------------
IntSub                               ; Your code goes here
                                     ; Solution has ~6 instructions
                                     
    ;Invert the register storing Param2
   ; Increment Param2 using an immediate add 
		LD R0,Param1
                LD R1,Param2
                NOT r1,r1
                ADD r1,r1,#1
                ADD r0,r1,r0
                ST r0,Result
                RET

;------------------------------------------------------------------------------
IntMul                               ; Your code goes here
                                     ; Solution has ~9 instructions
                AND r0,r0,#0
                LD r1,Param1
                brz Exit
                LD r2,Param2
                brz Exit
 Loop           ADD r0,r0,r1
		ADD r2,r2,#-1
		brp Loop
 Exit           ST r0,Result    
                RET

;------------------------------------------------------------------------------
               .END

