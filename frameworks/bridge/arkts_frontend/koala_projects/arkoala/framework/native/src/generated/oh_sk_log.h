#pragma once

#include <hilog/log.h>

#define OH_SK_LOG_INFO(msg) OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "Koala", msg)
#define OH_SK_LOG_INFO_A(msg, ...) OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00, "Koala", msg, ##__VA_ARGS__)
#define OH_SK_LOG_ERROR(msg) OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "Koala", msg)
#define OH_SK_LOG_ERROR_A(msg, ...) OH_LOG_Print(LOG_APP, LOG_ERROR, 0xFF00, "Koala", msg, ##__VA_ARGS__)
#define OH_SK_LOG_DEBUG(msg) OH_LOG_Print(LOG_APP, LOG_DEBUG, 0xFF00, "Koala", msg)
#define OH_SK_LOG_DEBUG_A(msg, ...) OH_LOG_Print(LOG_APP, LOG_DEBUG, 0xFF00, "Koala", msg, ##__VA_ARGS__)
#define OH_SK_LOG_WARN(msg) OH_LOG_Print(LOG_APP, LOG_WARN, 0xFF00, "Koala", msg)
#define OH_SK_LOG_WARN_A(msg, ...) OH_LOG_Print(LOG_APP, LOG_WARN, 0xFF00, "Koala", msg, ##__VA_ARGS__)
#define OH_SK_LOG_FATAL(msg) OH_LOG_Print(LOG_APP, LOG_FATAL, 0xFF00, "Koala", msg)
#define OH_SK_LOG_FATAL_A(msg, ...) OH_LOG_Print(LOG_APP, LOG_FATAL, 0xFF00, "Koala", msg, ##__VA_ARGS__)