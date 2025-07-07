/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_STATIC_H

#include "core/components/declaration/image/image_animator_declaration.h"
#include "core/components/image/image_event.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
// ImageModel is essentially the same class as ImageView
// there should be only one left in the final implementation

class ACE_EXPORT ImageModelStatic {
public:
    static void SetSmoothEdge(FrameNode* frameNode, const std::optional<float>& value);
    static void SetCopyOption(FrameNode* frameNode, const std::optional<CopyOptions>& copyOption);
    static void SetImageRepeat(FrameNode* frameNode, const std::optional<ImageRepeat>& imageRepeat);
    static void SetImageRenderMode(FrameNode* frameNode, const std::optional<ImageRenderMode>& imageRenderMode);
    static void SetImageMatrix(FrameNode* frameNode, const std::optional<Matrix4>& value);
    static void SetImageFit(FrameNode* frameNode, const std::optional<ImageFit>& value);
    static void SetImageSourceSize(FrameNode* frameNode, const std::optional<std::pair<Dimension, Dimension>>& size);
    static void SetImageFill(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetAlt(FrameNode* frameNode, const std::optional<ImageSourceInfo>& src);
    static void SetImageInterpolation(FrameNode* frameNode, const std::optional<ImageInterpolation>& interpolation);
    static void SetDynamicRangeMode(FrameNode* frameNode, const std::optional<DynamicRangeMode>& dynamicRangeMode);
    static void SetOrientation(FrameNode* frameNode, const std::optional<ImageRotateOrientation>& orientation);
    static void SetEnhancedImageQuality(FrameNode* frameNode, const std::optional<AIImageQuality>& imageQuality);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_STATIC_H
