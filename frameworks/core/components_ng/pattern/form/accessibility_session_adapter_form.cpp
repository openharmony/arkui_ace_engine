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

#include "core/components_ng/pattern/form/accessibility_session_adapter_form.h"

#include "core/components/form/resource/form_manager_delegate.h"

namespace OHOS::Ace::NG {
bool AccessibilitySessionAdapterForm::IgnoreHostNode() const
{
    return true;
}

void AccessibilitySessionAdapterForm::TransferHoverEvent(const PointF &point, SourceType source,
    AccessibilityHoverEventType eventType, TimeStamp time)
{
    auto formManagerDelegate = formManagerDelegate_.Upgrade();
    CHECK_NULL_VOID(formManagerDelegate);
    int64_t timeMs = std::chrono::time_point_cast<std::chrono::milliseconds>(time).time_since_epoch().count();
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "TransferHoverEvent point:%{public}s, sourceType:%{public}d, "
                                           "eventType:%{public}d, timeMs:%{public}" PRId64,
        point.ToString().c_str(), source, eventType, timeMs);
    formManagerDelegate->OnAccessibilityTransferHoverEvent(point.GetX(), point.GetY(),
        static_cast<int32_t>(source), static_cast<int32_t>(eventType), timeMs);
}
} // namespace OHOS::Ace::NG