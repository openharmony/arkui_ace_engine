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
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int DEFAULT_LENGTH = 4;
constexpr VerticalAlign DEFAULT_VERTICAL_ALIGN = VerticalAlign::BOTTOM;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;
constexpr Dimension DEFAULT_BASELINE_OFFSET { 0.0, DimensionUnit::FP };

void SetImageSpanVerticalAlign(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetVerticalAlign(frameNode, static_cast<VerticalAlign>(value));
}

int32_t GetImageSpanVerticalAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<int32_t>(DEFAULT_VERTICAL_ALIGN));
    return static_cast<int32_t>(ImageSpanView::GetVerticalAlign(frameNode));
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

void SetImageSpanTextBackgroundStyle(
    ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    TextBackgroundStyle font;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    font.backgroundColor = Color(color);
    font.backgroundRadius = borderRadius;
    font.backgroundRadius->multiValued = true;
    ImageSpanView::SetPlaceHolderStyle(frameNode, font);
}

void ResetImageSpanTextBackgroundStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextBackgroundStyle font;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    font.backgroundColor = Color(0x00000000);
    font.backgroundRadius = borderRadius;
    font.backgroundRadius->multiValued = true;
    ImageSpanView::SetPlaceHolderStyle(frameNode, font);
}

void GetImageSpanTextBackgroundStyle(ArkUINodeHandle node, ArkUITextBackgroundStyleOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto styleOptions = ImageSpanView::GetSpanTextBackgroundStyle(frameNode);
    options->color = styleOptions.backgroundColor->GetValue();
    options->topLeft = styleOptions.backgroundRadius->radiusTopLeft->Value();
    options->topRight = styleOptions.backgroundRadius->radiusTopRight->Value();
    options->bottomLeft = styleOptions.backgroundRadius->radiusBottomLeft->Value();
    options->bottomLeft = styleOptions.backgroundRadius->radiusBottomLeft->Value();
}

void SetImageSpanBaselineOffset(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetBaselineOffset(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetImageSpanBaselineOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetBaselineOffset(frameNode, DEFAULT_BASELINE_OFFSET);
}

float GetImageSpanBaselineOffset(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return ImageSpanView::GetBaselineOffset(frameNode, unit);
}

void SetImageSpanOnComplete(ArkUINodeHandle node, void *callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onComplete = reinterpret_cast<std::function<void(const LoadImageSuccessEvent&)>*>(callback);
        ImageSpanView::SetOnComplete(frameNode, std::move(*onComplete));
    } else {
        ImageSpanView::SetOnComplete(frameNode, nullptr);
    }
}

void ResetImageSpanOnComplete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetOnComplete(frameNode, nullptr);
}

void SetImageSpanOnError(ArkUINodeHandle node, void *callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onError = reinterpret_cast<std::function<void(const LoadImageFailEvent&)>*>(callback);
        ImageSpanView::SetOnError(frameNode, std::move(*onError));
    } else {
        ImageSpanView::SetOnError(frameNode, nullptr);
    }
}

void ResetImageSpanOnError(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetOnError(frameNode, nullptr);
}

void SetImageSpanBorderRadius(ArkUINodeHandle node, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    borderRadius.multiValued = true;
    ImageSpanView::SetBorderRadius(frameNode, borderRadius);
}

void ResetImageSpanBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::ResetBorderRadius(frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUIImageSpanModifier* GetImageSpanModifier()
{
    static const ArkUIImageSpanModifier modifier = { SetImageSpanVerticalAlign, ResetImageSpanVerticalAlign,
        SetImageSpanObjectFit, ResetImageSpanObjectFit, GetImageSpanVerticalAlign, GetImageSpanObjectFit,
        SetImageSpanTextBackgroundStyle, ResetImageSpanTextBackgroundStyle, GetImageSpanTextBackgroundStyle,
        SetImageSpanBaselineOffset, ResetImageSpanBaselineOffset, SetImageSpanOnComplete, ResetImageSpanOnComplete,
        SetImageSpanOnError, ResetImageSpanOnError, SetImageSpanBorderRadius, ResetImageSpanBorderRadius,
        GetImageSpanBaselineOffset };
    return &modifier;
}

const CJUIImageSpanModifier* GetCJUIImageSpanModifier()
{
    static const CJUIImageSpanModifier modifier = { SetImageSpanVerticalAlign, ResetImageSpanVerticalAlign,
        SetImageSpanObjectFit, ResetImageSpanObjectFit, GetImageSpanVerticalAlign, GetImageSpanObjectFit,
        SetImageSpanTextBackgroundStyle, ResetImageSpanTextBackgroundStyle, GetImageSpanTextBackgroundStyle,
        SetImageSpanBaselineOffset, ResetImageSpanBaselineOffset, SetImageSpanOnComplete, ResetImageSpanOnComplete,
        SetImageSpanOnError, ResetImageSpanOnError };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG