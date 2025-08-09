CC = gcc
CFLAGS = -MMD -MP -lm
OFLAGS = -Iinclude
BLDDIR = build
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BLDDIR)/%.o)
INSTALLDIR = /home/jaron/bin
CALCULATOR = $(BLDDIR)/calculator

.PHONY: all install uninstall

all: $(CALCULATOR) 

install: 
	cp $(CALCULATOR) $(INSTALLDIR)
	
uninstall:
	rm $(INSTALLDIR)/calculator

$(BLDDIR)/%.o:$(SRCDIR)/%.c | $(BLDDIR)
	$(CC) $(OFLAGS) -c $< -o $@

$(CALCULATOR) : $(OBJS) 
	$(CC) $^ -o $@ $(CFLAGS) 


$(BLDDIR):
	mkdir -p $(BLDDIR)

-include $(CALCULATOR).d