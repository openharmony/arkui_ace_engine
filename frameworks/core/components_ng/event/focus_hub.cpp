/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif

#ifndef ACE_UNITTEST
#ifdef ENABLE_STANDARD_INPUT
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif
#endif

namespace OHOS::Ace::NG {
constexpr uint32_t DELAY_TIME_FOR_RESET_UEC = 50;
Dimension FOCUS_SCROLL_MARGIN = 5.0_vp;
namespace {
float GetMoveOffset(const RefPtr<FrameNode>& parentFrameNode, const RefPtr<FrameNode>& curFrameNode, bool isVertical)
{
    constexpr float notMove = 0.0f;
    auto parentGeometryNode = parentFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(parentGeometryNode, notMove);
    auto parentFrameSize = parentGeometryNode->GetFrameSize();
    auto curFrameOffsetToWindow = curFrameNode->GetTransformRelativeOffset();
    auto parentFrameOffsetToWindow = parentFrameNode->GetTransformRelativeOffset();
    auto offsetToTarFrame = curFrameOffsetToWindow - parentFrameOffsetToWindow;
    auto curGeometry = curFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(curGeometry, notMove);
    auto curFrameSize = curGeometry->GetFrameSize();
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "Node: %{public}s/%{public}d - %{public}s-%{public}s on focus. Offset to target node: "
        "%{public}s/%{public}d - %{public}s-%{public}s is (%{public}f,%{public}f).",
        curFrameNode->GetTag().c_str(), curFrameNode->GetId(), curFrameOffsetToWindow.ToString().c_str(),
        curFrameSize.ToString().c_str(), parentFrameNode->GetTag().c_str(), parentFrameNode->GetId(),
        parentFrameOffsetToWindow.ToString().c_str(), parentFrameSize.ToString().c_str(), offsetToTarFrame.GetX(),
        offsetToTarFrame.GetY());

    float diffToTarFrame = isVertical ? offsetToTarFrame.GetY() : offsetToTarFrame.GetX();
    if (NearZero(diffToTarFrame)) {
        return notMove;
    }
    float curFrameLength = isVertical ? curFrameSize.Height() : curFrameSize.Width();
    float parentFrameLength = isVertical ? parentFrameSize.Height() : parentFrameSize.Width();
    float focusMargin = FOCUS_SCROLL_MARGIN.ConvertToPx();

    bool totallyShow = LessOrEqual(curFrameLength + focusMargin + focusMargin, (parentFrameLength));
    float startAlignOffset = -diffToTarFrame + focusMargin;
    float endAlignOffset = parentFrameLength - diffToTarFrame - curFrameLength - focusMargin;
    bool start2End = LessOrEqual(diffToTarFrame, focusMargin);
    bool needScroll = !NearZero(startAlignOffset, 1.0f) && !NearZero(endAlignOffset, 1.0f) &&
                      (std::signbit(startAlignOffset) == std::signbit(endAlignOffset));
    if (needScroll) {
        return (totallyShow ^ start2End) ? endAlignOffset : startAlignOffset;
    }
    return notMove;
}

template <bool isReverse>
bool AnyOfUINode(const RefPtr<UINode>& node, const std::function<bool(const RefPtr<FocusHub>&)>& operation)
{
    const auto& children = node->GetChildren(true);
    using IterType = std::conditional_t<isReverse, decltype(children.crbegin()), decltype(children.cbegin())>;
    IterType begin, end;
    if constexpr (isReverse) {
        begin = children.crbegin();
        end = children.crend();
    } else {
        begin = children.cbegin();
        end = children.cend();
    }
    for (auto iter = begin; iter != end; ++iter) {
        const auto& uiChild = *iter;
        if (uiChild && !uiChild->IsOnMainTree()) {
            continue;
        }
        auto frameChild = AceType::DynamicCast<FrameNode>(uiChild);
        if (frameChild && frameChild->GetFocusType() != FocusType::DISABLE) {
            const auto focusHub = frameChild->GetFocusHub();
            if (focusHub && operation(focusHub)) {
                return true;
            }
        } else if (AnyOfUINode<isReverse>(uiChild, operation)) {
            return true;
        }
    }
    return false;
}
}

RefPtr<FocusManager> FocusHub::GetFocusManager() const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    return focusManager;
}

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
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    return frameNode->GetInspectorId();
}

RefPtr<FocusHub> FocusHub::GetParentFocusHub() const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto parentNode = frameNode->GetFocusParent();
    return parentNode ? parentNode->GetFocusHub() : nullptr;
}

RefPtr<FocusHub> FocusHub::GetParentFocusHubWithBoundary() const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto parentNode = frameNode->GetFocusParentWithBoundary();
    return parentNode ? parentNode->GetFocusHub() : nullptr;
}

RefPtr<FocusHub> FocusHub::GetRootFocusHub()
{
    RefPtr<FocusHub> parent = AceType::Claim(this);
    while (parent->GetParentFocusHub()) {
        parent = parent->GetParentFocusHub();
    }
    return parent;
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

template <bool isReverse>
bool FocusHub::AnyChildFocusHub(const std::function<bool(const RefPtr<FocusHub>&)>& operation)
{
    RefPtr<UINode> node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    return AnyOfUINode<isReverse>(node, operation);
}

template <bool isReverse>
void FocusHub::AllChildFocusHub(const std::function<void(const RefPtr<FocusHub>&)>& operation)
{
    AnyChildFocusHub<isReverse>([&operation](const RefPtr<FocusHub>& focusHub) {
        operation(focusHub);
        return false;
    });
}
template void FocusHub::AllChildFocusHub<true>(const std::function<void(const RefPtr<FocusHub>&)>&);
template void FocusHub::AllChildFocusHub<false>(const std::function<void(const RefPtr<FocusHub>&)>&);

bool FocusHub::SkipFocusMoveBeforeRemove()
{
    return ((GetFrameName() == V2::MENU_WRAPPER_ETS_TAG) ||
        (GetFrameName() == V2::SHEET_WRAPPER_TAG));
}

std::list<RefPtr<FocusHub>>::iterator FocusHub::FlushChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes)
{
    focusNodes.clear();
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    decltype(focusNodes.begin()) lastIter;
    bool hasLastFocus = false;
    AllChildFocusHub([&focusNodes, &lastIter, &hasLastFocus, lastFocusNode](const RefPtr<FocusHub>& child) {
        auto iter = focusNodes.emplace(focusNodes.end(), child);
        if (child && lastFocusNode == child) {
            lastIter = iter;
            hasLastFocus = true;
        }
        return false;
    });
    return hasLastFocus ? lastIter : focusNodes.end();
}

bool FocusHub::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (!IsCurrentFocus()) {
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "node: %{public}s/%{public}d cannot handle key event because is not current focus",
            GetFrameName().c_str(), GetFrameId());
        return false;
    }
    bool shiftTabPressed = keyEvent.IsShiftWith(KeyCode::KEY_TAB);
    bool leftArrowPressed = keyEvent.code == KeyCode::KEY_DPAD_LEFT;
    hasBackwardMovement_ = keyEvent.action == KeyAction::DOWN && (shiftTabPressed || leftArrowPressed);

    bool tabOnlyPressed = (keyEvent.code == KeyCode::KEY_TAB) && (!shiftTabPressed);
    bool rightArrowPressed = keyEvent.code == KeyCode::KEY_DPAD_RIGHT;
    hasForwardMovement_ = keyEvent.action == KeyAction::DOWN && (tabOnlyPressed || rightArrowPressed);

    return OnKeyEvent(keyEvent);
}

void FocusHub::DumpFocusTree(int32_t depth, bool hasJson)
{
    if (focusType_ == FocusType::NODE) {
        if (hasJson) {
            DumpFocusNodeTreeInJson(depth);
        } else {
            DumpFocusNodeTree(depth);
        }
    } else if (focusType_ == FocusType::SCOPE) {
        if (hasJson) {
            DumpFocusScopeTreeInJson(depth);
        } else {
            DumpFocusScopeTree(depth);
        }
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
        information += (GetInspectorKey().has_value() ? " idstr:" + GetInspectorKey().value() : "");
        if (!IsFocusable()) {
            information = "(-)" + information;
            information += IsEnabled() ? "" : " Enabled:false";
            information += IsShow() ? "" : " Show:false";
            information += focusable_ ? "" : " Focusable:false";
            information += parentFocusable_ ? "" : " ParentFocusable:false";
        }
        information += IsDefaultFocus() ? "[Default]" : "";
        if (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PRIOR)) {
            information += (" prior-focus-in-" + focusScopeId_);
        }
        if (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PREVIOUS)) {
            information += (" previous-focus-in-" + focusScopeId_);
        }
        auto focusMgr = GetFocusManager();
        if (focusMgr && focusMgr->GetLastFocusStateNode() == this) {
            information += " [Painted]";
        }
        DumpFocusUie();
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
        information += (GetInspectorKey().has_value() ? " idstr:" + GetInspectorKey().value() : "");
        if (!IsFocusable()) {
            information = "(-)" + information;
            information += IsEnabled() ? "" : " Enabled:false";
            information += IsShow() ? "" : " Show:false";
            information += focusable_ ? "" : " Focusable:false";
            information += parentFocusable_ ? "" : " ParentFocusable:false";
        }
        information += IsDefaultFocus() ? "[Default]" : "";
        if (isFocusScope_ && !focusScopeId_.empty()) {
            information += GetIsFocusGroup() ? " GroupId:" : " ScopeId:";
            information += focusScopeId_;
            information += arrowKeyStepOut_ ? "" : " ArrowKeyStepOut:false";
        }
        bool isPrior = (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PRIOR));
        if (isPrior) {
            information += (" prior-focus-in-" + focusScopeId_);
        }
        bool isPrevious = (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PREVIOUS));
        if (isPrevious) {
            information += (" previous-focus-in-" + focusScopeId_);
        }
        auto focusMgr = GetFocusManager();
        if (focusMgr && focusMgr->GetLastFocusStateNode() == this) {
            information += " [Painted]";
        }
        DumpLog::GetInstance().Print(depth, information, static_cast<int32_t>(focusNodes.size()));
    }

    DumpFocusUie();
    for (const auto& item : focusNodes) {
        item->DumpFocusTree(depth + 1);
    }
}

void FocusHub::DumpFocusUie()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    if (pattern && frameNode->GetTag() == V2::UI_EXTENSION_COMPONENT_TAG) {
        pattern->DumpInfo();
    }
}

bool FocusHub::RequestFocusImmediately(bool isJudgeRootTree)
{
    TAG_LOGI(AceLogTag::ACE_FOCUS, "node %{public}s/%{public}d RequestFocusImmediately",
        GetFrameName().c_str(), GetFrameId());
    return RequestFocusImmediatelyInner(isJudgeRootTree);
}

bool FocusHub::RequestFocusImmediatelyInner(bool isJudgeRootTree)
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, false);
    auto focusManager = context->GetOrCreateFocusManager();
    CHECK_NULL_RETURN(focusManager, false);
    if (context && context->GetIsFocusingByTab()) {
        if (!IsFocusableByTab()) {
            focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_FOCUSABLE_BY_TAB);
            return false;
        }
    }

    if (IsCurrentFocus()) {
        return true;
    }

    if (!IsFocusableWholePath()) {
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_FOCUSABLE_ANCESTOR);
        return false;
    }

    if (isJudgeRootTree && !IsOnRootTree()) {
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_EXIST);
        return false;
    }

    currentFocus_ = true;

    if (onPreFocusCallback_) {
        onPreFocusCallback_();
    }
    FocusManager::FocusGuard guard(focusManager->GetCurrentFocus(), SwitchingStartReason::REQUEST_FOCUS);
    auto parent = GetParentFocusHub();
    if (parent) {
        if (focusManager) {
            auto weakFocusViewList = focusManager->GetWeakFocusViewList();
            for (const auto& weakFocusView : weakFocusViewList) {
                auto focusView = weakFocusView.Upgrade();
                auto viewRootScope = focusView ? focusView->GetViewRootScope() : nullptr;
                if (parent == viewRootScope) {
                    focusView->SetIsViewRootScopeFocused(false);
                    break;
                }
            }
        }
        parent->SwitchFocus(AceType::Claim(this));
    }

    HandleFocus();
    return true;
}

