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

#include "core/components_ng/pattern/canvas/canvas_paint_method.h"

#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/canvas/custom_paint_util.h"

#ifndef ACE_UNITTEST
#include "include/utils/SkBase64.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/image/image_cache.h"
#endif

namespace OHOS::Ace::NG {
constexpr Dimension DEFAULT_FONT_SIZE = 14.0_px;
CanvasPaintMethod::CanvasPaintMethod(RefPtr<CanvasModifier> contentModifier, const RefPtr<FrameNode>& frameNode)
    : frameNode_(frameNode)
{
    matrix_.Reset();
    context_ = frameNode ? frameNode->GetContextRefPtr() : nullptr;
    imageShadow_ = std::make_unique<Shadow>();
    contentModifier_ = contentModifier;
    // The default value of the font size in canvas is 14px.
    SetFontSize(DEFAULT_FONT_SIZE);
    if (apiVersion_ >= static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN)) {
        isPathChanged_ = false;
        isPath2dChanged_ = false;
    }
}

void CanvasPaintMethod::PushTask(const TaskFunc& task)
{
    static constexpr uint32_t suggestSize = 100000;
    tasks_.emplace_back(task);
    if (tasks_.size() >= suggestSize && tasks_.size() % suggestSize == 0) {
        TAG_LOGI(AceLogTag::ACE_CANVAS, "[%{public}s] Canvas task size: %{public}zu", customNodeName_.c_str(),
            tasks_.size());
    }
    CHECK_EQUAL_VOID(needMarkDirty_, false);
    needMarkDirty_ = false;
    auto host = frameNode_.Upgrade();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool CanvasPaintMethod::HasTask() const
{
    return !tasks_.empty();
}

void CanvasPaintMethod::FlushTask()
{
    ACE_SCOPED_TRACE("Canvas tasks count: %zu.", tasks_.size());
    for (auto& task : tasks_) {
        task(*this);
    }
    tasks_.clear();
    needMarkDirty_ = true;
}

void CanvasPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    ACE_SCOPED_TRACE("Canvas[%d] CanvasPaintMethod::UpdateContentModifier", GetId());
    auto host = frameNode_.Upgrade();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto pixelGridRoundSize = geometryNode->GetPixelGridRoundSize();
    lastLayoutSize_.SetSizeT(pixelGridRoundSize);
    auto recordingCanvas = std::static_pointer_cast<RSRecordingCanvas>(rsCanvas_);
    CHECK_NULL_VOID(recordingCanvas);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto fontManager = context->GetFontManager();
    if (fontManager) {
        recordingCanvas->SetIsCustomTextType(fontManager->IsDefaultFontChanged());
    }

    if (!HasTask()) {
        return;
    }

    FireOnModifierUpdateFunc();
    recordingCanvas->Scale(1.0, 1.0);
    FlushTask();
    if (!contentModifier_) {
        ACE_SCOPED_TRACE("Canvas[%d] contentModifier is NULL", GetId());
        TAG_LOGE(AceLogTag::ACE_CANVAS, "Canvas[%{public}d] contentModifier is NULL", GetId());
        return;
    }
    contentModifier_->MarkModifierDirty();
}

void CanvasPaintMethod::UpdateRecordingCanvas(float width, float height)
{
    ACE_SCOPED_TRACE("Canvas[%d] CanvasPaintMethod::UpdateRecordingCanvas[%f, %f]", GetId(), width, height);
    rsCanvas_ = std::make_shared<RSRecordingCanvas>(width, height);
    contentModifier_->UpdateCanvas(std::static_pointer_cast<RSRecordingCanvas>(rsCanvas_));
    CHECK_NULL_VOID(rsCanvas_);
    rsCanvas_->Save();
    FireRSCanvasCallback(width, height);
    ResetStates();
    needMarkDirty_ = true;
}

void CanvasPaintMethod::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
{
#ifndef ACE_UNITTEST
    InitImagePaint(nullptr, &imageBrush_, sampleOptions_);
    imageBrush_.SetAntiAlias(antiAlias_);
    RSBrush compositeOperationpBrush;
    InitPaintBlend(compositeOperationpBrush);
    RSSaveLayerOps layerOps(nullptr, &compositeOperationpBrush);
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->SaveLayer(layerOps);
    }
    if (state_.globalState.HasGlobalAlpha()) {
        imageBrush_.SetAlphaF(state_.globalState.GetAlpha());
    }

    if (HasShadow()) {
        auto tempPixelMap = pixelMap->GetPixelMapSharedPtr();
        CHECK_NULL_VOID(tempPixelMap);
        RSRect rec;
        if (canvasImage.flag == DrawImageType::THREE_PARAMS) {
            rec = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dx + tempPixelMap->GetWidth(), canvasImage.dy + tempPixelMap->GetHeight());
        } else {
            rec = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dx + canvasImage.dWidth, canvasImage.dy + canvasImage.dHeight);
        }
        RSPath path;
        path.AddRect(rec);
        PaintImageShadow(path, state_.shadow, &imageBrush_, nullptr,
            (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) ? &layerOps : nullptr);
    }
    DrawPixelMapInternal(pixelMap, canvasImage);
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->Restore();
    }
