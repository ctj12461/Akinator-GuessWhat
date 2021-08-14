controllerObjects = Main.o GameChecker.o GameController.o
modelObjects = LogicalNode.o ExtendedNode.o Network.o NodePool.o Database.o
viewObjects = InputBox.o Menu.o UserInterface.o

GuessWhat : $(controllerObjects) $(modelObjects) $(viewObjects)
	g++ -o GuessWhat $(controllerObjects) $(modelObjects) $(viewObjects)

# Controller Part
Main.o : Main.cpp GameChecker.h GameController.h
	g++ -c Main.cpp
GameChecker.o : GameChecker.cpp GameChecker.h
	g++ -c GameChecker.cpp
GameController.o : GameController.cpp GameController.h
	g++ -c GameController.cpp

# Model Part
LogicalNode.o : ./Model/LogicalNode.cpp ./Model/LogicalNode.h ./Model/Definition.h
	g++ -c ./Model/LogicalNode.cpp
ExtendedNode.o : ./Model/ExtendedNode.cpp ./Model/ExtendedNode.h ./Model/LogicalNode.h ./Model/Definition.h
	g++ -c ./Model/ExtendedNode.cpp
Network.o : ./Model/Network.cpp ./Model/Network.h ./Model/LogicalNode.h ./Model/ExtendedNode.h \
		./Model/NodePool.h ./Model/Definition.h
	g++ -c ./Model/Network.cpp
NodePool.o : ./Model/NodePool.h ./Model/LogicalNode.h ./Model/ExtendedNode.h \
		./Model/Database.h ./Model/Definition.h
	g++ -c ./Model/NodePool.cpp
Database.o: ./Model/Database.cpp ./Model/Database.h ./Model/Definition.h
	g++ -c ./Model/Database.cpp

# View Part
InputBox.o : ./View/InputBox.cpp ./View/InputBox.h
	g++ -c ./View/InputBox.cpp
Menu.o : ./View/Menu.cpp ./View/Menu.h
	g++ -c ./View/Menu.cpp
UserInterface.o : ./View/UserInterface.cpp ./View/UserInterface.h
	g++ -c ./View/UserInterface.cpp

.PHONY : clean
clean :
	-rm GuessWhat $(controllerObjects) $(modelObjects) $(viewObjects)
# 	-rm GuessWhat.config
# 	-rm -rf DefaultDatabase
