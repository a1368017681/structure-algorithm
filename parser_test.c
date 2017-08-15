#include "parser.h"
#include "debug.h"

#define MAX_LOG_NUM 8192
LOG Log[MAX_LOG_NUM];
char log_str[MAX_BUF];

int main() {
	FILE* fp = fopen("log.txt","r");
	CHECK_EXIT(fp != NULL,"open file failed!");
	//char* log_str = (char*)malloc(sizeof(char)*MAX_BUF);
	int cnt = 0;
	while(!feof(fp)){
		memset(log_str,'\0',sizeof(log_str));
		fgets(log_str,MAX_BUF,fp);
		LOG_PARSE_RET ret = log_parser(log_str,&(Log[cnt++]));
		CHECK_BREAK(ret == LOG_PARSE_OK,"parse %d line error",cnt);
		if(cnt >= MAX_LOG_NUM) break;

		//printf("%s\n\n", log_str);
		//printf("%c %d %c\n",(Log[cnt-1].col7_start),(int)(Log[cnt-1].col7_end - Log[cnt-1].col7_start),(Log[cnt-1].col7_end-1));
		printf("%d line is : \n", cnt);
		printf("%.*s\n",(int)(Log[cnt-1].col1_end - Log[cnt-1].col1_start),Log[cnt-1].col1_start);
		printf("%.*s\n",(int)(Log[cnt-1].col2_end - Log[cnt-1].col2_start),Log[cnt-1].col2_start);
		printf("%.*s\n",(int)(Log[cnt-1].col3_end - Log[cnt-1].col3_start),Log[cnt-1].col3_start);
		printf("%.*s\n",(int)(Log[cnt-1].col4_end - Log[cnt-1].col4_start),Log[cnt-1].col4_start);
		printf("%.*s\n",(int)(Log[cnt-1].col5_end - Log[cnt-1].col5_start),Log[cnt-1].col5_start);
		printf("%.*s\n",(int)(Log[cnt-1].col6_end - Log[cnt-1].col6_start),Log[cnt-1].col6_start);
		printf("%.*s\n",(int)(Log[cnt-1].col7_end - Log[cnt-1].col7_start),Log[cnt-1].col7_start);
		printf("%.*s\n",(int)(Log[cnt-1].col8_end - Log[cnt-1].col8_start),Log[cnt-1].col8_start);
		printf("%.*s\n",(int)(Log[cnt-1].col9_end - Log[cnt-1].col9_start),Log[cnt-1].col9_start);
		printf("%.*s\n",(int)(Log[cnt-1].col10_end - Log[cnt-1].col10_start),Log[cnt-1].col10_start);
		printf("%.*s\n",(int)(Log[cnt-1].col11_end - Log[cnt-1].col11_start),Log[cnt-1].col11_start);
		printf("%.*s\n",(int)(Log[cnt-1].col12_end - Log[cnt-1].col12_start),Log[cnt-1].col12_start);
		printf("%.*s\n",(int)(Log[cnt-1].col13_end - Log[cnt-1].col13_start),Log[cnt-1].col13_start);
		printf("%.*s\n\n",(int)(Log[cnt-1].col14_end - Log[cnt-1].col14_start),Log[cnt-1].col14_start);

	}
	fclose(fp);
	return 0;
}