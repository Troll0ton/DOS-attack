;------------------------------------------------------
;|||||||||||||||||TRANSLATIONS|||||||||||||||||||||||||
;------------------------------------------------------
;transform to bin
;------------------------------------------------------
;	Needs:		num in AX
;	Destroy List:	ax, bx, dx
;	Return:		number in array Num
;------------------------------------------------------
TrToBin		proc
		mov bx, ax

		mov ax, bx

		mov bx, 15d
		mov dh, 2d

@@Next:		div dh ; ah = ax mod 2, al = ax div 2
		mov dl, ah
		add dl, 48d
		mov byte ptr Troll[bx], dl  
		xor ah, ah

		dec bx

		mov dh, 2d

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
;	Destroy List:	ax, bx, dx
;	Return:		number in array Num
;------------------------------------------------------
TrToDec		proc


		mov bx, 15d
		mov dh, 10d

@@Next:		div dh ; ah = ax mod 10, al = ax div 10
		mov dl, ah
		add dl, 48d
		mov byte ptr Troll[bx], dl  
		xor ah, ah

		dec bx

		mov dh, 2d

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
;	Destroy List:	ax, bx, dx
;	Return:		number in array Num
;------------------------------------------------------
TrToHex		proc

		mov bx, 15d
		mov dh, 16d

@@Next:		div dh ; ah = ax mod 16, al = ax div 16
		mov dl, ah

		cmp dl, 10d

		jb @@Num
		sub dl, 10d
		add dl, 41h
		jmp @@Skip
@@Num:	add dl, 30h
@@Skip:
		mov byte ptr Troll[bx], dl  
		mov ah, 0h

		dec bx
		mov dh, 16d

		cmp ax, 0h
		jne @@Next
		
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------
;convert line to dec
;------------------------------------------------------
;	IN AX - num
;------------------------------------------------------
CnvLnDec		proc
		
		mov dx, 1d
		xor bx, bx
		mov cx, 5d
		mov si, 4d

@@Next:	
		xor ax, ax	
		mov al, byte ptr Line[si]
		sub al, 48d
		mul dl
		add bx, ax
		
		mov ax, 10d
		mul dl
		mov dx, ax

		dec si

		loop @@Next
		
		mov ax, bx		
		ret
		endp

;------------------------------------------------------
;||||||||||||||||||||||||||||||||||||||||||||||||||||||
;------------------------------------------------------