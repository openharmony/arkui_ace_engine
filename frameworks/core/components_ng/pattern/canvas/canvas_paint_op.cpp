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

#include "core/components_ng/pattern/canvas/canvas_paint_op.h"

#include "base/utils/utils.h"
#include "core/components_ng/image_provider/svg_dom_base.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"

namespace OHOS::Ace::NG {
void SaveOp::Draw(CanvasPaintMethod* method) const
{
    method->Save();
}

void RestoreOp::Draw(CanvasPaintMethod* method) const
{
    method->Restore();
}

void FillRectOp::Draw(CanvasPaintMethod* method) const
{
    method->FillRect(rect);
}

void FillTextOp::Draw(CanvasPaintMethod* method) const
{
    method->FillText(text, x, y, maxWidth);
}

void BezierCurveToOp::Draw(CanvasPaintMethod* method) const
{
    method->BezierCurveTo(param);
}

void SetTransformOp::Draw(CanvasPaintMethod* method) const
{
    method->SetTransform(param);
}

void SetFillColorOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFillColor(color);
}

void SetFillGradientOp::Draw(CanvasPaintMethod* method) const
{
    auto ptr = gradient.lock();
    CHECK_NULL_VOID(ptr);
    method->SetFillGradient(*ptr);
}

void SetFillPatternNGOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFillPatternNG(pattern);
}

void SetAlphaOp::Draw(CanvasPaintMethod* method) const
{
    method->SetAlpha(alpha);
}

void SetFillRuleForPathOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFillRuleForPath(rule);
}

void SetFillRuleForPath2DOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFillRuleForPath2D(rule);
}

void FillOp::Draw(CanvasPaintMethod* method) const
{
    method->Fill();
}

void Fill2DOp::Draw(CanvasPaintMethod* method) const
{
    method->Fill(path);
}

void MoveToOp::Draw(CanvasPaintMethod* method) const
{
    method->MoveTo(x, y);
}

void BeginPathOp::Draw(CanvasPaintMethod* method) const
{
    method->BeginPath();
}

void SetFilterParamOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFilterParam(filterStr);
}

void ClosePathOp::Draw(CanvasPaintMethod* method) const
{
    method->ClosePath();
}

void ClearRectOp::Draw(CanvasPaintMethod* method) const
{
    method->ClearRect(rect);
}

void SetStrokeColorOp::Draw(CanvasPaintMethod* method) const
{
    method->SetStrokeColor(color);
}

void SetStrokeGradientOp::Draw(CanvasPaintMethod* method) const
{
    auto ptr = gradient.lock();
    CHECK_NULL_VOID(ptr);
    method->SetStrokeGradient(*ptr);
}

void SetStrokePatternNGOp::Draw(CanvasPaintMethod* method) const
{
    method->SetStrokePatternNG(pattern);
}

void LineToOp::Draw(CanvasPaintMethod* method) const
{
    method->LineTo(x, y);
}

void SetLineJoinOp::Draw(CanvasPaintMethod* method) const
{
    method->SetLineJoin(style);
}

void SetLineCapOp::Draw(CanvasPaintMethod* method) const
{
    method->SetLineCap(style);
}

void SetLineWidthOp::Draw(CanvasPaintMethod* method) const
{
    method->SetLineWidth(width);
}

void SetMiterLimitOp::Draw(CanvasPaintMethod* method) const
{
    method->SetMiterLimit(limit);
}

void StrokeOp::Draw(CanvasPaintMethod* method) const
{
    method->Stroke();
}

void Stroke2DOp::Draw(CanvasPaintMethod* method) const
{
    method->Stroke(path);
}

void SetCompositeTypeOp::Draw(CanvasPaintMethod* method) const
{
    method->SetCompositeType(operation);
}

void ClipOp::Draw(CanvasPaintMethod* method) const
{
    method->Clip();
}

void Clip2DOp::Draw(CanvasPaintMethod* method) const
{
    method->Clip(path);
}

void StrokeRectOp::Draw(CanvasPaintMethod* method) const
{
    method->StrokeRect(rect);
}

void ArcOp::Draw(CanvasPaintMethod* method) const
{
    method->Arc(param);
}

void ArcToOp::Draw(CanvasPaintMethod* method) const
{
    method->ArcTo(param);
}

void AddRectOp::Draw(CanvasPaintMethod* method) const
{
    method->AddRect(rect);
}

void EllipseOp::Draw(CanvasPaintMethod* method) const
{
    method->Ellipse(param);
}

