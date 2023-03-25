/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/focus_hub.h"

#include <cinttypes>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/event/ace_event_handler.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> FocusHub::GetFrameNode() const
{
    auto eventHub = eventHub_.Upgrade();
    return eventHub ? eventHub->GetFrameNode() : nullptr;
}

RefPtr<GeometryNode> FocusHub::GetGeometryNode() const
{
    auto frameNode = GetFrameNode();
    return frameNode ? frameNode->GetGeometryNode() : nullptr;
}

std::optional<std::string> FocusHub::GetInspectorKey() const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN_NOLOG(frameNode, std::nullopt);
    return frameNode->GetInspectorId();
}

RefPtr<FocusHub> FocusHub::GetParentFocusHub() const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN_NOLOG(frameNode, nullptr);
    auto parentNode = frameNode->GetFocusParent();
    return parentNode ? parentNode->GetFocusHub() : nullptr;
}

std::string FocusHub::GetFrameName() const
{
    auto frameNode = GetFrameNode();
    return frameNode ? frameNode->GetTag() : "NULL";
}

int32_t FocusHub::GetFrameId() const
{
    auto frameNode = GetFrameNode();
    return frameNode ? frameNode->GetId() : -1;
}

std::list<RefPtr<FocusHub>>::iterator FocusHub::FlushChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes)
{
    focusNodes.clear();
    std::list<RefPtr<FrameNode>> childrenNode;
    auto frameNode = GetFrameNode();
    if (frameNode) {
        frameNode->GetFocusChildren(childrenNode);
    }
    for (const auto& child : childrenNode) {
        if (child->GetFocusHub()) {
            focusNodes.emplace_back(child->GetFocusHub());
        }
    }
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (!lastFocusNode) {
        return focusNodes.end();
    }
    return std::find(focusNodes.begin(), focusNodes.end(), lastFocusNode);
}

bool FocusHub::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (!IsCurrentFocus()) {
        return false;
    }
    return OnKeyEvent(keyEvent);
}

void FocusHub::DumpFocusTree(int32_t depth)
{
    if (focusType_ == FocusType::NODE) {
        DumpFocusNodeTree(depth);
    } else if (focusType_ == FocusType::SCOPE) {
        DumpFocusScopeTree(depth);
    }
}

void FocusHub::DumpFocusNodeTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        std::string information = GetFrameName();
        if (IsCurrentFocus()) {
            information += "(Node*)";
        } else {
            information += "(Node)";
        }
        information += (" id:" + std::to_string(GetFrameId()));
        if (!IsFocusable()) {
            information = "(-)" + information;
        }
        DumpLog::GetInstance().Print(depth, information, 0);
    }
}

void FocusHub::DumpFocusScopeTree(int32_t depth)
{
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    if (DumpLog::GetInstance().GetDumpFile()) {
        std::string information = GetFrameName();
        if (IsCurrentFocus()) {
            information += "(Scope*)";
        } else {
            information += "(Scope)";
        }
        information += (" id:" + std::to_string(GetFrameId()));
        if (!IsFocusable()) {
            information = "(-)" + information;
        }
        DumpLog::GetInstance().Print(depth, information, static_cast<int32_t>(focusNodes.size()));
    }

    for (const auto& item : focusNodes) {
        item->DumpFocusTree(depth + 1);
    }
}

bool FocusHub::RequestFocusImmediately()
{
    auto context = NG::PipelineContext::GetCurrentContext();
    if (context && context->GetIsFocusingByTab()) {
        if (!IsFocusableByTab()) {
            return false;
        }
    }

    if (IsCurrentFocus()) {
        return true;
    }

    if (!IsFocusable()) {
        return false;
    }

    currentFocus_ = true;
    UpdateAccessibilityFocusInfo();

    if (onPreFocusCallback_) {
        onPreFocusCallback_();
    }

    auto parent = GetParentFocusHub();
    if (parent) {
        parent->SwitchFocus(AceType::Claim(this));
    } else {
        LOGD("Switch focus. Has no parent.");
    }

    HandleFocus();
    return true;
}

void FocusHub::UpdateAccessibilityFocusInfo()
{
    // Need update
}

void FocusHub::LostFocus(BlurReason reason)
{
    if (IsCurrentFocus()) {
        blurReason_ = reason;
        currentFocus_ = false;
        UpdateAccessibilityFocusInfo();
        OnBlur();
    }
}

void FocusHub::LostSelfFocus()
{
    if (IsCurrentFocus()) {
        SetFocusable(false);
        SetFocusable(true);
    }
}

void FocusHub::RemoveSelf()
{
    auto parent = GetParentFocusHub();
    if (parent) {
        parent->RemoveChild(AceType::Claim(this));
    } else {
        LostFocus(BlurReason::FRAME_DESTROY);
    }
}

