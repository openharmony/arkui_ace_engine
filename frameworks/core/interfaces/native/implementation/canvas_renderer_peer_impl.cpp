/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "canvas_renderer_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {

void CanvasRendererPeerImpl::TriggerBeginPathImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerBeginPathImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->BeginPath();
}
void CanvasRendererPeerImpl::TriggerStroke0Impl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerStroke0Impl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Stroke();
}
void CanvasRendererPeerImpl::TriggerRestoreImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerRestoreImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Restore();
}
void CanvasRendererPeerImpl::TriggerSaveImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSaveImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Save();
}
void CanvasRendererPeerImpl::TriggerResetTransformImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerResetTransformImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->ResetTransform();
}
void CanvasRendererPeerImpl::TriggerSaveLayerImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSaveLayerImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->SaveLayer();
}
void CanvasRendererPeerImpl::TriggerRestoreLayerImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerRestoreLayerImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->RestoreLayer();
}
void CanvasRendererPeerImpl::TriggerResetImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerResetImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Reset();
}
std::optional<LineDashParam> CanvasRendererPeerImpl::TriggerGetLineDashImpl()
{
    auto opt = std::make_optional<LineDashParam>();
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerGetLineDashImpl pattern "
             "not bound to component.");
        return opt;
    }
    opt = pattern_->GetLineDash();
    return opt;
}
void CanvasRendererPeerImpl::TriggerSetLineDashImpl(const std::vector<double>& segments)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetLineDashImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateLineDash(segments);
}
void CanvasRendererPeerImpl::TriggerClearRectImpl(const Rect& rect)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerClearRect pattern "
             "not bound to component.");
        return;
    }
    pattern_->ClearRect(rect);
}
void CanvasRendererPeerImpl::TriggerFillRectImpl(const Rect& rect)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerFillRect pattern "
             "not bound to component.");
        return;
    }
    pattern_->FillRect(rect);
}
void CanvasRendererPeerImpl::TriggerStrokeRectImpl(const Rect& rect)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerFillRect pattern "
             "not bound to component.");
        return;
    }
    pattern_->StrokeRect(rect);
}
void CanvasRendererPeerImpl::TriggerRotateImpl(double angle)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerRotate pattern "
             "not bound to component.");
        return;
    }
    pattern_->Rotate(angle);
}
void CanvasRendererPeerImpl::TriggerScaleImpl(double x, double y)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerScale pattern "
             "not bound to component.");
        return;
    }
    pattern_->Scale(x, y);
}
void CanvasRendererPeerImpl::TriggerTranslateImpl(double x, double y)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerTranslate pattern "
             "not bound to component.");
        return;
    }
    pattern_->Translate(x, y);
}
void CanvasRendererPeerImpl::TriggerSetGlobalAlphaImpl(double alpha)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerUpdateGlobalAlpha pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateGlobalAlpha(alpha);
}
void CanvasRendererPeerImpl::TriggerFillTextImpl(
    const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerFillTextImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->FillText(text, x, y, maxWidth);
}
void CanvasRendererPeerImpl::TriggerStrokeTextImpl(
    const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerStrokeTextImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->StrokeText(text, x, y, maxWidth);
}
void CanvasRendererPeerImpl::TriggerSetTransformImpl(const TransformParam& param)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetTransform0Impl pattern "
             "not bound to component.");
        return;
    }
    pattern_->SetTransform(param);
}
void CanvasRendererPeerImpl::TriggerTransformImpl(const TransformParam& param)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerTransformImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Transform(param);
}
void CanvasRendererPeerImpl::TriggerSetGlobalCompositeOperationImpl(CompositeOperation& type)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetGlobalCompositeOperationImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateCompositeOperation(type);
}
void CanvasRendererPeerImpl::TriggerSetFilterImpl(const std::string& filterStr)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetFilterImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->SetFilterParam(filterStr);
}
void CanvasRendererPeerImpl::TriggerSetImageSmoothingEnabledImpl(bool enabled)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetImageSmoothingEnabledImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateSmoothingEnabled(enabled);
}
void CanvasRendererPeerImpl::TriggerSetLineDashOffsetImpl(double dash)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetLineDashOffsetImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateLineDashOffset(dash);
}
void CanvasRendererPeerImpl::TriggerSetLineWidthImpl(double width)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetLineWidthImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateLineWidth(width);
}
void CanvasRendererPeerImpl::TriggerSetMiterLimitImpl(double limit)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetMiterLimitImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateMiterLimit(limit);
}
void CanvasRendererPeerImpl::TriggerSetShadowBlurImpl(double blur)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetShadowBlurImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateShadowBlur(blur);
}
void CanvasRendererPeerImpl::TriggerSetShadowColorImpl(Color& color)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetShadowColorImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateShadowColor(color);
}
void CanvasRendererPeerImpl::TriggerSetShadowOffsetXImpl(double offsetX)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetShadowOffsetXImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateShadowOffsetX(offsetX);
}
void CanvasRendererPeerImpl::TriggerSetShadowOffsetYImpl(double offsetY)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetShadowOffsetYImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateShadowOffsetY(offsetY);
}
void CanvasRendererPeerImpl::TriggerStroke1Impl(const RefPtr<CanvasPath2D>& path)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerStroke1Impl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Stroke(path);
}
#ifdef PIXEL_MAP_SUPPORTED
void CanvasRendererPeerImpl::TriggerTransferFromImageBitmapImpl(const RefPtr<PixelMap>& pixelMap)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerTransferFromImageBitmapImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->TransferFromImageBitmap(pixelMap);
}
#else
void CanvasRendererPeerImpl::TriggerTransferFromImageBitmapImpl(const double width, const double height)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerTransferFromImageBitmapImpl pattern "
             "not bound to component.");
        return;
    }
    auto imageData = pattern_->GetImageData(0, 0, width, height);
    CHECK_NULL_VOID(imageData);
    pattern_->TransferFromImageBitmap(*imageData);
}
#endif
void CanvasRendererPeerImpl::TriggerSetFillStyleImpl(const Color& color)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetFillStyleImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateFillColor(color);
}
void CanvasRendererPeerImpl::TriggerSetFillStyleImpl(const std::shared_ptr<Ace::Gradient>& gradient)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetFillStyleImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->SetFillGradient(gradient);
}
void CanvasRendererPeerImpl::TriggerSetFillStyleImpl(const std::weak_ptr<Ace::Pattern>& pattern)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetFillStyleImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateFillPattern(pattern);
}
void CanvasRendererPeerImpl::TriggerSetStrokeStyleImpl(const Color& color)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetStrokeStyleImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateStrokeColor(color);
}
void CanvasRendererPeerImpl::TriggerSetStrokeStyleImpl(const std::shared_ptr<Ace::Gradient>& gradient)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetStrokeStyleImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->SetStrokeGradient(gradient);
}
void CanvasRendererPeerImpl::TriggerSetStrokeStyleImpl(const std::weak_ptr<Ace::Pattern>& pattern)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSetStrokeStyleImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateStrokePattern(pattern);
}
void CanvasRendererPeerImpl::TriggerUpdateFontWeight(Ace::FontWeight weight)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerUpdateFontWeight pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateFontWeight(weight);
}
void CanvasRendererPeerImpl::TriggerUpdateFontStyle(Ace::FontStyle style)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerUpdateFontStyle pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateFontStyle(style);
}
void CanvasRendererPeerImpl::TriggerUpdateFontFamilies(const std::vector<std::string>& families)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerUpdateFontFamilies pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateFontFamilies(families);
}
void CanvasRendererPeerImpl::TriggerUpdateFontSize(const Dimension& size)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerUpdateFontSize pattern "
             "not bound to component.");
        return;
    }

    pattern_->UpdateFontSize(size);
}

} // namespace OHOS::Ace::NG::GeneratedModifier
