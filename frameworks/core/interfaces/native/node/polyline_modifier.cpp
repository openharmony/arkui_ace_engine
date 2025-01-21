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
#include "core/interfaces/native/node/polyline_modifier.h"

#include "core/components_ng/pattern/shape/polygon_model_ng.h"

namespace OHOS::Ace::NG {

void SetPoints(ArkUINodeHandle node, const ArkUI_Float32* pointX, const ArkUI_Float32* pointY, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapePoint shapePoint;
    ShapePoints shapePoints;
    for (int32_t i = 0; i < length; i++) {
        auto xVal = pointX[i];
        auto yVal = pointY[i];
        shapePoint.first = Dimension(xVal, DimensionUnit::VP);
        shapePoint.second = Dimension(yVal, DimensionUnit::VP);
        shapePoints.push_back(shapePoint);
    }

    PolygonModelNG::SetPoints(frameNode, shapePoints);
}

void ResetPoints(ArkUINodeHandle node)
{
    ShapePoints points;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PolygonModelNG::SetPoints(frameNode, points);
}

namespace NodeModifier {
const ArkUIPolylineModifier* GetPolylineModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIPolylineModifier modifier = {
        .setPoints = SetPoints,
        .resetPoints = ResetPoints,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIPolylineModifier* GetCJUIPolylineModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIPolylineModifier modifier = {
        .setPoints = SetPoints,
        .resetPoints = ResetPoints,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
}
