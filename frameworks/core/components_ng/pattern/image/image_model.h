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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_H

#include <mutex>

#include "base/geometry/dimension.h"
#include "base/image/drawing_color_filter.h"
#include "base/image/drawing_lattice.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/image/image_animator_declaration.h"
#include "core/components/image/image_event.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

namespace OHOS::Ace {
struct ACE_FORCE_EXPORT ImageInfoConfig {
    std::shared_ptr<std::string> src;
    std::string bundleName;
    std::string moduleName;
    bool isUriPureNumber = false;
    bool isImageSpan = false;

    ImageInfoConfig() {}

    ImageInfoConfig(
        const std::shared_ptr<std::string>& src_, const std::string& bundleName_, const std::string& moduleName_)
        : src(src_), bundleName(bundleName_), moduleName(moduleName_)
    {}

    ImageInfoConfig(const std::shared_ptr<std::string>& src_, const std::string& bundleName_,
        const std::string& moduleName_, bool isUriPureNumber_, bool isImageSpan_)
        : src(src_), bundleName(bundleName_), moduleName(moduleName_), isUriPureNumber(isUriPureNumber_),
          isImageSpan(isImageSpan_)
    {}
};
class ACE_FORCE_EXPORT ImageModel {
public:
    static ImageModel *GetInstance();
    virtual ~ImageModel() = default;

    virtual void SetAlt(const ImageSourceInfo &src) = 0;
    virtual void SetBlur(double blur) = 0;
    virtual void SetBorder(const Border &border) = 0;
    virtual void SetBorderRadius(const Dimension& value) = 0;
    virtual void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) = 0;
    virtual void SetBorderRadius(const NG::BorderRadiusProperty& borderRadius) = 0;
    virtual void SetBackBorder() = 0;
    virtual void SetImageFit(ImageFit value) = 0;
    virtual void SetMatchTextDirection(bool value) = 0;
    virtual void SetFitOriginSize(bool value) = 0;
    virtual void SetOnComplete(std::function<void(const LoadImageSuccessEvent &info)> &&callback) = 0;
    virtual void SetOnError(std::function<void(const LoadImageFailEvent &info)> &&callback) = 0;
    virtual void SetSvgAnimatorFinishEvent(std::function<void()> &&callback) = 0;
    virtual void Create(const ImageInfoConfig& imageInfoConfig, RefPtr<PixelMap>& pixMap) = 0;
    virtual void ResetImage() = 0;
    virtual void CreateAnimation(const std::vector<ImageProperties>& imageList,
        int32_t duration, int32_t iteration) = 0;
    virtual void SetImageSourceSize(const std::pair<Dimension, Dimension> &size) = 0;
    virtual void SetImageFill(const Color &color) = 0;
    virtual void SetImageInterpolation(ImageInterpolation interpolation) = 0;
    virtual void SetImageRepeat(ImageRepeat imageRepeat) = 0;
    virtual void SetImageRenderMode(ImageRenderMode imageRenderMode) = 0;
    virtual bool IsSrcSvgImage() = 0;
    virtual void SetAutoResize(bool autoResize) = 0;
    virtual void SetResizableSlice(const ImageResizableSlice& slice) = 0;
    virtual void SetResizableLattice(const RefPtr<DrawingLattice>& lattice) = 0;
    virtual void ResetResizableLattice() = 0;
    virtual void SetSyncMode(bool syncMode) = 0;
    virtual void SetColorFilterMatrix(const std::vector<float>& matrix) = 0;
    virtual void SetDrawingColorFilter(RefPtr<DrawingColorFilter> &colorFilter) = 0;
    virtual void SetDraggable(bool draggable) = 0;
    virtual void SetOnDragStart(NG::OnDragStartFunc &&onDragStart) = 0;
    virtual void SetOnDragEnter(NG::OnDragDropFunc &&onDragEnter) = 0;
    virtual void SetOnDragLeave(NG::OnDragDropFunc &&onDragLeave) = 0;
    virtual void SetOnDragMove(NG::OnDragDropFunc &&onDragMove) = 0;
    virtual void SetOnDrop(NG::OnDragDropFunc &&onDrop) = 0;
    virtual void SetCopyOption(const CopyOptions &copyOption) = 0;
    virtual bool UpdateDragItemInfo(DragItemInfo &itemInfo) = 0;
    virtual void EnableAnalyzer(bool isEnableAnalyzer) = 0;
    virtual void SetImageAnalyzerConfig(const ImageAnalyzerConfig& config) = 0;
    virtual void SetImageAnalyzerConfig(void* config) = 0;
    virtual void SetImageAIOptions(void* options) = 0;
    virtual void SetSmoothEdge(float value) = 0;
    virtual void SetDynamicRangeMode(DynamicRangeMode dynamicRangeMode) = 0;
    virtual void SetEnhancedImageQuality(AIImageQuality imageQuality) = 0;
    virtual void SetOrientation(ImageRotateOrientation orientation) = 0;
    virtual bool GetIsAnimation() = 0;
private:
    static std::unique_ptr<ImageModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_H
