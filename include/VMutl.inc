;-----------------------------------------------------------------------------------
;||||||||||||||||||||||||||___VIDEO MEMORY UTILS___|||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Screen Cleaning (FAST CALL?)
;-----------------------------------------------------------------------------------
;	Needs:			nothing
;	Destroy List:	BX, CX, ES
;	Return:			empty
;-----------------------------------------------------------------------------------
ClrScr			proc

				mov cx, 80*25				;screen size
				mov bx, 0b800h				;video mem addr
				mov es, bx			
				xor bx, bx

@@Next:	   		mov word ptr es:[bx], 0h
				add bx, 2					;fill by empty cells
				loop @@Next

				ret
				endp
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Output line (FAST CALL?)
;-----------------------------------------------------------------------------------
;	Needs:			your text in SI, 
;			  		position in VM in BX,
;					lenght of line in CX,
;	Destroy List:	AX, BX, SI, CX, ES
;	Return:			your text in VM
;-----------------------------------------------------------------------------------
OutLine			proc

				mov ax, 0b800h				;VM segment
				mov es, ax
				xor ax, ax

				mov ah, 3h 					;green color

@@Next:			mov al, byte ptr [si]	
				mov word ptr es:[bx], ax	;filling vidio mem
				inc si
				add bx, 2
				loop @@Next

				ret
				endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Copy array to VM (STDCALL)
;-----------------------------------------------------------------------------------
;	Needs:   		STACK (pos in VM, width and height of the space, ptr to array)
;	Destroy List:	ax, bx, cx, dx, es, si
;	Return:			none
;-----------------------------------------------------------------------------------
CopyToVM		proc

				push bp						;PROLOGUE
				mov bp, sp

				mov ax, 0b800h				;VM segment
				mov es, ax
											
				mov bx, [bp + 4]			;get pos in VM
				mov cx, [bp + 8]			;get height
				mov si, [bp + 10]			;get ptr to array

@@Height:		mov ax, [bp + 6]			;get width
@@Width:	    mov dx, word ptr [si]		;copy array elem
				mov word ptr es:[bx], dx
				add si, 2 
				add bx, 2
				dec ax
				cmp ax, 0
				jne @@Width

				mov bx, [bp + 4]
				add bx, 160d
				mov word ptr [bp + 4], bx
				Loop @@Height

			    mov sp, bp					;EPILOGUE	
				pop bp
	 
				ret 8
				endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Copy VM to array (STDCALL)
;-----------------------------------------------------------------------------------
;	Needs:   		STACK (pos in VM, width and height of the space, ptr to array)
;	Destroy List:	ax, bx, cx, dx, es, si
;	Return:			none
;-----------------------------------------------------------------------------------
CopyFromVM		proc

				push bp						;PROLOGUE
				mov bp, sp

				mov ax, 0b800h				;VM segment
				mov es, ax
											
				mov bx, [bp + 4]			;get pos in VM
				mov cx, [bp + 8]			;get height
				mov si, [bp + 10]			;get ptr to array

@@Height:		mov ax, [bp + 6]			;get width
@@Width:	    mov dx, word ptr es:[bx]	;copy array elem
				mov word ptr [si], dx 
				add si, 2d
				add bx, 2d
				dec ax
				cmp ax, 0
				jne @@Width

				mov bx, [bp + 4]
				add bx, 160d
				mov word ptr [bp + 4], bx
				Loop @@Height

			    mov sp, bp					;EPILOGUE	
				pop bp
	 
				ret 8
				endp
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Compare VM, Saved, Draw buffers and handle them (STDCALL)
;-----------------------------------------------------------------------------------
;	Needs:   		STACK (ptr to VM, Saved Buffer and Draw Buffer, width and height)
;	Destroy List:	ax, bx, cx, dx, es, si, di
;	Return:			none
;-----------------------------------------------------------------------------------
HandleBuffers	proc

				push bp						;PROLOGUE
				mov bp, sp

				mov ax, 0b800h				;VM segment
				mov es, ax
				xor ax, ax

				mov bx, word ptr [bp + 4]	;get ptr to VM
				mov di, word ptr [bp + 6]	;get ptr to Saved Buffer
				mov si, word ptr [bp + 8]	;get ptr to Draw Buffer

				mov cx, [bp + 12]			;get height

