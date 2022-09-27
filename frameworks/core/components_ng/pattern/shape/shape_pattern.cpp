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

#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
bool ShapePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    ViewPortTansfer();
    return true;
}

void ShapePattern::ViewPortTansfer()
{
    auto curFrameNode = GetHost();
    auto renderContext = DynamicCast<RosenRenderContext>(curFrameNode->GetRenderContext());
    auto rsNode = renderContext->GetRSNode();
    if (!rsNode) {
        return;
    }
    auto geoNode = curFrameNode->GetGeometryNode();
    if (!geoNode) {
        return;
    }
    SizeF sizeF = geoNode->GetContentSize();
    auto containerPaintProperty = curFrameNode->GetPaintProperty<ContainerPaintProperty>();
    if (containerPaintProperty->HasShapeViewBox()) {
        if (containerPaintProperty->GetShapeViewBoxValue().IsValid()) {
            double portWidth = containerPaintProperty->GetShapeViewBoxValue().Width().ConvertToPx();
            double portHeight = containerPaintProperty->GetShapeViewBoxValue().Height().ConvertToPx();
            double portLeft = containerPaintProperty->GetShapeViewBoxValue().Left().ConvertToPx();
            double protTop = containerPaintProperty->GetShapeViewBoxValue().Top().ConvertToPx();
            double scale = std::min(sizeF.Width() / portWidth, sizeF.Height() / portHeight);
            double tx = sizeF.Width() * 0.5 - (portWidth * 0.5 + portLeft) * scale;
            double ty = sizeF.Height() * 0.5 - (portHeight * 0.5 + protTop) * scale;
            rsNode->SetClipToFrame(true);
            for (const auto child : curFrameNode->GetChildren()) {
                auto childFrameNode = DynamicCast<FrameNode>(child);
                if (!childFrameNode) {
                    continue;
                }
                auto childRenderContext = DynamicCast<RosenRenderContext>(curFrameNode->GetRenderContext());
                auto childRsNode = childRenderContext->GetRSNode();
                if (!childRsNode) {
                    continue;
                }
                childRsNode->SetPivot(0.0f, 0.0f);
                childRsNode->SetScale(static_cast<float>(scale));
                childRsNode->SetTranslate({ static_cast<float>(tx), static_cast<float>(ty) });
            }
        }
    }
}

} // namespace OHOS::Ace::NG