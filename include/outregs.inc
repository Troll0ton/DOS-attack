;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||TASK5_UTILS|||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Output regs (STDCALL)
;-----------------------------------------------------------------------------------
;	Needs:			all regs in stack
;	Destroy List:	look for calling funtions
;	Return:			none
;-----------------------------------------------------------------------------------
OutRegs			proc

				push bp						;PROLOGUE
				mov bp, sp

				;AX
				mov si, offset ax_line
				mov bx, 160 * 3 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 3 + 2*61
				mov dx, [bp + 18]	
				push ax bx dx
				Call PrintReg

				;BX
				mov si, offset bx_line
				mov bx, 160 * 4 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 4 + 2*61
				mov dx, [bp + 12]	
				push ax bx dx
				Call PrintReg

				;CX
				mov si, offset cx_line
				mov bx, 160 * 5 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 5 + 2*61
				mov dx, [bp + 16]	
				push ax bx dx
				Call PrintReg

				;DX
				mov si, offset dx_line
				mov bx, 160 * 6 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 6 + 2*61
				mov dx, [bp + 14]	
				push ax bx dx
				Call PrintReg

				;SP
				mov si, offset sp_line
				mov bx, 160 * 10 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 10 + 2*61
				mov dx, [bp + 10]	
				push ax bx dx
				Call PrintReg

				;BP
				mov si, offset bp_line
				mov bx, 160 * 9 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 9 + 2*61
				mov dx, [bp + 8]	
				push ax bx dx
				Call PrintReg

				;SI
				mov si, offset si_line
				mov bx, 160 * 7 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 7 + 2*61
				mov dx, [bp + 6]	
				push ax bx dx
				Call PrintReg

				;DI
				mov si, offset di_line
				mov bx, 160 * 8 + 2*58
				mov cx, 3d
				Call OutLine
				mov ax, offset Troll
				mov bx, 160 * 8 + 2*61
				mov dx, [bp + 4]	
				push ax bx dx
				Call PrintReg

				mov sp, bp					;EPILOGUE	
				pop bp

				ret 16
				endp
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;Print one register (STDCALL)
;-----------------------------------------------------------------------------------
;	Needs:   		(STACK) {(reg value, pos in VM)}
;	Destroy List:	look for calling functions 
;	Return:			none
;-----------------------------------------------------------------------------------
PrintReg		proc

				push bp						;PROLOGUE
				mov bp, sp

				mov ax, [bp + 4]			;Reg value
				Call TrToHex                ;Translate it to line

				mov bx, [bp + 6]			;Pos in VM
				mov si, [bp + 8]    		;Ptr to arr
				add si, 12
				mov cx, 4d
				Call OutLine
				Call ClrArr

				mov sp, bp					;EPILOGUE	
				pop bp
			
				ret 6
				endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------