void FocusHub::RemoveChild(const RefPtr<FocusHub>& focusNode)
{
    // Not belong to this focus scope.
    if (!focusNode || focusNode->GetParentFocusHub() != this) {
        return;
    }

    std::list<RefPtr<FocusHub>> focusNodes;
    auto itLastFocusNode = FlushChildrenFocusHub(focusNodes);

    if (focusNode->IsCurrentFocus()) {
        // Try to goto next focus, otherwise goto previous focus.
        if (!GoToNextFocusLinear(true) && !GoToNextFocusLinear(false)) {
            lastWeakFocusNode_ = nullptr;
            RemoveSelf();
        }
        focusNode->LostFocus(BlurReason::FRAME_DESTROY);
    } else {
        if (itLastFocusNode != focusNodes.end() && (*itLastFocusNode) == focusNode) {
            lastWeakFocusNode_ = nullptr;
        }
    }

    auto it = std::find(focusNodes.begin(), focusNodes.end(), focusNode);
    if (it == focusNodes.end()) {
        return;
    }
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode == focusNode) {
        lastWeakFocusNode_ = nullptr;
    }
}

// Need update RebuildChild function

bool FocusHub::IsFocusable()
{
    if (focusType_ == FocusType::NODE) {
        return IsFocusableNode();
    }
    if (focusType_ == FocusType::SCOPE) {
        return IsFocusableScope();
    }
    return false;
}

bool FocusHub::IsFocusableScope()
{
    if (!IsFocusableNode()) {
        return false;
    }
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    // TODO: Contaner without child can be focusable
    return std::any_of(focusNodes.begin(), focusNodes.end(),
        [](const RefPtr<FocusHub>& focusNode) { return focusNode->IsFocusable(); });
}

bool FocusHub::IsFocusableNode()
{
    return IsEnabled() && show_ && focusable_ && parentFocusable_;
}

void FocusHub::SetFocusable(bool focusable)
{
    if (focusable_ == focusable) {
        return;
    }
    focusable_ = focusable;
    RefreshParentFocusable(IsFocusable());
    RefreshFocus();
}

bool FocusHub::IsEnabled() const
{
    auto eventHub = eventHub_.Upgrade();
    return eventHub ? eventHub->IsEnabled() : true;
}

void FocusHub::SetEnabled(bool enabled)
{
    if (focusType_ == FocusType::NODE) {
        SetEnabledNode(enabled);
    } else if (focusType_ == FocusType::SCOPE) {
        SetEnabledScope(enabled);
    }
}

void FocusHub::SetEnabledNode(bool enabled)
{
    if (!enabled) {
        RefreshFocus();
    }
}

void FocusHub::SetEnabledScope(bool enabled)
{
    SetEnabledNode(enabled);
    RefreshParentFocusable(IsFocusableNode());
}

void FocusHub::SetShow(bool show)
{
    if (focusType_ == FocusType::NODE) {
        SetShowNode(show);
    } else if (focusType_ == FocusType::SCOPE) {
        SetShowScope(show);
    }
}

void FocusHub::SetShowNode(bool show)
{
    show_ = show;
    if (!show) {
        RefreshFocus();
    }
}

void FocusHub::SetShowScope(bool show)
{
    SetShowNode(show);
    RefreshParentFocusable(IsFocusableNode());
}

void FocusHub::SetIsFocusOnTouch(bool isFocusOnTouch)
{
    if (!focusCallbackEvents_) {
        focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
    }
    if (focusCallbackEvents_->IsFocusOnTouch().has_value() &&
        focusCallbackEvents_->IsFocusOnTouch().value() == isFocusOnTouch) {
        return;
    }
    focusCallbackEvents_->SetIsFocusOnTouch(isFocusOnTouch);

    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);

    if (!isFocusOnTouch && !focusOnTouchListener_) {
        return;
    }
    if (!isFocusOnTouch && focusOnTouchListener_) {
        gesture->RemoveTouchEvent(focusOnTouchListener_);
        return;
    }
    if (!focusOnTouchListener_) {
        auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
            auto focusHub = weak.Upgrade();
            if (focusHub && info.GetTouches().front().GetTouchType() == TouchType::UP) {
                focusHub->RequestFocusImmediately();
            }
        };
        focusOnTouchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    }
    gesture->AddTouchEvent(focusOnTouchListener_);
}

void FocusHub::RefreshFocus()
{
    if (!IsCurrentFocus()) {
        return;
    }

    // lost current focus and request another focus
    auto parent = GetParentFocusHub();

    // current node is root node
    if (!parent) {
        LostFocus();
        return;
    }
    while (!parent->IsFocusable()) {
        // parent node is root node
        if (!parent->GetParentFocusHub()) {
            parent->LostFocus();
            return;
        }
        parent = parent->GetParentFocusHub();
    }
    parent->LostFocus();
    parent->RequestFocusImmediately();
}

