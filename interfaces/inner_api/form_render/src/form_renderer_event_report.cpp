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

#include "form_renderer_event_report.h"

#include <cinttypes>
#include <string>
#include <map>

#include "hisysevent.h"
#include "xcollie/xcollie.h"
#include "xcollie/xcollie_define.h"
#include "form_renderer_hilog.h"

namespace OHOS::Ace {
namespace {
    constexpr const char *FORM_NODE_ERROR = "FORM_NODE_ERROR";
    constexpr const char *EVENT_KEY_FORM_ID = "FORM_ID";
    constexpr const char *EVENT_KEY_BUNDLE_NAME = "BUNDLE_NAME";
    constexpr const char *EVENT_KEY_FORM_NAME = "FORM_NAME";
    constexpr const char *EVENT_KEY_ERROR_NAME = "ERROR_NAME";
    constexpr const char *EVENT_KEY_ERROR_TYPE = "ERROR_TYPE";
    constexpr const char *EVENT_KEY_ERROR_CODE = "ERROR_CODE";
    constexpr int32_t SURFACE_NODE_CREATE_FAILED = 2;
    constexpr uint32_t SURFACE_NODE_CREATE_TIMEOUT = 10;
}

std::unordered_map<int64_t, int32_t> FormRenderEventReport::waitSurfaceNodeTimerMap_ = {};
std::mutex FormRenderEventReport::timerMutex_;

void FormRenderEventReport::StartSurfaceNodeTimeoutReportTimer(int64_t formId, const std::string &bundleName,
    const std::string &formName)
{
    auto timeoutCallback = [formId, bundleName, formName](void *) {
        HILOG_INFO("wait surface node create timeout, formId: %{public}" PRId64, formId);
        HiSysEventWrite(
            OHOS::HiviewDFX::HiSysEvent::Domain::FORM_MANAGER,
            "FORM_ERROR",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            EVENT_KEY_FORM_ID, formId,
            EVENT_KEY_BUNDLE_NAME, bundleName,
            EVENT_KEY_FORM_NAME, formName,
            EVENT_KEY_ERROR_NAME, FORM_NODE_ERROR,
            EVENT_KEY_ERROR_TYPE, SURFACE_NODE_CREATE_FAILED,
            EVENT_KEY_ERROR_CODE, 0);
    };
    FormRenderEventReport::StopTimer(formId);
    std::string taskName = "FRS_WaitSurfaceNodeCreate_" + std::to_string(formId);
    int32_t timerId = OHOS::HiviewDFX::XCollie::GetInstance().SetTimer(
        taskName, SURFACE_NODE_CREATE_TIMEOUT, timeoutCallback, nullptr, HiviewDFX::XCOLLIE_FLAG_NOOP);
    HILOG_INFO("wait surface node create start, formId: %{public}" PRId64 "timerId: %{public}d", formId, timerId);
    std::lock_guard<std::mutex> lock(FormRenderEventReport::timerMutex_);
    FormRenderEventReport::waitSurfaceNodeTimerMap_.emplace(formId, timerId);
}

void FormRenderEventReport::StopTimer(int64_t formId)
{
    std::lock_guard<std::mutex> lock(FormRenderEventReport::timerMutex_);
    auto iter = FormRenderEventReport::waitSurfaceNodeTimerMap_.find(formId);
    if (iter != FormRenderEventReport::waitSurfaceNodeTimerMap_.end()) {
        int32_t timerId = iter->second;
        HILOG_INFO("surface node create completed, formId:%{public}" PRId64 "timerId: %{public}d", formId, timerId);
        OHOS::HiviewDFX::XCollie::GetInstance().CancelTimer(timerId);
        FormRenderEventReport::waitSurfaceNodeTimerMap_.erase(iter);
    }
}
} // namespace OHOS::Ace
