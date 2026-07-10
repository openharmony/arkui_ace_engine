/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/common/container.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/bridge/shape_model_impl.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::ShapeModelImpl* GetShapeModelImpl()
{
    static Framework::ShapeModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t VIEW_PORT_SIZE = 4;

void CreateShape()
{
    ShapeModelNG model;
    model.Create();
}

void SetShapeViewPort(
    ArkUINodeHandle node, const ArkUI_Float32* dimValues, const ArkUI_Int32* dimUnits, void* resObjArray)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeViewPort");
    CalcDimension dimLeft = CalcDimension(dimValues[0], static_cast<DimensionUnit>(dimUnits[0]));
    CalcDimension dimTop = CalcDimension(dimValues[1], static_cast<DimensionUnit>(dimUnits[1]));
    CalcDimension dimWidth = CalcDimension(dimValues[2], static_cast<DimensionUnit>(dimUnits[2]));
    CalcDimension dimHeight = CalcDimension(dimValues[3], static_cast<DimensionUnit>(dimUnits[3]));
    std::vector<RefPtr<ResourceObject>> resObjArrayResult;
    auto* resObjPtr = static_cast<RefPtr<ResourceObject>*>(resObjArray);
    bool hasResObj = false;
    for (int32_t index = 0; index < VIEW_PORT_SIZE; index++) {
        if (resObjPtr[index]) {
            hasResObj = true;
        }
        resObjArrayResult.emplace_back(resObjPtr[index]);
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

void SetShapeMesh(
    ArkUINodeHandle node, const ArkUI_Float32* mesh, ArkUI_Uint32 arrayItemCount, ArkUI_Int32 column, ArkUI_Int32 row)
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

#ifndef CROSS_PLATFORM
void CreateShapeImpl()
{
    GetShapeModelImpl()->Create();
}

void SetShapeViewPortImpl(
    ArkUINodeHandle node, const ArkUI_Float32* dimValues, const ArkUI_Int32* dimUnits, void* resObjArray)
{
    CalcDimension dimLeft(dimValues[0], static_cast<DimensionUnit>(dimUnits[0]));
    CalcDimension dimTop(dimValues[1], static_cast<DimensionUnit>(dimUnits[1]));
    CalcDimension dimWidth(dimValues[2], static_cast<DimensionUnit>(dimUnits[2]));
    CalcDimension dimHeight(dimValues[3], static_cast<DimensionUnit>(dimUnits[3]));
    GetShapeModelImpl()->SetViewPort(dimLeft, dimTop, dimWidth, dimHeight);
}

void ResetShapeViewPortImpl(ArkUINodeHandle node)
{
    CalcDimension dimLeft(0.0, DimensionUnit::VP);
    CalcDimension dimTop(0.0, DimensionUnit::VP);
    CalcDimension dimWidth(0.0, DimensionUnit::VP);
    CalcDimension dimHeight(0.0, DimensionUnit::VP);
    GetShapeModelImpl()->SetViewPort(dimLeft, dimTop, dimWidth, dimHeight);
}

void SetShapeMeshImpl(
    ArkUINodeHandle node, const ArkUI_Float32* mesh, ArkUI_Uint32 arrayItemCount, ArkUI_Int32 column, ArkUI_Int32 row)
{
    std::vector<float> meshValues(mesh, mesh + arrayItemCount);
    GetShapeModelImpl()->SetBitmapMesh(meshValues, column, row);
}

void ResetShapeMeshImpl(ArkUINodeHandle node)
{
    std::vector<float> meshValues;
    int32_t column = 0;
    int32_t row = 0;
    GetShapeModelImpl()->SetBitmapMesh(meshValues, column, row);
}
#endif

} // namespace

namespace NodeModifier {
const ArkUIShapeModifier* GetShapeDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIShapeModifier modifier = {
            .createShape = CreateShapeImpl,
            .setShapeViewPort = SetShapeViewPortImpl,
            .resetShapeViewPort = ResetShapeViewPortImpl,
            .setShapeMesh = SetShapeMeshImpl,
            .resetShapeMesh = ResetShapeMeshImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIShapeModifier modifier = {
        .createShape = CreateShape,
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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
