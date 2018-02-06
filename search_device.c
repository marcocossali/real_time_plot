/*
 * search_device.c
 *
 *  Created on: 24 gen 2018
 *      Author: marco.cossali
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include "search_device.h"

int find_device_name(char *sensor_name){

	FILE *file;
	DIR *dr = opendir("/sys/bus/iio/devices");
	struct dirent *in_file;
	char str[20];
	char path[100];
	int num_dev = 0;
	int ret;

	while((in_file = readdir(dr)) != NULL){
		if(strncmp(in_file->d_name,"iio:device",10) == 0)
			num_dev++;
	}
	closedir(dr);

	for(ret=0; ret<num_dev; ret++){
		sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", ret);
		file = fopen(path, "r");
		fscanf(file, "%[^\n]", str);
		if(strcmp(sensor_name,str) == 0)
			break;
		fclose(file);
	}
	fclose(file);
	return ret;
}

void print_device_list(){

	FILE *file;
	DIR *dr = opendir("/sys/bus/iio/devices");
	struct dirent *in_file;
	char str[20];
	char path[100];
	int num_dev = 0;

	while((in_file = readdir(dr)) != NULL){
		if(strncmp(in_file->d_name,"iio:device",10) == 0){
			num_dev++;
		}
	}
	closedir(dr);

	for(int i=0; i<num_dev; i++){
		sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", i);
		file = fopen(path, "r");
		fscanf(file, "%[^\n]", str);
		printf("Device%d: %s\n", i, str);
		fclose(file);
	}
}

