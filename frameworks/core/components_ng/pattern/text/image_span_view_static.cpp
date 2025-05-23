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

#include "core/components_ng/pattern/text/image_span_view.h"
#include <cstdint>

#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/image_span_view_static.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
void ImageSpanViewStatic::SetObjectFit(FrameNode* frameNode, const std::optional<ImageFit>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, frameNode);
    }
}

void ImageSpanViewStatic::SetVerticalAlign(FrameNode* frameNode, const std::optional<VerticalAlign>& verticalAlign)
{
    if (verticalAlign) {
        ImageSpanView::SetVerticalAlign(frameNode, verticalAlign.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, VerticalAlign, frameNode);
    }
}

void ImageSpanViewStatic::SetBaselineOffset(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ImageSpanView::SetBaselineOffset(frameNode, value.value());
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, BaselineOffset, frameNode);
    }
}

void ImageSpanViewStatic::SetImageSpanSrc(FrameNode* frameNode, const ImageSourceInfo& info)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageSourceInfo, info, frameNode);
    if (info.IsPixmap()) {
        const auto& pattern = frameNode->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSyncLoad(true);
    }
}

} // namespace OHOS::Ace::NG
