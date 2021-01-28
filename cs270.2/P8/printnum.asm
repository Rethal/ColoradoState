; Author: Fritz Sieker
;
; ------------------------------------------------------------------------
; Begin reserved section - do not change ANYTHING is this section

               .ORIG x3000
               BR Main

option         .BLKW 1          ; select routine to test
data1          .BLKW 1          ; use ONLY for testing
data2          .BLKW 1          ; use ONLY for testing

stackBase      .FILL X4000      ; initial sttack pointer

Main           LD R6,stackBase  ; initialize stack pointer
               LD R0,option     ; select routine to test
               BRZ testPrintNum ; option = 0 means test printNum

               ADD R0,R0,#-1
               BRZ testGetDigit ; option = 1 means test getDidit

               ADD R0,R0,#-1
               BRZ testDivRem   ; option = 2 means test divRem

               HALT             ; invalid option if here

testPrintNum                    ; call printNum(x, base)
               LD R0,data2
               PUSH R0          ; push base argument
               LD R0,data1
               PUSH R0          ; push value argument
               JSR printNum
               ADD R6,R6,#2     ; caller clean up 2 parameters
               NEWLN
               BR endTest

testGetDigit                    ; call getChar(val)
               LD R0,data1
               PUSH R0          ; push argument (val to convert to ASCII)
               JSR getDigit     ; 
               POP R0           ; get the corresponding character
               ADD R6,R6,#1     ; caller clean up 1 parameter
               OUT              ; print the character
	       NEWLN
               BR endTest

testDivRem                      ; call divRem(num, denom, *quotient, *remainder)
               LEA R0,data2     ; get pointer to remainder (&data2)
               PUSH R0
               LEA R0,data1     ; get pointer to quotient (&data1)
               PUSH R0
               LD R0,data2
               PUSH R0          ; push demoninator
               LD R0,data1
               PUSH R0          ; push numerator
               JSR divRem       ; call routine
               ADD R6,R6,#4     ; caller clean up 4 parameters

endTest        LEA R0,endMsg
               PUTS
theEnd         HALT             ; look at data1/data2 for quotient/remainder

                                ; useful constants
endMsg         .STRINGz "Test complete!\n"

negSign        .FILL    x2D     ; ASCII '-'
digits         .STRINGZ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; up to base 36

; end reserved section

; ------------------------------------------------------------------------
; Author: Brenton Grundman
; ------------------------------------------------------------------------
;
; C declaration: char getDigit (int val);

getDigit                        ; callee setup
	and r2,r2,0
	push r2
	PUSH R7
	push r6
                                ; code for getDigit
	LEA r1,digits
	add r0,r0,0
	brz end1
loop1	ADD r1,r1,1
	add r0,r0,-1
	brnp loop1
end1	ldr r0,r1,0
                                ; callee cleanup
        pop r6
        POP r7
        STR r0,r6,0
               RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void divRem(int num, int denom, int*quotient, int*remainder);

divRem                          ; callee setup
	push r7
	push r6
                                ; code for divRem
        and r2,r2,0
        and r3,r3,0                        
        ldr r0,r6,2		;r0 contains num 
        brz norem		;if zero, end 
        ldr r1,r6,3		;r1 contains denom 
;        brz norem
	not r1,r1		;negate r1
	add r1,r1,1		;2's complement
divv	add r2,r2,1		;increment quotient 
	add r0,r0,r1		;negate denom from num 
	brz norem		;if it isn't zero:
	brp divv		;if positive, do it again
	
				;else
	add r2,r2,-1		;undo one from quotient
	add r3,r3,r0		;add current negative numerator to remainder
	not r1,r1		;2's complement denom
	add r1,r1,1		
	add r3,r3,r1		;add denom to remainder
norem				; callee cleanup
        ldr r0,r6,4		;address of data1
        str r2,r0,0		;store quotient in that address
        ldr r0,r6,5		;address of data2
        str r3,r0,0		;store remainder in that address
        pop r6
        pop r7
               RET              ; return
; ------------------------------------------------------------------------
;
; C declaration: void printNum (int val, int base);

printNum                        ; callee setup
	push r7
	push r5
	add r5,r6,-1
	add r6,r6,-2
                                ; code for printNum
      ;call divRem
	add r0,r5,0
	push r0			;push address for remainder
	add r0,r5,-1
	push r0			;push address for quotient
	ldr r0,r5,4		;base into r0
	push r0			;denominator
	ldr r0,r5,3		;val into r0
	push r0			;numerator
	jsr divRem		;load quotient and remainder into respective spots (flipped)
	add r6,r6,4
	

				;print remainder, call divRem with quotient and base
	ldr r0,r5,-1		;load quotient into r3
	brz recurd		;if quotient is 0, break
	
	ldr r0,r5,4		;load base into r0
	push r0			;push base
	ldr r0,r5,-1
	push r0			;push quotient
	jsr printNum	
	add r6,r6,2
	
recurd	ldr r0,r5,0		;remainder into r0 (like ld r0,data1)			
	push r0			
	jsr getDigit		
	pop r0			;pop because out prints from r0
	add r6,r6,3
	OUT			
                                ; callee cleanup
	pop r5
	pop r7
               RET              ; return
; ------------------------------------------------------------------------
               .END
