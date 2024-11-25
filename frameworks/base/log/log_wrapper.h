/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
#include <unordered_map>

#include "base/utils/macros.h"
#include "base/utils/system_properties.h"

#ifdef ACE_INSTANCE_LOG
#define ACE_FMT_PREFIX "[%{public}s(%{public}d)-(%{public}s)] "
#define ACE_LOG_ID_WITH_REASON , OHOS::Ace::LogWrapper::GetIdWithReason().c_str()
#else
#define ACE_FMT_PREFIX "[%{private}s(%{private}d)] "
#define ACE_LOG_ID_WITH_REASON
#endif

#if defined(USE_HILOG)
#include "hilog/log.h"
constexpr uint32_t ACE_DOMAIN = 0xD003900;
constexpr uint32_t APP_DOMAIN = 0xC0D0;
#ifdef IS_RELEASE_VERSION
#define PRINT_LOG(level, tag, fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_##level, (tag + ACE_DOMAIN), (OHOS::Ace::g_DOMAIN_CONTENTS_MAP.at(tag)),         \
            "[(%{public}s)] " fmt, OHOS::Ace::LogWrapper::GetIdWithReason().c_str(), ##__VA_ARGS__)
#else
#define PRINT_LOG(level, tag, fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_##level, (tag + ACE_DOMAIN), (OHOS::Ace::g_DOMAIN_CONTENTS_MAP.at(tag)),         \
            ACE_FMT_PREFIX fmt, OHOS::Ace::LogWrapper::GetBriefFileName(__FILE__),                            \
            __LINE__ ACE_LOG_ID_WITH_REASON, ##__VA_ARGS__)
