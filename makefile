proj1: ui.o db.o io.o
	cc -o proj1 ui.o db.o io.o 

ui.o: ui.c record.h recfunctions.h  
	cc -c -strict ui.c

db.o: db.c record.h recfunctions.h 
	cc -c -strict db.c

io.o: io.c record.h recfunctions.h
	cc -c -strict io.c

clean: 
	rm proj1 ui.o db.o io.o 
