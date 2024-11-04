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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_ROSEN_RENDER_CHECKBOX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_ROSEN_RENDER_CHECKBOX_H

#include "core/components/checkable/render_checkbox.h"
#include "core/components/common/painter/rosen_checkable_painter.h"

namespace OHOS::Ace {

class RosenRenderCheckbox : public RenderCheckbox, public RosenCheckablePainter {
    DECLARE_ACE_TYPE(RosenRenderCheckbox, RenderCheckbox);

public:
    RosenRenderCheckbox() = default;
    ~RosenRenderCheckbox() override = default;

    void Paint(RenderContext& context, const Offset& offset) override;

private:
    void DrawCheck(RSCanvas* canvas, const Offset& origin, const RSPen& pen,
        const RSPen& shadowPen) const;
    void DrawActiveBorder(
        RSCanvas* canvas, const Offset& paintOffset, RSPen& strokePen) const;
    void DrawPartSelect(RSCanvas* canvas, const Offset& paintOffset, RSPen& strokePen,
        const RSPen& shadowPen) const;
    void DrawUnselected(
        RSCanvas* canvas, const Offset& origin, uint32_t paintColor, RSPen& pen) const;
    void SetUIStatus(RSCanvas* canvas, const Offset& paintOffset, RSPen& strokePaint,
        RSPen& shadowPaint);
    void DrawBorder(RSCanvas* canvas, const Offset& origin, const Size& paintSize) const;
    void DrawAnimationOffToOn(RSCanvas* canvas, const Offset& origin, const RSPen& pen,
        const RSPen& shadowPen) const;
    void DrawAnimationOnToOff(RSCanvas* canvas, const Offset& origin, const RSPen& pen,
        const RSPen& shadowPen) const;
    void DrawFocusBorder(RenderContext& context, const Offset& offset);
    void DrawTouchBoard(const Offset& offset, RenderContext& context);
    void DrawHoverBoard(const Offset& offset, RenderContext& context);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CHECKABLE_ROSEN_RENDER_CHECKBOX_H
