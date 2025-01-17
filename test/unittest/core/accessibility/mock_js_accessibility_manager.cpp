/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/js_accessibility_manager.h"

#include "accessibility_constants.h"
#include "accessibility_event_info.h"
#include "accessibility_system_ability_client.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/core/accessibility/accessibility_manager_ng.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Accessibility;
using namespace OHOS::AccessibilityConfig;
using namespace std;

namespace OHOS::Ace::NG {

bool UIExtensionManager::IsShowPlaceholder(int32_t nodeId)
{
    return false;
}
bool UIExtensionManager::IsWrapExtensionAbilityId(int64_t elementId)
{
    return false;
}
std::pair<int64_t, int64_t> UIExtensionManager::UnWrapExtensionAbilityId(
    int64_t extensionOffset,
    int64_t elementId)
{
    if (extensionOffset == 0) {
        return std::pair<int64_t, int64_t>(0, 0);
    }
    int64_t index = elementId / extensionOffset;
    int64_t abilityId = elementId % extensionOffset;
    return std::pair<int64_t, int64_t>(index, abilityId);
}

void UIExtensionManager::TransferAccessibilityRectInfo()
{
}

void UIExtensionManager::RegisterBusinessDataConsumeCallback(
    UIContentBusinessCode code, UIExtBusinessDataConsumeCallback callback)
{
}

const RefPtr<FrameNode> UIExtensionManager::GetFocusUiExtensionNode()
{
    return nullptr;
}

bool UIExtensionManager::SendBusinessToHostSyncReply(
    UIContentBusinessCode code, AAFwk::Want&& data, AAFwk::Want& reply)
{
    return true;
}

RefPtr<AccessibilityManagerNG> PipelineContext::GetAccessibilityManagerNG()
{
    return nullptr;
}

} // OHOS::Ace::NG


namespace OHOS::Ace {
bool SystemProperties::accessTraceEnable_ = false;

bool PipelineContext::AccessibilityRequestFocus(const ComposeId& id)
{
    return false;
}
void PipelineContext::SendEventToFrontend(const EventMarker& eventMarker)
{
}

const Rect& RenderNode::GetPaintRect() const
{
    Rect mock (0, 0, 0, 0);
    return mock;
}
} // OHOS::Ace
