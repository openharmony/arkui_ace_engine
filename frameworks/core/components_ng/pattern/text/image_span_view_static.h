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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_SPAN_VIEW_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_SPAN_VIEW_STATIC_H

#include <string>

#include "base/image/pixel_map.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/components/image/image_event.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT ImageSpanViewStatic {
public:
    static void SetObjectFit(FrameNode* frameNode, const std::optional<ImageFit>& value);
    static void SetVerticalAlign(FrameNode* frameNode, const std::optional<VerticalAlign>& verticalAlign);
    static void SetBaselineOffset(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetImageSpanSrc(FrameNode* frameNode, const ImageSourceInfo& info);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_SPAN_VIEW_STATIC_H
