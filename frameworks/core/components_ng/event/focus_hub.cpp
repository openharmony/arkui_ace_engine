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
#include "base/utils/multi_thread.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/token_theme/token_theme_storage.h"

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
namespace {
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
        if (!uiChild || !uiChild->IsOnMainTree()) {
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

RefPtr<FocusHub> GetNextFocusNodeCustom(const RefPtr<FocusHub>& node, FocusReason focusReason)
{
    auto onGetNextFocusNodeFunc = node->GetOnGetNextFocusNodeFunc();
    CHECK_NULL_RETURN(onGetNextFocusNodeFunc, nullptr);
    auto focusManager = node->GetFocusManager();
    if (focusManager && focusManager->GetCurrentFocusEvent()) {
        auto focusEvent = focusManager->GetCurrentFocusEvent().value();
        auto nextFocusNode = onGetNextFocusNodeFunc(focusReason, focusEvent.intension);
        if (nextFocusNode) {
            TAG_LOGI(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d)
                " GetNextFocusNodeCustom by node %{public}s/" SEC_PLD(%{public}d),
                nextFocusNode->GetFrameName().c_str(), SEC_PARAM(nextFocusNode->GetFrameId()),
                node->GetFrameName().c_str(), SEC_PARAM(node->GetFrameId()));
            return nextFocusNode;
        }
    }
    return nullptr;
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

RefPtr<FrameNode> FocusState::GetFrameNode() const
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        auto eventHub = eventHub_.Upgrade();
        return eventHub ? eventHub->GetFrameNode() : nullptr;
    }
    return frameNode;
}

RefPtr<GeometryNode> FocusState::GetGeometryNode() const
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

RefPtr<FocusHub> FocusHub::GetFocusLeaf()
{
    auto leafFocusNode = AceType::Claim(this);
    auto nextFocusNode = leafFocusNode;
    while (nextFocusNode && nextFocusNode->IsFocusable()) {
        if (nextFocusNode->focusDepend_ == FocusDependence::SELF) {
            return nextFocusNode;
        }
        leafFocusNode = nextFocusNode;
        nextFocusNode = nextFocusNode->GetLastWeakFocusNode().Upgrade();
    }
    return leafFocusNode;
}

std::string FocusState::GetFrameName() const
{
    auto frameNode = GetFrameNode();
    return frameNode ? frameNode->GetTag() : "NULL";
}

int32_t FocusState::GetFrameId() const
{
    auto frameNode = GetFrameNode();
    return frameNode ? frameNode->GetId() : -1;
}

bool FocusHub::AnyChildFocusHub(const std::function<bool(const RefPtr<FocusHub>&)>& operation, bool isReverse)
{
    RefPtr<UINode> node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    return isReverse ? AnyOfUINode<true>(node, operation) : AnyOfUINode<false>(node, operation);
}

bool FocusHub::AllChildFocusHub(const std::function<void(const RefPtr<FocusHub>&)>& operation, bool isReverse)
{
    RefPtr<UINode> node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto wrappedOpration = [&operation](const RefPtr<FocusHub>& focusHub) {
        operation(focusHub);
        return false;
    };
    return isReverse ? AnyOfUINode<true>(node, wrappedOpration) : AnyOfUINode<false>(node, wrappedOpration);
}

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

bool FocusHub::HandleEvent(const NonPointerEvent& event)
{
    FocusEvent focusEvent(event);
    bool shiftTabPressed = focusEvent.intension == FocusIntension::SHIFT_TAB;
    bool leftArrowPressed = focusEvent.intension == FocusIntension::LEFT;
    hasBackwardMovement_ = (shiftTabPressed || leftArrowPressed);

    bool tabOnlyPressed = focusEvent.intension == FocusIntension::TAB;
    bool rightArrowPressed = focusEvent.intension == FocusIntension::RIGHT;
    hasForwardMovement_ = (tabOnlyPressed || rightArrowPressed);

    auto keyProcessingMode = static_cast<KeyProcessingMode>(GetKeyProcessingMode());
    if (keyProcessingMode == KeyProcessingMode::ANCESTOR_EVENT) {
        if (!OnFocusEvent(focusEvent)) {
            return HandleFocusNavigation(focusEvent);
        }
        return true;
    }
    return OnFocusEvent(focusEvent);
}

bool FocusHub::HandleFocusNavigation(const FocusEvent& event)
{
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode && lastFocusNode->IsCurrentFocus() && lastFocusNode->HandleFocusNavigation(event)) {
        return true;
    }
    return HandleFocusTravel(event);
}

