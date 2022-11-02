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
#include "core/common/ace_application_info.h"
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
    if (frameNode) {
        return frameNode->GetInspectorId();
    }
    return std::nullopt;
}

RefPtr<FocusHub> FocusHub::GetParentFocusHub() const
{
    auto frameNode = GetFrameNode();
    if (frameNode) {
        auto parentNode = frameNode->GetFocusParent();
        return parentNode ? parentNode->GetFocusHub() : nullptr;
    }
    return nullptr;
}

std::string FocusHub::GetFrameName() const
{
    auto frameNode = GetFrameNode();
    return frameNode ? frameNode->GetTag() : "NULL";
}

void FocusHub::FlushChildrenFocusHub()
{
    std::list<RefPtr<FrameNode>> childrenNode;
    auto frameNode = GetFrameNode();
    if (frameNode) {
        frameNode->GetFocusChildren(childrenNode);
    }
    focusNodes_.clear();
    for (const auto& child : childrenNode) {
        if (child->GetFocusHub()) {
            focusNodes_.emplace_back(child->GetFocusHub());
        }
    }
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (!lastFocusNode) {
        itLastFocusNode_ = focusNodes_.end();
    } else {
        auto it = std::find(focusNodes_.begin(), focusNodes_.end(), lastFocusNode);
        itLastFocusNode_ = it;
    }
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
        // DumpFocus();
        std::string information = GetFrameName();
        if (IsCurrentFocus()) {
            information += "(Node*)";
        } else {
            information += "(Node)";
        }
        if (!IsFocusable()) {
            information = "(-)" + information;
        }
        DumpLog::GetInstance().Print(depth, information, 0);
    }
}

void FocusHub::DumpFocusScopeTree(int32_t depth)
{
    FlushChildrenFocusHub();
    if (DumpLog::GetInstance().GetDumpFile()) {
        // DumpFocus();
        std::string information = GetFrameName();
        if (IsCurrentFocus()) {
            information += "(Scope*)";
        } else {
            information += "(Scope)";
        }
        if (!IsFocusable()) {
            information = "(-)" + information;
        }
        DumpLog::GetInstance().Print(depth, information, focusNodes_.size());
    }

    for (const auto& item : focusNodes_) {
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
    }

    HandleFocus();
    return true;
}

void FocusHub::UpdateAccessibilityFocusInfo()
{
    // Need update
}

void FocusHub::LostFocus()
{
    if (IsCurrentFocus()) {
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
    }
}

void FocusHub::RemoveChild(const RefPtr<FocusHub>& focusNode)
{
    // Not belong to this focus scope.
    if (!focusNode || focusNode->GetParentFocusHub() != this) {
        return;
    }

    FlushChildrenFocusHub();
    if (focusNode->IsCurrentFocus()) {
        // Try to goto next focus, otherwise goto previous focus.
        if (!GoToNextFocusLinear(true) && !GoToNextFocusLinear(false)) {
            itLastFocusNode_ = focusNodes_.end();
            lastWeakFocusNode_ = nullptr;
        }
        focusNode->LostFocus();
    } else {
        if (itLastFocusNode_ != focusNodes_.end() && (*itLastFocusNode_) == focusNode) {
            itLastFocusNode_ = focusNodes_.end();
            lastWeakFocusNode_ = nullptr;
        }
    }

    auto it = std::find(focusNodes_.begin(), focusNodes_.end(), focusNode);
    if (it == focusNodes_.end()) {
        return;
    }
    if (itLastFocusNode_ == it) {
        itLastFocusNode_ = focusNodes_.end();
        lastWeakFocusNode_ = nullptr;
    }
    focusNode->SetFocusType(FocusType::DISABLE);
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
    FlushChildrenFocusHub();
    // TODO: Contaner without child can be focusable
    return std::any_of(focusNodes_.begin(), focusNodes_.end(),
        [](const RefPtr<FocusHub>& focusNode) { return focusNode->IsFocusable(); });
}

bool FocusHub::IsFocusableNode()
{
    return enabled_ && show_ && focusable_ && parentFocusable_;
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
    enabled_ = enabled;
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
    if (focusCallbackEvents_->IsFocusOnTouch() == isFocusOnTouch) {
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
        return false;
    }
    LOGD("FocusHub::OnKeyEvent: Do key callback on %{public}s with key event{ Code(%{public}d), "
         "Action(%{public}d), "
         "SourceType(%{public}d), DeviceId(%{public}" PRId64 ") }. Return: %{public}d",
        GetFrameName().c_str(), info.GetKeyCode(), info.GetKeyType(), info.GetSourceDevice(), info.GetDeviceId(),
        info.IsStopPropagation());
    onKeyEventCallback(info);
    auto retCallback = info.IsStopPropagation();
    return retInternal || retCallback;
}

bool FocusHub::OnKeyEventScope(const KeyEvent& keyEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    FlushChildrenFocusHub();
    if (itLastFocusNode_ != focusNodes_.end() && (*itLastFocusNode_)->HandleKeyEvent(keyEvent)) {
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
            LOGI("Node: %{public}s request next focus by Key-'UP'", GetFrameName().c_str());
            return RequestNextFocus(true, true, GetRect());
        case KeyCode::TV_CONTROL_DOWN:
            LOGI("Node: %{public}s request next focus by Key-'DOWN'", GetFrameName().c_str());
            return RequestNextFocus(true, false, GetRect());
        case KeyCode::TV_CONTROL_LEFT:
            LOGI("Node: %{public}s request next focus by Key-'LEFT'", GetFrameName().c_str());
            return RequestNextFocus(false, !AceApplicationInfo::GetInstance().IsRightToLeft(), GetRect());
        case KeyCode::TV_CONTROL_RIGHT:
            LOGI("Node: %{public}s request next focus by Key-'RIGHT'", GetFrameName().c_str());
            return RequestNextFocus(false, AceApplicationInfo::GetInstance().IsRightToLeft(), GetRect());
        case KeyCode::KEY_TAB: {
            auto context = NG::PipelineContext::GetCurrentContext();
            bool ret = false;
            if (keyEvent.pressedCodes.size() == 1) {
                LOGI("Node: %{public}s request next focus by Key-'TAB'", GetFrameName().c_str());
                context->SetIsFocusingByTab(true);
                ret = RequestNextFocus(false, false, GetRect()) || RequestNextFocus(true, false, GetRect());
                context->SetIsFocusingByTab(false);
            } else if (keyEvent.IsShiftWith(KeyCode::KEY_TAB)) {
                LOGI("Node: %{public}s request next focus by Key-'SHIFT-TAB'", GetFrameName().c_str());
                context->SetIsFocusingByTab(true);
                ret = RequestNextFocus(false, true, GetRect()) || RequestNextFocus(true, true, GetRect());
                context->SetIsFocusingByTab(false);
            }
            return ret;
        }
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

bool FocusHub::RequestNextFocus(bool vertical, bool reverse, const RectF& rect)
{
    if (!focusAlgorithm_.getNextFocusNode) {
        if (focusAlgorithm_.isVertical != vertical) {
            return false;
        }
        return GoToNextFocusLinear(reverse, rect);
    }
    FlushChildrenFocusHub();
    FocusStep step = FocusStep::DOWN;
    if (vertical && !reverse) {
        step = FocusStep::DOWN;
    } else if (vertical && reverse) {
        step = FocusStep::UP;
    } else if (!vertical && !reverse) {
        step = FocusStep::RIGHT;
    } else {
        step = FocusStep::LEFT;
    }
    WeakPtr<FocusHub> nextFocusHubWeak;
    focusAlgorithm_.getNextFocusNode(step, lastWeakFocusNode_, nextFocusHubWeak);
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
    FlushChildrenFocusHub();
    for (auto& item : focusNodes_) {
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
        info.SetGlobalLocation(
            Offset((rect.Left() + rect.Right()) / 2, (rect.Top() + rect.Bottom()) / 2));
        info.SetLocalLocation(
            Offset((rect.Right() - rect.Left()) / 2, (rect.Bottom() - rect.Top()) / 2));
        info.SetSourceDevice(event.sourceType);
        info.SetDeviceId(event.deviceId);
        LOGD("FocusHub::OnClick: Do click callback on %{public}s with key event{ Global(%{public}f,%{public}f), "
             "Local(%{public}f,%{public}f), SourceType(%{public}d), DeviceId(%{public}" PRId64 ") }",
            GetFrameName().c_str(), info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY(),
            info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY(), info.GetSourceDevice(), info.GetDeviceId());
        onClickCallback(info);
    }
}

void FocusHub::SwitchFocus(const RefPtr<FocusHub>& focusNode)
{
    if (focusType_ != FocusType::SCOPE) {
        return;
    }
    FlushChildrenFocusHub();
    auto it = std::find(focusNodes_.begin(), focusNodes_.end(), focusNode);
    ACE_DCHECK(it != focusNodes_.end());

    auto itFocusNode = itLastFocusNode_;
    itLastFocusNode_ = it;
    lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode_));

    if (IsCurrentFocus()) {
        if (itFocusNode != focusNodes_.end() && itFocusNode != it) {
            (*itFocusNode)->LostFocus();
        }
    } else {
        RequestFocusImmediately();
    }
}

