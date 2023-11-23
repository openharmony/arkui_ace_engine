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

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::Ace::NG {
void ImageSpanView::SetObjectFit(ImageFit value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, ImageFit, value);
}

void ImageSpanView::SetVerticalAlign(VerticalAlign verticalAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ImageLayoutProperty, VerticalAlign, verticalAlign);
}

void ImageSpanView::SetVerticalAlign(FrameNode* frameNode, VerticalAlign verticalAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ImageLayoutProperty, VerticalAlign, verticalAlign, frameNode);
}
} // namespace OHOS::Ace::NG
