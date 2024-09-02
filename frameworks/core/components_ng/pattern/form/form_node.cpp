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

std::shared_ptr<MMI::PointerEvent> ConvertPointerEvent(const OffsetF offsetF, const TouchEvent& point,
    const WeakPtr<FrameNode>& node)
{
    std::shared_ptr<MMI::PointerEvent> pointerEvent = MMI::PointerEvent::Create();
    if (pointerEvent == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "pointerEvent is nullptr");
        return nullptr;
    }

    OHOS::MMI::PointerEvent::PointerItem item;
    PointF transformPoint(point.x, point.y);
    NGGestureRecognizer::Transform(transformPoint, node);
    item.SetWindowX(static_cast<int32_t>(transformPoint.GetX()));
    item.SetWindowY(static_cast<int32_t>(transformPoint.GetY()));
    item.SetWindowXPos(transformPoint.GetX());
    item.SetWindowYPos(transformPoint.GetY());
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

class FormAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    FormAccessibilityChildTreeCallback(const WeakPtr<FormNode> &weakFormNode, int64_t accessibilityId)
        : AccessibilityChildTreeCallback(accessibilityId), weakFormNode_(weakFormNode)
    {}

    ~FormAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override
    {
        auto formNode = weakFormNode_.Upgrade();
        if (formNode == nullptr) {
            return false;
        }
        if (isReg_) {
            return true;
        }
        formNode->OnAccessibilityChildTreeRegister(windowId, treeId);
        isReg_ = true;
        return true;
    }

    bool OnDeregister() override
    {
        auto formNode = weakFormNode_.Upgrade();
        if (formNode == nullptr) {
            return false;
        }
        if (!isReg_) {
            return true;
        }
        formNode->OnAccessibilityChildTreeDeregister();
        isReg_ = false;
        return true;
    }

    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override
    {
        auto formNode = weakFormNode_.Upgrade();
        if (formNode == nullptr) {
            return false;
        }
        formNode->OnSetAccessibilityChildTree(childWindowId, childTreeId);
        return true;
    }

    bool OnDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override
    {
        auto formNode = weakFormNode_.Upgrade();
        if (formNode == nullptr) {
            return false;
        }
        formNode->OnAccessibilityDumpChildInfo(params, info);
        return true;
    }

    void OnClearRegisterFlag() override
    {
        auto formNode = weakFormNode_.Upgrade();
        if (formNode == nullptr) {
            return;
        }
        isReg_ = false;
    }
private:
    bool isReg_ = false;
    WeakPtr<FormNode> weakFormNode_;
};
}

FormNode::~FormNode()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(GetAccessibilityId());
}

HitTestResult FormNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    // The mousetest has been merged into touchtest.
    // FormComponent does not support some mouse event(eg. Hover, HoverAnimation..).
    // Mouse event like LEFT_BUTTON, RELEASE use touchevent to dispatch, so they work well on FormComponent
    if (touchRestrict.hitTestType == SourceType::MOUSE) {
        return HitTestResult::OUT_OF_REGION;
    }

    auto testResult = FrameNode::TouchTest(
        globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result, touchId, responseLinkResult);
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
        auto callback = [weak = WeakClaim(this)](const TouchEvent& touchEvent, SerializedGesture& serializedGesture) {
            auto formNode = weak.Upgrade();
            CHECK_NULL_VOID(formNode);
            formNode->DispatchPointerEvent(touchEvent, serializedGesture);
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

void FormNode::DispatchPointerEvent(const TouchEvent& touchEvent,
    SerializedGesture& serializedGesture)
{
    auto pattern = GetPattern<FormPattern>();
    CHECK_NULL_VOID(pattern);
    auto selfGlobalOffset = GetFormOffset();
    auto pointerEvent = ConvertPointerEvent(selfGlobalOffset, touchEvent, WeakClaim(this));
    pattern->DispatchPointerEvent(pointerEvent, serializedGesture);
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
    formNode->InitializeFormAccessibility();
    ElementRegister::GetInstance()->AddUINode(formNode);
    return formNode;
}

void FormNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    auto eventHub = GetEventHub<FormEventHub>();
    eventHub->FireOnCache();
    FrameNode::OnDetachFromMainTree(recursive, context);
}

void FormNode::InitializeFormAccessibility()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityChildTreeCallback_ = std::make_shared<FormAccessibilityChildTreeCallback>(
        WeakClaim(this), GetAccessibilityId());
    accessibilityManager->RegisterAccessibilityChildTreeCallback(GetAccessibilityId(), accessibilityChildTreeCallback_);

}

void FormNode::NotifyAccessibilityChildTreeRegister()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(pipeline->GetWindowId(), 0);
    }
}

void FormNode::OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId)
{
    auto accessibilityId = GetAccessibilityId();
    auto pattern = GetPattern<FormPattern>();
    if (pattern == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "pattern is null");
        return;
    }
    pattern->OnAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void FormNode::OnAccessibilityChildTreeDeregister()
{
    auto pattern = GetPattern<FormPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->OnAccessibilityChildTreeDeregister();
}

void FormNode::OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId)
{
    auto accessibilityProperty = GetAccessibilityProperty<AccessibilityProperty>();
    if (accessibilityProperty != nullptr) {
        accessibilityProperty->SetChildWindowId(childWindowId);
        accessibilityProperty->SetChildTreeId(childTreeId);
    }
}

void FormNode::OnAccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto pattern = GetPattern<FormPattern>();
    if (pattern == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "pattern is null");
        return;
    }
    pattern->OnAccessibilityDumpChildInfo(params, info);
}

void FormNode::ClearAccessibilityChildTreeRegisterFlag()
{
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    accessibilityChildTreeCallback_->OnClearRegisterFlag();
}
} // namespace OHOS::Ace::NG
