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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t VALID_RADIUS_PAIR_FLAG = 1;
const std::vector<std::string> RADIUS_TYPES = { "TopLeft", "TopRight", "BottomRight", "BottomLeft" };
} // namespace
void SetRectRadiusWidth(
    ArkUINodeHandle node, ArkUI_Float32 radiusWidthValue, ArkUI_Int32 radiusWidthUnit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusWidth = CalcDimension(radiusWidthValue, (DimensionUnit)radiusWidthUnit);
    RectModelNG::SetRadiusWidth(frameNode, radiusWidth);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("RectRadiusWidth");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<CalcDimension>("RectRadiusWidth", resObj, radiusWidth);
    }
}

void ResetRectRadiusWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension defaultDimension;
    defaultDimension.Reset();
    RectModelNG::SetRadiusWidth(frameNode, defaultDimension);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("RectRadiusWidth");
    return;
}

void SetRectRadiusHeight(
    ArkUINodeHandle node, ArkUI_Float32 radiusHeightValue, ArkUI_Int32 radiusHeightUnit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusHeight = CalcDimension(radiusHeightValue, (DimensionUnit)radiusHeightUnit);
    RectModelNG::SetRadiusHeight(frameNode, radiusHeight);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("RectRadiusHeight");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<CalcDimension>("RectRadiusHeight", resObj, radiusHeight);
    }
}

void ResetRectRadiusHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension defaultDimension;
    defaultDimension.Reset();
    RectModelNG::SetRadiusHeight(frameNode, defaultDimension);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("RectRadiusHeight");
}

void SetRectRadiusWithArray(ArkUINodeHandle node, ArkUI_Float32* radiusValues, ArkUI_Int32* radiusUnits,
    ArkUI_Uint32* radiusValidPairs, ArkUI_Uint32 radiusValidPairsSize, void* radiusXResObjArray,
    void* radiusYResObjArray)
{
    NG::ResetRectRadiusHeight(node);
    NG::ResetRectRadiusWidth(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(radiusValues);
    CHECK_NULL_VOID(radiusUnits);
    CHECK_NULL_VOID(radiusValidPairs);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    RefPtr<ResourceObject>* radiusXResObjPtr = static_cast<RefPtr<ResourceObject>*>(radiusXResObjArray);
    RefPtr<ResourceObject>* radiusYResObjPtr = static_cast<RefPtr<ResourceObject>*>(radiusYResObjArray);
    for (size_t index = 0; index < radiusValidPairsSize; index++) {
        if (radiusValidPairs[index] == VALID_RADIUS_PAIR_FLAG) {
            std::string radiusType = RADIUS_TYPES[index];
            std::string key = std::string("RectRadius") + radiusType;
            pattern->UnRegisterResource(key);
            uint32_t xIndex = index * 2;
            uint32_t yIndex = xIndex + 1;
            auto radiusX = CalcDimension(radiusValues[xIndex], (DimensionUnit)radiusUnits[xIndex]);
            auto radiusY = CalcDimension(radiusValues[yIndex], (DimensionUnit)radiusUnits[yIndex]);
            if (SystemProperties::ConfigChangePerform() && (radiusXResObjPtr[index] || radiusYResObjPtr[index])) {
                RectModelNG::SetRadiusValue(
                    frameNode, radiusX, radiusY, radiusXResObjPtr[index], radiusYResObjPtr[index], index);
            }
            RectModelNG::SetRadiusValue(frameNode, radiusX, radiusY, index);
        }
    }
}

void SetRectRadiusWithValue(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ResetRectRadiusWidth(node);
    NG::ResetRectRadiusHeight(node);
    auto radius = CalcDimension(radiusValue, (DimensionUnit)radiusUnit);
    RectModelNG::SetRadiusWidth(frameNode, radius);
    RectModelNG::SetRadiusHeight(frameNode, radius);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("RectRadius");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<CalcDimension>("RectRadius", resObj, radius);
    }
}

void ResetRectRadius(ArkUINodeHandle node)
{
    NG::ResetRectRadiusHeight(node);
    NG::ResetRectRadiusWidth(node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("RectRadius");
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
