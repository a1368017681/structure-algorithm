#include "parser.h"
#include "debug.h"

#define MAX_LOG_NUM 8192
LOG log[MAX_LOG_NUM];

int main() {
	FILE* fp = fopen("log.txt","r");
	CHECK_EXIT(fp != NULL,"open file failed!");
	char* log_str = (char*)malloc(sizeof(char)*MAX_BUF);
	int cnt = 0;
	while(!feof(fp)){
		fgets(log_str,MAX_BUF,fp);
		log_parser(log_str,&log[cnt++]);
		if(cnt >= MAX_LOG_NUM) break;
		printf("%s", log_str);
	}
	fclose(fp);
	return 0;
}