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
#include "core/interfaces/native/node/polygon_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"

namespace OHOS::Ace::NG {
void SetPolygonPoints(ArkUINodeHandle node, const ArkUI_Float32* pointX, const ArkUI_Float32* pointY, int32_t length,
    void* xResObjArray, void* yResObjArray)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("PolygonPoints");
    ShapePoint shapePoint;
    ShapePoints shapePoints;
    std::vector<RefPtr<ResourceObject>> xResObjArrayResult;
    std::vector<RefPtr<ResourceObject>> yResObjArrayResult;
    RefPtr<ResourceObject>* xResObjPtr = static_cast<RefPtr<ResourceObject>*>(xResObjArray);
    RefPtr<ResourceObject>* yResObjPtr = static_cast<RefPtr<ResourceObject>*>(yResObjArray);
    bool hasResObj = false;
    for (int32_t i = 0; i < length; i++) {
        auto xVal = pointX[i];
        auto yVal = pointY[i];
        if (xResObjPtr[i] || yResObjPtr[i]) {
            hasResObj = true;
        }
        xResObjArrayResult.push_back(xResObjPtr[i]);
        yResObjArrayResult.push_back(yResObjPtr[i]);
        shapePoint.first = Dimension(xVal, DimensionUnit::VP);
        shapePoint.second = Dimension(yVal, DimensionUnit::VP);
        shapePoints.push_back(shapePoint);
    }
    if (SystemProperties::ConfigChangePerform() && hasResObj) {
        PolygonModelNG::SetPoints(frameNode, shapePoints, xResObjArrayResult, yResObjArrayResult);
    }

    PolygonModelNG::SetPoints(frameNode, shapePoints);
}

void ResetPolygonPoints(ArkUINodeHandle node)
{
    ShapePoints points;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PolygonModelNG::SetPoints(frameNode, points);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("PolygonPoints");
}

namespace NodeModifier {
const ArkUIPolygonModifier* GetPolygonModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIPolygonModifier modifier = {
        .setPolygonPoints = SetPolygonPoints,
        .resetPolygonPoints = ResetPolygonPoints,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIPolygonModifier* GetCJUIPolygonModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIPolygonModifier modifier = {
        .setPolygonPoints = SetPolygonPoints,
        .resetPolygonPoints = ResetPolygonPoints,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
