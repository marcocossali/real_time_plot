//
// rael_time_plot.c
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
//#include <artik_module.h>

#include "function.h"
#include "lsm303agr_accel.h"
#include "lsm303agr_magn.h"
#include "lsm6dsl_accel.h"
#include "v15310_prox.h"
#include "lps22hb_temp_pres.h"
#include "lsm6dsl_gyro.h"
#include "search_device.h"

int scelta;

struct thread_param{
	int device;
	int control;
	char *tty;
};

void* thread_buffer(void* parameter){

	struct thread_param* par = (struct thread_param*) parameter;

	FILE *file;
	uint8_t dati[16];
	char path[100];
	int16_t x;
	int16_t y;
	int16_t z;
	int32_t pres;
	int16_t temp;
//	int64_t timestamp;
	int fd;
	char pressure[4];
	char temperature[2];
	char x_vett[2];
	char y_vett[2];
	char z_vett[2];

	fd = open(par->tty, O_RDWR, O_NOCTTY);

	if(fd == -1){
		printf("Reception on serial port not started\n");
	}
	else{
		printf("\n");
	}

	sprintf(path, "/dev/iio:device%d", par->device);
	file = fopen(path, "r");

	if(scelta != 5){

		while(fread(dati, 16, 1, file) == 1 && par->control == 1){

			x = *((int16_t*)(dati + 0));
			sprintf(x_vett, "%d", x);
			write(fd, strcat(x_vett, ","), strlen(x_vett));

			y = *((int16_t*)(dati + 2));
			sprintf(y_vett, "%d", y);
			write(fd, strcat(y_vett, ","), strlen(y_vett));

			z = *((int16_t*)(dati + 4));
			sprintf(z_vett, "%d", z);
			write(fd, strcat(z_vett, "\n"), strlen(z_vett));
		}
		fclose(file);
	}
	else{
		while(fread(dati, 16, 1, file) == 1 && par->control == 1){

			pres = (*((int32_t*)(dati + 0)))/4096;
			sprintf(pressure, "%d", pres);
			write(fd, strcat(pressure, ","), strlen(pressure));

			temp = (*((int16_t*)(dati + 4)))/100;
			sprintf(temperature, "%d", temp);
			write(fd, strcat(temperature, "\n"), strlen(temperature));
		}
		fclose(file);
	}
	return NULL;
}