bool FocusHub::HandleFocusTravel(const FocusEvent& event)
{
    if (event.intension == FocusIntension::NONE) {
        return false;
    }
    ACE_DCHECK(IsCurrentFocus());
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (!pipeline->GetIsFocusActive()) {
        return false;
    }
    if (pipeline->IsTabJustTriggerOnKeyEvent()) {
        ScrollToLastFocusIndex();
        return false;
    }
    auto manager = GetFocusManager();
    CHECK_NULL_RETURN(manager, false);
    manager->SetCurrentFocusEvent(event);
    auto ret = RequestNextFocusByKey(event);
    manager->ResetCurrentFocusEvent();
    return ret;
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
        if (IsTabStop()) {
            information += " TabStop:true";
        }
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
        if (IsTabStop()) {
            information += " TabStop:true";
        }
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

bool FocusHub::RequestFocusImmediately(FocusReason focusReason)
{
    auto frameNode = GetFrameNode();
    TAG_LOGI(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d)
        " RequestFocusImmediately isOnMainTree:%{public}d",
        GetFrameName().c_str(), SEC_PARAM(GetFrameId()), frameNode ? frameNode->IsOnMainTree() : -1);
    return RequestFocusImmediatelyInner(focusReason);
}

bool FocusHub::RequestFocusImmediatelyInner(FocusReason focusReason)
{
    auto context = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
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
        focusManager->SetRequestFocusResult(ERROR_CODE_NON_FOCUSABLE_ANCESTOR);
        return false;
    }

    currentFocus_ = true;
    focusReason_ = focusReason;
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
        parent->SwitchFocus(AceType::Claim(this), focusReason);
    }

    focusManager->UpdateCurrentFocus(Claim(this), SwitchingUpdateReason::ON_FOCUS_NODE);
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

void FocusHub::LostFocusToTabStop(const RefPtr<FocusHub>& focusNode)
{
    CHECK_NULL_VOID(focusNode);
    if (!focusNode->IsCurrentFocus()) {
        return;
    }
    auto focusedChild = focusNode->lastWeakFocusNode_.Upgrade();
    CHECK_NULL_VOID(focusedChild);
    FocusManager::FocusGuard guard(focusNode, SwitchingStartReason::LOST_FOCUS_TO_TABSTOP);
    focusedChild->LostFocus(BlurReason::BACK_TO_TABSTOP);
    focusNode->AllChildFocusHub([](const RefPtr<FocusHub>& child) {
        if (child) {
            child->ClearLastFocusNode();
        }
    });
    focusNode->ClearLastFocusNode();
}

void FocusHub::LostFocus(BlurReason reason)
{
    TAG_LOGD(AceLogTag::ACE_FOCUS, "Node %{public}s/ " SEC_PLD(%{public}d)
        " lost focus. Lost reason: %{public}d.",
        GetFrameName().c_str(), SEC_PARAM(GetFrameId()), reason);
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
    auto frameNode = GetFrameNode();
#ifdef ACE_STATIC
    FREE_NODE_CHECK(frameNode, RemoveSelf, reason);
#endif
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d) " remove self focus.",
            GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
    }
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
    if (!parentFocusable_) {
        CloseChildFocusView();
    }
}

void FocusHub::CloseChildFocusView()
{
    auto manager = GetFocusManager();
    CHECK_NULL_VOID(manager);
    auto viewList = manager->GetWeakFocusViewList();
    for (auto& view : viewList) {
        auto focusView = view.Upgrade();
        if (!focusView) {
            continue;
        }
        auto focusViewHub = focusView->GetFocusHub();
        if (!focusViewHub) {
            continue;
        }
        if (focusViewHub->IsChildOf(Claim(this))) {
            focusView->FocusViewClose();
        }
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
            TAG_LOGD(AceLogTag::ACE_FOCUS, "Set node %{public}s/ " SEC_PLD(%{public}d)
                " to be unfocusable", GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
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
        focusManager->SetRequestFocusResult(ERROR_CODE_NON_EXIST);
        return false;
    }
    if (!focusable_) {
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_FOCUSABLE);
        focusManager->SetRequestFocusResult(ERROR_CODE_NON_FOCUSABLE);
        return false;
    }
    if (!parentFocusable_) {
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_FOCUSABLE_ANCESTOR);
        focusManager->SetRequestFocusResult(ERROR_CODE_NON_FOCUSABLE_ANCESTOR);
        return false;
    }
    return true;
}

bool FocusHub::IsEnabled() const
{
    auto frameNode = frameNode_.Upgrade();
    auto eventHub = frameNode ? frameNode->GetEventHub<EventHub>() : eventHub_.Upgrade();
    return eventHub ? eventHub->IsEnabled() : true;
}