#endif
}

void CanvasPaintMethod::DrawPixelMapInternal(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
{
#ifndef ACE_UNITTEST
    const std::shared_ptr<Media::PixelMap> tempPixelMap = pixelMap->GetPixelMapSharedPtr();
    CHECK_NULL_VOID(tempPixelMap);
    RSRect srcRect;
    RSRect dstRect;
    switch (canvasImage.flag) {
        case DrawImageType::THREE_PARAMS: {
            srcRect = RSRect(0, 0, tempPixelMap->GetWidth(), tempPixelMap->GetHeight());
            dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dx + tempPixelMap->GetWidth(),
                canvasImage.dy + tempPixelMap->GetHeight());
            break;
        }
        case DrawImageType::FIVE_PARAMS: {
            srcRect = RSRect(0, 0, tempPixelMap->GetWidth(), tempPixelMap->GetHeight());
            dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dx + canvasImage.dWidth,
                canvasImage.dy + canvasImage.dHeight);
            break;
        }
        case DrawImageType::NINE_PARAMS: {
            srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sx + canvasImage.sWidth,
                canvasImage.sy + canvasImage.sHeight);
            dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dx + canvasImage.dWidth,
                canvasImage.dy + canvasImage.dHeight);
            break;
        }
        default:
            break;
    }
    auto recordingCanvas = std::static_pointer_cast<RSRecordingCanvas>(rsCanvas_);
    CHECK_NULL_VOID(recordingCanvas);
    recordingCanvas->AttachBrush(imageBrush_);
    recordingCanvas->DrawPixelMapRect(tempPixelMap, srcRect, dstRect, sampleOptions_);
    recordingCanvas->DetachBrush();
#endif
}

void CanvasPaintMethod::CloseImageBitmap(const std::string& src)
{
#ifndef ACE_UNITTEST
    CHECK_NULL_VOID(imageCache_);
    auto cacheImage = imageCache_->GetCacheImage(src);
    CHECK_NULL_VOID(cacheImage);
    CHECK_NULL_VOID(cacheImage->imagePtr);
    imageCache_->ClearCacheImage(src);
#endif
}

std::unique_ptr<Ace::ImageData> CanvasPaintMethod::GetImageData(
    double left, double top, double width, double height)
{
    auto host = frameNode_.Upgrade();
    CHECK_NULL_RETURN(host, nullptr);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    double dirtyWidth = std::abs(width);
    double dirtyHeight = std::abs(height);
    double scaledLeft = left + std::min(width, 0.0);
    double scaledTop = top + std::min(height, 0.0);

    // copy the bitmap to tempCanvas
    RSBitmap currentBitmap;
    if (!DrawBitmap(renderContext, currentBitmap)) {
        return nullptr;
    }

    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_PREMUL };
    RSBitmap tempCache;
    tempCache.Build(dirtyWidth, dirtyHeight, format);
    int32_t size = dirtyWidth * dirtyHeight;

    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    auto srcRect = RSRect(scaledLeft, scaledTop, dirtyWidth + scaledLeft, dirtyHeight + scaledTop);
    auto dstRect = RSRect(0.0, 0.0, dirtyWidth, dirtyHeight);
    RSImage rsImage;
    rsImage.BuildFromBitmap(currentBitmap);
    tempCanvas.DrawImageRect(rsImage, srcRect, dstRect, RSSamplingOptions());
    const uint8_t* pixels = static_cast<const uint8_t*>(tempCache.GetPixels());
    CHECK_NULL_RETURN(pixels, nullptr);
    std::unique_ptr<Ace::ImageData> imageData = std::make_unique<Ace::ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data(blue, green, red, alpha)
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
    }
    return imageData;
}

