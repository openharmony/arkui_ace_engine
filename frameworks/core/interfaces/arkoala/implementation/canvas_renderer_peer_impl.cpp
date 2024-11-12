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
void CanvasRendererPeerImpl::TriggerSetTransform0Impl(const TransformParam& param)
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

void CanvasRendererPeerImpl::TriggerClip0Impl(const std::string& fillRule)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerClip0Impl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Clip();
}

void CanvasRendererPeerImpl::TriggerFill0Impl(const std::string& fillRule)
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerFill0Impl pattern "
             "not bound to component.");
        return;
    }
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Fill();
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



} // namespace OHOS::Ace::NG::GeneratedModifier