int main(int argc, char **argv)
{
//	artik_error ret = S_OK;

	FILE *file;
	char path[100];
	int enter;
	int fr;
	int device;
	struct thread_param param;
	pthread_t thread_id;

	int ver_lsm6dsl_acc = 0;
	int ver_lsm6dsl_gyro = 0;
	int ver_lsm303agr_acc = 0;
	int ver_lsm303agr_magn = 0;
	int ver_lps22hb = 0;

	if(find_device_name("lsm6dsl_accel") == 0 || find_device_name("lsm6dsl_accel") == 1 || find_device_name("lsm6dsl_accel") == 2 || find_device_name("lsm6dsl_accel") == 3 || find_device_name("lsm6dsl_accel") == 4 || find_device_name("lsm6dsl_accel") == 5 || find_device_name("lsm6dsl_accel") == 6){
		ver_lsm6dsl_acc = 1;
	}

	if(find_device_name("lsm6dsl_gyro") == 0 || find_device_name("lsm6dsl_gyro") == 1 || find_device_name("lsm6dsl_gyro") == 2 || find_device_name("lsm6dsl_gyro") == 3 || find_device_name("lsm6dsl_gyro") == 4 || find_device_name("lsm6dsl_gyro") == 5 || find_device_name("lsm6dsl_gyro") == 6){
		ver_lsm6dsl_gyro = 1;
	}

	if(find_device_name("lsm303agr_accel") == 0 || find_device_name("lsm303agr_accel") == 1 || find_device_name("lsm303agr_accel") == 2 || find_device_name("lsm303agr_accel") == 3 || find_device_name("lsm303agr_accel") == 4 || find_device_name("lsm303agr_accel") == 5 || find_device_name("lsm303agr_accel") == 6){
		ver_lsm303agr_acc = 1;
	}

	if(find_device_name("lsm303agr_magn") == 0 || find_device_name("lsm303agr_magn") == 1 || find_device_name("lsm303agr_magn") == 2 || find_device_name("lsm303agr_magn") == 3 || find_device_name("lsm303agr_magn") == 4 || find_device_name("lsm303agr_magn") == 5 || find_device_name("lsm303agr_magn") == 6){
		ver_lsm303agr_magn = 1;
	}

	if(find_device_name("lps22hb") == 0 || find_device_name("lps22hb") == 1 || find_device_name("lps22hb") == 2 || find_device_name("lps22hb") == 3 || find_device_name("lps22hb") == 4 || find_device_name("lps22hb") == 5 || find_device_name("lps22hb") == 6){
		ver_lps22hb = 1;
	}

//	if(argc == 2){

		while(1){

//			printf("************\n");
//			printf("*   MENU'  *\n");
//			printf("************\n");
			printf("Insert 0 to print the list of devices\n");
			if(ver_lsm6dsl_acc == 1){
				printf("Insert 1 to start the acquisition of occelerometer datas => lsm6dsl\n");
				printf("Insert 11 to change the reception frequency of the accelerometer lsm6dsl\n");
				printf("	 Frequency values allowed: 13 26 52 104 208 416\n");
			}
			if(ver_lsm6dsl_gyro == 1){
				printf("Insert 2 to start the acquisition of gyroscope datas => lsm6dsl\n");
				printf("Insert 22 to change the reception frequency of the gyroscope lsm6dsl \n");
				printf("	Frequency values allowed: 13 26 52 104 208 416\n");
			}
			if(ver_lsm303agr_acc == 1){
				printf("Insert 3 to start the acquisition of accelerometer datas  => lsm303agr\n");
				printf("Insert 33 to change the reception frequency of the accelerometer lsm303agr\n");
				printf("	Frequency values allowed: 1 10 25 50 100 200 400 1600\n");
			}
			if(ver_lsm303agr_magn == 1){
				printf("Insert 4 to start the acquisition of magnetometer datas => lsm303agr\n");
				printf("Insert 44 to change the reception frequency of the magnetometer lsm303agr \n");
				printf("	Frequency values allowed: 10 20 50 100\n");
			}
			if(ver_lps22hb == 1){
				printf("Insert 5 to start the acquisition of barometer datas=> lps22hb\n");
				printf("Insert 55 to change the reception frequency of the barometer lps22hb \n");
				printf("	Frequency values allowed:  1 10 25 50 75\n");
			}
			printf("Insert 9 to stop the acquisition\n");

			printf("Insert: ");
			scanf("%d", &scelta);

			switch(scelta){

			case 0:
				enter = 9090;
				print_device_list();
				while(enter != 13){
					printf("Press 1 to return to the menu': ");
					scanf("%d", &enter);
					if(enter == 1)
						break;
				}
				break;

			case 1:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				device = find_device_name("lsm6dsl_accel");

				if(fr==13 || fr==26 || fr==52 || fr==104 || fr==208 || fr==416){

					set_sampling_frequency_lsm6dsl(device, fr);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_accel_x_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_accel_y_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_accel_z_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_timestamp_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);

					param.control = 1;
					param.tty = argv[1];
//					param.tty = "/dev/ttySAC3";
					param.device = device;

					if(fr==13 || fr==26 || fr==52 || fr==104){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 2);
						set_buffer_watermark(device,1);
						set_buffer_enable(device, 1);
					}
					else if(fr == 208){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 20);
						set_buffer_watermark(device, 10);
						set_buffer_enable(device, 1);
					}
					else{
						set_buffer_enable(device, 0);
						set_buffer_length(device, 40);
						set_buffer_watermark(device, 20);
						set_buffer_enable(device, 1);
					}
					pthread_create (&thread_id, NULL, &thread_buffer, &param);
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 11:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				if(fr==13 || fr==26 || fr==52 || fr==104 || fr==208 || fr==416){

					device = find_device_name("lsm6dsl_accel");

					if(fr==13 || fr==26 || fr==52 || fr==104){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 2);
						set_buffer_watermark(device,1);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm6dsl(device, fr);
					}
					else if(fr == 208){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 20);
						set_buffer_watermark(device, 10);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm6dsl(device, fr);
					}
					else{
						set_buffer_enable(device, 0);
						set_buffer_length(device, 40);
						set_buffer_watermark(device, 20);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm6dsl(device, fr);
					}
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 2:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				device = find_device_name("lsm6dsl_gyro");

				if(fr==13 || fr==26 || fr==52 || fr==104 || fr==208 || fr==416){

					set_sampling_frequency_lsm6dsl_gyro(device, fr);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_anglvel_x_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_anglvel_y_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_anglvel_z_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_timestamp_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);

					param.control = 1;
					param.tty = argv[1];
//					param.tty = "/dev/ttySAC3";
					param.device = device;

					if(fr==13 || fr==26 || fr==52 || fr==104){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 2);
						set_buffer_watermark(device,1);
						set_buffer_enable(device, 1);
					}
					else if(fr == 208){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 20);
						set_buffer_watermark(device, 10);
						set_buffer_enable(device, 1);
					}
					else{
						set_buffer_enable(device, 0);
						set_buffer_length(device, 40);
						set_buffer_watermark(device, 20);
						set_buffer_enable(device, 1);
					}
					pthread_create (&thread_id, NULL, &thread_buffer, &param);
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 22:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				if(fr==13 || fr==26 || fr==52 || fr==104 || fr==208 || fr==416){

					device = find_device_name("lsm6dsl_gyro");

					if(fr==13 || fr==26 || fr==52 || fr==104){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 2);
						set_buffer_watermark(device,1);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm6dsl_gyro(device, fr);
					}
					else if(fr == 208){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 20);
						set_buffer_watermark(device, 10);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm6dsl_gyro(device, fr);
					}
					else{
						set_buffer_enable(device, 0);
						set_buffer_length(device, 40);
						set_buffer_watermark(device, 20);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm6dsl_gyro(device, fr);
					}
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 3:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				device = find_device_name("lsm303agr_accel");

				if(fr==1 || fr==10 || fr==25 || fr==50 || fr==100 || fr==200 || fr==400 || fr==1600){

					set_sampling_frequency_lsm303agr(device, fr);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_accel_x_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_accel_y_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_accel_z_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_timestamp_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);

					param.control = 1;
					param.tty = argv[1];
