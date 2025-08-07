/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_SPAN_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_SPAN_VIEW_H

#include <string>

#include "base/image/pixel_map.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/components/image/image_event.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT ImageSpanView {
public:
    static void SetObjectFit(ImageFit value);
    static void SetVerticalAlign(VerticalAlign verticalAlign);
    static void SetBaselineOffset(const Dimension& value);
    static void SetVerticalAlign(FrameNode* frameNode, VerticalAlign verticalAlign);
    static void SetBaselineOffset(FrameNode* frameNode, const Dimension& value);
    static float GetBaselineOffset(FrameNode* frameNode, int32_t unit);
    static void SetPlaceHolderStyle(TextBackgroundStyle& radius);
    static void Create();
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static ImageSourceInfo GetImageSpanSrc(FrameNode* frameNode);
    static ImageFit GetObjectFit(FrameNode* frameNode);
    static void SetAlt(FrameNode* frameNode, RefPtr<PixelMap>& pixMap);
    static VerticalAlign GetVerticalAlign(FrameNode* frameNode);
    static void SetPlaceHolderStyle(FrameNode* frameNode, TextBackgroundStyle& style);
    static TextBackgroundStyle GetSpanTextBackgroundStyle(FrameNode* frameNode);
    static void SetOnComplete(FrameNode* frameNode, std::function<void(const LoadImageSuccessEvent& info)>&& callback);
    static void SetOnError(FrameNode* frameNode, std::function<void(const LoadImageFailEvent& info)>&& callback);
    static void SetBorderRadius(FrameNode* frameNode, NG::BorderRadiusProperty borderRadius);
    static void ResetBorderRadius(FrameNode* frameNode);
    static void SetPixelMap(FrameNode* frameNode, RefPtr<PixelMap>& pixMap);
    static void SetSrc(FrameNode* frameNode, const std::string& src, const std::string& bundleName,
        const std::string& moduleName, bool isUriPureNumber);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_SPAN_VIEW_H
