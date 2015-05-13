# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
absname = absname
PSVNOPT = #--fwd_history_len=3 --bwd_history_len=0  --backwards_moves --state_map

psvn2c_core.c:
	cp ../psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn  psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../psvn2c  $(PSVNOPT) --name=$(*F)  < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c


%.c: %.psvn
	../psvn2c $(PSVNOPT) --name=$(*F)  < $< > $@

.PRECIOUS: %.c

psvn.cpp:
	cp ../psvn.cpp ./psvn.cpp

psvn.hpp:
	cp ../psvn.hpp ./psvn.hpp

priority_queue.hpp:
	cp ../priority_queue.hpp ./priority_queue.hpp

%.distSummary: %.c distSummary.cpp priority_queue.hpp
	$(CXX) $(OPT) distSummary.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.dist:	%.c dist.cpp priority_queue.hpp
	$(CXX) $(OPT) dist.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

abstractor: abstractor.cpp psvn.cpp psvn.hpp
	$(CXX) $(OPT) abstractor.cpp psvn.cpp -o $@
	rm -f ./psvn.cpp ./psvn.hpp

.PRECIOUS: $(absname).abst
.PRECIOUS: $(absname).state_map

.PHONY: pdb
pdb: abstractor
	#rm -f $(absname).abst $(absname).c $(absname).distSummary $(absname).dist $(absname).psvn $(absname).state_map
ifeq ($(strip $(wildcard $(absname).txt)),)
	./abstractor $(ss).psvn $(absname)
else
	./abstractor $(ss).psvn $(absname) < $(absname).txt
endif
	make $(absname).distSummary
	./$(absname).distSummary $(absname).state_map
	make $(absname).dist
	./$(absname).dist

.PHONY: clean
clean:
	rm -f  *.o  psvn.cpp  psvn.hpp psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c absname.psvn absname.abst absname.state_map absname.c abstractor hanoi3_5d.c priority_queue.hpp *.distSummary *.dist *~
