#include <json/json.h>
#include <stdio.h>

const char* config_data[100][20];
int arraylen = 0;
 
void json_parse(char* string, int max_column, char* column[]) {
 //enum json_type type;
	struct json_object *medi_array, *medi_array_obj, *medi_array_obj_name;
 	int i = 0;
	int n_column = 0;
 	medi_array= json_tokener_parse(string);
	//medi_array = jobj;
	arraylen = json_object_array_length(medi_array);
	for (i=0;i < arraylen;i++)
	{
		medi_array_obj = json_object_array_get_idx(medi_array, i);
		if (medi_array_obj == NULL)
		{
			printf("eror data null\n");
		}
		for(n_column=0;n_column<max_column;n_column++)
		{
			if (json_object_object_get_ex(medi_array_obj, column[n_column], &medi_array_obj_name))
			{
				//printf("data ada\n");
			}
			else{
				printf("data not found\n");
			}
			config_data [i][n_column] = json_object_get_string(medi_array_obj_name);
  		printf("%s:%s ", column[n_column], config_data [i][n_column]);
		}
		printf("\n");
  	// print out the name attribute
	}
}
/*
int main() {
	char * string = "{ \"sitename\" : 2, \"purpose\" : \"programming tips\", \"platform\" : \"wordpress\"}";
	char  mainstring[]="{\"ac_name\":\"AC1\",\"brand\":\"LG\",\"id_ir\":1}";
	char * string_2="{\"Data\":[{\"ac_name\":\"AC1\",\"brand\":\"LG\",\"id_ir\":1},{\"ac_name\":\"AC2\",\"brand\":\"Nexian\",\"id_ir\":1},{\"ac_name\":\"AC3\",\"brand\":\"Panasonic\",\"id_ir\":1},{\"ac_name\":\"AC4\",\"brand\":\"Panasonic\",\"id_ir\":1}]}";
 	printf ("JSON string: %s\n", string_2);
	json_parse(string_2);
}
*/
