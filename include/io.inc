;------------------------------------------------------
;|||||||||||||||||||||||IO|||||||||||||||||||||||||||||
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
		Call OutLine
		Call ClrArr		

		mov ax, word ptr Num[4]
		Call TrToDec
		add di, 80*2
		mov bx, di
		mov si, 16d
		Call OutLine
		Call ClrArr

		mov ax, word ptr Num[4]
		Call TrToBin
		add di, 80*2
		mov bx, di
		mov si, 16d	
		Call OutLine
		Call ClrArr
	 
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;Handle input of the program
;------------------------------------------------------
;	Needs:		none
;	Destroy List:	AX, BX, CX, DX, SI, ES
;	Return:		two numbers in Num[]
;------------------------------------------------------
HandleIn		proc

Call InLine		;Input number in dec
		Call CnvLnDec		;Convert to num LINE array
		mov word ptr Num[0], ax
		Call TrToHex		;translate to ?
		mov bx, 80*2*2+6 	;pos in VM
		mov si, 16d		;max len of line		
		Call OutLine		;print line
		Call ClrArr

		Call InLine
		Call CnvLnDec
		mov word ptr Num[2], ax
		Call TrToHex		
		mov bx, 80*3*2+6 	
		mov si, 16d			
		Call OutLine		
		Call ClrArr

		ret
		endp
;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------