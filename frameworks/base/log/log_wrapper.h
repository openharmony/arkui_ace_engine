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
#define ACE_FMT_PREFIX "[%{public}s(%{public}s)-(%{public}s)] "
#define ACE_LOG_ID_WITH_REASON , OHOS::Ace::LogWrapper::GetIdWithReason().c_str()
#else
#define ACE_FMT_PREFIX "[%{private}s(%{private}s)] "
#define ACE_LOG_ID_WITH_REASON
#endif

#define PRINT_LOG(level, tag, fmt, ...)                                                                       \
    do {                                                                                                      \
        if (OHOS::Ace::LogWrapper::JudgeLevel(OHOS::Ace::LogLevel::level)) {                                  \
            OHOS::Ace::LogWrapper::PrintLog(OHOS::Ace::LogDomain::FRAMEWORK, OHOS::Ace::LogLevel::level, tag, \
                ACE_FMT_PREFIX fmt, OHOS::Ace::LogWrapper::GetBriefFileName(__FILE__),                        \
                __FUNCTION__ ACE_LOG_ID_WITH_REASON, ##__VA_ARGS__);                                          \
        }                                                                                                     \
    } while (0)

#define LOGD(fmt, ...) TAG_LOGD(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) TAG_LOGI(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) TAG_LOGW(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) TAG_LOGE(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)
#define LOGF(fmt, ...) TAG_LOGF(OHOS::Ace::AceLogTag::DEFAULT, fmt, ##__VA_ARGS__)

#define TAG_LOGD(tag, fmt, ...) PRINT_LOG(DEBUG, tag, fmt, ##__VA_ARGS__)
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
    DEFAULT = 0,              // C03900
    ACE_ALPHABET_INDEXER,     // C03901
    ACE_COUNTER,              // C03902
    ACE_SUB_WINDOW,           // C03903
    ACE_FORM,                 // C03904
    ACE_DRAG,                 // C03905
    ACE_VIDEO,                // C03906
    ACE_COMPONENT_SNAPSHOT,   // C03907
    ACE_CANVAS,               // C03908
    ACE_REFRESH,              // C03909
    ACE_SCROLL,               // C0390A
    ACE_SCROLLABLE,           // C0390B
    ACE_FONT,                 // C0390C
    ACE_OVERLAY,              // C0390D
    ACE_DIALOG_TIMEPICKER,    // C0390E
    ACE_DIALOG,               // C0390F
    ACE_PANEL,                // C03910
    ACE_MENU,                 // C03911
    ACE_TEXTINPUT,            // C03912
    ACE_TEXT,                 // C03913
    ACE_TEXT_FIELD,           // C03914
    ACE_SWIPER,               // C03915
    ACE_TABS,                 // C03916
    ACE_BLANK,                // C03917
    ACE_GRIDROW,              // C03918
    ACE_INPUTTRACKING,        // C03919
    ACE_RICH_TEXT,            // C0391A
    ACE_WEB,                  // C0391B
    ACE_FOCUS,                // C0391C
    ACE_MOUSE,                // C0391D
    ACE_GESTURE,              // C0391E
    ACE_IMAGE,                // C0391F
    ACE_RATING,               // C03920
    ACE_LIST,                 // C03921
    ACE_NAVIGATION,           // C03922
    ACE_WATERFLOW,            // C03923
    ACE_ACCESSIBILITY,        // C03924
    ACE_ROUTER,               // C03925
    ACE_THEME,                // C03926
    ACE_BORDER_IMAGE,         // C03927
    ACE_GRID,                 // C03928
    ACE_PLUGIN_COMPONENT,     // C03929
    ACE_UIEXTENSIONCOMPONENT, // C0392A
    ACE_IF,                   // C0392B
    ACE_FOREACH,              // C0392C
    ACE_LAZY_FOREACH,         // C0392D
    ACE_GAUGE,                // C0392E
    ACE_HYPERLINK,            // C0392F
    ACE_ANIMATION,            // C03930
    ACE_XCOMPONENT,           // C03931
    ACE_AUTO_FILL,            // C03932
    ACE_KEYBOARD,             // C03933
    ACE_UIEVENT,              // C03934
    ACE_UI_SERVICE,           // C03935 ace_engine/adapter/ohos/services/uiservice/src/ui_service_hilog.h
    ACE_DISPLAY_SYNC,         // C03936
    ACE_RESOURCE,             // C03937
    ACE_SIDEBAR,              // C03938
    ACE_GEOMETRY_TRANSITION,  // C03939
    ACE_DOWNLOAD_MANAGER,     // C0393A
    ACE_WINDOW_SCENE,         // C0393B
    ACE_NODE_CONTAINER,       // C0393C
    ACE_NATIVE_NODE,          // C0393D
    ACE_DYNAMIC_COMPONENT,    // C0393E
    ACE_MARQUEE,              // C0393F
    ACE_OBSERVER,             // C03940

    FORM_RENDER = 255, // C039FF FormRenderer
    END = 256,         // Last one, do not use
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
#ifdef ACE_INSTANCE_LOG
    static int32_t GetId();
    static const std::string GetIdWithReason();
#endif

private:
    LogWrapper() = delete;
    ~LogWrapper() = delete;

    static LogLevel level_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_LOG_WRAPPER_H
