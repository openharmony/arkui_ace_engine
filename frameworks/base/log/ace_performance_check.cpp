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

#include "base/log/ace_performance_check.h"

#include <chrono>
#include <cstdint>
#include <ctime>
#include <map>
#include <string>

#include "base/i18n/localization.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t BASE_YEAR = 1900;
constexpr char DATE_FORMAT[] = "MM-dd HH:mm:ss";
static std::unordered_map<PerformanceParameterType, RuleNumber> typeMap = {
    { PerformanceParameterType::PAGE_NODES, RuleNumber::RULE_9901 },
    { PerformanceParameterType::PAGE_DEPTH, RuleNumber::RULE_9901 },
    { PerformanceParameterType::NODE_CHILDREN, RuleNumber::RULE_9901 },
    { PerformanceParameterType::FUNCTION_TIMEOUT, RuleNumber::RULE_9902 },
    { PerformanceParameterType::VSYNC_TIMEOUT, RuleNumber::RULE_9903 },
    { PerformanceParameterType::NODE_TIMEOUT, RuleNumber::RULE_9903 },
    { PerformanceParameterType::FOREACH_ITEMS, RuleNumber::RULE_9904 },
    { PerformanceParameterType::FLEX_LAYOUTS, RuleNumber::RULE_9905 },
};
} // namespace

std::unique_ptr<JsonValue> AcePerformanceCheck::performanceInfo_ = nullptr;

void AcePerformanceCheck::Start()
{
    if (SystemProperties::IsPerformanceCheckEnabled()) {
        performanceInfo_ = JsonUtil::Create(true);
    }
}

void AcePerformanceCheck::Stop()
{
    if (performanceInfo_) {
        auto info = performanceInfo_->ToString();
        // output info to json file
        performanceInfo_.reset(nullptr);
    }
}

AceScopedPerformanceCheck::AceScopedPerformanceCheck(PerformanceParameterType type) {}

AceScopedPerformanceCheck::~AceScopedPerformanceCheck() {}

void AceScopedPerformanceCheck::AddJsonToRuleScope(PerformanceParameterType type)
{
    if (AcePerformanceCheck::performanceInfo_) {
        auto ruleNumber = typeMap.find(type);
        switch (ruleNumber->second) {
            case RuleNumber::RULE_9901:
                AddJsonToRule9901();
                break;
            case RuleNumber::RULE_9902:
                AddJsonToRule9902();
                break;
            case RuleNumber::RULE_9903:
                AddJsonToRule9901();
                break;
            case RuleNumber::RULE_9904:
                AddJsonToRule9902();
                break;
            case RuleNumber::RULE_9905:
                AddJsonToRule9901();
                break;
            default:
                LOGE("There is no such performance check rule");
                break;
        }
    }
}

void AceScopedPerformanceCheck::AddJsonToRule9901() {}

void AceScopedPerformanceCheck::AddJsonToRule9902() {}

void AceScopedPerformanceCheck::AddJsonToRule9903() {}

void AceScopedPerformanceCheck::AddJsonToRule9904() {}

void AceScopedPerformanceCheck::AddJsonToRule9905() {}

std::string AceScopedPerformanceCheck::GetEventTime()
{
    // get system date and time
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto* local = std::localtime(&now);
    if (!local) {
        LOGE("Get localtime failed");
        return {};
    }

    // this is for i18n date time
    DateTime dateTime;
    dateTime.year = static_cast<uint32_t>(local->tm_year + BASE_YEAR);
    dateTime.month = static_cast<uint32_t>(local->tm_mon);
    dateTime.day = static_cast<uint32_t>(local->tm_mday);
    dateTime.hour = static_cast<uint32_t>(local->tm_hour);
    dateTime.minute = static_cast<uint32_t>(local->tm_min);
    dateTime.second = static_cast<uint32_t>(local->tm_sec);
    auto time = Localization::GetInstance()->FormatDateTime(dateTime, DATE_FORMAT);
    return time;
}

Framework::MappingInfo AceScopedPerformanceCheck::GetMappingInfo(int32_t row, int32_t col)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, {});
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, {});
    auto sourceMap = frontend->GetCurrentPageSourceMap();
    auto mappingInfo = sourceMap->Find(row, col);
    return mappingInfo;
}
} // namespace OHOS::Ace
