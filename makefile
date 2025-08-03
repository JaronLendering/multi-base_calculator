CC = gcc
CFLAGS = -MMD -MP -lm
OFLAGS = -Iinclude
BLDDIR = build
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BLDDIR)/%.o)

CALCULATOR = $(BLDDIR)/calculator

.PHONY: all

all: $(CALCULATOR) 

$(BLDDIR)/%.o:$(SRCDIR)/%.c | $(BLDDIR)
	$(CC) $(OFLAGS) -c $< -o $@

$(CALCULATOR) : $(OBJS) 
	$(CC) $^ -o $@ $(CFLAGS) 


$(BLDDIR):
	mkdir -p $(BLDDIR)

-include $(CALCULATOR).d