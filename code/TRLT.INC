;------------------------------------------------------
;|||||||||||||||||TRANSLATIONS|||||||||||||||||||||||||
;------------------------------------------------------
;Handle input of the program
;------------------------------------------------------
;	Needs:		input your number (00002 for example)
;	Destroy List:	AX, BX, CX, DX, SI, ES
;	Return:		two numbers in Num[]
;------------------------------------------------------
HandleIn		proc

		Call InLine		;Input number in dec
		Call CnvLnDec		;Convert to num LINE array
		mov word ptr Num[0], ax
		Call TrToHex		;translate to hex
		mov bx, 80*2*2+6 	;pos in VM
		mov si, 16d			;max len of line
		mov cx, si
		mov si, offset Troll		
		Call OutLine		;print line
		Call ClrArr

		Call InLine
		Call CnvLnDec
		mov word ptr Num[2], ax
		Call TrToHex		
		mov bx, 80*3*2+6 	
		mov si, 16d			
		mov cx, si
		mov si, offset Troll
		Call OutLine		
		Call ClrArr

		ret
		endp
;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;transform to bin
;------------------------------------------------------
;	Needs:		num in AX
;	Destroy List:	ax, bx, dx
;	Return:		number in array Num
;------------------------------------------------------
TrToBin		proc
		mov bx, 15d	; it is length of out line

@@Next:	mov dx, ax	
		and dx, 1d	; dl = ax % 2
		shr ax, 1d	; ax = ax / 2

		add dx, 48d	;transform to "char"
		mov byte ptr Troll[bx], dl  ;saved into line

		dec bx	;move to next num

		cmp ax, 0h
		jne @@Next
	 
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;transform to dec
;------------------------------------------------------
;	Needs:		num in AX
;	Destroy List:	AX, BX, DX, SI
;	Return:		number in array Troll
;------------------------------------------------------
TrToDec		proc
		mov si, 15d		; line length
		mov bx, 10d		

@@Next:	xor dx, dx	
		div bx 		; AX = DX_AX / BX, DX = DX_AX % BX 

		add dx, 48d
		mov byte ptr Troll[si], dl  ; save sym

		dec si		; move to next sym

		cmp ax, 0h
		jne @@Next
	 
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;transform to hex
;------------------------------------------------------
;	Needs:		num in AX
;	Destroy List:	AX, BX, DX
;	Return:		number in array Troll
;------------------------------------------------------
TrToHex		proc

		mov bx, 15d

@@Next:	mov dx, ax  ; dx = ax % 16
		and dx, 0Fh	; mask

		shr ax, 4d	; ax = ax / 16

		cmp dl, 10d
		jb @@Num	; consider num, sym cases
 				
		add dx, 55d ; to sym
		jmp @@Skip

@@Num:	add dx, 30h	; to num

@@Skip:	mov byte ptr Troll[bx], dl  ; save sym
		dec bx
		cmp ax, 0h
		jne @@Next
		
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;convert line to dec
;------------------------------------------------------
;	Needs:		num in Line
;	Destroy List:	AX, BX, CX, DX, SI
;	Return:		num in AX
;------------------------------------------------------
CnvLnDec		proc
		
		mov dx, 1d	; 10^x
		xor bx, bx	; result num
		mov cx, 5d	; counters
		mov si, 4d	

@@Next:	xor ax, ax	
		mov al, byte ptr Line[si]
		sub al, 48d	; transform to num
		mul dl	; al = al * 10^x
		add bx, ax	
		
		mov ax, 10d
		mul dl
		mov dx, ax	; dx = dx * 10 (dx = 10^x)

		dec si

		loop @@Next
		
		mov ax, bx		
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;Print result in different calc systems
;------------------------------------------------------
;	Needs:		num in Num[4], position in DI
;	Destroy List:	AX, BX, CX, DX, SI, ES, DI
;	Return:		none
;------------------------------------------------------
PrntRes		proc
		
		mov ax, word ptr Num[4]
		Call TrToHex		
		mov bx, di 	
		mov si, 16d	
		mov cx, si
		mov si, offset Troll			
		Call OutLine
		Call ClrArr		

		mov ax, word ptr Num[4]
		Call TrToDec
		add di, 80*2
		mov bx, di
		mov si, 16d
		mov cx, si
		mov si, offset Troll
		Call OutLine
		Call ClrArr

		mov ax, word ptr Num[4]
		Call TrToBin
		add di, 80*2
		mov bx, di
		mov si, 16d	
		mov cx, si
		mov si, offset Troll
		Call OutLine
		Call ClrArr
	 
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------