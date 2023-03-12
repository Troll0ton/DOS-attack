;------------------------------------------------------
;|||||||||||||||||VIDEO MEMORY UTILS|||||||||||||||||||
;------------------------------------------------------
;Screen Cleaning
;------------------------------------------------------
;	Needs:		nothing
;	Destroy List:	BX, CX, ES
;	Return:		empty
;------------------------------------------------------
ClrScr		proc

		mov cx, 80*25		;screen size
		mov bx, 0b800h		;video mem addr
		mov es, bx			
		xor bx, bx

@@Next:	        mov word ptr es:[bx], 0h
		add bx, 2		;fill by empty cells
		loop @@Next

		ret
		endp
;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;Output line (from Troll array)
;------------------------------------------------------
;	Needs:		your text in Troll, 
;			position in VM in BX,
;			lenght of line in SI,
;	Destroy List:	AX, BX, SI, CX
;	Return:		your text in VM
;------------------------------------------------------
OutLine		proc

		mov ax, 0b800h			;VM segment
		mov es, ax
		xor ax, ax

		mov ah, 3h 			;green color

		mov cx, si
		xor si, si

@@Next:		mov al, byte ptr Troll[si]	
	  	mov word ptr es:[bx], ax	;filling vidio mem
		inc si
		add bx, 2
		loop @@Next

		ret
		endp
;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;Clear array
;------------------------------------------------------
;	Needs:		none
;	Destroy List:	SI, CX
;	Return:		none
;------------------------------------------------------
CLrArr		proc

		xor si, si
		mov cx, 16

@@Next:		mov byte ptr Troll[si], 30h
		inc si
		loop @@Next

		ret
		endp
;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;Input Line (Into Line array)
;------------------------------------------------------
;	Needs:		
;------------------------------------------------------
InLine		proc
	
		mov cx, 5d 
		mov si, 0d
@@Next:	
		mov ah, 01h		;input (in al)
		int 21h

		mov byte ptr Line[si], al	
		inc si
		loop @@Next

		ret
		endp
;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;------------------------------------------------------
;Draw Frames
;------------------------------------------------------
;	Needs:		position in BX,
;				width in AL,
;				height in AH
;	Destroy List:	AX, BX, CX, DX
;	Return:		your green frame in VM		
;------------------------------------------------------
DrwFrm		proc

		mov dx, ax				;save frame size

		mov ax, 0b800h			;VM segment
		mov es, ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		mov al, 0dah			
		mov ah, 3h														
		mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		add bx, 2d

		mov cl, dl
		xor ch, ch
		sub cx, 2d
		mov ah, 3h
		mov al, 0c4h
@@Next1:		
	  	mov word ptr es:[bx], ax	
		add bx, 2d
		loop @@Next1
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		mov al, 0bfh
		mov ah, 3h
		mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		add bx, 80*2

		mov cl, dh
		xor ch, ch
		sub cx, 2d
		mov ah, 3h
		mov al, 0b3h
@@Next2:		
	  	mov word ptr es:[bx], ax	
		add bx, 80*2
		loop @@Next2
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		mov al, 0d9h
		mov ah, 3h
		mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		sub bx, 2d

		mov cl, dl
		xor ch, ch
		sub cx, 2d
		mov ah, 3h
		mov al, 0c4h
@@Next3:		
	  	mov word ptr es:[bx], ax	
		sub bx, 2d
		loop @@Next3

;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		mov al, 0c0h
		mov ah, 3h
		mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		sub bx, 80*2d

		mov cl, dh
		xor ch, ch
		sub cx, 2d
		mov ah, 3h
		mov al, 0b3h
@@Next4:		
	  	mov word ptr es:[bx], ax	
		sub bx, 80*2
		loop @@Next4
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

		ret
		endp
;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------

