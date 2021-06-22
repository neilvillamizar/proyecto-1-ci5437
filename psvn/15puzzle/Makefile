# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=0

psvn2c_core.c:
	@cp ../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp ../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp ../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@echo "**** Constructing $@ ..."
	@../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../global/succ.c
	@echo "**** Constructing $@ ..."
	@$(CC) $(OPT) ../global/succ.c -include $< -o $@
	@rm -f $*.c

%.dist: %.c ../global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c ../global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c ../global/generator.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) ../src/abstractor.cpp ../src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `basename $*`.abst `basename $*`.pdb `basename $*`.psvn
	@echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	@./abstractor ../../puzzles/15puzzle.psvn `basename $*` < `basename $*`.txt > /dev/null
	@make `basename $*`.distSummary
	@echo "**** Constructing PDB `basename $*`.pdb ..."
	@./`basename $*`.distSummary `basename $*`.pdb
	@rm -f abstractor `basename $*`.distSummary

%.dist_pdb: %.c ../global/dist_pdb.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../global/dist_pdb.cpp -include $< -o $@
	@rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~
