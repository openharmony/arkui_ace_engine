/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/canvas_renderer_model_impl.h"

#include "core/components/custom_paint/custom_paint_component.h"
#include "core/components/custom_paint/offscreen_canvas.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#endif

namespace OHOS::Ace::Framework {
void CanvasRendererModelImpl::SetFillText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->FillText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, baseInfo.paintState);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->FillText(fillTextInfo.text, Offset(fillTextInfo.x, fillTextInfo.y));
    }
}

void CanvasRendererModelImpl::SetStrokeText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->StrokeText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, baseInfo.paintState);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->StrokeText(fillTextInfo.text, Offset(fillTextInfo.x, fillTextInfo.y));
    }
}

void CanvasRendererModelImpl::SetAntiAlias(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetAntiAlias(baseInfo.anti);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->SetAntiAlias(baseInfo.anti);
    }
}

void CanvasRendererModelImpl::SetFontWeight(const BaseInfo& baseInfo, const FontWeight& weight)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFontWeight(weight);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontWeight(weight);
    }
}

void CanvasRendererModelImpl::SetFontStyle(const BaseInfo& baseInfo, const FontStyle& fontStyle)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFontStyle(fontStyle);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontStyle(fontStyle);
    }
}

void CanvasRendererModelImpl::SetFontFamilies(const BaseInfo& baseInfo, const std::vector<std::string>& families)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFontFamilies(families);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontFamilies(families);
    }
}

void CanvasRendererModelImpl::SetFontSize(const BaseInfo& baseInfo, const Dimension& size)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFontSize(size);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontSize(size);
    }
}

std::vector<double> CanvasRendererModelImpl::GetLineDash(const BaseInfo& baseInfo)
{
    std::vector<double> lineDash {};
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, lineDash);
        lineDash = offscreenPattern->GetLineDash().lineDash;
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, lineDash);
        lineDash = canvasPattern->GetLineDash().lineDash;
    }

    return lineDash;
}

void CanvasRendererModelImpl::SetFillGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillGradient(gradient);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillGradient(gradient);
    }
}

void CanvasRendererModelImpl::SetFillPattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillPattern(*(pattern.get()));
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillPattern(*(pattern.get()));
    }
}

void CanvasRendererModelImpl::SetFillColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag)
{
    if (!colorFlag) {
        return;
    }

    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillColor(color);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillColor(color);
    }
}

void CanvasRendererModelImpl::SetStrokeGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetStrokeGradient(gradient);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateStrokeGradient(gradient);
    }
}

void CanvasRendererModelImpl::SetStrokePattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetStrokePattern(*(pattern.get()));
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateStrokePattern(*(pattern.get()));
    }
}

void CanvasRendererModelImpl::SetStrokeColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag)
{
    if (!colorFlag) {
        return;
    }

    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetStrokeColor(color);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateStrokeColor(color);
    }
}

void CanvasRendererModelImpl::DrawImage(const BaseInfo& baseInfo, const ImageInfo& imageInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (imageInfo.isImage) {
            offscreenPattern->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
            return;
        }
        offscreenPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        if (imageInfo.isImage) {
            canvasPattern->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
            return;
        }
        canvasPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
    }
}

void CanvasRendererModelImpl::PutImageData(const BaseInfo& baseInfo, const ImageData& imageData)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->PutImageData(imageData);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->PutImageData(imageData);
    }
}

std::unique_ptr<ImageData> CanvasRendererModelImpl::GetImageData(const BaseInfo& baseInfo, const ImageSize& imageSize)
{
    std::unique_ptr<ImageData> data;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, data);
        data = offscreenPattern->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height);
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, data);
        data = canvasPattern->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height);
    }
    return data;
}

void CanvasRendererModelImpl::DrawPixelMap(const BaseInfo& baseInfo, const ImageInfo& imageInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
    }
}

