/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/calendar_picker_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "frameworks/core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
} // namespace

void SetTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontSize, const char* fontweight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(color);
    CalcDimension fontSizeDimension =
        StringUtils::StringToCalcDimension(std::string(fontSize), false, DimensionUnit::FP);
    if (fontSizeDimension.Unit() == DimensionUnit::PERCENT) {
        textStyle.fontSize = Dimension(-1);
    } else {
        textStyle.fontSize = fontSizeDimension;
    }
    textStyle.fontWeight = StringUtils::StringToFontWeight(fontweight, FontWeight::NORMAL);
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}

void ResetTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    NG::PickerTextStyle textStyle;
    textStyle.fontSize = calendarTheme->GetEntryFontSize();
    textStyle.textColor = calendarTheme->GetEntryFontColor();
    textStyle.fontWeight = FontWeight::NORMAL;
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}

void SetEdgeAlign(ArkUINodeHandle node, const ArkUI_Float32* values, const int* units, int32_t size, int32_t alignType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (size < NUM_2) {
        return;
    }

    Dimension dx = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    Dimension dy = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    NG::CalendarEdgeAlign align = static_cast<NG::CalendarEdgeAlign>(alignType);
    DimensionOffset offset = DimensionOffset(dx, dy);
    CalendarPickerModelNG::SetEdgeAlign(frameNode, align, offset);
}

void ResetEdgeAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset;
    CalendarPickerModelNG::SetEdgeAlign(frameNode, alignType, offset);
}

void SetCalendarPickerPadding(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
    const struct ArkUISizeType* bottom, const struct ArkUISizeType* left)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength topDim;
    CalcLength rightDim;
    CalcLength bottomDim;
    CalcLength leftDim;
    if (top->string != nullptr) {
        topDim = CalcLength(top->string);
    } else {
        topDim = CalcLength(top->value, static_cast<DimensionUnit>(top->unit));
    }
    if (right->string != nullptr) {
        rightDim = CalcLength(right->string);
    } else {
        rightDim = CalcLength(right->value, static_cast<DimensionUnit>(right->unit));
    }
    if (bottom->string != nullptr) {
        bottomDim = CalcLength(bottom->string);
    } else {
        bottomDim = CalcLength(bottom->value, static_cast<DimensionUnit>(bottom->unit));
    }
    if (left->string != nullptr) {
        leftDim = CalcLength(left->string);
    } else {
        leftDim = CalcLength(left->value, static_cast<DimensionUnit>(left->unit));
    }
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>();
    paddings.bottom = std::optional<CalcLength>();
    paddings.left = std::optional<CalcLength>();
    paddings.right = std::optional<CalcLength>();
    if (topDim.IsValid()) {
        paddings.top = std::optional<CalcLength>(topDim);
    }
    if (bottomDim.IsValid()) {
        paddings.bottom = std::optional<CalcLength>(bottomDim);
    }
    if (leftDim.IsValid()) {
        paddings.left = std::optional<CalcLength>(leftDim);
    }
    if (rightDim.IsValid()) {
        paddings.right = std::optional<CalcLength>(rightDim);
    }
    CalendarPickerModelNG::SetPadding(frameNode, paddings);
}

void ResetCalendarPickerPadding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>();
    paddings.bottom = std::optional<CalcLength>();
    paddings.left = std::optional<CalcLength>();
    paddings.right = std::optional<CalcLength>();
    CalendarPickerModelNG::SetPadding(frameNode, paddings);
}

void SetCalendarPickerBorder(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    ViewAbstract::SetBorderColor(frameNode, Color(color));
}

void ResetCalendarPickerBorder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    ViewAbstract::SetBorderWidth(frameNode, calendarTheme->GetEntryBorderWidth());
    ViewAbstract::SetBorderColor(frameNode, calendarTheme->GetEntryBorderColor());
    ViewAbstract::SetBorderRadius(frameNode, calendarTheme->GetEntryBorderRadius());
    ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
}

namespace NodeModifier {
const ArkUICalendarPickerModifier* GetCalendarPickerModifier()
{
    static const ArkUICalendarPickerModifier modifier = { SetTextStyle, ResetTextStyle, SetEdgeAlign, ResetEdgeAlign,
        SetCalendarPickerPadding, ResetCalendarPickerPadding, SetCalendarPickerBorder, ResetCalendarPickerBorder };

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