bool FocusHub::GoToNextFocusLinear(bool reverse, const RectF& rect)
{
    FlushChildrenFocusHub();
    if (focusNodes_.empty()) {
        LOGW("%{public}s has no next child focus node to go.", GetFrameName().c_str());
        return false;
    }
    auto itNewFocusNode = itLastFocusNode_;
    if (itNewFocusNode == focusNodes_.end()) {
        itNewFocusNode = focusNodes_.begin();
    }
    if (reverse) {
        if (itNewFocusNode == focusNodes_.begin()) {
            itNewFocusNode = focusNodes_.end();
            return false;
        }
        --itNewFocusNode;

        while (itNewFocusNode != focusNodes_.begin()) {
            if (TryRequestFocus(*itNewFocusNode, rect)) {
                return true;
            }
            --itNewFocusNode;
        }
        if (itNewFocusNode == focusNodes_.begin()) {
            if (TryRequestFocus(*itNewFocusNode, rect)) {
                return true;
            }
        }
    } else {
        if (itNewFocusNode != focusNodes_.end()) {
            ++itNewFocusNode;
        }
        while (itNewFocusNode != focusNodes_.end()) {
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
    FlushChildrenFocusHub();
    if (itLastFocusNode_ == focusNodes_.end()) {
        return false;
    }

    RectF childRect;
    if (!CalculateRect(*itLastFocusNode_, childRect)) {
        return false;
    }

    if ((*itLastFocusNode_)->IsChild()) {
        auto lastFocusGeometryNode = (*itLastFocusNode_)->GetGeometryNode();
        CHECK_NULL_RETURN(lastFocusGeometryNode, false);
        RectF rect(childRect.GetOffset(), lastFocusGeometryNode->GetFrameSize());
        (*itLastFocusNode_)->SetRect(rect);
        SetRect(rect);
    } else {
        SetRect((*itLastFocusNode_)->GetRect() + childRect.GetOffset());
    }

    return true;
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
    LOGI("FocusHub: Node(%{public}s) on focus", GetFrameName().c_str());
    if (onFocusInternal_) {
        onFocusInternal_();
    }
    auto onFocusCallback = GetOnFocusCallback();
    if (onFocusCallback) {
        onFocusCallback();
    }
    auto context = PipelineContext::GetCurrentContext();
    if (context && context->GetIsNeedShowFocus() && focusType_ == FocusType::NODE) {
        auto frameNode = GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->BlendBorderColor(Color(0xFF254FF7));
    }
}
void FocusHub::OnBlurNode()
{
    LOGI("FocusHub: Node(%{public}s) on blur", GetFrameName().c_str());
    if (onBlurInternal_) {
        onBlurInternal_();
    }
    auto onBlurCallback = GetOnBlurCallback();
    if (onBlurCallback) {
        onBlurCallback();
    }
    if (focusType_ == FocusType::NODE) {
        auto frameNode = GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->ResetBlendBorderColor();
    }
}

void FocusHub::OnFocusScope()
{
    FlushChildrenFocusHub();
    if (focusNodes_.empty()) {
        return;
    }

    auto itFocusNode = itLastFocusNode_;
    do {
        if (itLastFocusNode_ == focusNodes_.end()) {
            itLastFocusNode_ = focusNodes_.begin();
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode_));
            if (itLastFocusNode_ == itFocusNode) {
                break;
            }
        }
        if ((*itLastFocusNode_)->RequestFocusImmediately()) {
            OnFocusNode();
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode_));
            return;
        }
    } while ((++itLastFocusNode_) != itFocusNode);

    // Not found any focusable node, clear focus.
    itLastFocusNode_ = focusNodes_.end();
    lastWeakFocusNode_ = nullptr;
}

void FocusHub::OnBlurScope()
{
    FlushChildrenFocusHub();
    OnBlurNode();
    if (itLastFocusNode_ != focusNodes_.end() && *itLastFocusNode_) {
        (*itLastFocusNode_)->LostFocus();
    }
}

bool FocusHub::AcceptFocusByRectOfLastFocus(const RectF& rect)
{
    if (focusType_ == FocusType::NODE) {
        return AcceptFocusByRectOfLastFocusNode(rect);
    }
    if (focusType_ == FocusType::SCOPE) {
        if (focusAlgorithm_.scopeType == ScopeType::FLEX) {
            return AcceptFocusByRectOfLastFocusFlex(rect);
        }
        return AcceptFocusByRectOfLastFocusScope(rect);
    }
    return false;
}