bool FocusHub::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (focusType_ == FocusType::SCOPE) {
        return OnKeyEventScope(keyEvent);
    }
    if (focusType_ == FocusType::NODE) {
        return OnKeyEventNode(keyEvent);
    }
    LOGE("Current node focus type: %{public}d is invalid.", focusType_);
    return false;
}

bool FocusHub::OnKeyEventNode(const KeyEvent& keyEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    if (keyEvent.action == KeyAction::DOWN) {
        switch (keyEvent.code) {
            case KeyCode::KEY_SPACE:
                OnClick(keyEvent);
                break;
            default:
                LOGD("KeyCode is %{public}d. Do nothing", keyEvent.code);
        }
    }

    auto retInternal = false;
    if (onKeyEventInternal_) {
        retInternal = onKeyEventInternal_(keyEvent);
    }

    auto info = KeyEventInfo(keyEvent);
    auto onKeyEventCallback = GetOnKeyCallback();
    if (!onKeyEventCallback) {
        return retInternal;
    }
    LOGD("FocusHub::OnKeyEvent: Do key callback on %{public}s/%{public}d with key event{ Code(%{public}d), "
         "Action(%{public}d), "
         "SourceType(%{public}d), DeviceId(%{public}" PRId64 ") }. Return: %{public}d",
        GetFrameName().c_str(), GetFrameId(), info.GetKeyCode(), info.GetKeyType(), info.GetSourceDevice(),
        info.GetDeviceId(), info.IsStopPropagation());
    onKeyEventCallback(info);
    auto retCallback = info.IsStopPropagation();
    return retInternal || retCallback;
}

bool FocusHub::OnKeyEventScope(const KeyEvent& keyEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    std::list<RefPtr<FocusHub>> focusNodes;
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode && lastFocusNode->HandleKeyEvent(keyEvent)) {
        return true;
    }

    if (OnKeyEventNode(keyEvent)) {
        return true;
    }

    if (keyEvent.action != KeyAction::DOWN) {
        return false;
    }

    if (!CalculatePosition()) {
        return false;
    }

    switch (keyEvent.code) {
        case KeyCode::TV_CONTROL_UP:
            LOGI("Node: %{public}s/%{public}d request next focus by Key-'UP'", GetFrameName().c_str(), GetFrameId());
            return RequestNextFocus(FocusStep::UP, GetRect());
        case KeyCode::TV_CONTROL_DOWN:
            LOGI("Node: %{public}s/%{public}d request next focus by Key-'DOWN'", GetFrameName().c_str(), GetFrameId());
            return RequestNextFocus(FocusStep::DOWN, GetRect());
        case KeyCode::TV_CONTROL_LEFT:
            LOGI("Node: %{public}s/%{public}d request next focus by Key-'LEFT'", GetFrameName().c_str(), GetFrameId());
            return RequestNextFocus(FocusStep::LEFT, GetRect());
        case KeyCode::TV_CONTROL_RIGHT:
            LOGI("Node: %{public}s/%{public}d request next focus by Key-'RIGHT'", GetFrameName().c_str(), GetFrameId());
            return RequestNextFocus(FocusStep::RIGHT, GetRect());
        case KeyCode::KEY_TAB: {
            auto context = NG::PipelineContext::GetCurrentContext();
            bool ret = false;
            if (keyEvent.pressedCodes.size() == 1) {
                LOGI("Node: %{public}s/%{public}d request next focus by Key-'TAB'", GetFrameName().c_str(),
                    GetFrameId());
                context->SetIsFocusingByTab(true);
                ret = RequestNextFocus(FocusStep::RIGHT, GetRect()) || RequestNextFocus(FocusStep::DOWN, GetRect());
                context->SetIsFocusingByTab(false);
            } else if (keyEvent.IsShiftWith(KeyCode::KEY_TAB)) {
                LOGI("Node: %{public}s/%{public}d request next focus by Key-'SHIFT-TAB'", GetFrameName().c_str(),
                    GetFrameId());
                context->SetIsFocusingByTab(true);
                ret = RequestNextFocus(FocusStep::LEFT, GetRect()) || RequestNextFocus(FocusStep::UP, GetRect());
                context->SetIsFocusingByTab(false);
            }
            return ret;
        }
        case KeyCode::KEY_MOVE_HOME:
            LOGI("Node: %{public}s/%{public}d request next focus by Key-'HOME'", GetFrameName().c_str(), GetFrameId());
            return RequestNextFocus(FocusStep::LEFT_END, GetRect()) || RequestNextFocus(FocusStep::UP_END, GetRect());
        case KeyCode::KEY_MOVE_END:
            LOGI("Node: %{public}s/%{public}d request next focus by Key-'END'", GetFrameName().c_str(), GetFrameId());
            return RequestNextFocus(FocusStep::RIGHT_END, GetRect()) ||
                   RequestNextFocus(FocusStep::DOWN_END, GetRect());
        default:
            return false;
    }
}

