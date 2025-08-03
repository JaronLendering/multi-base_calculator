CC = gcc
CFLAGS = -MMD -MP -lm
BLDDIR = build
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BLDDIR)/%.o)

CALCULATOR = $(BLDDIR)/calculator

.PHONY: all

all: $(CALCULATOR) 

$(BLDDIR)/%.o:$(SRCDIR)/%.c
	$(CC) -c $< -o $@

$(CALCULATOR) : $(OBJS) | $(BLDDIR)
	$(CC) $^ -o $@ $(CFLAGS) 


$(BLDDIR):
	mkdir -p $(BLDDIR)

-include $(CALCULATOR).d