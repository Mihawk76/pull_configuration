//#define _GNU_SOURCE 1
#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include "paring.h"

//char*id_getway[100];
int total_pairing;
int pairing_id[1000];
int mysql_id;
struct tm start_operation;
struct tm end_operation;
typedef struct{
	uint16_t th_id;
}TH_CONFIG;
typedef struct{
	uint16_t io_id;
}IO_CONFIG;
typedef struct{
	uint16_t kwh_id;
}KWH_CONFIG;
typedef struct{
	int suhu;
	int no_byte;
	int value_byte;
}IR_COMMAND;
typedef struct{
	uint16_t ir_id;
	int default_temp;
}IR_CONFIG;
typedef struct{
	uint16_t io_id;
	char* brand;
	struct tm start_operation;
	struct tm end_operation;
	int channel;
	int type;
}LAMP_CONFIG;
typedef struct{
	char* brand;
	uint16_t kwh_id;
	struct tm start_operation;
	struct tm end_operation;
}AC_CONFIG;

TH_CONFIG th_config[10];
IO_CONFIG io_config[10];
IR_COMMAND ir_command[1000];
IR_CONFIG ir_config[10];
LAMP_CONFIG lamp_config[16];
AC_CONFIG ac_config[10];
KWH_CONFIG kwh_config[10];

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}
void insert_config(char* server, char* user ,char* password ,char* dbname,char* nm_table, char* column[], const char* data[]
			, int column_type[], int n_column)
{      
	MYSQL *con = mysql_init(NULL);

	if (con == NULL) 
	{
  	fprintf(stderr, "mysql_init() failed\n");
  	exit(1);
  }  
  
 	if (mysql_real_connect(con, server, user, password, 
  	dbname, 0, NULL, 0) == NULL) 
  {
  	finish_with_error(con);
  }    
 	char select[1000];
 	char temp[100];
 	//snprintf(select,"insert into  %s", nm_table); 
	snprintf(select, sizeof select, "insert into %s (", nm_table);
	int i = 0;
  for(i=0;i<n_column;i++)
  {
    snprintf(temp, sizeof temp, "%s", 
    column[i]);
    strcat(select, temp);
    if(i<(n_column-1)){
    snprintf(temp, sizeof select, ",");
    strcat(select, temp);
    }   
  }
  snprintf(temp, sizeof temp, ") values("); 
  strcat(select, temp);
  for(i=0;i<n_column;i++)
  {
		if(column_type[i] == 0){
    	snprintf(temp, sizeof temp, "\"%s\"", data[i]);
    	strcat(select, temp);
		}
		if(column_type[i] == 1){
    	snprintf(temp, sizeof temp, "%s", data[i]);
    	strcat(select, temp);
		}
    if(i<(n_column-1)){
    snprintf(temp, sizeof select, ",");
    strcat(select, temp);
    }   
  }
  snprintf(temp, sizeof temp, ")"); 
  strcat(select, temp);
	printf("%s\n",select);
	printf("tes\n");
 	if (mysql_query(con,select)) 
 	{ 
  	finish_with_error(con);
		printf("error\n");
 	}


 	//MYSQL_RES *result = mysql_store_result(con);  
 	//if (result == NULL) 
 	//{
  //	finish_with_error(con);
 	//}
	printf("after\n");
	
	/*int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	//{
  	while((row = mysql_fetch_row(result)) != NULL)
    {	
			//th_config[a].th_id = atoi(row[0]?row[0]:"NULL");	
			printf("th id %d\n", atoi(row[0]?row[0]:"NULL"));
			a++;
  		printf("\n"); 
		}
	*/
	mysql_close(con);
	//exit(0);
}
void del_config(char* server, char* user ,char* password ,char* dbname,char* nm_table)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"truncate %s", nm_table); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }



	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	/*{
   while((row = mysql_fetch_row(result)) != NULL)
    {	
			th_config[a].th_id = atoi(row[0]?row[0]:"NULL");	
			printf("th id %d\n", th_config[a].th_id);
			a++;
  		//printf("\n"); 
    }
	}*/
	mysql_close(con);
}
void get_th_config(char* server, char* user ,char* password ,char* dbname,char* nm_table,uint16_t gateway_id)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select id from %s where id_location=%d", nm_table, gateway_id); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {	
			th_config[a].th_id = atoi(row[0]?row[0]:"NULL");	
			printf("th id %d\n", th_config[a].th_id);
			a++;
  		//printf("\n"); 
    }
	}
	mysql_close(con);
}
void get_io_config(char* server, char* user ,char* password ,char* dbname,char* nm_table,uint16_t gateway_id)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select io_id from %s where Gateway_id=%d", nm_table, gateway_id); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {	
			io_config[a].io_id = atoi(row[0]?row[0]:"NULL");	
			printf("io id %02X\n", io_config[a].io_id);
			a++;
  		//printf("\n"); 
    }
	}
	mysql_close(con);
}
void get_kwh_config(char* server, char* user ,char* password ,char* dbname,char* nm_table,uint16_t gateway_id)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select kwh_id from %s where id_location=%d", nm_table, gateway_id); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {	
			kwh_config[a].kwh_id = atoi(row[0]?row[0]:"NULL");	
			printf("kwh id %02X\n", kwh_config[a].kwh_id);
			a++;
  		//printf("\n"); 
    }
	}
	mysql_close(con);
}
void get_lamp_config(char* server, char* user ,char* password ,char* dbname,char* nm_table,uint16_t gateway_id)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select io_id, start_operation, end_operation, phasa, channel from %s where id_location=%d", nm_table, gateway_id); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {	
			lamp_config[a].io_id = atoi(row[0]?row[0]:"NULL");	
			strptime((row[1]?row[1]:"NULL"),"%H:%M",&lamp_config[a].start_operation);
			strptime((row[2]?row[2]:"NULL"),"%H:%M",&lamp_config[a].end_operation);
			lamp_config[a].type = atoi(row[3]?row[3]:"NULL");	
			lamp_config[a].channel = atoi(row[4]?row[4]:"NULL");	
			printf("io_id %02X, type %d, channel %d\n", lamp_config[a].io_id, lamp_config[a].type, lamp_config[a].channel);
			printf("start %d:%d:%d\n", lamp_config[a].start_operation.tm_hour,
			lamp_config[a].start_operation.tm_min,lamp_config[a].start_operation.tm_sec);
			printf("end %d:%d:%d\n\n", lamp_config[a].end_operation.tm_hour,
			lamp_config[a].end_operation.tm_min,lamp_config[a].end_operation.tm_sec);
			a++;
  		//printf("\n"); 
			if (ir_command[a].suhu == 30){
				break;
			}
    }
	}
	mysql_close(con);
}
void get_ac_config(char* server, char* user ,char* password ,char* dbname,char* nm_table,uint16_t gateway_id)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select id_kwh, brand, start_operation, end_operation from %s where id_location=%d", nm_table, gateway_id); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {	
			ac_config[a].kwh_id = atoi(row[0]?row[0]:"NULL");
			ac_config[a].brand = (row[1]?row[1]:"NULL");	
			strptime((row[2]?row[2]:"NULL"),"%H:%M",&ac_config[a].start_operation);
			strptime((row[3]?row[3]:"NULL"),"%H:%M",&ac_config[a].end_operation);
			printf("id kwh %02X %s\n",ac_config[a].kwh_id, ac_config[a].brand);
			printf("start %d:%d:%d\n", ac_config[a].start_operation.tm_hour,
			ac_config[a].start_operation.tm_min,ac_config[a].start_operation.tm_sec);
			printf("end %d:%d:%d\n\n", ac_config[a].end_operation.tm_hour,
			ac_config[a].end_operation.tm_min,ac_config[a].end_operation.tm_sec);
			a++;
  		//printf("\n"); 
			if (ir_command[a].suhu == 30){
				break;
			}
    }
	}
	mysql_close(con);
}
void get_ir_config(char* server, char* user ,char* password ,char* dbname,char* nm_table,uint16_t gateway_id)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select ir_name, set_default from  %s where id_location=%d", nm_table, gateway_id); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {
     /*for (i = 0; i < num_fields; i++)
        {
      total_pairing = a+i;     
			pairing_id[total_pairing]= atoi(row[i]?row[i]:"NULL");
			printf("%d %d\n", pairing_id[total_pairing], total_pairing);
        //printf("data_library:%02X \n",pairing_id[total_pairing]);
        }
		a=a+i;*/
			ir_config[a].ir_id = atoi(row[0]?row[0]:"NULL");	
			ir_config[a].default_temp = atoi(row[1]?row[1]:"NULL");
			printf("%02X %d\n", ir_config[a].ir_id, ir_config[a].default_temp);
			a++;
  		//printf("\n"); 
			if (ir_command[a].suhu == 30){
				break;
			}
    }
	}
	mysql_close(con);
}
void get_ir_command(char* server, char* user ,char* password ,char* dbname,char* nm_table,char* tipe_ac, int suhu)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select suhu, no_byte, value_byte from  %s where tipe_ac='%s' && suhu=%d", nm_table, tipe_ac, suhu); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	//int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {
     /*for (i = 0; i < num_fields; i++)
        {
      total_pairing = a+i;     
			pairing_id[total_pairing]= atoi(row[i]?row[i]:"NULL");
			printf("%d %d\n", pairing_id[total_pairing], total_pairing);
        //printf("data_library:%02X \n",pairing_id[total_pairing]);
        }
		a=a+i;*/
			ir_command[a].suhu = atoi(row[0]?row[0]:"NULL");	
			ir_command[a].no_byte = atoi(row[1]?row[1]:"NULL");
			ir_command[a].value_byte = atoi(row[2]?row[2]:"NULL");
			printf("%d %d %02X\n", ir_command[a].suhu, ir_command[a].no_byte, ir_command[a].value_byte);
			a++;
  		//printf("\n"); 
			if (ir_command[a].suhu == 30){
				break;
			}
    }
	}
	mysql_close(con);
}
void get_id_pairing(char* server, char* user ,char* password ,char* dbname,char* nm_table,int kk)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select id_paring from  %s where tipe_ac=%d",nm_table,kk); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {
     for (i = 0; i < num_fields; i++)
        {
      total_pairing = a+i;     
			pairing_id[total_pairing]=atoi(row[i]);
        //printf("data_library:%02X \n",pairing_id[total_pairing]);
        }
		a=a+i;
  	//printf("\n"); 
    }
	}
	mysql_close(con);
}
void get_id(char* server, char* user ,char* password ,char* dbname,char* nm_table)
{      
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  if (mysql_real_connect(con, server, user, password, 
          dbname, 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    
	char select[100];
 sprintf(select,"select value from %s where label='id'",nm_table); 
 if (mysql_query(con,select)) 
 { 
      finish_with_error(con);
 }


 MYSQL_RES *result = mysql_store_result(con);  
 if (result == NULL) 
 {
      finish_with_error(con);
 }

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	int i;
	int a=0;
	{
   while((row = mysql_fetch_row(result)) != NULL)
    {
     for (i = 0; i < num_fields; i++)
        {
      total_pairing = a+i;     
			mysql_id=atoi(row[i]);
        //printf("data_library:%02X \n",pairing_id[total_pairing]);
        }
		a=a+i;
  	//printf("\n"); 
    }
	}
	mysql_close(con);
}

