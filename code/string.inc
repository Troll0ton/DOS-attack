;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||STRING FUNCTIONS||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;	     			USING STDCALL CALLING CONVENSION
;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						strlen
;-----------------------------------------------------------------------------------
;	Needs:  (STACK) {line ptr (use LEA for getting it)}
;	Destroy List:	AX, BX, CX
;	Return:		line length in AX
;-----------------------------------------------------------------------------------
StrLen		proc
		push bp		;PROLOGUE
		mov bp, sp

		mov bx, [bp + 4]	;getting arguments

		xor ax, ax

@@Next:	inc ax
		mov cl, [bx]	
		inc bx		
		cmp cl, 24h		;compare it with $ - end of line

		jne @@Next

		dec ax

		pop bp		;EPILOGUE
	 
		ret 2
		endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						memchr
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {line ptr (use LEA for getting it),
;				wanted symbol,
;				length of the line}
;	Destroy List:	AX, BX, CX
;	Return:		pointer to symbol in BX
;
;	(IF THERE IS NO SUCH SYMBOL IN THIS LINE IT RETURN NULL PTR)
;
;-----------------------------------------------------------------------------------
MemChr		proc
		push bp		;PROLOGUE
		mov bp, sp

		mov bx, [bp + 4]	;getting arguments
		mov ax, [bp + 6]
		mov cx, [bp + 8]

@@Next:	mov ah, [bx]	;getting curr symbol
		inc bx			
		cmp al, ah		;compare it with symbol

		je @@Meet		;meeting symbol occasion

		Loop @@Next

		mov bx, 1h

@@Meet:	dec bx		;save curr pos

		pop bp		;EPILOGUE
	 
		ret 6
	 
		endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						strchr
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {line ptr (use LEA for getting it),
;				wanted symbol}
;	Destroy List:	AX, BX
;	Return:		pointer to symbol in BX
;
;	(IF THERE IS NO SUCH SYMBOL IN THIS LINE IT RETURN NULL PTR)
;
;-----------------------------------------------------------------------------------
StrChr		proc
		push bp		;PROLOGUE
		mov bp, sp

		mov bx, [bp + 4]	;getting arguments
		mov ax, [bp + 6]
		

@@Next:	mov ah, [bx]	;get curr symbol
		inc bx
		cmp ah, al		;compare it with symbol

		je @@Skip		;meeting symbol occasion

		cmp ah, 24h		;find out end of string

		jne @@Next

		mov bx, 1h

@@Skip:	dec bx		;save curr pos in line

		pop bp		;EPILOGUE
	 
		ret 4
		endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						memcpy
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {dest  ptr (use LEA for getting it),
;				sours ptr (use LEA for getting it),
;				size}
;	Destroy List:	AX, BX, CX, DX
;	Return:		none
;
;-----------------------------------------------------------------------------------
MemCpy		proc
		push bp		;PROLOGUE
		mov bp, sp

		;getting arguments

		mov ax, [bp + 4]	;destination	
		mov bx, [bp + 6]  ;src
 		mov cx, [bp + 8]	;size
		
		xor dx, dx
		

@@Next:	mov dl, byte ptr [bx]	;get byte from src

		xchg ax, bx

		mov byte ptr [bx], dl	;save it in destination

		xchg ax, bx

		inc ax
		inc bx

		Loop @@Next

		pop bp		;EPILOGUE
	 
		ret 6
		endp