bool FocusHub::IsViewRootScope()
{
    auto focusManager = GetFocusManager();
    CHECK_NULL_RETURN(focusManager, false);
    auto lastFocusView = focusManager->GetLastFocusView().Upgrade();
    return (lastFocusView && lastFocusView->GetViewRootScope() == this);
}

void FocusHub::LostFocusToViewRoot()
{
    auto curFocusView = FocusView::GetCurrentFocusView();
    CHECK_NULL_VOID(curFocusView);
    auto viewRootScope = curFocusView->GetViewRootScope();
    CHECK_NULL_VOID(viewRootScope);
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Lost focus to view root: %{public}s",
        viewRootScope->GetFrameName().c_str());
    if (!viewRootScope->IsCurrentFocus()) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "View root: %{public}s is not on focusing.",
            viewRootScope->GetFrameName().c_str());
        return;
    }
    curFocusView->SetIsViewRootScopeFocused(true);
    auto focusedChild = viewRootScope->lastWeakFocusNode_.Upgrade();
    CHECK_NULL_VOID(focusedChild);
    FocusManager::FocusGuard guard(viewRootScope, SwitchingStartReason::LOST_FOCUS_TO_VIEW_ROOT);
    focusedChild->LostFocus(BlurReason::CLEAR_FOCUS);
}

void FocusHub::LostFocus(BlurReason reason)
{
    TAG_LOGD(AceLogTag::ACE_FOCUS, "Node %{public}s/%{public}d lost focus. Lost reason: %{public}d.",
        GetFrameName().c_str(), GetFrameId(), reason);
    if (IsCurrentFocus()) {
        blurReason_ = reason;
        currentFocus_ = false;
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

void FocusHub::RemoveSelf(BlurReason reason)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "%{public}s/%{public}d remove self focus.",
            GetFrameName().c_str(), GetFrameId());
    }
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto focusView = frameNode->GetPattern<FocusView>();
    auto* pipeline = frameNode->GetContext();
    auto screenNode = pipeline ? pipeline->GetScreenNode() : nullptr;
    auto screenFocusHub = screenNode ? screenNode->GetFocusHub() : nullptr;
    auto parent = GetParentFocusHub();
    if (parent && parent != screenFocusHub && !focusView) {
        parent->RemoveChild(AceType::Claim(this), reason);
    } else if (IsCurrentFocus()) {
        FocusManager::FocusGuard guard(parent, SwitchingStartReason::REMOVE_SELF);
        LostFocus(reason);
    }
    if (!focusScopeId_.empty()) {
        RemoveFocusScopeIdAndPriority();
    }
}

void FocusHub::RemoveChild(const RefPtr<FocusHub>& focusNode, BlurReason reason)
{
    // Not belong to this focus scope.
    if (!focusNode || focusNode->GetParentFocusHub() != this) {
        return;
    }

    if (focusNode->IsCurrentFocus()) {
        FocusManager::FocusGuard guard(Claim(this), SwitchingStartReason::REMOVE_CHILD);
        // Try to goto next focus, otherwise goto previous focus.
        if (!focusNode->SkipFocusMoveBeforeRemove() && !GoToNextFocusLinear(FocusStep::TAB) &&
            !GoToNextFocusLinear(FocusStep::SHIFT_TAB)) {
            lastWeakFocusNode_ = nullptr;
            auto focusView = FocusView::GetCurrentFocusView();
            auto mainViewRootScope = focusView ? focusView->GetViewRootScope() : nullptr;
            if (mainViewRootScope && mainViewRootScope == AceType::Claim(this)) {
                TAG_LOGI(AceLogTag::ACE_FOCUS,
                    "Focus will stop at root scope %{public}s/%{public}d of focus view %{public}s/%{public}d",
                    GetFrameName().c_str(), GetFrameId(), focusView->GetFrameName().c_str(), focusView->GetFrameId());
                focusView->SetIsViewRootScopeFocused(true);
            } else {
                RemoveSelf(reason);
            }
        }
        focusNode->LostFocus(reason);
    }
    if (lastWeakFocusNode_ == focusNode) {
        lastWeakFocusNode_ = nullptr;
    }
}

// Need update RebuildChild function

void FocusHub::SetParentFocusable(bool parentFocusable)
{
    parentFocusable_ = parentFocusable;
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
    if (focusDepend_ == FocusDependence::SELF || focusDepend_ == FocusDependence::AUTO) {
        return true;
    }
    
    return AnyChildFocusHub([](const RefPtr<FocusHub>& focusHub) { return focusHub->IsFocusable(); });
}

bool FocusHub::IsFocusableNode()
{
    return IsEnabled() && IsShow() && focusable_ && parentFocusable_;
}

void FocusHub::SetFocusable(bool focusable, bool isExplicit)
{
    if (isExplicit) {
        isFocusableExplicit_ = true;
    } else if (isFocusableExplicit_) {
        return;
    } else {
        implicitFocusable_ = focusable;
    }
    if (IsImplicitFocusableScope() && focusDepend_ == FocusDependence::CHILD) {
        focusDepend_ = FocusDependence::AUTO;
    }

    if (focusable_ == focusable) {
        return;
    }
    focusable_ = focusable;
    if (!focusable) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_FOCUS, "Set node %{public}s/%{public}d to be unfocusable", GetFrameName().c_str(),
                GetFrameId());
        }
        RemoveSelf(BlurReason::FOCUS_SWITCH);
    }
}

bool FocusHub::IsSyncRequestFocusable()
{
    if (focusType_ == FocusType::NODE) {
        return IsSyncRequestFocusableNode();
    }
    if (focusType_ == FocusType::SCOPE) {
        return IsSyncRequestFocusableScope();
    }
    return false;
}

bool FocusHub::IsSyncRequestFocusableScope()
{
    if (!IsSyncRequestFocusableNode()) {
        return false;
    }
    if (focusDepend_ == FocusDependence::SELF || focusDepend_ == FocusDependence::AUTO) {
        return true;
    }
    return AnyChildFocusHub([](const RefPtr<FocusHub>& focusNode) { return focusNode->IsFocusable(); });
}

bool FocusHub::IsSyncRequestFocusableNode()
{
    auto focusManager = GetFocusManager();
    CHECK_NULL_RETURN(focusManager, false);
    if (!IsEnabled() || !IsShow()) {
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_EXIST);
        return false;
    }
    if (!focusable_) {
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_FOCUSABLE);
        return false;
    }
    if (!parentFocusable_) {
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_FOCUSABLE_ANCESTOR);
        return false;
    }
    return true;
}

bool FocusHub::IsEnabled() const
{
    auto eventHub = eventHub_.Upgrade();
    return eventHub ? eventHub->IsEnabled() : true;
}

void FocusHub::SetEnabled(bool enabled)
{
    if (!enabled) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_FOCUS, "Set node %{public}s/%{public}d to be disabled", GetFrameName().c_str(),
                GetFrameId());
        }
        RemoveSelf(BlurReason::FOCUS_SWITCH);
    }
}

bool FocusHub::IsShow() const
{
    bool curIsVisible = true;
    for (RefPtr<UINode> node = GetFrameNode(); curIsVisible && node; node = node->GetParent()) {
        auto frameNode = AceType::DynamicCast<FrameNode>(node);
        if (frameNode && !frameNode->IsVisible()) {
            curIsVisible = false;
        }
    }
    return curIsVisible;
}

void FocusHub::SetShow(bool show)
{
    if (!show) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_FOCUS, "Set node %{public}s/%{public}d to be unShown", GetFrameName().c_str(),
                GetFrameId());
        }
        RemoveSelf(BlurReason::FOCUS_SWITCH);
    }
}

bool FocusHub::IsCurrentFocusWholePath()
{
    if (!currentFocus_) {
        return false;
    }
    if (focusType_ == FocusType::NODE) {
        return true;
    }
    if (focusType_ == FocusType::SCOPE) {
        if (focusDepend_ == FocusDependence::SELF || focusDepend_ == FocusDependence::AUTO) {
            return true;
        }
        std::list<RefPtr<FocusHub>> focusNodes;
        auto itLastFocusNode = FlushChildrenFocusHub(focusNodes);
        if (itLastFocusNode == focusNodes.end() || !(*itLastFocusNode)) {
            return false;
        }
        return (*itLastFocusNode)->IsCurrentFocusWholePath();
    }
    return false;
}

bool FocusHub::HasFocusedChild()
{
    if (!currentFocus_ || focusType_ != FocusType::SCOPE) {
        return false;
    }
    return AnyChildFocusHub([](const RefPtr<FocusHub>& node) { return node && node->IsCurrentFocus(); });
}

void FocusHub::SetIsFocusOnTouch(bool isFocusOnTouch)
{
    if (!focusCallbackEvents_) {
        focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();
    }
    if (focusCallbackEvents_->isFocusOnTouch_.has_value() &&
        focusCallbackEvents_->isFocusOnTouch_.value() == isFocusOnTouch) {
        return;
    }
    focusCallbackEvents_->isFocusOnTouch_ = isFocusOnTouch;

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
                TAG_LOGI(AceLogTag::ACE_FOCUS, "node %{public}s/%{public}d touch to be focused",
                    focusHub->GetFrameName().c_str(), focusHub->GetFrameId());
                focusHub->RequestFocusImmediatelyInner();
            }
        };
        focusOnTouchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    }
    gesture->AddTouchEvent(focusOnTouchListener_);
}

bool FocusHub::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (focusType_ == FocusType::SCOPE) {
        return OnKeyEventScope(keyEvent);
    }
    if (focusType_ == FocusType::NODE) {
        return OnKeyEventNode(keyEvent);
    }
    TAG_LOGW(AceLogTag::ACE_FOCUS, "Current node focus type: %{public}d is invalid.", focusType_);
    return false;
}

bool FocusHub::OnKeyPreIme(KeyEventInfo& info, const KeyEvent& keyEvent)
{
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "node: %{public}s/%{public}d try to handle OnKeyPreIme by "
        "code:%{private}d/action:%{public}d/isPreIme:%{public}d",
        GetFrameName().c_str(), GetFrameId(), keyEvent.code, keyEvent.action, keyEvent.isPreIme);
    auto onKeyPreIme = GetOnKeyPreIme();
    if (onKeyPreIme) {
        bool retPreIme = onKeyPreIme(info);
        auto pipeline = PipelineContext::GetCurrentContext();
        auto eventManager = pipeline->GetEventManager();
        if (eventManager) {
            eventManager->SetIsKeyConsumed(retPreIme);
        }
        TAG_LOGI(AceLogTag::ACE_FOCUS, "node: %{public}s/%{public}d handle OnKeyPreIme",
            GetFrameName().c_str(), GetFrameId());
        return info.IsStopPropagation();
    } else if (GetFrameName() == V2::UI_EXTENSION_COMPONENT_ETS_TAG ||
               GetFrameName() == V2::EMBEDDED_COMPONENT_ETS_TAG) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "node: %{public}s/%{public}d try to process OnKeyEventInternal",
            GetFrameName().c_str(), GetFrameId());
        return ProcessOnKeyEventInternal(keyEvent);
    } else {
        return false;
    }
}

void FocusHub::PrintOnKeyEventUserInfo(const KeyEvent& keyEvent, bool retCallback)
{
    TAG_LOGI(AceLogTag::ACE_FOCUS,
        "OnKeyEventUser: Node %{public}s/%{public}d handle KeyEvent(%{private}d, %{public}d) return: %{public}d",
        GetFrameName().c_str(), GetFrameId(), keyEvent.code, keyEvent.action, retCallback);
}

