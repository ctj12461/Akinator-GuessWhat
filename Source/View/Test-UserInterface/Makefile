Test : Test.o UserInterface.o Menu.o InputBox.o
	g++ -g -o Test Test.o UserInterface.o Menu.o InputBox.o
Test.o : Test.cpp ../Menu.h
	g++ -g -c Test.cpp
UserInterface.o : ../UserInterface.cpp ../UserInterface.h
	g++ -g -c ../UserInterface.cpp
Menu.o : ../Menu.cpp ../Menu.h
	g++ -g -c ../Menu.cpp
InputBox.o : ../InputBox.cpp ../InputBox.h
	g++ -g -c ../InputBox.cpp

.PHONY : clean
clean :
	-rm Test Test.o UserInterface.o