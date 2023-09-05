/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/form/form_node.h"

#include "base/utils/utils.h"
#include "core/components/form/sub_container.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "pointer_event.h"

namespace OHOS::Ace::NG {
namespace {
const std::unordered_map<SourceType, int32_t> SOURCE_TYPE_MAP = {
    { SourceType::TOUCH, MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN },
    { SourceType::TOUCH_PAD, MMI::PointerEvent::SOURCE_TYPE_TOUCHPAD },
    { SourceType::MOUSE, MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN },
};

const std::unordered_map<TouchType, int32_t> TOUCH_TYPE_MAP = {
    { TouchType::CANCEL, MMI::PointerEvent::POINTER_ACTION_CANCEL },
    { TouchType::DOWN, MMI::PointerEvent::POINTER_ACTION_DOWN },
    { TouchType::MOVE, MMI::PointerEvent::POINTER_ACTION_MOVE },
    { TouchType::UP, MMI::PointerEvent::POINTER_ACTION_UP },
    { TouchType::PULL_DOWN, MMI::PointerEvent::POINTER_ACTION_PULL_DOWN },
    { TouchType::PULL_MOVE, MMI::PointerEvent::POINTER_ACTION_PULL_MOVE },
    { TouchType::PULL_UP, MMI::PointerEvent::POINTER_ACTION_PULL_UP },
    { TouchType::PULL_IN_WINDOW, MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW },
    { TouchType::PULL_OUT_WINDOW, MMI::PointerEvent::POINTER_ACTION_PULL_OUT_WINDOW },
};

std::shared_ptr<MMI::PointerEvent> ConvertPointerEvent(const OffsetF offsetF, const TouchEvent& point)
{
    std::shared_ptr<MMI::PointerEvent> pointerEvent = MMI::PointerEvent::Create();

    OHOS::MMI::PointerEvent::PointerItem item;
    item.SetWindowX(static_cast<int32_t>(point.x - offsetF.GetX()));
    item.SetWindowY(static_cast<int32_t>(point.y - offsetF.GetY()));
    item.SetDisplayX(static_cast<int32_t>(point.screenX));
    item.SetDisplayY(static_cast<int32_t>(point.screenY));
    item.SetPointerId(point.id);
    pointerEvent->AddPointerItem(item);

    int32_t sourceType = MMI::PointerEvent::SOURCE_TYPE_UNKNOWN;
    auto sourceTypeIter = SOURCE_TYPE_MAP.find(point.sourceType);
    if (sourceTypeIter != SOURCE_TYPE_MAP.end()) {
        sourceType = sourceTypeIter->second;
    }
    pointerEvent->SetSourceType(sourceType);

    int32_t pointerAction = OHOS::MMI::PointerEvent::POINTER_ACTION_UNKNOWN;
    auto pointerActionIter = TOUCH_TYPE_MAP.find(point.type);
    if (pointerActionIter != TOUCH_TYPE_MAP.end()) {
        pointerAction = pointerActionIter->second;
    }
    pointerEvent->SetPointerAction(pointerAction);
    pointerEvent->SetPointerId(point.id);
    return pointerEvent;
}
}

HitTestResult FormNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, const TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId)
{
    // The mousetest has been merged into touchtest.
    // FormComponent does not support some mouse event(eg. Hover, HoverAnimation..).
    // Mouse event like LEFT_BUTTON, RELEASE use touchevent to dispatch, so they work well on FormComponent
    if (touchRestrict.hitTestType == SourceType::MOUSE) {
        return HitTestResult::OUT_OF_REGION;
    }

    auto testResult = FrameNode::TouchTest(globalPoint, parentLocalPoint, parentRevertPoint,
        touchRestrict, result, touchId);
    if (testResult == HitTestResult::OUT_OF_REGION) {
        return HitTestResult::OUT_OF_REGION;
    }

    auto context = GetContext();
    CHECK_NULL_RETURN(context, testResult);

    auto selfGlobalOffset = GetTransformRelativeOffset();
    auto pattern = GetPattern<FormPattern>();
    CHECK_NULL_RETURN(pattern, testResult);
    auto subContainer = pattern->GetSubContainer();
    CHECK_NULL_RETURN(subContainer, testResult);

    // Send TouchEvent Info to FormRenderService when Provider is ArkTS Card.
    if (subContainer->GetUISyntaxType() == FrontendType::ETS_CARD) {
        DispatchPointerEvent(touchRestrict.touchEvent);
        auto callback = [weak = WeakClaim(this)](const TouchEvent& touchEvent) {
            auto formNode = weak.Upgrade();
            CHECK_NULL_VOID(formNode);
            formNode->DispatchPointerEvent(touchEvent);
        };
        context->AddEtsCardTouchEventCallback(touchRestrict.touchEvent.id, callback);
        return testResult;
    }
    auto subContext = DynamicCast<OHOS::Ace::PipelineBase>(subContainer->GetPipelineContext());
    CHECK_NULL_RETURN(subContext, testResult);
    subContext->SetPluginEventOffset(Offset(selfGlobalOffset.GetX(), selfGlobalOffset.GetY()));
    context->SetTouchPipeline(WeakPtr<PipelineBase>(subContext));

    return testResult;
}

void FormNode::DispatchPointerEvent(const TouchEvent& touchEvent) const
{
    auto pattern = GetPattern<FormPattern>();
    CHECK_NULL_VOID(pattern);
    auto selfGlobalOffset = GetFormOffset();
    auto pointerEvent = ConvertPointerEvent(selfGlobalOffset, touchEvent);
    pattern->DispatchPointerEvent(pointerEvent);
}

OffsetF FormNode::GetFormOffset() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto offset = context->GetPaintRectWithoutTransform().GetOffset();
    auto parent = GetAncestorNodeOfFrame();

    while (parent) {
        auto parentRenderContext = parent->GetRenderContext();
        offset += parentRenderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }

    return offset;
}

RefPtr<FormNode> FormNode::GetOrCreateFormNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto formNode = ElementRegister::GetInstance()->GetSpecificItemById<FormNode>(nodeId);
    if (formNode) {
        if (formNode->GetTag() == tag) {
            return formNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = formNode->GetParent();
        if (parent) {
            parent->RemoveChild(formNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    formNode = AceType::MakeRefPtr<FormNode>(tag, nodeId, pattern, false);
    formNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(formNode);
    return formNode;
}

void FormNode::OnDetachFromMainTree(bool recursive)
{
    auto eventHub = GetEventHub<FormEventHub>();
    eventHub->FireOnCache();
    FrameNode::OnDetachFromMainTree(recursive);
}
} // namespace OHOS::Ace::NG
