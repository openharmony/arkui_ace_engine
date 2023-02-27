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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/toss_animation_controller.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
// TODO datepicker style modification
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
} // namespace

void TextPickerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

bool TextPickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN_NOLOG(config.frameSizeChange, false);
    CHECK_NULL_RETURN(dirty, false);
    SetButtonIdeaSize();
    return true;
}

void TextPickerPattern::SetButtonIdeaSize()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto children = host->GetChildren();
    auto height = pickerTheme->GetDividerSpacing();
    auto width = host->GetGeometryNode()->GetFrameSize().Width() / static_cast<float>(children.size());
    auto defaultWidth = height.ConvertToPx() * 2;
    if (width > defaultWidth) {
        width = static_cast<float>(defaultWidth);
    }
    for (const auto& child : children) {
        auto buttonNode = DynamicCast<FrameNode>(child->GetFirstChild());
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonLayoutProperty->UpdateBorderRadius(PRESS_RADIUS);
        buttonLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width - PRESS_INTERVAL.ConvertToPx()),
            CalcLength(CalculateHeight() - PRESS_INTERVAL.ConvertToPx())));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TextPickerPattern::OnModifyDone()
{
    OnColumnsBuilding();
    FlushOptions();
    CalculateHeight();
    SetEventCallback([weak = WeakClaim(this)](bool refresh) {
        auto refPtr = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(refPtr);
        refPtr->FireChangeEvent(refresh);
    });
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    InitOnKeyEvent(focusHub);
    InitDisabled();
}

void TextPickerPattern::SetEventCallback(EventCallback&& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(stackNode);
        auto childNode = DynamicCast<FrameNode>(stackNode->GetLastChild());
        CHECK_NULL_VOID(childNode);
        auto pickerColumnPattern = childNode->GetPattern<TextPickerColumnPattern>();
        CHECK_NULL_VOID(pickerColumnPattern);
        pickerColumnPattern->SetEventCallback(std::move(value));
    }
}

void TextPickerPattern::FireChangeEvent(bool refresh)
{
    auto columnNode = GetColumnNode();
    CHECK_NULL_VOID(columnNode);
    auto textPickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    if (refresh) {
        auto textPickerEventHub = GetEventHub<TextPickerEventHub>();
        CHECK_NULL_VOID(textPickerEventHub);
        auto currentIndex = textPickerColumnPattern->GetCurrentIndex();
        auto currentValue = textPickerColumnPattern->GetOption(currentIndex);
        textPickerEventHub->FireChangeEvent(currentValue, currentIndex);
        textPickerEventHub->FireDialogChangeEvent(GetSelectedObject(true, 1));
    }
}

void TextPickerPattern::InitDisabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto renderContext = host->GetRenderContext();
    enabled_ = eventHub->IsEnabled();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

RefPtr<FrameNode> TextPickerPattern::GetColumnNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto stackNode = host->GetFirstChild();
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto column = stackNode->GetLastChild();
    CHECK_NULL_RETURN(column, nullptr);
    return DynamicCast<FrameNode>(column);
}

