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

#include "core/components_ng/render/shape_container_painter.h"
#include <algorithm>

#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/shape_painter.h"

namespace OHOS::Ace::NG {
void ShapeContainerPainter::Transform(RSCanvas& canvas,float width,float height,const ShapeViewBox& shapeViewBox,const ImageMesh& imageMesh)
{
    if(shapeViewBox.IsValid() && shapeViewBox.Left().IsValid() && shapeViewBox.Top().IsValid()){
        double scale = std::min(width/shapeViewBox.Width().ConvertToPx(),height/shapeViewBox.Height().ConvertToPx());
        double tx = shapeViewBox.Left().ConvertToPx() * scale;
        double ty = shapeViewBox.Top().ConvertToPx() * scale;
        canvas.Translate(static_cast<RSScalar>(tx),static_cast<RSScalar>(ty));
    }
}
} // namespace OHOS::Ace::NG