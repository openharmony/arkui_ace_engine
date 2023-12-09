/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_MODEL_NG_CPP
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_MODEL_NG_CPP

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/pattern/shape/polygon_paint_property.h"
#include "core/components_ng/pattern/shape/polygon_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void PolygonModelNG::Create(bool isPolygon)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", isPolygon ? V2::POLYGON_ETS_TAG : V2::POLYLINE_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        isPolygon ? V2::POLYGON_ETS_TAG : V2::POLYLINE_ETS_TAG,
        nodeId, [isPolygon]() { return AceType::MakeRefPtr<PolygonPattern>(isPolygon); });
    stack->Push(frameNode);
}

void PolygonModelNG::SetPoints(const ShapePoints& points)
{
    ACE_UPDATE_PAINT_PROPERTY(PolygonPaintProperty, Points, points);
}

void PolygonModelNG::SetPoints(FrameNode* frameNode, const ShapePoints& points)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PolygonPaintProperty, Points, points, frameNode);
}

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_MODEL_NG_CPP