void FocusHub::RequestFocus() const
{
    if (IsCurrentFocus()) {
        return;
    }
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddDirtyFocus(GetFrameNode());
}

bool FocusHub::RequestNextFocus(FocusStep moveStep, const RectF& rect)
{
    bool vertical = IsFocusStepVertical(moveStep);
    bool reverse = !IsFocusStepForward(moveStep);
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        reverse = !reverse;
    }
    SetScopeFocusAlgorithm();
    if (!focusAlgorithm_.getNextFocusNode) {
        if (focusAlgorithm_.isVertical != vertical) {
            return false;
        }
        return GoToNextFocusLinear(reverse, rect);
    }
    WeakPtr<FocusHub> nextFocusHubWeak;
    focusAlgorithm_.getNextFocusNode(moveStep, lastWeakFocusNode_, nextFocusHubWeak);
    auto nextFocusHub = nextFocusHubWeak.Upgrade();
    if (!nextFocusHub) {
        LOGE("Can't find next focus hub with focus algorithm.");
        return false;
    }
    return nextFocusHub->RequestFocusImmediately();
}

void FocusHub::RefreshParentFocusable(bool focusable)
{
    if (focusType_ != FocusType::SCOPE) {
        return;
    }
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    for (auto& item : focusNodes) {
        if (focusable != item->IsParentFocusable()) {
            item->SetParentFocusable(focusable);
            item->RefreshParentFocusable(item->IsFocusableNode());
        }
    }
}

void FocusHub::OnClick(const KeyEvent& event)
{
    auto onClickCallback = GetOnClickCallback();
    if (onClickCallback) {
        auto info = GestureEvent();
        info.SetTimeStamp(event.timeStamp);
        auto rect = GetGeometryNode()->GetFrameRect();
        info.SetGlobalLocation(Offset((rect.Left() + rect.Right()) / 2, (rect.Top() + rect.Bottom()) / 2));
        info.SetLocalLocation(Offset((rect.Right() - rect.Left()) / 2, (rect.Bottom() - rect.Top()) / 2));
        info.SetSourceDevice(event.sourceType);
        info.SetDeviceId(event.deviceId);
        LOGD("FocusHub::OnClick: Do click callback on %{public}s/%{public}d with key event{ "
             "Global(%{public}f,%{public}f), Local(%{public}f,%{public}f), SourceType(%{public}d), "
             "DeviceId(%{public}" PRId64 ") }",
            GetFrameName().c_str(), GetFrameId(), info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY(),
            info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY(), info.GetSourceDevice(), info.GetDeviceId());
        onClickCallback(info);
    }
}

void FocusHub::SwitchFocus(const RefPtr<FocusHub>& focusNode)
{
    if (focusType_ != FocusType::SCOPE) {
        LOGE("SwitchFocus: parent focus node is not a scope!");
        return;
    }
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);

    auto it = std::find(focusNodes.begin(), focusNodes.end(), focusNode);
    if (it == focusNodes.end()) {
        LOGE("SwitchFocus: Can't find node: %{public}s/%{public}d in parent: %{public}s/%{public}d 's children",
            focusNode->GetFrameName().c_str(), focusNode->GetFrameId(), GetFrameName().c_str(), GetFrameId());
    }

    auto focusNodeNeedBlur = lastWeakFocusNode_.Upgrade();
    lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusNode));

    if (focusNodeNeedBlur) {
        LOGD("Switch focus frome %{public}s/%{public}d to %{public}s/%{public}d",
            focusNodeNeedBlur->GetFrameName().c_str(), focusNodeNeedBlur->GetFrameId(),
            focusNode->GetFrameName().c_str(), focusNode->GetFrameId());
    } else {
        LOGD("Switch focus frome NULL/NULL to %{public}s/%{public}d", focusNode->GetFrameName().c_str(),
            focusNode->GetFrameId());
    }
    if (IsCurrentFocus()) {
        if (focusNodeNeedBlur && focusNodeNeedBlur != focusNode) {
            focusNodeNeedBlur->LostFocus();
        }
    } else {
        RequestFocusImmediately();
    }
}

bool FocusHub::GoToNextFocusLinear(bool reverse, const RectF& rect)
{
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = FlushChildrenFocusHub(focusNodes);
    if (focusNodes.empty()) {
        LOGW("FocusNode: %{public}s/%{public}d has no next child focus node to go.", GetFrameName().c_str(),
            GetFrameId());
        return false;
    }
    if (itNewFocusNode == focusNodes.end()) {
        itNewFocusNode = focusNodes.begin();
    }
    if (reverse) {
        if (itNewFocusNode == focusNodes.begin()) {
            itNewFocusNode = focusNodes.end();
            return false;
        }
        --itNewFocusNode;

        while (itNewFocusNode != focusNodes.begin()) {
            if (TryRequestFocus(*itNewFocusNode, rect)) {
                return true;
            }
            --itNewFocusNode;
        }
        if (itNewFocusNode == focusNodes.begin()) {
            if (TryRequestFocus(*itNewFocusNode, rect)) {
                return true;
            }
        }
    } else {
        if (itNewFocusNode != focusNodes.end()) {
            ++itNewFocusNode;
        }
        while (itNewFocusNode != focusNodes.end()) {
            if (TryRequestFocus(*itNewFocusNode, rect)) {
                return true;
            }
            ++itNewFocusNode;
        }
    }

    return false;
}

