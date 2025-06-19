/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/core/components/svg/rosen_render_svg_pattern.h"

#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/components/transform/rosen_render_transform.h"

namespace OHOS::Ace {

void RosenRenderSvgPattern::Paint(RenderContext& context, const Offset& offset)
{
    return;
}

bool RosenRenderSvgPattern::OnAsPaint(const Offset& offset, const Rect& paintRect, RSPen* rsPen, RSBrush* rsBrush)
{
    Rect tileRect;
    RSMatrix matrix4;
    if (!FitAttribute(paintRect, tileRect, matrix4)) {
        LOGW("fit attribute fail.");
        return false;
    }

    RosenRenderContext rosenContext;
    FitRenderContext(rosenContext, tileRect);
    PaintDirectly(rosenContext, offset);

    auto rsPicture = rosenContext.FinishRecordingAsPicture();
    if (!rsPicture) {
        return false;
    }

    RSRect rect = RSRect(tileRect.Left(), tileRect.Top(), tileRect.Right(), tileRect.Bottom());
    auto shaderEffect = RSRecordingShaderEffect::CreatePictureShader(
        *rsPicture, RSTileMode::REPEAT, RSTileMode::REPEAT, RSFilterMode::NEAREST, matrix4, rect);

    if (rsPen != nullptr) {
        rsPen->SetShaderEffect(shaderEffect);
    }
    if (rsBrush != nullptr) {
        rsBrush->SetShaderEffect(shaderEffect);
    }
    return true;
}

bool RosenRenderSvgPattern::FitAttribute(const Rect& paintRect, Rect& tileRect, RSMatrix& matrix4)
{
    if (LessOrEqual(width_.Value(), 0.0) || LessOrEqual(height_.Value(), 0.0)) {
        return false;
    }
    tileRect = Rect(ParseUnitsAttr(x_, paintRect.Width()), ParseUnitsAttr(y_, paintRect.Height()),
        ParseUnitsAttr(width_, paintRect.Width()), ParseUnitsAttr(height_, paintRect.Height()));

    if (NearZero(viewBox_.Width()) || NearZero(viewBox_.Height())) {
        ResetAttrOffset();
        return true;
    }
    scaleX_ = tileRect.Width() / viewBox_.Width();
    scaleY_ = tileRect.Height() / viewBox_.Height();
    scale_ = std::min(scaleX_, scaleY_);
    tx_ = tileRect.Width() * 0.5 - (viewBox_.Width() * 0.5 + viewBox_.Left()) * scale_;
    ty_ = tileRect.Height() * 0.5 - (viewBox_.Height() * 0.5 + viewBox_.Top()) * scale_;

    matrix4 = RosenSvgPainter::ToDrawingMatrix(GetTransform(tileRect));
    return true;
}

const Matrix4 RosenRenderSvgPattern::GetTransform(const Rect& patternRect) const
{
    auto transformInfo = (!animateTransformAttrs_.empty()) ? SvgTransform::CreateInfoFromMap(animateTransformAttrs_)
                                                           : SvgTransform::CreateInfoFromString(transform_);
    if (!NearZero(patternRect.Left()) || !NearZero(patternRect.Top())) {
        transformInfo.matrix4 =
            Matrix4::CreateTranslate(patternRect.Left(), patternRect.Top(), 0) * transformInfo.matrix4;
    }

    if (transformInfo.hasRotateCenter) {
        transformInfo.matrix4 =
            RosenRenderTransform::GetTransformByOffset(transformInfo.matrix4, transformInfo.rotateCenter);
    }

    transformInfo.matrix4 = RosenRenderTransform::GetTransformByOffset(transformInfo.matrix4, GetGlobalOffset());
    return transformInfo.matrix4;
}

void RosenRenderSvgPattern::FitRenderContext(RosenRenderContext& context, const Rect& patternRect)
{
    Rect rect(patternRect.Left(), patternRect.Top(), patternRect.Width() / scaleX_, patternRect.Height() / scaleY_);
    context.InitContext(GetRSNode(), rect);
    context.StartRecording();

    auto* canvas = context.GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    canvas->Scale(SkDoubleToScalar(scale_), SkDoubleToScalar(scale_));
}

void RosenRenderSvgPattern::ResetAttrOffset()
{
    scaleY_ = 1.0f;
    scaleX_ = 1.0f;
    scale_ = 1.0f;
    tx_ = 0.0f;
    ty_ = 0.0f;
}

} // namespace OHOS::Ace
