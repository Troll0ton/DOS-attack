.model tiny
.code
org 100h
locals @@

Start:		Call ClrScr

			mov bx, 0b800h		;vidio mem seg addr
			mov es, bx
			xor bx, bx
	
			xor si, si			;counter
		
Next2:		mov cx, 0024h		;find length
			mov al, byte ptr Troll[si]

			xor cl, al			;if cl == al == 24h -> xor = 0
			inc si
			cmp cx, 0h			;compare with '$'
			jne Next2

;			IT IS LENGTH
;			    |
;			    V
			dec si				;remove extra symbol
 			xor cx, cx
						
								;find best position
			mov dx, 80			;length of screen
			sub dx, si
			shr dx, 1d			;dx /= 2

			add dx, 80*12
			shl dx, 1d			;bx - position in VM (video memory)
			mov bx, dx

			mov cx, si
			mov si, offset Troll

			Call OutLine	

			mov ax, 4c00h		;exit
			int 21h

			ret

			include vmutl.inc

.data
Troll:		db 'Hello World! Hello world!$'
Line:		db 30 DUP (0h)

end		Start