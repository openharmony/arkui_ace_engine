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

#include "base/log/ace_checker.h"

#ifdef HICHECKER_EXISTS
#include "caution.h"
#include "hichecker.h"
#include "parameter.h"
#include "parameters.h"
#endif

namespace OHOS::Ace {
namespace {
constexpr int32_t PAGE_NODES = 1000;
constexpr int32_t PAGE_DEPTH = 30;
constexpr int32_t NODE_CHILDREN = 100;
constexpr int32_t FUNCTION_TIMEOUT = 15;
constexpr int32_t VSYNC_TIMEOUT = 500;
constexpr int32_t NODE_TIMEOUT = 15;
constexpr int32_t FOREACH_ITEMS = 50;
constexpr int32_t FLEX_LAYOUTS = 8;
} // namespace

int32_t AceChecker::pageNodes_ = PAGE_NODES;
int32_t AceChecker::pageDepth_ = PAGE_DEPTH;
int32_t AceChecker::nodeChildren_ = NODE_CHILDREN;
int32_t AceChecker::functionTimeout_ = FUNCTION_TIMEOUT;
int32_t AceChecker::vsyncTimeout_ = VSYNC_TIMEOUT;
int32_t AceChecker::nodeTimeout_ = NODE_TIMEOUT;
int32_t AceChecker::foreachItems_ = FOREACH_ITEMS;
int32_t AceChecker::flexLayouts_ = FLEX_LAYOUTS;

#ifdef HICHECKER_EXISTS
bool AceChecker::IsPerformanceCheckEnabled()
{
    return HiviewDFX::HiChecker::Contains(HiviewDFX::Rule::RULE_CHECK_ARKUI_PERFORMANCE);
}

void AceChecker::NotifyCaution(const std::string& tag)
{
    HiviewDFX::Caution caution;
    caution.SetTriggerRule(HiviewDFX::Rule::RULE_CHECK_ARKUI_PERFORMANCE);
    HiviewDFX::HiChecker::NotifyCaution(HiviewDFX::Rule::RULE_CHECK_ARKUI_PERFORMANCE, tag, caution);
}

void AceChecker::InitPerformanceParameters()
{
    if (!IsPerformanceCheckEnabled()) {
        return;
    }
    AceChecker::pageNodes_ = system::GetIntParameter<int>("arkui.performancecheck.9901.pagenodes", PAGE_NODES);
    AceChecker::pageDepth_ = system::GetIntParameter<int>("arkui.performancecheck.9901.pagedepth", PAGE_DEPTH);
    AceChecker::nodeChildren_ = system::GetIntParameter<int>("arkui.performancecheck.9901.nodechildren", NODE_CHILDREN);
    AceChecker::functionTimeout_ =
        system::GetIntParameter<int>("arkui.performancecheck.9902.functiontimeout", FUNCTION_TIMEOUT);
    AceChecker::vsyncTimeout_ = system::GetIntParameter<int>("arkui.performancecheck.9903.vsynctimeout", VSYNC_TIMEOUT);
    AceChecker::nodeTimeout_ = system::GetIntParameter<int>("arkui.performancecheck.9903.nodetimeout", NODE_TIMEOUT);
    AceChecker::foreachItems_ = system::GetIntParameter<int>("arkui.performancecheck.9904.foreachitems", FOREACH_ITEMS);
    AceChecker::flexLayouts_ = system::GetIntParameter<int>("arkui.performancecheck.9905.flexlayouts", FLEX_LAYOUTS);
}
#else
bool AceChecker::IsPerformanceCheckEnabled()
{
    return false;
}

void AceChecker::NotifyCaution(const std::string& tag) {}
void AceChecker::InitPerformanceParameters() {}
#endif

} // namespace OHOS::Ace
