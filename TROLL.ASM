.model tiny
.code
org 100h 

Start:
		mov ah, 01h		;input (in al)
		int 21h

		mov dl, al		;copy into out 

		mov ah, 02h		;sym out
		int 21h

		mov ax, 4c00h		;exit
		int 21h
 
end		Start


