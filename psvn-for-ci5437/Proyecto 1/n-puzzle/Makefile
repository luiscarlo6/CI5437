CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backwards_moves --fwd_history_len=0

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

ucsDDD.cpp:
	cp ../codes/ucsDDD.cpp ./ucsDDD.cpp

dfid.cpp:
	cp ../codes/dfid.cpp ./dfid.cpp

dfucs.cpp:
	cp ../codes/dfucs.cpp ./dfucs.cpp

IDA*.cpp:
	cp ../codes/IDA*.cpp ./IDA*.cpp

manhattan.cpp:
	cp ../codes/manhattan.cpp ./manhattan.cpp

%.c: %.psvn  psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../psvn2c  $(PSVNOPT) --name=$(*F)  < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

%.c: %.psvn
	../psvn2c $(PSVNOPT) --name=$(*F)  < $< > $@

.PRECIOUS: %.c

psvn.cpp:
	cp ../../psvn.cpp ./psvn.cpp

psvn.hpp:
	cp ../../psvn.hpp ./psvn.hpp

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

%.ucsDDD: %.c ucsDDD.cpp priority_queue.hpp
	$(CXX) $(OPT) ucsDDD.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.dfid: %.c dfid.cpp priority_queue.hpp
	$(CXX) $(OPT) dfid.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.dfucs: %.c dfucs.cpp priority_queue.hpp
	$(CXX) $(OPT) dfucs.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

%.IDA*: %.c IDA*.cpp priority_queue.hpp
	$(CXX) $(OPT) IDA*.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

abstractor: abstractor.cpp psvn.cpp psvn.hpp
	$(CXX) $(OPT) abstractor.cpp psvn.cpp -o $@
	rm -f ./psvn.cpp ./psvn.hpp

%.manhattan: %.c manhattan.cpp priority_queue.hpp
	$(CXX) $(OPT) manhattan.cpp -include $< -o $@
	rm -f ./priority_queue.hpp

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
	rm -f dist.cpp bfsDDD.cpp ucsDDD.cpp dfid.cpp dfucs.cpp distSummary.cpp searchTree.cpp *.dist *.distSummary *.searchTree *.bfsDDD *.ucsDDD *.dfid *.o  priority_queue.hpp psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c IDA*.cpp manhattan.cpp psvn2c_abstraction.c absname.psvn absname.abst absname.state_map absname.c abstractor *~
