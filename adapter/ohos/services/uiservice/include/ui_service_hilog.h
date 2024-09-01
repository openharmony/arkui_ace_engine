/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_ACE_UI_SERVICE_HILOG_H
#define OHOS_ACE_UI_SERVICE_HILOG_H

#include "hilog/log.h"

#define UISERVICE_LOG_DOMAIN 0xD003935
#define UISERVICE_LOG_TAG "AceUIService"

#define UISERVICE_FILENAME (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#define ACE_FMT_PREFIX "[%{public}s:%{public}d]"

#ifdef IS_RELEASE_VERSION
#define PRINT_LOG(level, fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_##level, UISERVICE_LOG_DOMAIN, UISERVICE_LOG_TAG, fmt, ##__VA_ARGS__)
#else
#define PRINT_LOG(level, fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_##level, UISERVICE_LOG_DOMAIN, UISERVICE_LOG_TAG, \
        ACE_FMT_PREFIX fmt, UISERVICE_FILENAME, __LINE__, ##__VA_ARGS__)
#endif

#define LOGE(fmt, ...) PRINT_LOG(ERROR, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) PRINT_LOG(WARN, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) PRINT_LOG(INFO, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) PRINT_LOG(DEBUG, fmt, ##__VA_ARGS__)

#endif
