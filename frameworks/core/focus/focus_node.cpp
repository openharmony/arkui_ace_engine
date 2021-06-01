/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/focus/focus_node.h"

#include <atomic>

#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "core/common/ace_application_info.h"
#include "core/components/flex/flex_element.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline/base/render_element.h"

namespace OHOS::Ace {
namespace {

inline RefPtr<RenderNode> GetRenderNode(const RefPtr<FocusNode>& node)
{
    auto element = AceType::DynamicCast<RenderElement>(node);
    if (!element) {
        auto composedElement = AceType::DynamicCast<ComposedElement>(node);
        if (composedElement) {
            auto child = composedElement->GetChildren().front();
            return child ? child->GetRenderNode() : nullptr;
        }
        return nullptr;
    }
    return element->GetRenderNode();
}

} // namespace

int32_t FocusNode::GenerateFocusIndex()
{
    static std::atomic<int32_t> counter { 1 };
    return counter.fetch_add(1, std::memory_order_relaxed);
}

bool FocusNode::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (!IsCurrentFocus()) {
        return false;
    }

    if (OnKeyEvent(keyEvent)) {
        return true;
    }

    if (keyEvent.action != KeyAction::CLICK) {
        return false;
    }

    switch (keyEvent.code) {
        case KeyCode::KEYBOARD_ENTER:
        case KeyCode::KEYBOARD_NUMBER_ENTER:
        case KeyCode::KEYBOARD_CENTER:
            OnClick();
            return true;

        default:
            return false;
    }
}

void FocusNode::DumpFocus() {}

void FocusNode::DumpFocusTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpFocus();
        std::string information = AceType::TypeName(this);
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

bool FocusNode::RequestFocusImmediately()
{
    if (IsCurrentFocus()) {
        return true;
    }

    if (!IsFocusable()) {
        return false;
    }

    currentFocus_ = true;
    UpdateAccessibilityFocusInfo();
    auto parent = GetParent().Upgrade();
    if (parent) {
        parent->SwitchFocus(AceType::Claim(this));
    }

    HandleFocus();
    return true;
}

void FocusNode::UpdateAccessibilityFocusInfo()
{
    auto renderNode = GetRenderNode(AceType::Claim(this));
    if (!renderNode) {
        LOGW("FocusNode renderNode is null.");
        return;
    }
    auto accessibilityNode = renderNode->GetAccessibilityNode().Upgrade();
    if (!accessibilityNode) {
        return;
    }
    accessibilityNode->SetFocusedState(currentFocus_);
}

void FocusNode::LostFocus()
{
    if (IsCurrentFocus()) {
        currentFocus_ = false;
        UpdateAccessibilityFocusInfo();
        OnBlur();
    }
}

void FocusNode::LostSelfFocus()
{
    if (IsCurrentFocus()) {
        SetFocusable(false);
        SetFocusable(true);
    }
}

void FocusNode::RemoveSelf()
{
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->RemoveChild(AceType::Claim(this));
    }
}

void FocusNode::SetFocusable(bool focusable)
{
    if (focusable_ == focusable) {
        return;
    }
    focusable_ = focusable;
    RefreshParentFocusable(FocusNode::IsFocusable());
    RefreshFocus();
}

void FocusNode::SetShow(bool show)
{
    show_ = show;
    if (!show) {
        RefreshFocus();
    }
}

void FocusNode::RefreshFocus()
{
    if (!IsCurrentFocus()) {
        return;
    }

    // lost current focus and request another focus
    auto parent = GetParent().Upgrade();

    // current node is root node
    if (!parent) {
        LostFocus();
        return;
    }
    while (!parent->IsFocusable()) {
        // parent node is root node
        if (!parent->GetParent().Upgrade()) {
            parent->LostFocus();
            return;
        }
        parent = parent->GetParent().Upgrade();
    }
    parent->LostFocus();
    parent->RequestFocusImmediately();
}

void FocusNode::RefreshParentFocusable(bool focusable)
{
    // do nothing
}

void FocusNode::RequestFocus()
{
    if (IsCurrentFocus()) {
        return;
    }

    auto element = AceType::DynamicCast<Element>(this);
    if (!element) {
        return;
    }
    auto context = element->GetContext().Upgrade();
    if (context) {
        context->AddDirtyFocus(AceType::Claim(this));
    } else {
        LOGE("fail to add dirty focus due to context is null");
    }
}

void FocusGroup::AddChild(const RefPtr<FocusNode>& focusNode)
{
    // Already belong to any focus scope.
    if (!focusNode || !focusNode->GetParent().Invalid()) {
        return;
    }

    auto it = std::find(focusNodes_.begin(), focusNodes_.end(), focusNode);
    if (it == focusNodes_.end()) {
        focusNodes_.emplace_back(focusNode);
        focusNode->SetParent(AceType::WeakClaim(this));
    }
}

