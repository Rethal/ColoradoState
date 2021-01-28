; Begin reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------
; Author: Fritz Sieker
;
; Description: Tests the implementation of a simple string library and I/O
;
; The ONLY exception to this is that you MAY change the .FILL values for
; Option, Value1 and Value2. this makes it easy to initialze the values in the
; program, so that you do not need to continually re-enter them. This
; makes debugging easier as you need only change your code and re-assemble.
; Your test value(s) will already be set.

        .ORIG x3000
        BR Main
Functions
        .FILL Test_strlen       ; (option 0)
        .FILL Test_strcpy       ; (option 1)
        .FILL Test_strcat       ; (option 2)
        .FILL Test_strcmp       ; (option 3)
        .FILL Test_printCC      ; (option 4)
        .FILL Test_pack         ; (option 5)
        .FILL Test_unpack       ; (option 6)
        .FILL Test_getsp        ; (option 7)
        .FILL Test_strunpack    ; (option 8)

; Parameters and return values for all functions
Option  .FILL 2                 ; which function to call
String1 .FILL x4000             ; default location of 1st string
String2 .FILL x4100             ; default location of 2nd string
Result  .BLKW 1                 ; space to store result
Value1  .BLKW 1                 ; used for testing pack/unpack
Value2  .BLKW 1                 ; used for testing pack/unpack
prompt  .STRINGZ "Enter packed string> "

Main    LEA R0,Functions        ; get base of jump table
        LD  R1,Option           ; get option to use, no error checking
        ADD R0,R0,R1            ; add index of array
        LDR R0,R0,#0            ; get address to test
        JMP R0                  ; execute test

Test_strlen 
        LD R0,String1           ; load string pointer
        GETS                    ; get string
        LD R0,String1           ; load string pointer
        JSR strlen              ; calculate length
        ST R0,Result            ; save result
        HALT                    ; done - examine memory[Result]

Test_strcpy 
        LD R0,String1           ; load string pointer
        GETS                    ; get string
        LD R0,String2           ; R0 is dest
        LD R1,String1           ; R1 is src
        JSR strcpy              ; copy string
        PUTS                    ; print result of strcpy
        NEWLN                   ; add newline
        HALT                    ; done - examine output

Test_strcat 
        LD R0,String1           ; load first pointer
        GETS                    ; get first string
        LD R0,String2           ; load second pointer
        GETS                    ; get second string
        LD R0,String1           ; dest is first string
        LD R1,String2           ; src is second string
        JSR strcat              ; concatenate string
        PUTS                    ; print result of strcat
        NEWLN                   ; add newline
        HALT                    ; done - examine output

Test_strcmp 
        LD R0,String1           ; load first pointer
        GETS                    ; get first string
        LD R0,String2           ; load second pointer
        GETS                    ; get second string
        LD R0,String1           ; dest is first string
        LD R1,String2           ; src is second string
        JSR strcmp              ; compare strings
        JSR printCC             ; print result of strcmp
        HALT                    ; done - examine output

Test_printCC    
        LD R0,Value1            ; get the test value
        .ZERO R1                ; reset condition codes
        JSR printCC             ; print condition code
        HALT                    ; done - examine output

Test_pack   
        LD R0,Value1            ; load first character
        LD R1,Value2            ; load second character
        JSR pack                ; pack characters
        ST R0,Result            ; save packed result
        HALT                    ; done - examine Result

Test_unpack 
        LD R0,Value1            ; value to unpack
        JSR unpack              ; test unpack
        ST R0,Value1            ; save upper 8 bits
        ST R1,Value2            ; save lower 8 bits
        HALT                    ; done - examine Value1 and Value2

Test_getsp  
        LEA R0,prompt           ; load prompt
        PUTS                    ; print prompt
        LD R0,String1           ; R0 is dest
        JSR getsp               ; test getsp
        PUTSP                   ; print it back out
        NEWLN                   ; add newline
        HALT                    ; done - examine output and String1

Test_strunpack  
        LD R0,String1           ; load string address
        JSR getsp               ; get a packed string
        LD R0,String2           ; R0 is dest
        LD R1,String1           ; R1 is src
        JSR strunpack           ; test strunpack
        PUTS                    ; print it back out
        NEWLN                   ; add newline
        HALT                    ; done - examine output and String1

