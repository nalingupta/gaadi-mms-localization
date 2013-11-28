main: main.o vn200.o vncp_services.o MadgwickAHRS.o
	gcc -pthread -o main main.o vn200.o vncp_services.o MadgwickAHRS.o -lrt -lm

main.o: main.c
	gcc -c -Wall -I../vectorNav/include main.c
	
vn200.o: ../vectorNav/src/vn200.c
	gcc -c -I../vectorNav/include ../vectorNav/src/vn200.c

vncp_services.o: ../vectorNav/src/arch/linux/vncp_services.c
	gcc -c -I../vectorNav/include ../vectorNav/src/arch/linux/vncp_services.c

MadgwickAHRS.o: ./MadgwickAHRS.c
	gcc -c ./MadgwickAHRS.c

clean:
	rm -rf *o main