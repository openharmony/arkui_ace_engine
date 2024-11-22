/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_MODEL_IMPL_H

#define NAPI_VERSION 8

#include "core/components_ng/pattern/image/image_model.h"
#include "core/image/image_source_info.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace::Framework {

class ImageModelImpl : public OHOS::Ace::ImageModel {
public:
    void SetAlt(const ImageSourceInfo& src) override;
    void SetBorder(const Border& border) override;
    void SetBorderRadius(const Dimension& value) override {};
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override
    {}
    void SetBorderRadius(const NG::BorderRadiusProperty& borderRadius) override {}
    void SetBackBorder() override;
    void SetBlur(double blur) override;
    void SetImageFit(ImageFit value) override;
    void SetMatchTextDirection(bool value) override;
    void SetFitOriginSize(bool value) override;
    void SetOnComplete(std::function<void(const LoadImageSuccessEvent& info)>&& callback) override;
    void SetOnError(std::function<void(const LoadImageFailEvent& info)>&& callback) override;
    void SetSvgAnimatorFinishEvent(std::function<void()>&& callback) override;
    void Create(const ImageInfoConfig& imageInfoConfig, RefPtr<PixelMap>& pixMap) override;
    void SetImageSourceSize(const std::pair<Dimension, Dimension>& size) override;
    void SetImageFill(const Color& color) override;
    void SetImageInterpolation(ImageInterpolation iterpolation) override;
    void SetImageRepeat(ImageRepeat imageRepeat) override;
    void SetImageRenderMode(ImageRenderMode imageRenderMode) override;
    bool IsSrcSvgImage() override;
    void SetAutoResize(bool autoResize) override;
    void SetResizableSlice(const ImageResizableSlice& slice) override {};
    void SetResizableLattice(const RefPtr<DrawingLattice>& lattice) override {};
    void ResetResizableLattice() override {};
    void SetSyncMode(bool syncMode) override;
    void SetColorFilterMatrix(const std::vector<float>& matrix) override;
    void SetDrawingColorFilter(RefPtr<DrawingColorFilter>& colorFilter) override {};
    void SetDraggable(bool draggable) override {}
    void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) override;
    void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) override;
    void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) override;
    void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) override;
    void SetOnDrop(NG::OnDragDropFunc&& onDrop) override;
    void SetCopyOption(const CopyOptions& copyOption) override;
    bool UpdateDragItemInfo(DragItemInfo& itemInfo) override;
    void EnableAnalyzer(bool isEnableAnalyzer) override {}
    void SetImageAnalyzerConfig(const ImageAnalyzerConfig& config) override {}
    void SetImageAnalyzerConfig(void* config) override {}
    void SetImageAIOptions(void* config) override {}
    void SetSmoothEdge(float value)  override {}
    void ResetImage() override {}
    void SetDynamicRangeMode(DynamicRangeMode dynamicRangeMode) override {}
    void SetEnhancedImageQuality(AIImageQuality imageQuality) override {}
    void SetOrientation(ImageRotateOrientation orientation) override {}
    void CreateAnimation(const std::vector<ImageProperties>& imageList, int32_t duration, int32_t iteration) override {}
    bool GetIsAnimation() override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_MODEL_IMPL_H
