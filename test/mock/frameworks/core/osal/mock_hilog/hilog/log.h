#ifndef HILOG_MOCK_LOG_H
#define HILOG_MOCK_LOG_H

typedef enum {
    LOG_LEVEL_MIN = 0,
    LOG_DEBUG = 3,
    LOG_INFO = 4,
    LOG_WARN = 5,
    LOG_ERROR = 6,
    LOG_FATAL = 7,
    LOG_LEVEL_MAX,
} LogLevel;

typedef enum {
    LOG_TYPE_MIN = 0,
    LOG_APP = 0,
    LOG_INIT = 1,
    LOG_CORE = 3,
    LOG_KMSG = 4,
    LOG_TYPE_MAX
} LogType;

static inline void HILOG_IMPL(LogType type, LogLevel level, unsigned int domain, const char* tag, const char* fmt, ...)
{
    (void)type;
    (void)level;
    (void)domain;
    (void)tag;
    (void)fmt;
}

#endif // HILOG_MOCK_LOG_H
