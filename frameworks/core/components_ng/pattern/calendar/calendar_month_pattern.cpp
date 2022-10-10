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

#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void CalendarMonthPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool CalendarMonthPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return !(config.skipMeasure || dirty->SkipMeasureContent());
}

void CalendarMonthPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (clickListener_) {
        return;
    }
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto obtainedMonth = obtainedMonth_;
    auto clickCallback = [weak = WeakClaim(this), obtainedMonth](GestureEvent& info) {
        auto calendarPattern = weak.Upgrade();
        CHECK_NULL_VOID(calendarPattern);
        auto globalLocation = info.GetFingerList().begin()->globalLocation_;
        calendarPattern->OnClick(globalLocation, calendarPattern->obtainedMonth_);
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void CalendarMonthPattern::OnClick(Offset& globalLocation, const ObtainedMonth& obtainedMonth)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(pattern);
    auto index = JudgeArea(globalLocation);
    pattern->obtainedMonth_ = obtainedMonth;
    if (!obtainedMonth_.days.empty()) {
        for (auto& day : pattern->obtainedMonth_.days) {
            day.focused = false;
        }
        pattern->obtainedMonth_.days[index].focused = true;
        auto calendarEventHub = GetEventHub<CalendarEventHub>();
        CHECK_NULL_VOID(calendarEventHub);
        if (index >= 0 && index < static_cast<int32_t>(obtainedMonth.days.size())) {
            auto json = JsonUtil::Create(true);
            json->Put("day", obtainedMonth.days[index].day);
            json->Put("month", obtainedMonth.days[index].month.month);
            json->Put("year", obtainedMonth.days[index].month.year);
            calendarEventHub->UpdateSelectedChangeEvent(json->ToString());
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

int32_t CalendarMonthPattern::JudgeArea(const Offset& offset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto paintProperty = host->GetPaintProperty<CalendarPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto topPadding = theme->GetCalendarTheme().topPadding.ConvertToPx();
    auto weekHeight = paintProperty->GetWeekHeight().value_or(theme->GetCalendarTheme().weekHeight).ConvertToPx();
    auto weekAndDayRowSpace =
        paintProperty->GetWeekAndDayRowSpace().value_or(theme->GetCalendarTheme().weekAndDayRowSpace).ConvertToPx();
    auto dayHeight = paintProperty->GetDayHeight().value_or(theme->GetCalendarTheme().dayHeight).ConvertToPx();
    auto dayWidth = paintProperty->GetDayWidth().value_or(theme->GetCalendarTheme().dayWidth).ConvertToPx();
    const static int32_t rowsOfData = 5;
    const static int32_t columnsOfData = 7;
    auto rowSpace = (host->GetGeometryNode()->GetFrameSize().Height() - topPadding - weekHeight - weekAndDayRowSpace -
                        dayHeight * rowsOfData) /
                    (rowsOfData - 1);
    auto colSpace = (host->GetGeometryNode()->GetFrameSize().Width() - columnsOfData * dayWidth) / (columnsOfData - 1);
    auto browHeight = weekHeight + topPadding + weekAndDayRowSpace;
    auto maxHeight = host->GetGeometryNode()->GetFrameSize().Height();
    auto maxWidth = host->GetGeometryNode()->GetFrameSize().Width();
    if ((offset.GetX() < 0) || (offset.GetX() > maxWidth) || (offset.GetY() < browHeight) ||
        (offset.GetY() > maxHeight) || LessOrEqual(dayHeight, 0.0) || LessOrEqual(dayWidth, 0.0)) {
        return -1;
    }
    auto height = offset.GetY() - browHeight;
    int32_t y =
        height < (dayHeight + rowSpace / 2) ? 0 : (height - dayHeight - rowSpace / 2) / (dayHeight + rowSpace) + 1;
    int32_t x = offset.GetX() < (dayWidth + colSpace / 2)
                    ? 0
                    : (offset.GetX() - dayWidth - colSpace / 2) / (dayWidth + colSpace) + 1;
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        x = columnsOfData - x - 1;
    }
    return (y * columnsOfData + x);
}

} // namespace OHOS::Ace::NG