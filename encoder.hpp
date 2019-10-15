/*
 * encoder.hpp
 *
 *  Created on: 2018/09/03
 *      Author: Sekiguchi Takuya
 *  changed on:2019/06
 *     changer: Satoshi Ohya
 *
 */

#ifndef APPLICATION_USER_ENCODER_HPP_
#define APPLICATION_USER_ENCODER_HPP_

#include<stdint.h>
#include"tim.h"

class Encoder{
public:

	Encoder(TIM_HandleTypeDef *timer);
	void init();
	void start();
	void stop();
	void update();
	int32_t getCount();
	void resetCount();

private:
	uint8_t startFlag;
	TIM_HandleTypeDef *tim;
	uint16_t preRawCount;
	uint16_t curRawCount;
	int32_t count;

};

#endif /* APPLICATION_USER_ENCODER_HPP_ */