;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						strcpy
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {dest  ptr (use LEA for getting it),
;				sours ptr (use LEA for getting it}
;	Destroy List:	AX, BX, DX
;	Return:		none
;
;-----------------------------------------------------------------------------------
StrCpy		proc
		push bp		;PROLOGUE
		mov bp, sp

		;getting arguments

		mov ax, [bp + 4]	;destination	
		mov bx, [bp + 6]  ;src
		
		xor dx, dx
		

@@Next:	mov dl, byte ptr [bx]	;get byte from src

		xchg ax, bx

		mov byte ptr [bx], dl	;save it in destination

		xchg ax, bx

		inc ax
		inc bx

		cmp dl, 24h		;find out the end of the line	
	
		jne @@Next

		pop bp		;EPILOGUE
	 
		ret 4
		endp


;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						memmove
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {dest  ptr (use LEA for getting it),
;				sours ptr (use LEA for getting it),
;				size}
;	Destroy List:	AX, BX, CX, DX, SI
;	Return:		none
;
;-----------------------------------------------------------------------------------
MemMove		proc
		push bp		;PROLOGUE
		mov bp, sp

		;getting arguments

		mov ax, [bp + 4]	;destination	
		mov bx, [bp + 6]  ;src
 		mov cx, [bp + 8]	;size
			
		mov dx, cx		;save counter

		xor si, si

@@Create:	push si		;create space to tmp array
		Loop @@Create

		mov cx, dx		;rebuild counter		
		xor dx, dx
		mov si, bp
		sub bp, 2d
		
@@Next1:	mov dl, byte ptr [bx]		;get byte from src
		mov word ptr [bp], dx		;save it in tmp array
		inc bx
		sub bp, 2d
		Loop @@Next1

		mov cx, si
		sub cx, bp
		shr cx, 1d

		mov bp, si
		sub bp, 2d

		mov bx, ax
		
@@Next2:	mov dx, word ptr [bp]		;get byte from tmp array
		mov byte ptr [bx], dl		;save it in destination
		inc bx
		sub bp, 2d
		Loop @@Next2

		mov bp, si

		add bp, 2

		mov sp, bp	;EPILOGUE
	 
		ret 6
		endp


;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						memcmp
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {lhs ptr (use LEA for getting it),
;				rhs ptr (use LEA for getting it),
;				size}
;	Destroy List:	AX, BX, CX, DX
;	Return:		ax: 1 - equal, 0 - not equal
;
;-----------------------------------------------------------------------------------
MemCmp		proc
		push bp		;PROLOGUE
		mov bp, sp

		;getting arguments

		mov ax, [bp + 4]	;lhs	
		mov bx, [bp + 6]  ;rhs
		mov cx, [bp + 8]  ;size
		
		xor dx, dx
		

@@Next:	mov dl, byte ptr [bx]
		xchg ax, bx
		mov dh, byte ptr [bx]
		xchg ax, bx
		inc ax
		inc bx

		cmp dl, dh		;compare symbols
		mov dx, 0h				
		jne @@Miss
		Loop @@Next

		mov dx, 1h

@@Miss:	mov ax, dx		;return value

		pop bp		;EPILOGUE
	 
		ret 6
		endp


;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						strcmp
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {lhs ptr (use LEA for getting it),
;				rhs ptr (use LEA for getting it)}
;	Destroy List:	AX, BX, DX
;	Return:		ax: 1 - equal, 0 - not equal
;
;-----------------------------------------------------------------------------------
StrCmp		proc
		push bp		;PROLOGUE
		mov bp, sp

		;getting arguments

		mov ax, [bp + 4]	;lhs	
		mov bx, [bp + 6]  ;rhs

		;local data

		push cx	;save CX val
		
		xor dx, dx
		

@@Next:	mov dl, byte ptr [bx]
		xchg ax, bx
		mov dh, byte ptr [bx]
		xchg ax, bx
		inc ax
		inc bx		

		cmp dh, 24h		;find out the end of the line
		je @@Skip

		cmp dl, 24h		;find out the end of the line
		je @@Skip

		cmp dl, dh		;compare 2 symmbols
		mov dx, 1h				
		jne @@Miss

		jmp @@Next

@@Skip:	mov dx, 0h

@@Miss:	mov ax, dx		;return value

		mov cx, [bp - 2]	;get saved value of CX

		mov sp, bp	;EPILOGUE	
		pop bp	
	 
		ret 4
		endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------
;						StrStr
;-----------------------------------------------------------------------------------
;	Needs:   (STACK) {str ptr (use LEA for getting it),
;				substr ptr (use LEA for getting it)}
;	Destroy List:	AX, BX, CX, DX, SI, DI 
;	Return:		ax: ptr to first meet of substrin str
;-----------------------------------------------------------------------------------
StrStr		proc
		push bp		;PROLOGUE
		mov bp, sp

		;getting arguments

		mov di, [bp + 4]	;get str
		mov si, [bp + 6]	;get substr

		push di		;push str ptr
		Call StrLen 	;Find len of str

		mov cx, ax		;Save length

@@Next:	push di		;push str ptr
		push si		;push substr ptr

		Call StrCmp		;this funct save CX reg
		
		xor dx, dx
		cmp ax, dx		;find out the result of strcmp
		mov ax, 0h

		je @@Find

		inc di

		Loop @@Next

		mov di, 0h

@@Find:	mov ax, di		;return pos in str 

		mov sp, bp	;EPILOGUE	
		pop bp
	 
		ret 4
		endp

;-----------------------------------------------------------------------------------
;|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
;-----------------------------------------------------------------------------------