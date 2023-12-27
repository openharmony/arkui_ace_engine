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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H

#include "core/components_ng/pattern/image/image_model.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
// ImageModel is essentially the same class as ImageView
// there should be only one left in the final implementation

class ACE_EXPORT ImageModelNG : public OHOS::Ace::ImageModel {
public:
    void Create(const std::string &src, RefPtr<PixelMap> &pixMap, const std::string &bundleName,
        const std::string &moduleName) override;
    void SetAlt(const ImageSourceInfo &src) override;
    void SetBorder(const Border &border) override;
    void SetBackBorder() override;
    void SetBlur(double blur) override;
    void SetImageFit(ImageFit value) override;
    void SetMatchTextDirection(bool value) override;
    void SetFitOriginSize(bool value) override;
    void SetOnComplete(std::function<void(const LoadImageSuccessEvent &info)> &&callback) override;
    void SetOnError(std::function<void(const LoadImageFailEvent &info)> &&callback) override;
    void SetSvgAnimatorFinishEvent(std::function<void()> &&callback) override;
    void SetImageSourceSize(const std::pair<Dimension, Dimension> &size) override;
    void SetImageFill(const Color &color) override;
    void SetImageInterpolation(ImageInterpolation interpolation) override;
    void SetImageRepeat(ImageRepeat imageRepeat) override;
    void SetImageRenderMode(ImageRenderMode imageRenderMode) override;
    bool IsSrcSvgImage() override;
    void SetAutoResize(bool autoResize) override;
    void SetSyncMode(bool syncMode) override;
    void SetColorFilterMatrix(const std::vector<float> &matrix) override;
    void SetDraggable(bool draggable) override;
    void SetOnDragStart(OnDragStartFunc &&onDragStart) override;
    void SetOnDragEnter(OnDragDropFunc &&onDragEnter) override;
    void SetOnDragLeave(OnDragDropFunc &&onDragLeave) override;
    void SetOnDragMove(OnDragDropFunc &&onDragMove) override;
    void SetOnDrop(OnDragDropFunc &&onDrop) override;
    void SetCopyOption(const CopyOptions &copyOption) override;
    void SetSmoothEdge(float value) override;
    bool UpdateDragItemInfo(DragItemInfo &itemInfo) override;
    void EnableAnalyzer(bool isEnableAnalyzer) override;
    void SetImageAnalyzerConfig(const ImageAnalyzerConfig& config) override;
    void SetResizableSlice(const ImageResizableSlice& slice) override;
    static void SetSmoothEdge(FrameNode *frameNode, float value);
    static void SetCopyOption(FrameNode *frameNode, CopyOptions copyOption);
    static void SetAutoResize(FrameNode *frameNode, bool autoResize);
    static void SetImageRepeat(FrameNode *frameNode, ImageRepeat imageRepeat);
    static void SetImageRenderMode(FrameNode *frameNode, ImageRenderMode imageRenderMode);
    static void SetSyncMode(FrameNode *frameNode, bool syncMode);
    static void SetImageFit(FrameNode *frameNode, ImageFit value);
    static void SetFitOriginSize(FrameNode *framNode, bool value);
    static void SetImageSourceSize(FrameNode *frameNode, const std::pair<Dimension, Dimension> &size);
    static void SetMatchTextDirection(FrameNode *frameNode, bool value);
    static void SetImageFill(FrameNode *frameNode, const Color &color);
    static void SetAlt(FrameNode *frameNode, const ImageSourceInfo &src);
    static void SetImageInterpolation(FrameNode *frameNode, ImageInterpolation interpolation);
    static void SetColorFilterMatrix(FrameNode *frameNode, const std::vector<float> &matrix);
    static void SetDraggable(FrameNode *frameNode, bool draggable);
    static void SetBackBorder(FrameNode *frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H