bool FocusHub::AcceptFocusByRectOfLastFocusNode(const RectF &rect)
{
    return IsFocusable();
}

bool FocusHub::AcceptFocusByRectOfLastFocusScope(const RectF& rect)
{
    FlushChildrenFocusHub();
    if (focusNodes_.empty()) {
        return false;
    }
    auto itFocusNode = itLastFocusNode_;
    do {
        if (itLastFocusNode_ == focusNodes_.end()) {
            itLastFocusNode_ = focusNodes_.begin();
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode_));
            if (itLastFocusNode_ == itFocusNode) {
                break;
            }
        }
        RectF childRect;
        if (!CalculateRect(*itLastFocusNode_, childRect)) {
            continue;
        }

        if ((*itLastFocusNode_)->AcceptFocusByRectOfLastFocus(rect - childRect.GetOffset())) {
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode_));
            return true;
        }
    } while ((++itLastFocusNode_) != itFocusNode);
    if (itLastFocusNode_ == focusNodes_.end()) {
        lastWeakFocusNode_ = nullptr;
    } else {
        lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode_));
    }

    return false;
}

bool FocusHub::AcceptFocusByRectOfLastFocusFlex(const RectF& rect)
{
    if (!rect.IsValid()) {
        LOGE("the rect is not valid");
        return false;
    }

    FlushChildrenFocusHub();
    OffsetF offset;
    auto itNewFocusNode = focusNodes_.end();
    double minVal = std::numeric_limits<double>::max();
    for (auto it = focusNodes_.begin(); it != focusNodes_.end(); ++it) {
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

    if (itNewFocusNode != focusNodes_.end() && (*itNewFocusNode)->AcceptFocusByRectOfLastFocus(rect - offset)) {
        itLastFocusNode_ = itNewFocusNode;
        lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode_));
        return true;
    }
    return false;
}

bool FocusHub::CalculateRect(const RefPtr<FocusHub>& childNode, RectF& rect) const
{
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);

    auto childGeometryNode = childNode->GetGeometryNode();
    CHECK_NULL_RETURN(childGeometryNode, false);

    rect.SetRect(
        childGeometryNode->GetFrameOffset() - geometryNode->GetFrameOffset(), childGeometryNode->GetFrameSize());
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
    if (parent) {
        return (GetTabIndex() == 0) && (parent->GetTabIndex() == 0);
    }
    return GetTabIndex() == 0;
}

bool FocusHub::IsFocusableScopeByTab()
{
    FlushChildrenFocusHub();
    if (!IsFocusableNodeByTab()) {
        return false;
    }
    if (focusNodes_.empty()) {
        return true;
    }
    return std::any_of(focusNodes_.begin(), focusNodes_.end(),
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
    FlushChildrenFocusHub();
    if (GetFocusType() == FocusType::SCOPE && IsFocusable()) {
        if (focusNodes_.size() == 1 && focusNodes_.front()->GetFocusType() != FocusType::SCOPE) {
            if (GetTabIndex() > 0) {
                tabIndexNodes.emplace_back(GetTabIndex(), WeakClaim(this));
            }
            return;
        }
        for (auto& child : focusNodes_) {
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
    FlushChildrenFocusHub();
    for (const auto& child : focusNodes_) {
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
        FlushChildrenFocusHub();
        for (const auto& child : focusNodes_) {
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
    if (!focusNode) {
        LOGW("Can not find focus node by id: %{public}s", id.c_str());
        return false;
    }
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

bool FocusHub::HandleFocusByTabIndex(const KeyEvent& event, const RefPtr<FocusHub>& curPage)
{
    if (event.code != KeyCode::KEY_TAB || event.action != KeyAction::DOWN) {
        return false;
    }
    if (!curPage) {
        LOGE("Current page node is not exit. Can't handle focus by tabIndex.");
        return false;
    }
    TabIndexNodeList tabIndexNodes;
    tabIndexNodes.clear();
    curPage->CollectTabIndexNodes(tabIndexNodes);
    tabIndexNodes.sort([](std::pair<int32_t, WeakPtr<FocusHub>>& a, std::pair<int32_t, WeakPtr<FocusHub>>& b) {
        return a.first < b.first;
    });
    int32_t curTabFocusIndex = curPage->GetFocusingTabNodeIdx(tabIndexNodes);
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
