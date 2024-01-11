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
#include "core/interfaces/native/node/node_image_span_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr VerticalAlign DEFAULT_VERTICAL_ALIGN = VerticalAlign::BOTTOM;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;

void SetImageSpanVerticalAlign(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetVerticalAlign(frameNode, static_cast<VerticalAlign>(value));
}

void ResetImageSpanVerticalAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetVerticalAlign(frameNode, DEFAULT_VERTICAL_ALIGN);
}

void SetImageSpanObjectFit(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, static_cast<ImageFit>(value));
}

void ResetImageSpanObjectFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, DEFAULT_OBJECT_FIT);
}
} // namespace

namespace NodeModifier {
const ArkUIImageSpanModifier* GetImageSpanModifier()
{
    static const ArkUIImageSpanModifier modifier = { SetImageSpanVerticalAlign, ResetImageSpanVerticalAlign,
        SetImageSpanObjectFit, ResetImageSpanObjectFit };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG