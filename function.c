/*
 * start_buffer.c
 *
 *  Created on: 26 gen 2018
 *      Author: marco.cossali
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include "search_device.h"
#include "function.h"

void stop_scan(int n_device){

	FILE *file;
	char path[100];
	char str[100];

	sprintf(str, "%d", 0);
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/buffer/enable", n_device);
	file = fopen(path, "w");
	fprintf(file,"%s", str);
	fclose(file);
}

int calc_freq(int n_device){

	FILE *file;
	char path[100];
	char str[100];
	double d = 0.0f;

	sprintf(path, "/sys/bus/iio/devices/iio:device%d/sampling_frequency", n_device);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str);
	sscanf(str, "%lf", &d);
	fclose(file);
	return d;
}

void set_buffer_length(int n_device, int length){

	FILE *file;
	char path[100];
	char str[100];

	sprintf(str, "%d", length);
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/buffer/length", n_device);
	file = fopen(path, "w");
	fprintf(file, "%s", str);
	fclose(file);
}

void set_buffer_watermark(int n_device, int watermark){

	FILE *file;
	char path[100];
	char str[100];

	sprintf(str, "%d", watermark);
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/buffer/watermark", n_device);
	file = fopen(path, "w");
	fprintf(file,"%s", str);
	fclose(file);
}

void set_buffer_enable(int n_device, int enable){

	FILE *file;
	char path[100];
	char str[100];

	sprintf(str, "%d", enable);
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/buffer/enable", n_device);
	file = fopen(path, "w");
	fprintf(file,"%s", str);
	fclose(file);
}

int get_buffer_enable(int n_device){

	FILE *file;
	double d = 0;
	char str[1000];
	char path[100];

	sprintf(path, "/sys/bus/iio/devices/iio:device%d/buffer/enable", n_device);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str);
	sscanf(str, "%lf", &d);
	fclose(file);
	return d;
}

