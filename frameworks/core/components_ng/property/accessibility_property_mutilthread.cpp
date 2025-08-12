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

#include "core/components_ng/property/accessibility_property.h"

#include "core/accessibility/accessibility_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void AccessibilityProperty::SetAccessibilityGroupMultiThread()
{
    // no need send event when node is free
}

void AccessibilityProperty::SetAccessibilityTextWithEventMultiThread()
{
    // no need send event when node is free
}

void AccessibilityProperty::SetAccessibilityDescriptionWithEventMultiThread()
{
    // no need send event when node is free
}

void AccessibilityProperty::SetAccessibilityLevelMultiThread(const std::string& backupLevel)
{
    // no need send event when node is free
}

void AccessibilityProperty::NotifyComponentChangeEventMultiThread(AccessibilityEventType eventType)
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = WeakPtr(frameNode)]() {
        if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto pipeline = frameNode->GetContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->AddAccessibilityCallbackEvent(AccessibilityCallbackEventId::ON_SEND_ELEMENT_INFO_CHANGE,
                                                    frameNode->GetAccessibilityId());
        }
    });
}
} // namespace OHOS::Ace::NG
