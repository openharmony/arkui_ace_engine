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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PAINT_METHOD_H

#include "ui/rs_node.h"
#include "base/geometry/ng/image_mesh.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/pattern/shape/shape_view_box.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/shape_container_painter.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ContainerPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ContainerPaintMethod, NodePaintMethod)
public:
    ContainerPaintMethod(float width, float height, ShapeViewBox& shapeViewBox, ImageMesh& imageMesh,Rosen::RSNode& rsNode)
        : width_(width), height_(height), shapeViewBox_(shapeViewBox), imageMesh_(imageMesh)
    {}
    ~ContainerPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        auto shapePaintProperty = DynamicCast<ShapePaintProperty>(paintWrapper->GetPaintProperty());
        if (!shapePaintProperty) {
            return nullptr;
        }


        return [shapePaintProperty, width = width_, height = height_, shapeViewBox = shapeViewBox_,
                   imageMesh = imageMesh_](RSCanvas& canvas) {
            ShapeContainerPainter::Transform(canvas, width, height, shapeViewBox, imageMesh);
        };
    }

private:
    float width_;
    float height_;
    ShapeViewBox shapeViewBox_;
    ImageMesh imageMesh_;
    ACE_DISALLOW_COPY_AND_MOVE(ContainerPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PAINT_METHOD_H