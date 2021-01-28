;; File:	pa8.asm
;; Description: Solution assembly code for PA8, CS270
;; Author:	Jack Applin
;; Date:	April 6, 2015


;; Here are some traps that will prove useful:
;
;	out			; emit character in R0
;
;	gets			; R0 = buffer address
;				; Read a line, strip off the trailing newline,
;				; and null-terminate the string.

	.orig	x3000

	;; Program entry point
main	ld	r6,stack	; Initialize stack pointer
	lea	r0,buf		; input buffer address
	gets			; read a string
	lea	r0,buf		; input buffer address
	push	r0		; Push buffer address parameter
	jsr	reverse		; display string, reversed, translated
	pop	r0		; Remove parameter from stack
	ld	r0,newline
	out
	halt			; Program complete

;; Print a string, reversed & translated
reverse push	r7		; Push return address
	push	r5		; Push frame pointer
	add	r5,r6,#0	; Setup frame pointer

	;; function body

	;; Is the first character null?
	ldr r0,r5,2		; Get the argument--pointer to chars
	brnp reverse		; Is the first character null?
				; If null, we have nothing to do.

	; Call reverse on the subsequent characters

	; Emit a single character.
	; First, translate it.

	;; stack exit
	pop	r5		; Pop frame pointer
	pop	r7		; Pop return address
	ret			; Return

;;;;; Translate a/e/i/o/u to *.
translate 
	;; stack entry
	push	r7		; Push return address
	push	r5		; Push frame pointer
	add	r5,r6,#0	; Setup frame pointer

	;; function body

	;; stack exit
	pop	r5		; Pop frame pointer
	pop	r7		; Pop return address
	ret


;; Constants & storage
stack	.fill	x4000		; stack starts at location x4000
buf	.blkw	80		; input characters go here
newline	.fill	10		; \n

	.end
