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
constexpr Dimension MAX_WINDOW_WIDTH = 600.0_vp;
constexpr Dimension DIVIDER_WIDTH = 1.0_vp;

const char* DeviceOrientationToString(DeviceOrientation ori)
{
    switch (ori) {
        case DeviceOrientation::PORTRAIT:
            return "PORTRAIT";
        case DeviceOrientation::LANDSCAPE:
            return "LANDSCAPE";
        case DeviceOrientation::ORIENTATION_UNDEFINED:
            return "ORIENTATION_UNDEFINED";
        default:
            return "UNKNOWN";
    }
}

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
    pipeline->AddWindowSizeChangeCallback(id);
    pipeline->AddWindowStateChangedCallback(id);
    CalculateMode(pipeline->GetRootWidth());
}

bool ParallelStagePattern::CalculateMode(double width)
{
    // calculate mode
    PageMode splitMode = PageMode::STACK;
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    auto pipelineContext = hostNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_RETURN(stageManager, false);
    if (stageManager->GetForceSplitEnable()) {
        auto thresholdWidth = MAX_WINDOW_WIDTH.ConvertToPx();
        auto dipScale = pipelineContext->GetDipScale();
        bool ignoreOrientation = stageManager->GetIgnoreOrientation();
        auto orientation = SystemProperties::GetDeviceOrientation();
        bool isInSplitScreenMode = false;
        auto windowManager = pipelineContext->GetWindowManager();
        CHECK_NULL_RETURN(windowManager, false);
        auto windowMode = windowManager->GetWindowMode();
        if (windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
            isInSplitScreenMode = true;
        }
        splitMode = ((ignoreOrientation || orientation == DeviceOrientation::LANDSCAPE) &&
            thresholdWidth < width && !isInSplitScreenMode) ? PageMode::SPLIT : PageMode::STACK;
        TAG_LOGI(AceLogTag::ACE_ROUTER,
            "calc splitMode, ignoreOrientation: %{public}d, orientation: %{public}s, dipScale: %{public}f, "
            "thresholdWidth: %{public}f, curWidth: %{public}f, windowMode: %{public}d, isInSplitScreenMode: "
            "%{public}d, resultMode: %{public}d", ignoreOrientation, DeviceOrientationToString(orientation), dipScale,
            thresholdWidth, width, windowMode, static_cast<int32_t>(isInSplitScreenMode),
            static_cast<int32_t>(splitMode));
    }
    if (mode_ == splitMode) {
        return false;
    }
    mode_ = splitMode;
    TAG_LOGI(AceLogTag::ACE_ROUTER, "update router mode: %{public}d", mode_);
    if (stageManager->GetDetectPrimaryPageEnable()) {
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
    CalculateMode(width);
}

void ParallelStagePattern::OnDirectionConfigurationUpdate()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    CalculateMode(pipeline->GetRootWidth());
}

void ParallelStagePattern::OnDetachFromMainTree()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto id = hostNode->GetId();
    pipeline->RemoveWindowSizeChangeCallback(id);
    pipeline->RemoveWindowStateChangedCallback(id);
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

void ParallelStagePattern::OnForceSplitConfigUpdate()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    CalculateMode(pipeline->GetRootWidth());
}
} // namespace OHOS::Ace::NG