void FocusHub::SetEnabled(bool enabled)
{
    if (!enabled) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_FOCUS, "Set node %{public}s/" SEC_PLD(%{public}d)
                " to be disabled", GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
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
            TAG_LOGD(AceLogTag::ACE_FOCUS, "Set node %{public}s/" SEC_PLD(%{public}d)
                " to be unShown", GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
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
                TAG_LOGI(AceLogTag::ACE_FOCUS, "node %{public}s/" SEC_PLD(%{public}d) " touch to be focused",
                    focusHub->GetFrameName().c_str(), SEC_PARAM(focusHub->GetFrameId()));
                focusHub->RequestFocusImmediatelyInner(FocusReason::FOCUS_TOUCH);
            }
        };
        focusOnTouchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    }
    gesture->AddTouchEvent(focusOnTouchListener_);
}

void FocusHub::LostChildFocusToSelf()
{
    if (!IsCurrentFocus()) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Node need to lost focus: %{public}s/%{public}d is not on focusing.",
            GetFrameName().c_str(), GetFrameId());
        return;
    }
    auto focusedChild = lastWeakFocusNode_.Upgrade();
    CHECK_NULL_VOID(focusedChild);
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Node: %{public}s/%{public}d need to lost focus of item %{public}s/%{public}d.",
        GetFrameName().c_str(), GetFrameId(), focusedChild->GetFrameName().c_str(), focusedChild->GetFrameId());
    if (focusDepend_ == FocusDependence::AUTO) {
        focusDepend_ = FocusDependence::SELF;
    }
    focusedChild->LostFocus();
}

bool FocusHub::IsFocusStepKey(KeyCode keyCode)
{
    return keyCode == KeyCode::KEY_TAB || keyCode == KeyCode::KEY_DPAD_LEFT || keyCode == KeyCode::KEY_DPAD_RIGHT ||
           keyCode == KeyCode::KEY_DPAD_UP || keyCode == KeyCode::KEY_DPAD_DOWN;
}

bool FocusHub::GetNextFocusByStep(const KeyEvent& keyEvent)
{
    TAG_LOGI(AceLogTag::ACE_FOCUS, "node: %{public}s/%{public}d request next focus by step", GetFrameName().c_str(),
        GetFrameId());
    FocusEvent event(keyEvent);
    return RequestNextFocusByKey(event);
}

bool FocusHub::RequestUserNextFocus(const FocusEvent& event)
{
    CHECK_EQUAL_RETURN(nextStep_.empty(), true, false);
    int32_t key = static_cast<int32_t>(event.intension);
    auto item = nextStep_.find(key);
    if (item  == nextStep_.end()) {
        return false;
    }
    const auto& input = item->second;
    RefPtr<FrameNode> frameNode = nullptr;
    if (std::holds_alternative<std::string>(input)) {
        frameNode = Inspector::GetFrameNodeByKey(std::get<std::string>(input));
    } else if (std::holds_alternative<WeakPtr<AceType>>(input)) {
        frameNode = AceType::DynamicCast<FrameNode>(std::get<WeakPtr<AceType>>(input).Upgrade());
    }
    if (frameNode == nullptr) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Cannot find user specified nextFocus.");
        return false;
    }
    auto focusHub = frameNode->GetFocusHub();
    return focusHub->RequestFocusImmediately();
}

bool FocusHub::RequestNextFocusByKey(const FocusEvent& event)
{
    CHECK_EQUAL_RETURN(RequestUserNextFocus(event), true, true);

    switch (event.intension) {
        case FocusIntension::TAB:
        case FocusIntension::SHIFT_TAB:
            return RequestNextFocusOfKeyTab(event);
        case FocusIntension::UP:
            return RequestNextFocus(FocusStep::UP);
        case FocusIntension::DOWN:
            return RequestNextFocus(FocusStep::DOWN);
        case FocusIntension::LEFT:
            return RequestNextFocus(FocusStep::LEFT);
        case FocusIntension::RIGHT:
            return RequestNextFocus(FocusStep::RIGHT);
        case FocusIntension::SELECT:
            return RequestNextFocusOfKeyEnter();
        case FocusIntension::ESC:
            return RequestNextFocusOfKeyEsc();
        case FocusIntension::HOME:
            return RequestNextFocus(FocusStep::LEFT_END) || RequestNextFocus(FocusStep::UP_END);
        case FocusIntension::END:
            return RequestNextFocus(FocusStep::RIGHT_END) || RequestNextFocus(FocusStep::DOWN_END);
        default:
            return false;
    }
}

