CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = 

psvn2c_core.c:
	cp ../psvn/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../psvn/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../psvn/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../psvn/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../psvn/global/succ.c
	$(CC) $(OPT) ../psvn/global/succ.c -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~
