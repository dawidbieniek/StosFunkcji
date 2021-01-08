a.out: main.o parser.o alex.o printer.o fun_stack.o kontener.o
	cc main.o parser.o alex.o printer.o fun_stack.o kontener.o -Wall -pedantic -ansi

main.o: parser.h printer.h kontener.h
parser.o: parser.h alex.h fun_stack.h kontener.h 	
alex.o: alex.h fun_stack.h
printer.o: printer.h kontener.h 
fun_stack.o: fun_stack.h
kontener.o: kontener.h
	
