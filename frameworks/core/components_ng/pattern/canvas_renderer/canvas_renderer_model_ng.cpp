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

#include "core/components_ng/pattern/canvas_renderer/canvas_renderer_model_ng.h"

#include "securec.h"

#include "frameworks/core/components_ng/pattern/custom_paint/custom_paint_pattern.h"
#include "frameworks/core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#endif

namespace OHOS::Ace::NG {
void CanvasRendererModelNG::SetFillText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->FillText(
            fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth, baseInfo.paintState);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->FillText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth);
    }
}

void CanvasRendererModelNG::SetStrokeText(const BaseInfo& baseInfo, const FillTextInfo& fillTextInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->StrokeText(
            fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth, baseInfo.paintState);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->StrokeText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth);
    }
}

void CanvasRendererModelNG::SetAntiAlias(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetAntiAlias(baseInfo.anti);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->SetAntiAlias(baseInfo.anti);
    }
}

void CanvasRendererModelNG::SetFontWeight(const BaseInfo& baseInfo, const FontWeight& weight)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFontWeight(weight);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontWeight(weight);
    }
}

void CanvasRendererModelNG::SetFontStyle(const BaseInfo& baseInfo, const FontStyle& fontStyle)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFontStyle(fontStyle);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontStyle(fontStyle);
    }
}

void CanvasRendererModelNG::SetFontFamilies(const BaseInfo& baseInfo, const std::vector<std::string>& families)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFontFamilies(families);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontFamilies(families);
    }
}

void CanvasRendererModelNG::SetFontSize(const BaseInfo& baseInfo, const Dimension& size)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFontSize(size);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFontSize(size);
    }
}

std::vector<double> CanvasRendererModelNG::GetLineDash(const BaseInfo& baseInfo)
{
    std::vector<double> lineDash {};
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, lineDash);
        if (!offscreenPattern->IsSucceed()) {
            return lineDash;
        }
        lineDash = offscreenPattern->GetLineDash().lineDash;
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, lineDash);
        lineDash = canvasPattern->GetLineDash().lineDash;
    }

    return lineDash;
}

void CanvasRendererModelNG::SetFillGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillGradient(gradient);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillGradient(gradient);
    }
}

void CanvasRendererModelNG::SetFillPattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern)
{
    std::weak_ptr<Ace::Pattern> patternWeakptr = pattern;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillPattern(patternWeakptr);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillPattern(patternWeakptr);
    }
}

void CanvasRendererModelNG::SetFillColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillColor(color);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillColor(color);
    }
}

void CanvasRendererModelNG::SetStrokeGradient(const BaseInfo& baseInfo, const Ace::Gradient& gradient)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetStrokeGradient(gradient);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateStrokeGradient(gradient);
    }
}

void CanvasRendererModelNG::SetStrokePattern(const BaseInfo& baseInfo, const std::shared_ptr<Ace::Pattern>& pattern)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetStrokePattern(pattern);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateStrokePattern(pattern);
    }
}

void CanvasRendererModelNG::SetStrokeColor(const BaseInfo& baseInfo, const Color& color, bool colorFlag)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetStrokeColor(color);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateStrokeColor(color);
    }
}

void CanvasRendererModelNG::DrawImage(const BaseInfo& baseInfo, const ImageInfo& imageInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        if (imageInfo.isImage) {
            offscreenPattern->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
            return;
        }
        offscreenPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        if (imageInfo.isImage) {
            canvasPattern->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
            return;
        }
        canvasPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
    }
}

void CanvasRendererModelNG::PutImageData(const BaseInfo& baseInfo, const Ace::ImageData& imageData)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->PutImageData(imageData);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->PutImageData(imageData);
    }
}

void CanvasRendererModelNG::CloseImageBitmap(const BaseInfo& baseInfo, const std::string& src)
{
    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->CloseImageBitmap(src);
    }
}

std::unique_ptr<Ace::ImageData> CanvasRendererModelNG::GetImageData(
    const BaseInfo& baseInfo, const ImageSize& imageSize)
{
    std::unique_ptr<Ace::ImageData> data;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, data);
        if (!offscreenPattern->IsSucceed()) {
            return data;
        }
        data = offscreenPattern->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height);
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, data);
        data = canvasPattern->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height);
    }
    return data;
}

void CanvasRendererModelNG::DrawPixelMap(const BaseInfo& baseInfo, const ImageInfo& imageInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
    }
}

void CanvasRendererModelNG::SetFilterParam(const BaseInfo& baseInfo, const std::string& src)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFilterParam(src);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->SetFilterParam(src);
    }
}

