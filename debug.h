#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <errno.h>

#define MAX_BUF 8192

#define NDEBUG 
#ifdef NDEBUG
#define DEBUG(M, ...)
#else
#define DEBUG(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define ERRNO_INFO() (errno == 0 ? "None" : strerror(errno))

#define LOG_ERROR(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ERRNO_INFO(), ##__VA_ARGS__)

#define LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, ERRNO_INFO(), ##__VA_ARGS__)

#define LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define CHECK(A, M, ...) if(!(A)) { LOG_ERROR(M "\n", ##__VA_ARGS__);  }

#define CHECK_EXIT(A, M, ...) if(!(A)) { LOG_ERROR(M "\n", ##__VA_ARGS__); exit(1);}

#define CHECK_BREAK(A, M, ...) if((!(A))) { LOG_ERROR(M "\n", ##__VA_ARGS__); break;}

#define CHECK_DEBUG(A, M, ...) if(!(A)) { debug(M "\n", ##__VA_ARGS__); /* exit(1); */}

#endif
