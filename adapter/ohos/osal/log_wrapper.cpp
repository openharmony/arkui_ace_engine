/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <cstring>

#include "hilog/log.h"

extern "C" {
int HiLogPrintArgs(LogType type, LogLevel level, unsigned int domain, const char* tag, const char* fmt, va_list ap);
}

namespace OHOS::Ace {

namespace {

const ::LogLevel LOG_LEVELS[] = {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
};

const char* LOG_TAGS[] = {
    "Ace",
    "JSApp",
};

constexpr uint32_t LOG_DOMAINS[] = {
    0xD003900,
    0xD003B00,
};

}

// initial static member object
LogLevel LogWrapper::level_ = LogLevel::DEBUG;

char LogWrapper::GetSeparatorCharacter()
{
    return '/';
}

void LogWrapper::PrintLog(LogDomain domain, LogLevel level, const char* fmt, va_list args)
{
    HiLogPrintArgs(LOG_CORE, LOG_LEVELS[static_cast<uint32_t>(level)], LOG_DOMAINS[static_cast<uint32_t>(domain)],
        LOG_TAGS[static_cast<uint32_t>(domain)], fmt, args);
}

} // namespace OHOS::Ace
