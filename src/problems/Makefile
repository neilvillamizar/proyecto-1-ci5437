# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --abstraction

psvn2c_core.c:
	@cp ../../psvn/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp ../../psvn/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp ../../psvn/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@echo "**** Constructing $@ ..."
	@../../psvn/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../../psvn/global/succ.c
	@echo "**** Constructing $@ ..."
	@$(CC) $(OPT) ../../psvn/global/succ.c -include $< -o $@
	@rm -f $*.c

%.dist: %.c ../../psvn/global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../psvn/global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c ../../psvn/global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../psvn/global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c ../../psvn/global/generator.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../psvn/global/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) ../../psvn/src/abstractor.cpp ../../psvn/src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f heuristics/$*.abst heuristics/$*.pdb heuristics/$*.psvn
	@echo "**** Running abstractor on source/`dirname $*`.psvn with heuristics/$*.txt ..."
	@./abstractor source/`dirname $*`.psvn heuristics/$* < heuristics/$*.txt > /dev/null
	@make heuristics/$*.distSummary
	@echo "**** Constructing PDB heuristics/$*.pdb ..."
	@./heuristics/$*.distSummary heuristics/$*.pdb
	@rm -f abstractor heuristics/$*.distSummary

%.dist_pdb: %.c ../../psvn/global/dist_pdb.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../psvn/global/dist_pdb.cpp -include $< -o $@
	@rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~
