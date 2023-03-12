.model tiny
.code
.286
org 100h
locals @@

Start:		Call ClrScr				;Clear screen

			Call HandleIn			;Handle Input

			mov ax, word ptr Num[0]	;calculate sum
			add ax, word ptr Num[2] 
			mov word ptr Num[4], ax	
		
			mov di, 80*7*2+6		;position in VM

			Call PrntRes			;print in bin, hex, dec 

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
		
			mov bx, 80*6*2			;position in VM
			mov al, 40d				;width of frame
			mov ah, 9d				;height of frame
			Call DrwFrm				;draw frames

			mov ax, 4c00h			;exit
			int 21h

			ret

			include trlt.inc
			include vmutl.inc

.data
FoolLine:		db '9728989$'
CoolLine:		db '89$'
Troll:			db 16 DUP (30h)
Line:			db 5 DUP (0h)
Num:			dw 3 DUP (0h)
;REGS LINES
ax_line:		db 'ax '
bx_line:		db 'bx '
cx_line:		db 'cx '
dx_line:		db 'dx '
si_line:		db 'si '
di_line:		db 'di '
bp_line:		db 'bp '
sp_line:		db 'sp '

end		Start