/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/accessibility_session_adapter_isolated_component.h"

#include <cinttypes>

namespace OHOS::Ace::NG {
void AccessibilitySessionAdapterIsolatedComponent::TransferHoverEvent(const PointF &point, SourceType source,
    AccessibilityHoverEventType eventType, TimeStamp time)
{
    auto dynamicComponentRenderer = dynamicComponentRenderer_.Upgrade();
    CHECK_NULL_VOID(dynamicComponentRenderer);
    int64_t timeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch().count();
    TAG_LOGI(AceLogTag::ACE_ISOLATED_COMPONENT, "TransferHoverEvent point:%{public}s, sourceType:%{public}d, "
        "eventType:%{public}d, timeMs:%{public}" PRId64,
        point.ToString().c_str(), source, eventType, timeMs);
    dynamicComponentRenderer->TransferAccessibilityHoverEvent(point.GetX(), point.GetY(),
        static_cast<int32_t>(source), static_cast<int32_t>(eventType), timeMs);
}

bool AccessibilitySessionAdapterIsolatedComponent::IgnoreHostNode() const
{
    return true;
}
} // namespace OHOS::Ace::NG
