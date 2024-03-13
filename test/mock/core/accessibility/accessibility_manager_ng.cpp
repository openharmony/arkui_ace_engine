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

#include "core/accessibility/accessibility_manager_ng.h"

namespace OHOS::Ace::NG {
void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const MouseEvent& event)
{
    return;
}

void AccessibilityManagerNG::HandleAccessibilityHoverEvent(const RefPtr<FrameNode>& root, const TouchEvent& event)
{
    return;
}

void AccessibilityManagerNG::HandleAccessibilityHoverEventInner(
    const RefPtr<FrameNode>& root,
    const PointF& point,
    SourceType sourceType,
    AccessibilityHoverEventType eventType,
    TimeStamp time)
{
    return;
}

void AccessibilityManagerNG::ResetHoverState()
{
    return;
}

void AccessibilityManagerNG::HoverTestDebug(const RefPtr<FrameNode>& root, const PointF& point,
    std::string& summary, std::string& detail) const
{
    return;
}
} // namespace OHOS::Ace::NG
