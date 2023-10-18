/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

#include <string>

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/base/i18n/localization.h"
#include "frameworks/base/utils/time_util.h"
#include "frameworks/core/components/refresh/refresh_theme.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/event/event_hub.h"
#include "frameworks/core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t CHILD_COUNT = 2;
constexpr double DEFAULT_INDICATOR_OFFSET = 16.0;
constexpr int32_t DEFAULT_FRICTION_RATIO = 42;
constexpr char REFRESH_LAST_UPDATED[] = "refresh.last_updated"; // I18n for last updated
constexpr Dimension LOADING_PROGRESS_SIZE = 32.0_vp;
} // namespace

void RefreshModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::REFRESH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RefreshPattern>(); });
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(
        RefreshLayoutProperty, IndicatorOffset, Dimension(DEFAULT_INDICATOR_OFFSET, DimensionUnit::VP));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, Friction, DEFAULT_FRICTION_RATIO);
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsUseOffset, true);
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsShowLastTime, false);
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ScrollableOffset, OffsetF(0.0, 0.0));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ShowTimeOffset, OffsetF(0.0, 0.0));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, LoadingProcessOffset, OffsetF(0.0, 0.0));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, TriggerRefreshDistance, Dimension(0.0, DimensionUnit::VP));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, RefreshDistance, Dimension(0.0, DimensionUnit::VP));
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsRefresh, true);
}

void RefreshModelNG::Pop()
{
    auto refreshNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(refreshNode);
    auto layoutProperty = refreshNode->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto refreshRenderProperty = refreshNode->GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(refreshRenderProperty);
    auto pattern = refreshNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->GetIsCustomBuilderExist()) {
        if (refreshNode->TotalChildCount() >= CHILD_COUNT) {
            LOGI("%{public}s have %{public}d child", refreshNode->GetTag().c_str(), refreshNode->TotalChildCount());
            return;
        }
        auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(textChild);
        refreshNode->AddChild(textChild);
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (layoutProperty->GetIsShowLastTimeValue()) {
            textLayoutProperty->UpdateContent(refreshRenderProperty->GetTimeTextValue());
            auto lastTimeText = Localization::GetInstance()->GetEntryLetters(REFRESH_LAST_UPDATED);
            refreshRenderProperty->UpdateLastTimeText(lastTimeText);
            auto timeText = StringUtils::FormatString("");
            refreshRenderProperty->UpdateTimeText(timeText);
        }
        auto textStyle = layoutProperty->GetTextStyle();
        CHECK_NULL_VOID(textStyle);
        textLayoutProperty->UpdateTextAlign(textStyle->GetTextAlign());
        textLayoutProperty->UpdateTextBaseline(textStyle->GetTextBaseline());
        textLayoutProperty->UpdateTextCase(textStyle->GetTextCase());
        textLayoutProperty->UpdateTextColor(textStyle->GetTextColor());
        textLayoutProperty->UpdateFontWeight(textStyle->GetFontWeight());
        textLayoutProperty->UpdateFontFamily(textStyle->GetFontFamilies());
        textLayoutProperty->UpdateTextDecoration(textStyle->GetTextDecoration());
        textLayoutProperty->UpdateTextDecorationColor(textStyle->GetTextDecorationColor());
        textLayoutProperty->UpdateTextDecorationStyle(textStyle->GetTextDecorationStyle());
        textLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);

        auto loadingProgressChild = FrameNode::CreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LoadingProgressPattern>());
        CHECK_NULL_VOID(loadingProgressChild);
        auto gestureHub = loadingProgressChild->GetEventHub<EventHub>();
        if (gestureHub) {
            gestureHub->SetEnabled(false);
        }
        auto progressLayoutProperty = loadingProgressChild->GetLayoutProperty<LoadingProgressLayoutProperty>();
        progressLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LOADING_PROGRESS_SIZE.ConvertToPx()), CalcLength(LOADING_PROGRESS_SIZE.ConvertToPx())));
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto themeManager = pipeline->GetThemeManager();
        CHECK_NULL_VOID(themeManager);
        auto theme = themeManager->GetTheme<RefreshTheme>();
        CHECK_NULL_VOID(theme);
        auto paintProperty = loadingProgressChild->GetPaintProperty<LoadingProgressPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateColor(theme->GetProgressColor());
        auto progressContext = loadingProgressChild->GetRenderContext();
        CHECK_NULL_VOID(progressContext);
        progressContext->UpdateOpacity(0.0);
        refreshNode->AddChild(loadingProgressChild);
        loadingProgressChild->MarkDirtyNode();
    }
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}
void RefreshModelNG::SetRefreshing(bool isRefreshing)
{
    ACE_UPDATE_PAINT_PROPERTY(RefreshRenderProperty, IsRefreshing, isRefreshing);
}

void RefreshModelNG::SetRefreshDistance(const Dimension& refreshDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, RefreshDistance, refreshDistance);
}

void RefreshModelNG::SetUseOffset(bool isUseOffset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsUseOffset, isUseOffset);
}

void RefreshModelNG::SetIndicatorOffset(const Dimension& indicatorOffset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IndicatorOffset, indicatorOffset);
}

void RefreshModelNG::SetFriction(int32_t friction)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, Friction, friction);
}

void RefreshModelNG::IsRefresh(bool isRefresh)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsRefresh, isRefresh);
}

void RefreshModelNG::SetLoadingDistance(const Dimension& loadingDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, LoadingDistance, loadingDistance);
}

void RefreshModelNG::SetProgressDistance(const Dimension& progressDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ProgressDistance, progressDistance);
}

void RefreshModelNG::SetProgressDiameter(const Dimension& progressDiameter)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ProgressDiameter, progressDiameter);
}

void RefreshModelNG::SetMaxDistance(const Dimension& maxDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, MaxDistance, maxDistance);
}

void RefreshModelNG::SetIsShowLastTime(bool isShowlastTime)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsShowLastTime, isShowlastTime);
}

void RefreshModelNG::SetShowTimeDistance(const Dimension& showTimeDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ShowTimeDistance, showTimeDistance);
}

void RefreshModelNG::SetTextStyle(const TextStyle& textStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, TextStyle, textStyle);
}

void RefreshModelNG::SetProgressColor(const Color& progressColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ProgressColor, progressColor);
}

void RefreshModelNG::SetProgressBackgroundColor(const Color& backgroundColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, BackgroundColor, backgroundColor);
}

void RefreshModelNG::SetOnStateChange(StateChangeEvent&& stateChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStateChange(std::move(stateChange));
}

void RefreshModelNG::SetOnRefreshing(RefreshingEvent&& refreshing)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRefreshing(std::move(refreshing));
}

void RefreshModelNG::SetChangeEvent(ChangeEvent&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void RefreshModelNG::SetCustomBuilder(const RefPtr<NG::UINode>& customBuilder)
{
    CHECK_NULL_VOID(customBuilder);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddCustomBuilderNode(customBuilder);
}

} // namespace OHOS::Ace::NG
