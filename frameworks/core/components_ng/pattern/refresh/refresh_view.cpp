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

#include "core/components_ng/pattern/refresh/refresh_view.h"

#include <string>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void RefreshView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::REFRESH_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RefreshPattern>(); });
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
}

void RefreshView::Pop()
{
    auto refreshNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(refreshNode);
    if (refreshNode->TotalChildCount() >= 2) {
        LOGI("%{public}s have %{public}d child", refreshNode->GetTag().c_str(), refreshNode->TotalChildCount());
        return;
    }
    auto layoutProperty = refreshNode->GetLayoutProperty<RefreshLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto refreshRenderProperty = refreshNode->GetPaintProperty<RefreshRenderProperty>();
    CHECK_NULL_VOID(refreshRenderProperty);

    auto textChild = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(textChild);
    refreshNode->AddChild(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(refreshRenderProperty->GetTimeTextValue());
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
    textLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);

    auto progressChild = FrameNode::CreateFrameNode(V2::PROGRESS_ETS_TAG, -1, AceType::MakeRefPtr<ProgressPattern>());
    CHECK_NULL_VOID(progressChild);
    refreshNode->AddChild(progressChild);
    auto progressLayoutProperty = progressChild->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    auto progressPaintProperty = progressChild->GetPaintProperty<ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    progressPaintProperty->UpdateValue(10.0);
    progressPaintProperty->UpdateMaxValue(10.0);
    progressLayoutProperty->UpdateColor(Color::BLUE);
    progressLayoutProperty->UpdateType(ProgressType::SCALE);
    progressLayoutProperty->UpdateStrokeWidth(Dimension(15, DimensionUnit::VP));
    progressPaintProperty->UpdateScaleCount(15);
    progressPaintProperty->UpdateScaleWidth(Dimension(5, DimensionUnit::VP));
    progressLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
}
void RefreshView::SetRefreshing(bool isRefreshing)
{
    ACE_UPDATE_PAINT_PROPERTY(RefreshRenderProperty, IsRefreshing, isRefreshing);
}

void RefreshView::SetRefreshDistance(const Dimension& refreshDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, RefreshDistance, refreshDistance);
}

void RefreshView::SetUseOffset(bool isUseOffset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsUseOffset, isUseOffset);
}

void RefreshView::SetIndicatorOffset(const Dimension& indicatorOffset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IndicatorOffset, indicatorOffset);
}

void RefreshView::SetFriction(int32_t friction)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, Friction, friction);
}

void RefreshView::IsRefresh(bool isRefresh)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsRefresh, isRefresh);
}

void RefreshView::SetLoadingDistance(const Dimension& loadingDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, LoadingDistance, loadingDistance);
}

void RefreshView::SetProgressDistance(const Dimension& progressDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ProgressDistance, progressDistance);
}

void RefreshView::SetProgressDiameter(const Dimension& progressDiameter)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ProgressDiameter, progressDiameter);
}

void RefreshView::SetMaxDistance(const Dimension& maxDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, MaxDistance, maxDistance);
}

void RefreshView::SetIsShowLastTime(bool isShowlastTime)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, IsShowLastTime, isShowlastTime);
}

void RefreshView::SetShowTimeDistance(const Dimension& showTimeDistance)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ShowTimeDistance, showTimeDistance);
}

void RefreshView::SetTextStyle(const TextStyle& textStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, TextStyle, textStyle);
}

void RefreshView::SetProgressColor(const Color& progressColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, ProgressColor, progressColor);
}

void RefreshView::SetProgressBackgroundColor(const Color& backgroundColor)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RefreshLayoutProperty, BackgroundColor, backgroundColor);
}

void RefreshView::SetOnStateChange(StateChangeEvent&& stateChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStateChange(std::move(stateChange));
}

void RefreshView::SetOnRefreshing(RefreshingEvent&& refreshing)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRefreshing(std::move(refreshing));
}

void RefreshView::SetChangeEvent(ChangeEvent&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RefreshEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

} // namespace OHOS::Ace::NG
