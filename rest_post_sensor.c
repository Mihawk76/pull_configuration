#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>

char scoreData[10000];
char temp[1000];	


int test (int kwh[])
{
	int channel;
	for (channel = 0; channel <=18; channel++)
	{
		printf("Nilai Kwh %d %d \n", channel , kwh[channel]);
	}
	return 0;
}
/* function prototypes to define later */
char *get_config (char* location,uint16_t gateway_id, char* table, int max_column, char* column[]);
size_t static write_callback_func(void *buffer,
                        size_t size,
                        size_t nmemb,
                        void *userp);

/* the main function invoking */
/*int main()
{
    char *location_config = "http://35.166.240.126:3000/api/apps/config";
    char *content = NULL;

    content = get_config(location_config, 1002, "ac", "ac_name", "brand", "id_ir");

    printf("%s\n", content);
}*/
char *get_config (char* location,uint16_t gateway_id,char* table, int max_column, char* column[])
{
	char *response = NULL;
	snprintf(scoreData, sizeof scoreData, 
	/*"{\"id_gateway\": %d,\"table\":\"%s\",\"column\": [\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"]}",
	gateway_id, table, column_1, column_2, column_3, column_4, column_5, column_6, column_7, column_8, column_9);*/
	"{\"id_gateway\": %d,\"table\":\"%s\",\"column\": [",
	gateway_id, table);
	int n_column = 0;
  for(n_column=0;n_column<max_column;n_column++)
  {
    snprintf(temp, sizeof scoreData, "\"%s\"", 
    column[n_column]);
    strcat(scoreData, temp);
    if(n_column<(max_column-1)){
    snprintf(temp, sizeof scoreData, ",");
    strcat(scoreData, temp);
    }   
  }
  snprintf(temp, sizeof scoreData, "]}");
  strcat(scoreData, temp);
	printf("%s\n", scoreData);
	CURL *curl;
	CURLcode res; 
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl) { 
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
		char errbuf[CURL_ERROR_SIZE];
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
		//curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 0);
		curl_easy_setopt(curl, CURLOPT_URL, location);
		// provide a buffer to store errors in 
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
		// set the error buffer as empty before performing a request 
  	errbuf[0] = 0;
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
   	// follow locations specified by the response header 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, scoreData);
    // setting a callback function to return the data 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

    // passing the pointer to the response as the callback parameter 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
		  fprintf(stderr, "\ncurl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		  curl_easy_cleanup(curl);
			size_t len = strlen(errbuf);
    	fprintf(stderr, "\nlibcurl: (%d) ", res);
    	if(len)
      	fprintf(stderr, "ini error %s%s", errbuf,
              ((errbuf[len - 1] != '\n') ? "\n" : ""));
    	else
      	fprintf(stderr, "%s\n", curl_easy_strerror(res));
		}   
	curl_global_cleanup();
	//printf("\n\ntes %s\n",response);
	return response;
}
/* the function to invoke as the data recieved */
size_t static write_callback_func(void *buffer,
                        size_t size,
                        size_t nmemb,
                        void *userp)
{
    char **response_ptr =  (char**)userp;

    /* assuming the response is a string */
    *response_ptr = strndup(buffer, (size_t)(size *nmemb));

}


	
