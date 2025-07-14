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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t VIEW_POTR_SIZE = 4;
}
void SetShapeViewPort(
    ArkUINodeHandle node, const ArkUI_Float32* dimValues, const ArkUI_Int32* dimUnits, void* resObjArray)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeViewPort");
    CalcDimension dimLeft = CalcDimension(dimValues[0], (DimensionUnit)dimUnits[0]);
    CalcDimension dimTop = CalcDimension(dimValues[1], (DimensionUnit)dimUnits[1]);
    CalcDimension dimWidth = CalcDimension(dimValues[2], (DimensionUnit)dimUnits[2]);
    CalcDimension dimHeight = CalcDimension(dimValues[3], (DimensionUnit)dimUnits[3]);
    std::vector<RefPtr<ResourceObject>> resObjArrayResult;
    RefPtr<ResourceObject>* resObjPtr = static_cast<RefPtr<ResourceObject>*>(resObjArray);
    bool hasResObj = false;
    for (int32_t i = 0; i < VIEW_POTR_SIZE; i++) {
        if (resObjPtr[i]) {
            hasResObj = true;
        }
        resObjArrayResult.emplace_back(resObjPtr[i]);
    }
    if (SystemProperties::ConfigChangePerform() && hasResObj) {
        std::vector<Dimension> dimArray = { dimLeft, dimTop, dimWidth, dimHeight };
        ShapeModelNG::SetViewPort(frameNode, dimArray, resObjArrayResult);
    }
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
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeViewPort");
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
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIShapeModifier modifier = {
        .setShapeViewPort = SetShapeViewPort,
        .resetShapeViewPort = ResetShapeViewPort,
        .setShapeMesh = SetShapeMesh,
        .resetShapeMesh = ResetShapeMesh,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIShapeModifier* GetCJUIShapeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIShapeModifier modifier = {
        .setShapeViewPort = SetShapeViewPort,
        .resetShapeViewPort = ResetShapeViewPort,
        .setShapeMesh = SetShapeMesh,
        .resetShapeMesh = ResetShapeMesh,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
