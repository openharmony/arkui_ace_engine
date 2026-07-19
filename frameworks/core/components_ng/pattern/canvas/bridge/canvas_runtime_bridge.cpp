/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/canvas_runtime_bridge_api.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.h"

namespace OHOS::Ace::NG {
namespace {

RefPtr<RenderingContext2DModel> CreateCanvasRenderingContext2DModelImpl()
{
    return AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
}

RefPtr<RenderingContext2DModel> CreateOffscreenCanvasRenderingContext2DModelImpl()
{
    return AceType::MakeRefPtr<OffscreenCanvasRenderingContext2DModelNG>();
}

RefPtr<CanvasRenderingContext2DModel> GetCanvasRenderingContext2DModel(
    const RefPtr<RenderingContext2DModel>& context)
{
    return AceType::DynamicCast<CanvasRenderingContext2DModel>(context);
}

void SetCanvasRenderingContext2DCallbacksImpl(
    const RefPtr<RenderingContext2DModel>& context, std::function<void()> onAttach, std::function<void()> onDetach)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_VOID(model);
    model->SetOnAttach(std::move(onAttach));
    model->SetOnDetach(std::move(onDetach));
}

void SetCanvasRenderingContext2DPatternInstanceIdImpl(
    const RefPtr<RenderingContext2DModel>& context, int32_t instanceId)
{
    CHECK_NULL_VOID(context);
    context->SetPatternInstanceId(instanceId);
}

int32_t GetCanvasRenderingContext2DIdImpl(const RefPtr<RenderingContext2DModel>& context)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_RETURN(model, -1);
    return model->GetId();
}

void GetCanvasRenderingContext2DWidthImpl(const RefPtr<RenderingContext2DModel>& context, double& width)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_VOID(model);
    model->GetWidth(width);
}

void GetCanvasRenderingContext2DHeightImpl(const RefPtr<RenderingContext2DModel>& context, double& height)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_VOID(model);
    model->GetHeight(height);
}

#ifdef PIXEL_MAP_SUPPORTED
void TransferCanvasRenderingContext2DFromImageBitmapImpl(
    const RefPtr<RenderingContext2DModel>& context, const RefPtr<AceType>& pixelMap)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_VOID(model);
    model->TransferFromImageBitmap(pixelMap);
}
#else
void TransferCanvasRenderingContext2DFromImageBitmapImpl(
    const RefPtr<RenderingContext2DModel>& context, const std::shared_ptr<::OHOS::Ace::ImageData>& imageData)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_VOID(model);
    model->TransferFromImageBitmap(imageData);
}
#endif

void StartCanvasImageAnalyzerImpl(
    const RefPtr<RenderingContext2DModel>& context, void* config, OnAnalyzedCallback& onAnalyzed)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_VOID(model);
    model->StartImageAnalyzer(config, onAnalyzed);
}

void StopCanvasImageAnalyzerImpl(const RefPtr<RenderingContext2DModel>& context)
{
    auto model = GetCanvasRenderingContext2DModel(context);
    CHECK_NULL_VOID(model);
    model->StopImageAnalyzer();
}

void DrawCanvasImageImpl(const RefPtr<RenderingContext2DModel>& context, const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(context);
    context->DrawImage(imageInfo);
}

void DrawCanvasSvgImageImpl(const RefPtr<RenderingContext2DModel>& context, const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(context);
    context->DrawSvgImage(imageInfo);
}

void DrawCanvasPixelMapImpl(const RefPtr<RenderingContext2DModel>& context, const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(context);
    context->DrawPixelMap(imageInfo);
}

void PutCanvasImageDataImpl(const RefPtr<RenderingContext2DModel>& context, const ImageData& imageData)
{
    CHECK_NULL_VOID(context);
    context->PutImageData(imageData);
}

RefPtr<AceType> CreateOffscreenPatternImpl(int32_t width, int32_t height)
{
    return AceType::MakeRefPtr<OffscreenCanvasPattern>(width, height);
}

size_t GetOffscreenBitmapSizeImpl(const RefPtr<AceType>& offscreenPattern)
{
    auto pattern = AceType::DynamicCast<OffscreenCanvasPattern>(offscreenPattern);
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->GetBitmapSize();
}

