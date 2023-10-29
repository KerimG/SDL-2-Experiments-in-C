TARGET := main
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic $(shell pkg-config --cflags --libs sdl2)

.PHONY: all clean run

all: $(TARGET)

$(target): main.c
	gcc -o $(TARGET) $(TARGET).c $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run:
	./$(TARGET)

