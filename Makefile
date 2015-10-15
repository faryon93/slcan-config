BINARY = slcan_config

all: slcan_config.c
	gcc -O2 --std=gnu99 -o $(BINARY) $<

install: all install-header
	cp -n $(BINARY) /usr/local/bin/

install-header: slcan.h
	cp -n $< /usr/local/include/

clean: 
	rm $(BINARY)