bool FocusHub::OnKeyEventNode(const KeyEvent& keyEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    // ReDispatch keyEvent will NOT be consumed again.
    if (keyEvent.isRedispatch) {
        return false;
    }

    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto info = KeyEventInfo(keyEvent);
    if (pipeline->IsKeyInPressed(KeyCode::KEY_META_LEFT) ||
        pipeline->IsKeyInPressed(KeyCode::KEY_META_RIGHT)) {
        info.SetMetaKey(1);
    }
    if (keyEvent.isPreIme) {
        return OnKeyPreIme(info, keyEvent);
    }

    bool retInternal = OnKeyEventNodeInternal(keyEvent);
    bool retCallback = OnKeyEventNodeUser(info, keyEvent);
    if (!retInternal && !retCallback && keyEvent.action == KeyAction::DOWN) {
        auto ret = false;
        switch (keyEvent.code) {
            case KeyCode::KEY_SPACE:
            case KeyCode::KEY_ENTER:
            case KeyCode::KEY_NUMPAD_ENTER:
                ret = OnClick(keyEvent);
                TAG_LOGI(AceLogTag::ACE_FOCUS,
                    "OnClick: Node %{public}s/%{public}d handle KeyEvent(%{private}d, %{public}d) return: %{public}d",
                    GetFrameName().c_str(), GetFrameId(), keyEvent.code, keyEvent.action, ret);
                break;
            default:;
        }
        return ret;
    }
    return retInternal || retCallback;
}

bool FocusHub::OnKeyEventNodeInternal(const KeyEvent& keyEvent)
{
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    bool isBypassInner = keyEvent.IsKey({ KeyCode::KEY_TAB }) && pipeline && pipeline->IsTabJustTriggerOnKeyEvent();
    auto retInternal = false;
    if ((GetFrameName() == V2::UI_EXTENSION_COMPONENT_ETS_TAG || GetFrameName() == V2::EMBEDDED_COMPONENT_ETS_TAG ||
        GetFrameName() == V2::ISOLATED_COMPONENT_ETS_TAG)
        && (!IsCurrentFocus() || forceProcessOnKeyEventInternal_)) {
        isBypassInner = false;
        forceProcessOnKeyEventInternal_ = false;
    }
    if (!isBypassInner && !onKeyEventsInternal_.empty()) {
        retInternal = ProcessOnKeyEventInternal(keyEvent);
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "OnKeyEventInteral: Node %{public}s/%{public}d handle KeyEvent(%{private}d, %{public}d) "
            "return: %{public}d",
            GetFrameName().c_str(), GetFrameId(), keyEvent.code, keyEvent.action, retInternal);
    }
    return retInternal;
}

bool FocusHub::OnKeyEventNodeUser(KeyEventInfo& info, const KeyEvent& keyEvent)
{
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto retCallback = false;
    auto onKeyEventCallback = GetOnKeyCallback();
    if (onKeyEventCallback) {
        onKeyEventCallback(info);
        retCallback = info.IsStopPropagation();
        auto eventManager = pipeline->GetEventManager();
        PrintOnKeyEventUserInfo(keyEvent, retCallback);
    }

    auto onJSFrameNodeKeyCallback = GetOnJSFrameNodeKeyCallback();
    if (onJSFrameNodeKeyCallback) {
        onJSFrameNodeKeyCallback(info);
        retCallback = info.IsStopPropagation();
        PrintOnKeyEventUserInfo(keyEvent, retCallback);
    }
    return retCallback;
}

bool FocusHub::OnKeyEventScope(const KeyEvent& keyEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    std::list<RefPtr<FocusHub>> focusNodes;
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode && lastFocusNode->HandleKeyEvent(keyEvent)) {
        TAG_LOGD(AceLogTag::ACE_FOCUS,
            "OnKeyEvent: Node %{public}s/%{public}d will not handle KeyEvent(code:%{private}d, action:%{public}d). "
            "Because its child %{public}s/%{public}d already has consumed this event.",
            GetFrameName().c_str(), GetFrameId(), keyEvent.code, keyEvent.action, lastFocusNode->GetFrameName().c_str(),
            lastFocusNode->GetFrameId());
        return true;
    }

    if (OnKeyEventNode(keyEvent)) {
        return true;
    }

    if (keyEvent.isPreIme || keyEvent.action != KeyAction::DOWN) {
        return false;
    }

    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (!pipeline->GetIsFocusActive()) {
        return false;
    }
    if (keyEvent.IsKey({ KeyCode::KEY_TAB }) && IsInFocusGroup()) {
        return false;
    }
    if (keyEvent.IsKey({ KeyCode::KEY_TAB }) && pipeline->IsTabJustTriggerOnKeyEvent()) {
        ScrollToLastFocusIndex();
        return false;
    }

    if (!CalculatePosition()) {
        return false;
    }

    return RequestNextFocusByKey(keyEvent);
}

bool FocusHub::RequestNextFocusByKey(const KeyEvent& keyEvent)
{
    switch (keyEvent.code) {
        case KeyCode::TV_CONTROL_UP:
            return RequestNextFocus(FocusStep::UP, GetRect());
        case KeyCode::TV_CONTROL_DOWN:
            return RequestNextFocus(FocusStep::DOWN, GetRect());
        case KeyCode::TV_CONTROL_LEFT:
            return RequestNextFocus(FocusStep::LEFT, GetRect());
        case KeyCode::TV_CONTROL_RIGHT:
            return RequestNextFocus(FocusStep::RIGHT, GetRect());
        case KeyCode::KEY_TAB:
            return RequestNextFocusOfKeyTab(keyEvent);
        case KeyCode::KEY_MOVE_HOME:
            return RequestNextFocus(FocusStep::LEFT_END, GetRect()) || RequestNextFocus(FocusStep::UP_END, GetRect());
        case KeyCode::KEY_MOVE_END:
            return RequestNextFocus(FocusStep::RIGHT_END, GetRect()) ||
                   RequestNextFocus(FocusStep::DOWN_END, GetRect());
        default:
            return false;
    }
}

bool FocusHub::RequestNextFocusOfKeyTab(const KeyEvent& keyEvent)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto* context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto curFocusView = FocusView::GetCurrentFocusView();
    auto entryFocusView = curFocusView ? curFocusView->GetEntryFocusView() : nullptr;
    auto entryFocusViewHub = entryFocusView ? entryFocusView->GetFocusHub() : nullptr;
    auto focusParent = GetParentFocusHub();
    bool isCurrentHandledByFocusView =
        (entryFocusViewHub && entryFocusViewHub == this) || !focusParent || !focusParent->IsCurrentFocus();
    bool ret = false;
    if (keyEvent.pressedCodes.size() == 1) {
        context->SetIsFocusingByTab(true);
        ret = RequestNextFocus(FocusStep::TAB, GetRect());
        if (!ret && isCurrentHandledByFocusView) {
            auto container = Container::GetContainer(context->GetInstanceId());
            auto isDynamicRender = container == nullptr ? false : container->IsDynamicRender();
            bool isFocusWindowIdSetted = context->IsFocusWindowIdSetted();
            if (isFocusWindowIdSetted) {
                // Delay focus transfer to avoid focusbox twinkling when USC lost focus.
                // UEC should inherit common FocusHub to handle such case in the future.
                auto taskExecutor = context->GetTaskExecutor();
                CHECK_NULL_RETURN(taskExecutor, false);
                auto instanceId = context->GetInstanceId();
                taskExecutor->PostDelayedTask(
                    [weak = WeakClaim(this), instanceId] {
                        ContainerScope scope(instanceId);
                        auto focusHub = weak.Upgrade();
                        CHECK_NULL_VOID(focusHub);
                        focusHub->HandleLastFocusNodeInFocusWindow();
                    }, TaskExecutor::TaskType::UI,
                    DELAY_TIME_FOR_RESET_UEC, "FocusToHeadOrTailChildInUEC");
                return false;
            } else if (isDynamicRender) {
                FocusToHeadOrTailChild(true);
                return false;
            }
            ret = FocusToHeadOrTailChild(true);
        }
        context->SetIsFocusingByTab(false);
    } else if (keyEvent.IsShiftWith(KeyCode::KEY_TAB)) {
        context->SetIsFocusingByTab(true);
        ret = RequestNextFocus(FocusStep::SHIFT_TAB, GetRect());
        if (!ret && isCurrentHandledByFocusView) {
            auto container = Container::GetContainer(context->GetInstanceId());
            auto isDynamicRender = container == nullptr ? false : container->IsDynamicRender();
            if (context->IsFocusWindowIdSetted() || isDynamicRender) {
                FocusToHeadOrTailChild(false);
                return false;
            }
            ret = FocusToHeadOrTailChild(false);
        }
        context->SetIsFocusingByTab(false);
    }
    return ret;
}

void FocusHub::HandleLastFocusNodeInFocusWindow()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto* context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    FocusToHeadOrTailChild(true);
    if (!context->IsWindowFocused()) {
        LostFocus(BlurReason::WINDOW_BLUR);
    }
}

void FocusHub::RequestFocus() const
{
    if (IsCurrentFocus()) {
        return;
    }
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (!frameNode->IsOnMainTree()) {
        TAG_LOGW(AceLogTag::ACE_FOCUS,
            "Can't find Node %{public}s/%{public}d on tree, please check the timing of the function call.",
            frameNode->GetTag().c_str(), frameNode->GetId());
    }
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Node: %{public}s/%{public}d RequestFocus.", GetFrameName().c_str(), GetFrameId());
    context->AddDirtyFocus(GetFrameNode());
}

bool FocusHub::RequestNextFocus(FocusStep moveStep, const RectF& rect)
{
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Request next focus on node: %{public}s/%{public}d by step: %{public}d.",
        GetFrameName().c_str(), GetFrameId(), moveStep);
    SetScopeFocusAlgorithm();
    if (!focusAlgorithm_.getNextFocusNode) {
        return RequestNextFocusByDefaultAlgorithm(moveStep, rect);
    }
    return RequestNextFocusByCustomAlgorithm(moveStep, rect);
}

bool FocusHub::RequestNextFocusByDefaultAlgorithm(FocusStep moveStep, const RectF& rect)
{
    if (focusAlgorithm_.scopeType == ScopeType::PROJECT_AREA) {
        auto lastFocusNode = lastWeakFocusNode_.Upgrade();
        CHECK_NULL_RETURN(lastFocusNode, false);
        RefPtr<FocusHub> nextFocusHub = nullptr;
        std::list<RefPtr<FocusHub>> children;
        FlushChildrenFocusHub(children);
        if (IsFocusStepTab(moveStep)) {
            nextFocusHub = lastFocusNode->GetNearestNodeByProjectArea(
                children, GetRealFocusStepByTab(moveStep, AceApplicationInfo::GetInstance().IsRightToLeft()));
        }
        if (!nextFocusHub) {
            nextFocusHub = lastFocusNode->GetNearestNodeByProjectArea(children, moveStep);
        }
        if (!nextFocusHub || nextFocusHub == lastFocusNode) {
            TAG_LOGI(
                AceLogTag::ACE_FOCUS, "Request next focus failed becase cannot find next node by project area.");
            return false;
        }
        auto ret = TryRequestFocus(nextFocusHub, rect, moveStep);
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "Request next focus by project area. Next focus node is %{public}s/%{public}d. Return %{public}d",
            nextFocusHub->GetFrameName().c_str(), nextFocusHub->GetFrameId(), ret);
        return ret;
    }
    if (focusAlgorithm_.direction != ScopeFocusDirection::UNIVERSAL && !IsFocusStepTab(moveStep) &&
        focusAlgorithm_.isVertical != IsFocusStepVertical(moveStep)) {
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "Request next focus failed because direction of node(%{public}d) is different with step(%{public}d).",
            focusAlgorithm_.isVertical, moveStep);
        return IsArrowKeyStepOut(moveStep);
    }
    auto ret = GoToNextFocusLinear(moveStep, rect);
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Request next focus by default linear algorithm. Return %{public}d.", ret);
    return (ret || IsArrowKeyStepOut(moveStep));
}

