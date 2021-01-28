; Recitation 8
; Author: Brenton Grundman
; Date:   10/16/1992
; Email:  grundman@rams.colostate.edu
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000

                JSR mirror           ; call function
                HALT

; Parameter and return value
Param           .BLKW 1              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants
One             .FILL #1             ; the number 1       
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
mirror                               ; Mirrors bits 7:0 to 15:8
                                     ; ~20 lines of assembly code
 
                LD R0,Param          ; load pattern
                                     ; your code here
                LD R1,Param
                ld r2, Mask
                and r1,r1,r2
                ld r2,One
                ld r3,One
                ld r4,Eight
shift           add r3,r3,r3
                add r4,r4,#-1
                brp shift
                ld r4,Eight
copy            and r5,r5,#0
                and r5,r2,r1
                brz noAdd
                add r1,r1,r3
noAdd           add r2,r2,r2
		add r3,r3,r3
		add r4,r4,#-1
		brp copy
                ST R1,Result         ; store result
                RET
;--------------------------------------------------------------------------
               .END