void FocusGroup::AddChild(const RefPtr<FocusNode>& focusNode, const RefPtr<FocusNode>& nextFocusNode)
{
    // Already belong to any focus scope.
    if (!focusNode || !focusNode->GetParent().Invalid()) {
        return;
    }

    auto it = std::find(focusNodes_.begin(), focusNodes_.end(), focusNode);
    auto pos = std::find(focusNodes_.begin(), focusNodes_.end(), nextFocusNode);
    if (it == focusNodes_.end()) {
        focusNodes_.insert(pos, focusNode);
        focusNode->SetParent(AceType::WeakClaim(this));
    }
}

void FocusGroup::DumpFocusTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpFocus();
        std::string information = AceType::TypeName(this);
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

void FocusGroup::RemoveChild(const RefPtr<FocusNode>& focusNode)
{
    // Not belong to this focus scope.
    if (!focusNode || focusNode->GetParent() != this) {
        return;
    }

    if (focusNode->IsCurrentFocus()) {
        // Try to goto next focus, otherwise goto previous focus.
        if (!GoToNextFocus(true) && !GoToNextFocus(false)) {
            itLastFocusNode_ = focusNodes_.end();
        }
        focusNode->LostFocus();
    } else {
        if (itLastFocusNode_ != focusNodes_.end() && (*itLastFocusNode_) == focusNode) {
            itLastFocusNode_ = focusNodes_.end();
        }
    }

    auto it = std::find(focusNodes_.begin(), focusNodes_.end(), focusNode);
    if (it == focusNodes_.end()) {
        return;
    }
    focusNodes_.erase(it);
    focusNode->SetParent(nullptr);
}

void FocusGroup::SwitchFocus(const RefPtr<FocusNode>& focusNode)
{
    auto it = std::find(focusNodes_.begin(), focusNodes_.end(), focusNode);
    ACE_DCHECK(it != focusNodes_.end());

    auto itFocusNode = itLastFocusNode_;
    itLastFocusNode_ = it;

    if (IsCurrentFocus()) {
        if (itFocusNode != focusNodes_.end() && itFocusNode != it) {
            (*itFocusNode)->LostFocus();
        }
    } else {
        RequestFocusImmediately();
    }
}

bool FocusGroup::IsFocusable() const
{
    if (!FocusNode::IsFocusable()) {
        return false;
    }
    return std::any_of(focusNodes_.begin(), focusNodes_.end(),
        [](const RefPtr<FocusNode>& focusNode) { return focusNode->IsFocusable(); });
}