;------------------------------------------------------------------------------
; End of reserved section
;
; Author: Brenton Grundman
strlen_ra	.BLKW 1
strlen          st r7,strlen_ra            ; size_t strlen(char *s)
                            ; on entry R0 contains s
                            ; on exit R0 contains length of s
	and r1,r1,0
	ldr r2,r0,0
	brz null
count1  add r1,r1,1
	add r0,r0,1
	ldr r2,r0,0
	brnp count1
null	and r0,r0,0
	add r0,r0,r1
	ld r7,strlen_ra
        RET

;------------------------------------------------------------------------------
dest	.BLKW 1        
strcpy                      ; char *strcpy(char *dest, char *src)
                            ; on entry R0 contains dest
                            ;          R1 contains src
                            ; on exit  R0 contains dest
        st r0,dest
        
iterate	ldr r2,r1,0	;read character from source
	str r2,r0,0	;write character to dest
	brz done	;stop on null termination
	add r0,r0,1	;increment dest
	add r1,r1,1	;increment src
	br iterate
done	ld r0,dest
        RET

;------------------------------------------------------------------------------

strcat                      ; char *strcat(char *dest, char *src)
                            ; on entry R0 contains dest
                            ;          R1 contains src
                            ; on exit  R0 contains dest
		st r0,dest	
append		add r0,r0,1	;increment dest
		ldr r2,r0,0	;read char from dest
		brnp append	;find the end of the line
iterate1	ldr r2,r1,0	;read character from source
		str r2,r0,0	;write character at end of line
		brz done1	;stop on null termination
		add r0,r0,1	;increment dest
		add r1,r1,1	;increment src
		br iterate1
done1		ld r0,dest
		RET

;------------------------------------------------------------------------------
s1	.BLKW 1
strcmp                      ; int strcmp(char *s1, char *s2)
                            ; on entry R0 contains s1
                            ;          R1 contains s2
                            ; on exit R0 contains negative number, if s1 < s2
                            ; a positive number if s1 > s2, else a zero
        st r0,s1
next1   ldr r2,r0,0	;read char from s1
	brz zzero	;check for zero case (matching) (end of line)
        ldr r3,r1,0	;read char from s2
        not r3,r3	;negate s2 char
        add r3,r3,1
        add r2,r3,r2	;compare s1 and s2 chars
        ;if zero, try next letter; if negative, return neg, if postive, return pos
        brn negzero
        brp poszero
        add r0,r0,1	;increment s1
        add r1,r1,1	;increment s2
        br next1	;check next letter
negzero	and r0,r0,0	;return a negative (s1<s2)
	add r0,r0,-1
	br done2
poszero	and r0,r0,0	;return a positive (s1>s2)
	add r0,r0,1	
	br done2
zzero	ldr r2,r1,0	;check for matching
	brz retzero	;return zero if matching (also end of line)
	br negzero	;otherwise s1 is negative
	
retzero	and r0,r0,0	;return zero (s1=s2)
done2
        RET

;------------------------------------------------------------------------------
negative	.STRINGZ "NEGATIVE"
positive	.STRINGZ "POSITIVE"
zero		.STRINGZ "ZERO"
printCC_ra	.BLKW 1
printCC         st r7,printCC_ra            	; on entry R0 contains value
						; on exit "NEGATIVE/ZERO/POSITIVE" printed
						; followed by newline
        add r0,r0,0		;checks sign
        brn neg
        brz zer
        brp pos
neg	lea r0, negative	;loads "NEGATIVE"        
	PUTS			;prints
	NEWLN			;new line
	br done3		;leave
pos	lea r0,positive		;loads "POSITIVE"
	PUTS
	NEWLN
	br done3
zer	lea r0,zero		;loads "ZERO"
	PUTS
	NEWLN
done3	ld r7,printCC_ra
	RET


;------------------------------------------------------------------------------
EightBits	.FILL xFF
Eight		.FILL 8
pack_ra	.BLKW 1
pack    st r7,pack_ra       ; on entry R0 contains 1st value
                            ;          R1 contains 2nd value
                            ; on exit R0 result of pack
        ld r2,eightbits
	and r0,r2,r0
	and r1,r2,r1
	ld r3,eight