@@Height:		mov ax, [bp + 10]			;get width
@@Width:	    mov dx, word ptr [si]		;compare Draw Buffer and VM
				sub dx, word ptr es:[bx]	
				cmp dx, 0h
				je @@Skip

				mov dx, word ptr es:[bx]	;if they are not equal
				mov word ptr [di], dx  		;copy to Saved Buffer new one

@@Skip:			add bx, 2d					;move to next cell
				add si, 2d
				add di, 2d

				dec ax
				cmp ax, 0
				jne @@Width

				mov bx, [bp + 4]
				add bx, 160d
				mov word ptr [bp + 4], bx
				Loop @@Height

			    mov sp, bp					;EPILOGUE	
				pop bp
	 
				ret 10
				endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Clear array (Troll array) (FAST CALL?)
;-----------------------------------------------------------------------------------
;	Needs:			none
;	Destroy List:	SI, CX
;	Return:			none
;-----------------------------------------------------------------------------------
CLrArr			proc

				xor si, si
				mov cx, 16

@@Next:			mov byte ptr Troll[si], 30h
				inc si
				loop @@Next

				ret
				endp
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Input Line (Into Line array) (FAST CALL?)
;-----------------------------------------------------------------------------------
;	Needs:			none
;	Destroy List:	AX, CX, SI
;	Return:			none		
;-----------------------------------------------------------------------------------
InLine			proc
	
				mov cx, 5d 					;you can input only 5 symbols
				mov si, 0d
@@Next:	
				mov ah, 01h					;input (in al)
				int 21h

				mov byte ptr Line[si], al	;saved value into array
				inc si
				loop @@Next

				ret
				endp
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Draw Frames (FAST CALL?)
;-----------------------------------------------------------------------------------
;	Needs:			position in BX,
;					width in AL,
;					height in AH
;	Destroy List:	AX, BX, CX, DX
;	Return:			your green frame in VM		
;-----------------------------------------------------------------------------------
DrwFrm			proc

				mov dx, ax					;save frame size

				mov ax, 0b800h				;VM segment
				mov es, ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
;			 __ __________ ___
;VIEW:		|				  |
;			|				  |
;			|				  |
;			|				  |
;			|				  |
;			 --- _________ --- 
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
								;      __
				mov al, 0dah    ;	     |		
				mov ah, 3h														
				mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
						
				add bx, 2d			;	_________
				mov cl, dl
				xor ch, ch
				sub cx, 2d
				mov ah, 3h
				mov al, 0c4h
@@Next1:		mov word ptr es:[bx], ax	
				add bx, 2d
				loop @@Next1
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
									;	__
				mov al, 0bfh		;	  |
				mov ah, 3h			       
				mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 

				add bx, 80*2		;	|
									;   |
				mov cl, dh			;	|
				xor ch, ch
				sub cx, 2d
				mov ah, 3h
				mov al, 0b3h
@@Next2:		mov word ptr es:[bx], ax	
				add bx, 80*2
				loop @@Next2
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 

				mov al, 0d9h		;	|		
				mov ah, 3h			;   ---
				mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 

				sub bx, 2d			;	_________

				mov cl, dl
				xor ch, ch
				sub cx, 2d
				mov ah, 3h
				mov al, 0c4h
@@Next3:		mov word ptr es:[bx], ax	
				sub bx, 2d
				loop @@Next3

;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 

				mov al, 0c0h		;	|
				mov ah, 3h			;	---
				mov word ptr es:[bx], ax
;_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 

				sub bx, 80*2d		;	|
									;	|
				mov cl, dh			;	|
				xor ch, ch
				sub cx, 2d
				mov ah, 3h
				mov al, 0b3h
@@Next4:		mov word ptr es:[bx], ax	
				sub bx, 80*2
				loop @@Next4

				ret
				endp
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------