bool FocusGroup::GoToNextFocus(bool reverse, const Rect& rect)
{
    if (focusNodes_.empty()) {
        return false;
    }
    auto itNewFocusNode = itLastFocusNode_;

    if (reverse) {
        while (itNewFocusNode != focusNodes_.begin()) {
            --itNewFocusNode;
            if (TryRequestFocus(*itNewFocusNode, rect)) {
                return true;
            }
        }
    } else {
        if (itNewFocusNode == focusNodes_.end()) {
            itNewFocusNode = focusNodes_.begin();
        } else {
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

bool FocusGroup::OnKeyEvent(const KeyEvent& keyEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    if (itLastFocusNode_ != focusNodes_.end() && (*itLastFocusNode_)->HandleKeyEvent(keyEvent)) {
        return true;
    }

    if (FocusNode::OnKeyEvent(keyEvent)) {
        return true;
    }

    if (keyEvent.action != KeyAction::UP) {
        return false;
    }

    if (!CalculatePosition()) {
        return false;
    }

    LOGD("Position information: X: %{public}lf Y: %{public}lf W: %{public}lf H: %{public}lf", GetRect().Left(),
        GetRect().Top(), GetRect().Width(), GetRect().Height());

    switch (keyEvent.code) {
        case KeyCode::TV_CONTROL_UP:
            return RequestNextFocus(true, true, GetRect());
        case KeyCode::TV_CONTROL_DOWN:
            return RequestNextFocus(true, false, GetRect());
        case KeyCode::TV_CONTROL_LEFT:
            return RequestNextFocus(false, !AceApplicationInfo::GetInstance().IsRightToLeft(), GetRect());
        case KeyCode::TV_CONTROL_RIGHT:
            return RequestNextFocus(false, AceApplicationInfo::GetInstance().IsRightToLeft(), GetRect());
        case KeyCode::KEYBOARD_TAB:
            return RequestNextFocus(false, false, GetRect()) || RequestNextFocus(true, false, GetRect());
        default:
            return false;
    }
}

bool FocusGroup::CalculatePosition()
{
    if (itLastFocusNode_ == focusNodes_.end()) {
        return false;
    }

    Rect childRect;
    if (!CalculateRect(*itLastFocusNode_, childRect)) {
        return false;
    }

    if ((*itLastFocusNode_)->IsChild()) {
        auto renderNode = GetRenderNode(*itLastFocusNode_);
        if (!renderNode) {
            return false;
        }

        Rect rect(childRect.GetOffset(), renderNode->GetLayoutSize());
        (*itLastFocusNode_)->SetRect(rect);
        SetRect(rect);
    } else {
        SetRect((*itLastFocusNode_)->GetRect() + childRect.GetOffset());
    }

    return true;
}

void FocusGroup::OnFocus()
{
    if (focusNodes_.empty()) {
        return;
    }

    auto itFocusNode = itLastFocusNode_;
    do {
        if (itLastFocusNode_ == focusNodes_.end()) {
            itLastFocusNode_ = focusNodes_.begin();
        }
        if ((*itLastFocusNode_)->RequestFocusImmediately()) {
            FocusNode::OnFocus();
            return;
        }
    } while ((++itLastFocusNode_) != itFocusNode);

    // Not found any focusable node, clear focus.
    itLastFocusNode_ = focusNodes_.end();
}

void FocusGroup::OnBlur()
{
    FocusNode::OnBlur();

    if (itLastFocusNode_ != focusNodes_.end()) {
        (*itLastFocusNode_)->LostFocus();
    }
}

void FocusGroup::SetShow(bool show)
{
    FocusNode::SetShow(show);
    RefreshParentFocusable(FocusNode::IsFocusable());
}

bool FocusGroup::TryRequestFocus(const RefPtr<FocusNode>& focusNode, const Rect& rect)
{
    if (rect.IsValid()) {
        Rect childRect;
        if (!CalculateRect(focusNode, childRect) ||
            !focusNode->AcceptFocusByRectOfLastFocus(rect - childRect.GetOffset())) {
            return false;
        }
    }
    return focusNode->RequestFocusImmediately();
}

bool FocusGroup::AcceptFocusByRectOfLastFocus(const Rect& rect)
{
    if (focusNodes_.empty()) {
        return false;
    }

    auto itFocusNode = itLastFocusNode_;
    do {
        if (itLastFocusNode_ == focusNodes_.end()) {
            itLastFocusNode_ = focusNodes_.begin();
            if (itLastFocusNode_ == itFocusNode) {
                break;
            }
        }
        Rect childRect;
        if (!CalculateRect(*itLastFocusNode_, childRect)) {
            continue;
        }

        if ((*itLastFocusNode_)->AcceptFocusByRectOfLastFocus(rect - childRect.GetOffset())) {
            return true;
        }
    } while ((++itLastFocusNode_) != itFocusNode);

    return false;
}

bool FocusGroup::CalculateRect(const RefPtr<FocusNode>& node, Rect& rect)
{
    auto renderNode = GetRenderNode(AceType::Claim(this));
    if (!renderNode) {
        return false;
    }
    Offset nowOffset = renderNode->GetOffsetFromOrigin(Offset());

    renderNode = GetRenderNode(node);
    if (!renderNode) {
        return false;
    }
    Offset childOffset = renderNode->GetOffsetFromOrigin(Offset());
    rect.SetRect(childOffset - nowOffset, renderNode->GetLayoutSize());
    return true;
}

void FocusGroup::RefreshParentFocusable(bool focusable)
{
    for (auto& item : focusNodes_) {
        if (focusable != item->IsParentFocusable()) {
            item->SetParentFocusable(focusable);
            item->RefreshParentFocusable(item->FocusNode::IsFocusable());
        }
    }
}

void FocusGroup::RebuildChild(std::list<RefPtr<FocusNode>>&& rebuildFocusNodes)
{
    if (rebuildFocusNodes.empty() || rebuildFocusNodes.size() > focusNodes_.size()) {
        return;
    }

    focusNodes_ = std::move(rebuildFocusNodes);
    itLastFocusNode_ = focusNodes_.end();
    if (!IsCurrentFocus()) {
        return;
    }

    auto it = focusNodes_.begin();
    while (it != focusNodes_.end()) {
        if ((*it)->IsCurrentFocus()) {
            itLastFocusNode_ = it;
            return;
        }
        ++it;
    }

    LostFocus();
    itLastFocusNode_ = focusNodes_.end();
    RequestFocusImmediately();
}

} // namespace OHOS::Ace
