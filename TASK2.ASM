.model tiny
.code
org 100h
locals @@

Start:		Call ClrScr

		mov bx, 0b800h		;vidio mem seg addr
		mov es, bx

		xor bx, bx
		xor cx, cx  		;nullify regs
		xor ax, ax
		xor si, si
		
Next2:		mov cx, 0024h		;find length
		mov al, byte ptr Troll[si]
		xor cl, al
		inc si
		cmp cx, 0
		jne Next2

		dec si		
 		xor cx, cx
		
				;find best position
		mov dx, 80
		sub dx, si
		mov ax, dx
		mov bh, 2
		div bh
		mov ah, 00h
		mov dx, ax
		mov cx, 80*12
		add cx, dx
		add cx, cx
		mov bx, cx
		

		Call OutLine		

		mov ax, 4c00h
		int 21h

		ret

		include vmutl.inc

Troll:		db 'Hello World! Hello world!$'

end		Start