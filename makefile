chklinks: chklinks.o syscalls.o helpMethods.o syscalls.h
	gcc -g -lcurl -o chkLinks chklinks.o syscalls.o helpMethods.o

helpMethods.o: helpMethods.c syscalls.h
	gcc -g -c -Wall -Wextra -Wwrite-strings helpMethods.c

syscalls.o: syscalls.c syscalls.h
	gcc -g -c -Wall -Wextra -Wwrite-strings syscalls.c

chklinks.o: chklinks.c syscalls.h
	gcc -g -c -Wall -Wextra -Wwrite-strings chklinks.c

clean:
	rm -f *.o
	rm chkLinks
