/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <hilog/log.h>

typedef enum {
    Log_Debug,
    Log_Info,
    Log_Warn,
    Log_Error,
    Log_Fatal
} oh_sk_log_type;

void oh_sk_file_log(oh_sk_log_type type, const char* msg, ...);
const char* oh_sk_log_type_str(oh_sk_log_type type);

#ifdef OH_SK_LOG_TO_FILE

#define OH_SK_LOG_INFO(msg) oh_sk_file_log(oh_sk_log_type::Log_Info, msg)
#define OH_SK_LOG_INFO_A(msg, ...) oh_sk_file_log(oh_sk_log_type::Log_Info, msg, ##__VA_ARGS__)
#define OH_SK_LOG_ERROR(msg) oh_sk_file_log(oh_sk_log_type::Log_Error, msg)
#define OH_SK_LOG_ERROR_A(msg, ...) oh_sk_file_log(oh_sk_log_type::Log_Error, msg, ##__VA_ARGS__)
#define OH_SK_LOG_DEBUG(msg) oh_sk_file_log(oh_sk_log_type::Log_Debug, msg)
#define OH_SK_LOG_DEBUG_A(msg, ...) oh_sk_file_log(oh_sk_log_type::Log_Debug, msg, ##__VA_ARGS__)
#define OH_SK_LOG_WARN(msg) oh_sk_file_log(oh_sk_log_type::Log_Warn, msg)
#define OH_SK_LOG_WARN_A(msg, ...) oh_sk_file_log(oh_sk_log_type::Log_Warn, msg, ##__VA_ARGS__)
#define OH_SK_LOG_FATAL(msg) oh_sk_file_log(oh_sk_log_type::Log_Fatal, msg)
#define OH_SK_LOG_FATAL_A(msg, ...) oh_sk_file_log(oh_sk_log_type::Log_Fatal, msg, ##__VA_ARGS__)

#else

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

#endif
