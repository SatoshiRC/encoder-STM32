/*
 * encoder.cpp
 *
 *  Created on: 2018/09/03
 *      Author: Sekiguchi Takuya
 */

#include "encoder.hpp"

Encoder::Encoder(TIM_HandleTypeDef *htim){
	tim = htim;
	preRawCount = 0;
	curRawCount = 0;
	startFlag = 0;
	count = 0;
}

void Encoder::init(){
	count = 0;
}

void Encoder::start(){
	int16_t tmpCount = count;
	if(startFlag != 1)
		HAL_TIM_Encoder_Start(tim,TIM_CHANNEL_ALL);
	__HAL_TIM_CLEAR_FLAG(tim, TIM_CHANNEL_ALL);
	__HAL_TIM_SET_COUNTER(tim , 0);
	startFlag = 1;
	update();
	count = tmpCount;
}

void Encoder::stop(){
	HAL_TIM_Encoder_Stop(tim,TIM_CHANNEL_ALL);
	__HAL_TIM_SET_COUNTER(tim , 0);
	update();
	startFlag = 0;
}

void Encoder::update() {

	preRawCount = curRawCount;

	if (__HAL_TIM_GET_FLAG(tim, TIM_FLAG_UPDATE)) {

		curRawCount = __HAL_TIM_GET_COUNTER(tim);

		if (curRawCount > preRawCount) {
			//under_flow
			count += (curRawCount - __HAL_TIM_GET_AUTORELOAD(tim)) - preRawCount;
		} else {
			//over_flow
			count += curRawCount - (preRawCount - __HAL_TIM_GET_AUTORELOAD(tim));
		}
		__HAL_TIM_CLEAR_FLAG(tim, TIM_FLAG_UPDATE);
	} else {
		curRawCount = __HAL_TIM_GET_COUNTER(tim);

		count += curRawCount - preRawCount;
	}
}

int32_t Encoder::getCount() {
	return count;
}

void Encoder::resetCount(){
	update();
	count = 0;
}
