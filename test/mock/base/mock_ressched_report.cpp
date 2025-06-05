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

#include "base/ressched/ressched_report.h"

namespace OHOS::Ace {
ResSchedReport& ResSchedReport::GetInstance()
{
    static ResSchedReport instance;
    return instance;
}

namespace {
    constexpr char ABILITY_OR_PAGE_SWITCH_START[] = "ability_or_page_switch_start";
    constexpr char ABILITY_OR_PAGE_SWITCH_END[] = "ability_or_page_switch_end";
    constexpr uint64_t RES_TYPE_ABILITY_OR_PAGE_SWITCH = 156;
}

ResSchedReport::ResSchedReport()
{}

void ResSchedReport::ResSchedDataReport(
    const char* name , const std::unordered_map<std::string, std::string>& param)
{
    reportDataFunc_ = nullptr;
    if (std::strcmp(ABILITY_OR_PAGE_SWITCH_START, name) == 0 || std::strcmp(ABILITY_OR_PAGE_SWITCH_END, name) == 0) {
        keyEventCountMS = RES_TYPE_ABILITY_OR_PAGE_SWITCH;
    }
}

void ResSchedReport::ResSchedDataReport(
    uint32_t resType, int32_t value, const std::unordered_map<std::string, std::string>& payload)
{}

void ResSchedReport::OnTouchEvent(const TouchEvent& touchEvent, const ReportConfig& config) {}

void ResSchedReport::HandlePageTransition(const std::string& fromPage,
    const std::string& toPage, const std::string& mode)
{}

ResSchedReportScope::ResSchedReportScope(
    const std::string& name, const std::unordered_map<std::string, std::string>& param)
    : name_(name), payload_(param)
{}

ResSchedReportScope::~ResSchedReportScope() = default;
} // namespace OHOS::Ace
