CC = gcc
CFLAGS = -Wall -Wextra -O2

ifeq ($(OS),Windows_NT)
    RM = cmd /C del
    EXE = .exe
    MAIN_SRC = main_win.c
else
    RM = rm -f
    EXE = 
    MAIN_SRC = main_linux.c
endif

TARGET = game$(EXE)
SOURCES = $(MAIN_SRC)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
