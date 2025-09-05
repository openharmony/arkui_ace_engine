/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/tab_bar/rosen_render_tab_bar_item.h"

#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

namespace {

constexpr double CLICKED_RADIUS = 8.0;

} // namespace

void RosenRenderTabBarItem::Paint(RenderContext& context, const Offset& offset)
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (!rsNode) {
        return;
    }
    rsNode->SetClipToFrame(true);
    RenderNode::Paint(context, offset);

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }

    pipelineContext->AddDirtyLayoutNode(AceType::Claim(this));

    double dipScale = pipelineContext->GetDipScale();

    rsNode->SetForegroundColor(Color::BLACK.BlendOpacity(hoverOpacity_).GetValue());
    rsNode->SetCornerRadius(Dimension(CLICKED_RADIUS, DimensionUnit::VP).ConvertToPx(dipScale));
    RenderTabBarItemBoundary(context, offset, GetLayoutSize().Width(), GetLayoutSize().Height());
}

void RosenRenderTabBarItem::RenderTabBarItemBoundary(RenderContext& context, const Offset& offset,
    double width, double height)
{
    if (SystemProperties::GetDebugBoundaryEnabled()) {
        auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
        if (rsNode == nullptr) {
            LOGE("Paint rsNode is null.");
            return;
        }
#ifndef USE_ROSEN_DRAWING
        rsNode->DrawOnNode(Rosen::ModifierNG::RSModifierType::OVERLAY_STYLE,
            [offset, layoutSize = Size(width, height)](std::shared_ptr<SkCanvas> canvas) {
                DebugBoundaryPainter::PaintDebugBoundary(canvas.get(), offset, layoutSize);
                DebugBoundaryPainter::PaintDebugCorner(canvas.get(), offset, layoutSize);
            });
#else
        rsNode->DrawOnNode(Rosen::ModifierNG::RSModifierType::OVERLAY_STYLE,
            [offset, layoutSize = Size(width, height)](std::shared_ptr<RSCanvas> canvas) {
                DebugBoundaryPainter::PaintDebugBoundary(canvas.get(), offset, layoutSize);
                DebugBoundaryPainter::PaintDebugCorner(canvas.get(), offset, layoutSize);
            });
#endif
    }
}

} // namespace OHOS::Ace
