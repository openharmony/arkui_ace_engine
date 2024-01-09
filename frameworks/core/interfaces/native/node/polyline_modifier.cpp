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

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "base/geometry/shape.h"

namespace OHOS::Ace::NG {

void SetPoints(NodeHandle node, const double* pointX, const double* pointY, int32_t length)
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

void ResetPoints(NodeHandle node)
{
    ShapePoints points;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PolygonModelNG::SetPoints(frameNode, points);
}

ArkUIPolylineModifierAPI GetPolylineModifier()
{
    static const ArkUIPolylineModifierAPI modifier = {SetPoints, ResetPoints};

    return modifier;
}
}