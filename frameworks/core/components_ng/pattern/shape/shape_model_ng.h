/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_MODEL_NG_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ShapeModelNG : public ShapeModel {
public:
    void Create() override;
    void SetBitmapMesh(const std::vector<float>& mesh, int32_t column, int32_t row) override;
    void SetViewPort(const Dimension& dimLeft, const Dimension& dimTop, const Dimension& dimWidth,
        const Dimension& dimHeight) override;
    void SetViewPort(
        const std::vector<Dimension>& dimArray, const std::vector<RefPtr<ResourceObject>>& resObjArray) override;
    void InitBox(const RefPtr<PixelMap>& pixMap) override;
    void SetStroke(const Color& color) override;
    void SetFill(const Color& color) override;
    void SetForegroundColor(const Color& color) override;
    void SetStrokeDashOffset(const Ace::Dimension& dashOffset) override;
    void SetStrokeLineCap(int lineCapStyle) override;
    void SetStrokeLineJoin(int lineJoinStyle) override;
    void SetStrokeMiterLimit(double miterLimit) override;
    void SetStrokeOpacity(double opacity) override;
    void SetFillOpacity(double opacity) override;
    void SetStrokeWidth(const Ace::Dimension& lineWidth) override;
    void SetStrokeDashArray(const std::vector<Ace::Dimension>& segments) override;
    void SetStrokeDashArray(
        const std::vector<Ace::Dimension>& segments, const std::vector<RefPtr<ResourceObject>>& resObjArray) override;
    void SetAntiAlias(bool antiAlias) override;
    void SetWidth() override {}
    void SetHeight() override {}
    static void SetStrokeDashArray(FrameNode* frameNode, const std::vector<Ace::Dimension>& segments);
    static void SetStrokeDashArray(FrameNode* frameNode, const std::vector<Ace::Dimension>& segments,
        const std::vector<RefPtr<ResourceObject>>& resObjArray);
    static void SetStrokeMiterLimit(FrameNode* frameNode, double miterLimit);
    static void SetFillOpacity(FrameNode* frameNode, double fillOpacity);
    static void SetStrokeOpacity(FrameNode* frameNode, double strokeOpacity);
    static void SetStrokeWidth(FrameNode* frameNode, const Ace::Dimension& strokeWidth);
    static void SetAntiAlias(FrameNode* frameNode, bool antiAlias);
    static void SetStroke(FrameNode* frameNode, const Color& color);
    static void SetFill(FrameNode* frameNode, const Color& color);
    static void SetStrokeDashOffset(FrameNode* frameNode, const Ace::Dimension& dashOffset);
    static void SetStrokeLineCap(FrameNode* frameNode, int lineCapStyle);
    static void SetStrokeLineJoin(FrameNode* frameNode, int lineJoinStyle);
    static void SetViewPort(FrameNode* frameNode, const Dimension& dimLeft, const Dimension& dimTop,
        const Dimension& dimWidth, const Dimension& dimHeight);
    static void SetViewPort(FrameNode* frameNode, const std::vector<Dimension>& dimArray,
        const std::vector<RefPtr<ResourceObject>>& resObjArray);
    static void SetBitmapMesh(FrameNode* frameNode, const std::vector<float>& mesh, int32_t column, int32_t row);
    static void SetWidth(FrameNode* frameNode) {}
    static void SetHeight(FrameNode* frameNode) {}
    static void InitBox(FrameNode* frameNode, const RefPtr<PixelMap>& pixMap);
};

} // namespace OHOS::Ace::NG

#endif