void CanvasPaintMethod::GetImageData(
    const std::shared_ptr<Ace::ImageData>& imageData)
{
#ifndef ACE_UNITTEST
    auto host = frameNode_.Upgrade();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    CHECK_NULL_VOID(imageData);
    auto dirtyWidth = std::abs(imageData->dirtyWidth);
    auto dirtyHeight = std::abs(imageData->dirtyHeight);
    auto scaledLeft = imageData->dirtyX + std::min(imageData->dirtyWidth, 0);
    auto scaledTop = imageData->dirtyY + std::min(imageData->dirtyHeight, 0);

    auto recordingCanvas = std::static_pointer_cast<RSRecordingCanvas>(rsCanvas_);
    CHECK_NULL_VOID(recordingCanvas);
    auto drawCmdList = recordingCanvas->GetDrawCmdList();
    auto rect = RSRect(scaledLeft, scaledTop, dirtyWidth + scaledLeft, dirtyHeight + scaledTop);
    auto pixelMap = imageData->pixelMap;
    CHECK_NULL_VOID(pixelMap);
    auto sharedPixelMap = pixelMap->GetPixelMapSharedPtr();
    auto ret = rosenRenderContext->GetPixelMap(sharedPixelMap, drawCmdList, &rect);
    if (!ret) {
        if (!drawCmdList || drawCmdList->IsEmpty()) {
            return;
        }
        RSBitmap bitmap;
        RSImageInfo info = RSImageInfo(rect.GetWidth(), rect.GetHeight(),
            RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_PREMUL);
        bitmap.InstallPixels(info, pixelMap->GetWritablePixels(), pixelMap->GetRowBytes());
        RSCanvas canvas;
        canvas.Bind(bitmap);
        canvas.Translate(-rect.GetLeft(), -rect.GetTop());
        drawCmdList->Playback(canvas, &rect);
    }
#endif
}

#ifdef PIXEL_MAP_SUPPORTED
void CanvasPaintMethod::TransferFromImageBitmap(const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_VOID(pixelMap);
    InitImagePaint(nullptr, &imageBrush_, sampleOptions_);
    auto recordingCanvas = std::static_pointer_cast<RSRecordingCanvas>(rsCanvas_);
    CHECK_NULL_VOID(recordingCanvas);
    const std::shared_ptr<Media::PixelMap> tempPixelMap = pixelMap->GetPixelMapSharedPtr();
    CHECK_NULL_VOID(tempPixelMap);
    RSRect srcRect = RSRect(0, 0, tempPixelMap->GetWidth(), tempPixelMap->GetHeight());
    RSRect dstRect = RSRect(0, 0, tempPixelMap->GetWidth(), tempPixelMap->GetHeight());
    recordingCanvas->AttachBrush(imageBrush_);
    recordingCanvas->DrawPixelMapRect(tempPixelMap, srcRect, dstRect, sampleOptions_);
    recordingCanvas->DetachBrush();
}
#endif

std::string CanvasPaintMethod::ToDataURL(const std::string& type, const double quality)
{
#ifndef ACE_UNITTEST
    auto host = frameNode_.Upgrade();
    CHECK_NULL_RETURN(host, UNSUPPORTED);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, UNSUPPORTED);
    std::string mimeType = GetMimeType(type);
    // Quality needs to be between 0.0 and 1.0 for MimeType jpeg and webp
    double qua = GetQuality(mimeType, quality);
    double width = lastLayoutSize_.Width();
    double height = lastLayoutSize_.Height();
    auto imageInfo = SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType);
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888,
        (mimeType == IMAGE_JPEG) ? RSAlphaType::ALPHATYPE_OPAQUE : RSAlphaType::ALPHATYPE_UNPREMUL };
    RSBitmap tempCache;
    tempCache.Build(width, height, format);
    RSBitmap currentBitmap;
    if (!DrawBitmap(renderContext, currentBitmap)) {
        return UNSUPPORTED;
    }
    bool success = currentBitmap.GetPixmap().ScalePixels(
        tempCache.GetPixmap(), RSSamplingOptions(RSCubicResampler { 1 / 3.0f, 1 / 3.0f }));
    CHECK_NULL_RETURN(success, UNSUPPORTED);
    RSPixmap rsSrc = tempCache.GetPixmap();
    SkPixmap src { imageInfo, rsSrc.GetAddr(), rsSrc.GetRowBytes() };
    SkDynamicMemoryWStream dst;
    success = EncodeImage(mimeType, qua, src, dst);
    CHECK_NULL_RETURN(success, UNSUPPORTED);
    auto result = dst.detachAsData();
    CHECK_NULL_RETURN(result, UNSUPPORTED);
    size_t len = SkBase64::Encode(result->data(), result->size(), nullptr);
    if (len > MAX_LENGTH) {
        return UNSUPPORTED;
    }
    SkString info(len);
    SkBase64::Encode(result->data(), result->size(), info.writable_str());
    return std::string(URL_PREFIX).append(mimeType).append(URL_SYMBOL).append(info.c_str());
#else
    return UNSUPPORTED;
#endif
}