void QuadraticCurveToOp::Draw(CanvasPaintMethod* method) const
{
    method->QuadraticCurveTo(param);
}

void PutImageDataOp::Draw(CanvasPaintMethod* method) const
{
    method->PutImageData(imageData);
}

void ScaleOp::Draw(CanvasPaintMethod* method) const
{
    method->Scale(x, y);
}

void RotateOp::Draw(CanvasPaintMethod* method) const
{
    method->Rotate(angle);
}

void TransformOp::Draw(CanvasPaintMethod* method) const
{
    method->Transform(param);
}

void TranslateOp::Draw(CanvasPaintMethod* method) const
{
    method->Translate(x, y);
}

void SaveLayerOp::Draw(CanvasPaintMethod* method) const
{
    method->SaveLayer();
}

void RestoreLayerOp::Draw(CanvasPaintMethod* method) const
{
    method->RestoreLayer();
}

void SetAntiAliasOp::Draw(CanvasPaintMethod* method) const
{
    method->SetAntiAlias(isEnabled);
}

void SetTextDirectionOp::Draw(CanvasPaintMethod* method) const
{
    method->SetTextDirection(direction);
}

void SetLineDashOffsetOp::Draw(CanvasPaintMethod* method) const
{
    method->SetLineDashOffset(offset);
}

void SetLineDashOp::Draw(CanvasPaintMethod* method) const
{
    method->SetLineDash(segments);
}

void SetTextAlignOp::Draw(CanvasPaintMethod* method) const
{
    method->SetTextAlign(align);
}

void SetTextBaselineOp::Draw(CanvasPaintMethod* method) const
{
    method->SetTextBaseline(baseline);
}

void SetShadowColorOp::Draw(CanvasPaintMethod* method) const
{
    method->SetShadowColor(color);
}

void SetShadowBlurOp::Draw(CanvasPaintMethod* method) const
{
    method->SetShadowBlur(blur);
}

void SetShadowOffsetXOp::Draw(CanvasPaintMethod* method) const
{
    method->SetShadowOffsetX(x);
}

void SetShadowOffsetYOp::Draw(CanvasPaintMethod* method) const
{
    method->SetShadowOffsetY(y);
}

void SetSmoothingEnabledOp::Draw(CanvasPaintMethod* method) const
{
    method->SetSmoothingEnabled(enabled);
}

void SetSmoothingQualityOp::Draw(CanvasPaintMethod* method) const
{
    method->SetSmoothingQuality(quality);
}

void SetFontSizeOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFontSize(size);
}

void SetFontStyleOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFontStyle(style);
}

void SetFontWeightOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFontWeight(weight);
}

void SetFontFamiliesOp::Draw(CanvasPaintMethod* method) const
{
    method->SetFontFamilies(fontFamilies);
}

void DrawSvgImageOp::Draw(CanvasPaintMethod* method) const
{
    method->DrawSvgImage(svgDom, canvasImage, imageFit);
}

void DrawImageOp::Draw(CanvasPaintMethod* method) const
{
    method->DrawImage(canvasImage, width, height);
}

void DrawPixelMapOp::Draw(CanvasPaintMethod* method) const
{
    method->DrawPixelMap(pixelMap, canvasImage);
}

#ifdef PIXEL_MAP_SUPPORTED
void TransferFromImageBitmapOp::Draw(CanvasPaintMethod* method) const
{
    method->TransferFromImageBitmap(pixelMap);
}
#endif

void StrokeTextOp::Draw(CanvasPaintMethod* method) const
{
    method->StrokeText(text, x, y, maxWidth);
}

void ResetCanvasOp::Draw(CanvasPaintMethod* method) const
{
    method->Reset();
}

void ResetTransformOp::Draw(CanvasPaintMethod* method) const
{
    method->ResetTransform();
}

void SetInvalidateOp::Draw(CanvasPaintMethod* method) const {}

void CanvasPaintOp::Draw(CanvasPaintMethod* method) const
{
    Map(DRAW_FNS, method);
}

void CanvasPaintOp::Reset()
{
    Map(DTOR_FBS);
    fUsed = 0;
}

template <typename Fn, typename... Args>
inline void CanvasPaintOp::Map(const Fn fns[], Args... args) const
{
    auto end = fBytes.get() + fUsed;
    for (const uint8_t* ptr = fBytes.get(); ptr < end;) {
        auto op = (const Op*)ptr;
        auto type = op->type;
        auto skip = op->skip;
        if (auto fn = fns[type]) {
            fn(op, args...);
        }
        ptr += skip;
    }
}

} // namespace OHOS::Ace::NG