//				 	param.tty = "/dev/ttySAC3";
					param.device = device;

					if(fr==1 || fr==10 || fr==25 || fr==50 || fr==100){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 2);
						set_buffer_watermark(device,1);
						set_buffer_enable(device, 1);
					}
					else if(fr == 200){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 20);
						set_buffer_watermark(device, 10);
						set_buffer_enable(device, 1);
					}
					else if(fr == 400){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 40);
						set_buffer_watermark(device, 20);
						set_buffer_enable(device, 1);
					}
					else{
						set_buffer_enable(device, 0);
						set_buffer_length(device, 400);
						set_buffer_watermark(device, 200);
						set_buffer_enable(device, 1);
					}
					pthread_create (&thread_id, NULL, &thread_buffer, &param);
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 33:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				if(fr==1 || fr==10 || fr==25 || fr==50 || fr==100 || fr==200 || fr==400 || fr==1600){

					device = find_device_name("lsm303agr_accel");

					if(fr==1 || fr==10 || fr==25 || fr==50 || fr==100){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 2);
						set_buffer_watermark(device,1);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm303agr(device, fr);
					}
					else if(fr == 200){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 20);
						set_buffer_watermark(device, 10);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm303agr(device, fr);
					}
					else if(fr == 400){
						set_buffer_enable(device, 0);
						set_buffer_length(device, 40);
						set_buffer_watermark(device, 20);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm303agr(device, fr);
					}
					else{
						set_buffer_enable(device, 0);
						set_buffer_length(device, 400);
						set_buffer_watermark(device, 200);
						set_buffer_enable(device, 1);
						set_sampling_frequency_lsm303agr(device, fr);
					}
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 4:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				device = find_device_name("lsm303agr_magn");

				if(fr==10 || fr==20 || fr==50 || fr==100){

					set_sampling_frequency_lsm303agr_magn(device, fr);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_magn_x_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_magn_y_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_magn_z_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_timestamp_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);

					param.control = 1;
					param.tty = argv[1];
//					param.tty = "/dev/ttySAC3";
					param.device = device;

					set_buffer_enable(device, 0);
					set_buffer_length(device, 2);
					set_buffer_watermark(device,1);
					set_buffer_enable(device, 1);

					pthread_create (&thread_id, NULL, &thread_buffer, &param);
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 44:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				if(fr==10 || fr==20 || fr==50 || fr==100){

					device = find_device_name("lsm303agr_magn");

					set_buffer_enable(device, 0);
					set_buffer_length(device, 2);
					set_buffer_watermark(device,1);
					set_buffer_enable(device, 1);

					set_sampling_frequency_lsm303agr_magn(device, fr);
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 5:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				device = find_device_name("lps22hb");

				if(calc_freq(device)==1 || calc_freq(device)==10 ||calc_freq(device)==25 || calc_freq(device)==50 || calc_freq(device)==75){

					set_sampling_frequency_lps22hb_temp_pres(device, fr);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_pressure_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_temp_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/scan_elements/in_timestamp_en", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);
					sprintf(path, "/sys/bus/iio/devices/iio:device%d/buffer/enable", device);
					file = fopen(path, "w");
					fprintf(file,"%s", "1");
					fclose(file);

					param.control = 1;
					param.tty = argv[1];
//					param.tty = "/dev/ttySAC3";
					param.device = device;

					set_buffer_enable(device, 0);
					set_buffer_length(device, 2);
					set_buffer_watermark(device,1);
					set_buffer_enable(device, 1);

					pthread_create (&thread_id, NULL, &thread_buffer, &param);
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 55:
				printf("Insert frequency: ");
				scanf("%d", &fr);
				if(calc_freq(device)==1 || calc_freq(device)==10 ||calc_freq(device)==25 || calc_freq(device)==50 || calc_freq(device)==75){

					device = find_device_name("lps22hb");

					set_buffer_enable(device, 0);
					set_buffer_length(device, 2);
					set_buffer_watermark(device,1);
					set_buffer_enable(device, 1);

					set_sampling_frequency_lps22hb_temp_pres(device, fr);
				}
				else
					printf("Frequency entered incorrectly\n");
				break;

			case 9:
				param.control = 0;
//				pthread_cancel(thread_id);
			}
		}
//	}
//	else
//		printf("Number of arguments entered, incorrect. Insert for example: nome.c /dev/ttySAC0\n");

//	return (ret == S_OK) ? 0 : -1;
}