void TextPickerPattern::OnColumnsBuilding()
{
    auto frameNode = GetColumnNode();
    CHECK_NULL_VOID(frameNode);
    auto textPickerColumnPattern = frameNode->GetPattern<TextPickerColumnPattern>();
    CHECK_NULL_VOID(textPickerColumnPattern);
    ClearOption();
    for (const auto& item : range_) {
        AppendOption(item);
    }
    selectedIndex_ = range_.empty() ? 0 : GetSelected() % range_.size();
    textPickerColumnPattern->SetCurrentIndex(selectedIndex_);
    textPickerColumnPattern->SetOptions(options_);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TextPickerPattern::FlushOptions()
{
    auto frameNode = GetColumnNode();
    CHECK_NULL_VOID(frameNode);
    auto columnPattern = frameNode->GetPattern<TextPickerColumnPattern>();
    columnPattern->FlushCurrentOptions();
    frameNode->MarkModifyDone();
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

double TextPickerPattern::CalculateHeight()
{
    double height = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, height);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(textPickerLayoutProperty, height);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, height);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, height);
    if (textPickerLayoutProperty->HasDefaultPickerItemHeight()) {
        auto defaultPickerItemHeightValue = textPickerLayoutProperty->GetDefaultPickerItemHeightValue();
        if (context->NormalizeToPx(defaultPickerItemHeightValue) <= 0) {
            height = pickerTheme->GetDividerSpacing().ConvertToPx();
            return height;
        }
        if (defaultPickerItemHeightValue.Unit() == DimensionUnit::PERCENT) {
            height = pickerTheme->GetGradientHeight().ConvertToPx() * defaultPickerItemHeightValue.Value();
        } else {
            height = context->NormalizeToPx(defaultPickerItemHeightValue);
        }
    } else {
        height = pickerTheme->GetDividerSpacing().ConvertToPx();
    }
    if (defaultPickerItemHeight_ != height) {
        defaultPickerItemHeight_ = height;
        PaintFocusState();
        SetButtonIdeaSize();
    }
    auto frameNode = GetColumnNode();
    CHECK_NULL_RETURN(frameNode, height);
    auto textPickerColumnPattern = frameNode->GetPattern<TextPickerColumnPattern>();
    CHECK_NULL_RETURN(textPickerColumnPattern, height);
    textPickerColumnPattern->SetDefaultPickerItemHeight(height);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return height;
}

void TextPickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

void TextPickerPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPickerPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto frameWidth = host->GetGeometryNode()->GetFrameSize().Width();
    auto pickerThemeWidth = pipeline->NormalizeToPx(pickerTheme->GetDividerSpacing()) * 2;
    auto centerX = (frameWidth - pickerThemeWidth) / 2 + PRESS_INTERVAL.ConvertToPx();
    auto centerY =
        (host->GetGeometryNode()->GetFrameRect().Height() - CalculateHeight()) / 2 + PRESS_INTERVAL.ConvertToPx();

    if (frameWidth > pickerThemeWidth) {
        frameWidth = static_cast<float>(pickerThemeWidth);
    }
    paintRect.SetRect(RectF(static_cast<float>(centerX), static_cast<float>(centerY),
        frameWidth - static_cast<float>(PRESS_INTERVAL.ConvertToPx() * 2),
        static_cast<float>(CalculateHeight() - PRESS_INTERVAL.ConvertToPx() * 2)));

    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
}

bool TextPickerPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN ||
        event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_DPAD_RIGHT) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool TextPickerPattern::HandleDirectionKey(KeyCode code)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto frameNode = GetColumnNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto textPickerColumnPattern = frameNode->GetPattern<TextPickerColumnPattern>();
    CHECK_NULL_RETURN(textPickerColumnPattern, false);
    auto currernIndex = textPickerColumnPattern->GetCurrentIndex();
    auto totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return false;
    }
    if (code == KeyCode::KEY_DPAD_UP) {
        textPickerColumnPattern->SetCurrentIndex((totalOptionCount + currernIndex - 1) % totalOptionCount);
        FlushOptions();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        textPickerColumnPattern->SetCurrentIndex((totalOptionCount + currernIndex + 1) % totalOptionCount);
        FlushOptions();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    return false;
}

std::string TextPickerPattern::GetSelectedObject(bool isColumnChange, int32_t status) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto stackNode = host->GetFirstChild();
    CHECK_NULL_RETURN(stackNode, "");
    auto column = stackNode->GetLastChild();
    CHECK_NULL_RETURN(column, "");
    auto textPickerColumnPattern = DynamicCast<FrameNode>(column)->GetPattern<TextPickerColumnPattern>();
    auto value = GetOption(textPickerColumnPattern->GetSelected());
    auto index = textPickerColumnPattern->GetSelected();
    if (isColumnChange) {
        value = textPickerColumnPattern->GetCurrentText();
        index = textPickerColumnPattern->GetCurrentIndex();
    }

    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, "");

    if (context->GetIsDeclarative()) {
        return std::string("{\"value\":") + "\"" + value + "\"" + ",\"index\":" + std::to_string(index) +
               ",\"status\":" + std::to_string(status) + "}";
    } else {
        return std::string("{\"newValue\":") + "\"" + value + "\"" + ",\"newSelected\":" + std::to_string(index) +
               ",\"status\":" + std::to_string(status) + "}";
    }
}

} // namespace OHOS::Ace::NG
