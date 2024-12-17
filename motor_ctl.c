#include <wiringPi.h>
#include <stddef.h>
#include <threads.h>
#include <malloc.h>
#include "config.h"
#include "motor_ctl.h"
#include "pin_list.h"

#define PIN_MOTOR_CTL 1

static int motor_ctl_inited = 0;
static int motor_ctl_state = 0;
static pin_list *motor_ctl_list = NULL;
static thrd_t motor_ctl_thread_id;
static void motor_ctl_isr(void)
{
    if(motor_ctl_list == NULL) return;
    pin_list* temp = motor_ctl_list;
    while (temp != NULL && temp->state) {
        digitalWrite(temp->pin, !digitalRead(temp->pin));
        temp = temp->next;
    }
}

static int motor_ctr_thread(void* arg)
{
    printf("motor_ctl_thread start\n");
    pwmWrite(PIN_MOTOR_CTL, DEFAULT_DUTY);
    while(motor_ctl_state)
    {
        delay(1000);
    }
    pwmWrite(PIN_MOTOR_CTL, 0);
    return 0;
}
int motor_ctl_init(void)
{

    if(motor_ctl_inited) return 0;

    int iret = wiringPiSetup();
    if(iret < 0)
        return -1;
    iret = wiringPiISR(PIN_MOTOR_CTL, INT_EDGE_RISING, &motor_ctl_isr);
    if(iret < 0)
        return -2;

    pinMode(PIN_MOTOR_CTL, PWM_OUTPUT);
    pwmSetClock(MIN_LCK);
    pwmSetRange(DEFAULT_RANGE);
    pwmSetMode(PWM_MODE_MS);

    
    
    motor_ctl_state = 1;
    thrd_create(&motor_ctl_thread_id, motor_ctr_thread, NULL);

    return 0;
}

void motor_ctl_deinit(void)
{
    motor_ctl_state = 0;
    thrd_join(motor_ctl_thread_id, NULL);
    wiringPiISRStop(PIN_MOTOR_CTL);
    pin_list* temp = motor_ctl_list;
    while (temp != NULL) {
        pinMode(temp->pin, INPUT);
        temp = temp->next;
    }
    free_pin_list(&motor_ctl_list);
}

int enable_motor(unsigned int pin)
{
    if(motor_ctl_list == NULL)
    {
        motor_ctl_list = create_pin(pin);
        pinMode(pin,OUTPUT);
    }else
    {
        pin_list* temp = find_pin(&motor_ctl_list, pin);
        if(temp == NULL)
        {
            temp = create_pin(pin);
            pinMode(pin,OUTPUT);
            add_pin(&motor_ctl_list, pin);
        }else{
            temp->state = 1;
        }
    }

    return 0;
}
