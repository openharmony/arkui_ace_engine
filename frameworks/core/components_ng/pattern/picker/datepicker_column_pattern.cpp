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

#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"

#include <cstdint>
#include <iterator>
#include <list>
#include <stdint.h>

#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {

// TODO datepicker style modification
constexpr float LAYOUT_WEIGHT = 30.0f;
constexpr float PADDING_WEIGHT = 10.0f;
const Dimension FONT_SIZE = Dimension(2.0);
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const int32_t DIVIDER_SIZE = 2;
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;

} // namespace

void DatePickerColumnPattern::OnAttachToFrameNode()
{
    ScrollColumn();
}

bool DatePickerColumnPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
    return true;
}

void DatePickerColumnPattern::FlushCurrentOptions()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parentNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(parentNode);

    auto dataPickerLayoutProperty = host->GetLayoutProperty<DataPickerLayoutProperty>();
    CHECK_NULL_VOID(dataPickerLayoutProperty);
    dataPickerLayoutProperty->UpdateLayoutWeight(LAYOUT_WEIGHT);
    dataPickerLayoutProperty->UpdatePadding(PaddingProperty { CalcLength(PADDING_WEIGHT, DimensionUnit::PX) });
    dataPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);

    auto datePickerPattern = parentNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    auto showOptionCount = datePickerPattern->GetShowCount();
    uint32_t totalOptionCount = datePickerPattern->GetOptionCount(host);
    uint32_t currentIndex = host->GetPattern<DatePickerColumnPattern>()->GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.

    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showOptionCount) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto middleIndex = showOptionCount / 2;
    auto normalOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    auto focusOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();
    SetCurrentIndex(currentIndex);
    SetDividerHeight(showOptionCount);
    for (uint32_t index = 0; index < showOptionCount; index++) {
        currentChildIndex_ = index;
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - selectedIndex) % totalOptionCount;
        auto optionValue = datePickerPattern->GetAllOptions(host)[optionIndex];
        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (index < middleIndex) {
            if (index == 0) {
                textLayoutProperty->UpdateFontSize(normalOptionSize);
            } else {
                textLayoutProperty->UpdateFontSize(focusOptionSize);
            }
            textLayoutProperty->UpdateMaxLines(1);
            textLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetDividerSpacing() * DIVIDER_SIZE),
                    CalcLength(pickerTheme->GetGradientHeight())));
            textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
        }
        if (index == middleIndex) {
            textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
            textLayoutProperty->UpdateMaxLines(1);
            textLayoutProperty->UpdateFontSize(selectedOptionSize);
            textLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetDividerSpacing() * DIVIDER_SIZE),
                    CalcLength(pickerTheme->GetDividerSpacing())));
            textLayoutProperty->UpdateAlignment(Alignment::CENTER);
        }
        if (index > middleIndex) {
            if (index == showOptionCount - 1) {
                textLayoutProperty->UpdateFontSize(normalOptionSize);
            } else {
                textLayoutProperty->UpdateFontSize(focusOptionSize);
            }
            textLayoutProperty->UpdateMaxLines(1);
            textLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetDividerSpacing() * DIVIDER_SIZE),
                    CalcLength(pickerTheme->GetGradientHeight())));
            textLayoutProperty->UpdateAlignment(Alignment::BOTTOM_CENTER);
        }
        textLayoutProperty->UpdateContent(optionValue);
        textNode->MarkDirtyNode();
        iter++;
    }
}

void DatePickerColumnPattern::SetDividerHeight(uint32_t showOptionCount)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    if (showOptionCount != OPTION_COUNT_PHONE_LANDSCAPE) {
        gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value() * TEXT_HEIGHT_NUMBER);
    } else {
        gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value());
    }
    dividerHeight_ = static_cast<float>(
        gradientHeight_ + pickerTheme->GetDividerSpacing().Value() + pickerTheme->GetGradientHeight().Value());
    dividerSpacingWidth_ = static_cast<float>(pickerTheme->GetDividerSpacing().Value() * TEXT_WEIGHT_NUMBER);
}

bool DatePickerColumnPattern::NotLoopOptions() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto showOptionCount = GetShowCount();
    auto options = GetOptions();
    uint32_t totalOptionCount = options[host].size();
    return totalOptionCount <= showOptionCount / 2 + 1; // the critical value of loop condition.
}

bool DatePickerColumnPattern::InnerHandleScroll(bool isDown)
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

void DatePickerColumnPattern::UpdateColumnChildPosition(double y)
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
    auto pickerTheme = context->GetTheme<PickerTheme>();
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

bool DatePickerColumnPattern::CanMove(bool isDown) const
{
    if (!NotLoopOptions()) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    int totalOptionCount = static_cast<int>(options[host].size());

    auto datePickerColumnPattern = host->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(datePickerColumnPattern, false);
    int currentIndex = static_cast<int>(datePickerColumnPattern->GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

void DatePickerColumnPattern::ScrollColumn()
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

void DatePickerColumnPattern::UpdateCurrentOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset_ + offset;
    UpdateColumnChildPosition(GetCurrentOffset());
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}
} // namespace OHOS::Ace::NG