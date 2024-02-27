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
constexpr int32_t FRONTEND_VERTICAL_ALIGN_BASELINE = 0;
constexpr int32_t FRONTEND_VERTICAL_ALIGN_BOTTOM = 1;
constexpr int32_t FRONTEND_VERTICAL_ALIGN_CENTER = 2;
constexpr int32_t FRONTEND_VERTICAL_ALIGN_TOP = 3;

VerticalAlign GetBackendVerticalAlign(int32_t ndkVerticalAlign)
{
    switch (ndkVerticalAlign) {
        case FRONTEND_VERTICAL_ALIGN_BASELINE:
            return VerticalAlign::BASELINE;
            break;
        case FRONTEND_VERTICAL_ALIGN_BOTTOM:
            return VerticalAlign::BOTTOM;
            break;
        case FRONTEND_VERTICAL_ALIGN_CENTER:
            return VerticalAlign::CENTER;
            break;
        case FRONTEND_VERTICAL_ALIGN_TOP:
            return VerticalAlign::TOP;
            break;
        default:
            break;
    }
    return VerticalAlign::BOTTOM;
}

void SetImageSpanVerticalAlign(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetVerticalAlign(frameNode, GetBackendVerticalAlign(value));
}

int32_t GetFrontEndVerticalAlign(int32_t ndkVerticalAlign)
{
    switch (ndkVerticalAlign) {
        case static_cast<int32_t>(VerticalAlign::BASELINE):
            return FRONTEND_VERTICAL_ALIGN_BASELINE;
            break;
        case static_cast<int32_t>(VerticalAlign::BOTTOM):
            return FRONTEND_VERTICAL_ALIGN_BOTTOM;
            break;
        case static_cast<int32_t>(VerticalAlign::CENTER):
            return FRONTEND_VERTICAL_ALIGN_CENTER;
            break;
        case static_cast<int32_t>(VerticalAlign::TOP):
            return FRONTEND_VERTICAL_ALIGN_TOP;
            break;
        default:
            break;
    }
    return FRONTEND_VERTICAL_ALIGN_BOTTOM;
}

int32_t GetImageSpanVerticalAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, FRONTEND_VERTICAL_ALIGN_BOTTOM);
    return GetFrontEndVerticalAlign(static_cast<int32_t>(ImageSpanView::GetVerticalAlign(frameNode)));
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

int32_t GetImageSpanObjectFit(ArkUINodeHandle node)
{
    int32_t defaultObjectFit = static_cast<int32_t>(DEFAULT_OBJECT_FIT);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, defaultObjectFit);
    return static_cast<int32_t>(ImageModelNG::GetObjectFit(frameNode));
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
        SetImageSpanObjectFit, ResetImageSpanObjectFit, GetImageSpanVerticalAlign, GetImageSpanObjectFit};
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG