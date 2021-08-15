Test : Test.o NodePool.o Database.o LogicalNode.o ExtendedNode.o
	g++ -g -o Test Test.o NodePool.o Database.o LogicalNode.o ExtendedNode.o
Test.o : Test.cpp ../Definition.h ../NodePool.h ../Database.h ../LogicalNode.h ../ExtendedNode.h
	g++ -g -c Test.cpp
NodePool.o : ../NodePool.cpp ../Definition.h ../NodePool.h ../Database.h ../LogicalNode.h ../ExtendedNode.h
	g++ -g -c ../NodePool.cpp
Database.o : ../Database.cpp ../Database.h ../Definition.h
	g++ -g -c ../Database.cpp
LogicalNode.o : ../LogicalNode.cpp ../LogicalNode.h
	g++ -g -c ../LogicalNode.cpp
ExtendedNode.o : ../ExtendedNode.cpp ../ExtendedNode.h
	g++ -g -c ../ExtendedNode.cpp

.PHONY : clean
clean :
	-rm Test Test.o NodePool.o Database.o LogicalNode.o ExtendedNode.o
	-rm TestDatabase/TestDatabase.gwdb-header TestDatabase/1.gwdb-data TestDatabase/2.gwdb-data
	echo -e "TestDatabase\n3\n1\n" > TestDatabase/TestDatabase.gwdb-header
	echo "1 0 Query 2 3 1 - QueryNode" > TestDatabase/1.gwdb-data
	echo "2 1 Answer 2 - AnswerNode (Yes)" >> TestDatabase/1.gwdb-data
	echo "3 1 Answer 3 - AnswerNode (No)" >> TestDatabase/1.gwdb-data