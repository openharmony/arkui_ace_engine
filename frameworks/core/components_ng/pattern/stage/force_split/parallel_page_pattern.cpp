/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"

#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

namespace OHOS::Ace::NG {
namespace {
bool IsVirtualStackBasedSplit(const PipelineContext* context)
{
    CHECK_NULL_RETURN(context, false);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    return forceSplitMgr->CanPushPageToPrimary();
}

bool IsSplitExitTransition(PageTransitionType type)
{
    return type == PageTransitionType::EXIT_PUSH || type == PageTransitionType::EXIT_POP;
}
}

void ParallelPagePattern::OnShow(bool isAppStateChange)
{
    if (IsShowOrHideAllowed()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "page show");
        PagePattern::OnShow(isAppStateChange);
    }
}

void ParallelPagePattern::OnHide(bool isAppStateChange)
{
    if (IsShowOrHideAllowed()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "page hide");
        PagePattern::OnHide(isAppStateChange);
    }
}

bool ParallelPagePattern::IsShowOrHideAllowed()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipeline->GetStageManager());
    CHECK_NULL_RETURN(stageManager, false);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    if (SystemProperties::GetDeviceType() != DeviceType::TABLET &&
        SystemProperties::GetDeviceType() != DeviceType::TWO_IN_ONE &&
        !forceSplitMgr->IsForceSplitEnable(true)) {
        return true;
    }
    return stageManager->IsInStageOperation();
}

void ParallelPagePattern::InitOnTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipeline->GetStageManager());
        CHECK_NULL_VOID(stageManager);
        if (IsVirtualStackBasedSplit(pipeline)) {
            stageManager->SetTouchedPrimaryColumnPage(
                stageManager->GetTopPrimaryColumnPage() == host ? host : nullptr);
            stageManager->SetTouchedSecondaryColumnPage(
                stageManager->GetTopSecondaryColumnPage() == host ? host : nullptr);
        }
        stageManager->SetHomePageTouched(pattern->GetPageType() == RouterPageType::HOME_PAGE);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ParallelPagePattern::RemoveOnTouchEvent()
{
    if (!touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    gesture->RemoveTouchEvent(touchListener_);
    touchListener_ = nullptr;
}

void ParallelPagePattern::PrepareSplitTransition(int32_t animationId, PageTransitionType type)
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    CaptureSplitTransitionVisualState();
    UpdateSplitTransitionState(type, SplitTransitionPhase::START);
    auto eventHub = host->GetEventHub<EventHub>();
    if (eventHub && (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) ||
        type == PageTransitionType::EXIT_POP)) {
        eventHub->SetEnabled(false);
    }
    SetPageInTransition(true);
    SetAnimationId(animationId);
}

void ParallelPagePattern::UpdateSplitTransitionState(PageTransitionType type, SplitTransitionPhase phase)
{
    splitTransitionType_ = type;
    splitTransitionPhase_ = phase;
}

void ParallelPagePattern::OnSplitTransitionStart(PageTransitionType type)
{
    HandleSplitTransitionStage(type, true);
}

void ParallelPagePattern::OnSplitTransitionEnd(PageTransitionType type)
{
    HandleSplitTransitionStage(type, false);
}

bool ParallelPagePattern::IsPageInStack()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_RETURN(stageManager, false);
    return stageManager->IsPageInStack(host);
}

