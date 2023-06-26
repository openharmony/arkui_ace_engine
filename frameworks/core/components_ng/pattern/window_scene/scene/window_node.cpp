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

#include "core/components_ng/pattern/window_scene/scene/window_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
HitTestResult WindowNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId)
{
    auto rectWithTransform = GetPaintRectWithTransform();
    if (!rectWithTransform.IsInRegion(parentLocalPoint)) {
        return HitTestResult::OUT_OF_REGION;
    }
    auto context = PipelineContext::GetCurrentContext();
    auto pointerEvent = touchRestrict.touchEvent.pointerEvent;
    if (pointerEvent == nullptr) {
        return HitTestResult::OUT_OF_REGION;
    }
    auto selfGlobalOffset = GetTransformRelativeOffset();
    Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, GetTransformScale());
    auto pattern = GetPattern<WindowPattern>();
    pattern->DispatchPointerEvent(pointerEvent);
    auto callback = [weak = WeakClaim(this)](const std::shared_ptr<MMI::PointerEvent>& pointerEvent) {
        auto windowNode = weak.Upgrade();
        CHECK_NULL_VOID(windowNode);
        auto selfGlobalOffset = windowNode->GetTransformRelativeOffset();
        Platform::CalculatePointerEvent(selfGlobalOffset, pointerEvent, windowNode->GetTransformScale());
        auto pattern = windowNode->GetPattern<WindowPattern>();
        pattern->DispatchPointerEvent(pointerEvent);
    };
    context->AddWindowSceneTouchEventCallback(touchRestrict.touchEvent.id, callback);
    return HitTestResult::BUBBLING;
}

RefPtr<WindowNode> WindowNode::GetOrCreateWindowNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto windowNode = ElementRegister::GetInstance()->GetSpecificItemById<WindowNode>(nodeId);
    if (windowNode) {
        if (windowNode->GetTag() == tag) {
            return windowNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = windowNode->GetParent();
        if (parent) {
            parent->RemoveChild(windowNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    windowNode = AceType::MakeRefPtr<WindowNode>(tag, nodeId, pattern, false);
    windowNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(windowNode);
    return windowNode;
}
} // namespace OHOS::Ace::NG
