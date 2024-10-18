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

#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_session_adapter.h"

#include <cinttypes>
#include "base/log/log.h"
#include "core/accessibility/accessibility_constants.h"
#include "core/event/ace_events.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void XcomponentAccessibilitySessionAdapter::TransferHoverEvent(
    const PointF &point, SourceType source,
    AccessibilityHoverEventType eventType, TimeStamp time)
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->TransferThirdProviderHoverEvent(
        host_, point, source,  eventType, time);
}

bool XcomponentAccessibilitySessionAdapter::IgnoreHostNode() const
{
    return true;
}

} // namespace OHOS::Ace::NG