std::string CanvasRendererModelImpl::GetJsonData(const BaseInfo& baseInfo, const std::string& path)
{
    std::string jsonData = "";
    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, jsonData);
        jsonData = canvasPattern->GetJsonData(path);
    }
    return jsonData;
}

std::string CanvasRendererModelImpl::ToDataURL(const BaseInfo& baseInfo, const std::string& dataUrl, double quality)
{
    std::string result = "";
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, result);
        result = offscreenPattern->ToDataURL(dataUrl, quality);
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, result);
        result = canvasPattern->ToDataURL(dataUrl + "," + std::to_string(quality));
    }
    return result;
}

void CanvasRendererModelImpl::SetLineCap(const BaseInfo& baseInfo, const LineCapStyle& lineCap)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetLineCap(lineCap);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineCap(lineCap);
    }
}

void CanvasRendererModelImpl::SetLineJoin(const BaseInfo& baseInfo, const LineJoinStyle& lineJoin)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetLineJoin(lineJoin);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineJoin(lineJoin);
    }
}

void CanvasRendererModelImpl::SetMiterLimit(const BaseInfo& baseInfo, double limit)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetMiterLimit(limit);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateMiterLimit(limit);
    }
}

void CanvasRendererModelImpl::SetLineWidth(const BaseInfo& baseInfo, double lineWidth)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetLineWidth(lineWidth);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineWidth(lineWidth);
    }
}

void CanvasRendererModelImpl::SetGlobalAlpha(const BaseInfo& baseInfo, double alpha)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetAlpha(alpha);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateGlobalAlpha(alpha);
    }
}

void CanvasRendererModelImpl::SetCompositeType(const BaseInfo& baseInfo, const CompositeOperation& type)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetCompositeType(type);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateCompositeOperation(type);
    }
}

void CanvasRendererModelImpl::SetLineDashOffset(const BaseInfo& baseInfo, double lineDashOffset)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetLineDashOffset(lineDashOffset);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineDashOffset(lineDashOffset);
    }
}

void CanvasRendererModelImpl::SetShadowBlur(const BaseInfo& baseInfo, double blur)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetShadowBlur(blur);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowBlur(blur);
    }
}

void CanvasRendererModelImpl::SetShadowColor(const BaseInfo& baseInfo, const Color& color)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetShadowColor(color);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowColor(color);
    }
}

void CanvasRendererModelImpl::SetShadowOffsetX(const BaseInfo& baseInfo, double offsetX)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetShadowOffsetX(offsetX);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowOffsetX(offsetX);
    }
}

void CanvasRendererModelImpl::SetShadowOffsetY(const BaseInfo& baseInfo, double offsetY)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetShadowOffsetY(offsetY);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowOffsetY(offsetY);
    }
}

void CanvasRendererModelImpl::SetSmoothingEnabled(const BaseInfo& baseInfo, bool enabled)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetSmoothingEnabled(enabled);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateSmoothingEnabled(enabled);
    }
}

void CanvasRendererModelImpl::SetSmoothingQuality(const BaseInfo& baseInfo, const std::string& quality)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetSmoothingQuality(quality);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateSmoothingQuality(quality);
    }
}

void CanvasRendererModelImpl::MoveTo(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->MoveTo(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->MoveTo(x, y);
    }
}

void CanvasRendererModelImpl::LineTo(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->LineTo(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->LineTo(x, y);
    }
}

void CanvasRendererModelImpl::BezierCurveTo(const BaseInfo& baseInfo, const BezierCurveParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->BezierCurveTo(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->BezierCurveTo(param);
    }
}

void CanvasRendererModelImpl::QuadraticCurveTo(const BaseInfo& baseInfo, const QuadraticCurveParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->QuadraticCurveTo(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->QuadraticCurveTo(param);
    }
}

void CanvasRendererModelImpl::ArcTo(const BaseInfo& baseInfo, const ArcToParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->ArcTo(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ArcTo(param);
    }
}

