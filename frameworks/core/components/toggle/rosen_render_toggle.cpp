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

#include "core/components/toggle/rosen_render_toggle.h"

#ifdef OHOS_PLATFORM
#include "core/components/common/painter/rosen_svg_painter.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

namespace OHOS::Ace {

void RosenRenderToggle::PerformLayout()
{
    RenderToggle::PerformLayout();
    UpdateLayer();
}

void RosenRenderToggle::UpdateLayer()
{
    float translateX = GetLayoutSize().Width() / 2.0 * (1.0 - scale_);
    float translateY = GetLayoutSize().Height() / 2.0 * (1.0 - scale_);
    Matrix4 translateMatrix = Matrix4::CreateTranslate(translateX, translateY, 0.0);
    Matrix4 scaleMatrix = Matrix4::CreateScale(scale_, scale_, 1.0);
    Matrix4 transformMatrix = translateMatrix * scaleMatrix;
    transformLayer_ = transformMatrix;
}

void RosenRenderToggle::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }
    UpdateLayer();
#ifdef OHOS_PLATFORM
    auto recordingCanvas = static_cast<RSRecordingCanvas*>(canvas);
    recordingCanvas->ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(transformLayer_));
#endif
    DrawToggle(canvas, offset);
    RenderNode::Paint(context, offset);
}

Size RosenRenderToggle::Measure()
{
    toggleSize_ = GetLayoutParam().GetMaxSize();
    if (NearEqual(GetLayoutParam().GetMaxSize().Width(), Size::INFINITE_SIZE) || (!widthDefined_)) {
        toggleSize_.SetWidth(0.0);
    }
    return toggleSize_;
}

void RosenRenderToggle::DrawToggle(RSCanvas* canvas, const Offset& offset) const
{
    RSBrush brush;
    brush.SetColor(GetStatusColor().GetValue());
    brush.SetAntiAlias(true);

    double radius = toggleSize_.Height() / 2;
    RSRoundRect rRect(
        RSRect(0, 0, static_cast<RSScalar>(toggleSize_.Width()),
            static_cast<RSScalar>(toggleSize_.Height())),
        radius, radius);
    rRect.Offset(offset.GetX(), offset.GetY());
    canvas->AttachBrush(brush);
    canvas->DrawRoundRect(rRect);
    canvas->DetachBrush();
}

Color RosenRenderToggle::GetStatusColor() const
{
    auto checkColor = toggleComponent_->GetCheckedColor();
    auto pressedColor = toggleComponent_->GetPressedBlendColor();
    auto backgroundColor = toggleComponent_->GetBackgroundColor();
    if (toggleComponent_->GetCheckedState()) {
        if (isPressed_) {
            return checkColor.BlendColor(pressedColor);
        }
        return checkColor;
    }
    if (isPressed_) {
        return backgroundColor.BlendColor(pressedColor);
    }
    return backgroundColor;
}

bool RosenRenderToggle::HasEffectiveTransform() const
{
    return scale_ == 1;
}

} // namespace OHOS::Ace
