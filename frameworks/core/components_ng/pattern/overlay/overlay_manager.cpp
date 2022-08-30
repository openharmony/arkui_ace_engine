/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/overlay/overlay_manager.h"

#include "core/components/common/properties/color.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

void OverlayManager::ShowToast(const RefPtr<UINode>& rootNode, int32_t toastId, const std::string& message,
    const std::string& bottom, bool isRightToLeft)
{
    if (!rootNode) {
        LOGE("the root node is nullptr");
        return;
    }
    LOGI("show toast in overlaymanager, id is %{public}d, message is %{public}s", toastId, message.c_str());
    // save root node to overlaymanager
    rootNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(rootNode));
    // make toast node
    auto toastNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, toastId, MakeRefPtr<TextPattern>());
    auto layoutProperty = toastNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    // update toast props
    layoutProperty->UpdateContent(message);
    auto target = toastNode->GetRenderContext();
    auto pipeline = toastNode->GetContext();
    auto themeManager = pipeline->GetThemeManager();
    Color toastColor = Color::BLUE;
    if (themeManager) {
        auto toastTheme = themeManager->GetTheme<ToastTheme>();
        if (toastTheme) {
            toastColor = toastTheme->GetBackgroundColor();
        }
    }
    if (target) {
        target->UpdateBackgroundColor(toastColor);
    }
    // save toast node in overlay manager
    ToastInfo info = { toastId, toastNode };
    toastStack_.emplace_back(info);
    // mount to parent
    toastNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void OverlayManager::PopToast(int32_t toastId)
{
    RefPtr<UINode> toastUnderPop;
    auto toastIter = toastStack_.end() - 1;
    for (; toastIter >= toastStack_.begin(); --toastIter) {
        if (toastIter->toastId == toastId) {
            toastUnderPop = toastIter->toastNode;
            break;
        }
    }
    if (!toastUnderPop) {
        LOGE("No toast under pop");
        return;
    }
    auto rootNode = rootNodeWeak_.Upgrade();
    if (!rootNode) {
        LOGE("No root node in OverlayManager");
        return;
    }
    LOGI("begin to pop toast, id is %{public}d", toastId);
    toastStack_.erase(toastIter);
    rootNode->RemoveChild(toastUnderPop);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

} // namespace OHOS::Ace::NG
