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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_PERFORMANCE_CHECK_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_PERFORMANCE_CHECK_H

#include <memory>
#include <string>

#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/system_properties.h"
#include "bridge/common/utils/source_map.h"

namespace OHOS::Ace {
enum class RuleNumber { RULE_9901 = 0, RULE_9902, RULE_9903, RULE_9904, RULE_9905 };

class ACE_EXPORT AcePerformanceCheck final {
public:
    static void Start();
    static void Stop();

private:
    AcePerformanceCheck() = default;
    ~AcePerformanceCheck() = default;

    static std::unique_ptr<JsonValue> performanceInfo_;

    friend class AceScopedPerformanceCheck;
    ACE_DISALLOW_COPY_AND_MOVE(AcePerformanceCheck);
};

class ACE_EXPORT AceScopedPerformanceCheck final {
public:
    explicit AceScopedPerformanceCheck(PerformanceParameterType type);
    ~AceScopedPerformanceCheck();

    static void AddJsonToRuleScope(PerformanceParameterType type);

private:
    static std::string GetEventTime();
    static Framework::MappingInfo GetMappingInfo(int32_t row, int32_t col);

    static void AddJsonToRule9901();
    static void AddJsonToRule9902();
    static void AddJsonToRule9903();
    static void AddJsonToRule9904();
    static void AddJsonToRule9905();

    ACE_DISALLOW_COPY_AND_MOVE(AceScopedPerformanceCheck);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_PERFORMANCE_CHECK_H
