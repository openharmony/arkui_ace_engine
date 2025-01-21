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

#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include <cstdint>

namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t PRESS_STYLE_DELAY = 300;
constexpr uint32_t PRESS_CANCEL_STYLE_DELAY = 64;
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
            TAG_LOGW(AceLogTag::ACE_STATE_STYLE, "the touch info is illegal");
            return;
        }

        auto lastPoint = changeTouches.back();
        const auto& type = lastPoint.GetTouchType();
        if (type == TouchType::DOWN) {
            stateStyleMgr->HandleTouchDown();
            stateStyleMgr->pointerId_.insert(lastPoint.GetFingerId());
        }
        if ((type == TouchType::UP) || (type == TouchType::CANCEL)) {
            stateStyleMgr->pointerId_.erase(lastPoint.GetFingerId());
            if (stateStyleMgr->pointerId_.size() == 0) {
                stateStyleMgr->HandleTouchUp();
            }
        }
        if ((type == TouchType::MOVE) &&
            (stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED) || stateStyleMgr->IsPressedStatePending())) {
            int32_t sourceType = static_cast<int32_t>(touches.front().GetSourceDevice());
            if (stateStyleMgr->IsOutOfPressedRegion(sourceType, lastPoint.GetGlobalLocation())) {
                auto frameNode = stateStyleMgr->GetFrameNode();
                CHECK_NULL_VOID(frameNode);
                TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Move out of node pressed region: %{public}s",
                    frameNode->GetTag().c_str());
                stateStyleMgr->pointerId_.erase(lastPoint.GetFingerId());
                if (stateStyleMgr->pointerId_.size() == 0) {
                    stateStyleMgr->ResetPressedState();
                    stateStyleMgr->PostListItemPressStyleTask(stateStyleMgr->currentState_);
                }
            }
        }
    };
    pressedFunc_ = MakeRefPtr<TouchEventImpl>(std::move(pressedCallback));
    return pressedFunc_;
}

void StateStyleManager::HandleTouchDown()
{
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);
#ifdef IS_RELEASE_VERSION
    TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Handle TouchDown event node: %{public}s", node->GetTag().c_str());
#else
    TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Handle TouchDown event node: %{public}s/%{public}d",
        node->GetTag().c_str(), node->GetId());
#endif
    HandleScrollingParent();
    if (!hasScrollingParent_) {
        UpdateCurrentUIState(UI_STATE_PRESSED);
        PostListItemPressStyleTask(currentState_);
    } else {
        if (IsPressedCancelStatePending()) {
            ResetPressedCancelState();
        }
        PostPressStyleTask(PRESS_STYLE_DELAY);
        PendingPressedState();
    }
}

void StateStyleManager::HandleTouchUp()
{
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);
#ifdef IS_RELEASE_VERSION
    TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Handle TouchUp or Cancel event node: %{public}s",
        node->GetTag().c_str());
#else
    TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Handle TouchUp or Cancel event node: %{public}s/%{public}d",
        node->GetTag().c_str(), node->GetId());
#endif
    if (IsPressedStatePending()) {
        DeletePressStyleTask();
        ResetPressedPendingState();
        UpdateCurrentUIState(UI_STATE_PRESSED);
        PostPressCancelStyleTask(PRESS_CANCEL_STYLE_DELAY);
        PendingCancelPressedState();
    } else if (!IsPressedCancelStatePending()) {
        ResetPressedState();
        PostListItemPressStyleTask(currentState_);
    }
    if (hasScrollingParent_) {
        CleanScrollingParentListener();
    }
}

void StateStyleManager::FireStateFunc(bool isReset)
{
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);
    auto nodeId = node->GetId();
#ifdef IS_RELEASE_VERSION
    TAG_LOGI(AceLogTag::ACE_STATE_STYLE,"Start execution, node is %{public}s, "
        "reset is %{public}d", node->GetTag().c_str(), isReset);
#else
    TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Start execution, node is %{public}s/%{public}d, "
        "reset is %{public}d", node->GetTag().c_str(), nodeId, isReset);