bool FocusHub::RequestNextFocusByCustomAlgorithm(FocusStep moveStep, const RectF& rect)
{
    if (!lastWeakFocusNode_.Upgrade()) {
        return IsArrowKeyStepOut(moveStep);
    }
    WeakPtr<FocusHub> nextFocusHubWeak;
    focusAlgorithm_.getNextFocusNode(moveStep, lastWeakFocusNode_, nextFocusHubWeak);
    auto nextFocusHub = nextFocusHubWeak.Upgrade();
    if (!nextFocusHub || nextFocusHub == lastWeakFocusNode_.Upgrade()) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Request next focus failed by custom focus algorithm.");
        return IsArrowKeyStepOut(moveStep);
    }
    auto ret = TryRequestFocus(nextFocusHub, rect, moveStep);
    TAG_LOGI(AceLogTag::ACE_FOCUS,
        "Request next focus by custom focus algorithm. Next focus node is %{public}s/%{public}d. Return %{public}d",
        nextFocusHub->GetFrameName().c_str(), nextFocusHub->GetFrameId(), ret);
    return (ret || IsArrowKeyStepOut(moveStep));
}

bool FocusHub::IsArrowKeyStepOut(FocusStep moveStep)
{
    if (!IsFocusStepTab(moveStep) && GetIsFocusGroup() && !arrowKeyStepOut_) {
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "IsArrowKeyStepOut Node(%{public}s/%{public}d), step(%{public}d),"
            "this node is focus group and set can not step out!",
            GetFrameName().c_str(), GetFrameId(), moveStep);
        return true;
    }
    return false;
}

bool FocusHub::FocusToHeadOrTailChild(bool isHead)
{
    if (!IsFocusableWholePath()) {
        return false;
    }
    if (GetIsFocusGroup() && !IsNestingFocusGroup()) {
        return RequestFocusImmediatelyInner();
    }
    if (focusType_ != FocusType::SCOPE || (focusType_ == FocusType::SCOPE && focusDepend_ == FocusDependence::SELF)) {
        return RequestFocusImmediatelyInner();
    }

    auto curFrameNode = GetFrameNode();
    auto curPattern = curFrameNode ? curFrameNode->GetPattern<ScrollablePattern>() : nullptr;
    auto scrollIndexAbility = curPattern ? curPattern->GetScrollIndexAbility() : nullptr;
    if (scrollIndexAbility) {
        scrollIndexAbility(isHead ? FocusHub::SCROLL_TO_HEAD : FocusHub::SCROLL_TO_TAIL);
        auto node = GetFrameNode();
        CHECK_NULL_RETURN(node, false);
        auto pipeline = node->GetContextRefPtr();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }

    bool canChildBeFocused = false;
    if (isHead) {
        canChildBeFocused =
            AnyChildFocusHub<false>([](const RefPtr<FocusHub>& node) { return node->FocusToHeadOrTailChild(true); });
    } else {
        canChildBeFocused =
            AnyChildFocusHub<true>([](const RefPtr<FocusHub>& node) { return node->FocusToHeadOrTailChild(false); });
    }

    if (focusDepend_ == FocusDependence::CHILD) {
        return canChildBeFocused;
    }
    if (focusDepend_ == FocusDependence::AUTO) {
        if (!canChildBeFocused) {
            return RequestFocusImmediatelyInner();
        }
        return canChildBeFocused;
    }
    return false;
}

bool FocusHub::OnClick(const KeyEvent& event)
{
    auto onClickCallback = GetOnClickCallback();
    if (onClickCallback) {
        auto info = GestureEvent();
        info.SetTimeStamp(event.timeStamp);
        auto geometryNode = GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, false);
        auto rect = geometryNode->GetFrameRect();
        auto centerToWindow = Offset((rect.Left() + rect.Right()) / 2, (rect.Top() + rect.Bottom()) / 2);
        auto centerToNode = Offset((rect.Right() - rect.Left()) / 2, (rect.Bottom() - rect.Top()) / 2);
        info.SetGlobalLocation(centerToWindow);
        info.SetLocalLocation(centerToNode);
        info.SetSourceDevice(event.sourceType);
        info.SetDeviceId(event.deviceId);
        auto node = GetFrameNode();
        CHECK_NULL_RETURN(node, false);
        auto pipelineContext = node->GetContextRefPtr();
        if (pipelineContext) {
            auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset() + centerToWindow;
            info.SetScreenLocation(windowOffset);
        }
        info.SetSourceTool(SourceTool::UNKNOWN);
        auto eventHub = eventHub_.Upgrade();
        if (eventHub) {
            auto targetImpl = eventHub->CreateGetEventTargetImpl();
            info.SetTarget(targetImpl().value_or(EventTarget()));
        }
        onClickCallback(info);
        return true;
    }
    return false;
}

void FocusHub::SwitchFocus(const RefPtr<FocusHub>& focusNode)
{
    if (focusType_ != FocusType::SCOPE) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "SwitchFocus: parent focus node is not a scope!");
        return;
    }

    auto focusNodeNeedBlur = lastWeakFocusNode_.Upgrade();
    lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusNode));

    TAG_LOGD(AceLogTag::ACE_FOCUS, "Switch focus from %{public}s/%{public}d to %{public}s/%{public}d",
        focusNodeNeedBlur ? focusNodeNeedBlur->GetFrameName().c_str() : "NULL",
        focusNodeNeedBlur ? focusNodeNeedBlur->GetFrameId() : -1, focusNode->GetFrameName().c_str(),
        focusNode->GetFrameId());
    if (IsCurrentFocus()) {
        auto focusManger = GetFocusManager();
        CHECK_NULL_VOID(focusManger);
        focusManger->UpdateCurrentFocus(Claim(this), SwitchingUpdateReason::SWITCH_FOCUS);
        if (focusNodeNeedBlur && focusNodeNeedBlur != focusNode) {
            focusNodeNeedBlur->LostFocus();
        }
    } else {
        RequestFocusImmediatelyInner();
    }
}

bool FocusHub::GoToNextFocusLinear(FocusStep step, const RectF& rect)
{
    if (step == FocusStep::NONE) {
        return false;
    }
    bool reverse = !IsFocusStepForward(step, IsComponentDirectionRtl());
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = FlushChildrenFocusHub(focusNodes);
    if (focusNodes.empty()) {
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
            if (TryRequestFocus(*itNewFocusNode, rect, step)) {
                return true;
            }
            --itNewFocusNode;
        }
        if (itNewFocusNode == focusNodes.begin()) {
            if (TryRequestFocus(*itNewFocusNode, rect, step)) {
                return true;
            }
        }
    } else {
        if (itNewFocusNode != focusNodes.end()) {
            ++itNewFocusNode;
        }
        while (itNewFocusNode != focusNodes.end()) {
            if (TryRequestFocus(*itNewFocusNode, rect, step)) {
                return true;
            }
            ++itNewFocusNode;
        }
    }

    return false;
}

bool FocusHub::TryRequestFocus(const RefPtr<FocusHub>& focusNode, const RectF& rect, FocusStep step)
{
    if (IsFocusStepTab(step) && focusNode->AcceptFocusOfPriorityChild()) {
        return focusNode->RequestFocusImmediatelyInner();
    }
    if (IsFocusStepTab(step) && focusNode->AcceptFocusOfSpecifyChild(step)) {
        return focusNode->RequestFocusImmediatelyInner();
    }
    if (!IsFocusStepTab(step) && step != FocusStep::NONE && focusNode->GetIsFocusGroup() &&
        !focusNode->IsNestingFocusGroup()) {
        return focusNode->RequestFocusImmediatelyInner();
    }
    if (rect.IsValid()) {
        RectF childRect;
        if (!CalculateRect(focusNode, childRect) ||
            !focusNode->AcceptFocusByRectOfLastFocus(rect - childRect.GetOffset())) {
            return false;
        }
    }
    return focusNode->RequestFocusImmediatelyInner();
}

bool FocusHub::CalculatePosition()
{
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

void FocusHub::SetLastFocusNodeIndex(const RefPtr<FocusHub>& focusNode)
{
    auto frame = GetFrameNode();
    CHECK_NULL_VOID(frame);
    auto pattern = frame->GetPattern();
    CHECK_NULL_VOID(pattern);
    lastFocusNodeIndex_ = pattern->GetFocusNodeIndex(focusNode);
}

void FocusHub::ScrollToLastFocusIndex() const
{
    if (lastFocusNodeIndex_ == -1) {
        return;
    }
    auto frame = GetFrameNode();
    CHECK_NULL_VOID(frame);
    auto pattern = frame->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->ScrollToFocusNodeIndex(lastFocusNodeIndex_);
}

void FocusHub::OnFocus()
{
    if (focusType_ == FocusType::NODE) {
        OnFocusNode();
    } else if (focusType_ == FocusType::SCOPE) {
        OnFocusScope();
    }
    // if root focused, it has no focus view to update.
    auto node = GetFrameNode();
    if (!node || node->IsRootNode()) {
        return;
    }
    UpdateFocusView();
}

void FocusHub::OnBlur()
{
    if (focusType_ == FocusType::NODE) {
        OnBlurNode();
    } else if (focusType_ == FocusType::SCOPE) {
        OnBlurScope();
    }
}

void FocusHub::OnFocusNode()
{
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Node(%{public}s/%{public}d) on focus", GetFrameName().c_str(), GetFrameId());
    if (onFocusInternal_) {
        onFocusInternal_();
    }
    auto node = GetFrameNode();
    CHECK_NULL_VOID(node);
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weak = WeakClaim(this)]() {
        auto focusHub = weak.Upgrade();
        CHECK_NULL_VOID(focusHub);
        auto onFocusCallback = focusHub->GetOnFocusCallback();
        if (onFocusCallback) {
            onFocusCallback();
        }
        auto onJSFrameNodeFocusCallback = focusHub->GetOnJSFrameNodeFocusCallback();
        if (onJSFrameNodeFocusCallback) {
            onJSFrameNodeFocusCallback();
        }
    });
    auto parentFocusHub = GetParentFocusHub();
    if (parentFocusHub) {
        parentFocusHub->SetLastFocusNodeIndex(AceType::Claim(this));
    }

    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->UpdateCurrentFocus(Claim(this), SwitchingUpdateReason::ON_FOCUS_NODE);
    if (focusType_ == FocusType::NODE) {
        focusManager->FocusSwitchingEnd(SwitchingEndReason::NODE_FOCUS);
    }

    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::FOCUS);

    pipeline->RequestFrame();
}

void FocusHub::OnBlurNode()
{
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Node(%{public}s/%{public}d) on blur by %{public}d", GetFrameName().c_str(),
        GetFrameId(), blurReason_);
    if (onBlurInternal_) {
        onBlurInternal_();
    }
    if (onBlurReasonInternal_) {
        onBlurReasonInternal_(blurReason_);
    }
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto* pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([focusHub = Claim(this)]() {
        CHECK_NULL_VOID(focusHub);
        auto onBlurCallback = focusHub->GetOnBlurCallback();
        if (onBlurCallback) {
            onBlurCallback();
        }
        auto onJSFrameNodeBlurCallback_ = focusHub->GetOnJSFrameNodeBlurCallback();
        if (onJSFrameNodeBlurCallback_) {
            onJSFrameNodeBlurCallback_();
        }
    });
    if (blurReason_ != BlurReason::FRAME_DESTROY) {
        ClearFocusState();
    }

    pipeline->RequestFrame();
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

bool FocusHub::HasFocusStateStyle()
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_RETURN(eventHub, false);
    return eventHub->HasStateStyle(UI_STATE_FOCUSED);
}

