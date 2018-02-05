/*
 * v15310x_prox.c
 *
 *  Created on: 23 gen 2018
 *      Author: marco.cossali
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "v15310_prox.h"
#include "search_device.h"

void get_name_v15310_prox(int n_device){

	FILE *file;
	char str[1000];
	char path[100];

	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", n_device);
	file = fopen(path, "r");	fscanf(file, "%[^\n]", str);
	printf("NAME SENSOR: %s\n", str);
	fclose(file);
}

double get_in_proximity_input(int n_device){

	FILE *file;
	double d = 0.0f;
	char str[1000];
	char path[100];

	sprintf(path, "/sys/bus/iio/devices/iio:device%d/in_proximity_input", n_device);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str);
	sscanf(str, "%lf", &d);
	return d;
	fclose(file);
}

void get_in_proximity_range_avaiable(int n_device){

	FILE *file;
	char str[1000];
	char path[100];

	sprintf(path, "/sys/bus/iio/devices/iio:device%d/in_proximity_range_avaiable", n_device);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str);
	printf("%s\n", str);
	fclose(file);
}

void get_in_proximity_set_range(int n_device){

	FILE *file;
	char str[1000];
	char path[100];

	sprintf(path, "/sys/bus/iio/devices/iio:device%d/in_proximity_set_range", n_device);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str);
	printf("%s\n", str);
	fclose(file);
}

