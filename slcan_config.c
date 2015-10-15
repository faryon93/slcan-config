#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>

void print_usage(char *prog)
{
	printf("Usage: %s [options] tty\n\n", prog);
	printf("Options: -s <speed> 	(set CAN speed 0..8)\n");
	printf("\nPossibe baudrates:\n");
	printf("0 = 10 kBaud\n");
	printf("1 = 20 kBaud\n");
	printf("S2 = 50 kBaud\n");
	printf("S3 = 100 kBaud\n");
	printf("S4 = 125 kBaud\n");
	printf("S5 = 250 kBaud\n");
	printf("S6 = 500 kBaud\n");
	printf("S7 = 800 kBaud\n");
	printf("S8 = 1 MBaud\n");
}

int main(int argc, char *argv[])
{
	int opt;
	int bitrate = -1;

	while ((opt = getopt(argc, argv, "s:")) != -1)
	{
		switch (opt)
		{
			case 's':
				bitrate = atoi(optarg);
				break;
		}
	}

	if (argc - optind != 1)
	{
		print_usage(argv[0]);
		return -1;
	}

	// open the tty device
	int fd;
	if ((fd = open(argv[optind], O_WRONLY | O_NOCTTY)) < 0) {
		perror(argv[optind]);
		return -1;
	}

	// configure a new baudrate
	if (bitrate >= 0 && bitrate <= 8) {
		if (ioctl (fd, 22, bitrate) < 0) {
			printf("error: %d\n", errno);
			perror("ioctl SLCAN_SET_BITRT");
			goto err;
		}
	}


	close(fd);
	return 0;

err:
	close(fd);
	return -1;
}
