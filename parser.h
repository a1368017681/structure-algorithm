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
	void *first_num_start,*first_num_end;
	void *none_start,*none_end;
	void *first_minus_start;
	void *ip_start,*ip_end;	
}LOG;


#endif