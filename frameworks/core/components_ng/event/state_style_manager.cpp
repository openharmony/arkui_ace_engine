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

#include "core/components_ng/event/state_style_manager.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t PRESS_STYLE_DELAY = 300;
}

StateStyleManager::StateStyleManager(WeakPtr<FrameNode> frameNode) : host_(std::move(frameNode)) {}

StateStyleManager::~StateStyleManager() = default;

const RefPtr<TouchEventImpl>& StateStyleManager::GetPressedListener()
{
    if (pressedFunc_) {
        return pressedFunc_;
    }
    auto pressedCallback = [weak = WeakClaim(this)](TouchEventInfo& info) {
        auto stateStyleMgr = weak.Upgrade();
        CHECK_NULL_VOID(stateStyleMgr);
        const auto& touches = info.GetTouches();
        const auto& changeTouches = info.GetChangedTouches();
        if (touches.empty() || changeTouches.empty()) {
            LOGW("the touch info is illegal");
            return;
        }

        auto lastPoint = changeTouches.back();
        const auto& type = lastPoint.GetTouchType();
        if (type == TouchType::DOWN) {
            if (!stateStyleMgr->HandleScrollingParent()) {
                stateStyleMgr->UpdateCurrentUIState(UI_STATE_PRESSED);
            } else {
                stateStyleMgr->PostPressStyleTask(PRESS_STYLE_DELAY);
                stateStyleMgr->PendingPressedState();
            }
            stateStyleMgr->pointerId_.insert(lastPoint.GetFingerId());
        }
        if ((type == TouchType::UP) || (type == TouchType::CANCEL)) {
            stateStyleMgr->pointerId_.erase(lastPoint.GetFingerId());
            if (stateStyleMgr->pointerId_.size() == 0) {
                stateStyleMgr->ResetPressedState();
            }
        }
        if ((type == TouchType::MOVE) &&
            (stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED) || stateStyleMgr->IsPressedStatePending())) {
            int32_t sourceType = static_cast<int32_t>(touches.front().GetSourceDevice());
            if (stateStyleMgr->IsOutOfPressedRegion(sourceType, lastPoint.GetGlobalLocation())) {
                stateStyleMgr->pointerId_.erase(lastPoint.GetFingerId());
                if (stateStyleMgr->pointerId_.size() == 0) {
                    stateStyleMgr->ResetPressedState();
                }
            }
        }
    };
    pressedFunc_ = MakeRefPtr<TouchEventImpl>(std::move(pressedCallback));
    return pressedFunc_;
}

void StateStyleManager::FireStateFunc()
{
    auto node = host_.Upgrade();
    CHECK_NULL_VOID(node);
    auto nodeId = node->GetId();
    RefPtr<CustomNodeBase> customNode;
    if (AceType::InstanceOf<CustomNodeBase>(node)) {
        customNode = DynamicCast<CustomNodeBase>(node);
    }
    if (!customNode) {
        auto parent = node->GetParent();
        while (parent) {
            if (AceType::InstanceOf<NavDestinationGroupNode>(parent)) {
                auto navDestinationGroupNode = DynamicCast<NavDestinationGroupNode>(parent);
                CHECK_NULL_VOID(navDestinationGroupNode);
                customNode = navDestinationGroupNode->GetNavDestinationCustomNode();
            }

            auto parentFrameNode = DynamicCast<FrameNode>(parent);
            auto parentPattern = parentFrameNode ? parentFrameNode->GetPattern<PopupBasePattern>() : nullptr;
            if (parentFrameNode && InstanceOf<PopupBasePattern>(parentPattern)) {
                parent = ElementRegister::GetInstance()->GetUINodeById(parentPattern->GetTargetId());
                continue;
            }

            if (customNode) {
                break;
            }

            if (AceType::InstanceOf<CustomNodeBase>(parent)) {
                customNode = DynamicCast<CustomNodeBase>(parent);
                break;
            }
            parent = parent->GetParent();
        }
    }
    if (!customNode) {
        return;
    }
    ScopedViewStackProcessor processor;
    customNode->FireNodeUpdateFunc(nodeId);
}

void StateStyleManager::PostPressStyleTask(uint32_t delayTime)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    if (IsPressedStatePending()) {
        return;
    }

    auto weak = AceType::WeakClaim(this);
    pressStyleTask_.Reset([weak = WeakClaim(this)] {
        auto stateStyleMgr = weak.Upgrade();
        CHECK_NULL_VOID(stateStyleMgr);
        stateStyleMgr->ResetPressedPendingState();
        stateStyleMgr->UpdateCurrentUIState(UI_STATE_PRESSED);
    });

    taskExecutor->PostDelayedTask(pressStyleTask_, TaskExecutor::TaskType::UI, delayTime);
}

bool StateStyleManager::HandleScrollingParent()
{
    auto node = host_.Upgrade();
    CHECK_NULL_RETURN(node, false);

    auto scrollingEventCallback = [weak = WeakClaim(this)]() {
        auto stateStyleMgr = weak.Upgrade();
        CHECK_NULL_VOID(stateStyleMgr);
        stateStyleMgr->ResetCurrentUIState(UI_STATE_PRESSED);
        stateStyleMgr->pointerId_.clear();
        stateStyleMgr->ResetPressedPendingState();
        if (stateStyleMgr->pressStyleTask_) {
            stateStyleMgr->CancelPressStyleTask();
        }
    };

    auto scrollingListener = MakeRefPtr<ScrollingListener>(std::move(scrollingEventCallback));

    bool hasScrollingParent = false;
    auto parent = node->GetAncestorNodeOfFrame();
    while (parent) {
        auto pattern = parent->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        if (pattern->ShouldDelayChildPressedState()) {
            hasScrollingParent = true;
            pattern->RegisterScrollingListener(scrollingListener);
        }
        parent = parent->GetAncestorNodeOfFrame();
    }

    return hasScrollingParent;
}

void StateStyleManager::Transform(PointF& localPointF, const WeakPtr<FrameNode>& node) const
{
    if (node.Invalid()) {
        return;
    }

    std::vector<Matrix4> vTrans {};
    auto host = node.Upgrade();
    while (host) {
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        auto localMat = context->GetLocalTransformMatrix();
        vTrans.emplace_back(localMat);
        host = host->GetAncestorNodeOfFrame();
    }

    Point temp(localPointF.GetX(), localPointF.GetY());
    for (auto iter = vTrans.rbegin(); iter != vTrans.rend(); iter++) {
        temp = *iter * temp;
    }
    localPointF.SetX(temp.GetX());
    localPointF.SetY(temp.GetY());
}

bool StateStyleManager::IsOutOfPressedRegion(int32_t sourceType, const Offset& location) const
{
    auto node = host_.Upgrade();
    CHECK_NULL_RETURN(node, false);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);

    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    auto responseRegionList = node->GetResponseRegionList(paintRect, sourceType);
    Offset offset = { paintRect.GetOffset().GetX(), paintRect.GetOffset().GetY() };
    PointF current = { location.GetX(), location.GetY() };
    Transform(current, node);
    PointF parentPoint = { current.GetX() + offset.GetX(), current.GetY() + offset.GetY() };
    if (!node->InResponseRegionList(parentPoint, responseRegionList)) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG