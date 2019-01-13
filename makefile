docteur.o : docteur.c docteur.h
	gcc -Wall -c docteur.c

patient.o : patient.c patient.h docteur.o
	gcc -Wall -c patient.c

fileattente.o : fileattente.c fileattente.h
	gcc -Wall -c fileattente.c

pathologie.o : pathologie.c pathologie.h
	gcc -Wall -c pathologie.c

main.o : main.c pathologie.o fileattente.o patient.o docteur.o
	gcc -Wall -c main.c

compile : main.o pathologie.o fileattente.o patient.o docteur.o
	gcc -Wall -o hopital main.o pathologie.o fileattente.o patient.o docteur.o