void UpdateOffscreenSizeImpl(const RefPtr<AceType>& offscreenPattern, int32_t width, int32_t height)
{
    auto pattern = AceType::DynamicCast<OffscreenCanvasPattern>(offscreenPattern);
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSize(width, height);
}

RefPtr<PixelMap> TransferOffscreenToImageBitmapImpl(const RefPtr<AceType>& offscreenPattern)
{
    auto pattern = AceType::DynamicCast<OffscreenCanvasPattern>(offscreenPattern);
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->TransferToImageBitmap();
}

std::unique_ptr<::OHOS::Ace::ImageData> GetOffscreenImageDataImpl(
    const RefPtr<AceType>& offscreenPattern, double left, double top, double width, double height)
{
    auto pattern = AceType::DynamicCast<OffscreenCanvasPattern>(offscreenPattern);
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetImageData(left, top, width, height);
}

RefPtr<AceType> GetCanvasPatternImpl(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    return CanvasModelNG::GetCanvasPattern(frameNode);
}

void SetCanvasImageAIOptionsImpl(const RefPtr<AceType>& pattern, void* options)
{
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetImageAIOptions(options);
}

void SetCanvasInvalidateImpl(const RefPtr<AceType>& pattern)
{
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetInvalidate();
}

void SetCanvasRSCanvasCallbackImpl(
    const RefPtr<AceType>& pattern, std::function<void(std::shared_ptr<RSCanvas>, double, double)>& callback)
{
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetRSCanvasCallback(callback);
}

void SetCanvasUpdateContextCallbackImpl(
    const RefPtr<AceType>& pattern, std::function<void(CanvasUnit)>&& callback)
{
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetUpdateContextCallback(std::move(callback));
}

void SetCanvasRSCanvasForDrawingContextImpl(const RefPtr<AceType>& pattern)
{
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetRSCanvasForDrawingContext();
}

} // namespace

const ArkUICanvasRuntimeBridge* GetCanvasRuntimeBridge()
{
    static const ArkUICanvasRuntimeBridge bridge = {
        .createCanvasRenderingContext2DModel = CreateCanvasRenderingContext2DModelImpl,
        .createOffscreenCanvasRenderingContext2DModel = CreateOffscreenCanvasRenderingContext2DModelImpl,
        .setCanvasRenderingContext2DCallbacks = SetCanvasRenderingContext2DCallbacksImpl,
        .setCanvasRenderingContext2DPatternInstanceId = SetCanvasRenderingContext2DPatternInstanceIdImpl,
        .getCanvasRenderingContext2DId = GetCanvasRenderingContext2DIdImpl,
        .getCanvasRenderingContext2DWidth = GetCanvasRenderingContext2DWidthImpl,
        .getCanvasRenderingContext2DHeight = GetCanvasRenderingContext2DHeightImpl,
        .transferCanvasRenderingContext2DFromImageBitmap = TransferCanvasRenderingContext2DFromImageBitmapImpl,
        .startCanvasImageAnalyzer = StartCanvasImageAnalyzerImpl,
        .stopCanvasImageAnalyzer = StopCanvasImageAnalyzerImpl,
        .drawCanvasImage = DrawCanvasImageImpl,
        .drawCanvasSvgImage = DrawCanvasSvgImageImpl,
        .drawCanvasPixelMap = DrawCanvasPixelMapImpl,
        .putCanvasImageData = PutCanvasImageDataImpl,
        .createOffscreenPattern = CreateOffscreenPatternImpl,
        .getOffscreenBitmapSize = GetOffscreenBitmapSizeImpl,
        .updateOffscreenSize = UpdateOffscreenSizeImpl,
        .transferOffscreenToImageBitmap = TransferOffscreenToImageBitmapImpl,
        .getOffscreenImageData = GetOffscreenImageDataImpl,
        .getCanvasPattern = GetCanvasPatternImpl,
        .setCanvasImageAIOptions = SetCanvasImageAIOptionsImpl,
        .setCanvasInvalidate = SetCanvasInvalidateImpl,
        .setCanvasRSCanvasCallback = SetCanvasRSCanvasCallbackImpl,
        .setCanvasUpdateContextCallback = SetCanvasUpdateContextCallbackImpl,
        .setCanvasRSCanvasForDrawingContext = SetCanvasRSCanvasForDrawingContextImpl,
    };
    return &bridge;
}

} // namespace OHOS::Ace::NG
