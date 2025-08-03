CC = gcc
SRCS = $(wildcard src/*.c)
BLDFLDR = build/
CALCULATOR = $(BLDFLDR)calculator

.PHONY: all

all: $(CALCULATOR) 

$(CALCULATOR) : $(SRCS) 
	mkdir -p build
	$(CC) $^ -o $@