CC=g++
CFLAGS=-Wall

EXEC=main.exe

all: $(EXEC)

$(EXEC): main.cpp calculator.cpp calculator.hpp
	$(CC) $(CFLAGS) -o $(EXEC) main.cpp calculator.cpp

clean:
	rm -f main.exe