void FocusHub::OnFocusScope(bool currentHasFocused)
{
    if (focusDepend_ == FocusDependence::SELF) {
        lastWeakFocusNode_ = nullptr;
        OnFocusNode();
        GetFocusManager()->FocusSwitchingEnd(SwitchingEndReason::DEPENDENCE_SELF);
        return;
    }

    std::list<RefPtr<FocusHub>> focusNodes;
    auto itLastFocusNode = FlushChildrenFocusHub(focusNodes);
    bool isAnyChildFocusable = focusNodes.empty()
                                   ? false
                                   : std::any_of(focusNodes.begin(), focusNodes.end(),
                                         [](const RefPtr<FocusHub>& focusNode) { return focusNode->IsFocusable(); });

    if (focusDepend_ == FocusDependence::AUTO && !isAnyChildFocusable) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Node(%{public}s/%{public}d) has no focusable child.", GetFrameName().c_str(),
            GetFrameId());
        lastWeakFocusNode_ = nullptr;
        OnFocusNode();
        GetFocusManager()->FocusSwitchingEnd(SwitchingEndReason::NO_FOCUSABLE_CHILD);
        return;
    }

    if ((focusDepend_ == FocusDependence::AUTO || focusDepend_ == FocusDependence::CHILD) && isAnyChildFocusable) {
        auto itFocusNode = itLastFocusNode;
        if (RequestFocusByPriorityInScope()) {
            if (!currentHasFocused) {
                OnFocusNode();
            }
            return;
        }
        do {
            if (itLastFocusNode == focusNodes.end()) {
                itLastFocusNode = focusNodes.begin();
                lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode));
                if (itLastFocusNode == itFocusNode) {
                    break;
                }
            }
            lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*itLastFocusNode));
            if ((*itLastFocusNode)->RequestFocusImmediatelyInner()) {
                if (!currentHasFocused) {
                    OnFocusNode();
                }
                return;
            }
        } while ((++itLastFocusNode) != itFocusNode);

        // Not found any focusable node, clear focus.
        itLastFocusNode = focusNodes.end();
        lastWeakFocusNode_ = nullptr;
    }
}

void FocusHub::OnBlurScope()
{
    OnBlurNode();
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode) {
        lastFocusNode->LostFocus(blurReason_);
    }
}

bool FocusHub::PaintFocusState(bool isNeedStateStyles)
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, false);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (!context->GetIsFocusActive() || !IsNeedPaintFocusState()) {
        return false;
    }

    if (HasFocusStateStyle()) {
        if (isNeedStateStyles) {
            // do focus state style.
            CheckFocusStateStyle(true);
        }
        return true;
    }

    if (focusStyleType_ == FocusStyleType::NONE) {
        return false;
    }

    if (focusStyleType_ == FocusStyleType::FORCE_NONE) {
        return true;
    }

    if (focusStyleType_ == FocusStyleType::CUSTOM_REGION) {
        CHECK_NULL_RETURN(getInnerFocusRectFunc_, false);
        RoundRect focusRectInner;
        focusRectInner.SetRect({ -1, -1, -1, -1 });
        getInnerFocusRectFunc_(focusRectInner);
        if (!focusRectInner.GetRect().IsValid()) {
            return false;
        }
        return PaintInnerFocusState(focusRectInner);
    }
    return PaintFocusStateToRenderContext();
}

void FocusHub::GetPaintColorFromBox(Color& paintColor)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    if (box_.paintStyle_ && box_.paintStyle_->strokeColor) {
        paintColor = box_.paintStyle_->strokeColor.value();
    } else if (HasPaintColor()) {
        paintColor = GetPaintColor();
    } else {
        paintColor = appTheme->GetFocusColor();
    }
}

void FocusHub::GetPaintWidthFromBox(Dimension& paintWidth)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    if (box_.paintStyle_ && box_.paintStyle_->strokeWidth) {
        paintWidth = box_.paintStyle_->strokeWidth.value();
    } else if (HasPaintWidth()) {
        paintWidth = GetPaintWidth();
    } else {
        paintWidth = appTheme->GetFocusWidthVp();
    }
}

void FocusHub::GetPaintPaddingVp(Dimension& focusPaddingVp)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    focusPaddingVp = Dimension(0.0, DimensionUnit::VP);
    if (box_.paintStyle_ && box_.paintStyle_->margin) {
        focusPaddingVp = box_.paintStyle_->margin.value();
    } else if (HasFocusPadding()) {
        focusPaddingVp = GetFocusPadding();
    } else if (focusStyleType_ == FocusStyleType::INNER_BORDER) {
        focusPaddingVp = -appTheme->GetFocusWidthVp();
    } else if (focusStyleType_ == FocusStyleType::OUTER_BORDER || focusStyleType_ == FocusStyleType::FORCE_BORDER) {
        focusPaddingVp = appTheme->GetFocusOutPaddingVp();
    }
}

bool FocusHub::PaintFocusStateToRenderContext()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(context, false);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_RETURN(appTheme, false);
    Color paintColor;
    GetPaintColorFromBox(paintColor);
    Dimension paintWidth;
    GetPaintWidthFromBox(paintWidth);
    if (NEAR_ZERO(paintWidth.Value())) {
        return true;
    }

    if (focusStyleType_ == FocusStyleType::CUSTOM_BORDER) {
        if (!HasPaintRect()) {
            return false;
        }
        renderContext->PaintFocusState(GetPaintRect(), paintColor, paintWidth);
        return true;
    }

    Dimension focusPaddingVp;
    GetPaintPaddingVp(focusPaddingVp);
    if (HasPaintRect()) {
        renderContext->PaintFocusState(GetPaintRect(), focusPaddingVp, paintColor, paintWidth);
    } else {
        renderContext->PaintFocusState(focusPaddingVp, paintColor, paintWidth);
    }
    return true;
}

void FocusHub::RaiseZIndex()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    const auto& target = frameNode->GetRenderContext();
    if (target && !target->HasZIndex()) {
        target->UpdateZIndex(INT32_MAX); // default focus zIndex
        isRaisedZIndex_ = true;
    }
}

bool FocusHub::PaintAllFocusState()
{
    auto focusManager = GetFocusManager();
    CHECK_NULL_RETURN(focusManager, false);

    if (PaintFocusState()) {
        focusManager->SetLastFocusStateNode(AceType::Claim(this));
        RaiseZIndex();
        if (onPaintFocusStateCallback_) {
            return onPaintFocusStateCallback_();
        }
        return !isFocusActiveWhenFocused_;
    }
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode && lastFocusNode->IsCurrentFocus() && lastFocusNode->IsFocusableNode()) {
        return lastFocusNode->PaintAllFocusState();
    }
    if (onPaintFocusStateCallback_) {
        return onPaintFocusStateCallback_();
    }
    if (focusStyleType_ != FocusStyleType::NONE) {
        return false;
    }

    // Force paint focus box for the component on the tail of focus-chain.
    // This is designed for the focus-chain that all components' focus style are none.
    if (IsViewRootScope()) {
        return !isFocusActiveWhenFocused_;
    }
    focusStyleType_ = FocusStyleType::FORCE_BORDER;
    if (PaintFocusState()) {
        RaiseZIndex();
    }
    focusManager->SetLastFocusStateNode(AceType::Claim(this));
    return !isFocusActiveWhenFocused_;
}

bool FocusHub::PaintInnerFocusState(const RoundRect& paintRect, bool forceUpdate)
{
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, false);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (!forceUpdate && (!context->GetIsFocusActive() || !IsNeedPaintFocusState())) {
        return false;
    }
    auto appTheme = context->GetTheme<AppTheme>();
    CHECK_NULL_RETURN(appTheme, false);
    Color paintColor;
    if (box_.paintStyle_ && box_.paintStyle_->strokeColor) {
        paintColor = box_.paintStyle_->strokeColor.value();
    } else if (HasPaintColor()) {
        paintColor = GetPaintColor();
    } else {
        paintColor = appTheme->GetFocusColor();
    }
    Dimension paintWidth;
    if (box_.paintStyle_ && box_.paintStyle_->strokeWidth) {
        paintWidth = box_.paintStyle_->strokeWidth.value();
    } else if (HasPaintWidth()) {
        paintWidth = GetPaintWidth();
    } else {
        paintWidth = appTheme->GetFocusWidthVp();
    }
    renderContext->ClearFocusState();
    if (NEAR_ZERO(paintWidth.Value())) {
        return true;
    }
    renderContext->PaintFocusState(paintRect, paintColor, paintWidth);
    return true;
}

void FocusHub::ClearFocusState(bool isNeedStateStyles)
{
    if (isNeedStateStyles) {
        // check focus state style.
        CheckFocusStateStyle(false);
    }
    if (onClearFocusStateCallback_) {
        onClearFocusStateCallback_();
    }
    if (focusStyleType_ != FocusStyleType::NONE) {
        auto frameNode = GetFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (isRaisedZIndex_) {
            renderContext->ResetZIndex();
            renderContext->OnZIndexUpdate(0);
            isRaisedZIndex_ = false;
        }
        renderContext->ClearFocusState();
    }
}

void FocusHub::ClearAllFocusState()
{
    ClearFocusState();
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode) {
        lastFocusNode->ClearAllFocusState();
    }
    if (focusStyleType_ == FocusStyleType::FORCE_BORDER) {
        focusStyleType_ = FocusStyleType::NONE;
    }
}

bool FocusHub::IsNeedPaintFocusState()
{
    if (currentFocus_ && IsFocusableNode() &&
        (focusDepend_ == FocusDependence::SELF || focusType_ == FocusType::NODE)) {
        return IsNeedPaintFocusStateSelf();
    }
    auto lastFocusNode = GetLastWeakFocusNode().Upgrade();
    while (lastFocusNode) {
        if (!lastFocusNode->IsCurrentFocus() || !lastFocusNode->IsFocusableNode()) {
            break;
        }
        if (lastFocusNode->IsNeedPaintFocusStateSelf()) {
            return false;
        }
        lastFocusNode = lastFocusNode->GetLastWeakFocusNode().Upgrade();
    }
    return IsNeedPaintFocusStateSelf();
}

bool FocusHub::IsNeedPaintFocusStateSelf()
{
    return focusStyleType_ != FocusStyleType::NONE || HasFocusStateStyle() || box_.HasCustomStyle();
}

bool FocusHub::AcceptFocusOfSpecifyChild(FocusStep step)
{
    if (focusType_ == FocusType::NODE) {
        return IsFocusable();
    }
    if (focusType_ != FocusType::SCOPE || !IsFocusableScope()) {
        return false;
    }
    if (focusDepend_ == FocusDependence::SELF) {
        return true;
    }
    if (IsFocusStepTab(step) && AcceptFocusOfPriorityChild()) {
        return true;
    }

    auto operation = [this, step](const RefPtr<FocusHub>& focusHub) {
        if (focusHub && focusHub->AcceptFocusOfSpecifyChild(step)) {
            lastWeakFocusNode_ = focusHub;
            return true;
        }
        return false;
    };
    bool canChildBeFocused = false;
    if (step == FocusStep::TAB) {
        canChildBeFocused = AnyChildFocusHub<false>(operation);
    } else if (step == FocusStep::SHIFT_TAB) {
        canChildBeFocused = AnyChildFocusHub<true>(operation);
    } else {
        LOGI("Invalid focus step: %{public}d for %{public}s/%{public}d specify focus child.", step,
            GetFrameName().c_str(), GetFrameId());
    }
    if (focusDepend_ == FocusDependence::CHILD) {
        return canChildBeFocused;
    }
    return focusDepend_ == FocusDependence::AUTO;
}

bool FocusHub::AcceptFocusOfLastFocus()
{
    if (focusType_ == FocusType::SCOPE) {
        auto lastFocusNode = lastWeakFocusNode_.Upgrade();
        return lastFocusNode ? lastFocusNode->AcceptFocusOfLastFocus() : false;
    }
    if (focusType_ == FocusType::NODE) {
        return IsFocusableWholePath();
    }
    return false;
}

bool FocusHub::AcceptFocusByRectOfLastFocus(const RectF& rect)
{
    if (focusType_ == FocusType::NODE) {
        return AcceptFocusByRectOfLastFocusNode(rect);
    }
    if (focusType_ == FocusType::SCOPE) {
        return AcceptFocusByRectOfLastFocusFlex(rect);
    }
    return false;
}

bool FocusHub::AcceptFocusByRectOfLastFocusNode(const RectF& rect)
{
    return IsFocusableWholePath();
}

