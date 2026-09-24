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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_INVOKE_SCOPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_INVOKE_SCOPE_H

#include <memory>
#include <vector>

namespace OHOS::Ace::NG {

template <typename MonitorState>
class SmartGestureMonitorInvokeScope final {
public:
    SmartGestureMonitorInvokeScope()
    {
        ++GetInvoking();
    }

    ~SmartGestureMonitorInvokeScope()
    {
        if (--GetInvoking() != 0) {
            return;
        }
        auto pending = std::move(GetPendingDetaches());
        GetPendingDetaches().clear();
        for (const auto& state : pending) {
            if (state) {
                state->Detach();
            }
        }
    }

    static void DetachOrDefer(std::shared_ptr<MonitorState> state)
    {
        if (!state) {
            return;
        }
        if (GetInvoking() != 0) {
            GetPendingDetaches().emplace_back(std::move(state));
            return;
        }
        state->Detach();
    }

private:
    static int& GetInvoking()
    {
        static int invoking = 0;
        return invoking;
    }

    static std::vector<std::shared_ptr<MonitorState>>& GetPendingDetaches()
    {
        static std::vector<std::shared_ptr<MonitorState>> pending;
        return pending;
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SMART_GESTURE_SMART_GESTURE_INVOKE_SCOPE_H
