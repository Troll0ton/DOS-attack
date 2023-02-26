.model tiny
.code
org 100h
locals @@

Start:		Call ClrScr		;Clear screen

		Call HandleIn		;Handle Input

		mov ax, word ptr Num[0]	;calculate sum
		add ax, word ptr Num[2] 
		mov word ptr Num[4], ax
		
		mov di, 80*7*2+6	;position in VM

		Call PrntRes

		mov ax, word ptr Num[0]	;calculate sub
		sub ax, word ptr Num[2] 
		mov word ptr Num[4], ax

		mov di, 80*11*2+6

		Call PrntRes

		mov ax, word ptr Num[0]	;calculate mul
		mov dx, word ptr Num[2]
		mul dl
		mov word ptr Num[4], ax

		mov di, 80*7*2+44

		Call PrntRes

		mov ax, word ptr Num[0]	;calculate mul
		mov dx, word ptr Num[2]
		div dl
		mov word ptr Num[4], ax

		mov di, 80*11*2+44

		Call PrntRes
		
		mov bx, 80*6*2
		mov al, 40d
		mov ah, 9d		
		Call DrwFrm		;draw frames

		mov ax, 4c00h		;exit
		int 21h

		ret

		include trlt.inc
		include vmutl.inc
		include io.inc

Troll:		db 16 DUP (30h)

Line:		db 5 DUP (0h)

Num:		dw 3 DUP (0h)

end		Start