bool FocusHub::AcceptFocusByRectOfLastFocusFlex(const RectF& rect)
{
    if (!rect.IsValid()) {
        return false;
    }

    if (focusType_ != FocusType::SCOPE || !IsFocusableWholePath()) {
        return false;
    }
    if (focusDepend_ == FocusDependence::SELF) {
        return true;
    }
    if (AcceptFocusOfPriorityChild()) {
        return true;
    }
    bool canChildBeFocused = false;
    OffsetF offset;
    RefPtr<FocusHub> newFocusNode;
    AllChildFocusHub([this, &rect, &offset, &newFocusNode](const RefPtr<FocusHub>& child) {
        double minVal = std::numeric_limits<double>::max();
        if (!child->IsFocusable()) {
            return;
        }

        RectF childRect;
        if (!CalculateRect(child, childRect)) {
            return;
        }
        if (!childRect.IsValid() || NearZero(childRect.Width()) || NearZero(childRect.Height())) {
            return;
        }
        OffsetF vec = childRect.Center() - rect.Center();
        double val = (vec.GetX() * vec.GetX()) + (vec.GetY() * vec.GetY());
        if (minVal > val) {
            minVal = val;
            newFocusNode = child;
            offset = childRect.GetOffset();
        }
    });

    if (newFocusNode && newFocusNode->AcceptFocusByRectOfLastFocus(rect - offset)) {
        lastWeakFocusNode_ = newFocusNode;
        canChildBeFocused = true;
    }
    if (focusDepend_ == FocusDependence::CHILD) {
        return canChildBeFocused;
    }
    return focusDepend_ == FocusDependence::AUTO;
}

bool FocusHub::CalculateRect(const RefPtr<FocusHub>& childNode, RectF& rect) const
{
    auto frameNode = childNode->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    rect = frameNode->GetPaintRectWithTransform();

    //  Calculate currentNode -> childNode offset
    auto parent = frameNode->GetAncestorNodeOfFrame();
    while (parent && parent != GetFrameNode()) {
        rect += parent->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
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
    return false;
}

bool FocusHub::IsFocusableNodeByTab()
{
    auto parent = GetParentFocusHub();
    CHECK_NULL_RETURN(parent, GetTabIndex() == 0);
    return (GetTabIndex() == 0) && (parent->GetTabIndex() == 0);
}

bool FocusHub::IsFocusableScopeByTab()
{
    if (!IsFocusableNodeByTab()) {
        return false;
    }
    bool hasChild = false;
    return AnyChildFocusHub([&hasChild](const RefPtr<FocusHub>& focusNode) {
        hasChild = true;
        return focusNode->IsFocusableByTab();
    }) || !hasChild;
}

bool FocusHub::IsFocusableWholePath()
{
    auto parent = GetParentFocusHubWithBoundary();
    while (parent) {
        if (!parent->IsFocusableNode()) {
            return false;
        }
        parent = parent->GetParentFocusHubWithBoundary();
    }
    return IsFocusable();
}

WeakPtr<FocusHub> FocusHub::GetUnfocusableParentFocusNode()
{
    if (!IsFocusable()) {
        return AceType::WeakClaim(this);
    }
    auto parent = GetParentFocusHubWithBoundary();
    while (parent) {
        if (!parent->IsFocusableNode()) {
            return AceType::WeakClaim(AceType::RawPtr(parent));
        }
        parent = parent->GetParentFocusHubWithBoundary();
    }
    return nullptr;
}

bool FocusHub::IsSelfFocusableWholePath()
{
    auto parent = GetParentFocusHubWithBoundary();
    while (parent) {
        if (!parent->IsFocusableNode()) {
            return false;
        }
        parent = parent->GetParentFocusHubWithBoundary();
    }
    return IsFocusableNode();
}

bool FocusHub::IsOnRootTree() const
{
    auto parent = GetParentFocusHub();
    while (parent) {
        auto parentName = parent->GetFrameName();
        if (parentName == V2::ROOT_ETS_TAG) {
            return true;
        }
        parent = parent->GetParentFocusHub();
    }
    return false;
}

void FocusHub::CollectTabIndexNodes(TabIndexNodeList& tabIndexNodes)
{
    if (GetTabIndex() > 0 && IsFocusableWholePath()) {
        tabIndexNodes.emplace_back(GetTabIndex(), WeakClaim(this));
    }
    if (GetFocusType() == FocusType::SCOPE) {
        AllChildFocusHub([&tabIndexNodes](const RefPtr<FocusHub>& child) {
            child->CollectTabIndexNodes(tabIndexNodes);
        });
    }
}

bool FocusHub::GoToFocusByTabNodeIdx(TabIndexNodeList& tabIndexNodes, int32_t tabNodeIdx)
{
    auto iter = tabIndexNodes.begin();
    std::advance(iter, tabNodeIdx);
    if (iter == tabIndexNodes.end()) {
        return false;
    }
    auto nodeNeedToFocus = (*iter).second.Upgrade();
    if (!nodeNeedToFocus) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "Tab index node is null");
        return false;
    }
    auto nodeIdNeedToFocus = nodeNeedToFocus->GetFrameId();
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Move focus to tab index node(%{public}d: %{public}s/%{public}d)", tabNodeIdx,
        nodeNeedToFocus->GetFrameName().c_str(), nodeNeedToFocus->GetFrameId());
    if (nodeNeedToFocus->GetFocusType() == FocusType::SCOPE && !nodeNeedToFocus->IsDefaultGroupHasFocused()) {
        auto defaultFocusNode = nodeNeedToFocus->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT);
        if (defaultFocusNode) {
            if (!defaultFocusNode->IsFocusableWholePath()) {
                TAG_LOGI(AceLogTag::ACE_FOCUS, "node(%{public}d) is not focusable", tabNodeIdx);
                return false;
            }
            nodeNeedToFocus->SetIsDefaultGroupHasFocused(true);
            if (defaultFocusNode->RequestFocusImmediatelyInner()) {
                lastTabIndexNodeId_ = nodeIdNeedToFocus;
                return true;
            }
            return false;
        }
    }
    if (!nodeNeedToFocus->IsFocusableWholePath()) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "node(%{public}d) is not focusable", tabNodeIdx);
        return false;
    }
    if (nodeNeedToFocus->RequestFocusImmediatelyInner()) {
        lastTabIndexNodeId_ = nodeIdNeedToFocus;
        return true;
    }
    return false;
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
    RefPtr<FocusHub> target;
    AnyChildFocusHub([&target, nodeType](const RefPtr<FocusHub>& child) {
        if (!child) {
            return false;
        }
        auto childFrame = child->GetFrameNode();
        if (!childFrame) {
            return false;
        }
        auto childFocusView = childFrame->GetPattern<FocusView>();
        if (childFocusView && childFocusView->IsFocusViewLegal() && childFocusView->IsEntryFocusView()) {
            return false;
        }
        target = child->GetChildFocusNodeByType(nodeType);
        return target ? true : false;
    });
    return target;
}

RefPtr<FocusHub> FocusHub::GetChildFocusNodeById(const std::string& id)
{
    if (id.empty()) {
        return nullptr;
    }
    if (GetInspectorKey().has_value() && GetInspectorKey().value() == id) {
        return AceType::Claim(this);
    }
    RefPtr<FocusHub> target;
    if (focusType_ == FocusType::SCOPE) {
        AnyChildFocusHub([&target, &id](const RefPtr<FocusHub>& child) {
            target = child->GetChildFocusNodeById(id);
            return target ? true : false;
        });
    }
    return target;
}

RefPtr<FocusView> FocusHub::GetFirstChildFocusView()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto focusView = frameNode->GetPattern<FocusView>();
    if (focusView) {
        return focusView;
    }
    AnyChildFocusHub<true>(
        [&focusView](const RefPtr<FocusHub>& childFocusHub) {
            if (!childFocusHub) {
                return false;
            }
            focusView = childFocusHub->GetFirstChildFocusView();
            return focusView ? true : false;
        });
    return focusView;
}

bool FocusHub::TriggerFocusScroll()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto* context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    if (!context->GetIsFocusActive() || (focusType_ == FocusType::DISABLE && !isFocusUnit_)) {
        return false;
    }
    return ScrollByOffset();
}

bool FocusHub::ScrollByOffset()
{
    auto parent = GetParentFocusHub();
    RefPtr<FrameNode> parentFrame;
    RefPtr<Pattern> parentPattern;
    bool ret = false;
    while (parent) {
        if (parent->isFocusUnit_) {
            return false;
        }
        parentFrame = parent->GetFrameNode();
        if (!parentFrame) {
            parent = parent->GetParentFocusHub();
            continue;
        }
        if (ScrollByOffsetToParent(parentFrame)) {
            ret = true;
        }
        parent = parent->GetParentFocusHub();
    }
    return ret;
}

bool FocusHub::ScrollByOffsetToParent(const RefPtr<FrameNode>& parentFrameNode) const
{
    auto curFrameNode = GetFrameNode();
    CHECK_NULL_RETURN(curFrameNode, false);
    CHECK_NULL_RETURN(parentFrameNode, false);
    auto parentPattern = parentFrameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(parentPattern, false);

    auto scrollAbility = parentPattern->GetScrollOffsetAbility();
    auto scrollFunc = scrollAbility.first;
    auto scrollAxis = scrollAbility.second;
    if (!scrollFunc || scrollAxis == Axis::NONE) {
        return false;
    }
    auto moveOffset = GetMoveOffset(parentFrameNode, curFrameNode, scrollAxis == Axis::VERTICAL);
    if (!NearZero(moveOffset)) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Scroll offset: %{public}f on %{public}s/%{public}d, axis: %{public}d",
            moveOffset, parentFrameNode->GetTag().c_str(), parentFrameNode->GetId(), scrollAxis);
        auto ret = scrollFunc(moveOffset);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
        return ret;
    }
    return false;
}

bool FocusHub::RequestFocusImmediatelyById(const std::string& id, bool isSyncRequest)
{
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto pipeline = node->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_RETURN(focusManager, false);
    auto focusNode = GetChildFocusNodeById(id);
    if (!focusNode) {
#ifdef IS_RELEASE_VERSION
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Request focus id can not found.");
#else
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Request focus id: %{public}s can not found.", id.c_str());
#endif
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_EXIST);
        return false;
    }
    auto result = true;
    if ((isSyncRequest && !focusNode->IsSyncRequestFocusable()) ||
        (!isSyncRequest && !focusNode->IsFocusable())) {
        result = false;
    }
#ifdef IS_RELEASE_VERSION
    TAG_LOGI(AceLogTag::ACE_FOCUS,
        "Request focus immediately %{public}s by id: %{public}s. The node is %{public}s/%{public}d.",
        isSyncRequest ? "sync" : "async", id.c_str(), focusNode->GetFrameName().c_str(), focusNode->GetFrameId());
#else
    TAG_LOGI(AceLogTag::ACE_FOCUS,
        "Request focus immediately %{public}s by id. The node is %{public}s/%{public}d.",
        isSyncRequest ? "sync" : "async", focusNode->GetFrameName().c_str(), focusNode->GetFrameId());
#endif
    if (result || !isSyncRequest) {
        pipeline->AddDirtyRequestFocus(focusNode->GetFrameNode());
        if (isSyncRequest) {
            focusNode->SetLastWeakFocusNodeToPreviousNode();
            pipeline->FlushRequestFocus();
        }
    }
    return result;
}

int32_t FocusHub::GetFocusingTabNodeIdx(TabIndexNodeList& tabIndexNodes) const
{
    if (lastTabIndexNodeId_ == DEFAULT_TAB_FOCUSED_INDEX) {
        return DEFAULT_TAB_FOCUSED_INDEX;
    }
    int32_t i = 0;
    for (auto& wpNode : tabIndexNodes) {
        auto node = wpNode.second.Upgrade();
        if (node && node->IsCurrentFocus() && node->GetFrameId() == lastTabIndexNodeId_) {
            return i;
        }
        ++i;
    }
    return DEFAULT_TAB_FOCUSED_INDEX;
}

