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

#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

#include <cstdint>

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
// TODO datepicker style modification
constexpr float LAYOUT_WEIGHT = 30.0;
constexpr float PADDING_WEIGHT = 10.0;
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
} // namespace

void TextPickerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);
    textPickerLayoutProperty->UpdateLayoutWeight(LAYOUT_WEIGHT);
    textPickerLayoutProperty->UpdatePadding(PaddingProperty { CalcLength(PADDING_WEIGHT, DimensionUnit::PX) });
    textPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);

    InitilaScorllEvent();
    host->GetRenderContext()->SetClipToFrame(true);
}

void TextPickerPattern::OnModifyDone()
{
    OnColumnsBuilding();
    FlushCurrentOptions();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    if (focusHub) {
        InitOnKeyEvent(focusHub);
    }
}

void TextPickerPattern::OnColumnsBuilding()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameNode = DynamicCast<FrameNode>(host);
    auto children = frameNode->GetChildren();
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->ClearOption();
    for (const auto& item : range_) {
        textPickerPattern->AppendOption(item);
    }
    selectedIndex_ = range_.empty() ? 0 : GetSelected() % range_.size();
    SetCurrentIndex(selectedIndex_);
}

uint32_t TextPickerPattern::GetShowOptionCount() const
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, 0);
    auto showCount = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = OPTION_COUNT_PHONE_LANDSCAPE;
    }
    return showCount;
}

void TextPickerPattern::FlushCurrentOptions()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    uint32_t showCount = GetShowOptionCount();
    auto textPickerPattern = host->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);

    uint32_t totalOptionCount = GetOptionCount();
    uint32_t currentIndex = GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showCount / 2; // the center option is selected.

    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    Size optionSize;
    DimensionUnit optionSizeUnit = DimensionUnit::PX;
    optionSize = pickerTheme->GetOptionSize(textPickerPattern->GetSelected());
    if (!NearZero(
            context->NormalizeToPx(textPickerLayoutProperty->GetDefaultPickerItemHeight().value_or(Dimension(0))))) {
        optionSize.SetHeight(context->NormalizeToPx(textPickerLayoutProperty->GetDefaultPickerItemHeightValue()));
    }
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }

    for (uint32_t index = 0; index < showCount; index++) {
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - selectedIndex) % totalOptionCount;
        auto optionValue = textPickerPattern->GetOption(optionIndex);
        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        // TODO Property Update
        textLayoutProperty->UpdateContent(optionValue);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
        textLayoutProperty->UpdateLineHeight(Dimension(optionSize.Height(), optionSizeUnit));
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        iter++;
    }
    selectedIndex_ = currentIndex;
    if (isIndexChanged_) {
        auto textPickerEventHub = GetEventHub<TextPickerEventHub>();
        CHECK_NULL_VOID(textPickerEventHub);
        auto currentValue = textPickerPattern->GetOption(currentIndex);
        textPickerEventHub->FireChangeEvent(currentValue, currentIndex);
        textPickerEventHub->FireDialogChangeEvent(GetSelectedObject(true, 1));
    }
}

std::string TextPickerPattern::GetSelectedObject(bool isColumnChange, int32_t status) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto value = GetOption(GetSelected());
    auto index = GetSelected();
    if (isColumnChange) {
        value = GetCurrentText();
        index = GetCurrentIndex();
    }

    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, "");

    if (context->GetIsDeclarative()) {
        return std::string("{\"value\":") + "\"" + value + "\"" +
            ",\"index\":" + std::to_string(index) +
            ",\"status\":" + std::to_string(status) + "}";
    } else {
        return std::string("{\"newValue\":") + "\"" + value + "\"" +
            ",\"newSelected\":" + std::to_string(index) +
            ",\"status\":" + std::to_string(status) + "}";
    }
}

void TextPickerPattern::InitilaScorllEvent()
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

void TextPickerPattern::UpdateCurrentOffset(float offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentOffset_ = currentOffset_ + offset;
    UpdateColumnChildPosition(GetCurrentOffset());
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TextPickerPattern::UpdateColumnChildPosition(double y)
{
    yLast_ = y;
    double dragDelta = yLast_ - yOffset_;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }

    auto context = PipelineContext::GetCurrentContext();
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

bool TextPickerPattern::CanMove(bool isDown) const
{
    if (!NotLoopOptions()) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    int totalOptionCount = static_cast<int>(GetOptionCount());
    int currentIndex = static_cast<int>(GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

bool TextPickerPattern::NotLoopOptions() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto showOptionCount = GetShowOptionCount();
    uint32_t totalOptionCount = GetOptionCount();
    return totalOptionCount <= showOptionCount / 2 + 1; // the critical value of loop condition.
}

bool TextPickerPattern::InnerHandleScroll(bool isDown)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto totalOptionCount = GetOptionCount();

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
    isIndexChanged_ = true;
    return true;
}

void TextPickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool TextPickerPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool TextPickerPattern::HandleDirectionKey(KeyCode code)
{
    if (code == KeyCode::KEY_DPAD_UP) {
        // Need to update: current selection
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        // Need to update: current selection
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
