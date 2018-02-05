/*
 * lps22hb_temp_pres.h
 *
 *  Created on: 23 gen 2018
 *      Author: marco.cossali
 */

#ifndef LPS22HB_TEMP_PRES_H_
#define LPS22HB_TEMP_PRES_H_

void get_name_lps22hb_temp_pres();

double get_in_pressure_raw();

double get_in_pressure_scale();

double get_in_temp_raw();

double get_in_temp_scale();

int get_sampling_frequency_lps22hb_temp_pres();

void set_sampling_frequency_lps22hb_temp_pres();

void getLIST_sampling_frequency_lps22hb_temp_pres();

#endif /* LPS22HB_TEMP_PRES_H_ */
