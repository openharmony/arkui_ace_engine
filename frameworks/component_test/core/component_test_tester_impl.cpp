/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "component_test/core/component_test_tester_impl.h"

#include <algorithm>
#include <queue>

#include "base/geometry/ng/point_t.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components_ng/base/ui_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::ComponentTest {
ComponentTestComponentImpl* ComponentTestTesterImpl::FindComponentImpl(
    const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const
{
    errInfo = QueryRetMsg(RET_ERR_FAILED);
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(context, nullptr);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);
    errInfo = QueryRetMsg(RET_OK);
    std::queue<RefPtr<NG::UINode>> elements;
    elements.push(rootNode);
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        if (matcher.Match(current)) {
            ComponentTestComponentImpl* componentTestComponentImpl = new ComponentTestComponentImpl();
            componentTestComponentImpl->SetUiNode(current);
            componentTestComponentImpl->SetEffective();
            return componentTestComponentImpl;
        }

        const auto& children = current->GetChildren();
        for (const auto& child : children) {
            elements.push(child);
        }
    }
    return nullptr;
}

std::unique_ptr<std::vector<ComponentTestComponentImpl*>> ComponentTestTesterImpl::FindComponentsImpl(
    const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const
{
    auto testerElements = std::make_unique<std::vector<ComponentTestComponentImpl*>>();
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    errInfo = QueryRetMsg(RET_ERR_FAILED);
    CHECK_NULL_RETURN(container, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(context, nullptr);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);
    errInfo = QueryRetMsg(RET_OK);

    std::queue<RefPtr<NG::UINode>> elements;
    elements.push(rootNode);
    RefPtr<NG::UINode> inspectorElement;
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        if (matcher.Match(current)) {
            ComponentTestComponentImpl* componentTestComponentImpl = new ComponentTestComponentImpl();
            componentTestComponentImpl->SetUiNode(current);
            componentTestComponentImpl->SetEffective();
            testerElements->emplace_back(componentTestComponentImpl);
        }

        const auto& children = current->GetChildren();
        for (const auto& child : children) {
            elements.push(child);
        }
    }
    return testerElements;
}

void ComponentTestTesterImpl::AssertComponentExistImpl(const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const
{
    ComponentTestComponentImpl* component = FindComponentImpl(matcher, errInfo);
    if (component == nullptr) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_ASSERTION_COMPONENT_EXIST);
        return;
    }
    delete component;
}

ComponentTestComponentImpl* ComponentTestTesterImpl::ScrollUntilExistImpl(
    const ComponentTestMatcherImpl& matcher, ErrInfo& errInfo) const
{
    errInfo = QueryRetMsg(ErrCode::RET_ERR_FAILED);
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(context, nullptr);
    auto rootNode = context->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);

    std::queue<RefPtr<NG::UINode>> elements;
    RefPtr<NG::UINode> target = nullptr;
    elements.push(rootNode);
    auto scale = context->GetViewScale();
    NG::RectF screenRect(0.0, 0.0, context->GetRootWidth() * scale, context->GetRootHeight() * scale);
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        if (matcher.Match(current)) {
            target = current;
            break;
        }

        const auto& children = current->GetChildren();
        for (const auto& child : children) {
            elements.push(child);
        }
    }
    if (target) {
        const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(target);
        NG::RectF rect = frameNode->GetTransformRectRelativeToWindow();
        ScrollImpl(rect.GetX(), rect.GetY(), errInfo);
        ComponentTestComponentImpl* componentTestComponentImpl = new ComponentTestComponentImpl();
        componentTestComponentImpl->SetUiNode(target);
        errInfo = QueryRetMsg(ErrCode::RET_OK);
        return componentTestComponentImpl;
    }
    return nullptr;
}

void ComponentTestTesterImpl::TriggerKeyImpl(OHOS::MMI::KeyCode keyCode, ErrInfo& errInfo) const
{
    SingleKeyAction singleKeyAction(keyCode);
    singleKeyAction.Send();
}

void ComponentTestTesterImpl::TriggerCombineKeysImpl(
    const std::vector<OHOS::MMI::KeyCode>& keyCodes, ErrInfo& errInfo) const
{
    CombinedKeysAction combinedKeysAction(keyCodes);
    combinedKeysAction.Send();
}

