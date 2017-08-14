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

enum {
	ls_start = 0,
	ls_major_digit,
	ls_minor_digit,
	ls_spaces_after_digit,
	ls_spaces_before_N,
	ls_N,
	ls_NO,
	ls_NON,
	ls_NONE,
	ls_spaces_before_first_minus,
	ls_first_minus,
	ls_spaces_after_first_minus
}log_state;

LOG_PARSE_RET log_parser(char* log_str,LOG *log){
	char ch;
	log_state = ls_start;
	uint len = strlen(log_str);
	uint i = 0;
	//printf("%d\n", len);
	for(i = 0; i < len; i++) {
		char *p = log_str[i];
		ch = *p;
		switch(log_state){
			case ls_start:
				if(IS_SPACE(ch)) continue;
				log->first_num_start = p;
				if(!IS_NUM_GT_ZERO(ch)){
					return LOG_PARSE_FAIL;
				}
				log_state = major_digit;
				break;
			case ls_major_digit:
				if(IS_NUM(ch)) continue;
				if(ch != '.') return LOG_PARSE_FAIL;
				log_state = ls_minor_digit;
				break;
			case ls_minor_digit:
				if(IS_NUM(ch)) continue;
				if(!IS_SPACE(ch))  return LOG_PARSE_FAIL;
				log_state = ls_spaces_before_N;
				log->first_num_end = p;
				break;
			case ls_spaces_before_N:
				switch(ch){
					case ' ':
						continue;
					case 'N':
						log_state = ls_N;
						log->none_start = p;
					default:
						return LOG_PARSE_FAIL;
				}
			case ls_N:
				switch(ch){
					case 'O':
						log_state = ls_NO;
					default:
						return LOG_PARSE_FAIL;
				}
			case ls_NO:
				switch(ch) {
					case 'N':
						log_state = ls_NON;
					default:
						return LOG_PARSE_FAIL;
				}
			case ls_NON:
				switch(ch){
					case 'E':
						log_state = ls_NONE;
						log->none_end = p;
					default:
						return LOG_PARSE_FAIL;
				}
			case ls_NONE:
				switch(ch){

				}
		}
	}
	return LOG_PARSE_OK;
}