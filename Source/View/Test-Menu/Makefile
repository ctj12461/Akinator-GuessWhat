Test : Test.o Menu.o
	g++ -g -o Test Test.o Menu.o
Test.o : Test.cpp ../Menu.h
	g++ -g -c Test.cpp
Menu.o : ../Menu.cpp ../Menu.h
	g++ -g -c ../Menu.cpp

.PHONY : clean
clean :
	-rm Test Test.o Menu.o