bool FocusHub::TryRequestFocus(const RefPtr<FocusHub>& focusNode, const RectF& rect)
{
    if (focusNode->AcceptFocusOfLastFocus()) {
        return focusNode->RequestFocusImmediately();
    }
    if (rect.IsValid()) {
        RectF childRect;
        if (!CalculateRect(focusNode, childRect) ||
            !focusNode->AcceptFocusByRectOfLastFocus(rect - childRect.GetOffset())) {
            return false;
        }
    }
    return focusNode->RequestFocusImmediately();
}

bool FocusHub::CalculatePosition()
{
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    CHECK_NULL_RETURN(lastFocusNode, false);

    RectF childRect;
    if (!CalculateRect(lastFocusNode, childRect)) {
        return false;
    }

    if (lastFocusNode->IsChild()) {
        auto lastFocusGeometryNode = lastFocusNode->GetGeometryNode();
        CHECK_NULL_RETURN(lastFocusGeometryNode, false);
        RectF rect(childRect.GetOffset(), lastFocusGeometryNode->GetFrameSize());
        lastFocusNode->SetRect(rect);
        SetRect(rect);
    } else {
        SetRect(lastFocusNode->GetRect() + childRect.GetOffset());
    }

    return true;
}

void FocusHub::SetScopeFocusAlgorithm()
{
    auto frame = GetFrameNode();
    CHECK_NULL_VOID(frame);
    auto pattern = frame->GetPattern();
    CHECK_NULL_VOID(pattern);
    focusAlgorithm_ = pattern->GetScopeFocusAlgorithm();
}

void FocusHub::OnFocus()
{
    if (focusType_ == FocusType::NODE) {
        OnFocusNode();
    } else if (focusType_ == FocusType::SCOPE) {
        OnFocusScope();
    } else {
        LOGE("Current node focus type: %{public}d is invalid.", focusType_);
    }
}

void FocusHub::OnBlur()
{
    if (focusType_ == FocusType::NODE) {
        OnBlurNode();
    } else if (focusType_ == FocusType::SCOPE) {
        OnBlurScope();
    } else {
        LOGE("Current node focus type: %{public}d is invalid.", focusType_);
    }
}

void FocusHub::OnFocusNode()
{
    LOGI("FocusHub: Node(%{public}s/%{public}d) on focus", GetFrameName().c_str(), GetFrameId());
    if (onFocusInternal_) {
        onFocusInternal_();
    }
    auto onFocusCallback = GetOnFocusCallback();
    if (onFocusCallback) {
        onFocusCallback();
    }
    // check focus state style.
    CheckFocusStateStyle(true);
    PaintFocusState();
}

void FocusHub::OnBlurNode()
{
    LOGI("FocusHub: Node(%{public}s/%{public}d) on blur", GetFrameName().c_str(), GetFrameId());
    if (onBlurInternal_) {
        onBlurInternal_();
    }
    if (onBlurReasonInternal_) {
        LOGI("FocusHub: Node(%{public}s/%{public}d) 's blur reason is %{public}d", GetFrameName().c_str(), GetFrameId(),
            blurReason_);
        onBlurReasonInternal_(blurReason_);
    }
    auto onBlurCallback = GetOnBlurCallback();
    if (onBlurCallback) {
        onBlurCallback();
    }
    // check focus state style.
    CheckFocusStateStyle(false);
    if (blurReason_ != BlurReason::FRAME_DESTROY) {
        ClearFocusState();
    }
}

void FocusHub::CheckFocusStateStyle(bool onFocus)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    if (onFocus) {
        eventHub->UpdateCurrentUIState(UI_STATE_FOCUSED);
    } else {
        eventHub->ResetCurrentUIState(UI_STATE_FOCUSED);
    }
}

void FocusHub::OnFocusScope()
{
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itLastFocusNode = FlushChildrenFocusHub(focusNodes);
    if (focusNodes.empty()) {
        LOGE("OnFocusScope focus nodes is empty. No child will be focused.");
        return;
    }

    auto itFocusNode = itLastFocusNode;
    do {
        if (itLastFocusNode == focusNodes.end()) {
            itLastFocusNode = focusNodes.begin();
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode));
            if (itLastFocusNode == itFocusNode) {
                break;
            }
        }
        lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode));
        if ((*itLastFocusNode)->RequestFocusImmediately()) {
            OnFocusNode();
            return;
        }
    } while ((++itLastFocusNode) != itFocusNode);

    // Not found any focusable node, clear focus.
    itLastFocusNode = focusNodes.end();
    lastWeakFocusNode_ = nullptr;
}