void CanvasRendererModelImpl::Arc(const BaseInfo& baseInfo, const ArcParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Arc(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Arc(param);
    }
}

void CanvasRendererModelImpl::Ellipse(const BaseInfo& baseInfo, const EllipseParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Ellipse(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Ellipse(param);
    }
}

void CanvasRendererModelImpl::SetFillRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillRuleForPath(fillRule);
        offscreenPattern->Fill();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath(fillRule);
        canvasPattern->Fill();
    }
}

void CanvasRendererModelImpl::SetFillRuleForPath2D(
    const BaseInfo& baseInfo, const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillRuleForPath2D(fillRule);
        offscreenPattern->Fill(path);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath2D(fillRule);
        canvasPattern->Fill(path);
    }
}

void CanvasRendererModelImpl::SetStrokeRuleForPath2D(
    const BaseInfo& baseInfo, const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillRuleForPath(fillRule);
        offscreenPattern->Stroke(path);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath2D(fillRule);
        canvasPattern->Stroke(path);
    }
}

void CanvasRendererModelImpl::SetStrokeRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillRuleForPath2D(fillRule);
        offscreenPattern->Stroke();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath(fillRule);
        canvasPattern->Stroke();
    }
}

void CanvasRendererModelImpl::SetClipRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillRuleForPath(fillRule);
        offscreenPattern->Clip();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath(fillRule);
        canvasPattern->Clip();
    }
}

void CanvasRendererModelImpl::SetClipRuleForPath2D(
    const BaseInfo& baseInfo, const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetFillRuleForPath2D(fillRule);
        offscreenPattern->Clip(path);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath2D(fillRule);
        canvasPattern->Clip(path);
    }
}

void CanvasRendererModelImpl::AddRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->AddRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->AddRect(rect);
    }
}

void CanvasRendererModelImpl::BeginPath(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->BeginPath();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->BeginPath();
    }
}

void CanvasRendererModelImpl::ClosePath(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->ClosePath();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ClosePath();
    }
}

void CanvasRendererModelImpl::Restore(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Restore();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Restore();
    }
}

void CanvasRendererModelImpl::CanvasRendererSave(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Save();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Save();
    }
}

void CanvasRendererModelImpl::CanvasRendererRotate(const BaseInfo& baseInfo, double angle)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Rotate(angle);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Rotate(angle);
    }
}

void CanvasRendererModelImpl::CanvasRendererScale(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Scale(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Scale(x, y);
    }
}

void CanvasRendererModelImpl::SetTransform(const BaseInfo& baseInfo, TransformParam& param, bool lengthFlag)
{
    if (!lengthFlag) {
        return;
    }

    auto temp = param.skewX;
    param.skewX = param.skewY;
    param.skewY = temp;

    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetTransform(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->SetTransform(param);
    }
}

void CanvasRendererModelImpl::ResetTransform(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->ResetTransform();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ResetTransform();
    }
}

void CanvasRendererModelImpl::Transform(const BaseInfo& baseInfo, const TransformParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Transform(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Transform(param);
    }
}

void CanvasRendererModelImpl::Translate(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->Translate(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Translate(x, y);
    }
}

void CanvasRendererModelImpl::SetLineDash(const BaseInfo& baseInfo, const std::vector<double>& lineDash)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetLineDash(lineDash);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineDash(lineDash);
    }
}

void CanvasRendererModelImpl::SetTextAlign(const BaseInfo& baseInfo, const TextAlign& align)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetTextAlign(align);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateTextAlign(align);
    }
}

void CanvasRendererModelImpl::SetTextBaseline(const BaseInfo& baseInfo, const TextBaseline& baseline)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->SetTextBaseline(baseline);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateTextBaseline(baseline);
    }
}

double CanvasRendererModelImpl::GetMeasureTextWidth(const BaseInfo& baseInfo, const std::string& text)
{
    double width = 0.0;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, width);
        width = offscreenPattern->MeasureText(text, baseInfo.paintState);
        return width;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, width);
        width = canvasPattern->MeasureText(text, baseInfo.paintState);
    }
    return width;
}

double CanvasRendererModelImpl::GetMeasureTextHeight(const BaseInfo& baseInfo, const std::string& text)
{
    double height = 0.0;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, height);
        height = offscreenPattern->MeasureTextHeight(text, baseInfo.paintState);
        return height;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, height);
        height = canvasPattern->MeasureTextHeight(text, baseInfo.paintState);
    }
    return height;
}

void CanvasRendererModelImpl::FillRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->FillRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->FillRect(rect);
    }
}

void CanvasRendererModelImpl::StrokeRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->StrokeRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->StrokeRect(rect);
    }
}

void CanvasRendererModelImpl::ClearRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->ClearRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CanvasTaskPool>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ClearRect(rect);
    }
}

void CanvasRendererModelImpl::DrawBitmapMesh(const BitmapMeshInfo& bitmapMeshInfo)
{
    CHECK_NULL_VOID(bitmapMeshInfo.pool);
    auto pool = AceType::DynamicCast<CanvasTaskPool>(bitmapMeshInfo.pool);
    CHECK_NULL_VOID(pool);
    CHECK_NULL_VOID(bitmapMeshInfo.offscreenPattern);
    auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(bitmapMeshInfo.offscreenPattern);
    CHECK_NULL_VOID(offscreenPattern);
    pool->DrawBitmapMesh(offscreenPattern, bitmapMeshInfo.mesh, bitmapMeshInfo.column, bitmapMeshInfo.row);
}

std::unique_ptr<OHOS::Media::PixelMap> CanvasRendererModelImpl::GetPixelMap(
    const BaseInfo& baseInfo, const ImageSize& imageSize)
{
#ifdef PIXEL_MAP_SUPPORTED
    // 1 Get data from canvas
    std::unique_ptr<ImageData> canvasData = GetImageData(baseInfo, imageSize);
    CHECK_NULL_RETURN(canvasData, nullptr);

    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        LOGE("Integer Overflow!!!the product of finalHeight and finalWidth is too big.");
        return nullptr;
    }
    uint32_t length = finalHeight * finalWidth;
    uint32_t* data = new uint32_t[length];
    for (uint32_t i = 0; i < finalHeight; i++) {
        for (uint32_t j = 0; j < finalWidth; j++) {
            uint32_t idx = i * finalWidth + j;
            Color pixel = canvasData->data[idx];
            data[idx] = pixel.GetValue();
        }
    }

    // 2 Create pixelmap
    OHOS::Media::InitializationOptions options;
    options.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
    options.pixelFormat = OHOS::Media::PixelFormat::RGBA_8888;
    options.scaleMode = OHOS::Media::ScaleMode::CENTER_CROP;
    options.size.width = static_cast<int32_t>(finalWidth);
    options.size.height = static_cast<int32_t>(finalHeight);
    options.editable = true;
    std::unique_ptr<OHOS::Media::PixelMap> pixelmap = OHOS::Media::PixelMap::Create(data, length, options);
    delete[] data;
    return pixelmap;
#else
    return nullptr;
#endif
}

void CanvasRendererModelImpl::GetImageDataModel(const BaseInfo& baseInfo, const ImageSize& imageSize, uint8_t* buffer)
{
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    std::unique_ptr<Ace::ImageData> data = GetImageData(baseInfo, imageSize);

    if (data != nullptr) {
        for (uint32_t idx = 0; idx < finalHeight * finalWidth; ++idx) {
            buffer[4 * idx] = data->data[idx].GetRed();
            buffer[4 * idx + 1] = data->data[idx].GetGreen();
            buffer[4 * idx + 2] = data->data[idx].GetBlue();
            buffer[4 * idx + 3] = data->data[idx].GetAlpha();
        }
    }
}
} // namespace OHOS::Ace::Framework