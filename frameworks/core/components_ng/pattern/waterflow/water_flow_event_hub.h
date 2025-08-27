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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_EVENT_HUB_H

#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"

namespace OHOS::Ace::NG {
using ScrollIndexFunc = std::function<void(int32_t, int32_t)>;

class WaterFlowEventHub : public ScrollableEventHub {
    DECLARE_ACE_TYPE(WaterFlowEventHub, ScrollableEventHub);

public:
    void SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex)
    {
        onScrollIndexEvent_ = std::move(onScrollIndex);
    }

    const ScrollIndexFunc& GetOnScrollIndex() const
    {
        return onScrollIndexEvent_;
    }

    void SetJSFrameNodeOnWaterFlowScrollIndex(ScrollIndexFunc&& onScroll)
    {
        onJSFrameNodeScrollIndexEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnWaterFlowScrollIndex()
    {
        if (onJSFrameNodeScrollIndexEvent_) {
            onJSFrameNodeScrollIndexEvent_ = nullptr;
        }
    }

    const ScrollIndexFunc& GetJSFrameNodeOnWaterFlowScrollIndex() const
    {
        return onJSFrameNodeScrollIndexEvent_;
    }

private:
    ScrollIndexFunc onScrollIndexEvent_;
    ScrollIndexFunc onJSFrameNodeScrollIndexEvent_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_EVENT_HUB_H