void FocusHub::OnBlurScope()
{
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    OnBlurNode();
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode) {
        lastFocusNode->LostFocus(blurReason_);
    }
}

void FocusHub::PaintFocusState()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (focusStyleType_ == FocusStyleType::NONE || !context->GetIsNeedShowFocus()) {
        return;
    }

    if (focusStyleType_ == FocusStyleType::CUSTOM_REGION) {
        CHECK_NULL_VOID(getInnerFocusRectFunc_);
        RoundRect focusRectInner;
        getInnerFocusRectFunc_(focusRectInner);
        PaintInnerFocusState(focusRectInner);
        return;
    }

    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    Color paintColor;
    if (HasPaintColor()) {
        paintColor = GetPaintColor();
    } else {
        paintColor = appTheme->GetFocusColor();
    }
    Dimension paintWidth;
    if (HasPaintWidth()) {
        paintWidth = GetPaintWidth();
    } else {
        paintWidth = appTheme->GetFocusWidthVp();
    }

    if (focusStyleType_ == FocusStyleType::CUSTOM_BORDER) {
        if (!HasPaintRect()) {
            LOGE("PaintFocusState: frame rect has no value while focus style is CUSTOMIZE");
            return;
        }
        renderContext->PaintFocusState(GetPaintRect(), paintColor, paintWidth);
        return;
    }

    Dimension focusPaddingVp = Dimension(0.0, DimensionUnit::VP);
    if (HasFocusPadding()) {
        focusPaddingVp = GetFocusPadding();
    } else {
        if (focusStyleType_ == FocusStyleType::INNER_BORDER) {
            focusPaddingVp = -appTheme->GetFocusWidthVp();
        } else if (focusStyleType_ == FocusStyleType::OUTER_BORDER) {
            focusPaddingVp = appTheme->GetFocusOutPaddingVp();
        }
    }
    if (HasPaintRect()) {
        renderContext->PaintFocusState(GetPaintRect(), focusPaddingVp, paintColor, paintWidth);
    } else {
        renderContext->PaintFocusState(focusPaddingVp, paintColor, paintWidth);
    }
}

void FocusHub::PaintAllFocusState()
{
    PaintFocusState();
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode) {
        lastFocusNode->PaintAllFocusState();
    }
}

void FocusHub::PaintInnerFocusState(const RoundRect& paintRect)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!context->GetIsNeedShowFocus()) {
        return;
    }
    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    Color paintColor;
    if (HasPaintColor()) {
        paintColor = GetPaintColor();
    } else {
        paintColor = appTheme->GetFocusColor();
    }
    Dimension paintWidth;
    if (HasPaintWidth()) {
        paintWidth = GetPaintWidth();
    } else {
        paintWidth = appTheme->GetFocusWidthVp();
    }
    renderContext->ClearFocusState();
    renderContext->PaintFocusState(paintRect, paintColor, paintWidth);
}

void FocusHub::ClearFocusState()
{
    if (focusStyleType_ != FocusStyleType::NONE) {
        auto frameNode = GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->ClearFocusState();
    }
}

void FocusHub::ClearAllFocusState()
{
    ClearFocusState();
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode) {
        lastFocusNode->ClearAllFocusState();
    }
}

bool FocusHub::AcceptFocusOfLastFocus()
{
    if (focusType_ == FocusType::SCOPE) {
        auto lastFocusNode = lastWeakFocusNode_.Upgrade();
        return lastFocusNode ? lastFocusNode->AcceptFocusOfLastFocus() : false;
    }
    if (focusType_ == FocusType::NODE) {
        return IsFocusable();
    }
    return false;
}

bool FocusHub::AcceptFocusByRectOfLastFocus(const RectF& rect)
{
    if (focusType_ == FocusType::NODE) {
        return AcceptFocusByRectOfLastFocusNode(rect);
    }
    if (focusType_ == FocusType::SCOPE) {
        SetScopeFocusAlgorithm();
        if (focusAlgorithm_.scopeType == ScopeType::FLEX) {
            return AcceptFocusByRectOfLastFocusFlex(rect);
        }
        return AcceptFocusByRectOfLastFocusScope(rect);
    }
    return false;
}

bool FocusHub::AcceptFocusByRectOfLastFocusNode(const RectF& rect)
{
    return IsFocusable();
}

