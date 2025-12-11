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

#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"

namespace OHOS::Ace::NG {

namespace {
constexpr Dimension DIVIDER_WIDTH = 1.0_vp;

void LogPrimaryChange(const WeakPtr<FrameNode>& prePage, const RefPtr<FrameNode>& newPage)
{
    auto prePrimaryPage = prePage.Upgrade();
    if (prePrimaryPage == newPage) {
        return;
    }
    bool hasPrePage = prePrimaryPage != nullptr;
    bool hasCurPage = newPage != nullptr;
    if (hasPrePage && hasCurPage) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "set PrimaryPage to new one");
        return;
    }
    if (hasPrePage) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "clear PrimaryPage");
    } else {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "set PrimaryPage");
    }
}
}

void ParallelStagePattern::SetPrimaryPage(const RefPtr<FrameNode>& pageNode)
{
    auto originNode = primaryPageNode_.Upgrade();
    if (originNode) {
        auto originPattern = originNode->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(originPattern);
        originPattern->RemoveOnTouchEvent();
    }
    if (pageNode) {
        auto pagePattern = pageNode->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->InitOnTouchEvent();
    }
    LogPrimaryChange(primaryPageNode_, pageNode);
    primaryPageNode_ = pageNode;
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    if (pageNode == nullptr) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "set primary page nullptr");
        if (hasDividerNode_) {
            hostNode->RemoveChild(dividerNode_);
            hasDividerNode_ = false;
        }
        return;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "update primary page: %{public}d", pageNode->GetId());
    if (mode_ != PageMode::SPLIT) {
        if (hasDividerNode_) {
            hostNode->RemoveChild(dividerNode_);
            hasDividerNode_ = false;
        }
        return;
    }
    if (!hasDividerNode_) {
        CreateDividerNodeIfNeeded();
        TAG_LOGD(AceLogTag::ACE_ROUTER, "add dividerNode after setPrimaryPage");
        hostNode->AddChild(dividerNode_, 0);
        hasDividerNode_ = true;
    }
}

void ParallelStagePattern::FireModeChangeCallback()
{
    if (modeChangeCallback_) {
        modeChangeCallback_();
    }
}

void ParallelStagePattern::OnAttachToMainTree()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto id = hostNode->GetId();
    pipeline->AddWindowStateChangedCallback(id);
    pipeline->AddWindowSizeChangeCallback(id);
    auto mgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(mgr);
    auto listener = [weakPattern = WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CalculateMode();
    };
    mgr->AddForceSplitStateListener(hostNode->GetId(), std::move(listener));
    CalculateMode();
}

bool ParallelStagePattern::CalculateMode()
{
    // calculate mode
    PageMode splitMode = PageMode::STACK;
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    auto pipelineContext = hostNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto forceSplitMgr = AceType::DynamicCast<ForceSplitManager>(pipelineContext->GetForceSplitManager());
    CHECK_NULL_RETURN(forceSplitMgr, false);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipelineContext->GetStageManager());
    CHECK_NULL_RETURN(stageManager, false);
    if (forceSplitMgr->IsForceSplitEnable(true) && !stageManager->IsTopFullScreenPage()) {
        auto container = Container::GetContainer(pipelineContext->GetInstanceId());
        CHECK_NULL_RETURN(container, false);
        bool isMainWindow = container->IsMainWindow();
        auto windowManager = pipelineContext->GetWindowManager();
        CHECK_NULL_RETURN(windowManager, false);
        auto windowMode = windowManager->GetWindowMode();
        bool isInSplitScreenMode =
            windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY;
        splitMode = (isMainWindow && !isInSplitScreenMode) ? PageMode::SPLIT : PageMode::STACK;
        TAG_LOGI(AceLogTag::ACE_ROUTER,
            "calc splitMode, isMainWindow: %{public}d, windowMode: %{public}d, isInSplitScreenMode: %{public}d, "
            "resultMode: %{public}d", isMainWindow, windowMode, isInSplitScreenMode, static_cast<int32_t>(splitMode));
    }
    if (mode_ == splitMode) {
        return false;
    }
    mode_ = splitMode;
    TAG_LOGI(AceLogTag::ACE_ROUTER, "update router mode: %{public}d", mode_);
    if (forceSplitMgr->IsForceSplitSupported(true)) {
        pipelineContext->SetIsCurrentInForceSplitMode(mode_ == PageMode::SPLIT);
    }
    if (mode_ == PageMode::SPLIT) {
        // show placeholder page
        auto primaryNode = primaryPageNode_.Upgrade();
        if (primaryNode) {
            auto primaryPattern = primaryNode->GetPattern<PagePattern>();
            if (primaryPattern) {
                primaryPattern->ResetPageTransitionEffect();
            }
        }
        // primary page is set, need to attach divider node
        if (!hasDividerNode_ && primaryNode) {
            CreateDividerNodeIfNeeded();
            TAG_LOGD(AceLogTag::ACE_ROUTER, "add dividerNode after changeMode");
            hostNode->AddChild(dividerNode_, 0);
            hasDividerNode_ = true;
        }
        // current page is free page, don't need to show divider node
        if (hasDividerNode_ && !primaryNode) {
            hostNode->RemoveChild(dividerNode_);
            hasDividerNode_ = false;
        }
    } else {
        if (hasDividerNode_) {
            hostNode->RemoveChild(dividerNode_);
            hasDividerNode_ = false;
        }
    }
    FireModeChangeCallback();
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

void ParallelStagePattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    CalculateMode();
}

void ParallelStagePattern::OnDirectionConfigurationUpdate()
{
    CalculateMode();
}

void ParallelStagePattern::OnDetachFromMainTree()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    do {
        CHECK_NULL_BREAK(relatedPage_);
        auto relatedPattern = relatedPage_->GetPattern<ParallelPagePattern>();
        CHECK_NULL_BREAK(relatedPattern);
        if (hostNode->GetChildIndex(relatedPage_) == -1) {
            // relatedPage has already detach from main tree.
            relatedPattern->NotifyAboutToDisappear();
            relatedPage_ = nullptr;
        } else {
            // relatedPage still exist on main tree, it will detach from main tree late.
            relatedPattern->SetNeedNotifyRelatedPageAboutToDisappear(true);
        }
    } while (false);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto id = hostNode->GetId();
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    auto mgr = pipeline->GetForceSplitManager();
    CHECK_NULL_VOID(mgr);
    mgr->RemoveForceSplitStateListener(id);
}

void ParallelStagePattern::CreateDividerNodeIfNeeded()
{
    if (dividerNode_) {
        return;
    }
    int32_t dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    dividerNode_ = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    auto dividerLayoutProperty = dividerNode_->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateStrokeWidth(DIVIDER_WIDTH);
    dividerLayoutProperty->UpdateVertical(true);
    // set divider color
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<NavigationBarTheme>();
    auto dividerRenderProperty = dividerNode_->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(Color::TRANSPARENT);
    // set background color can expand to safe area
    dividerNode_->GetRenderContext()->UpdateBackgroundColor(theme->GetNavigationDividerColor());
}

void ParallelStagePattern::OnWindowShow()
{
    if (windowStateChangeCallback_) {
        windowStateChangeCallback_(true);
    }
}

void ParallelStagePattern::OnWindowHide()
{
    if (windowStateChangeCallback_) {
        windowStateChangeCallback_(false);
    }
}
} // namespace OHOS::Ace::NG
