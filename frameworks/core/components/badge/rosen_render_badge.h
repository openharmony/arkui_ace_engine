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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BADGE_ROSEN_RENDER_BADGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BADGE_ROSEN_RENDER_BADGE_H

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/components/badge/render_badge.h"
#include "core/components/common/painter/debug_boundary_painter.h"

namespace OHOS::Ace {

class RosenRenderBadge : public RenderBadge {
    DECLARE_ACE_TYPE(RosenRenderBadge, RenderBadge);

public:
    RosenRenderBadge() = default;
    ~RosenRenderBadge() override = default;

    void Paint(RenderContext& context, const Offset& offset) override;

private:
    void DrawBadge(RenderContext& context, const Offset& offset);
    Size CalculateTextSize(
        const std::string& text, const TextStyle& textStyle, RefPtr<RenderText>& renderText) override;
    void PaintText(const Offset& textOffset, RenderContext& context) const;
#ifndef USE_ROSEN_DRAWING
    void DrawCircleBadge(SkCanvas* canvas, const Offset& offset);
    void DrawNumericalBadge(SkCanvas* canvas, const Offset& offset);
    void RenderBadgeBoundary(SkCanvas* canvas, double startX, double startY, double width, double height);
    void SetBoundaryForNumericalBadge(
        double& boundaryStartX, double& boundaryStartY, SkRRect& rRect, const Offset& offset);
#else
    void DrawCircleBadge(RSCanvas* canvas, const Offset& offset);
    void DrawNumericalBadge(RSCanvas* canvas, const Offset& offset);
    void RenderBadgeBoundary(RSCanvas* canvas, double startX, double startY, double width, double height);
    void SetBoundaryForNumericalBadge(
        double& boundaryStartX, double& boundaryStartY, RSRoundRect& rRect, const Offset& offset);
#endif

    double badgeCircleDiameter_ = 0.0;
    double badgeCircleRadius_ = 0.0;
    double badgeWidth_ = 0.0;
    double badgeHeight_ = 0.0;
    Size textSize_;
    Offset textInitialOffset_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BADGE_ROSEN_RENDER_BADGE_H