bool ParallelPagePattern::OnSplitTransitionFinish(int32_t animationId, PageTransitionType type)
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_RETURN(host, false);
    if (!GetPageInTransition() || GetAnimationId() != animationId) {
        return false;
    }
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateTranslateInXY(OffsetF());
    }
    auto eventHub = host->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(true);
    }
    SetPageInTransition(false);
    splitTransitionType_ = PageTransitionType::NONE;
    splitTransitionPhase_ = SplitTransitionPhase::NONE;
    hasSplitTransitionVisualOffset_ = false;
    if (IsSplitExitTransition(type)) {
        if (type == PageTransitionType::EXIT_POP && !IsPageInStack()) {
            host->SetChildrenInDestroying();
            auto parent = host->GetParent();
            CHECK_NULL_RETURN(parent, false);
            auto context = host->GetContext();
            parent->RemoveChild(host);
            parent->RebuildRenderContextTree();
            CHECK_NULL_RETURN(context, true);
            auto stageManager = AceType::DynamicCast<ParallelStageManager>(context->GetStageManager());
            if (stageManager) {
                stageManager->OnStageNodeStructureChanged();
            }
            context->RequestFrame();
            return true;
        }
        ProcessHideState();
    }
    auto context = host->GetContext();
    if (context) {
        context->MarkNeedFlushMouseEvent();
    }
    return true;
}

void ParallelPagePattern::AbortSplitTransition()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateTranslateInXY(OffsetF());
    }
    auto eventHub = host->GetEventHub<EventHub>();
    if (eventHub) {
        eventHub->SetEnabled(true);
    }
    SetPageInTransition(false);
    splitTransitionType_ = PageTransitionType::NONE;
    splitTransitionPhase_ = SplitTransitionPhase::NONE;
    auto context = host->GetContext();
    if (context) {
        context->MarkNeedFlushMouseEvent();
    }
    hasSplitTransitionVisualOffset_ = false;
}

bool ParallelPagePattern::IsInSplitTransitionLayout() const
{
    return GetPageInTransition() && GetSplitTransitionColumnType() != ForceSplitPageColumnType::NONE;
}

ForceSplitPageColumnType ParallelPagePattern::GetSplitTransitionColumnType() const
{
    if (splitTransitionPhase_ == SplitTransitionPhase::NONE) {
        return ForceSplitPageColumnType::NONE;
    }
    switch (splitTransitionType_) {
        case PageTransitionType::EXIT_PUSH:
        case PageTransitionType::ENTER_POP:
            return ForceSplitPageColumnType::PRIMARY;
        case PageTransitionType::ENTER_PUSH:
        case PageTransitionType::EXIT_POP:
            return ForceSplitPageColumnType::SECONDARY;
        case PageTransitionType::MOVE_PUSH:
            return splitTransitionPhase_ == SplitTransitionPhase::START ? ForceSplitPageColumnType::SECONDARY
                                                                        : ForceSplitPageColumnType::PRIMARY;
        case PageTransitionType::MOVE_POP:
            return splitTransitionPhase_ == SplitTransitionPhase::START ? ForceSplitPageColumnType::PRIMARY
                                                                        : ForceSplitPageColumnType::SECONDARY;
        default:
            return ForceSplitPageColumnType::NONE;
    }
}

void ParallelPagePattern::CaptureSplitTransitionVisualState()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto renderContext = host->GetRenderContext();
    OffsetF currentVisualOffset = geometry->GetMarginFrameOffset();
    if (renderContext) {
        currentVisualOffset += renderContext->GetTranslateXYProperty();
    }
    splitTransitionVisualOffset_ = currentVisualOffset;
    hasSplitTransitionVisualOffset_ = true;
}

void ParallelPagePattern::HandleSplitTransitionStage(PageTransitionType type, bool isStart)
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto hostGeometry = host->GetGeometryNode();
    CHECK_NULL_VOID(hostGeometry);
    float translateX = 0.0f;
    const auto width = hostGeometry->GetFrameSize().Width();
    const bool rtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto calcPreservedVisualTranslate = [&]() -> float {
        if (!hasSplitTransitionVisualOffset_) {
            return 0.0f;
        }
        return splitTransitionVisualOffset_.GetX() - hostGeometry->GetMarginFrameOffset().GetX();
    };

    switch (type) {
        case PageTransitionType::ENTER_PUSH:
            if (isStart) {
                translateX = rtl ? -width : width;
            }
            break;
        case PageTransitionType::ENTER_POP:
            if (isStart) {
                translateX = rtl ? width : -width;
            }
            break;
        case PageTransitionType::EXIT_PUSH:
            if (isStart) {
                translateX = calcPreservedVisualTranslate();
                break;
            }
            if (!isStart) {
                translateX = rtl ? width : -width;
            }
            break;
        case PageTransitionType::EXIT_POP:
            if (isStart) {
                translateX = calcPreservedVisualTranslate();
                break;
            }
            if (!isStart) {
                translateX = rtl ? -width : width;
            }
            break;
        case PageTransitionType::MOVE_PUSH:
        case PageTransitionType::MOVE_POP:
            if (isStart) {
                translateX = calcPreservedVisualTranslate();
            }
            break;
        default:
            break;
    }
    renderContext->UpdateTranslateInXY(OffsetF(translateX, 0.0f));
}