packing	add r0,r0,r0
	add r3,r3,-1
	brp packing
	add r0,r1,r0
        ld r7,pack_ra
        RET

;------------------------------------------------------------------------------
One		.FILL 1
unpack_ra	.BLKW 1
unpack          st r7,unpack_ra	            ; on entry R0 contains a value
				; on exit R0 contains upper 8 bits
				;         R1 contains lower 8 bits
        and r1,r1,0		;clear r1
        and r2,r2,0		;clear r2
        add r2,r2,r0		;move r0
        and r0,r0,0		;clear r0
        ld r3,eight		;set up iterator
        ld r4,one		;set up bitchecker
cycle1	and r5,r2,r4		;check if bit is set in initial (lower section)
        brz noadd1		;if not, don't set it
        add r1,r1,r4		;if so, set it
noadd1	add r4,r4,r4		;increment bitchecker
	add r3,r3,-1		;count down iterator
	brp cycle1		;if not zero, check next bit
	ld r3,eight		;reload iterator
	ld r6,one		;load r6 with bitchecker-8
cycle2	and r5,r2,r4		;check if bit is set in initial (upper section)
	brz noadd2		;if not, don't set it
	add r0,r0, r6		;if so, set it
noadd2	add r4,r4,r4		;increment bitchecker
	add r6,r6,r6		;increment bitchecker-8
	add r3,r3,-1		;count down iterator
	brp cycle2		;if not zero, check next bit
	ld r7,unpack_ra
        RET

;------------------------------------------------------------------------------
getsp_ra	.BLKW 1
spstring	.BLKW 1
spoffset	.BLKW 1
spletter	.BLKW 1
getsp           st r7,getsp_ra	; on entry R0 contains dest
				; on exit R0 constains
				; dest filled with packed string
				; be sure and add null char
        GETS		;read string
        st r0,spstring	;store r0 address
        st r0,spoffset	;store offset (new letters) address
        st r0,spletter	;store letter reading address
next2   ldr r1,r0,1	;read second char
	ldr r0,r0,0	;read first char (lose address)
	brz Null2	;if null character, exit
	JSR pack	;pack them
	and r2,r2,0	;wipe r2
	add r2,r2,r0	;move the pack into r2
	ld r0,spoffset  ;go back to r0 offset address
	str r2,r0,0	;store pack into r0 offset by whatever
	add r0,r0,1	;increase stored location offset
	st r0,spoffset	;store new offset address
	ld r0,spletter	;load string reader location
	add r0,r0,2	;increment reader location by 2
	st r0,spletter	;save new reader location
	br next2	;repeat for next two letters
Null2	and r3,r3,0	;create null character
	ld r0,spoffset	;load offset
	str r3,r0,0	;store null character
	ld r0,spstring	;return to r0 string location
	ld r7,getsp_ra
        RET


;------------------------------------------------------------------------------
strunpack_ra	.BLKW 1
src		.BLKW 1
strunpack	st r7,strunpack_ra	; char *strunpack(char *dest, char *src)
					; on entry R0 contains dest
					;          R1 contains src
					; on exit  R0 contains dest
        st r0,dest		;store r0 location into dest
        ld r2,dest		;give r2 dest location
next3   st r1,src		;store r1 location into src
        ldr r0,r1,0		;read first packed character into r0
        JSR unpack		;unpack packed character into r0 and r1
        str r0,r2,0		;write character from r0 into r2 offset by 0
        brz null3		;if null, exit
        str r1,r2,1		;write character from r1 into r2 offset by 1
        brz null3		;if null, exit
        add r2,r2,2		;increment r2 by 2 for the next writing
        ld r1,src		;load source pointer into r1
        add r1,r1,1		;increment source pointer
        br next3		;go on to next character
null3	and r3,r3,0		;create null character
	str r3,r2,0		;store null character
	ld r0,dest		;return to r0 string location
	ld r7,strunpack_ra
        RET

;------------------------------------------------------------------------------
                .END

