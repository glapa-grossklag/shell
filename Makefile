SRC    = $(wildcard *.c)
OBJ    = $(SRC:%.c=%.o)
BIN    = shell

CC     = gcc
CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=c11
LFLAGS =

.PHONY: all
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

.PHONY: tidy
tidy:
	rm -f $(OBJ)

.PHONY: clean
clean: tidy
	rm -f $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
