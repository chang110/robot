#ifndef __MOTOR_CTL_H__
#define __MOTOR_CTL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define FREQ_UNCOUNTER          -1

extern int motor_ctl_init(void);
extern void motor_ctl_deinit(void);
extern int enable_motor(unsigned int pin,unsigned int counter);
extern int disable_motor(unsigned int pin);
extern double motor_ctl_get_speed(void);
extern int motor_ctl_set_speed(unsigned int speed);

#ifdef __cplusplus
}
#endif // DEBUG

#endif // !__MOTOR_CTL_H__