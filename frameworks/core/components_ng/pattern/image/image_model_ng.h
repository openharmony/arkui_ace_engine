/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H

#include "core/components/common/layout/constants.h"
#include "core/components/declaration/image/image_animator_declaration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_model.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::Ace::NG {
// ImageModel is essentially the same class as ImageView
// there should be only one left in the final implementation

class ACE_EXPORT ImageModelNG : public OHOS::Ace::ImageModel {
public:
    void Create(const ImageInfoConfig& imageInfoConfig, RefPtr<PixelMap>& pixMap) override;
    void CreateWithResourceObj(ImageResourceType resourceType, const RefPtr<ResourceObject>& resObject) override;
    void ResetImage() override;
    void CreateAnimation(const std::vector<ImageProperties>& imageList, int32_t duration, int32_t iteration) override;
    bool GetIsAnimation() override;
    void SetAlt(const ImageSourceInfo& src) override;
    void SetBorder(const Border& border) override;
    void SetBackBorder() override;
    void SetBorderRadius(const Dimension& value) override;
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override;
    void SetBorderRadius(const NG::BorderRadiusProperty& borderRadius) override;
    void SetBlur(double blur) override;
    void SetImageFit(ImageFit value) override;
    void SetImageMatrix(const Matrix4& value) override;
    void SetMatchTextDirection(bool value) override;
    void SetFitOriginSize(bool value) override;
    void SetOnComplete(std::function<void(const LoadImageSuccessEvent& info)>&& callback) override;
    void SetOnError(std::function<void(const LoadImageFailEvent& info)>&& callback) override;
    void SetSvgAnimatorFinishEvent(std::function<void()>&& callback) override;
    void SetImageSourceSize(const std::pair<Dimension, Dimension>& size) override;
    void SetImageFill(const Color& color) override;
    void ResetImageFill() override;
    void SetImageInterpolation(ImageInterpolation interpolation) override;
    void SetImageRepeat(ImageRepeat imageRepeat) override;
    void SetImageRenderMode(ImageRenderMode imageRenderMode) override;
    bool IsSrcSvgImage() override;
    void SetAutoResize(bool autoResize) override;
    void SetSyncMode(bool syncMode) override;
    void SetColorFilterMatrix(const std::vector<float>& matrix) override;
    void SetDrawingColorFilter(RefPtr<DrawingColorFilter>& colorFilter) override;
    void SetDraggable(bool draggable) override;
    void SetOnDragStart(OnDragStartFunc&& onDragStart) override;
    void SetOnDragEnter(OnDragDropFunc&& onDragEnter) override;
    void SetOnDragLeave(OnDragDropFunc&& onDragLeave) override;
    void SetOnDragMove(OnDragDropFunc&& onDragMove) override;
    void SetOnDrop(OnDragDropFunc&& onDrop) override;
    void SetCopyOption(const CopyOptions& copyOption) override;
    void SetSmoothEdge(float value) override;
    void SetDynamicRangeMode(DynamicRangeMode dynamicRangeMode) override;
    void SetHdrBrightness(float hdrBrightness) override;
    void SetEnhancedImageQuality(AIImageQuality imageQuality) override;
    void SetOrientation(ImageRotateOrientation orientation) override;
    bool UpdateDragItemInfo(DragItemInfo& itemInfo) override;
    void EnableAnalyzer(bool isEnableAnalyzer) override;
    void SetImageAnalyzerConfig(const ImageAnalyzerConfig& config) override;
    void SetImageAnalyzerConfig(void* config) override;
    void SetImageAIOptions(void* options) override;
    void SetResizableSlice(ImageResizableSlice& slice) override;
    void SetResizableLattice(const RefPtr<DrawingLattice>& lattice) override;
    void ResetResizableLattice() override;
    void SetImageFillSetByUser(bool value) override;
    void SetSupportSvg2(bool enable) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, const std::string& src, RefPtr<PixelMap>& pixMap,
        const std::string& bundleName, const std::string& moduleName, bool isUriPureNumber = false);
    static void InitImage(FrameNode* frameNode, std::string& src);
    static void ResetImage(FrameNode* frameNode);
    static void SetInitialSrc(FrameNode* frameNode, const std::string& src, const std::string& bundleName,
        const std::string& moduleName, bool isUriPureNumber = false);
    static void SetInitialPixelMap(FrameNode* frameNode, RefPtr<PixelMap>& pixMap);
    static void SetSmoothEdge(FrameNode* frameNode, float value);
    static void SetCopyOption(FrameNode* frameNode, CopyOptions copyOption);
    static void SetAutoResize(FrameNode* frameNode, bool autoResize);
    static void ResetAutoResize(FrameNode* frameNode);
    static void SetImageRepeat(FrameNode* frameNode, ImageRepeat imageRepeat);
    static void SetImageRenderMode(FrameNode* frameNode, ImageRenderMode imageRenderMode);
    static void SetOrientation(FrameNode* frameNode, ImageRotateOrientation orientation);
    static void SetSyncMode(FrameNode* frameNode, bool syncMode);
    static void SetImageMatrix(FrameNode* frameNode, const Matrix4& value);
    static void SetImageFit(FrameNode* frameNode, ImageFit value);
    static void SetDrawingColorFilter(FrameNode* frameNode, RefPtr<DrawingColorFilter>& colorFilter);
    static void SetFitOriginSize(FrameNode* framNode, bool value);
    static void SetImageSourceSize(FrameNode* frameNode, const std::pair<Dimension, Dimension>& size);
    static void SetMatchTextDirection(FrameNode* frameNode, bool value);
    static void SetImageFill(FrameNode* frameNode, const Color& color);
    static void ResetImageFill(FrameNode* frameNode);
    static void SetAlt(FrameNode* frameNode, const ImageSourceInfo& src);
    static void SetImageInterpolation(FrameNode* frameNode, ImageInterpolation interpolation);
    static void ResetImageInterpolation(FrameNode* frameNode);
    static void SetColorFilterMatrix(FrameNode* frameNode, const std::vector<float>& matrix);
    static void SetDraggable(FrameNode* frameNode, bool draggable);
    static void SetBackBorder(FrameNode* frameNode);
    static void SetBorderRadius(FrameNode* frameNode, const Dimension& value);
    static void SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight);
    static void SetBorderRadius(FrameNode* frameNode, const NG::BorderRadiusProperty& borderRadius);
    static void ResetBackBorder(FrameNode* frameNode);
    static bool IsSrcSvgImage(FrameNode* frameNode);
    static void SetOnComplete(FrameNode* frameNode, std::function<void(const LoadImageSuccessEvent& info)>&& callback);
    static void SetOnError(FrameNode* frameNode, std::function<void(const LoadImageFailEvent& info)>&& callback);
    static void SetOnSvgPlayFinish(FrameNode* frameNode, std::function<void()>&& callback);
    static void SetOnDownloadProgress(
        FrameNode* frameNode, std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>&& callback);
    static ImageSourceInfo GetSrc(FrameNode* frameNode);
    static ImageFit GetObjectFit(FrameNode* frameNode);
    static ImageRotateOrientation GetOrientation(FrameNode* frameNode);
    static std::pair<CalcDimension, CalcDimension> GetImageSourceSize(FrameNode* frameNode);
    static float GetHdrBrightness(FrameNode* frameNode);
    static DynamicRangeMode GetDynamicRangeMode(FrameNode* frameNode);
    static bool GetEnableAnalyzer(FrameNode* frameNode);
    static CopyOptions GetCopyOption(FrameNode* frameNode);
    static bool GetMatchTextDirection(FrameNode* frameNode);
    static Matrix4 GetImageMatrix(FrameNode* frameNode);
    static ImageInterpolation GetInterpolation(FrameNode* frameNode);
    static ImageRepeat GetObjectRepeat(FrameNode* frameNode);
    static std::vector<float> GetColorFilter(FrameNode* frameNode);
    static bool GetAutoResize(FrameNode* frameNode);
    static bool GetSyncLoad(FrameNode* frameNode);
    static ImageSourceInfo GetAlt(FrameNode* frameNode);
    static bool GetDraggable(FrameNode* frameNode);
    static ImageRenderMode GetImageRenderMode(FrameNode* frameNode);
    static void SetResizableSlice(FrameNode* frameNode, ImageResizableSlice& slice);
    static void SetResizableLattice(FrameNode* frameNode, const RefPtr<DrawingLattice>& lattice);
    static void ResetResizableLattice(FrameNode* frameNode);
    static ImageResizableSlice GetResizableSlice(FrameNode* frameNode);
    static void SetDynamicRangeMode(FrameNode* frameNode, DynamicRangeMode dynamicRangeMode);
    static void SetHdrBrightness(FrameNode* frameNode, float hdrBrightness);
    static void SetEnhancedImageQuality(FrameNode* frameNode, AIImageQuality imageQuality);
    static bool GetFitOriginalSize(FrameNode* frameNode);
    static uint32_t GetFillColor(FrameNode* frameNode);
    static void SetPixelMap(FrameNode* frameNode, void* drawableDescriptor);
    static void SetPixelMapArray(FrameNode* frameNode, void* animatedDrawableDescriptor);
    static void SetResource(FrameNode* frameNode, void* resource);
    static void EnableAnalyzer(FrameNode* frameNode, bool isEnableAnalyzer);
    static void SetImageAnalyzerConfig(FrameNode* frameNode, void* config);
    static RefPtr<DrawingColorFilter> GetDrawingColorFilter(FrameNode* frameNode);
    static void ResetImageSrc(FrameNode* frameNode);
    static void ResetImageAlt(FrameNode* frameNode);
    static void SetAltPixelMap(FrameNode* frameNode, void* pixelMap);
    static void SetAltResource(FrameNode* frameNode, void* resource);
    static void CreateWithResourceObj(
        FrameNode* frameNode, ImageResourceType resourceType, const RefPtr<ResourceObject>& resObject);
    static void SetSupportSvg2(FrameNode* frameNode, bool enable);
    static void ResetSupportSvg2(FrameNode* frameNode);

private:
    ImagePattern* GetImagePattern();
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H
