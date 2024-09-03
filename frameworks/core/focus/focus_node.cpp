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

#include "core/focus/focus_node.h"

#include "base/log/dump_log.h"
#include "core/components/flex/flex_element.h"
#include "core/pipeline/base/composed_element.h"

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

    auto element = AceType::DynamicCast<Element>(this);
    if (!element) {
        return false;
    }
    auto context = element->GetContext().Upgrade();
    if (!context) {
        return false;
    }

    switch (keyEvent.code) {
        case KeyCode::KEY_ENTER:
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_DPAD_CENTER:
            if (keyEvent.action != KeyAction::DOWN) {
                return false;
            }
            if (context->GetIsDeclarative()) {
                return OnClick(keyEvent);
            }
            OnClick();
            return true;

        default:
            return false;
    }
}

void FocusNode::CollectTabIndexNodes(TabIndexNodeList& tabIndexNodes)
{
    RefPtr<FocusNode> node = AceType::Claim(this);
    CHECK_NULL_VOID(node);
    RefPtr<FocusGroup> scope = AceType::DynamicCast<FocusGroup>(node);
    if (scope && scope->IsFocusable()) {
        auto children = scope->GetChildrenList();
        if (children.size() == 1 && !AceType::DynamicCast<FocusGroup>(children.front())) {
            if (scope->GetTabIndex() > 0) {
                tabIndexNodes.emplace_back(scope->GetTabIndex(), WeakClaim(AceType::RawPtr(scope)));
            }
            return;
        }
        for (auto& child : children) {
            child->CollectTabIndexNodes(tabIndexNodes);
        }
    }
    if (node->IsFocusable() && node->GetTabIndex() > 0) {
        tabIndexNodes.emplace_back(node->GetTabIndex(), WeakClaim(AceType::RawPtr(node)));
    }
}

bool FocusNode::GoToFocusByTabNodeIdx(TabIndexNodeList& tabIndexNodes, int32_t tabNodeIdx)
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
    auto scopeNeedToFocus = AceType::DynamicCast<FocusGroup>(nodeNeedToFocus);
    if (scopeNeedToFocus && !scopeNeedToFocus->IsGroupDefaultFocused()) {
        auto defaultFocusNode = nodeNeedToFocus->GetChildDefaultFocusNode(false);
        if (defaultFocusNode) {
            if (!defaultFocusNode->IsFocusableWholePath()) {
                LOGW("node(%{public}d) is not focusable", tabNodeIdx);
                return false;
            }
            scopeNeedToFocus->SetIsGroupDefaultFocused(true);
            return defaultFocusNode->RequestFocusImmediately();
        }
    }
    if (!nodeNeedToFocus->IsFocusableWholePath()) {
        LOGW("node(%{public}d) is not focusable", tabNodeIdx);
        return false;
    }
    return nodeNeedToFocus->RequestFocusImmediately();
}

