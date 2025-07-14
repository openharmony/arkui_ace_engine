/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_MODEL_STATIC_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ShapeModelStatic {
public:
    static void InitBox(FrameNode* frameNode, const RefPtr<PixelMap>& pixMap);
    static void SetStrokeMiterLimit(FrameNode* frameNode, const std::optional<double>& miterLimit);
    static void SetFillOpacity(FrameNode* frameNode, const std::optional<double>& fillOpacity);
    static void SetStrokeOpacity(FrameNode* frameNode, const std::optional<double>& strokeOpacity);
    static void SetStrokeWidth(FrameNode* frameNode, const std::optional<Ace::Dimension>& strokeWidth);
    static void SetStroke(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetFill(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetStrokeDashOffset(FrameNode* frameNode, const std::optional<Ace::Dimension>& dashOffset);
    static void SetStrokeLineCap(FrameNode* frameNode, const std::optional<int>& lineCapStyle);
    static void SetStrokeLineJoin(FrameNode* frameNode, const std::optional<int>& lineJoinStyle);
    static void SetViewPort(FrameNode* frameNode,
        const std::optional<Dimension>& dimLeft, const std::optional<Dimension>& dimTop,
        const std::optional<Dimension>& dimWidth, const std::optional<Dimension>& dimHeight);
    static RefPtr<NG::FrameNode> CreateFrameNode(int32_t nodeId);
};

} // namespace OHOS::Ace::NG

#endif
