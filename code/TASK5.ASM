.286
.model tiny
.code
org 100h
locals @@

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------

Start:			cli:							;forbid interrupts (OPEN)

				; ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
				;CHANGE 08 INT
				xor bx, bx
				mov es, bx
				mov bx, 4*8						; 08 segment in RAM         

				mov ax, es:[bx]            		;saved old offset interrupt 09
				mov word ptr Old08[0], ax       
				mov ax, offset New08			;load new segment
				mov es:[bx], ax

				mov ax, cs						

				mov dx, es:[bx + 2]
				mov word ptr Old08[2], dx       ;saved old segment
				mov es:[bx + 2], ax				;save old cs
				; ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
				;CHANGE 09 INT
				xor bx, bx
				mov es, bx
				mov bx, 4*9						; 09 segment in RAM         

				mov ax, es:[bx]            		;saved old offset interrupt 09
				mov word ptr Old09[0], ax       
				mov ax, offset New09			;load new segment
				mov es:[bx], ax

				mov ax, cs						

				mov dx, es:[bx + 2]
				mov word ptr Old09[2], dx       ;saved old segment
				mov es:[bx + 2], ax				;save old cs                         	
				; ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

				sti:							; (CLOSE)

				mov ax, 3100h					;terminate and stay resident
				mov dx, offset EOP				;EOP - end of programm
				shr dx, 4						;PARAGRAPH store 4 bytes
				inc dx
				int 21h

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;RESIDENT PROGRAMM BODY
;-----------------------------------------------------------------------------------
New08			proc							;resident program

				pusha							;save all regs
				push es ds di cs 
				pop ds

				pusha							;Outregs params
				
				mov al, byte ptr ShowFlag		;check on or off
				cmp al, 0h	
				je @@DelPars

				mov bx, 160 * 2 + 2*57
				mov di, offset SavedBuffer
				mov si, offset DrawBuffer
				mov ax, 9
				mov dx, 10
				push dx ax si di bx
				Call HandleBuffers				;compare VM and Draw Buffer and changes Saved buffer

				mov bx, 160 * 2 + 2*57			;Draw our picture
				mov al, 9
				mov ah, 10
				Call DrwFrm						;draw frame				
				Call OutRegs					;out regs
				mov al, 1h						;ON
				mov byte ptr ShowFlag, al

				mov bx, 160 * 2 + 2*57
				mov ax, 9d
				mov cx, 10d
				mov si, offset DrawBuffer
				push si cx ax bx
				Call CopyFromVM					;REMAKE DRAW BUFFER

				jmp @@Skip

@@DelPars:		add sp, 16						; remove useless params for OutRegs

@@Skip:			pop di ds es					; load saved all regs
				popa	

				db 0eah							; old 09 int
Old08 			dd 0
				iret	
				endp					
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
New09			proc							;resident program

				pusha							;save all regs
				push es ds di cs 
				pop ds

				in al, 60h						;check symbol in 60h port
				cmp al, 58h
				jne @@Skip

				mov al, byte ptr ShowFlag		;change visibility
				cmp al, 1		
				je @@Hide						;Hide it

				mov al, 1
				mov byte ptr ShowFlag, al		;Now we can output our regs
				jmp @@Skip

@@Hide:			xor al, al
				mov byte ptr ShowFlag, al		;Now we can output our regs
				
				mov bx, 160 * 2 + 2*57
				mov ax, 9d
				mov cx, 10d
				mov si, offset SavedBuffer
				push si cx ax bx
				Call CopyToVM					;OUT SAVED BUFFER

@@Skip:			xor ax, ax                      
                in al, 61h                     
                mov ah, al                                                           
            	or al, 80h                      
                out 61h, al                                                      
                mov al, ah                     
                out 61h, al                                                      
                mov al, 20h                     
                out 20h, al                     

				pop di ds es			 		; load saved all regs
				popa	

				db 0eah							; old 09 int
Old09 			dd 0
				iret	
				endp

				include trlt.inc
				include vmutl.inc
				include outregs.inc

;Utils arrays
Troll:			db 16 DUP (30h)
Line:			db 5 DUP (0h)
Num:			dw 3 DUP (0h)
ShowFlag:		db 0h

;BUFFERS
DrawBuffer:		dw 9*10 dup (0h)
SavedBuffer:	dw 9*10 dup (0h)

;REGS LINES
ax_line:		db 'ax '
bx_line:		db 'bx '
cx_line:		db 'cx '
dx_line:		db 'dx '
si_line:		db 'si '
di_line:		db 'di '
bp_line:		db 'bp '
sp_line:		db 'sp '

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
EOP:
end		Start