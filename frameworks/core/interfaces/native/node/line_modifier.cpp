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
#include "core/interfaces/native/node/line_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"

namespace OHOS::Ace::NG {
void SetStartPoint(ArkUINodeHandle node, const ArkUI_Float32* pointValues, const ArkUI_Int32* pointUnits,
    const char* pointStr[], void* resObjArray)
{
    ShapePoint point;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("LineStartPoint");
    point.first = Dimension(pointValues[0], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[0]));
    point.second = Dimension(pointValues[1], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[1]));
    RefPtr<ResourceObject>* resObjPtr = static_cast<RefPtr<ResourceObject>*>(resObjArray);
    if (SystemProperties::ConfigChangePerform() && (resObjPtr[0] || resObjPtr[1])) {
        std::vector<RefPtr<ResourceObject>> resObjArrayResult = { resObjPtr[0], resObjPtr[1] };
        LineModelNG::StartPoint(frameNode, point, resObjArrayResult);
    }
    LineModelNG::StartPoint(frameNode, point);
}

void ResetStartPoint(ArkUINodeHandle node)
{
    ShapePoint point;
    point.first = 0.0_vp;
    point.second = 0.0_vp;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LineModelNG::StartPoint(frameNode, point);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("LineStartPoint");
}

void SetEndPoint(ArkUINodeHandle node, const ArkUI_Float32* pointValues, const ArkUI_Int32* pointUnits,
    const char* pointStr[], void* resObjArray)
{
    ShapePoint point;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("LineEndPoint");
    point.first = Dimension(pointValues[0], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[0]));
    point.second = Dimension(pointValues[1], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[1]));
    RefPtr<ResourceObject>* resObjPtr = static_cast<RefPtr<ResourceObject>*>(resObjArray);
    if (SystemProperties::ConfigChangePerform() && (resObjPtr[0] || resObjPtr[1])) {
        std::vector<RefPtr<ResourceObject>> resObjArrayResult = { resObjPtr[0], resObjPtr[1] };
        LineModelNG::EndPoint(frameNode, point, resObjArrayResult);
    }
    LineModelNG::EndPoint(frameNode, point);
}

void ResetEndPoint(ArkUINodeHandle node)
{
    ShapePoint point;
    point.first = 0.0_vp;
    point.second = 0.0_vp;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LineModelNG::EndPoint(frameNode, point);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("LineEndPoint");
}

namespace NodeModifier {
const ArkUILineModifier* GetLineModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILineModifier modifier = {
        .setStartPoint = SetStartPoint,
        .resetStartPoint = ResetStartPoint,
        .setEndPoint = SetEndPoint,
        .resetEndPoint = ResetEndPoint,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUILineModifier* GetCJUILineModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUILineModifier modifier = {
        .setStartPoint = SetStartPoint,
        .resetStartPoint = ResetStartPoint,
        .setEndPoint = SetEndPoint,
        .resetEndPoint = ResetEndPoint,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
}
