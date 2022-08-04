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

#include <unistd.h>

#include "core/common/ace_application_info.h"
#include "base/ressched/ressched_report.h"

namespace OHOS::Ace {
namespace {
    const uint32_t RES_TYPE_CLICK_RECOGNIZE = 9;
    const uint32_t RES_TYPE_PUSH_PAGE       = 10;
    const uint32_t RES_TYPE_SLIDE           = 11;
    const int32_t TOUCH_EVENT               = 1;
    const int32_t CLICK_EVENT               = 2;
}

ResSchedReport& ResSchedReport::GetInstance()
{
    static ResSchedReport instance;
    return instance;
}

void ResSchedReport::ResSchedDataReport(const char* name)
{
    std::unordered_map<std::string, std::string> payload;
    payload["name"] = name;
    if (reportDataFunc_ == nullptr) {
        reportDataFunc_ = LoadReportDataFunc();
    }
    if (reportDataFunc_ != nullptr) {
        if (strcmp(name, "click") == 0) {
            reportDataFunc_(RES_TYPE_CLICK_RECOGNIZE, CLICK_EVENT, payload);
        } else if (strcmp(name, "slide_on") == 0) {
            reportDataFunc_(RES_TYPE_SLIDE, 1, payload);
        } else if (strcmp(name, "slide_off") == 0) {
            reportDataFunc_(RES_TYPE_SLIDE, 0, payload);
        }
    }
}

void ResSchedReport::ResSchedDataReport(const char* name, const std::unordered_map<std::string, std::string>& param)
{
    std::unordered_map<std::string, std::string> payload = param;
    payload["name"] = name;
    if (reportDataFunc_ == nullptr) {
        reportDataFunc_ = LoadReportDataFunc();
    }
    if (reportDataFunc_ != nullptr) {
        if (strcmp(name, "push_page_start") == 0) {
            LoadAceApplicationContext(payload);
            reportDataFunc_(RES_TYPE_PUSH_PAGE, 0, payload);
        } else if (strcmp(name, "push_page_complete") == 0) {
            LoadAceApplicationContext(payload);
            reportDataFunc_(RES_TYPE_PUSH_PAGE, 1, payload);
        }
    }
}

void ResSchedReport::MarkNeedUpdate()
{
    std::unordered_map<std::string, std::string> payload;
    payload["name"] = "touch_event";
    if (reportDataFunc_ == nullptr) {
        reportDataFunc_ = LoadReportDataFunc();
    }
    if (reportDataFunc_ != nullptr && isInTouchDownUp_) {
        reportDataFunc_(RES_TYPE_CLICK_RECOGNIZE, TOUCH_EVENT, payload);
        isInTouchDownUp_ = false;
    }
}

void ResSchedReport::DispatchTouchEventStart(const TouchType& touchType)
{
    if (touchType == TouchType::DOWN || touchType == TouchType::UP) {
        isInTouchDownUp_ = true;
    } else {
        isInTouchDownUp_ = false;
    }
}

void ResSchedReport::DispatchTouchEventEnd()
{
    isInTouchDownUp_ = false;
}

void ResSchedReport::LoadAceApplicationContext(std::unordered_map<std::string, std::string>& payload)
{
    pid_t pid = getpid();
    payload["pid"] = std::to_string(pid);
    payload["bundleName"] = AceApplicationInfo::GetInstance().GetPackageName();
    payload["uid"] = std::to_string(AceApplicationInfo::GetInstance().GetUid());
}
} // namespace OHOS::Ace
