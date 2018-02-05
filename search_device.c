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

#include "search_device.h"

int find_device_name(char *sensor_name){

	FILE *file;
	char str[20];
	char path[100];

	char str0[100];
	char str1[100];
	char str2[100];
	char str3[100];
	char str4[100];
	char str5[100];
	char str6[100];

	static char sensor0[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 0);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str0);
	strcpy(sensor0, str0);
	fclose(file);

	static char sensor1[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 1);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str1);
	strcpy(sensor1, str1);
	fclose(file);

	static char sensor2[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 2);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str2);
	strcpy(sensor2, str2);
	fclose(file);

	static char sensor3[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 3);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str3);
	strcpy(sensor3, str3);
	fclose(file);

	static char sensor4[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 4);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str4);
	strcpy(sensor4, str4);
	fclose(file);

	static char sensor5[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 5);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str5);
	strcpy(sensor5, str5);
	fclose(file);

	static char sensor6[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 6);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str6);
	strcpy(sensor6, str6);
	fclose(file);

	char *sensors[7];
	sensors[0] = sensor0;
	sensors[1] = sensor1;
	sensors[2] = sensor2;
	sensors[3] = sensor3;
	sensors[4] = sensor4;
	sensors[5] = sensor5;
	sensors[6] = sensor6;

	char device0[20];
	char device1[20];
	char device2[20];
	char device3[20];
	char device4[20];
	char device5[20];
	char device6[20];

	for(int i=0; i<7; i++){
		for(int j=0; j<7; j++){
			sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", j);
			if(j==0){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device0, sensors[i]);
					break;
				}
			}
			else if(j==1){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device1, sensors[i]);
					break;
				}
			}
			else if(j==2){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device2, sensors[i]);
					break;
				}
			}
			else if(j==3){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device3, sensors[i]);
					break;
				}
			}
			else if(j==4){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device4, sensors[i]);
					break;
				}
			}
			else if(j==5){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device5, sensors[i]);
					break;
				}
			}
			else
			{
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device6, sensors[i]);
					break;
				}
			}
		}
	}

	if(strcmp(sensor_name,device0) == 0){
//		printf("IL SENSORE %s CORRISPONDE AL DEVICE %d\n", sensor_name, 0);
		return 0;
	}
	else if(strcmp(sensor_name,device1) == 0){
//		printf("IL SENSORE %s CORRISPONDE AL DEVICE %d\n", sensor_name, 1);
		return 1;
	}
	else if(strcmp(sensor_name,device2) == 0){
//		printf("IL SENSORE %s CORRISPONDE AL DEVICE %d\n", sensor_name, 2);
		return 2;
	}
	else if(strcmp(sensor_name,device3) == 0){
//		printf("IL SENSORE %s CORRISPONDE AL DEVICE %d\n", sensor_name, 3);
		return 3;
	}
	else if(strcmp(sensor_name,device4) == 0){
//		printf("IL SENSORE %s CORRISPONDE AL DEVICE %d\n", sensor_name, 4);
		return 4;
	}
	else if(strcmp(sensor_name,device5) == 0){
//		printf("IL SENSORE %s CORRISPONDE AL DEVICE %d\n", sensor_name, 5);
		return 5;
	}
	else{
//		printf("IL SENSORE %s CORRISPONDE AL DEVICE %d\n", sensor_name, 6);
		return 6;
	}
}


void print_device_list(){

	FILE *file;
	char str[20];
	char path[100];

	char str0[100];
	char str1[100];
	char str2[100];
	char str3[100];
	char str4[100];
	char str5[100];
	char str6[100];

	static char sensor0[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 0);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str0);
	strcpy(sensor0, str0);
	fclose(file);

	static char sensor1[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 1);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str1);
	strcpy(sensor1, str1);
	fclose(file);

	static char sensor2[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 2);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str2);
	strcpy(sensor2, str2);
	fclose(file);

	static char sensor3[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 3);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str3);
	strcpy(sensor3, str3);
	fclose(file);

	static char sensor4[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 4);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str4);
	strcpy(sensor4, str4);
	fclose(file);

	static char sensor5[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 5);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str5);
	strcpy(sensor5, str5);
	fclose(file);

	static char sensor6[20];
	sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", 6);
	file = fopen(path, "r");
	fscanf(file, "%[^\n]", str6);
	strcpy(sensor6, str6);
	fclose(file);

	char *sensors[7];
	sensors[0] = sensor0;
	sensors[1] = sensor1;
	sensors[2] = sensor2;
	sensors[3] = sensor3;
	sensors[4] = sensor4;
	sensors[5] = sensor5;
	sensors[6] = sensor6;

	char device0[20];
	char device1[20];
	char device2[20];
	char device3[20];
	char device4[20];
	char device5[20];
	char device6[20];

	for(int i=0; i<7; i++){
		for(int j=0; j<7; j++){
			sprintf(path, "/sys/bus/iio/devices/iio:device%d/name", j);
			if(j==0){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device0, sensors[i]);
					break;
				}
			}
			else if(j==1){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device1, sensors[i]);
					break;
				}
			}
			else if(j==2){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device2, sensors[i]);
					break;
				}
			}
			else if(j==3){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device3, sensors[i]);
					break;
				}
			}
			else if(j==4){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device4, sensors[i]);
					break;
				}
			}
			else if(j==5){
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device5, sensors[i]);
					break;
				}
			}
			else
			{
				file = fopen(path, "r");
				fscanf(file, "%[^\n]", str);
				if(strcmp(str,sensors[i]) == 0){
					strcpy(device6, sensors[i]);
					break;
				}
			}
		}
	}
	printf("device0: %s\n", device0);
	printf("device1: %s\n", device1);
	printf("device2: %s\n", device2);
	printf("device3: %s\n", device3);
	printf("device4: %s\n", device4);
	printf("device5: %s\n", device5);
	printf("device6: %s\n", device6);
}

