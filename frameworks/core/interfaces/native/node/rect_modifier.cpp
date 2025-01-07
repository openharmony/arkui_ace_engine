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
#include "core/interfaces/native/node/rect_modifier.h"

#include "core/components_ng/pattern/shape/rect_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t VALID_RADIUS_PAIR_FLAG = 1;
} // namespace
void SetRectRadiusWidth(ArkUINodeHandle node, ArkUI_Float32 radiusWidthValue, ArkUI_Int32 radiusWidthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RectModelNG::SetRadiusWidth(frameNode, CalcDimension(radiusWidthValue, (DimensionUnit)radiusWidthUnit));
}

void ResetRectRadiusWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension defaultDimension;
    defaultDimension.Reset();
    RectModelNG::SetRadiusWidth(frameNode, defaultDimension);
    return;
}

void SetRectRadiusHeight(ArkUINodeHandle node, ArkUI_Float32 radiusHeightValue, ArkUI_Int32 radiusHeightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RectModelNG::SetRadiusHeight(frameNode, CalcDimension(radiusHeightValue, (DimensionUnit)radiusHeightUnit));
}

void ResetRectRadiusHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension defaultDimension;
    defaultDimension.Reset();
    RectModelNG::SetRadiusHeight(frameNode, defaultDimension);
}

void SetRectRadiusWithArray(ArkUINodeHandle node, ArkUI_Float32* radiusValues, ArkUI_Int32* radiusUnits,
    ArkUI_Uint32* radiusValidPairs, ArkUI_Uint32 radiusValidPairsSize)
{
    NG::ResetRectRadiusHeight(node);
    NG::ResetRectRadiusWidth(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(radiusValues);
    CHECK_NULL_VOID(radiusUnits);
    CHECK_NULL_VOID(radiusValidPairs);
    for (size_t index = 0; index < radiusValidPairsSize; index++) {
        if (radiusValidPairs[index] == VALID_RADIUS_PAIR_FLAG) {
            uint32_t xIndex = index * 2;
            uint32_t yIndex = xIndex + 1;
            auto radiusX = CalcDimension(radiusValues[xIndex], (DimensionUnit)radiusUnits[xIndex]);
            auto radiusY = CalcDimension(radiusValues[yIndex], (DimensionUnit)radiusUnits[yIndex]);
            RectModelNG::SetRadiusValue(frameNode, radiusX, radiusY, index);
        }
    }
}

void SetRectRadiusWithValue(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ResetRectRadiusWidth(node);
    NG::ResetRectRadiusHeight(node);
    RectModelNG::SetRadiusWidth(frameNode, CalcDimension(radiusValue, (DimensionUnit)radiusUnit));
    RectModelNG::SetRadiusHeight(frameNode, CalcDimension(radiusValue, (DimensionUnit)radiusUnit));
}

void ResetRectRadius(ArkUINodeHandle node)
{
    NG::ResetRectRadiusHeight(node);
    NG::ResetRectRadiusWidth(node);
}

namespace NodeModifier {
const ArkUIRectModifier* GetRectModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIRectModifier modifier = {
        .setRectRadiusWidth = SetRectRadiusWidth,
        .resetRectRadiusWidth = ResetRectRadiusWidth,
        .setRectRadiusHeight = SetRectRadiusHeight,
        .resetRectRadiusHeight = ResetRectRadiusHeight,
        .setRectRadiusWithArray = SetRectRadiusWithArray,
        .setRectRadiusWithValue = SetRectRadiusWithValue,
        .resetRectRadius = ResetRectRadius,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIRectModifier* GetCJUIRectModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIRectModifier modifier = {
        .setRectRadiusWidth = SetRectRadiusWidth,
        .resetRectRadiusWidth = ResetRectRadiusWidth,
        .setRectRadiusHeight = SetRectRadiusHeight,
        .resetRectRadiusHeight = ResetRectRadiusHeight,
        .setRectRadiusWithArray = SetRectRadiusWithArray,
        .setRectRadiusWithValue = SetRectRadiusWithValue,
        .resetRectRadius = ResetRectRadius,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
