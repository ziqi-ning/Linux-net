# Makefile
#

#CROSS_COMPILE = arm-linux-gnu-

CC = $(CROSS_COMPILE)gcc

ifdef CROSS_COMPILE
TARGET = /opt/filesystem
endif


#DEBUG = -g -O0 -Wall
DEBUG = -g -O2
CFLAGS += $(DEBUG)

PROGS = ${patsubst %.c, %, ${wildcard *.c}} 

all : $(PROGS)

install: $(PROGS)
ifdef CROSS_COMPILE
	mkdir $(TARGET)/root/long_term/networks -p
	cp $(PROGS) $(TARGET)/root/long_term/networks -f
endif
% : %.c
	$(CC)  $(CFLAGS)   -o $@ $< -lpthread

.PHONY: uninstall clean dist

uninstall :
ifdef CROSS_COMPILE
	cd $(TARGET)/root/long_term/networks && rm -f $(PROGS)
endif

clean : uninstall
	- rm -f $(PROGS) core *.gz

dist: clean
	tar czf ../farsight_network_2nd_tcp_thread_for_1603.tar.gz ../tcp_thread_demo
	
