/*
 * SERVO_MOTOR_interface.h
 *
 * Created: 10/19/2026 2:41:07 AM
 *  Author: East-Sound
 */ 


#ifndef SERVO_MOTOR_INTERFACE_H_
#define SERVO_MOTOR_INTERFACE_H_

void SERVOMOTOR_voidInit(void);
void SERVOMOTOR_voidSetAngleWithFreq(u16 copy_u16Frequency, s16 copy_s16Angle , u16 copy_u16MinControlPulseMicroSec, u16 copy_u16MaxControlPulseMicroSec);


#endif /* SERVO_MOTOR_INTERFACE_H_ */