#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>

#define SLCAN_SET_BITRT	22

void print_usage()
{
	printf("./bitrate <tty> <1..8>\n");
	printf("0 = 10 kBaud\n1 = 20 kBaud\nS2 = 50 kBaud\nS3 = 100 kBaud\nS4 = 125 kBaud\nS5 = 250 kBaud\nS6 = 500 kBaud\nS7 = 800 kBaud\nS8 = 1 MBaud\n");
}

int main(int argc, char *argv[])
{
	int opt;
	int bitrate = -1;
	int real_bitrate = 0;

	while ((opt = getopt(argc, argv, "s:B:")) != -1)
	{
		switch (opt)
		{
			case 's':
				bitrate = atoi(optarg);
				break;
			case 'B':
				real_bitrate = atoi(optarg);
				break;
		}
	}

	if (real_bitrate > 0 && real_bitrate <= 1000000)
	{
		// open the tty device
                int fd;
                if ((fd = open(argv[optind], O_WRONLY | O_NOCTTY)) < 0) {
                        perror(argv[optind]);
                        exit(1);
                }

                // issue the set bitrate ioctl command
                printf("setting real bitrate to %d\n", real_bitrate);
                if (ioctl (fd, 23, real_bitrate) < 0) {
                        printf("error: %d\n", errno);
                        perror("ioctl SLCAN_SET_BITRT");
                        exit(1);
                }

                close(fd);

                return 0;
	}

	if (bitrate >= 0 && bitrate <= 8)
	{
		// open the tty device
		int fd;
		if ((fd = open(argv[optind], O_WRONLY | O_NOCTTY)) < 0) {
			perror(argv[optind]);
			exit(1);
		}

		// issue the set bitrate ioctl command
		printf("setting bitrate to %d\n", bitrate);
		if (ioctl (fd, 22, bitrate) < 0) {
			printf("error: %d\n", errno);
			perror("ioctl SLCAN_SET_BITRT");
			exit(1);
		}

		close(fd);

		return 0;
	}
	
	return -1;
}
