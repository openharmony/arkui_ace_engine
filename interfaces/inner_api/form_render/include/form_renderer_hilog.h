/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FORM_RENDERER_HILOG_H
#define FORM_RENDERER_HILOG_H

#define CONFIG_HILOG
#ifdef CONFIG_HILOG
#include "hilog/log.h"

#ifdef HILOG_FATAL
#undef HILOG_FATAL
#endif

#ifdef HILOG_ERROR
#undef HILOG_ERROR
#endif

#ifdef HILOG_WARN
#undef HILOG_WARN
#endif

#ifdef HILOG_INFO
#undef HILOG_INFO
#endif

#ifdef HILOG_DEBUG
#undef HILOG_DEBUG
#endif

#ifndef FR_LOG_DOMAIN
#define FR_LOG_DOMAIN 0xD0039FF
#endif

#ifndef FR_LOG_TAG
#define FR_LOG_TAG "FormRenderer"
#endif

#ifdef LOG_LABEL
#undef LOG_LABEL
#endif

static constexpr OHOS::HiviewDFX::HiLogLabel LOG_LABEL = {LOG_CORE, FR_LOG_DOMAIN, FR_LOG_TAG};

#define FR_FILENAME (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#ifdef IS_RELEASE_VERSION
#define PRINT_HILOG(level, fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_##level, FR_LOG_DOMAIN, FR_LOG_TAG, fmt, ##__VA_ARGS__)
#else
#define PRINT_HILOG(level, fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_##level, FR_LOG_DOMAIN, FR_LOG_TAG, "[%{public}s:%{public}d]" fmt, \
        FR_FILENAME, __LINE__, ##__VA_ARGS__)
#endif

#define HILOG_FATAL(fmt, ...) PRINT_HILOG(FATAL, fmt, ##__VA_ARGS__)
#define HILOG_ERROR(fmt, ...) PRINT_HILOG(ERROR, fmt, ##__VA_ARGS__)
#define HILOG_WARN(fmt, ...) PRINT_HILOG(WARN, fmt, ##__VA_ARGS__)
#define HILOG_INFO(fmt, ...) PRINT_HILOG(INFO, fmt, ##__VA_ARGS__)
#define HILOG_DEBUG(fmt, ...) PRINT_HILOG(DEBUG, fmt, ##__VA_ARGS__)
#else

#define HILOG_FATAL(...)
#define HILOG_ERROR(...)
#define HILOG_WARN(...)
#define HILOG_INFO(...)
#define HILOG_DEBUG(...)
#endif  // CONFIG_HILOG

#endif  // FORM_RENDERER_HILOG_H
