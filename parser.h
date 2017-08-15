#ifndef _LOG_PARSE_H_
#define _LOG_PARSE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
	LOG_PARSE_OK = 0,
	LOG_PARSE_FAIL
}LOG_PARSE_RET;

typedef struct {
	void *col1_start,*col1_end;
	void *col2_start,*col2_end;
	void *col3_start,*col3_end;
	void *col4_start,*col4_end;
	void *col5_start,*col5_end;
	void *col6_start,*col6_end;	
	void *col7_start,*col7_end;
	void *col8_start,*col8_end;
	void *col9_start,*col9_end;
	void *col10_start,*col10_end;
	void *col11_start,*col11_end;
	void *col12_start,*col12_end;
	void *col13_start,*col13_end;
	void *col14_start,*col14_end;
}LOG;

LOG_PARSE_RET log_parser(char* log_str,LOG *log);

#endif