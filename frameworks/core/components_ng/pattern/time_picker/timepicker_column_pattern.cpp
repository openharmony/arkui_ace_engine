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

#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"

#include <cstdint>
#include <iterator>
#include <list>

#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
// TODO timepicker style modification
constexpr Dimension LAYOUT_WEIGHT = 30.0_vp;
constexpr Dimension PADDING_WEIGHT = 10.0_vp;
} // namespace

void TimePickerColumnPattern::OnAttachToFrameNode()
{
    ScrollTimeColumn();
}

void TimePickerColumnPattern::FlushCurrentOptions()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parentNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto dataPickerLayoutProperty = host->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(dataPickerLayoutProperty);
    dataPickerLayoutProperty->UpdateLayoutWeight(static_cast<float>(LAYOUT_WEIGHT.ConvertToPx()));
    dataPickerLayoutProperty->UpdatePadding(
        PaddingProperty { CalcLength(static_cast<float>(PADDING_WEIGHT.ConvertToPx()), DimensionUnit::PX) });
    dataPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    auto showOptionCount = GetShowCount();
    uint32_t totalOptionCount = timePickerRowPattern->GetOptionCount(host);
    uint32_t currentIndex = host->GetPattern<TimePickerColumnPattern>()->GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.

    auto child = host->GetChildren();
    auto iter = child.begin();

    if (child.size() != showOptionCount) {
        return;
    }

    for (uint32_t index = 0; index < showOptionCount; index++) {
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - selectedIndex) % totalOptionCount;
        auto optionValue = timePickerRowPattern->GetAllOptions(host)[optionIndex];
        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(optionValue);
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        iter++;
    }
}

bool TimePickerColumnPattern::NotLoopOptions() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto showOptionCount = GetShowCount();
    auto options = GetOptions();
    uint32_t totalOptionCount = options[host].size();
    return totalOptionCount <= showOptionCount / 2 + 1; // the critical value of loop condition.
}

bool TimePickerColumnPattern::InnerHandleScroll(bool isDown)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    auto totalOptionCount = options[host].size();

    if (!host || !totalOptionCount) {
        LOGE("options is empty.");
        return false;
    }

    uint32_t currentIndex = GetCurrentIndex();
    if (isDown) {
        currentIndex = (totalOptionCount + currentIndex + 1) % totalOptionCount; // index add one
    } else {
        currentIndex = (totalOptionCount + currentIndex - 1) % totalOptionCount; // index reduce one
    }
    SetCurrentIndex(currentIndex);
    FlushCurrentOptions();
    HandleChangeCallback(isDown, true);
    HandleEventCallback(true);
    return true;
}

void TimePickerColumnPattern::UpdateColumnChildPosition(double y)
{
    yLast_ = y;
    double dragDelta = yLast_ - yOffset_;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    jumpInterval_ = Dimension(pickerTheme->GetJumpInterval().ConvertToPx(), DimensionUnit::PX);
    // the abs of drag delta is less than jump interval.
    if (LessNotEqual(0.0 - jumpInterval_.Value(), dragDelta) && LessNotEqual(dragDelta, jumpInterval_.Value())) {
        LOGE("the abs of drag delta is less than jump interval");
        return;
    }
    InnerHandleScroll(LessNotEqual(dragDelta, 0.0));
    double jumpDelta = (LessNotEqual(dragDelta, 0.0) ? jumpInterval_.Value() : 0.0 - jumpInterval_.Value());
    yOffset_ = y - jumpDelta;
}

bool TimePickerColumnPattern::CanMove(bool isDown) const
{
    if (!NotLoopOptions()) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    int totalOptionCount = static_cast<int>(options[host].size());
    auto timePickerColumnPattern = host->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(timePickerColumnPattern, false);
    int currentIndex = static_cast<int>(timePickerColumnPattern->GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

void TimePickerColumnPattern::ScrollTimeColumn()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto task = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateCurrentOffset(static_cast<float>(offset));
            }
        }
        return true;
    };

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollableEvent_->SetScrollPositionCallback(std::move(task));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

void TimePickerColumnPattern::UpdateCurrentOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset_ + offset;
    UpdateColumnChildPosition(GetCurrentOffset());
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}
} // namespace OHOS::Ace::NG