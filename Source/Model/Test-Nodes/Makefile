Test : Test.o LogicalNode.o ExtendedNode.o
	g++ -g -o Test Test.o LogicalNode.o ExtendedNode.o

Test.o : Test.cpp ../LogicalNode.h ../ExtendedNode.h
	g++ -c Test.cpp
LogicalNode.o : ../LogicalNode.cpp ../LogicalNode.h
	g++ -c ../LogicalNode.cpp
ExtendedNode.o : ../ExtendedNode.cpp ../ExtendedNode.h
	g++ -c ../ExtendedNode.cpp

.PHONY : clean
clean :
	-rm Test Test.o LogicalNode.o ExtendedNode.o
