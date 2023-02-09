.model tiny
.code
org 100h 

Start:
;-----------------------DEFINE----------------------------

		input   EQU mov ah, 01h
		sym_out EQU mov ah, 02h
		str_out EQU mov ah, 09h
		exit    EQU mov ax, 4C00h

		dos_srv EQU int 21h

;-----------------------PROGRAM---------------------------

		input
		dos_srv

		mov dl, al

		KAB=10h

		sym_out
		dos_srv

		exit
		dos_srv

;---------------------------------------------------------
 
end		Start


