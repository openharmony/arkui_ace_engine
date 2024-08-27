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

#include "core/components/qrcode/rosen_render_qrcode.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#include "include/core/SkImage.h"
#include "include/core/SkRRect.h"
#endif

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

void RosenRenderQrcode::Paint(RenderContext& context, const Offset& offset)
{
    auto qrCode = qrcodegen::QrCode::encodeText(value_.c_str(), qrcodegen::QrCode::Ecc::LOW);
    if (!qrCode.getFlag() || qrCode.getSize() == 0 || width_ <= 0 || width_ < qrCode.getSize()) {
        LOGE("RosenRenderQrcode::DrawQRCode qrcode create error");
        return;
    }
    int32_t blockWidth = width_ / qrCode.getSize();
    int32_t sizeInPixel = blockWidth * qrCode.getSize();
    auto qrOffset =
        Alignment::GetAlignPosition(Size(width_, height_), Size(sizeInPixel, sizeInPixel), Alignment::CENTER);
    DrawQRCode(context, offset + qrOffset, sizeInPixel, qrCode);
}

void RosenRenderQrcode::DrawQRCode(
    RenderContext& context, const Offset& topLeft, int32_t size, const qrcodegen::QrCode& qrCode)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    if (!qrcode_) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    if (qrcode_->GetType() == QrcodeType::CIRCLE) {
        SkRect clipRect = { topLeft.GetX(), topLeft.GetY(), topLeft.GetX() + size, topLeft.GetY() + size };
        auto clipLayer = SkRRect::MakeRectXY(clipRect, size / 2.0, size / 2.0);
        canvas->clipRRect(clipLayer, SkClipOp::kIntersect, true);
    }

    SkBitmap skBitmap = ProcessQrcodeData(size, qrCode);
    canvas->drawImage(skBitmap.asImage(), topLeft.GetX(), topLeft.GetY(), SkSamplingOptions());
    if (qrcode_->GetType() == QrcodeType::CIRCLE) {
        int32_t smallSquareWidth = size / sqrt(2);

        skBitmap = ProcessQrcodeData(smallSquareWidth, qrCode);
        // draw without border around
        canvas->drawImage(skBitmap.asImage(),
            topLeft.GetX() + (size - smallSquareWidth) / 2.0,
            topLeft.GetY() + (size - smallSquareWidth) / 2.0, SkSamplingOptions());
    }
#else
    if (qrcode_->GetType() == QrcodeType::CIRCLE) {
        RSRect clipRect = { topLeft.GetX(), topLeft.GetY(),
            topLeft.GetX() + size, topLeft.GetY() + size };
        auto clipLayer = RSRoundRect(clipRect, size / 2.0, size / 2.0);
        canvas->ClipRoundRect(clipLayer, RSClipOp::INTERSECT, true);
    }
    canvas->DrawBitmap(ProcessQrcodeData(size, qrCode), topLeft.GetX(), topLeft.GetY());
    if (qrcode_->GetType() == QrcodeType::CIRCLE) {
        int32_t smallSquareWidth = size / sqrt(2);
        // draw without border around
        canvas->DrawBitmap(ProcessQrcodeData(smallSquareWidth, qrCode),
            topLeft.GetX() + (size - smallSquareWidth) / 2.0, topLeft.GetY() + (size - smallSquareWidth) / 2.0);
    }
#endif
}

uint32_t RosenRenderQrcode::ConvertColorFromHighToLow(const Color& color)
{
    BGRA convertedColor;
    convertedColor.argb.blue = color.GetBlue();
    convertedColor.argb.green = color.GetGreen();
    convertedColor.argb.red = color.GetRed();
    convertedColor.argb.alpha = color.GetAlpha();
    return convertedColor.value;
}

#ifndef USE_ROSEN_DRAWING
SkBitmap RosenRenderQrcode::ProcessQrcodeData(int32_t width, const qrcodegen::QrCode& qrCode)
{
    // each block width may smaller the width / qrCode.getSize(), because of precision loss.
    auto imageInfo =
        SkImageInfo::Make(width, width, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap skBitmap;
    if (!qrcode_) {
        return skBitmap;
    }
    skBitmap.allocPixels(imageInfo);
    void* rawData = skBitmap.getPixels();
    CHECK_NULL_RETURN(rawData, skBitmap);
    uint32_t* data = reinterpret_cast<uint32_t*>(rawData);
    int32_t blockWidth = width / qrCode.getSize();
    for (int32_t i = 0; i < width; i++) {
        for (int32_t j = 0; j < width; j++) {
            data[i * width + j] = qrCode.getModule(i / blockWidth, j / blockWidth)
                                      ? ConvertColorFromHighToLow(qrcode_->GetQrcodeColor())
                                      : ConvertColorFromHighToLow(qrcode_->GetBackgroundColor());
        }
    }
    return skBitmap;
}
#else
RSBitmap RosenRenderQrcode::ProcessQrcodeData(int32_t width, const qrcodegen::QrCode& qrCode)
{
    // each block width may smaller the width / qrCode.getSize(), because of precision loss.
    RSBitmapFormat format {RSColorType::COLORTYPE_RGBA_8888,
        RSAlphaType::ALPHATYPE_OPAQUE};
    RSBitmap bitmap;
    if (!qrcode_) {
        return bitmap;
    }
    bitmap.Build(width, width, format);
    void* rawData = bitmap.GetPixels();
    CHECK_NULL_RETURN(rawData, bitmap);
    uint32_t* data = reinterpret_cast<uint32_t*>(rawData);
    int32_t blockWidth = width / qrCode.getSize();
    for (int32_t i = 0; i < width; i++) {
        for (int32_t j = 0; j < width; j++) {
            data[i * width + j] = qrCode.getModule(i / blockWidth, j / blockWidth)
                                      ? ConvertColorFromHighToLow(qrcode_->GetQrcodeColor())
                                      : ConvertColorFromHighToLow(qrcode_->GetBackgroundColor());
        }
    }
    return bitmap;
}
#endif

} // namespace OHOS::Ace
