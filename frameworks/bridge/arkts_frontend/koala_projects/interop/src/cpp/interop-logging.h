/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef _INTEROP_LGGING_H
#define _INTEROP_LGGING_H

#include <stdio.h>
#include <stdint.h>

#if defined(KOALA_OHOS)
#include "oh_sk_log.h"
#define LOG(msg) OH_SK_LOG_INFO(msg);
#define LOGI(msg, ...) OH_SK_LOG_INFO_A(msg, ##__VA_ARGS__);
#define LOGE(msg, ...) OH_SK_LOG_ERROR_A(msg, ##__VA_ARGS__);
#define LOG_PUBLIC "{public}"
#else
#define LOG(msg) fprintf(stdout, msg "\n");
#define LOGI(msg, ...) fprintf(stdout, msg "\n", ##__VA_ARGS__);
#define LOGE(msg, ...) fprintf(stderr, msg "\n", ##__VA_ARGS__);
#define LOG_PUBLIC ""
#endif

#if defined(KOALA_WINDOWS)
#define INTEROP_API_EXPORT __declspec(dllexport)
#else
#define INTEROP_API_EXPORT __attribute__((visibility("default")))
#endif

// Grouped logs. Keep consistent with type in ServiceGroupLogger
typedef struct GroupLogger {
    void (*startGroupedLog)(int kind);
    void (*stopGroupedLog)(int kind);
    void (*appendGroupedLog)(int kind, const char* str);
    const char* (*getGroupedLog)(int kind);
    int (*needGroupedLog)(int kind);
} GroupLogger;

const GroupLogger* GetDefaultLogger();

#endif // _INTEROP_LOGGING_H