bool FocusHub::RequestNextFocusOfKeyTab(const FocusEvent& event)
{
    if (IsInFocusGroup()) {
        return false;
    }
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
    if (event.intension == FocusIntension::TAB) {
        context->SetIsFocusingByTab(true);
        ret = RequestNextFocus(FocusStep::TAB);
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
    } else if ((event.intension == FocusIntension::SHIFT_TAB)) {
        context->SetIsFocusingByTab(true);
        ret = RequestNextFocus(FocusStep::SHIFT_TAB);
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

bool FocusHub::RequestNextFocusOfKeyEnter()
{
    if (IsTabStop() && focusType_ == FocusType::SCOPE) {
        isSwitchByEnter_ = true;
        focusReason_ = FocusReason::FOCUS_TRAVEL;
        OnFocusScope(true);
        return true;
    }
    return false;
}

bool FocusHub::RequestNextFocusOfKeyEsc()
{
    auto curFocusView = FocusView::GetCurrentFocusView();
    CHECK_NULL_RETURN(curFocusView, false);
    auto curFocusViewHub = curFocusView->GetFocusHub();
    CHECK_NULL_RETURN(curFocusViewHub, false);
    auto lastViewFocusHub = curFocusViewHub->GetFocusLeaf();
    CHECK_NULL_RETURN(lastViewFocusHub, false);
    auto viewRootScope = curFocusView->GetViewRootScope();
    CHECK_NULL_RETURN(viewRootScope, false);
    if (lastViewFocusHub != this || viewRootScope == this || curFocusViewHub == this) {
        return false;
    }
    auto parent = GetParentFocusHubWithBoundary();
    CHECK_NULL_RETURN(parent, false);
    while (parent) {
        if (parent->IsTabStop()) {
            LostFocusToTabStop(parent);
            return true;
        }
        if (parent == viewRootScope) {
            break;
        }
        parent = parent->GetParentFocusHubWithBoundary();
    }
    return false;
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
    auto context = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Node: %{public}s/" SEC_PLD(%{public}d) " RequestFocus.",
        GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
    context->AddDirtyFocus(GetFrameNode());
}

bool FocusHub::RequestNextFocus(FocusStep moveStep)
{
    if (!CalculatePosition()) {
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Request next focus on node: %{public}s/" SEC_PLD(%{public}d)
        " by step: %{public}d.",
        GetFrameName().c_str(), SEC_PARAM(GetFrameId()), moveStep);
    SetScopeFocusAlgorithm();
    if (!focusAlgorithm_.getNextFocusNode) {
        return RequestNextFocusByDefaultAlgorithm(moveStep, GetRect());
    }
    return RequestNextFocusByCustomAlgorithm(moveStep, GetRect());
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
            "Request next focus by project area. Next focus node is %{public}s/" SEC_PLD(%{public}d)
            ". Return %{public}d",
            nextFocusHub->GetFrameName().c_str(), SEC_PARAM(nextFocusHub->GetFrameId()), ret);
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
    auto success = focusAlgorithm_.getNextFocusNode(moveStep, lastWeakFocusNode_, nextFocusHubWeak);
    auto nextFocusHub = nextFocusHubWeak.Upgrade();
    if (!success || !nextFocusHub) {
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
    auto foundChild = GetHeadOrTailChild(isHead);
    if (foundChild) {
        return foundChild->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL);
    } else {
        return false;
    }
}

void FocusHub::SwitchFocus(const RefPtr<FocusHub>& focusNode, FocusReason focusReason)
{
    if (focusType_ != FocusType::SCOPE) {
        TAG_LOGW(AceLogTag::ACE_FOCUS, "SwitchFocus: parent focus node is not a scope!");
        return;
    }

    auto focusNodeNeedBlur = lastWeakFocusNode_.Upgrade();
    lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusNode));
    TAG_LOGD(AceLogTag::ACE_FOCUS, "Switch focus from %{public}s/"
        SEC_PLD(%{public}d) " to %{public}s/" SEC_PLD(%{public}d),
        focusNodeNeedBlur ? focusNodeNeedBlur->GetFrameName().c_str() : "NULL",
        SEC_PARAM(focusNodeNeedBlur ? focusNodeNeedBlur->GetFrameId() : -1),
        focusNode->GetFrameName().c_str(),
        SEC_PARAM(focusNode->GetFrameId()));
    if (IsCurrentFocus()) {
        auto focusManger = GetFocusManager();
        CHECK_NULL_VOID(focusManger);
        focusManger->UpdateCurrentFocus(Claim(this), SwitchingUpdateReason::SWITCH_FOCUS);
        if (focusNodeNeedBlur && focusNodeNeedBlur != focusNode) {
            focusNodeNeedBlur->LostFocus();
        }
    } else {
        RequestFocusImmediatelyInner(focusReason);
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
        return focusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL);
    }
    if (IsFocusStepTab(step) && focusNode->AcceptFocusOfSpecifyChild(step)) {
        return focusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL);
    }
    if (!IsFocusStepTab(step) && step != FocusStep::NONE && focusNode->GetIsFocusGroup() &&
        !focusNode->IsNestingFocusGroup()) {
        return focusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL);
    }
    if (rect.IsValid()) {
        RectF childRect;
        if (!CalculateRect(focusNode, childRect) ||
            !focusNode->AcceptFocusByRectOfLastFocus(rect - childRect.GetOffset())) {
            return false;
        }
    }
    return focusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL);
}