void ComponentTestTesterImpl::TapImpl(float x, float y, ErrInfo& errInfo) const
{
    GenericClick(x, y, TouchType::TAP);
}

void ComponentTestTesterImpl::DoubleTapImpl(float x, float y, ErrInfo& errInfo) const
{
    GenericClick(x, y, TouchType::DOUBLE_TAP);
}

void ComponentTestTesterImpl::PressImpl(float x, float y, ErrInfo& errInfo, uint32_t duration) const
{
    GenericClick(x, y, TouchType::PRESS, duration);
}

void ComponentTestTesterImpl::ScrollImpl(float deltaX, float deltaY, ErrInfo& errInfo) const
{
    ScrollAction scrollAction(deltaX, deltaY);
    EventSequenceManager::GetInstance().Execute(&scrollAction);
}

void ComponentTestTesterImpl::DragImpl(
    float startX, float startY, float endX, float endY, uint32_t speed, ErrInfo& errInfo) const
{
    NG::PointF startPonit(startX, startY);
    NG::PointF endPonit(endX, endY);
    MoveAction moveAction(startPonit, endPonit, TouchType::DRAG);
    EventSequenceManager::GetInstance().Execute(&moveAction);
}

void ComponentTestTesterImpl::FlingImpl(
    const NG::PointF& from, const NG::PointF& to, uint32_t stepLen, uint32_t speed, ErrInfo& errInfo) const
{
    int32_t distanceX = to.GetX() - from.GetX();
    int32_t distanceY = to.GetY() - from.GetY();
    uint32_t distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    if (stepLen > 0 && stepLen <= distance) {
        uint32_t steps = distance / stepLen;
        if (speed < MIN_SPEED || speed > MAX_SPEED) {
            LOGW("%{public}s", "The fling speed out of range");
            speed = DEFAULT_SPEED;
        }
        MoveAction moveAction(from, to, TouchType::FLING, speed, steps);
        EventSequenceManager::GetInstance().Execute(&moveAction);
        errInfo = QueryRetMsg(ErrCode::RET_OK);
    } else {
        errInfo = QueryRetMsg(ErrCode::RET_ERROR_PARAM_INVALID);
    }
}

void ComponentTestTesterImpl::FlingImpl(UiDirection direction, uint32_t speed, ErrInfo& errInfo) const
{
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    if (!container) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_FAILED);
        return;
    }
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!context) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_FAILED);
        return;
    }
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    NG::RectF screenRect(0.0, 0.0, rootWidth * scale, rootHeight * scale);
    NG::PointF to;
    NG::PointF from(screenRect.Width() * HALF, screenRect.Height() * HALF);
    switch (direction) {
        case UiDirection::TO_UP:
            to.SetX(screenRect.Width() * HALF);
            to.SetY(screenRect.Height() * HALF - screenRect.Height() * QUARTER);
            break;
        case UiDirection::TO_DOWN:
            to.SetX(screenRect.Width() * HALF);
            to.SetY(screenRect.Height() * HALF + screenRect.Width() * QUARTER);
            break;
        case UiDirection::TO_LEFT:
            to.SetX(screenRect.Width() * HALF - screenRect.Width() * QUARTER);
            to.SetY(screenRect.Height() * HALF);
            break;
        case UiDirection::TO_RIGHT:
            to.SetX(screenRect.Width() * HALF + screenRect.Width() * QUARTER);
            to.SetY(screenRect.Height() * HALF);
            break;
        default:
            errInfo = QueryRetMsg(ErrCode::RET_ERROR_PARAM_INVALID);
            return;
    }
    MoveAction moveAction(from, to, TouchType::FLING, speed, MIN_STEP_CONUT);
    EventSequenceManager::GetInstance().Execute(&moveAction);
    errInfo = QueryRetMsg(ErrCode::RET_OK);
}

void ComponentTestTesterImpl::GenericClick(float x, float y, const TouchType touchType, uint32_t duration) const
{
    auto point = NG::PointF(x, y);
    ClickAction clickAction(point, touchType, duration);
    EventSequenceManager::GetInstance().Execute(&clickAction);
}

} // namespace OHOS::Ace::ComponentTest
