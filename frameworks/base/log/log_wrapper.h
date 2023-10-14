/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_LOG_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_LOG_WRAPPER_H

#include <cstdarg>
#include <cstdint>
#include <cstring>
#include <string>

#include "base/utils/macros.h"
#include "base/utils/system_properties.h"

#ifdef ACE_INSTANCE_LOG
#define ACE_FMT_PREFIX "[%{public}s(%{public}s)-(%{public}d)] "
#define ACE_LOG_ID , OHOS::Ace::LogWrapper::GetId()
#else
#define ACE_FMT_PREFIX "[%{private}s(%{private}s)] "
#define ACE_LOG_ID
#endif

#define PRINT_LOG(level, tag, fmt, ...)                                                                         \
    do {                                                                                                        \
        if (OHOS::Ace::LogWrapper::JudgeLevel(OHOS::Ace::LogLevel::level)) {                                    \
            OHOS::Ace::LogWrapper::PrintLog(OHOS::Ace::LogDomain::FRAMEWORK, OHOS::Ace::LogLevel::level, tag,   \
                ACE_FMT_PREFIX fmt, OHOS::Ace::LogWrapper::GetBriefFileName(__FILE__), __FUNCTION__ ACE_LOG_ID, \
                ##__VA_ARGS__);                                                                                 \
        }                                                                                                       \
    } while (0)

#define LOGD(fmt, ...) TAG_LOGD(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) TAG_LOGI(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) TAG_LOGW(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) TAG_LOGE(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGF(fmt, ...) TAG_LOGF(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)

#ifdef ACE_DEBUG_LOG
#define TAG_LOGD(tag, fmt, ...) PRINT_LOG(DEBUG, tag, fmt, ##__VA_ARGS__)
#else
#define TAG_LOGD(tag, fmt, ...) ((void)0)
#endif
#define TAG_LOGI(tag, fmt, ...) PRINT_LOG(INFO, tag, fmt, ##__VA_ARGS__)
#define TAG_LOGW(tag, fmt, ...) PRINT_LOG(WARN, tag, fmt, ##__VA_ARGS__)
#define TAG_LOGE(tag, fmt, ...) PRINT_LOG(ERROR, tag, fmt, ##__VA_ARGS__)
#define TAG_LOGF(tag, fmt, ...) PRINT_LOG(FATAL, tag, fmt, ##__VA_ARGS__)

#define LOG_DESTROY() LOGI("destroyed")
#define LOG_FUNCTION() LOGD("function track: %{public}s", __FUNCTION__)

#define PRINT_APP_LOG(level, fmt, ...) \
    OHOS::Ace::LogWrapper::PrintLog(   \
        OHOS::Ace::LogDomain::JS_APP, OHOS::Ace::LogLevel::level, OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)

#define APP_LOGD(fmt, ...) PRINT_APP_LOG(DEBUG, fmt, ##__VA_ARGS__)
#define APP_LOGI(fmt, ...) PRINT_APP_LOG(INFO, fmt, ##__VA_ARGS__)
#define APP_LOGW(fmt, ...) PRINT_APP_LOG(WARN, fmt, ##__VA_ARGS__)
#define APP_LOGE(fmt, ...) PRINT_APP_LOG(ERROR, fmt, ##__VA_ARGS__)
#define APP_LOGF(fmt, ...) PRINT_APP_LOG(FATAL, fmt, ##__VA_ARGS__)

namespace OHOS::Ace {

enum class AceLogTag : uint8_t {
    DEFAULT = 0,
    ACE_SUB_WINDOW,
    ACE_FORM,
    ACE_DRAG,
    ACE_VIDEO,
    ACE_SCROLL,
    ACE_SCROLLABLE,
    ACE_INNER_SCROLL_BAR,
    ACE_OUTER_SCROLL_BAR,
    ACE_FONT,
    ACE_TEXTINPUT,
    ACE_SWIPER,
    ACE_TABS,
    ACE_RICH_TEXT,
    ACE_WEB,
    ACE_IMAGE,
    ACE_RATING,
};

enum class LogDomain : uint32_t {
    FRAMEWORK = 0,
    JS_APP,
};

enum class LogLevel : uint32_t {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    FATAL,
};

class ACE_FORCE_EXPORT LogWrapper final {
public:
    static bool JudgeLevel(LogLevel level)
    {
        if (level == LogLevel::DEBUG) {
            return SystemProperties::GetDebugEnabled();
        }
        return level_ <= level;
    }

    static void SetLogLevel(LogLevel level)
    {
        level_ = level;
    }

    static LogLevel GetLogLevel()
    {
        return level_;
    }

    static const char* GetBriefFileName(const char* name)
    {
        static const char separator = GetSeparatorCharacter();
        const char* p = strrchr(name, separator);
        return p != nullptr ? p + 1 : name;
    }

    static void StripFormatString(const std::string& prefix, std::string& str)
    {
        for (auto pos = str.find(prefix, 0); pos != std::string::npos; pos = str.find(prefix, pos)) {
            str.erase(pos, prefix.size());
        }
    }

    static void ReplaceFormatString(const std::string& prefix, const std::string& replace, std::string& str)
    {
        for (auto pos = str.find(prefix, 0); pos != std::string::npos; pos = str.find(prefix, pos)) {
            str.replace(pos, prefix.size(), replace);
        }
    }

    static void PrintLog(LogDomain domain, LogLevel level, AceLogTag tag, const char* fmt, ...)
        __attribute__((__format__(os_log, 4, 5)))
    {
        va_list args;
        va_start(args, fmt);
        PrintLog(domain, level, tag, fmt, args);
        va_end(args);
    }

    // MUST implement these interface on each platform.
    static char GetSeparatorCharacter();
    static void PrintLog(LogDomain domain, LogLevel level, AceLogTag tag, const char* fmt, va_list args);
    static int32_t GetId();

private:
    LogWrapper() = delete;
    ~LogWrapper() = delete;

    static LogLevel level_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_LOG_WRAPPER_H
