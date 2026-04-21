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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_EVENT_TRACKER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_EVENT_TRACKER_H

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>

#include "base/thread/task_executor.h"
#include "interfaces/inner_api/ace/ui_content_config.h"

namespace OHOS::Ace {
class UIEventTracker final {
public:
    UIEventTracker(int32_t instanceId, WeakPtr<TaskExecutor> taskExecutor);
    ~UIEventTracker();

    UIEventTracker(const UIEventTracker&) = delete;
    UIEventTracker& operator=(const UIEventTracker&) = delete;

    bool IsLoggable() const;
    void ReportNavigateChange(const NavigateChangeInfo& from, const NavigateChangeInfo& to);
    void ReportEvent(const std::string& event);

    static void NotifyLogStatusChanged(bool status);

private:
    void HandleUIEventTrackerStatusChanged(bool enabled);
    void TryRegisterNavigateChangeTrackerCallback();
    void TryUnregisterNavigateChangeTrackerCallback();
    void OnLogStatusChanged(bool status);

    int32_t instanceId_ { -1 };
    WeakPtr<TaskExecutor> taskExecutor_;
    std::atomic<bool> loggable_ { false };
    int32_t navigateChangeCallbackId_ { -1 };
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_UI_EVENT_TRACKER_H