void FocusHub::ClearLastFocusNode()
{
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode) {
        lastFocusNode->ClearLastFocusNode();
        lastFocusNode->SetCurrentFocus(false);
        lastWeakFocusNode_ = nullptr;
    }
}

bool FocusHub::CalculatePosition()
{
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    CHECK_NULL_RETURN(lastFocusNode, false);
    if (!lastFocusNode->IsCurrentFocus()) {
        return false;
    }

    RectF childRect;
    if (!CalculateRect(lastFocusNode, childRect)) {
        return false;
    }

    // relative position and width/height need to be calculated.
    // 1. lastFocusNode is node
    // 2. lastFocusNode do not have focusing child
    if (lastFocusNode->IsChild() || !lastFocusNode->IsLastWeakNodeFocused()) {
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
        OnFocusNode(false);
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

void FocusHub::HandleAccessibilityEvent()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    ACE_EVENT_SCOPED_TRACE(
        "HandleFocusAccessibilityEvent Node:[%s][%d]", frameNode->GetTag().c_str(), frameNode->GetId());
    frameNode->OnAccessibilityEvent(AccessibilityEventType::FOCUS);
}

void FocusHub::OnFocusNode(bool currentHasFocused)
{
    if (currentHasFocused || !IsCurrentFocus()) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d) " focus",
        GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
    if (onFocusInternal_) {
        ACE_EVENT_SCOPED_TRACE("HandleFocusEventInternal Node[%s][%d]", GetFrameName().c_str(), GetFrameId());
        onFocusInternal_(focusReason_);
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
        auto onJSFrameNodeFocusCallback = focusHub->GetJSFrameNodeOnFocusCallback();
        if (onJSFrameNodeFocusCallback) {
            onJSFrameNodeFocusCallback();
        }
    });
    auto parentFocusHub = GetParentFocusHub();
    if (parentFocusHub) {
        parentFocusHub->SetLastFocusNodeIndex(AceType::Claim(this));
    }
    HandleAccessibilityEvent();

    pipeline->RequestFrame();
}

void FocusHub::OnBlurNode()
{
    TAG_LOGD(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d) " blur by %{public}d",
        GetFrameName().c_str(), SEC_PARAM(GetFrameId()), blurReason_);
    if (onBlurInternal_) {
        ACE_EVENT_SCOPED_TRACE("HandleBlurEventInternal Node[%s][%d]", GetFrameName().c_str(), GetFrameId());
        onBlurInternal_();
    }
    if (onBlurReasonInternal_) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d) "trigger onBlurReasonInternal by %{public}d",
            GetFrameName().c_str(), SEC_PARAM(GetFrameId()), blurReason_);
        ACE_EVENT_SCOPED_TRACE("HandleBlurReasonEventInternal Node[%s][%d]", GetFrameName().c_str(), GetFrameId());
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
        auto onJSFrameNodeBlurCallback_ = focusHub->GetJSFrameNodeOnBlurCallback();
        if (onJSFrameNodeBlurCallback_) {
            onJSFrameNodeBlurCallback_();
        }
    });
    if (blurReason_ != BlurReason::FRAME_DESTROY) {
        ClearFocusState();
    } else {
        ClearFocusState(true, false);
    }

    pipeline->RequestFrame();
}

void FocusHub::CheckFocusStateStyle(bool onFocus)
{
    auto frameNode = frameNode_.Upgrade();
    auto eventHub = frameNode ? frameNode->GetEventHub<EventHub>() : eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    if (onFocus) {
        eventHub->UpdateCurrentUIState(UI_STATE_FOCUSED);
    } else {
        eventHub->ResetCurrentUIState(UI_STATE_FOCUSED);
    }
}

bool FocusHub::HasFocusStateStyle()
{
    auto frameNode = frameNode_.Upgrade();
    auto eventHub = frameNode ? frameNode->GetEventHub<EventHub>() : eventHub_.Upgrade();
    CHECK_NULL_RETURN(eventHub, false);
    return eventHub->HasStateStyle(UI_STATE_FOCUSED);
}

bool FocusHub::IsLeafFocusScope()
{
    auto focusManager = GetFocusManager();
    CHECK_NULL_RETURN(focusManager, false);
    if (IsTabStop()) {
        if (isSwitchByEnter_) {
            if (focusDepend_ == FocusDependence::SELF) {
                focusDepend_ = FocusDependence::AUTO;
            }
            isSwitchByEnter_ = false;
            return false;
        }
        focusManager->UpdateSwitchingEndReason(SwitchingEndReason::TAB_STOP);
        return true;
    }
    if (focusDepend_ == FocusDependence::SELF) {
        focusManager->UpdateSwitchingEndReason(SwitchingEndReason::DEPENDENCE_SELF);
        return true;
    }
    return false;
}

