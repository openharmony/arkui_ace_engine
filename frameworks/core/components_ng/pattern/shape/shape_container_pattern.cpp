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

#include <algorithm>

#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/render/adapter/skia_decoration_painter.h"

namespace OHOS::Ace::NG {
bool ShapeContainerPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    ViewPortTansform();
    return true;
}

void ShapeContainerPattern::ViewPortTansform()
{
    auto curFrameNode = GetHost();
    auto renderContext = curFrameNode->GetRenderContext();
    auto geoNode = curFrameNode->GetGeometryNode();
    if (!geoNode) {
        return;
    }
    SizeF sizeF = geoNode->GetContentSize();
    auto containerPaintProperty = curFrameNode->GetPaintProperty<ContainerPaintProperty>();
    if (containerPaintProperty->HasShapeViewBox() && containerPaintProperty->GetShapeViewBoxValue().IsValid()) {
        double portWidth = containerPaintProperty->GetShapeViewBoxValue().Width().ConvertToPx();
        double portHeight = containerPaintProperty->GetShapeViewBoxValue().Height().ConvertToPx();
        double portLeft = containerPaintProperty->GetShapeViewBoxValue().Left().ConvertToPx();
        double portTop = containerPaintProperty->GetShapeViewBoxValue().Top().ConvertToPx();
        RectF rectF;
        if (sizeF.IsNegative()) {
            rectF = RectF(-1 * portLeft, -1 * portTop, sizeF.Width(), sizeF.Height());
        } else {
            rectF = RectF(-1 * portLeft, -1 * portTop, static_cast<float>(portWidth), static_cast<float>(portHeight));
        }
        renderContext->OnTransformTranslateUpdate({ static_cast<float>(portLeft), static_cast<float>(portTop), 0 });
        renderContext->ClipWithRect(rectF);
    }
}

} // namespace OHOS::Ace::NG