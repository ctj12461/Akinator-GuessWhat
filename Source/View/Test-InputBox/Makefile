Test : Test.o InputBox.o
	g++ -g -o Test Test.o InputBox.o
Test.o : Test.cpp ../Menu.h
	g++ -g -c Test.cpp
InputBox.o : ../InputBox.cpp ../InputBox.h
	g++ -g -c ../InputBox.cpp

.PHONY : clean
clean :
	-rm Test Test.o InputBox.o