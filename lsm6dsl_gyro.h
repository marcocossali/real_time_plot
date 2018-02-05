/*
 * lsm6dsl_gyro.h
 *
 *  Created on: 24 gen 2018
 *      Author: marco.cossali
 */

#ifndef LSM6DSL_GYRO_H_
#define LSM6DSL_GYRO_H_

void get_name_lsm6dsl_gyro();

double get_in_anglvel_x_raw_lsm6dsl_gyro();

double get_in_anglvel_x_scale_lsm6dsl_gyro();

double get_in_anglvel_y_raw_lsm6dsl_gyro();

double get_in_anglvel_y_scale_lsm6dsl_gyro();

double get_in_anglvel_z_raw_lsm6dsl_gyro();

double get_in_anglvel_z_scale_lsm6dsl_gyro();

double get_sampling_frequency_lsm6dsl_gyro();

void set_sampling_frequency_lsm6dsl_gyro();

void getLIST_sampling_frequency_lsm6dsl_gyro();

#endif /* LSM6DSL_GYRO_H_ */