bool FocusHub::HandleFocusByTabIndex(const KeyEvent& event)
{
    if (event.code != KeyCode::KEY_TAB || event.action != KeyAction::DOWN) {
        return false;
    }
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto pipeline = node->GetContextRefPtr();
    if (pipeline && pipeline->IsTabJustTriggerOnKeyEvent()) {
        return false;
    }
    TabIndexNodeList tabIndexNodes;
    tabIndexNodes.clear();
    CollectTabIndexNodes(tabIndexNodes);
    if (tabIndexNodes.empty()) {
        return false;
    }
    tabIndexNodes.sort([](std::pair<int32_t, WeakPtr<FocusHub>>& a, std::pair<int32_t, WeakPtr<FocusHub>>& b) {
        return a.first < b.first;
    });
    int32_t curTabFocusIndex = GetFocusingTabNodeIdx(tabIndexNodes);
    if ((curTabFocusIndex < 0 || curTabFocusIndex >= static_cast<int32_t>(tabIndexNodes.size())) &&
        curTabFocusIndex != DEFAULT_TAB_FOCUSED_INDEX) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Current focused tabIndex: %{public}d is not valid. Use default focus system.",
            curTabFocusIndex);
        return false;
    }
    if (curTabFocusIndex == DEFAULT_TAB_FOCUSED_INDEX) {
        curTabFocusIndex = 0;
    } else {
        if (event.IsShiftWith(KeyCode::KEY_TAB)) {
            --curTabFocusIndex;
        } else {
            ++curTabFocusIndex;
        }
        if (curTabFocusIndex < 0 || curTabFocusIndex >= static_cast<int32_t>(tabIndexNodes.size())) {
            curTabFocusIndex = (curTabFocusIndex + static_cast<int32_t>(tabIndexNodes.size())) %
                               static_cast<int32_t>(tabIndexNodes.size());
        }
    }
    return GoToFocusByTabNodeIdx(tabIndexNodes, curTabFocusIndex);
}

bool FocusHub::HasBackwardFocusMovementInChildren()
{
    return AnyChildFocusHub([](const RefPtr<FocusHub>& child) { return child->HasBackwardFocusMovement(); });
}

bool FocusHub::HasForwardFocusMovementInChildren()
{
    return AnyChildFocusHub([](const RefPtr<FocusHub>& child) { return child->HasForwardFocusMovement(); });
}

void FocusHub::ClearFocusMovementFlagsInChildren()
{
    AllChildFocusHub([](const RefPtr<FocusHub>& child) {
        child->ClearFocusMovementFlags();
        child->ClearFocusMovementFlagsInChildren();
    });
}

double FocusHub::GetProjectAreaOnRect(const RectF& rect, const RectF& projectRect, FocusStep step)
{
    float areaWidth = 0.0;
    float areaHeight = 0.0;
    switch (step) {
        case FocusStep::UP:
            if (rect.Top() < projectRect.Bottom() && rect.Right() > projectRect.Left() &&
                rect.Left() < projectRect.Right()) {
                areaWidth = std::min(rect.Right(), projectRect.Right()) - std::max(rect.Left(), projectRect.Left());
                areaHeight = std::min(rect.Bottom(), projectRect.Bottom()) - rect.Top();
            }
            break;
        case FocusStep::DOWN:
            if (rect.Bottom() > projectRect.Top() && rect.Right() > projectRect.Left() &&
                rect.Left() < projectRect.Right()) {
                areaWidth = std::min(rect.Right(), projectRect.Right()) - std::max(rect.Left(), projectRect.Left());
                areaHeight = rect.Bottom() - std::max(rect.Top(), projectRect.Top());
            }
            break;
        case FocusStep::LEFT:
            if (rect.Left() < projectRect.Right() && rect.Bottom() > projectRect.Top() &&
                rect.Top() < projectRect.Bottom()) {
                areaWidth = std::min(rect.Right(), projectRect.Right()) - rect.Left();
                areaHeight = std::min(rect.Bottom(), projectRect.Bottom()) - std::max(rect.Top(), projectRect.Top());
            }
            break;
        case FocusStep::RIGHT:
            if (rect.Right() > projectRect.Left() && rect.Bottom() > projectRect.Top() &&
                rect.Top() < projectRect.Bottom()) {
                areaWidth = rect.Right() - std::max(rect.Left(), projectRect.Left());
                areaHeight = std::min(rect.Bottom(), projectRect.Bottom()) - std::max(rect.Top(), projectRect.Top());
            }
            break;
        default:
            break;
    }
    return areaWidth * areaHeight;
}

RefPtr<FocusHub> FocusHub::GetNearestNodeByProjectArea(const std::list<RefPtr<FocusHub>>& allNodes, FocusStep step)
{
    CHECK_NULL_RETURN(!allNodes.empty(), nullptr);
    auto curFrameNode = GetFrameNode();
    CHECK_NULL_RETURN(curFrameNode, nullptr);
    auto curFrameOffset = curFrameNode->GetTransformRelativeOffset();
    auto curGeometryNode = curFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(curGeometryNode, nullptr);
    RectF curFrameRect = RectF(curFrameOffset, curGeometryNode->GetFrameRect().GetSize());
    curFrameRect.SetOffset(curFrameOffset);
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "Current focus node is %{public}s/%{public}d. Rect is {%{public}f,%{public}f,%{public}f,%{public}f}.",
        GetFrameName().c_str(), GetFrameId(), curFrameRect.Left(), curFrameRect.Top(), curFrameRect.Right(),
        curFrameRect.Bottom());
    bool isTabStep = IsFocusStepTab(step);
    double resDistance = !isTabStep ? std::numeric_limits<double>::max() : 0.0f;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    RefPtr<FocusHub> nextNode;
    for (const auto& node : allNodes) {
        if (!node || AceType::RawPtr(node) == this) {
            continue;
        }
        auto frameNode = node->GetFrameNode();
        if (!frameNode) {
            continue;
        }
        auto frameOffset = frameNode->GetTransformRelativeOffset();
        auto geometryNode = frameNode->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        if (!node->IsFocusable()) {
            continue;
        }
        RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());
        auto realStep = step;
        if (step == FocusStep::TAB) {
            frameRect -= OffsetF(0, curFrameRect.Height());
            // If TAB step, for RTL, the direction of focus is RIGHT.
            // If TAB step, for LTR, the direction of focus is LEFT.
            realStep = isRtl ? FocusStep::RIGHT : FocusStep::LEFT;
        } else if (step == FocusStep::SHIFT_TAB) {
            frameRect += OffsetF(0, curFrameRect.Height());
            // If SHIFT_TAB step, for RTL, the direction of focus is LEFT.
            // If SHIFT_TAB step, for LTR, the direction of focus is RIGHT.
            realStep = isRtl ? FocusStep::LEFT : FocusStep::RIGHT;
        }
        auto projectArea = GetProjectAreaOnRect(frameRect, curFrameRect, realStep);
        if (Positive(projectArea)) {
            OffsetF vec = frameRect.Center() - curFrameRect.Center();
            double val = (vec.GetX() * vec.GetX()) + (vec.GetY() * vec.GetY());
            // The operation direction is opposite for RTL languages.
            if ((step == FocusStep::TAB && (isRtl ? Negative(vec.GetX()) : Positive(vec.GetX()))) ||
                (step == FocusStep::SHIFT_TAB && (isRtl ? Positive(vec.GetX()) : Negative(vec.GetX())))) {
                val *= -1.0;
            }
            if ((!isTabStep && val < resDistance) || (isTabStep && val > resDistance)) {
                resDistance = val;
                nextNode = node;
            }
        }
    }
    TAG_LOGD(AceLogTag::ACE_FOCUS, "Next focus node is %{public}s/%{public}d. Min distance is %{public}f.",
        nextNode ? nextNode->GetFrameName().c_str() : "NULL", nextNode ? nextNode->GetFrameId() : -1, resDistance);
    return nextNode;
}

bool FocusHub::UpdateFocusView()
{
    CHECK_NULL_RETURN(IsCurrentFocus(), false);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto focusView = frameNode->GetPattern<FocusView>();
    if (!focusView) {
        auto focusManager = GetFocusManager();
        CHECK_NULL_RETURN(focusManager, false);
        focusManager->FlushFocusView();
        return true;
    }
    auto focusedChild = lastWeakFocusNode_.Upgrade();
    while (focusedChild) {
        auto focusedChildFrame = focusedChild->GetFrameNode();
        if (!focusedChildFrame) {
            focusedChild = focusedChild->lastWeakFocusNode_.Upgrade();
            continue;
        }
        auto focusedChildFocusView = focusedChildFrame->GetPattern<FocusView>();
        if (focusedChildFocusView) {
            return false;
        }
        focusedChild = focusedChild->lastWeakFocusNode_.Upgrade();
    }
    auto curFocusView = FocusView::GetCurrentFocusView();
    if (focusView && focusView->IsFocusViewLegal() && focusView != curFocusView) {
        auto focusViewRootScope = focusView->GetViewRootScope();
        auto focusViewRootScopeChild = focusViewRootScope ? focusViewRootScope->lastWeakFocusNode_.Upgrade() : nullptr;
        if (focusViewRootScopeChild && focusViewRootScopeChild->IsCurrentFocus()) {
            focusView->SetIsViewRootScopeFocused(false);
        }
        TAG_LOGD(AceLogTag::ACE_FOCUS, "UpdateFocusView by node %{public}s/%{public}d.",
            GetFrameName().c_str(), GetFrameId());
        focusView->FocusViewShow(true);
    }
    return true;
}

void FocusHub::SetFocusScopeId(const std::string& focusScopeId, bool isGroup, bool arrowKeyStepOut)
{
    if (focusType_ != FocusType::SCOPE) {
        return;
    }
    auto focusManager = GetFocusManager();
    if (focusScopeId.empty()) {
        if (!focusScopeId_.empty() && focusManager) {
            focusManager->RemoveFocusScope(focusScopeId_);
        }
        focusScopeId_ = focusScopeId;
        isFocusScope_ = false;
        isGroup_ = false;
        arrowKeyStepOut_ = true;
        return;
    }
    if (focusManager && !focusManager->AddFocusScope(focusScopeId, AceType::Claim(this))) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "node(%{public}s/%{public}d) focusScopeId exist.", GetFrameName().c_str(),
            GetFrameId());
        bool isValidFocusScope = (isFocusScope_ && !focusScopeId_.empty());
        if (isValidFocusScope) {
            isGroup_ = isGroup;
            arrowKeyStepOut_ = arrowKeyStepOut;
        }
        return;
    }
    focusScopeId_ = focusScopeId;
    isFocusScope_ = true;
    isGroup_ = isGroup;
    arrowKeyStepOut_ = arrowKeyStepOut;
}

void FocusHub::RemoveFocusScopeIdAndPriority()
{
    auto focusManager = GetFocusManager();
    if (isFocusScope_) {
        if (!focusScopeId_.empty() && focusManager) {
            focusManager->RemoveFocusScope(focusScopeId_);
        }
    } else {
        if (focusPriority_ != FocusPriority::AUTO && !focusScopeId_.empty() && focusManager) {
            focusManager->RemoveScopePriorityNode(focusScopeId_, AceType::Claim(this));
        }
    }
}

void FocusHub::SetFocusScopePriority(const std::string& focusScopeId, const uint32_t focusPriority)
{
    if (isFocusScope_) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "FocusScope can not set focusPriority");
        return;
    }
    auto focusManager = GetFocusManager();
    if (focusScopeId.empty()) {
        if (!focusScopeId_.empty() && focusManager) {
            focusManager->RemoveScopePriorityNode(focusScopeId_, AceType::Claim(this));
        }
        focusScopeId_ = focusScopeId;
        focusPriority_ = FocusPriority::AUTO;
        return;
    }
    if (!focusScopeId_.empty() && focusScopeId_ != focusScopeId && focusManager) {
        focusManager->RemoveScopePriorityNode(focusScopeId_, AceType::Claim(this));
    }

    if (focusPriority == static_cast<uint32_t>(FocusPriority::PRIOR)) {
        focusPriority_ = FocusPriority::PRIOR;
        if (focusManager) {
            focusManager->AddScopePriorityNode(focusScopeId, AceType::Claim(this), false);
        }
    } else if (focusPriority == static_cast<uint32_t>(FocusPriority::PREVIOUS)) {
        focusPriority_ = FocusPriority::PREVIOUS;
        if (focusManager) {
            focusManager->AddScopePriorityNode(focusScopeId, AceType::Claim(this), true);
        }
    } else {
        if (focusScopeId_ == focusScopeId && focusPriority_ != FocusPriority::AUTO && focusManager) {
            focusManager->RemoveScopePriorityNode(focusScopeId, AceType::Claim(this));
        }
        focusPriority_ = FocusPriority::AUTO;
    }
    focusScopeId_ = focusScopeId;
}

