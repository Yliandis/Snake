CC = g++
EXEC = Snake
FLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
STD = -std=c++17
S = src
O = obj
B = bin

all: $(O) $(B) $(O)/main.o
	$(CC) $(O)/*.o -o $(B)/$(EXEC) $(LIBS)

$(O)/main.o: $(O)/Game.o
	$(CC) $(S)/main.cpp -c -o $(O)/main.o $(STD) $(FLAGS)

$(O)/Game.o: $(O)/World.o
	$(CC) $(S)/Game.cpp -c -o $(O)/Game.o $(STD) $(FLAGS)

$(O)/World.o: $(O)/Snake.o
	$(CC) $(S)/World.cpp -c -o $(O)/World.o $(STD) $(FLAGS)

$(O)/Snake.o:
	$(CC) $(S)/Snake.cpp -c -o $(O)/Snake.o $(STD) $(FLAGS)

clean: $(O) $(B)
	rm -r $(O)
	rm -r $(B)

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)
