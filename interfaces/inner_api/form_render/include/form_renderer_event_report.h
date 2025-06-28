/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_EVENT_REPORT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_EVENT_REPORT_H

#include <string>
#include <unordered_map>
#include <mutex>

#include "hisysevent.h"

using HiSysEventType = OHOS::HiviewDFX::HiSysEvent::EventType;
using HiSysEvent = OHOS::HiviewDFX::HiSysEvent;

namespace OHOS::Ace {

class FormRenderEventReport {
public:
    static void StartSurfaceNodeTimeoutReportTimer(int64_t formId, const std::string &bundleName,
        const std::string &formName);
    static void StopTimer(int64_t formId);

private:
    static std::unordered_map<int64_t, int32_t> waitSurfaceNodeTimerMap_;
    static std::mutex timerMutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_GROUP_EVENT_REPORT_H
