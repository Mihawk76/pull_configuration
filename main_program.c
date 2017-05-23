#define _GNU_SOURCE 1
#include <stdio.h>
//#include "paring.c"
#include <stdint.h>
#include "rest_post_sensor.c"
#include "json_parse.c"
#include "mysql_api.c"
const char* io_id_data[10][5];
typedef struct {
	int AlarmCode;
	const char* value1;
	const char* value2;
}ALARM_CONFIG;
ALARM_CONFIG alarm_config[50];

int main()
	{

					//char* location = "http://35.160.141.229:3000/api/ths";a
	//char* location_io = "http://35.166.240.126:3000/api/ios/save";
	char* location_config = "http://35.166.240.126:3000/api/apps/config";
	int alarm_value[80][3];
	//char* location_wattR = "http://35.160.141.229:3000/api/RWatts";
	//char* location_wattS = "http://35.160.141.229:3000/api/SWatts";
	//char* location_wattT = "http://35.160.141.229:3000/api/TWatts";
	//char* column_alarm[] = {"AlarmCode", "value1", "value2", "alarm_message"};
	//char* column_alarm[] = {"AlarmCode", "value1", "value2"};
	char* column_alarm[3][3] = {{"AlarmCode"},{"value1"},{"value2"}};
	char* column_ac_server[] = {"ac_name", "phasa", "id_temp", "channel", "ir_id", "kwh_id", "brand", "start_operation", "end_operation", "tempMin", "tempMax", "currentMin", "currentMax", "tempTimeOut", "currentTimeOut", "irTimeOut"};
	char* column[] = {"ac_name", "phasa", "id_temp", "channel", "id_ir", "id_kwh", "brand", "start_operation", "end_operation", "tempMin", "tempMax", "currentMin", "currentMax", "tempTimeOut", "currentTimeOut", "irTimeOut"};
	//tabel ac
	int column_type[] = {0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1};
	// 0 = varchar, 1 = int
	// infrared
	char* column_1[] = {"ir_name", "channel", "set_default", "brand", "id_ir"};
	int column_type_1[] = {0,0,1,0,1};
	//temperature
	char* column_2[] = {"temp_name", "th_id", "humidity", "threshold"};
	int column_type_2[] = {0,1,1,1};
	//lamp
	char* column_3[] = {"id_kwh", "phasa", "channel", "start_operation", "end_operation", "lamp_name", "io_id"};
	int column_type_3[] = {1,0,1,0,0,0,1};
	//main_power
	char* column_4[] = {"label", "phase", "channel", "voltMin", "voltMax", "vTimeOut", "currentMin","currentMax","curTimeOut"};
	int column_type_4[] = {0,0,1,1,1,1,1,1,1};
	//kwh
	char* column_5[] = {"kwh_name","kwh_id","brand"};
	int column_type_5[] = {0,1,0};
	//door
	char* column_6[] = {"door_name", "io_id", "max_threshold", "channel", "open_logic", "doorTimeOut"};
	char* column_6_1[] = {"door_name", "io_id", "max_threshold", "i_channel", "open_logic", "doorTimeOut"};
	int column_type_6[] = {0,1,1,1,1,1};
	//io
	char* column_7[] = {"io_id"};
	int column_type_7[] = {0};
	//char* location = "http://10.42.0.1/chart/post2.php";
	//char* location = "http://52.43.48.93/post.php";
	//char* location = "http://192.168.88.19:1616/dcms/rest/alfa";
	//uint16_t gateway_ID = mac_address();
  //char* gateway_ID = "EM24010101";
	//uint16_t humidity = 2000;
	//uint16_t temp1 = 2708;
	//uint16_t temp2 = 0;
	//uint16_t temp3 = 3300;
	//uint16_t cc1120_TH_ID = 1908;
	//uint16_t gateway = 1002;
	int n_array = 0;
	//int channel = 10;
	//printf("Gateway id is %d\n", gateway_ID);
	//uint16_t kwh[18];
	int kwh[18];
	int i;
	int32_t t = 0;
 	char *content = NULL;
	int tes = 0;
	int n_io_id = 0;
	//printf("%d\n", sizeof kwh);
  get_id("localhost","root","satunol10","paring","main");
	for (i=0;i<18;i++)
	{
		kwh[i]=t;
		t=t-1;
	}
	
	//n_array = (sizeof (column_alarm))/(sizeof (column_alarm[0]));
	//printf("jumlah column c_a %d\n", n_array);
	for(i=0;i<3;i++){
		content = get_config(location_config, 1002, "type_alarm", 1, column_alarm[i]);
		json_parse(content, 1, column_alarm[i]);
		int length = 0;
		for (length=0;length<arraylen;length++){
			//alarm_value[column_alarm][i] = atoi(config_data[length][0]);
			alarm_value[length][i] = atoi(config_data[length][0]);
			if(i==0){
				alarm_config[length].AlarmCode = atoi(config_data[length][0]);
			}
			if(i==1){
				alarm_config[length].value1 = config_data[length][0];
			}
			if(i==2){
				alarm_config[length].value2 = config_data[length][0];
			}
			//printf(" alarm value %d\n",alarm_value[length][i]);
		}
 		printf("%s\n", content);
		sleep(1);
	}
	//ac
	content = get_config(location_config, 1002, "ac", 9, column_ac_server);
 	printf("%s\n", content);
	json_parse(content, 9, column_ac_server);
	n_array = (sizeof (column))/(sizeof (column[0]));
	printf("%d\n", n_array);
  del_config("localhost","root","satunol10","EMS","ac");
	for(i=0;i<arraylen;i++)
	{
		for (tes = 0; tes <= 80; tes++)
		{
			if (alarm_value[tes][0] == 210)//210 ac temp 
			{	
				int temp = 0;
				config_data[i][9] = alarm_config[tes].value1;
				config_data[i][10] = alarm_config[tes].value2;
				printf("config temp ketemu\n");
			}
			if (alarm_value[tes][0] == 220)//220 ac current
			{
				config_data[i][11] = alarm_config[tes].value1;
				config_data[i][12] = alarm_config[tes].value2;
				printf("config current ketemu\n");
			}
			if (alarm_value[tes][0] == 212)//212 ac temp disconnected
			{
				config_data[i][13] = alarm_config[tes].value1;
				printf("config temp disc ketemu\n");
			}
			if (alarm_value[tes][0] == 222)//222 ac current disconnected
			{
				config_data[i][14] = alarm_config[tes].value1;
				printf("config current disc ketemu\n");
			}
			if (alarm_value[tes][0] == 201)//220 ac infrared disconnected
			{
				config_data[i][15] = alarm_config[tes].value1;
				printf("config infrared ketemu\n");
			}
				//config_data[i][15] = "100";
		}
				//config_data[i][9] = "100";
				//config_data[i][10] = "100";
				//config_data[i][11] = "100";			
				//config_data[i][12] = "100";			
		//printf("column %s, data %s, column_type %d, array len %d, column[arraylen],
  	insert_config("localhost","root","satunol10","EMS","ac", column, config_data[i], column_type, n_array, mysql_id);
	}
	//infrared
	n_array = (sizeof (column_1))/(sizeof (column_1[0]));
	content = get_config(location_config, 1002, "infrared", n_array, column_1);
	json_parse(content, n_array, column_1);
 	printf("%s\n", content);
	printf("%d\n", n_array);
  del_config("localhost","root","satunol10","EMS","infrared");
	for(i=0;i<arraylen;i++)
	{
  	insert_config("localhost","root","satunol10","EMS","infrared", column_1, config_data[i], column_type_1, n_array, mysql_id);
	}

	//temperature
	content = get_config(location_config, 1002, "temperature", 4, column_2);
	json_parse(content, 4, column_2);
 	printf("%s\n", content);
	n_array = (sizeof (column_2))/(sizeof (column_2[0]));
	printf("%d\n", n_array);
  del_config("localhost","root","satunol10","EMS","temperature");
	for(i=0;i<arraylen;i++)
	{
  	insert_config("localhost","root","satunol10","EMS","temperature", column_2, config_data[i], column_type_2, n_array, mysql_id);
	}

	//lamp
	content = get_config(location_config, 1002, "lamp", 7, column_3);
	json_parse(content, 7, column_3);
 	printf("%s\n", content);
	n_array = (sizeof (column_3))/(sizeof (column_3[0]));
	printf("%d\n", n_array);
  del_config("localhost","root","satunol10","EMS","lamp");
	for(i=0;i<arraylen;i++)
	{
  	insert_config("localhost","root","satunol10","EMS","lamp", column_3, config_data[i], column_type_3, n_array, mysql_id);
		io_id_data[n_io_id][0] = config_data[i][6];
		printf("io id %s\n",io_id_data[n_io_id][0]);
		n_io_id++;
	}

	//main_power
	n_array = (sizeof (column_4))/(sizeof (column_4[0]));
	content = get_config(location_config, 1002, "main_power", n_array, column_4);
 	printf("%s\n", content);
	json_parse(content, n_array, column_4);
  del_config("localhost","root","satunol10","EMS","main_power");
	for(i=0;i<arraylen;i++)
	{
  	insert_config_main_power("localhost","root","satunol10","EMS","main_power", column_4, config_data[i], column_type_4, n_array);
	}
	//kwh
	n_array = (sizeof (column_5))/(sizeof (column_5[0]));
	content = get_config(location_config, 1002, "kwh", n_array, column_5);
 	printf("%s\n", content);
	json_parse(content, n_array, column_5);
  del_config("localhost","root","satunol10","EMS","kwh");
	for(i=0;i<arraylen;i++)
	{
  	insert_config("localhost","root","satunol10","EMS","kwh", column_5, config_data[i], column_type_5, n_array, mysql_id);
	}
	//door
	n_array = (sizeof (column_6))/(sizeof (column_6[0]));
	content = get_config(location_config, 1002, "door", n_array-2, column_6);
 	printf("%s\n", content);
	json_parse(content, n_array-2, column_6);
	printf("%d\n", n_array);
  del_config("localhost","root","satunol10","EMS","door");
	for(i=0;i<arraylen;i++)
	{
		io_id_data[n_io_id][0] = config_data[i][1];
		printf("io id door %s n %d\n",io_id_data[n_io_id][0],n_io_id);
		n_io_id++;
		for (tes = 0; tes <= 80; tes++)
		{
			if (alarm_value[tes][0] == 400)//400 door  
			{	
				int temp = 0;
				config_data[i][n_array-2] = alarm_config[tes].value1;//door timeout
				config_data[i][n_array-1] = alarm_config[tes].value2;//door open logic (0/1)
				printf("config temp ketemu\n");
			}
				//config_data[i][15] = "100";
		}
				//config_data[i][9] = "100";
				//config_data[i][10] = "100";
				//config_data[i][11] = "100";			
				//config_data[i][12] = "100";			
		//printf("column %s, data %s, column_type %d, array len %d, column[arraylen],
  	insert_config("localhost","root","satunol10","EMS","door", column_6_1, config_data[i], column_type_6, n_array, mysql_id);
	}
	//io
  del_config("localhost","root","satunol10","EMS","io");
  for(i=0;i<n_io_id;i++)
  {
    for(tes=i+1;tes<n_io_id;tes++)
    {
      if(strcmp(io_id_data[i][0],io_id_data[tes][0])==0)
      {
        io_id_data[tes][0] = "0";
      }
    }
   }
  for(i=0;i<n_io_id;i++)
  {
		printf("new io id %s\n",io_id_data[i][0]);
		if(strcmp(io_id_data[i][0],"0")!=0)
		{
  		insert_config_io("localhost","root","satunol10","EMS","io", column_7, io_id_data[i], column_type_7, 1, mysql_id);
		}
	}
 //	
  //trap_th(location, 10, gateway_ID, 1245,1,2,1356,3005,5,6,7);
	//res_kwh_2 (location, kwh, 4004, 2000, 1003, 4004, 2000, 14, cc1120_TH_ID, channel);*/
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
  //del_config("localhost","root","satunol10","paring","th");
  //get_lamp_config("localhost","root","satunol10","EMS","lamp", 1002);
  //printf("%d\n",mysql_id);
		return 0;
	}