bool FocusHub::AcceptFocusByRectOfLastFocusScope(const RectF& rect)
{
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itLastFocusNode = FlushChildrenFocusHub(focusNodes);
    if (focusNodes.empty()) {
        return false;
    }
    auto itFocusNode = itLastFocusNode;
    do {
        if (itLastFocusNode == focusNodes.end()) {
            itLastFocusNode = focusNodes.begin();
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode));
            if (itLastFocusNode == itFocusNode) {
                break;
            }
        }
        RectF childRect;
        if (!CalculateRect(*itLastFocusNode, childRect)) {
            continue;
        }

        if ((*itLastFocusNode)->AcceptFocusByRectOfLastFocus(rect - childRect.GetOffset())) {
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode));
            return true;
        }
    } while ((++itLastFocusNode) != itFocusNode);
    if (itLastFocusNode == focusNodes.end()) {
        lastWeakFocusNode_ = nullptr;
    } else {
        lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode));
    }

    return false;
}

bool FocusHub::AcceptFocusByRectOfLastFocusFlex(const RectF& rect)
{
    if (!rect.IsValid()) {
        LOGE("the rect is not valid");
        return false;
    }

    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    OffsetF offset;
    auto itNewFocusNode = focusNodes.end();
    double minVal = std::numeric_limits<double>::max();
    for (auto it = focusNodes.begin(); it != focusNodes.end(); ++it) {
        if (!(*it)->IsFocusable()) {
            continue;
        }

        RectF childRect;
        if (!CalculateRect(*it, childRect)) {
            continue;
        }

        OffsetF vec = childRect.Center() - rect.Center();
        double val = (vec.GetX() * vec.GetX()) + (vec.GetY() * vec.GetY());
        if (minVal > val) {
            minVal = val;
            itNewFocusNode = it;
            offset = childRect.GetOffset();
        }
    }

    if (itNewFocusNode != focusNodes.end() && (*itNewFocusNode)->AcceptFocusByRectOfLastFocus(rect - offset)) {
        lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itNewFocusNode));
        return true;
    }
    return false;
}

bool FocusHub::CalculateRect(const RefPtr<FocusHub>& childNode, RectF& rect) const
{
    auto childGeometryNode = childNode->GetGeometryNode();
    CHECK_NULL_RETURN(childGeometryNode, false);
    rect = childGeometryNode->GetFrameRect();
    return true;
}

bool FocusHub::IsFocusableByTab()
{
    if (focusType_ == FocusType::NODE) {
        return IsFocusableNodeByTab();
    }
    if (focusType_ == FocusType::SCOPE) {
        return IsFocusableScopeByTab();
    }
    LOGE("Current node focus type: %{public}d is invalid.", focusType_);
    return false;
}

bool FocusHub::IsFocusableNodeByTab()
{
    auto parent = GetParentFocusHub();
    CHECK_NULL_RETURN_NOLOG(parent, GetTabIndex() == 0);
    return (GetTabIndex() == 0) && (parent->GetTabIndex() == 0);
}

bool FocusHub::IsFocusableScopeByTab()
{
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    if (!IsFocusableNodeByTab()) {
        return false;
    }
    if (focusNodes.empty()) {
        return true;
    }
    return std::any_of(focusNodes.begin(), focusNodes.end(),
        [](const RefPtr<FocusHub>& focusNode) { return focusNode->IsFocusableByTab(); });
}

bool FocusHub::IsFocusableWholePath()
{
    auto parent = GetParentFocusHub();
    while (parent) {
        if (!parent->IsFocusable()) {
            return false;
        }
        parent = parent->GetParentFocusHub();
    }
    return IsFocusable();
}

void FocusHub::CollectTabIndexNodes(TabIndexNodeList& tabIndexNodes)
{
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    if (GetFocusType() == FocusType::SCOPE && IsFocusable()) {
        if (focusNodes.size() == 1 && focusNodes.front()->GetFocusType() != FocusType::SCOPE) {
            if (GetTabIndex() > 0) {
                tabIndexNodes.emplace_back(GetTabIndex(), WeakClaim(this));
            }
            return;
        }
        for (auto& child : focusNodes) {
            child->CollectTabIndexNodes(tabIndexNodes);
        }
    }
    if (IsFocusable() && GetTabIndex() > 0) {
        tabIndexNodes.emplace_back(GetTabIndex(), WeakClaim(this));
    }
}

bool FocusHub::GoToFocusByTabNodeIdx(TabIndexNodeList& tabIndexNodes, int32_t tabNodeIdx)
{
    auto iter = tabIndexNodes.begin();
    std::advance(iter, tabNodeIdx);
    if (iter == tabIndexNodes.end()) {
        LOGE("Tab index node is not found");
        return false;
    }
    auto nodeNeedToFocus = (*iter).second.Upgrade();
    if (!nodeNeedToFocus) {
        LOGE("Tab index node is null");
        return false;
    }
    LOGI("Focus on tab index node(%{public}d)", tabNodeIdx);
    if (nodeNeedToFocus->GetFocusType() == FocusType::SCOPE && !nodeNeedToFocus->IsDefaultGroupHasFocused()) {
        auto defaultFocusNode = nodeNeedToFocus->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT);
        if (defaultFocusNode) {
            if (!defaultFocusNode->IsFocusableWholePath()) {
                LOGW("node(%{public}d) is not focusable", tabNodeIdx);
                return false;
            }
            nodeNeedToFocus->SetIsDefaultGroupHasFocused(true);
            return defaultFocusNode->RequestFocusImmediately();
        }
    }
    if (!nodeNeedToFocus->IsFocusableWholePath()) {
        LOGW("node(%{public}d) is not focusable", tabNodeIdx);
        return false;
    }
    return nodeNeedToFocus->RequestFocusImmediately();
}

