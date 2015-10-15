all: slcan_config.c
	gcc --std=gnu99 -o slcan_config $<