void CanvasRendererModelNG::SetTextDirection(const BaseInfo& baseInfo, const TextDirection& direction)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetTextDirection(direction);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->SetTextDirection(direction);
    }
}

std::string CanvasRendererModelNG::GetJsonData(const BaseInfo& baseInfo, const std::string& path)
{
    std::string jsonData = "";
    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, jsonData);
        jsonData = canvasPattern->GetJsonData(path);
    }
    return jsonData;
}

std::string CanvasRendererModelNG::ToDataURL(const BaseInfo& baseInfo, const std::string& dataUrl, double quality)
{
    std::string result = "";
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, result);
        if (!offscreenPattern->IsSucceed()) {
            return result;
        }
        result = offscreenPattern->ToDataURL(dataUrl, quality);
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, result);
        result = canvasPattern->ToDataURL(dataUrl + "," + std::to_string(quality));
    }
    return result;
}

void CanvasRendererModelNG::SetLineCap(const BaseInfo& baseInfo, const LineCapStyle& lineCap)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetLineCap(lineCap);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineCap(lineCap);
    }
}

void CanvasRendererModelNG::SetLineJoin(const BaseInfo& baseInfo, const LineJoinStyle& lineJoin)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetLineJoin(lineJoin);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineJoin(lineJoin);
    }
}

void CanvasRendererModelNG::SetMiterLimit(const BaseInfo& baseInfo, double limit)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetMiterLimit(limit);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateMiterLimit(limit);
    }
}

void CanvasRendererModelNG::SetLineWidth(const BaseInfo& baseInfo, double lineWidth)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetLineWidth(lineWidth);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineWidth(lineWidth);
    }
}

void CanvasRendererModelNG::SetGlobalAlpha(const BaseInfo& baseInfo, double alpha)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetAlpha(alpha);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateGlobalAlpha(alpha);
    }
}

void CanvasRendererModelNG::SetCompositeType(const BaseInfo& baseInfo, const CompositeOperation& type)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetCompositeType(type);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateCompositeOperation(type);
    }
}

void CanvasRendererModelNG::SetLineDashOffset(const BaseInfo& baseInfo, double lineDashOffset)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetLineDashOffset(lineDashOffset);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineDashOffset(lineDashOffset);
    }
}

void CanvasRendererModelNG::SetShadowBlur(const BaseInfo& baseInfo, double blur)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetShadowBlur(blur);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowBlur(blur);
    }
}

void CanvasRendererModelNG::SetShadowColor(const BaseInfo& baseInfo, const Color& color)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetShadowColor(color);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowColor(color);
    }
}

void CanvasRendererModelNG::SetShadowOffsetX(const BaseInfo& baseInfo, double offsetX)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetShadowOffsetX(offsetX);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowOffsetX(offsetX);
    }
}

void CanvasRendererModelNG::SetShadowOffsetY(const BaseInfo& baseInfo, double offsetY)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetShadowOffsetY(offsetY);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateShadowOffsetY(offsetY);
    }
}

void CanvasRendererModelNG::SetSmoothingEnabled(const BaseInfo& baseInfo, bool enabled)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetSmoothingEnabled(enabled);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateSmoothingEnabled(enabled);
    }
}

void CanvasRendererModelNG::SetSmoothingQuality(const BaseInfo& baseInfo, const std::string& quality)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetSmoothingQuality(quality);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateSmoothingQuality(quality);
    }
}

void CanvasRendererModelNG::MoveTo(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->MoveTo(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->MoveTo(x, y);
    }
}

void CanvasRendererModelNG::LineTo(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->LineTo(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->LineTo(x, y);
    }
}

void CanvasRendererModelNG::BezierCurveTo(const BaseInfo& baseInfo, const BezierCurveParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->BezierCurveTo(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->BezierCurveTo(param);
    }
}

void CanvasRendererModelNG::QuadraticCurveTo(const BaseInfo& baseInfo, const QuadraticCurveParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->QuadraticCurveTo(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->QuadraticCurveTo(param);
    }
}

void CanvasRendererModelNG::ArcTo(const BaseInfo& baseInfo, const ArcToParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->ArcTo(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ArcTo(param);
    }
}

void CanvasRendererModelNG::Arc(const BaseInfo& baseInfo, const ArcParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Arc(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Arc(param);
    }
}

void CanvasRendererModelNG::Ellipse(const BaseInfo& baseInfo, const EllipseParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Ellipse(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Ellipse(param);
    }
}

void CanvasRendererModelNG::SetFillRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillRuleForPath(fillRule);
        offscreenPattern->Fill();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath(fillRule);
        canvasPattern->Fill();
    }
}

