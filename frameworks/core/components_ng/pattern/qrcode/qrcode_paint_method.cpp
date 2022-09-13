/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/qrcode/qrcode_paint_method.h"

#include <cstdint>

#include "qrcodegen.hpp"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/qrcode/qrcode_paint_property.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction QRCodePaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto qrcode = weak.Upgrade();
        if (qrcode) {
            qrcode->Paint(canvas, paintWrapper);
        }
    };
    return paintFunc;
}

void QRCodePaintMethod::Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = AceType::DynamicCast<QRCodePaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->GetValue().has_value()) {
        LOGE("QRCode value is empty, can't paint");
        return;
    }
    auto value = paintProperty->GetValueValue();
    // TODO use theme
    Color color = Color::BLACK;
    if (paintProperty->HasColor()) {
        color = paintProperty->GetColorValue();
    }
    // TODO use theme
    Color backgroundColor = Color::WHITE;
    if (paintProperty->HasBackgroundColor()) {
        backgroundColor = paintProperty->GetBackgroundColorValue();
    }
    // auto geometryNode = paintWrapper->GetGeometryNode();
    // CHECK_NULL_VOID(geometryNode);
    auto qrCode = qrcodegen::QrCode::encodeText(value.c_str(), qrcodegen::QrCode::Ecc::LOW);
    if (!qrCode.getFlag() || qrCode.getSize() == 0 || qrCodeSize_ <= 0 ||
        qrCodeSize_ < static_cast<float>(qrCode.getSize())) {
        LOGE("QRCodePaintMethod:: qrcode create error");
        return;
    }
    auto bitMap = CreateBitMap(static_cast<int32_t>(qrCodeSize_), qrCode, color, backgroundColor);
    auto paintOffset = paintWrapper->GetContentOffset();
    canvas.DrawBitmap(bitMap, paintOffset.GetX(), paintOffset.GetY());
}

RSBitmap QRCodePaintMethod::CreateBitMap(
    int32_t width, const qrcodegen::QrCode& qrCode, const Color& color, const Color& backgroundColor) const
{
    RSBitmap bitMap;
    RSBitmapFormat colorType = { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    bitMap.Build(width, width, colorType);

    void* rawData = bitMap.GetPixels();
    auto* data = reinterpret_cast<uint32_t*>(rawData);
    int32_t blockWidth = width / qrCode.getSize();
    for (int32_t i = 0; i < width; i++) {
        for (int32_t j = 0; j < width; j++) {
            data[i * width + j] = qrCode.getModule(i / blockWidth, j / blockWidth)
                                      ? ConvertColorFromHighToLow(color)
                                      : ConvertColorFromHighToLow(backgroundColor);
        }
    }
    return bitMap;
}

uint32_t QRCodePaintMethod::ConvertColorFromHighToLow(const Color& color) const
{
    BGRA convertedColor;
    convertedColor.argb.blue = color.GetBlue();
    convertedColor.argb.green = color.GetGreen();
    convertedColor.argb.red = color.GetRed();
    convertedColor.argb.alpha = color.GetAlpha();
    return convertedColor.value;
}

} // namespace OHOS::Ace::NG