void FocusHub::OnFocusScope(bool currentHasFocused)
{
    if (IsLeafFocusScope()) {
        OnFocusNode(currentHasFocused);
        return;
    }

    std::list<RefPtr<FocusHub>> focusNodes;
    auto itLastFocusNode = FlushChildrenFocusHub(focusNodes);
    bool isAnyChildFocusable = focusNodes.empty() ? false : std::any_of(focusNodes.begin(), focusNodes.end(),
        [](const RefPtr<FocusHub>& focusNode) { return focusNode->IsFocusable(); });

    if (focusDepend_ == FocusDependence::AUTO && !isAnyChildFocusable) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Node(%{public}s/%{public}d) has no focusable child.", GetFrameName().c_str(),
            GetFrameId());
        lastWeakFocusNode_ = nullptr;
        OnFocusNode(currentHasFocused);
        auto focusManager = GetFocusManager();
        CHECK_NULL_VOID(focusManager);
        focusManager->UpdateSwitchingEndReason(SwitchingEndReason::NO_FOCUSABLE_CHILD);
        return;
    }

    if ((focusDepend_ == FocusDependence::AUTO || focusDepend_ == FocusDependence::CHILD) && isAnyChildFocusable) {
        auto itFocusNode = itLastFocusNode;
        if (RequestFocusByPriorityInScope()) {
            OnFocusNode(currentHasFocused);
            return;
        }

        auto nextFocusNode = GetNextFocusNodeCustom(AceType::Claim(this), focusReason_);
        if (nextFocusNode && nextFocusNode->RequestFocusImmediately(focusReason_)) {
            OnFocusNode(currentHasFocused);
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
            if ((*itLastFocusNode)->RequestFocusImmediatelyInner(focusReason_)) {
                OnFocusNode(currentHasFocused);
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
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
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
        return;
    }
    if (HasPaintColor()) {
        paintColor = GetPaintColor();
        return;
    }
    auto themeScopeId = frameNode->GetThemeScopeId();
    auto tokenTheme = TokenThemeStorage::GetInstance()->GetTheme(themeScopeId);
    auto themeColors = tokenTheme ? tokenTheme->Colors() : nullptr;
    if (themeColors) {
        paintColor = themeColors->InteractiveFocus();
        return;
    }
    paintColor = appTheme->GetFocusColor();
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
        renderContext->PaintFocusState(GetPaintRect(), paintColor, paintWidth, false, appTheme->IsFocusBoxGlow());
        return true;
    }

    Dimension focusPaddingVp;
    GetPaintPaddingVp(focusPaddingVp);
    if (HasPaintRect()) {
        renderContext->PaintFocusState(GetPaintRect(),
                                       focusPaddingVp,
                                       paintColor,
                                       paintWidth,
                                       {false, appTheme->IsFocusBoxGlow()});
    } else {
        renderContext->PaintFocusState(focusPaddingVp,
                                       paintColor,
                                       paintWidth,
                                       appTheme->IsFocusBoxGlow());
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
        focusManager->SetLastFocusStateNode(AceType::Claim(this));
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
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    GetPaintColorFromBox(paintColor);
    Dimension paintWidth;
    GetPaintWidthFromBox(paintWidth);
    renderContext->ClearFocusState();
    if (NEAR_ZERO(paintWidth.Value())) {
        return true;
    }
    if (box_.paintStyle_ && box_.paintStyle_->margin) {
        Dimension focusPaddingVp = box_.paintStyle_->margin.value();
        renderContext->PaintFocusState(focusPaddingVp, paintColor, paintWidth, appTheme->IsFocusBoxGlow());
    } else {
        renderContext->PaintFocusState(paintRect, paintColor, paintWidth, false, appTheme->IsFocusBoxGlow());
    }
    return true;
}

void FocusHub::ClearFocusState(bool isNeedStateStyles, bool isNeedClearCallBack)
{
    if (isNeedStateStyles) {
        // check focus state style.
        CheckFocusStateStyle(false);
    }
    if (isNeedClearCallBack && onClearFocusStateCallback_) {
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

    auto operation = [&lastfocus = lastWeakFocusNode_, step](const RefPtr<FocusHub>& focusHub) {
        if (focusHub && focusHub->AcceptFocusOfSpecifyChild(step)) {
            lastfocus = focusHub;
            return true;
        }
        return false;
    };
    bool canChildBeFocused = false;
    if (step == FocusStep::TAB) {
        canChildBeFocused = AnyChildFocusHub(operation, false);
    } else if (step == FocusStep::SHIFT_TAB) {
        canChildBeFocused = AnyChildFocusHub(operation, true);
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
    double minVal = std::numeric_limits<double>::max();
    AllChildFocusHub([this, &rect, &offset, &newFocusNode, &minVal](const RefPtr<FocusHub>& child) {
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
    auto parent = frameNode->GetAncestorNodeOfFrame(true);
    while (parent && parent != GetFrameNode()) {
        rect += parent->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
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
    TAG_LOGI(AceLogTag::ACE_FOCUS, "Move focus to tab index node %{public}d: %{public}s/" SEC_PLD(%{public}d),
        tabNodeIdx, nodeNeedToFocus->GetFrameName().c_str(), SEC_PARAM(nodeNeedToFocus->GetFrameId()));
    if (nodeNeedToFocus->GetFocusType() == FocusType::SCOPE && !nodeNeedToFocus->IsDefaultGroupHasFocused()) {
        auto defaultFocusNode = nodeNeedToFocus->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT);
        if (defaultFocusNode) {
            if (!defaultFocusNode->IsFocusableWholePath()) {
                TAG_LOGI(AceLogTag::ACE_FOCUS, "node(%{public}d) is not focusable", tabNodeIdx);
                return false;
            }
            nodeNeedToFocus->SetIsDefaultGroupHasFocused(true);
            if (defaultFocusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL)) {
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
    if (nodeNeedToFocus->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL)) {
        auto curFocusHub = Claim(this);
        while (curFocusHub) {
            curFocusHub->lastTabIndexNodeId_ = nodeIdNeedToFocus;
            curFocusHub = curFocusHub->GetParentFocusHub();
        }
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
    AnyChildFocusHub(
        [&focusView](const RefPtr<FocusHub>& childFocusHub) {
            if (!childFocusHub) {
                return false;
            }
            focusView = childFocusHub->GetFirstChildFocusView();
            return focusView ? true : false;
        }, true);
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
    auto scrollFunc = scrollAbility.scrollFunc;
    auto scrollAxis = scrollAbility.axis;
    if (!scrollFunc || scrollAxis == Axis::NONE) {
        return false;
    }
    MoveOffsetParam param {
        scrollAxis == Axis::VERTICAL,
        scrollAbility.contentStartOffset,
        scrollAbility.contentEndOffset,
        false
    };
    auto moveOffset = ScrollableUtils::GetMoveOffset(parentFrameNode, curFrameNode, param);
    if (!NearZero(moveOffset)) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Scroll offset: %{public}f on %{public}s/%{public}d, axis: %{public}d",
            moveOffset, parentFrameNode->GetTag().c_str(), parentFrameNode->GetId(), scrollAxis);
        auto ret = scrollFunc(parentPattern->IsReverse() ? -moveOffset : moveOffset);
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
        TAG_LOGI(AceLogTag::ACE_FOCUS, "Request focus id can not found.");
        focusManager->TriggerRequestFocusCallback(RequestFocusResult::NON_EXIST);
        return false;
    }
    auto result = true;
    if ((isSyncRequest && !focusNode->IsSyncRequestFocusable()) ||
        (!isSyncRequest && !focusNode->IsFocusable())) {
        result = false;
    }
    TAG_LOGI(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d) "Request focus %{public}s by id",
        focusNode->GetFrameName().c_str(), SEC_PARAM(focusNode->GetFrameId()), isSyncRequest ? "sync" : "async");
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
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto isDirectionKeyDown = GetDirectionalKeyFocus() && event.IsDirectionalKey() &&
        event.action == KeyAction::DOWN;
    auto isTabDown = event.code == KeyCode::KEY_TAB && event.action == KeyAction::DOWN;
    if (!isDirectionKeyDown && !isTabDown) {
        return false;
    }

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
    TAG_LOGD(AceLogTag::ACE_FOCUS, "Current focus node is %{public}s/" SEC_PLD(%{public}d)
        " Next focus node is %{public}s/" SEC_PLD(%{public}d) ". Min distance is %{public}f.",
        GetFrameName().c_str(), SEC_PARAM(GetFrameId()),
        nextNode ? nextNode->GetFrameName().c_str() : "NULL",
        SEC_PARAM(nextNode ? nextNode->GetFrameId() : -1), resDistance);
    return nextNode;
}

bool FocusHub::UpdateFocusView()
{
    CHECK_NULL_RETURN(IsCurrentFocus(), false);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto focusView = frameNode->GetPattern<FocusView>();
    if (!focusView) {
        if (frameNode->IsOnMainTree()) {
            auto focusManager = GetFocusManager();
            CHECK_NULL_RETURN(focusManager, false);
            focusManager->FlushFocusView();
        }
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
        TAG_LOGD(AceLogTag::ACE_FOCUS, "UpdateFocusView by node %{public}s/" SEC_PLD(%{public}d),
            GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
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

bool FocusHub::IsChildOf(const RefPtr<FocusHub>& parentFocusHub)
{
    auto parent = GetParentFocusHub();
    while (parent) {
        if (parent == parentFocusHub) {
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
    auto newFocusNodeWeak = GetChildPriorfocusNode(focusScopeId_);
    auto newFocusNode = newFocusNodeWeak.Upgrade();
    if (newFocusNode && newFocusNode->GetFocusPriority() == FocusPriority::PREVIOUS
        && newFocusNode == lastFocusNode) {
        return lastFocusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL);
    }
    if (!lastFocusNode) {
        if (!newFocusNode) {
            return false;
        }
        newFocusNode->SetLastWeakFocusNodeWholeScope(focusScopeId_);
        lastFocusNode = lastWeakFocusNode_.Upgrade();
        if (lastFocusNode && lastFocusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL)) {
            return true;
        }
        return false;
    }
    if (GetIsFocusGroup() && !IsNestingFocusGroup()) {
        SetLastWeakFocusNodeToPreviousNode();
        lastFocusNode = lastWeakFocusNode_.Upgrade();
        if (lastFocusNode && lastFocusNode->RequestFocusImmediatelyInner(FocusReason::FOCUS_TRAVEL)) {
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
    bool tabStop = false;
    if (hub) {
        enabled = hub->IsEnabled();
        defaultFocus = hub->IsDefaultFocus();
        groupDefaultFocus = hub->IsDefaultGroupFocus();
        focusOnTouch = hub->IsFocusOnTouch().value_or(false);
        tabIndex = hub->GetTabIndex();
        focusBox = FocusBox::ToJsonValue(hub->box_);
        tabStop = hub->IsTabStop();
    }
    json->PutExtAttr("enabled", enabled, filter);
    json->PutExtAttr("defaultFocus", defaultFocus, filter);
    json->PutExtAttr("groupDefaultFocus", groupDefaultFocus, filter);
    json->PutExtAttr("focusOnTouch", focusOnTouch, filter);
    json->PutExtAttr("tabIndex", tabIndex, filter);
    json->PutExtAttr("focusBox", focusBox, filter);
    json->PutExtAttr("tabStop", tabStop, filter);
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
    if (IsTabStop()) {
        children->Put("TabStop", IsTabStop());
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
    if (IsTabStop()) {
        children->Put("TabStop", IsTabStop());
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

bool FocusHub::IsLastWeakNodeFocused() const
{
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    CHECK_NULL_RETURN(lastFocusNode, false);
    return lastFocusNode->IsCurrentFocus();
}

RefPtr<FocusHub> FocusHub::GetHeadOrTailChild(bool isHead)
{
    auto curFrameNode = GetFrameNode();
    auto curFocusHub = curFrameNode->GetFocusHub();
    if (!IsFocusableWholePath()) {
        return nullptr;
    }
    // focus moves within current scope
    if (IsCurrentFocus() && !IsAllowedLoop()) {
        return nullptr;
    }
    if (GetIsFocusGroup() && !IsNestingFocusGroup()) {
        return curFocusHub;
    }
    if (focusType_ != FocusType::SCOPE || (focusType_ == FocusType::SCOPE && focusDepend_ == FocusDependence::SELF)) {
        return curFocusHub;
    }

    if (IsTabStop()) {
        std::list<RefPtr<FocusHub>> focusNodes;
        auto itLastFocusNode = FlushChildrenFocusHub(focusNodes);
        // A(Tabstop)->B(TabStop)->C
        //              `--------->D
        // if D is the last leaf node, then press the Tab key to shift the focus to C.
        if (!(IsCurrentFocus() && itLastFocusNode != focusNodes.end() && (*itLastFocusNode)->IsCurrentFocus())) {
            return curFocusHub;
        }
    }

    auto curPattern = curFrameNode ? curFrameNode->GetPattern<ScrollablePattern>() : nullptr;
    auto scrollIndexAbility = curPattern ? curPattern->GetScrollIndexAbility() : nullptr;
    if (scrollIndexAbility) {
        scrollIndexAbility(isHead ? FocusHub::SCROLL_TO_HEAD : FocusHub::SCROLL_TO_TAIL);
        auto node = GetFrameNode();
        CHECK_NULL_RETURN(node, nullptr);
        auto pipeline = node->GetContextRefPtr();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }

    bool canChildBeFocused = false;
    RefPtr<FocusHub> foundNode = nullptr;
    canChildBeFocused = AnyChildFocusHub(
        [isHead, &foundNode](const RefPtr<FocusHub>& node) {
            auto nextFocusNode = GetNextFocusNodeCustom(node, FocusReason::FOCUS_TRAVEL);
            if (nextFocusNode) {
                foundNode = nextFocusNode->GetHeadOrTailChild(isHead);
                if (foundNode) {
                    return true;
                }
            }
            foundNode = node->GetHeadOrTailChild(isHead);
            return foundNode != nullptr;
        }, !isHead);
    if (focusDepend_ == FocusDependence::CHILD) {
        return foundNode;
    }
    if (focusDepend_ == FocusDependence::AUTO) {
        if (!canChildBeFocused) {
            return curFocusHub;
        }
        return foundNode;
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
