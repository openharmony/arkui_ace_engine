/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/common/container.h"

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/components_ng/pattern/shape/bridge/line_model_impl.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::LineModelImpl* GetLineModelImpl()
{
    static Framework::LineModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

#ifndef CROSS_PLATFORM
void CreateLineImpl()
{
    GetLineModelImpl()->Create();
}
#endif
} // namespace

void CreateLine()
{
    LineModelNG model;
    model.Create();
}

void SetStartPoint(ArkUINodeHandle node, const ArkUI_Float32* pointValues, const ArkUI_Int32* pointUnits,
    const char* pointStr[], void* resObjArray)
{
    ShapePoint point;
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LineModelNG::EndPoint(frameNode, point);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("LineEndPoint");
}

#ifndef CROSS_PLATFORM
void SetStartPointImpl(ArkUINodeHandle node, const ArkUI_Float32* pointValues, const ArkUI_Int32* pointUnits,
    const char* pointStr[], void* resObjArray)
{
    auto* model = GetLineModelImpl();
    CHECK_NULL_VOID(model);
    ShapePoint point;
    point.first = Dimension(pointValues[0], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[0]));
    point.second = Dimension(pointValues[1], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[1]));
    model->StartPoint(point);
}

void ResetStartPointImpl(ArkUINodeHandle node)
{
    auto* model = GetLineModelImpl();
    CHECK_NULL_VOID(model);
    ShapePoint point;
    point.first = 0.0_vp;
    point.second = 0.0_vp;
    model->StartPoint(point);
}

void SetEndPointImpl(ArkUINodeHandle node, const ArkUI_Float32* pointValues, const ArkUI_Int32* pointUnits,
    const char* pointStr[], void* resObjArray)
{
    auto* model = GetLineModelImpl();
    CHECK_NULL_VOID(model);
    ShapePoint point;
    point.first = Dimension(pointValues[0], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[0]));
    point.second = Dimension(pointValues[1], static_cast<OHOS::Ace::DimensionUnit>(pointUnits[1]));
    model->EndPoint(point);
}

void ResetEndPointImpl(ArkUINodeHandle node)
{
    auto* model = GetLineModelImpl();
    CHECK_NULL_VOID(model);
    ShapePoint point;
    point.first = 0.0_vp;
    point.second = 0.0_vp;
    model->EndPoint(point);
}
#endif

namespace NodeModifier {
const ArkUILineModifier* GetLineDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUILineModifier modifier = {
            .createLine = CreateLineImpl,
            .setStartPoint = SetStartPointImpl,
            .resetStartPoint = ResetStartPointImpl,
            .setEndPoint = SetEndPointImpl,
            .resetEndPoint = ResetEndPointImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILineModifier modifier = {
        .createLine = CreateLine,
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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
