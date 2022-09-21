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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/log/dump_log.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/event/ace_event_handler.h"
#include "core/gestures/click_recognizer.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

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
        focusNodes_.emplace_back(child->GetFocusHub());
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
    if (OnKeyEvent(keyEvent)) {
        return true;
    }

    auto context = NG::PipelineContext::GetCurrentContext();

    switch (keyEvent.code) {
        case KeyCode::KEY_ENTER:
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_DPAD_CENTER:
            if (keyEvent.action != KeyAction::DOWN) {
                return false;
            }
            OnClick(keyEvent);
            return true;
        default:
            return false;
    }
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
        std::string information = GetFrameNode()->GetTag();
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
        std::string information = GetFrameNode()->GetTag();
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
    LOGI("Node: %{public}s request focus immediately", GetFrameName().c_str());
    auto context = NG::PipelineContext::GetCurrentContext();

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

void FocusHub::UpdateAccessibilityFocusInfo() {}

void FocusHub::LostFocus()
{
    if (IsCurrentFocus()) {
        currentFocus_ = false;
        UpdateAccessibilityFocusInfo();
        OnBlur();
    }
}

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
        [](const RefPtr<FocusHub>& focusNode) { return focusNode->IsFocusableNode(); });
}

bool FocusHub::IsFocusableNode()
{
    return focusable_ && parentFocusable_;
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
    if (handleKeyEvent_ && handleKeyEvent_(keyEvent)) {
        return true;
    }
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
    auto info = KeyEventInfo(keyEvent);
    if (!onKeyEventCallback_) {
        return false;
    }
    onKeyEventCallback_(info);
    return info.IsStopPropagation();
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
                ret = RequestNextFocus(false, false, GetRect()) || RequestNextFocus(true, false, GetRect());
            } else if (keyEvent.IsShiftWith(KeyCode::KEY_TAB)) {
                LOGI("Node: %{public}s request next focus by Key-'SHIFT-TAB'", GetFrameName().c_str());
                ret = RequestNextFocus(false, true, GetRect()) || RequestNextFocus(true, true, GetRect());
            }
            return ret;
        }
        default:
            return false;
    }
}

bool FocusHub::RequestNextFocus(bool vertical, bool reverse, const RectF& rect)
{
    return GoToNextFocus(reverse, rect);
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

void FocusHub::OnClick(const KeyEvent& event) {}

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

bool FocusHub::GoToNextFocus(bool reverse, const RectF& rect)
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
        auto lastFocusGeometryNode = GetGeometryNode();
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
    if (onFocusCallback_) {
        onFocusCallback_();
    }
}
void FocusHub::OnBlurNode()
{
    LOGI("FocusHub: Node(%{public}s) on blur", GetFrameName().c_str());
    if (onBlurInternal_) {
        onBlurInternal_();
    }
    if (onBlurCallback_) {
        onBlurCallback_();
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
        return IsFocusable();
    }

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
} // namespace OHOS::Ace::NG
