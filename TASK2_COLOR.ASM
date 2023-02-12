.model tiny
.code
org 100h

Start:		mov bx, 0b800h		;vidio mem seg addr
		mov es, bx
	
		xor bx, bx

		mov cx, 80*25
		mov ax, 0ce00h

Next:		mov dx, ax
		add dx, 00058h

		mov word ptr es:[bx], dx
		add ax, 100h

		add bx, 2
		loop Next

		mov ax, 4c00h
		int 21h

end		Start