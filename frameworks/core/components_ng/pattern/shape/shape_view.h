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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_VIEW_H

#include "base/geometry/dimension.h"
#include "base/geometry/ng/image_mesh.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/shape/shape_view_box.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ShapeView {
public:
    ShapeView() = default;
    ~ShapeView() = default;
    static void Create();
    static void SetStroke(const Color& color);
    static void SetFill(const Color& color);
    static void SetStrokeDashOffset(const Ace::Dimension& dashOffset);
    static void SetStrokeLineCap(int lineCapStyle);
    static void SetStrokeLineJoin(int lineJoinStyle);
    static void SetStrokeMiterLimit(double miterLimit);
    static void SetStrokeOpacity(double opacity);
    static void SetFillOpacity(double opacity);
    static void SetStrokeWidth(const Ace::Dimension& lineWidth);
    static void SetStrokeDashArray(const std::vector<Ace::Dimension>& segments);
    static void SetAntiAlias(bool antiAlias);
    static void SetBitmapMesh(const ImageMesh& imageMesh);
    static void SetViewPort(const ShapeViewBox& viewBox);
};

} // namespace OHOS::Ace::NG

#endif