bool FocusHub::IsInFocusGroup()
{
    if (GetIsFocusGroup() && !IsNestingFocusGroup()) {
        return true;
    }
    auto parent = GetParentFocusHub();
    while (parent) {
        if (parent->GetIsFocusGroup() && !parent->IsNestingFocusGroup()) {
            return true;
        }
        auto frameNode = parent->GetFrameNode();
        auto focusView = frameNode ? frameNode->GetPattern<FocusView>() : nullptr;
        if (focusView) {
            return false;
        }
        parent = parent->GetParentFocusHub();
    }
    return false;
}

void FocusHub::SetLastWeakFocusNodeWholeScope(const std::string& focusScopeId)
{
    RefPtr<FocusHub> thisNode = AceType::Claim(this);
    auto parent = GetParentFocusHub();
    while (parent) {
        parent->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(thisNode)));
        if (parent->GetIsFocusScope() && (parent->GetFocusScopeId() == focusScopeId)) {
            return;
        }
        thisNode = parent;
        parent = parent->GetParentFocusHub();
    }
}

bool FocusHub::IsFocusAbleChildOf(const RefPtr<FocusHub>& parentFocusHub)
{
    auto parent = GetParentFocusHub();
    while (parent) {
        if (parent == parentFocusHub) {
            if (!IsFocusableWholePath()) {
                return false;
            }
            return true;
        }
        parent = parent->GetParentFocusHub();
    }
    return false;
}

WeakPtr<FocusHub> FocusHub::GetChildPriorfocusNode(const std::string& focusScopeId)
{
    if (focusScopeId.empty()) {
        return nullptr;
    }

    auto focusManager = GetFocusManager();
    if (!focusManager) {
        return nullptr;
    }
    RefPtr<FocusHub> thisNode = AceType::Claim(this);
    auto optionalList = focusManager->GetFocusScopePriorityList(focusScopeId);
    if (!optionalList.has_value()) {
        return nullptr;
    }
    auto focusScopePriorityList = optionalList.value();
    for (const auto& childWeak : (*focusScopePriorityList)) {
        auto child = childWeak.Upgrade();
        if (!child) {
            continue;
        }
        if (child->IsFocusAbleChildOf(thisNode)) {
            return childWeak;
        }
    }
    return nullptr;
}

bool FocusHub::SetLastWeakFocusNodeToPreviousNode()
{
    if (focusType_ != FocusType::SCOPE || focusScopeId_.empty() || !isFocusScope_) {
        return false;
    }
    auto newFocusNodeWeak = GetChildPriorfocusNode(focusScopeId_);
    auto newFocusNode = newFocusNodeWeak.Upgrade();
    if (!newFocusNode) {
        return false;
    }
    if (newFocusNode->GetFocusPriority() == FocusPriority::PREVIOUS) {
        newFocusNode->SetLastWeakFocusNodeWholeScope(focusScopeId_);
        return true;
    }
    return false;
}

void FocusHub::SetLastWeakFocusToPreviousInFocusView()
{
    if (SetLastWeakFocusNodeToPreviousNode()) {
        return;
    }
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    while (lastFocusNode) {
        if (lastFocusNode->SetLastWeakFocusNodeToPreviousNode()) {
            return;
        }
        auto newLastWeak = lastFocusNode->GetLastWeakFocusNode();
        lastFocusNode = newLastWeak.Upgrade();
    }
    return;
}

bool FocusHub::AcceptFocusOfPriorityChild()
{
    if (focusType_ != FocusType::SCOPE || focusScopeId_.empty() || !isFocusScope_) {
        return false;
    }

    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (!lastFocusNode) {
        auto newFocusNodeWeak = GetChildPriorfocusNode(focusScopeId_);
        auto newFocusNode = newFocusNodeWeak.Upgrade();
        if (!newFocusNode) {
            return false;
        }
        newFocusNode->SetLastWeakFocusNodeWholeScope(focusScopeId_);
        return true;
    } else {
        if (GetIsFocusGroup() && !IsNestingFocusGroup()) {
            SetLastWeakFocusNodeToPreviousNode();
            return true;
        }
    }
    return false;
}

bool FocusHub::RequestFocusByPriorityInScope()
{
    if (focusScopeId_.empty() || !isFocusScope_) {
        return false;
    }
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (!lastFocusNode) {
        auto newFocusNodeWeak = GetChildPriorfocusNode(focusScopeId_);
        auto newFocusNode = newFocusNodeWeak.Upgrade();
        if (!newFocusNode) {
            return false;
        }
        newFocusNode->SetLastWeakFocusNodeWholeScope(focusScopeId_);
        lastFocusNode = lastWeakFocusNode_.Upgrade();
        if (lastFocusNode && lastFocusNode->RequestFocusImmediatelyInner()) {
            return true;
        }
        return false;
    }
    if (GetIsFocusGroup() && !IsNestingFocusGroup()) {
        SetLastWeakFocusNodeToPreviousNode();
        lastFocusNode = lastWeakFocusNode_.Upgrade();
        if (lastFocusNode && lastFocusNode->RequestFocusImmediatelyInner()) {
            return true;
        }
    }
    return false;
}

bool FocusHub::IsNestingFocusGroup()
{
    if (!GetIsFocusGroup()) {
        return false;
    }
    auto parent = GetParentFocusHub();
    while (parent) {
        if (parent->GetIsFocusGroup()) {
            return true;
        }
        parent = parent->GetParentFocusHub();
    }
    return false;
}

void FocusHub::ToJsonValue(
    const RefPtr<FocusHub>& hub, std::unique_ptr<JsonValue>& json, const InspectorFilter& filter)
{
    bool focusable = false;
    bool focused = false;
    if (hub) {
        focusable = hub->IsFocusable();
        focused = hub->IsCurrentFocus();
    }
    if (filter.CheckFixedAttr(FIXED_ATTR_FOCUSABLE)) {
        json->Put("focusable", focusable);
        json->Put("focused", focused);
    }
    if (filter.IsFastFilter()) {
        return;
    }

    bool enabled = true;
    bool defaultFocus = false;
    bool groupDefaultFocus = false;
    bool focusOnTouch = false;
    int32_t tabIndex = 0;
    std::unique_ptr<JsonValue> focusBox = nullptr;
    if (hub) {
        enabled = hub->IsEnabled();
        defaultFocus = hub->IsDefaultFocus();
        groupDefaultFocus = hub->IsDefaultGroupFocus();
        focusOnTouch = hub->IsFocusOnTouch().value_or(false);
        tabIndex = hub->GetTabIndex();
        focusBox = FocusBox::ToJsonValue(hub->box_);
    }
    json->PutExtAttr("enabled", enabled, filter);
    json->PutExtAttr("defaultFocus", defaultFocus, filter);
    json->PutExtAttr("groupDefaultFocus", groupDefaultFocus, filter);
    json->PutExtAttr("focusOnTouch", focusOnTouch, filter);
    json->PutExtAttr("tabIndex", tabIndex, filter);
    json->PutExtAttr("focusBox", focusBox, filter);
}

bool FocusHub::IsComponentDirectionRtl()
{
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto frame = GetFrameNode();
    CHECK_NULL_RETURN(frame, isRightToLeft);
    auto layoutProperty = frame->GetLayoutPropertyPtr<LayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, isRightToLeft);
    auto layoutDirection = layoutProperty->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO) {
        return isRightToLeft;
    }
    if (layoutDirection == TextDirection::LTR) {
        return false;
    }
    if (layoutDirection == TextDirection::RTL) {
        return true;
    }
    return isRightToLeft;
}

void FocusHub::DumpFocusScopeTreeInJson(int32_t depth)
{
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
    std::list<RefPtr<FocusHub>> focusNodes;
    FlushChildrenFocusHub(focusNodes);
    std::string information = GetFrameName();
    information += IsCurrentFocus() ? "(Scope*)" : "(Scope)";
    auto frameId = GetFrameId();
    children->Put("childSize", static_cast<int32_t>(focusNodes.size()));
    children->Put("id", frameId);
    if (GetInspectorKey().has_value()) {
        children->Put("idstr", GetInspectorKey().value().c_str());
    }
    if (!IsFocusable()) {
        information = "(-)" + information;
        children->Put("Enabled", IsEnabled());
        children->Put("Show", IsShow());
        children->Put("Focusable", focusable_);
        children->Put("ParentFocusable", parentFocusable_);
    }
    if (IsDefaultFocus()) {
        information += "[Default]";
    }
    if (isFocusScope_ && !focusScopeId_.empty()) {
        if (GetIsFocusGroup()) {
            children->Put("GroupId", focusScopeId_.c_str());
        } else {
            children->Put("ScopeId", focusScopeId_.c_str());
        }
    }
    if (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PRIOR)) {
        children->Put("prior-focus-in-", focusScopeId_.c_str());
    }
    if (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PREVIOUS)) {
        children->Put("previous-focus-in-", focusScopeId_.c_str());
    }
    auto focusMgr = GetFocusManager();
    if (focusMgr && focusMgr->GetLastFocusStateNode() == this) {
        information += " [Painted]";
    }
    information += ("_" + std::to_string(frameId));
    json->Put(information.c_str(), children);
    DumpFocusUieInJson(json);
    std::string jsonstr = DumpLog::GetInstance().FormatDumpInfo(json->ToString(), depth);
    auto prefix = DumpLog::GetInstance().GetPrefix(depth);
    DumpLog::GetInstance().PrintJson(prefix + jsonstr);
    for (const auto& child : focusNodes) {
        child->DumpFocusTree(depth + 1, true);
    }
}

void FocusHub::DumpFocusNodeTreeInJson(int32_t depth)
{
    auto json = JsonUtil::Create(true);
    std::string information = GetFrameName();
    std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
    if (IsCurrentFocus()) {
        information += "(Node*)";
    } else {
        information += "(Node)";
    }
    auto frameId = GetFrameId();
    children->Put("childSize", 0);
    children->Put("id", frameId);
    if (GetInspectorKey().has_value()) {
        children->Put("idstr", GetInspectorKey().value().c_str());
    }
    if (!IsFocusable()) {
        information = "(-)" + information;
        children->Put("Enabled", IsEnabled());
        children->Put("Show", IsShow());
        children->Put("Focusable", focusable_);
        children->Put("ParentFocusable", parentFocusable_);
    }
    information += IsDefaultFocus() ? "[Default]" : "";
    if (isFocusScope_ && !focusScopeId_.empty()) {
        if (GetIsFocusGroup()) {
            children->Put("GroupId", focusScopeId_.c_str());
        } else {
            children->Put("ScopeId", focusScopeId_.c_str());
        }
    }
    if (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PRIOR)) {
        children->Put("prior-focus-in-", focusScopeId_.c_str());
    }
    if (!focusScopeId_.empty() && (focusPriority_ == FocusPriority::PREVIOUS)) {
        children->Put("previous-focus-in-", focusScopeId_.c_str());
    }
    auto focusMgr = GetFocusManager();
    if (focusMgr && focusMgr->GetLastFocusStateNode() == this) {
        information += " [Painted]";
    }
    information += ("_" + std::to_string(frameId));
    json->Put(information.c_str(), children);
    DumpFocusUieInJson(json);
    std::string jsonstr = DumpLog::GetInstance().FormatDumpInfo(json->ToString(), depth);
    auto prefix = DumpLog::GetInstance().GetPrefix(depth);
    DumpLog::GetInstance().PrintJson(prefix + jsonstr);
}

void FocusHub::DumpFocusUieInJson(std::unique_ptr<JsonValue>& json)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    if (pattern && frameNode->GetTag() == V2::UI_EXTENSION_COMPONENT_TAG) {
        pattern->DumpInfo(json);
    }
}
} // namespace OHOS::Ace::NG
