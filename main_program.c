#include <stdio.h>
//#include "paring.c"
#include <stdint.h>
#include "res_sensor.c"
#include "json_type.c"

int main()
	{
	char* location = "http://35.160.141.229:3000/api/ths";
	char* location_io = "http://35.166.240.126:3000/api/ios/save";
	char* location_config = "http://35.166.240.126:3000/api/apps/config";
	char* location_wattR = "http://35.160.141.229:3000/api/RWatts";
	char* location_wattS = "http://35.160.141.229:3000/api/SWatts";
	char* location_wattT = "http://35.160.141.229:3000/api/TWatts";
	char* column[] = {"ac_name", "phasa", "id_temp", "channel", "id_ir", "id_kwh", "brand", "start_operation", "end_operation"};
	char* column_1[] = {"ir_name", "channel", "set_default", "brand"};
	char* column_2[] = {"temp_name", "th_id", "humidity", "threshold"};
	char* column_3[] = {"id_kwh", "phasa", "channel", "start_operation", "end_operation", "lamp_name", "io_id"};
	//char* location = "http://10.42.0.1/chart/post2.php";
	//char* location = "http://52.43.48.93/post.php";
	//char* location = "http://192.168.88.19:1616/dcms/rest/alfa";
	//uint16_t gateway_ID = mac_address();
  char* gateway_ID = "EM24010101";
	uint16_t humidity = 2000;
	uint16_t temp1 = 2708;
	uint16_t temp2 = 0;
	uint16_t temp3 = 3300;
	uint16_t cc1120_TH_ID = 1908;
	uint16_t gateway = 1002;
	int channel = 10;
	//printf("Gateway id is %d\n", gateway_ID);
	uint16_t kwh[18];
	int i;
	int32_t t = 0;
 	char *content = NULL;
	//printf("%d\n", sizeof kwh);
	for (i=0;i<18;i++)
	{
		kwh[i]=t;
		//t=t-1;
	}
	content = get_config(location_config, 1002, "ac", 9, column);
 	printf("%s\n", content);
	json_parse(content, 9, column);
	content = get_config(location_config, 1002, "infrared", 4, column_1);
	json_parse(content, 4, column_1);
 	printf("%s\n", content);
	content = get_config(location_config, 1002, "temperature", 4, column_2);
	json_parse(content, 4, column_2);
 	printf("%s\n", content);
	content = get_config(location_config, 1002, "lamp", 7, column_3);
	json_parse(content, 7, column_3);
 	printf("%s\n", content);
  //trap_th(location, 10, gateway_ID, 1245,1,2,1356,3005,5,6,7);
	//res_kwh_2 (location, kwh, 4004, 2000, 1003, 4004, 2000, 14, cc1120_TH_ID, channel);
	/*res_kwh_array(location, kwh, kwh, kwh, 
								kwh, kwh, kwh, kwh, 
								kwh, kwh, 14, 1002, gateway)*/
	//res_th (location, temp1, temp2, temp3, humidity, 11, cc1120_TH_ID, gateway);
	//res_R_WattPrd_WattHour(location_wattR, kwh, kwh, 14, cc1120_TH_ID, gateway);
	//res_S_WattPrd_WattHour(location_wattS, kwh, kwh, 14, cc1120_TH_ID, gateway);
	//res_T_WattPrd_WattHour(location_wattT, kwh, kwh, 14, cc1120_TH_ID, gateway);
	//res_T_I(location, kwh, 14, cc1120_TH_ID, gateway);
	//res_th_2 (location, temp1, temp2, temp3, humidity, 11, cc1120_TH_ID);
  //get_id("localhost","root","satunol10","paring","main");
  //get_lamp_config("localhost","root","satunol10","EMS","lamp", 1002);
  //printf("%d\n",mysql_id);
	return 0;
	}
