Test : Test.o Database.o
	g++ -g -o Test Test.o Database.o
Test.o : Test.cpp ../Database.h ../Definition.h
	g++ -c Test.cpp
Database.o : ../Database.cpp ../Database.h ../Definition.h
	g++ -c ../Database.cpp

.PHONY : clean
clean :
	-rm Test Test.o Database.o
	echo -e "TestDatabase\n3\n1\n" > TestDatabase.gwdb-header
	echo "1 0 Query 2 3 1 - QueryNode" > 1.gwdb-data
	echo "2 1 Answer 2 - AnswerNode (Yes)" >> 1.gwdb-data
	echo "3 1 Answer 3 - AnswerNode (No)" >> 1.gwdb-data