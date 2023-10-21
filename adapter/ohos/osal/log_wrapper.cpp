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
#include <map>
#include <unordered_map>

#include "hilog/log.h"

#ifdef ACE_INSTANCE_LOG
#include "core/common/container.h"
#endif

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

const std::map<AceLogTag, const char*> DOMAIN_CONTENTS_MAP = {
    { AceLogTag::DEFAULT, "Ace" },
    { AceLogTag::ACE_SUB_WINDOW, "AceSubWindow" },
    { AceLogTag::ACE_FORM, "AceForm" },
    { AceLogTag::ACE_DRAG, "AceDrag" },
    { AceLogTag::ACE_VIDEO, "AceVideo" },
    { AceLogTag::ACE_FONT, "AceFont" },
    { AceLogTag::ACE_TEXTINPUT, "AceTextInput" },
    { AceLogTag::ACE_SWIPER, "AceSwiper" },
    { AceLogTag::ACE_TABS, "AceTabs" },
    { AceLogTag::ACE_DIVIDER, "AceDivider" },
    { AceLogTag::ACE_BLANK, "AceBlank" },
};

const char* APP_DOMAIN_CONTENT = "JSApp";

constexpr uint32_t LOG_DOMAINS[] = {
    0xD003900,
    0xC0D0,
};

constexpr LogType LOG_TYPES[] = {
    LOG_CORE,
    LOG_APP,
};

}

// initial static member object
LogLevel LogWrapper::level_ = LogLevel::DEBUG;

char LogWrapper::GetSeparatorCharacter()
{
    return '/';
}

void LogWrapper::PrintLog(LogDomain domain, LogLevel level, AceLogTag tag, const char* fmt, va_list args)
{
    uint32_t hilogDomain = LOG_DOMAINS[static_cast<uint32_t>(domain)] + static_cast<uint32_t>(tag);
    const char* domainContent = domain == LogDomain::FRAMEWORK ? DOMAIN_CONTENTS_MAP.at(tag) : APP_DOMAIN_CONTENT;
#ifdef ACE_PRIVATE_LOG
    std::string newFmt(fmt);
    ReplaceFormatString("{private}", "{public}", newFmt);
    HiLogPrintArgs(LOG_TYPES[static_cast<uint32_t>(domain)], LOG_LEVELS[static_cast<uint32_t>(level)],
        hilogDomain, domainContent, newFmt.c_str(), args);
#else
    HiLogPrintArgs(LOG_TYPES[static_cast<uint32_t>(domain)], LOG_LEVELS[static_cast<uint32_t>(level)],
        hilogDomain, domainContent, fmt, args);
#endif
}

int32_t LogWrapper::GetId()
{
#ifdef ACE_INSTANCE_LOG
    return Container::CurrentId();
#else
    return 0;
#endif
}

} // namespace OHOS::Ace
