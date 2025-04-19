/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/calendar_picker/calendar_dialog_layout_algorithm.h"

#include <algorithm>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CALENDAR_NODE = 0;
constexpr int32_t CALENDAR_MONTH_NODE = 1;
constexpr int32_t SCROLL_NODE = 2;
constexpr int32_t BUTTON_COLUMN_NODE = 3;
constexpr Dimension SPACE_HEIGHT = 32.0_vp;
} // namespace

void CalendarDialogLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto columnNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(columnNode);
    auto scrollNode = columnNode->GetChildAtIndex(SCROLL_NODE);
    CHECK_NULL_VOID(scrollNode);
    auto calendarNode = scrollNode->GetChildAtIndex(CALENDAR_NODE);
    CHECK_NULL_VOID(calendarNode);
    auto columnFrameNode = AceType::DynamicCast<NG::FrameNode>(columnNode);
    CHECK_NULL_VOID(columnFrameNode);
    auto columnLayoutProperty = columnFrameNode->GetLayoutProperty();
    CHECK_NULL_VOID(columnLayoutProperty);
    auto columnHeight = columnLayoutProperty->GetContentLayoutConstraint()->maxSize.Height();
    auto swiperNode = calendarNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto calendarMonthNode = swiperNode->GetChildAtIndex(CALENDAR_MONTH_NODE);
    CHECK_NULL_VOID(calendarMonthNode);
    auto yearRowHeight = GetYearRowHeight(columnNode);
    auto buttonColumnHeight = GetButtonColumnHeight(columnNode);
    auto calendarHeight = GetCalendarHeight(calendarNode);
    float scrollHeight = 0.0f;
    auto pipelineContext = columnNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    auto calendarMonthFrameNode = AceType::DynamicCast<NG::FrameNode>(calendarMonthNode);
    CHECK_NULL_VOID(calendarMonthFrameNode);
    auto calendarPaintProperty = calendarMonthFrameNode->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_VOID(calendarPaintProperty);
    auto gregorianDayHeight = calendarPaintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx() <= 0
                ? calendarTheme->GetCalendarTheme().gregorianCalendarHeight.ConvertToPx()
                : calendarPaintProperty->GetGregorianCalendarHeightValue({}).ConvertToPx();
    auto topPadding = calendarTheme->GetCalendarTheme().topPadding.ConvertToPx();
    if (buttonColumnHeight != 0.0f) {
        scrollHeight = columnHeight - yearRowHeight - buttonColumnHeight
            - SPACE_HEIGHT.ConvertToPx() - gregorianDayHeight - topPadding;
    } else {
        scrollHeight = columnHeight - yearRowHeight - SPACE_HEIGHT.ConvertToPx() - gregorianDayHeight - topPadding;
    }
    auto scrollFrameNode = AceType::DynamicCast<NG::FrameNode>(scrollNode);
    CHECK_NULL_VOID(scrollFrameNode);
    auto props = scrollFrameNode->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(props);
    if (calendarHeight <= scrollHeight) {
        scrollHeight = calendarHeight;
    }
    FireIsFoldStatusChanged(swiperNode);
    props->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(scrollHeight))));
    LinearLayoutAlgorithm::Measure(layoutWrapper);
}

void CalendarDialogLayoutAlgorithm::FireIsFoldStatusChanged(RefPtr<UINode>& swiperNode)
{
    for (const auto& calendarMonthNode : swiperNode->GetChildren()) {
        auto calenderMonthFrameNode = AceType::DynamicCast<FrameNode>(calendarMonthNode);
        CHECK_NULL_VOID(calenderMonthFrameNode);
        auto calenderMonthPattern = calenderMonthFrameNode->GetPattern<CalendarMonthPattern>();
        CHECK_NULL_VOID(calenderMonthPattern);
        calenderMonthPattern->FireIsFoldStatusChanged();
    }
}

float CalendarDialogLayoutAlgorithm::GetYearRowHeight(RefPtr<FrameNode>& columnNode)
{
    auto yearRowNode = columnNode->GetChildren().front();
    CHECK_NULL_RETURN(yearRowNode, 0.0f);
    auto yearRowFrameNode = AceType::DynamicCast<NG::FrameNode>(yearRowNode);
    CHECK_NULL_RETURN(yearRowFrameNode, 0.0f);
    return yearRowFrameNode->GetLayoutProperty()->GetCalcLayoutConstraint()
        ->selfIdealSize->Height()->GetDimension().ConvertToPx();
}

float CalendarDialogLayoutAlgorithm::GetButtonColumnHeight(RefPtr<FrameNode>& columnNode)
{
    float buttonColumnHeight = 0.0f;
    auto buttonColumnNode = columnNode->GetChildAtIndex(BUTTON_COLUMN_NODE);
    CHECK_NULL_RETURN(buttonColumnNode, buttonColumnHeight);
    auto buttonColumnFrameNode = AceType::DynamicCast<NG::FrameNode>(buttonColumnNode);
    CHECK_NULL_RETURN(buttonColumnFrameNode, buttonColumnHeight);
    buttonColumnHeight = buttonColumnFrameNode->GetLayoutProperty()
        ->GetCalcLayoutConstraint()->selfIdealSize->Height()->GetDimension().ConvertToPx();
    return buttonColumnHeight;
}

float CalendarDialogLayoutAlgorithm::GetCalendarHeight(RefPtr<UINode>& calendarNode)
{
    auto calendarFrameNode = AceType::DynamicCast<NG::FrameNode>(calendarNode);
    CHECK_NULL_RETURN(calendarFrameNode, 0.0f);
    return calendarFrameNode->GetLayoutProperty()
        ->GetCalcLayoutConstraint()->selfIdealSize->Height()->GetDimension().ConvertToPx();
}
} // namespace OHOS::Ace::NG