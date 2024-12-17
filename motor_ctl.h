#ifndef __MOTOR_CTL_H__
#define __MOTOR_CTL_H__

#ifdef __cplusplus
extern "C" {
#endif

extern int motor_ctl_init(void);
extern void motor_ctl_deinit(void);
extern int enable_motor(unsigned int pin);

#ifdef __cplusplus
}
#endif // DEBUG

#endif // !__MOTOR_CTL_H__