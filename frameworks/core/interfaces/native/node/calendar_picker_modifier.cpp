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

void SetTextStyle(NodeHandle node, uint32_t color, const char* fontSize, const char* fontweight)
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

void ResetTextStyle(NodeHandle node)
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

void SetEdgeAlign(NodeHandle node, const double* values, const int* units, int32_t size, int32_t alignType)
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

void ResetEdgeAlign(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset;
    CalendarPickerModelNG::SetEdgeAlign(frameNode, alignType, offset);
}
ArkUICalendarPickerModifierAPI GetCalendarPickerModifier()
{
    static const ArkUICalendarPickerModifierAPI modifier = { SetTextStyle, ResetTextStyle, SetEdgeAlign,
        ResetEdgeAlign };

    return modifier;
}
} // namespace OHOS::Ace::NG
