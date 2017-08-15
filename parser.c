#include "parser.h"
#include "debug.h"

typedef unsigned int uint;

#define CR '\r'
#define LF '\n'
#define CRLF '\r\n'
#define CRLFCRLF '\r\n\r\n'

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#define LOWER(c) (unsigned char)(c | 0x20)
#define IS_LOWERCASE(c) ((c) >= 'a' && (c) <= 'z')
#define IS_UPPERCASE(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_ALPHA(c) (LOWER(c) >= 'a' && LOWER(c) <= 'z')
#define IS_NUM(c)           ((c) >= '0' && (c) <= '9')
#define IS_NUM_GT_ZERO(c)      ((c) >= '1' && (c) <= '9')
#define IS_ALPHANUM(c)      (IS_ALPHA(c) || IS_NUM(c))
#define IS_HEX(c)           (IS_NUM(c) || (LOWER(c) >= 'a' && LOWER(c) <= 'f'))
#define IS_SPACE(c)   ((c) == ' ')
#define IS_MINUS(c)   ((c) == '-')
#define IS_QUATOTION(c)    ((c) == '"')

/*
这里写的其实是个准确性比较低的状态机，因为每一列的具体格式不是很明了，只能写个简单的文法（依靠空格和引号判断状态切换）
复杂度的话只是扫一遍O(n)，程序大致意思就是根据空格，引号还有当前状态判断下一个状态是什么，程序意思是比较简单的
*/

enum {
	ls_start = 0,
	ls_digit,
	ls_NONE,
	ls_first_minus,
	ls_ip,
	ls_first_quatotion,
	ls_first_quatotion_end,
	ls_domain,
	ls_uri,
	ls_method,
	ls_second_quatotion,
	ls_second_quatotion_end,
	ls_status_code,
	ls_third_quatotion,
	ls_third_quatotion_end,
	ls_fourth_quatotion,
	ls_fourth_quatotion_end,
	ls_fifth_quatotion,
	ls_fifth_quatotion_end,
	ls_sixth_quatotion,
	//ls_sixth_quatotion_end,
	ls_done
}log_state;

LOG_PARSE_RET log_parser(char* log_str,LOG *log){
	char ch;
	log_state = ls_start;
	uint len = strlen(log_str);
	uint i = 0;
	//printf("%d\n", len);
	for(i = 0; i < len; i++) {
		char *p = &log_str[i];
		ch = *p;
		switch(log_state){
			case ls_start:
				log->col1_start = p;
				log_state = ls_digit;
				break;
			case ls_digit:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_NUM(ch)) continue;
				else if(IS_SPACE(ch)){
					log->col1_end = p;
					log->col2_start = p+1;
					log_state = ls_NONE;
				}
				break;
			case ls_NONE:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_ALPHA(ch)) continue;
				else if(IS_SPACE(ch)){
					log->col2_end = p;
					log->col3_start = p+1;
					log_state = ls_first_minus;
				}
				break;
			case ls_first_minus:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_MINUS(ch)) continue;
				else if(IS_SPACE(ch)){
					log->col3_end = p;
					//printf("%c dfdsf\n", *(p-1));
					log->col4_start = p+1;
					log_state = ls_ip;
				};
				break;
			case ls_ip:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_QUATOTION(ch)) continue;
				else{
					log->col4_end = p-1;
					log->col5_start = p;
					log_state = ls_first_quatotion;
				} 
				break;
			case ls_first_quatotion:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_QUATOTION(ch)) continue;
				else{
					log->col5_end = p+1;
					//log->col6_start = p+1;
					log_state = ls_first_quatotion_end;
				}
				break;
			case ls_first_quatotion_end:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_SPACE(ch)) continue;
				else {
					log->col6_start = p;
					log_state = ls_domain;
				}
				break;
			case ls_domain:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_ALPHA(ch) || ch == '.') continue;
				else if(IS_SPACE(ch)) {
					log->col6_end = p;
					log->col7_start = p+1;
					log_state = ls_uri;
				}
				break;
			case ls_uri:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_SPACE(ch)){
					continue;
				}else if(IS_SPACE(ch)){
					log->col7_end = p;
					log->col8_start = p+1;
					log_state = ls_method;
				}
				break;
			case ls_method:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_UPPERCASE(ch) || IS_SPACE(ch)) continue;
				else if(IS_QUATOTION(ch)) {
					log->col8_end = p-1;
					//printf("%c ddds\n", *(p-2));
					log->col9_start = p;
					log_state = ls_second_quatotion;
				}
				break;
			case ls_second_quatotion:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_QUATOTION(ch)) continue;
				else{
					log->col9_end = p+1;
					log_state = ls_second_quatotion_end;
				}
				break;
			case ls_second_quatotion_end:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_SPACE(ch)) continue;
				else{
					log->col10_start = p;
					log_state = ls_status_code;
				}
				break;
			case ls_status_code:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_NUM(ch)) continue;
				else if(IS_QUATOTION(ch)){
					log->col10_end = p;
					log->col11_start = p;
					log_state = ls_third_quatotion;
				}
				break;
			case ls_third_quatotion:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_QUATOTION(ch)) continue;
				else{
					log->col11_end = p+1;
					log_state = ls_third_quatotion_end;
				}
				break;
			case ls_third_quatotion_end:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_SPACE(ch)) continue;
				else{
					log->col12_start = p;
					log_state = ls_fourth_quatotion;
				}
				break;
			case ls_fourth_quatotion:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_QUATOTION(ch)) continue;
				else{
					log->col12_end = p+1;
					log_state = ls_fourth_quatotion_end;
				}
				break;
			case ls_fourth_quatotion_end:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_SPACE(ch)) continue;
				else{
					log->col13_start = p;
					log_state = ls_fifth_quatotion;
				}
				break;
			case ls_fifth_quatotion:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_QUATOTION(ch)) continue;
				else{
					log->col13_end = p+1;
					log_state = ls_fifth_quatotion_end;
				}
				break;
			case ls_fifth_quatotion_end:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(IS_SPACE(ch)) continue;
				else{
					log->col14_start = p;
					log_state = ls_sixth_quatotion;
				}
				break;
			case ls_sixth_quatotion:
				if(ch == LF) return LOG_PARSE_FAIL;
				if(!IS_QUATOTION(ch)) continue;
				else{
					log->col14_end = p+1;
					log_state = ls_done;
				}
				break;
			case ls_done:
				break;
 		}
	}
	//printf("%d\n", log_state);
	if(log_state == ls_done) return LOG_PARSE_OK;
	else return LOG_PARSE_FAIL;
}