bool CanvasPaintMethod::DrawBitmap(RefPtr<RenderContext> renderContext, RSBitmap& currentBitmap)
{
#ifndef ACE_UNITTEST
    auto recordingCanvas = std::static_pointer_cast<RSRecordingCanvas>(rsCanvas_);
    CHECK_NULL_RETURN(recordingCanvas, false);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(renderContext);
    CHECK_NULL_RETURN(rosenRenderContext, false);
    auto drawCmdList = recordingCanvas->GetDrawCmdList();
    CHECK_NULL_RETURN(drawCmdList, false);
    bool res = rosenRenderContext->GetBitmap(currentBitmap, drawCmdList);
    if (res) {
        return true;
    }
    if (drawCmdList->IsEmpty()) {
        return false;
    }
    currentBitmap.Free();
    RSBitmapFormat format;
    if (apiVersion_ >= static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN)) {
        format = { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_PREMUL };
    } else {
        format = { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    }
    currentBitmap.Build(lastLayoutSize_.Width(), lastLayoutSize_.Height(), format);

    RSCanvas currentCanvas;
    currentCanvas.Bind(currentBitmap);
    drawCmdList->Playback(currentCanvas);
    return true;
#else
    return false;
#endif
}

std::string CanvasPaintMethod::GetJsonData(const std::string& path)
{
#ifndef ACE_UNITTEST
    AssetImageLoader imageLoader;
    return imageLoader.LoadJsonData(path, context_);
#else
    return "";
#endif
}

void CanvasPaintMethod::Reset()
{
    ResetStates();
    CHECK_NULL_VOID(rsCanvas_);
    if (rsCanvas_->GetSaveCount() >= DEFAULT_SAVE_COUNT) {
        rsCanvas_->RestoreToCount(0);
    }
    rsCanvas_->ResetMatrix();
    rsCanvas_->Clear(RSColor::COLOR_TRANSPARENT);
    rsCanvas_->Save();
}

int32_t CanvasPaintMethod::GetId() const
{
    auto host = frameNode_.Upgrade();
    CHECK_NULL_RETURN(host, -1);
    return host->GetId();
}

TextDirection CanvasPaintMethod::GetSystemDirection()
{
    auto host = frameNode_.Upgrade();
    CHECK_NULL_RETURN(host, TextDirection::AUTO);
    auto layoutProperty = host->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(host, TextDirection::AUTO);
    auto direction = layoutProperty->GetLayoutDirection();
    if (direction == TextDirection::AUTO) {
        direction = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    return direction;
}

#ifndef ACE_UNITTEST
void CanvasPaintMethod::ConvertTxtStyle(const TextStyle& textStyle, Rosen::TextStyle& txtStyle)
{
    Constants::ConvertTxtStyle(textStyle, context_, txtStyle);
}
#endif

std::string CanvasPaintMethod::GetDumpInfo()
{
    CHECK_NULL_RETURN(rsCanvas_, "Canvas is nullptr");
    // translate
    std::string trans = "TRANS: " + std::to_string(rsCanvas_->GetTotalMatrix().Get(RSMatrix::TRANS_X)) + ", " +
                        std::to_string(rsCanvas_->GetTotalMatrix().Get(RSMatrix::TRANS_Y)) + "; ";
    // scale
    std::string scale = "SCALE: " + std::to_string(rsCanvas_->GetTotalMatrix().Get(RSMatrix::SCALE_X)) + ", " +
                        std::to_string(rsCanvas_->GetTotalMatrix().Get(RSMatrix::SCALE_Y)) + "; ";
    // rotate
    std::string skew = "SKEW: " + std::to_string(rsCanvas_->GetTotalMatrix().Get(RSMatrix::SKEW_X)) + ", " +
                       std::to_string(rsCanvas_->GetTotalMatrix().Get(RSMatrix::SKEW_Y)) + "; ";
    return trans.append(scale).append(skew);
}

void CanvasPaintMethod::SetHostCustomNodeName()
{
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto customNode = frameNode->GetParentCustomNode();
    CHECK_NULL_VOID(customNode);
    customNodeName_ = customNode->GetJSViewName();
}

void CanvasPaintMethod::GetSimplifyDumpInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(rsCanvas_);
    auto matrix = rsCanvas_->GetTotalMatrix();
    json->Put("Trans",
        (std::to_string(matrix.Get(RSMatrix::TRANS_X)) + "," + std::to_string(matrix.Get(RSMatrix::TRANS_Y))).c_str());
    json->Put("Scale",
        (std::to_string(matrix.Get(RSMatrix::SCALE_X)) + "," + std::to_string(matrix.Get(RSMatrix::SCALE_Y))).c_str());
    json->Put("Skew",
        (std::to_string(matrix.Get(RSMatrix::SKEW_X)) + "," + std::to_string(matrix.Get(RSMatrix::SKEW_Y))).c_str());
}
} // namespace OHOS::Ace::NG
