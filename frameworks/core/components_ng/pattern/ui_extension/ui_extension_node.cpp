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

#include "core/components_ng/pattern/ui_extension/ui_extension_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
HitTestResult UIExtensionNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId)
{
    const auto& rect = GetGeometryNode()->GetFrameRect();
    if (!rect.IsInRegion(parentLocalPoint)) {
        return HitTestResult::OUT_OF_REGION;
    }
    auto context = GetContext();
    CHECK_NULL_RETURN(context, HitTestResult::BUBBLING);
    DispatchPointerEvent(touchRestrict.touchEvent);
    auto callback = [weak = WeakClaim(this)](const TouchEvent& point) {
        auto uiExtensionNode = weak.Upgrade();
        CHECK_NULL_VOID(uiExtensionNode);
        uiExtensionNode->DispatchPointerEvent(point);
    };
    context->AddUIExtensionCallback(callback);
    return HitTestResult::BUBBLING;
}

void UIExtensionNode::DispatchPointerEvent(const TouchEvent& point) const
{
    auto selfGlobalOffset = GetTransformRelativeOffset();
    auto pointerEvent = Platform::ConvertPointerEvent(selfGlobalOffset, point);
    GetPattern<UIExtensionPattern>()->DispatchPointerEvent(pointerEvent);
}

RefPtr<UIExtensionNode> UIExtensionNode::GetOrCreateUIExtensionNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto uiExtensionNode = ElementRegister::GetInstance()->GetSpecificItemById<UIExtensionNode>(nodeId);
    if (uiExtensionNode) {
        if (uiExtensionNode->GetTag() == tag) {
            return uiExtensionNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = uiExtensionNode->GetParent();
        if (parent) {
            parent->RemoveChild(uiExtensionNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    uiExtensionNode = AceType::MakeRefPtr<UIExtensionNode>(tag, nodeId, pattern, false);
    uiExtensionNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(uiExtensionNode);
    return uiExtensionNode;
}
} // namespace OHOS::Ace::NG
