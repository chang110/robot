#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "motor_ctl.h"


static int stop_signal = 1;
void signal_handler(int signo)
{
    stop_signal = 0;
}
int main(int argc, char *argv[])
{
    signal(SIGINT, signal_handler);
    int iRet = motor_ctl_init();
    if (iRet != 0)
    {
        printf("motor_ctl_init failed\n");
        return -1;
    }
    enable_motor(0);

    while (stop_signal)
    {
        sleep(1);
    }

    motor_ctl_deinit();
    printf("exit\n");
    
}