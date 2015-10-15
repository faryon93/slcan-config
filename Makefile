all: slcan_config.c
	gcc -O2 --std=gnu99 -o slcan_config $<
