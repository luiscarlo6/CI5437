CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --no_abstraction --backwards_moves --fwd_history_len=0

psvn2c_core.c:
	cp ../../psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../psvn2c_abstraction.c ./psvn2c_abstraction.c

dist.cpp:
	cp ../codes/dist.cpp ./dist.cpp

distSummary.cpp:
	cp ../codes/distSummary.cpp ./distSummary.cpp

searchTree.cpp:
	cp ../codes/searchTree.cpp ./searchTree.cpp

bfsDDD.cpp:
	cp ../codes/bfsDDD.cpp ./bfsDDD.cpp

dfid.cpp:
	cp ../codes/dfid.cpp ./dfid.cpp

%.c: %.psvn  psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../psvn2c  $(PSVNOPT) --name=$(*F)  < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

priority_queue.hpp:
	cp ../../priority_queue.hpp ./priority_queue.hpp

%.dist: %.c dist.cpp priority_queue.hpp
	$(CXX) $(OPT) dist.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.distSummary: %.c distSummary.cpp priority_queue.hpp
	$(CXX) $(OPT) distSummary.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.searchTree: %.c searchTree.cpp priority_queue.hpp
	$(CXX) $(OPT) searchTree.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.bfsDDD: %.c bfsDDD.cpp priority_queue.hpp
	$(CXX) $(OPT) bfsDDD.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.dfid: %.c dfid.cpp priority_queue.hpp
	$(CXX) $(OPT) dfid.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

.PHONY: clean
clean:
	rm -f dfid.cpp dist.cpp bfsDDD.cpp distSummary.cpp searchTree.cpp *.dfid *.dist *.distSummary *.searchTree *.bfsDDD *.o  priority_queue.hpp psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *~