#endif
    auto uiNode = DynamicCast<UINode>(node);
    CHECK_NULL_VOID(uiNode);
    RefPtr<CustomNodeBase> customNode;
    GetCustomNode(customNode, uiNode);
    if (!customNode || (!customNode->FireHasNodeUpdateFunc(nodeId))) {
        TAG_LOGW(AceLogTag::ACE_STATE_STYLE, "Can not find customNode!");
        return;
    }
    ScopedViewStackProcessor processor;
    customNode->FireNodeUpdateFunc(nodeId);
}

void StateStyleManager::GetCustomNode(RefPtr<CustomNodeBase>& customNode, RefPtr<UINode> node)
{
    auto nodeId = node->GetId();
    while (node) {
        if (GetCustomNodeFromNavgation(node, customNode, nodeId)) {
            return;
        }

        auto parentFrameNode = DynamicCast<FrameNode>(node);
        auto parentPattern = parentFrameNode ? parentFrameNode->GetPattern<PopupBasePattern>() : nullptr;
        if (parentFrameNode && InstanceOf<PopupBasePattern>(parentPattern)) {
            auto elementRegister = ElementRegister::GetInstance();
            CHECK_NULL_VOID(elementRegister);
            node = elementRegister->GetUINodeById(parentPattern->GetTargetId());
            continue;
        }

        if (GetCustomNodeFromSelf(node, customNode, nodeId)) {
            return;
        }
        node = node->GetParent();
    }
}

bool StateStyleManager::GetCustomNodeFromSelf(RefPtr<UINode>& node, RefPtr<CustomNodeBase>& customNode, int32_t nodeId)
{
    if (node && AceType::InstanceOf<CustomNodeBase>(node)) {
        auto customNodeBase = DynamicCast<CustomNodeBase>(node);
        if (customNodeBase && customNodeBase->FireHasNodeUpdateFunc(nodeId)) {
            customNode = customNodeBase;
            TAG_LOGI(
                AceLogTag::ACE_STATE_STYLE, "Find customNode by self: %{public}s", customNode->GetJSViewName().c_str());
            return true;
        }
    }
    return false;
}

bool StateStyleManager::GetCustomNodeFromNavgation(
    RefPtr<UINode>& node, RefPtr<CustomNodeBase>& customNode, int32_t nodeId)
{
    while (node && AceType::InstanceOf<NavDestinationGroupNode>(node)) {
        auto navDestinationGroupNode = DynamicCast<NavDestinationGroupNode>(node);
        CHECK_NULL_RETURN(navDestinationGroupNode, false);
        auto navDestinationCustomNode = navDestinationGroupNode->GetNavDestinationCustomNode();
        CHECK_NULL_RETURN(navDestinationCustomNode, false);
        if (navDestinationCustomNode->FireHasNodeUpdateFunc(nodeId)) {
            customNode = navDestinationCustomNode;
            TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Find customNode from Navgation: %{public}s",
                customNode->GetJSViewName().c_str());
            return true;
        }
        auto customParent = DynamicCast<CustomNode>(navDestinationCustomNode);
        CHECK_NULL_RETURN(navDestinationCustomNode, false);
        node = customParent->GetParent();
    }
    return false;
}

void StateStyleManager::PostPressStyleTask(uint32_t delayTime)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
        TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Execute press task");
        stateStyleMgr->ResetPressedPendingState();
        stateStyleMgr->UpdateCurrentUIState(UI_STATE_PRESSED);
        stateStyleMgr->PostListItemPressStyleTask(stateStyleMgr->currentState_);
    });

    taskExecutor->PostDelayedTask(pressStyleTask_, TaskExecutor::TaskType::UI, delayTime, "ArkUIPressStateStyle");
}

void StateStyleManager::PostPressCancelStyleTask(uint32_t delayTime)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    if (IsPressedStatePending() || IsPressedCancelStatePending()) {
        return;
    }

    auto weak = AceType::WeakClaim(this);
    pressCancelStyleTask_.Reset([weak = WeakClaim(this)] {
        auto stateStyleMgr = weak.Upgrade();
        CHECK_NULL_VOID(stateStyleMgr);
        TAG_LOGI(AceLogTag::ACE_STATE_STYLE, "Execute press clear task");
        stateStyleMgr->ResetPressedCancelPendingState();
        stateStyleMgr->ResetCurrentUIState(UI_STATE_PRESSED);
        stateStyleMgr->PostListItemPressStyleTask(stateStyleMgr->currentState_);
    });

    taskExecutor->PostDelayedTask(
        pressCancelStyleTask_, TaskExecutor::TaskType::UI, delayTime, "ArkUIPressCancelStateStyle");
}