#endif
#define PRINT_APP_LOG(level, fmt, ...) HILOG_IMPL(LOG_APP, LOG_##level, APP_DOMAIN, "JSAPP", fmt, ##__VA_ARGS__)
#else
#define PRINT_LOG(level, tag, fmt, ...)                                                                       \
    do {                                                                                                      \
        if (OHOS::Ace::LogWrapper::JudgeLevel(OHOS::Ace::LogLevel::level)) {                                  \
            OHOS::Ace::LogWrapper::PrintLog(OHOS::Ace::LogDomain::FRAMEWORK, OHOS::Ace::LogLevel::level, tag, \
                ACE_FMT_PREFIX fmt, OHOS::Ace::LogWrapper::GetBriefFileName(__FILE__),                        \
                __LINE__ ACE_LOG_ID_WITH_REASON, ##__VA_ARGS__);                                          \
        }                                                                                                     \
    } while (0)

#define PRINT_APP_LOG(level, fmt, ...) \
    OHOS::Ace::LogWrapper::PrintLog(   \
        OHOS::Ace::LogDomain::JS_APP, OHOS::Ace::LogLevel::level, OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN,   \
        fmt, ##__VA_ARGS__)
#endif

#define LOGD(fmt, ...) TAG_LOGD(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) TAG_LOGI(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, fmt, ##__VA_ARGS__)
#define LOGF(fmt, ...) TAG_LOGF(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, fmt, ##__VA_ARGS__)

#define TAG_LOGD(tag, fmt, ...) PRINT_LOG(DEBUG, tag, fmt, ##__VA_ARGS__)
#define TAG_LOGI(tag, fmt, ...) PRINT_LOG(INFO, tag, fmt, ##__VA_ARGS__)
#define TAG_LOGW(tag, fmt, ...) PRINT_LOG(WARN, tag, fmt, ##__VA_ARGS__)
#define TAG_LOGE(tag, fmt, ...) PRINT_LOG(ERROR, tag, fmt, ##__VA_ARGS__)
#define TAG_LOGF(tag, fmt, ...) PRINT_LOG(FATAL, tag, fmt, ##__VA_ARGS__)

#define LOG_FUNCTION() LOGD("function track: %{public}s", __FUNCTION__)

#define APP_LOGD(fmt, ...) PRINT_APP_LOG(DEBUG, fmt, ##__VA_ARGS__)
#define APP_LOGI(fmt, ...) PRINT_APP_LOG(INFO, fmt, ##__VA_ARGS__)
#define APP_LOGW(fmt, ...) PRINT_APP_LOG(WARN, fmt, ##__VA_ARGS__)
#define APP_LOGE(fmt, ...) PRINT_APP_LOG(ERROR, fmt, ##__VA_ARGS__)
#define APP_LOGF(fmt, ...) PRINT_APP_LOG(FATAL, fmt, ##__VA_ARGS__)

#define JSON_STRING_PUT_INT(jsonValue, var) (jsonValue)->Put(#var, static_cast<int64_t>(var))
#define JSON_STRING_PUT_BOOL(jsonValue, var) (jsonValue)->Put(#var, (var))
#define JSON_STRING_PUT_STRING(jsonValue, var) (jsonValue)->Put(#var, (var).c_str())
#define JSON_STRING_PUT_STRINGABLE(jsonValue, var) (jsonValue)->Put(#var, (var).ToString().c_str())

#define JSON_STRING_PUT_OPTIONAL_INT(jsonValue, var)          \
    do {                                                      \
        if (var) {                                            \
            (jsonValue)->Put(#var, static_cast<int64_t>(*(var))); \
        }                                                     \
    } while (0)                                               \

#define JSON_STRING_PUT_OPTIONAL_STRING(jsonValue, var) \
    do {                                                \
        if (var) {                                      \
            (jsonValue)->Put(#var, (var)->c_str());         \
        }                                               \
    } while (0)                                         \


#define JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, var) \
    do {                                                    \
        if (var) {                                          \
            (jsonValue)->Put(#var, (var)->ToString().c_str());  \
        }                                                   \
    } while (0)                                             \


namespace OHOS::Ace {
enum AceLogTag : uint8_t {
    ACE_DEFAULT_DOMAIN = 0,        // C03900
    ACE_ALPHABET_INDEXER = 1,      // C03901
    ACE_COUNTER = 2,               // C03902
    ACE_SUB_WINDOW = 3,            // C03903
    ACE_FORM = 4,                  // C03904
    ACE_DRAG = 5,                  // C03905
    ACE_VIDEO = 6,                 // C03906
    ACE_COMPONENT_SNAPSHOT = 7,    // C03907
    ACE_CANVAS = 8,                // C03908
    ACE_REFRESH = 9,               // C03909
    ACE_SCROLL = 10,               // C0390A
    ACE_SCROLLABLE = 11,           // C0390B
    ACE_FONT = 12,                 // C0390C
    ACE_OVERLAY = 13,              // C0390D
    ACE_DIALOG_TIMEPICKER = 14,    // C0390E
    ACE_DIALOG = 15,               // C0390F
    ACE_PANEL = 16,                // C03910
    ACE_MENU = 17,                 // C03911
    ACE_TEXTINPUT = 18,            // C03912
    ACE_TEXT = 19,                 // C03913
    ACE_TEXT_FIELD = 20,           // C03914
    ACE_SWIPER = 21,               // C03915
    ACE_TABS = 22,                 // C03916
    ACE_BLANK = 23,                // C03917
    ACE_GRIDROW = 24,              // C03918
    ACE_INPUTTRACKING = 25,        // C03919
    ACE_RICH_TEXT = 26,            // C0391A
    ACE_WEB = 27,                  // C0391B
    ACE_FOCUS = 28,                // C0391C
    ACE_MOUSE = 29,                // C0391D
    ACE_GESTURE = 30,              // C0391E
    ACE_IMAGE = 31,                // C0391F
    ACE_RATING = 32,               // C03920
    ACE_LIST = 33,                 // C03921
    ACE_NAVIGATION = 34,           // C03922
    ACE_WATERFLOW = 35,            // C03923
    ACE_ACCESSIBILITY = 36,        // C03924
    ACE_ROUTER = 37,               // C03925
    ACE_THEME = 38,                // C03926
    ACE_BORDER_IMAGE = 39,         // C03927
    ACE_GRID = 40,                 // C03928
    ACE_PLUGIN_COMPONENT = 41,     // C03929
    ACE_UIEXTENSIONCOMPONENT = 42, // C0392A
    ACE_IF = 43,                   // C0392B
    ACE_FOREACH = 44,              // C0392C
    ACE_LAZY_FOREACH = 45,         // C0392D
    ACE_GAUGE = 46,                // C0392E
    ACE_HYPERLINK = 47,            // C0392F
    ACE_ANIMATION = 48,            // C03930
    ACE_XCOMPONENT = 49,           // C03931
    ACE_AUTO_FILL = 50,            // C03932
    ACE_KEYBOARD = 51,             // C03933
    ACE_UIEVENT = 52,              // C03934
    ACE_UI_SERVICE = 53,           // C03935 ace_engine/adapter/ohos/services/uiservice/src/ui_service_hilog.h
    ACE_DISPLAY_SYNC = 54,         // C03936
    ACE_RESOURCE = 55,             // C03937
    ACE_SIDEBAR = 56,              // C03938
    ACE_GEOMETRY_TRANSITION = 57,  // C03939
    ACE_DOWNLOAD_MANAGER = 58,     // C0393A
    ACE_WINDOW_SCENE = 59,         // C0393B
    ACE_NODE_CONTAINER = 60,       // C0393C
    ACE_NATIVE_NODE = 61,          // C0393D
    ACE_ISOLATED_COMPONENT = 62,   // C0393E
    ACE_MARQUEE = 63,              // C0393F
    ACE_OBSERVER = 64,             // C03940
    ACE_EMBEDDED_COMPONENT = 65,   // C03941
    ACE_TEXT_CLOCK = 66,           // C03942
    ACE_FOLDER_STACK = 67,         // C03943
    ACE_SELECT_COMPONENT = 68,     // C03944
    ACE_STATE_STYLE = 69,          // C03945
    ACE_SEARCH = 70,               // C03946
    ACE_STATE_MGMT = 71,           // C03947
    ACE_REPEAT = 72,               // C03948
    ACE_SHEET = 73,                // C03949
    ACE_CANVAS_COMPONENT = 74,     // C0394A
    ACE_SCROLL_BAR = 75,           // C0394B
    ACE_MOVING_PHOTO = 76,         // C0394C
    ACE_ARK_COMPONENT = 77,        // C0394D
    ACE_WINDOW = 78,               // C0394E
    ACE_SECURITYUIEXTENSION = 79,  // C0394F
    ACE_WINDOW_PIPELINE = 80,      // C03950
    ACE_INPUTKEYFLOW = 81,         // C03951
    ACE_APPBAR = 82,               // C03952
    ACE_SELECT_OVERLAY = 83,       // C03953
    ACE_CLIPBOARD = 84,            // C03954
    ACE_VISUAL_EFFECT = 85,        // C03955
    ACE_SECURITY_COMPONENT = 86,   // C03956
    ACE_MEDIA_QUERY = 87,          // C03957
    ACE_LAYOUT_INSPECTOR = 88,     // C03958
    ACE_LAYOUT = 89,               // C03959
    ACE_STYLUS = 90,               // C0395A
    ACE_BADGE = 92,                // C0395C
    ACE_QRCODE = 93,               // C0395D
    ACE_PROGRESS = 94,             // C0395E

    FORM_RENDER = 255, // C039FF FormRenderer, last domain, do not add
};

ACE_FORCE_EXPORT extern const std::unordered_map<AceLogTag, const char*> g_DOMAIN_CONTENTS_MAP;

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

bool LogBacktrace(size_t maxFrameNums = 256);
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_LOG_WRAPPER_H