void CanvasRendererModelNG::SetFillRuleForPath2D(
    const BaseInfo& baseInfo, const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillRuleForPath2D(fillRule);
        offscreenPattern->Fill(path);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath2D(fillRule);
        canvasPattern->Fill(path);
    }
}

void CanvasRendererModelNG::SetStrokeRuleForPath2D(
    const BaseInfo& baseInfo, const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillRuleForPath(fillRule);
        offscreenPattern->Stroke(path);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath2D(fillRule);
        canvasPattern->Stroke(path);
    }
}

void CanvasRendererModelNG::SetStrokeRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillRuleForPath(fillRule);
        offscreenPattern->Stroke();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath(fillRule);
        canvasPattern->Stroke();
    }
}

void CanvasRendererModelNG::SetClipRuleForPath(const BaseInfo& baseInfo, const CanvasFillRule& fillRule)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillRuleForPath(fillRule);
        offscreenPattern->Clip();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath(fillRule);
        canvasPattern->Clip();
    }
}

void CanvasRendererModelNG::SetClipRuleForPath2D(
    const BaseInfo& baseInfo, const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetFillRuleForPath2D(fillRule);
        offscreenPattern->Clip(path);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateFillRuleForPath2D(fillRule);
        canvasPattern->Clip(path);
    }
}

void CanvasRendererModelNG::AddRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->AddRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->AddRect(rect);
    }
}

void CanvasRendererModelNG::BeginPath(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->BeginPath();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->BeginPath();
    }
}

void CanvasRendererModelNG::ClosePath(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->ClosePath();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ClosePath();
    }
}

void CanvasRendererModelNG::Restore(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Restore();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Restore();
    }
}

void CanvasRendererModelNG::CanvasRendererSave(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Save();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Save();
    }
}

void CanvasRendererModelNG::CanvasRendererRotate(const BaseInfo& baseInfo, double angle)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Rotate(angle);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Rotate(angle);
    }
}

void CanvasRendererModelNG::CanvasRendererScale(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Scale(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Scale(x, y);
    }
}

void CanvasRendererModelNG::SetTransform(const BaseInfo& baseInfo, TransformParam& param, bool lengthFlag)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetTransform(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->SetTransform(param);
    }
}

void CanvasRendererModelNG::ResetTransform(const BaseInfo& baseInfo)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->ResetTransform();
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ResetTransform();
    }
}

void CanvasRendererModelNG::Transform(const BaseInfo& baseInfo, const TransformParam& param)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Transform(param);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Transform(param);
    }
}

void CanvasRendererModelNG::Translate(const BaseInfo& baseInfo, double x, double y)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->Translate(x, y);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->Translate(x, y);
    }
}

void CanvasRendererModelNG::SetLineDash(const BaseInfo& baseInfo, const std::vector<double>& lineDash)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetLineDash(lineDash);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateLineDash(lineDash);
    }
}

void CanvasRendererModelNG::SetTextAlign(const BaseInfo& baseInfo, const TextAlign& align)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetTextAlign(align);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateTextAlign(align);
    }
}

void CanvasRendererModelNG::SetTextBaseline(const BaseInfo& baseInfo, const TextBaseline& baseline)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->SetTextBaseline(baseline);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->UpdateTextBaseline(baseline);
    }
}

double CanvasRendererModelNG::GetMeasureTextWidth(const BaseInfo& baseInfo, const std::string& text)
{
    double width = 0.0;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, width);
        if (!offscreenPattern->IsSucceed()) {
            return width;
        }
        width = offscreenPattern->MeasureText(text, baseInfo.paintState);
        return width;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, width);
        width = canvasPattern->MeasureText(text, baseInfo.paintState);
    }
    return width;
}

double CanvasRendererModelNG::GetMeasureTextHeight(const BaseInfo& baseInfo, const std::string& text)
{
    double height = 0.0;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, height);
        if (!offscreenPattern->IsSucceed()) {
            return height;
        }
        height = offscreenPattern->MeasureTextHeight(text, baseInfo.paintState);
        return height;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, height);
        height = canvasPattern->MeasureTextHeight(text, baseInfo.paintState);
    }
    return height;
}

void CanvasRendererModelNG::FillRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->FillRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->FillRect(rect);
    }
}

void CanvasRendererModelNG::StrokeRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->StrokeRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->StrokeRect(rect);
    }
}

void CanvasRendererModelNG::ClearRect(const BaseInfo& baseInfo, const Rect& rect)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        if (!offscreenPattern->IsSucceed()) {
            return;
        }
        offscreenPattern->ClearRect(rect);
        return;
    }

    if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->ClearRect(rect);
    }
}

