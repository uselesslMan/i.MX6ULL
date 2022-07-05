#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

const char default_path[] = "/dev/input/by-path/platform-sgpio-keys-event";

int main(int argc, char *argv[])
{
    int fd;
    struct input_event event;
    char *path;

    printf("This is a input device demo. \n");

    if (argc > 1)
        path = argv[1];
    else
        path = (char *)default_path;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        printf("Fail to open device: %s .\n"
               "please confirm the path or you have permission to do this.\n",
               path);
        exit(1);
    }
    printf("Test device: %s.\nWaiting for input...\n", path);

    while (1)
    {
        if (read(fd, &event, sizeof(event)) == sizeof(event))
            if (event.type != EV_SYN)
            {
                printf("Event: time %ld.%ld, type %d, code %d, value %d\n",
                       event.time.tv_sec, event.time.tv_usec,
                       event.type,
                       event.code,
                       event.value);
            }
    }
    close(fd);
    return 0;
}