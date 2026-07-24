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

#include "adapter/ohos/entrance/ui_event_tracker.h"

#include <mutex>
#include <string>

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/log_wrapper.h"
#include "base/utils/time_util.h"
#include "core/common/ace_engine.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "page_switch_log.h"

namespace OHOS::Ace {
namespace {
std::once_flag g_registerStatusCallbackOnceFlag;
std::atomic<int32_t> g_uiEventTrackerCount(0);
constexpr int32_t INVALID_CALLBACK_ID = -1;

std::shared_ptr<UIEventTracker> GetUIEventTrackerByInstanceId(int32_t instanceId)
{
    auto container = Platform::AceContainer::GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetUIEventTracker();
}

extern "C" void OnPageSwitchLogStatusChangedForArkUI(bool status)
{
    UIEventTracker::NotifyLogStatusChanged(status);
}
} // namespace

UIEventTracker::UIEventTracker(int32_t instanceId, WeakPtr<TaskExecutor> taskExecutor)
    : instanceId_(instanceId), taskExecutor_(std::move(taskExecutor))
{
    g_uiEventTrackerCount.fetch_add(1);
    std::call_once(g_registerStatusCallbackOnceFlag, []() {
        if (!RegisterPageSwitchLogStatusCallback(OnPageSwitchLogStatusChangedForArkUI)) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "Failed to register page switch log status callback.");
        }
    });
    OnLogStatusChanged(IsLoggable());
}

UIEventTracker::~UIEventTracker()
{
    TryUnregisterNavigateChangeTrackerCallback();
    if (g_uiEventTrackerCount.fetch_sub(1) == 1) {
        UnregisterPageSwitchLogStatusCallback(OnPageSwitchLogStatusChangedForArkUI);
    }
}

bool UIEventTracker::IsLoggable() const
{
    return OHOS::HiviewDFX::IsPageSwitchLoggable();
}

void UIEventTracker::HandleUIEventTrackerStatusChanged(bool enabled)
{
    if (enabled) {
        TryRegisterNavigateChangeTrackerCallback();
    } else {
        TryUnregisterNavigateChangeTrackerCallback();
    }
}

void UIEventTracker::TryRegisterNavigateChangeTrackerCallback()
{
    if (navigateChangeCallbackId_ != INVALID_CALLBACK_ID) {
        return;
    }

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        return;
    }
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipeline) {
        return;
    }
    auto navigationManager = pipeline->GetNavigationManager();
    if (!navigationManager) {
        return;
    }
    auto callbackId = navigationManager->RegisterNavigateChangeCallback(
        [instanceId = instanceId_](const NavigateChangeInfo& from, const NavigateChangeInfo& to,
            [[maybe_unused]] bool isRouter) {
            auto tracker = GetUIEventTrackerByInstanceId(instanceId);
            CHECK_NULL_VOID(tracker);
            tracker->ReportNavigateChange(from, to);
        });
    if (callbackId < 0) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "Failed to register navigate change callback for DFX tracker.");
        return;
    }
    navigateChangeCallbackId_ = callbackId;
    if (!IsLoggable()) {
        TryUnregisterNavigateChangeTrackerCallback();
    }
}

void UIEventTracker::TryUnregisterNavigateChangeTrackerCallback()
{
    auto callbackId = navigateChangeCallbackId_;
    if (callbackId < 0) {
        return;
    }
    navigateChangeCallbackId_ = INVALID_CALLBACK_ID;

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        return;
    }
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipeline) {
        return;
    }
    auto navigationManager = pipeline->GetNavigationManager();
    if (!navigationManager) {
        return;
    }
    navigationManager->UnregisterNavigateChangeCallback(callbackId);
}

void UIEventTracker::ReportNavigateChange(const NavigateChangeInfo& from, const NavigateChangeInfo& to)
{
    if (!loggable_.load()) {
        return;
    }
    std::string event = "Navigate change at ";
    event += std::to_string(GetCurrentTimestamp());
    event += ": from page '";
    event += from.name;
    event += "' (split: ";
    event += from.isSplit ? "true" : "false";
    event += ") to page '";
    event += to.name;
    event += "' (split: ";
    event += to.isSplit ? "true" : "false";
    event += ").";
    ReportEvent(event);
}

void UIEventTracker::ReportEvent(const std::string& event)
{
    if (!loggable_.load() || event.empty()) {
        return;
    }
    (void)OHOS::HiviewDFX::WritePageSwitchStr(event);
}

void UIEventTracker::NotifyLogStatusChanged(bool status)
{
    AceEngine::Get().NotifyContainers([status](const RefPtr<Container>& container) {
        auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
        if (!aceContainer) {
            return;
        }
        auto tracker = aceContainer->GetUIEventTracker();
        if (!tracker) {
            return;
        }
        tracker->OnLogStatusChanged(status);
    });
}

void UIEventTracker::OnLogStatusChanged(bool status)
{
    loggable_.store(status);
    auto taskExecutor = taskExecutor_.Upgrade();
    if (!taskExecutor) {
        return;
    }
    auto handleTask = [instanceId = instanceId_, status]() {
        auto tracker = GetUIEventTrackerByInstanceId(instanceId);
        CHECK_NULL_VOID(tracker);
        tracker->HandleUIEventTrackerStatusChanged(status);
    };
    taskExecutor->PostTask(handleTask, TaskExecutor::TaskType::UI, "ArkUIPageSwitchLogStatusChanged");
}
} // namespace OHOS::Ace