bool FocusNode::HandleFocusByTabIndex(const KeyEvent& event, const RefPtr<FocusGroup>& mainNode)
{
    if (event.code != KeyCode::KEY_TAB || event.action != KeyAction::DOWN) {
        return false;
    }
    if (!mainNode) {
        LOGE("Current page node is not exit. Can't handle focus by tabIndex.");
        return false;
    }
    TabIndexNodeList tabIndexNodes;
    tabIndexNodes.clear();
    mainNode->CollectTabIndexNodes(tabIndexNodes);
    tabIndexNodes.sort([](std::pair<int32_t, WeakPtr<FocusNode>>& a, std::pair<int32_t, WeakPtr<FocusNode>>& b) {
        return a.first < b.first;
    });
    int32_t curTabFocusIndex = mainNode->GetFocusingTabNodeIdx(tabIndexNodes);
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

bool FocusNode::IsFocusableByTab() const
{
    auto parent = GetParent().Upgrade();
    if (parent) {
        return (tabIndex_ == 0) && (parent->tabIndex_ == 0);
    }
    return tabIndex_ == 0;
}

bool FocusNode::IsFocusableWholePath() const
{
    auto parent = GetParent().Upgrade();
    while (parent) {
        if (!parent->IsFocusable()) {
            return false;
        }
        parent = parent->GetParent().Upgrade();
    }
    return IsFocusable();
}

bool FocusNode::RequestFocusImmediately()
{
    auto renderNode = GetRenderNode(AceType::Claim(this));
    if (renderNode) {
        auto context = renderNode->GetContext().Upgrade();
        if (context && context->IsJsCard()) {
            return false;
        }
        if (context && context->GetIsFocusingByTab()) {
            if (!IsFocusableByTab()) {
                return false;
            }
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
    auto parent = GetParent().Upgrade();
    if (parent) {
        parent->SwitchFocus(AceType::Claim(this));
    }

    HandleFocus();
    return true;
}

RefPtr<FocusNode> FocusNode::GetChildDefaultFocusNode(bool isGetDefaultFocus)
{
    if (isGetDefaultFocus && isDefaultFocus_ && IsFocusable()) {
        return AceType::Claim(this);
    }
    if (!isGetDefaultFocus && isDefaultGroupFocus_ && IsFocusable()) {
        return AceType::Claim(this);
    }
    RefPtr<FocusGroup> scope = AceType::DynamicCast<FocusGroup>(AceType::Claim(this));
    if (!scope) {
        return nullptr;
    }
    auto children = scope->GetChildrenList();
    for (const auto& child : children) {
        auto findNode = child->GetChildDefaultFocusNode(isGetDefaultFocus);
        if (findNode) {
            return findNode;
        }
    }
    return nullptr;
}

RefPtr<FocusNode> FocusNode::GetChildFocusNodeById(const std::string& id)
{
    if (id.empty()) {
        return nullptr;
    }
    if (GetInspectorKey() == id) {
        return AceType::Claim(this);
    }
    RefPtr<FocusGroup> scope = AceType::DynamicCast<FocusGroup>(AceType::Claim(this));
    if (scope) {
        auto children = scope->GetChildrenList();
        for (const auto& child : children) {
            auto findNode = child->GetChildFocusNodeById(id);
            if (findNode) {
                return findNode;
            }
        }
    }
    return nullptr;
}

bool FocusNode::RequestFocusImmediatelyById(const std::string& id)
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

void FocusNode::LostFocus(BlurReason reason)
{
    if (IsCurrentFocus()) {
        blurReason_ = reason;
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

void FocusNode::SetEnabled(bool enabled)
{
    enabled_ = enabled;
    if (!enabled) {
        RefreshFocus();
    }
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

bool FocusNode::OnKeyEvent(const KeyEvent& keyEvent)
{
    auto element = AceType::DynamicCast<Element>(this);
    if (!element) {
        return false;
    }
    auto context = element->GetContext().Upgrade();
    if (!context) {
        return false;
    }
    if (context->GetIsDeclarative()) {
        auto info = std::make_shared<KeyEventInfo>(keyEvent);
        if (!onKeyEventCallback_) {
            return false;
        }
        onKeyEventCallback_(info);
        return info->IsStopPropagation();
    } else {
        if (onKeyCallback_) {
            return onKeyCallback_(keyEvent);
        }
    }
    return false;
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

bool FocusNode::OnClick(const KeyEvent& event)
{
    if (onClickEventCallback_) {
        auto info = std::make_shared<ClickInfo>(-1);
        info->SetTimeStamp(event.timeStamp);
        info->SetGlobalLocation(
            Offset((GetRect().Left() + GetRect().Right()) / 2, (GetRect().Top() + GetRect().Bottom()) / 2));
        info->SetLocalLocation(
            Offset((GetRect().Right() - GetRect().Left()) / 2, (GetRect().Bottom() - GetRect().Top()) / 2));
        info->SetSourceDevice(static_cast<SourceType>(event.sourceType));
        info->SetDeviceId(event.deviceId);
        onClickEventCallback_(info);
        return true;
    }
    return false;
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
    if (itLastFocusNode_ == it) {
        itLastFocusNode_ = focusNodes_.end();
    }
    focusNode->SetParent(nullptr);
    focusNodes_.erase(it);
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

bool FocusGroup::IsFocusableByTab() const
{
    if (!FocusNode::IsFocusableByTab()) {
        return false;
    }
    if (focusNodes_.empty()) {
        return true;
    }
    return std::any_of(focusNodes_.begin(), focusNodes_.end(),
        [](const RefPtr<FocusNode>& focusNode) { return focusNode->IsFocusableByTab(); });
}

bool FocusGroup::GoToNextFocus(bool reverse, const Rect& rect)
{
    if (focusNodes_.empty()) {
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
        } else {
            --itNewFocusNode;
        }
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

bool FocusGroup::OnKeyEvent(const KeyEvent& keyEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    if (itLastFocusNode_ != focusNodes_.end() && (*itLastFocusNode_)->HandleKeyEvent(keyEvent)) {
        return true;
    }

    if (FocusNode::OnKeyEvent(keyEvent)) {
        return true;
    }

    if (keyEvent.action != KeyAction::DOWN) {
        return false;
    }

    if (!CalculatePosition()) {
        return false;
    }

    OnFocusMove(keyEvent.code);
    switch (keyEvent.code) {
        case KeyCode::TV_CONTROL_UP:
            LOGI("RequestNextFocus 'UP' by KeyCode(%{public}d)", keyEvent.code);
            return RequestNextFocus(true, true, GetRect());
        case KeyCode::TV_CONTROL_DOWN:
            LOGI("RequestNextFocus 'DOWN' by KeyCode(%{public}d)", keyEvent.code);
            return RequestNextFocus(true, false, GetRect());
        case KeyCode::TV_CONTROL_LEFT:
            LOGI("RequestNextFocus 'LEFT' by KeyCode(%{public}d)", keyEvent.code);
            return RequestNextFocus(false, !AceApplicationInfo::GetInstance().IsRightToLeft(), GetRect());
        case KeyCode::TV_CONTROL_RIGHT:
            LOGI("RequestNextFocus 'RIGHT' by KeyCode(%{public}d)", keyEvent.code);
            return RequestNextFocus(false, AceApplicationInfo::GetInstance().IsRightToLeft(), GetRect());
        case KeyCode::KEY_TAB: {
            auto element = AceType::DynamicCast<Element>(this);
            if (!element) {
                return false;
            }
            auto context = element->GetContext().Upgrade();
            if (!context) {
                return false;
            }
            bool ret = false;
            if (keyEvent.pressedCodes.size() == 1) {
                LOGI("RequestNextFocus 'TAB' by KeyCode(%{public}d)", keyEvent.code);
                context->SetIsFocusingByTab(true);
                ret = RequestNextFocus(false, false, GetRect()) || RequestNextFocus(true, false, GetRect());
                context->SetIsFocusingByTab(false);
            } else {
                LOGI("RequestNextFocus 'SHIFT-TAB' by KeyCode(%{public}d)", keyEvent.code);
                if (keyEvent.IsKey({ KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB }) ||
                    keyEvent.IsKey({ KeyCode::KEY_SHIFT_RIGHT, KeyCode::KEY_TAB })) {
                    context->SetIsFocusingByTab(true);
                    ret = RequestNextFocus(false, true, GetRect()) || RequestNextFocus(true, true, GetRect());
                    context->SetIsFocusingByTab(false);
                }
            }
            return ret;
        }
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
            if (itLastFocusNode_ == itFocusNode) {
                break;
            }
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

    if (itLastFocusNode_ != focusNodes_.end() && *itLastFocusNode_) {
        (*itLastFocusNode_)->LostFocus(blurReason_);
    }
}

void FocusGroup::SetShow(bool show)
{
    FocusNode::SetShow(show);
    RefreshParentFocusable(FocusNode::IsFocusable());
}

void FocusGroup::SetEnabled(bool enabled)
{
    FocusNode::SetEnabled(enabled);
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
    if (rebuildFocusNodes.empty()) {
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

int32_t FocusGroup::GetFocusingTabNodeIdx(TabIndexNodeList& tabIndexNodes)
{
    if (tabIndexNodes.empty()) {
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

} // namespace OHOS::Ace
