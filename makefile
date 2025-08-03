CC = gcc
CFLAGS = -MMD -MP
SRCS = $(wildcard src/*.c)
BLDFLDR = build/
CALCULATOR = $(BLDFLDR)calculator

.PHONY: all

all: $(CALCULATOR) 

$(CALCULATOR) : $(SRCS) 
	mkdir -p build
	$(CC) $(CFLAGS) $(SRCS) -o $@

-include $(CALCULATOR).d