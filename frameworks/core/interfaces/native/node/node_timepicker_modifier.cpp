/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_timepicker_modifier.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components/common/properties/text_style.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DEFAULT_BG_COLOR = 0xFF007DFF;

void SetTimepickerSelected(ArkUINodeHandle node, ArkUI_Uint32 hour, ArkUI_Uint32 minute)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetSelectedTime(frameNode, PickerTime(hour, minute, 0));
}

void ResetTimepickerSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    time_t now = time(nullptr);
    auto currentTm = localtime(&now);
    PickerTime pickerTime(currentTm->tm_hour, currentTm->tm_min, 0);

    TimePickerModelNG::SetSelectedTime(frameNode, pickerTime);
}

void SetTimepickerBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetTimepickerBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetBackgroundColor(frameNode, Color(DEFAULT_BG_COLOR));
}

void SetTimepickerTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    NodeModifier::GetPickerTextStyle(color, fontInfo, styleVal, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TimePickerModelNG::SetNormalTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void ResetTimepickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TimePickerModelNG::SetNormalTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTimepickerSelectedTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    NodeModifier::GetPickerTextStyle(color, fontInfo, styleVal, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TimePickerModelNG::SetSelectedTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void ResetTimepickerSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TimePickerModelNG::SetSelectedTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTimepickerDisappearTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    NodeModifier::GetPickerTextStyle(color, fontInfo, styleVal, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TimePickerModelNG::SetDisappearTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void ResetTimepickerDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();

    TimePickerModelNG::SetDisappearTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTimepickerUseMilitaryTime(ArkUINodeHandle node, int isUseMilitaryTime)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetHour24(frameNode, isUseMilitaryTime);
}

void ResetTimepickerUseMilitaryTime(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetHour24(frameNode, false);
}
} // namespace

namespace NodeModifier {
const ArkUITimepickerModifier* GetTimepickerModifier()
{
    static const ArkUITimepickerModifier modifier = {
        SetTimepickerSelected, ResetTimepickerSelected, SetTimepickerBackgroundColor, SetTimepickerDisappearTextStyle,
        SetTimepickerTextStyle, SetTimepickerSelectedTextStyle,
        ResetTimepickerDisappearTextStyle, ResetTimepickerTextStyle,
        ResetTimepickerSelectedTextStyle, ResetTimepickerBackgroundColor,
        SetTimepickerUseMilitaryTime, ResetTimepickerUseMilitaryTime
    };

    return &modifier;
}

void SetTimePickerOnChange(ArkUINodeHandle node, ArkUI_Int32 eventId, void* extraParam)
{
    auto onChange = [eventId, extraParam](const BaseEventInfo* info) {
        ArkUINodeEvent event;
        event.kind = ON_TIME_PICKER_CHANGE;
        event.eventId = eventId;
        event.extraParam= extraParam;
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo->GetSelectedStr());
        if (!argsPtr) {
            event.componentAsyncEvent.data[0].i32 = 0;
            event.componentAsyncEvent.data[1].i32 = 0;
        }
        auto hour = argsPtr->GetValue("hour");
        auto minute = argsPtr->GetValue("minute");
        if (hour && hour->IsNumber()) {
            event.componentAsyncEvent.data[0].i32 = hour->GetInt();
        }
        if (minute && minute->IsNumber()) {
            event.componentAsyncEvent.data[1].i32 = minute->GetInt();
        }
        SendArkUIAsyncEvent(&event);
    };
    TimePickerModel::GetInstance()->SetOnChange(std::move(onChange));
}
}
}