void StateStyleManager::PostListItemPressStyleTask(UIState state)
{
    bool isPressed = state == UI_STATE_PRESSED;
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);
    auto nodeId = node->GetId();
    if (node->GetTag() == V2::LIST_ITEM_ETS_TAG) {
        auto frameNode = node->GetAncestorNodeOfFrame(false);
        CHECK_NULL_VOID(frameNode);
        if (frameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
            auto listGroupPattern = DynamicCast<ListItemGroupPattern>(frameNode->GetPattern());
            CHECK_NULL_VOID(listGroupPattern);
            listGroupPattern->SetItemPressed(isPressed, nodeId);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        if (frameNode->GetTag() == V2::LIST_ETS_TAG) {
            auto listPattern = DynamicCast<ListPattern>(frameNode->GetPattern());
            CHECK_NULL_VOID(listPattern);
            listPattern->SetItemPressed(isPressed, nodeId);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

void StateStyleManager::HandleScrollingParent()
{
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);

    auto scrollingEventCallback = [weak = WeakClaim(this)]() {
        auto stateStyleMgr = weak.Upgrade();
        CHECK_NULL_VOID(stateStyleMgr);
        stateStyleMgr->ResetCurrentUIState(UI_STATE_PRESSED);
        stateStyleMgr->PostListItemPressStyleTask(stateStyleMgr->currentState_);
        stateStyleMgr->pointerId_.clear();
        stateStyleMgr->ResetPressedPendingState();
        if (stateStyleMgr->pressStyleTask_) {
            stateStyleMgr->DeletePressStyleTask();
        }
    };

    auto scrollingListener = MakeRefPtr<ScrollingListener>(std::move(scrollingEventCallback));

    auto parent = node->GetAncestorNodeOfFrame(false);
    while (parent) {
        auto pattern = parent->GetPattern();
        CHECK_NULL_VOID(pattern);
        if (pattern->ShouldDelayChildPressedState()) {
            hasScrollingParent_ = true;
            pattern->RegisterScrollingListener(scrollingListener);
        }
        parent = parent->GetAncestorNodeOfFrame(false);
    }
}

void StateStyleManager::CleanScrollingParentListener()
{
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);

    auto parent = node->GetAncestorNodeOfFrame(false);
    while (parent) {
        auto pattern = parent->GetPattern();
        CHECK_NULL_VOID(pattern);
        if (pattern->ShouldDelayChildPressedState()) {
            pattern->CleanScrollingListener();
        }
        parent = parent->GetAncestorNodeOfFrame(false);
    }
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
        host = host->GetAncestorNodeOfFrame(true);
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
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    if (IsOutOfPressedRegionWithoutClip(node, sourceType, location)) {
        return true;
    }
    auto parent = node->GetAncestorNodeOfFrame(true);
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        if (!renderContext) {
            parent = parent->GetAncestorNodeOfFrame(true);
            continue;
        }
        // If the parent node has a "clip" attribute, the press region should be re-evaluated.
        auto clip = renderContext->GetClipEdge().value_or(false);
        if (clip && IsOutOfPressedRegionWithoutClip(parent, sourceType, location)) {
            return true;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return false;
}

bool StateStyleManager::IsOutOfPressedRegionWithoutClip(RefPtr<FrameNode> node, int32_t sourceType,
    const Offset& location) const
{
    CHECK_NULL_RETURN(node, false);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);

    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    auto responseRegionList = node->GetResponseRegionList(paintRect, sourceType);
    Offset offset = { paintRect.GetOffset().GetX(), paintRect.GetOffset().GetY() };
    PointF current = { location.GetX(), location.GetY() };
    NGGestureRecognizer::Transform(current, node);
    PointF parentPoint = { current.GetX() + offset.GetX(), current.GetY() + offset.GetY() };
    if (!node->InResponseRegionList(parentPoint, responseRegionList)) {
        return true;
    }
    return false;
}

RefPtr<FrameNode> StateStyleManager::GetFrameNode() const
{
    return host_.Upgrade();
}
} // namespace OHOS::Ace::NG