RefPtr<FocusHub> FocusHub::GetChildFocusNodeByType(FocusNodeType nodeType)
{
    if (nodeType == FocusNodeType::DEFAULT && IsDefaultFocus() && IsFocusable()) {
        return AceType::Claim(this);
    }
    if (nodeType == FocusNodeType::GROUP_DEFAULT && IsDefaultGroupFocus() && IsFocusable()) {
        return AceType::Claim(this);
    }
    if (focusType_ != FocusType::SCOPE) {
        return nullptr;
    }
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    for (const auto& child : focusNodes) {
        auto findNode = child->GetChildFocusNodeByType(nodeType);
        if (findNode) {
            return findNode;
        }
    }
    return nullptr;
}

RefPtr<FocusHub> FocusHub::GetChildFocusNodeById(const std::string& id)
{
    if (id.empty()) {
        return nullptr;
    }
    if (GetInspectorKey().has_value() && GetInspectorKey().value() == id) {
        return AceType::Claim(this);
    }
    if (focusType_ == FocusType::SCOPE) {
        std::list<RefPtr<FocusHub>> focusNodes;
        FlushChildrenFocusHub(focusNodes);
        for (const auto& child : focusNodes) {
            auto findNode = child->GetChildFocusNodeById(id);
            if (findNode) {
                return findNode;
            }
        }
    }
    return nullptr;
}

bool FocusHub::RequestFocusImmediatelyById(const std::string& id)
{
    auto focusNode = GetChildFocusNodeById(id);
    CHECK_NULL_RETURN(focusNode, false);
    if (!focusNode->IsFocusableWholePath()) {
        return false;
    }
    return focusNode->RequestFocusImmediately();
}

int32_t FocusHub::GetFocusingTabNodeIdx(TabIndexNodeList& tabIndexNodes)
{
    if (tabIndexNodes.empty()) {
        LOGD("No tabIndex node exist in this page.");
        return NONE_TAB_FOCUSED_INDEX;
    }
    if (isFirstFocusInPage_) {
        isFirstFocusInPage_ = false;
        return DEFAULT_TAB_FOCUSED_INDEX;
    }
    int32_t res = NONE_TAB_FOCUSED_INDEX;
    int32_t i = 0;
    for (auto& wpNode : tabIndexNodes) {
        auto node = wpNode.second.Upgrade();
        if (node && node->IsCurrentFocus()) {
            res = i;
            break;
        }
        ++i;
    }
    return res;
}

bool FocusHub::HandleFocusByTabIndex(const KeyEvent& event, const RefPtr<FocusHub>& mainFocusHub)
{
    if (event.code != KeyCode::KEY_TAB || event.action != KeyAction::DOWN) {
        return false;
    }
    CHECK_NULL_RETURN(mainFocusHub, false);
    TabIndexNodeList tabIndexNodes;
    tabIndexNodes.clear();
    mainFocusHub->CollectTabIndexNodes(tabIndexNodes);
    tabIndexNodes.sort([](std::pair<int32_t, WeakPtr<FocusHub>>& a, std::pair<int32_t, WeakPtr<FocusHub>>& b) {
        return a.first < b.first;
    });
    int32_t curTabFocusIndex = mainFocusHub->GetFocusingTabNodeIdx(tabIndexNodes);
    if ((curTabFocusIndex < 0 || curTabFocusIndex >= static_cast<int32_t>(tabIndexNodes.size())) &&
        curTabFocusIndex != DEFAULT_TAB_FOCUSED_INDEX) {
        LOGI("Current focused tabIndex node: %{public}d. Use default focus system.", curTabFocusIndex);
        return false;
    }
    if (curTabFocusIndex == DEFAULT_TAB_FOCUSED_INDEX) {
        curTabFocusIndex = 0;
    } else {
        if (event.IsShiftWith(KeyCode::KEY_TAB)) {
            LOGI("RequestNextFocus by 'SHIFT-TAB'");
            --curTabFocusIndex;
        } else {
            LOGI("RequestNextFocus by 'TAB'");
            ++curTabFocusIndex;
        }
    }
    if (curTabFocusIndex < 0 || curTabFocusIndex >= static_cast<int32_t>(tabIndexNodes.size())) {
        LOGI("Focus from tab index node to normal node. Use default focus system.");
        return false;
    }
    return GoToFocusByTabNodeIdx(tabIndexNodes, curTabFocusIndex);
}
} // namespace OHOS::Ace::NG
