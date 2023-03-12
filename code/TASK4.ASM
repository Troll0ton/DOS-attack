.model tiny
.code
org 100h
locals @@

Start:		;Call ClrScr		;Clear screen

Next:		mov ax, 1111h
			mov bx, 2222h
			mov cx, 3333h
			mov dx, 4444h
			mov si, 5555h
			mov di, 6666h
			mov bp, 7777h

			jmp Next

			mov ax, 4c00h		;exit
			int 21h

			ret

			include trlt.inc
			include vmutl.inc

Troll:			db 16 DUP (30h)
Line:			db 5 DUP (0h)
Num:			dw 3 DUP (0h)

end		Start