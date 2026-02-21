#ifndef _LOGGER_H
#define _LOGGER_H

typedef enum { LOG_INFO, LOG_DEBUG, LOG_WARN, LOG_ERROR } log_level_t;

void nrx_log(log_level_t log_level, const char *fmt, ...);

#endif
