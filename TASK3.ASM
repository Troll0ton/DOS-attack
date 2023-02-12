.model tiny
.code
org 100h

Start:		mov bx, 0b800h		;vidio mem seg addr
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
		mov dx, si		;save lenght
 		xor cx, cx

		neg dx			;find best position
		add dx, 80
		mov ax, dx
		mov bh, 2
		div bh
		mov dx, ax
		add cx, 80*12
		add cx, dx
		

		xor bx, bx

Next1:		mov ax, 0000h
		mov word ptr es:[bx], ax
		add bx, 2
		loop Next1
		
		mov cx, si
		xor ax, ax
		mov ah, 00eh
		xor si, si

Next3:		mov al, byte ptr Troll[si]	
	  	mov word ptr es:[bx], ax	;filling vidio mem
		inc ah
		and ah, 00Fh
		inc si
		add bx, 2
		loop Next3

		mov cx, 80*12

Next4:		mov ax, 0000h			;filling empty lines
		mov word ptr es:[bx], ax
		add bx, 2
		loop Next4		

		mov ax, 4c00h
		int 21h

Troll:		db 'Hello World!$'

end		Start