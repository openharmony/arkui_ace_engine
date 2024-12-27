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
#include "core/interfaces/native/node/shape_modifier.h"

#include "core/components_ng/pattern/shape/shape_model_ng.h"

namespace OHOS::Ace::NG {
void SetShapeViewPort(ArkUINodeHandle node, const ArkUI_Float32* dimValues, const ArkUI_Int32* dimUnits)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension dimLeft = CalcDimension(dimValues[0], (DimensionUnit)dimUnits[0]);
    CalcDimension dimTop = CalcDimension(dimValues[1], (DimensionUnit)dimUnits[1]);
    CalcDimension dimWidth = CalcDimension(dimValues[2], (DimensionUnit)dimUnits[2]);
    CalcDimension dimHeight = CalcDimension(dimValues[3], (DimensionUnit)dimUnits[3]);
    ShapeModelNG::SetViewPort(frameNode, dimLeft, dimTop, dimWidth, dimHeight);
}

void ResetShapeViewPort(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension dimLeft = CalcDimension(0.0, DimensionUnit::PX);
    CalcDimension dimTop = CalcDimension(0.0, DimensionUnit::PX);
    CalcDimension dimWidth = CalcDimension(0.0, DimensionUnit::PX);
    CalcDimension dimHeight = CalcDimension(0.0, DimensionUnit::PX);
    ShapeModelNG::SetViewPort(frameNode, dimLeft, dimTop, dimWidth, dimHeight);
}

void SetShapeMesh(ArkUINodeHandle node, const ArkUI_Float32* mesh, ArkUI_Uint32 arrayItemCount,
    ArkUI_Int32 column, ArkUI_Int32 row)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<float> meshValues(mesh, mesh + arrayItemCount);
    ShapeModelNG::SetBitmapMesh(frameNode, meshValues, column, row);
}

void ResetShapeMesh(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<float> meshValues;
    int32_t column = 0;
    int32_t row = 0;
    ShapeModelNG::SetBitmapMesh(frameNode, meshValues, column, row);
}

namespace NodeModifier {
const ArkUIShapeModifier* GetShapeModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIShapeModifier modifier = {
        .setShapeViewPort = SetShapeViewPort,
        .resetShapeViewPort = ResetShapeViewPort,
        .setShapeMesh = SetShapeMesh,
        .resetShapeMesh = ResetShapeMesh,
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

const CJUIShapeModifier* GetCJUIShapeModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIShapeModifier modifier = {
        .setShapeViewPort = SetShapeViewPort,
        .resetShapeViewPort = ResetShapeViewPort,
        .setShapeMesh = SetShapeMesh,
        .resetShapeMesh = ResetShapeMesh,
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
} // namespace OHOS::Ace::NG
