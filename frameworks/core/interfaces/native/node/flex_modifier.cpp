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
#include "core/interfaces/native/node/flex_modifier.h"

#include "core/components_ng/pattern/flex/flex_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;

int ParseFlexToWrap(int align)
{
    FlexAlign alignment = FlexAlign::AUTO;
    switch (align) {
        case NUM_0: //WrapAlignment::START
            alignment = FlexAlign::FLEX_START;
            break;
        case NUM_1: //WrapAlignment::CENTER
            alignment = FlexAlign::CENTER;
            break;
        case NUM_2: //WrapAlignment::END
            alignment = FlexAlign::FLEX_END;
            break;
        case NUM_3: //WrapAlignment::SPACE_AROUND
            alignment = FlexAlign::SPACE_AROUND;
            break;
        case NUM_4: //WrapAlignment::SPACE_BETWEEN
            alignment = FlexAlign::SPACE_BETWEEN;
            break;
        case NUM_5: //WrapAlignment::STRETCH
            alignment = FlexAlign::STRETCH;
            break;
        case NUM_6: //WrapAlignment::SPACE_EVENLY
            alignment = FlexAlign::SPACE_EVENLY;
            break;
        case NUM_7: //WrapAlignment::BASELINE
            alignment = FlexAlign::BASELINE;
            break;
        default:
            break;
    }
    return static_cast<int32_t>(alignment);
}

void SetFlexOptions(ArkUINodeHandle node, int* options, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    int direction = options[NUM_0];
    int wrap = options[NUM_1];
    int justifyContent = options[NUM_2];
    int alignItems = options[NUM_3];
    int alignContent = options[NUM_4];
    if (wrap <= 0) {
        FlexModelNG::SetFlexRow(frameNode);
        if (direction >= 0 && direction <= DIRECTION_MAX_VALUE) {
            FlexModelNG::SetFlexDirection(frameNode, static_cast<OHOS::Ace::FlexDirection>(direction));
        }

        if (justifyContent >= 0 && justifyContent <= MAIN_ALIGN_MAX_VALUE) {
            FlexModelNG::SetFlexJustifyContent(frameNode, justifyContent);
        }

        if (alignItems >= 0 && alignItems <= CROSS_ALIGN_MAX_VALUE) {
            FlexModelNG::SetFlexAlignItems(frameNode, alignItems);
        }
    } else if (wrap > 0) {
        FlexModelNG::SetFlexWrap(frameNode);
        if (direction >= 0 && direction <= DIRECTION_MAX_VALUE) {
            FlexModelNG::SetFlexDirection(frameNode, static_cast<OHOS::Ace::FlexDirection>(direction));
            // WrapReverse means wrapVal = 2. Wrap means wrapVal = 1.
            direction <= 1 ? direction += NUM_2 * (wrap - NUM_1) : direction -= NUM_2 * (wrap - NUM_1);
            FlexModelNG::SetFlexWrapDirection(frameNode, static_cast<WrapDirection>(direction));
        } else {
            // No direction set case: wrapVal == 2 means FlexWrap.WrapReverse.
            WrapDirection wrapDirection = wrap == NUM_2 ? WrapDirection::HORIZONTAL_REVERSE : WrapDirection::HORIZONTAL;
            FlexModelNG::SetFlexWrapDirection(frameNode, wrapDirection);
        }

        if (justifyContent >= 0 && justifyContent <= MAIN_ALIGN_MAX_VALUE) {
            FlexModelNG::SetFlexJustifyContent(frameNode, static_cast<int>(WRAP_TABLE[justifyContent]));
        }

        if (alignItems >= 0 && alignItems <= CROSS_ALIGN_MAX_VALUE) {
            FlexModelNG::SetFlexAlignItems(frameNode, static_cast<int>(WRAP_TABLE[alignItems]));
        }

        if (alignContent >= 0 && alignContent <= MAIN_ALIGN_MAX_VALUE) {
            FlexModelNG::SetFlexAlignContent(frameNode, static_cast<int>(WRAP_TABLE[alignContent]));
        }
    }
}

void ResetFlexOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexModelNG::SetFlexRow(frameNode);
    FlexModelNG::SetFlexDirection(frameNode, OHOS::Ace::FlexDirection::ROW);
    FlexModelNG::SetFlexJustifyContent(frameNode, NUM_1);
    FlexModelNG::SetFlexAlignItems(frameNode, NUM_1);
    FlexModelNG::SetFlexAlignContent(frameNode, NUM_1);
}

void GetFlexOptions(ArkUINodeHandle node, ArkUIFlexOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    options->direction = FlexModelNG::GetFlexDirection(frameNode);
    options->wrap = FlexModelNG::GetFlexWrap(frameNode);
    if (FlexModelNG::GetFlexWrap(frameNode) <= 0) {
        options->justifyContent = FlexModelNG::GetFlexJustifyContent(frameNode);
        options->alignItems = FlexModelNG::GetFlexAlignItems(frameNode);
        options->alignContent = FlexModelNG::GetFlexAlignContent(frameNode);
    } else {
        options->justifyContent = ParseFlexToWrap(FlexModelNG::GetFlexJustifyContent(frameNode));
        options->alignItems = ParseFlexToWrap(FlexModelNG::GetFlexAlignItems(frameNode));
        options->alignContent = ParseFlexToWrap(FlexModelNG::GetFlexAlignContent(frameNode));
    }
}

void setFlexCrossSpace(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexModelNG::SetCrossSpace(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void SetMainSpace(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexModelNG::SetMainSpace(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

namespace NodeModifier {
const ArkUIFlexModifier* GetFlexModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIFlexModifier modifier = {
        .setFlexOptions = SetFlexOptions,
        .resetFlexOptions = ResetFlexOptions,
        .getFlexOptions = GetFlexOptions,
        .setFlexCrossSpace = setFlexCrossSpace,
        .setFlexMainSpace = SetMainSpace,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

const CJUIFlexModifier* GetCJUIFlexModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIFlexModifier modifier = {
        .setFlexOptions = SetFlexOptions,
        .resetFlexOptions = ResetFlexOptions,
        .getFlexOptions = GetFlexOptions,
        .setFlexCrossSpace = setFlexCrossSpace,
        .setFlexMainSpace = SetMainSpace,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}
}
}