void ParallelPagePattern::BeforeCreateLayoutWrapper()
{
    PagePattern::BeforeCreateLayoutWrapper();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    // SafeArea already applied to AppBar (AtomicServicePattern)
    if (context->GetInstallationFree()) {
        return;
    }
    RefPtr<FrameNode> stageNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(stageNode);
    auto stagePattern = stageNode->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    if (!stagePattern->GetIsSplit()) {
        return;
    }

    auto props = host->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    const auto& safeArea = props->GetSafeAreaInsets();
    CHECK_NULL_VOID(safeArea);
    SafeAreaInsets newSafeArea(*safeArea);
    if (IsVirtualStackBasedSplit(context)) {
        auto stageManager = AceType::DynamicCast<ParallelStageManager>(context->GetStageManager());
        CHECK_NULL_VOID(stageManager);
        auto primaryColumnPage = stageManager->GetTopPrimaryColumnPage();
        if (!primaryColumnPage) {
            return;
        }
        if (primaryColumnPage == host) {
            newSafeArea.right_.end = newSafeArea.right_.start;
        } else {
            newSafeArea.left_.start = newSafeArea.left_.end;
        }
    } else {
        auto homePage = stagePattern->GetHomePage();
        if (!homePage) {
            return;
        }
        if (type_ == RouterPageType::HOME_PAGE) {
            newSafeArea.right_.end = newSafeArea.right_.start;
        } else {
            newSafeArea.left_.start = newSafeArea.left_.end;
        }
    }
    props->UpdateSafeAreaInsets(newSafeArea);
}

void ParallelPagePattern::OnAttachToMainTree()
{
    if (type_ == RouterPageType::RELATED_PAGE || type_ == RouterPageType::PLACEHOLDER_PAGE) {
#if defined(ENABLE_SPLIT_MODE)
        if (!needFireObserver_) {
            return;
        }
#endif
        auto info = GetPageInfo();
        CHECK_NULL_VOID(info);
        // index of router page start from 1.
        info->SetPageIndex(-1);
        if (needNotifyRelatedPageAboutToAppear_) {
            needNotifyRelatedPageAboutToAppear_ = false;
            state_ = RouterPageState::ABOUT_TO_APPEAR;
            UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_, currentPageSize_);
        }
        return;
    }
    PagePattern::OnAttachToMainTree();
}

void ParallelPagePattern::NotifyAboutToDisappear()
{
    needNotifyRelatedPageAboutToAppear_ = true;
    state_ = RouterPageState::ABOUT_TO_DISAPPEAR;
    UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_, currentPageSize_);
}

void ParallelPagePattern::OnDetachFromMainTree()
{
    if (type_ == RouterPageType::RELATED_PAGE || type_ == RouterPageType::PLACEHOLDER_PAGE) {
        if (needNotifyRelatedPageAboutToDisappear_) {
            needNotifyRelatedPageAboutToDisappear_ = false;
            state_ = RouterPageState::ABOUT_TO_DISAPPEAR;
            UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_, currentPageSize_);
        }
        return;
    }
    PagePattern::OnDetachFromMainTree();
}
} // namespace OHOS::Ace::NG
