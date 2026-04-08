/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/log/log_wrapper.h"

#include <cstdarg>
#include <cstring>

#include "base/utils/system_properties.h"

namespace OHOS::Ace {

bool LogWrapper::JudgeLevel(LogLevel level)
{
    if (level == LogLevel::DEBUG) {
        return SystemProperties::GetDebugEnabled();
    }
    return level_ <= level;
}

void LogWrapper::SetLogLevel(LogLevel level)
{
    level_ = level;
}

LogLevel LogWrapper::GetLogLevel()
{
    return level_;
}

const char* LogWrapper::GetBriefFileName(const char* name)
{
    static const char separator = GetSeparatorCharacter();
    const char* p = strrchr(name, separator);
    return p != nullptr ? p + 1 : name;
}

void LogWrapper::StripFormatString(const std::string& prefix, std::string& str)
{
    for (auto pos = str.find(prefix, 0); pos != std::string::npos; pos = str.find(prefix, pos)) {
        str.erase(pos, prefix.size());
    }
}

void LogWrapper::ReplaceFormatString(const std::string& prefix, const std::string& replace, std::string& str)
{
    for (auto pos = str.find(prefix, 0); pos != std::string::npos; pos = str.find(prefix, pos)) {
        str.replace(pos, prefix.size(), replace);
    }
}

#if !defined(USE_HILOG)
void LogWrapper::PrintLog(LogDomain domain, LogLevel level, AceLogTag tag, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    PrintLog(domain, level, tag, fmt, args);
    va_end(args);
}
#endif

} // namespace OHOS::Ace
