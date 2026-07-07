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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_CANVAS_RUNTIME_BRIDGE_API_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_CANVAS_RUNTIME_BRIDGE_API_H

#include <functional>
#include <memory>

#include "base/memory/ace_type.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/pattern/canvas/rendering_context_2d_model.h"

namespace OHOS::Ace::NG {
class FrameNode;
}

namespace OHOS::Ace {

struct ArkUICanvasRuntimeBridge {
    RefPtr<RenderingContext2DModel> (*createCanvasRenderingContext2DModel)();
    RefPtr<RenderingContext2DModel> (*createOffscreenCanvasRenderingContext2DModel)();
    void (*setCanvasRenderingContext2DCallbacks)(
        const RefPtr<RenderingContext2DModel>& context, std::function<void()> onAttach, std::function<void()> onDetach);
    void (*setCanvasRenderingContext2DPatternInstanceId)(
        const RefPtr<RenderingContext2DModel>& context, int32_t instanceId);
    int32_t (*getCanvasRenderingContext2DId)(const RefPtr<RenderingContext2DModel>& context);
    void (*getCanvasRenderingContext2DWidth)(const RefPtr<RenderingContext2DModel>& context, double& width);
    void (*getCanvasRenderingContext2DHeight)(const RefPtr<RenderingContext2DModel>& context, double& height);
#ifdef PIXEL_MAP_SUPPORTED
    void (*transferCanvasRenderingContext2DFromImageBitmap)(
        const RefPtr<RenderingContext2DModel>& context, const RefPtr<AceType>& pixelMap);
#else
    void (*transferCanvasRenderingContext2DFromImageBitmap)(
        const RefPtr<RenderingContext2DModel>& context, const std::shared_ptr<::OHOS::Ace::ImageData>& imageData);
#endif
    void (*startCanvasImageAnalyzer)(
        const RefPtr<RenderingContext2DModel>& context, void* config, OnAnalyzedCallback& onAnalyzed);
    void (*stopCanvasImageAnalyzer)(const RefPtr<RenderingContext2DModel>& context);
    void (*drawCanvasImage)(const RefPtr<RenderingContext2DModel>& context, const ImageInfo& imageInfo);
    void (*drawCanvasSvgImage)(const RefPtr<RenderingContext2DModel>& context, const ImageInfo& imageInfo);
    void (*drawCanvasPixelMap)(const RefPtr<RenderingContext2DModel>& context, const ImageInfo& imageInfo);
    void (*putCanvasImageData)(const RefPtr<RenderingContext2DModel>& context, const ImageData& imageData);
    RefPtr<AceType> (*createOffscreenPattern)(int32_t width, int32_t height);
    size_t (*getOffscreenBitmapSize)(const RefPtr<AceType>& offscreenPattern);
    void (*updateOffscreenSize)(const RefPtr<AceType>& offscreenPattern, int32_t width, int32_t height);
    RefPtr<PixelMap> (*transferOffscreenToImageBitmap)(const RefPtr<AceType>& offscreenPattern);
    std::unique_ptr<::OHOS::Ace::ImageData> (*getOffscreenImageData)(
        const RefPtr<AceType>& offscreenPattern, double left, double top, double width, double height);
    RefPtr<AceType> (*getCanvasPattern)(NG::FrameNode* frameNode);
    void (*setCanvasImageAIOptions)(const RefPtr<AceType>& pattern, void* options);
    void (*setCanvasInvalidate)(const RefPtr<AceType>& pattern);
    void (*setCanvasRSCanvasCallback)(
        const RefPtr<AceType>& pattern, std::function<void(std::shared_ptr<RSCanvas>, double, double)>& callback);
    void (*setCanvasUpdateContextCallback)(
        const RefPtr<AceType>& pattern, std::function<void(CanvasUnit)>&& callback);
    void (*setCanvasRSCanvasForDrawingContext)(const RefPtr<AceType>& pattern);
};

} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
const ArkUICanvasRuntimeBridge* GetCanvasRuntimeBridge();
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_CANVAS_RUNTIME_BRIDGE_API_H