TransformParam CanvasRendererModelNG::GetTransform(const BaseInfo& baseInfo)
{
    TransformParam param;
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_RETURN(offscreenPattern, param);
        if (!offscreenPattern->IsSucceed()) {
            return param;
        }
        param = offscreenPattern->GetTransform();
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_RETURN(canvasPattern, param);
        param = canvasPattern->GetTransform();
    }
    return param;
}

RefPtr<Ace::PixelMap> CanvasRendererModelNG::GetPixelMap(const BaseInfo& baseInfo, const ImageSize& imageSize)
{
#ifdef PIXEL_MAP_SUPPORTED
    // 1 Get data from canvas
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        return nullptr;
    }

    // 2 Create pixelmap
    OHOS::Media::InitializationOptions options;
    options.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    options.pixelFormat = OHOS::Media::PixelFormat::RGBA_8888;
    options.scaleMode = OHOS::Media::ScaleMode::CENTER_CROP;
    options.size.width = static_cast<int32_t>(finalWidth);
    options.size.height = static_cast<int32_t>(finalHeight);
    options.editable = true;
    auto pixelMap = Ace::PixelMap::Create(OHOS::Media::PixelMap::Create(options));
    if (pixelMap) {
        std::shared_ptr<Ace::ImageData> imageData = std::make_shared<Ace::ImageData>();
        imageData->pixelMap = pixelMap;
        imageData->dirtyX = static_cast<int32_t>(imageSize.left);
        imageData->dirtyY = static_cast<int32_t>(imageSize.top);
        imageData->dirtyWidth = static_cast<int32_t>(imageSize.width);
        imageData->dirtyHeight = static_cast<int32_t>(imageSize.height);
        GetImageData(baseInfo, imageData);
    }
    return pixelMap;
#else
    return nullptr;
#endif
}

void CanvasRendererModelNG::GetImageDataModel(const BaseInfo& baseInfo, const ImageSize& imageSize, uint8_t* buffer)
{
#ifdef PIXEL_MAP_SUPPORTED
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        return;
    }
    OHOS::Media::InitializationOptions options;
    options.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    options.pixelFormat = OHOS::Media::PixelFormat::RGBA_8888;
    options.scaleMode = OHOS::Media::ScaleMode::CENTER_CROP;
    options.size.width = static_cast<int32_t>(finalWidth);
    options.size.height = static_cast<int32_t>(finalHeight);
    options.editable = true;
    auto pixelMap = Ace::PixelMap::Create(OHOS::Media::PixelMap::Create(options));
    if (pixelMap) {
        std::shared_ptr<Ace::ImageData> imageData = std::make_shared<Ace::ImageData>();
        imageData->pixelMap = pixelMap;
        imageData->dirtyX = static_cast<int32_t>(imageSize.left);
        imageData->dirtyY = static_cast<int32_t>(imageSize.top);
        imageData->dirtyWidth = static_cast<int32_t>(imageSize.width);
        imageData->dirtyHeight = static_cast<int32_t>(imageSize.height);
        GetImageData(baseInfo, imageData);
        auto pixelsSize = pixelMap->GetRowBytes() * pixelMap->GetHeight();
        memcpy_s(buffer, pixelsSize, pixelMap->GetWritablePixels(), pixelsSize);
    }
#else
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    std::unique_ptr<Ace::ImageData> data = GetImageData(baseInfo, imageSize);

    if (data != nullptr) {
        for (uint32_t idx = 0; idx < finalHeight * finalWidth; ++idx) {
            buffer[4 * idx] = data->data[idx].GetRed();
            buffer[4 * idx + 1] = data->data[idx].GetGreen();
            buffer[4 * idx + 2] = data->data[idx].GetBlue();
            buffer[4 * idx + 3] = data->data[idx].GetAlpha();
        }
    }
#endif
}

void CanvasRendererModelNG::GetImageData(const BaseInfo& baseInfo, const std::shared_ptr<Ace::ImageData>& imageData)
{
    if (baseInfo.isOffscreen && baseInfo.offscreenPattern) {
        auto offscreenPattern = AceType::DynamicCast<OffscreenCanvasPattern>(baseInfo.offscreenPattern);
        CHECK_NULL_VOID(offscreenPattern);
        offscreenPattern->GetImageData(imageData);
    } else if (!baseInfo.isOffscreen && baseInfo.canvasPattern) {
        auto canvasPattern = AceType::DynamicCast<CustomPaintPattern>(baseInfo.canvasPattern);
        CHECK_NULL_VOID(canvasPattern);
        canvasPattern->GetImageData(imageData);
    }
}
} // namespace OHOS::Ace::NG
