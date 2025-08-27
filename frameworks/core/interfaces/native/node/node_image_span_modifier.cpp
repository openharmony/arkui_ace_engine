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

#include "core/components/image/image_component.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/image_span_view.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int DEFAULT_LENGTH = 4;
constexpr int32_t LOAD_ERROR_CODE = 401;
constexpr int32_t IMAGE_LOAD_STATUS_INDEX = 0;
constexpr int32_t IMAGE_WIDTH_INDEX = 1;
constexpr int32_t IMAGE_HEIGHT_INDEX = 2;
constexpr int32_t IMAGE_COMPONENT_WIDTH_INDEX = 3;
constexpr int32_t IMAGE_COMPONENT_HEIGHT_INDEX = 4;
constexpr int32_t IMAGE_CONTENT_OFFSET_X_INDEX = 5;
constexpr int32_t IMAGE_CONTENT_OFFSET_Y_INDEX = 6;
constexpr int32_t IMAGE_CONTENT_WIDTH_INDEX = 7;
constexpr int32_t IMAGE_CONTENT_HEIGHT_INDEX = 8;
constexpr VerticalAlign DEFAULT_VERTICAL_ALIGN = VerticalAlign::BOTTOM;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;
constexpr Dimension DEFAULT_BASELINE_OFFSET { 0.0, DimensionUnit::FP };
const std::vector<float> DEFAULT_COLOR_FILTER = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

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
    ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length,
    void* style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    if (SystemProperties::ConfigChangePerform() && style) {
        auto textBackgroundStyle = reinterpret_cast<TextBackgroundStyle*>(style);
        ImageSpanView::SetPlaceHolderStyle(frameNode, *textBackgroundStyle);
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
    options->bottomRight = styleOptions.backgroundRadius->radiusBottomRight->Value();
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

/**
 * @param values radius values
 * value[0] : radius value for TopLeft，value[1] : radius value for TopRight
 * value[2] : radius value for BottomLeft，value[3] : radius value for BottomRight
 * @param units radius units
 * units[0]: radius unit for TopLeft ,units[1] : radius unit for TopRight
 * units[2]: radius unit for BottomLeft, units[3] : radius unit for TopRight
 */
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

void SetImageSpanColorFilter(ArkUINodeHandle node, const ArkUI_Float32* array, int length)
{
    CHECK_NULL_VOID(array);
    if (length != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, std::vector<float>(array, array + length));
}

void ResetImageSpanColorFilter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, DEFAULT_COLOR_FILTER);
}

void SetImageSpanSrc(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName,
    ArkUI_Bool isUriPureNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetSrc(frameNode, src, bundleName, moduleName, isUriPureNumber);
}
} // namespace

namespace NodeModifier {
const ArkUIImageSpanModifier* GetImageSpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIImageSpanModifier modifier = {
        .setImageSpanVerticalAlign = SetImageSpanVerticalAlign,
        .resetImageSpanVerticalAlign = ResetImageSpanVerticalAlign,
        .setImageSpanObjectFit = SetImageSpanObjectFit,
        .resetImageSpanObjectFit = ResetImageSpanObjectFit,
        .getImageSpanVerticalAlign = GetImageSpanVerticalAlign,
        .getImageSpanObjectFit = GetImageSpanObjectFit,
        .setImageSpanTextBackgroundStyle = SetImageSpanTextBackgroundStyle,
        .resetImageSpanTextBackgroundStyle = ResetImageSpanTextBackgroundStyle,
        .getImageSpanTextBackgroundStyle = GetImageSpanTextBackgroundStyle,
        .setImageSpanBaselineOffset = SetImageSpanBaselineOffset,
        .resetImageSpanBaselineOffset = ResetImageSpanBaselineOffset,
        .setImageSpanOnComplete = SetImageSpanOnComplete,
        .resetImageSpanOnComplete = ResetImageSpanOnComplete,
        .setImageSpanOnError = SetImageSpanOnError,
        .resetImageSpanOnError = ResetImageSpanOnError,
        .setImageSpanBorderRadius = SetImageSpanBorderRadius,
        .resetImageSpanBorderRadius = ResetImageSpanBorderRadius,
        .setImageSpanColorFilter = SetImageSpanColorFilter,
        .resetImageSpanColorFilter = ResetImageSpanColorFilter,
        .getImageSpanBaselineOffset = GetImageSpanBaselineOffset,
        .setImageSpanSrc = SetImageSpanSrc,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIImageSpanModifier* GetCJUIImageSpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIImageSpanModifier modifier = {
        .setImageSpanVerticalAlign = SetImageSpanVerticalAlign,
        .resetImageSpanVerticalAlign = ResetImageSpanVerticalAlign,
        .setImageSpanObjectFit = SetImageSpanObjectFit,
        .resetImageSpanObjectFit = ResetImageSpanObjectFit,
        .getImageSpanVerticalAlign = GetImageSpanVerticalAlign,
        .getImageSpanObjectFit = GetImageSpanObjectFit,
        .setImageSpanTextBackgroundStyle = SetImageSpanTextBackgroundStyle,
        .resetImageSpanTextBackgroundStyle = ResetImageSpanTextBackgroundStyle,
        .getImageSpanTextBackgroundStyle = GetImageSpanTextBackgroundStyle,
        .setImageSpanBaselineOffset = SetImageSpanBaselineOffset,
        .resetImageSpanBaselineOffset = ResetImageSpanBaselineOffset,
        .setImageSpanOnComplete = SetImageSpanOnComplete,
        .resetImageSpanOnComplete = ResetImageSpanOnComplete,
        .setImageSpanOnError = SetImageSpanOnError,
        .resetImageSpanOnError = ResetImageSpanOnError,
        .setImageSpanSrc = SetImageSpanSrc,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

void SetImageSpanOnCompleteEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const LoadImageSuccessEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_SPAN_COMPLETE;
        event.componentAsyncEvent.data[IMAGE_LOAD_STATUS_INDEX].i32 = info.GetLoadingStatus();
        event.componentAsyncEvent.data[IMAGE_WIDTH_INDEX].f32 = info.GetWidth();
        event.componentAsyncEvent.data[IMAGE_HEIGHT_INDEX].f32 = info.GetHeight();
        event.componentAsyncEvent.data[IMAGE_COMPONENT_WIDTH_INDEX].f32 = info.GetComponentWidth();
        event.componentAsyncEvent.data[IMAGE_COMPONENT_HEIGHT_INDEX].f32 = info.GetComponentHeight();
        event.componentAsyncEvent.data[IMAGE_CONTENT_OFFSET_X_INDEX].f32 = info.GetContentOffsetX();
        event.componentAsyncEvent.data[IMAGE_CONTENT_OFFSET_Y_INDEX].f32 = info.GetContentOffsetY();
        event.componentAsyncEvent.data[IMAGE_CONTENT_WIDTH_INDEX].f32 = info.GetContentWidth();
        event.componentAsyncEvent.data[IMAGE_CONTENT_HEIGHT_INDEX].f32 = info.GetContentHeight();
        SendArkUISyncEvent(&event);
    };
    ImageSpanView::SetOnComplete(frameNode, std::move(onEvent));
}

void SetImageSpanOnErrorEvent(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const LoadImageFailEvent& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_SPAN_ERROR;
        event.componentAsyncEvent.data[0].i32 = LOAD_ERROR_CODE;
        SendArkUISyncEvent(&event);
    };
    ImageSpanView::SetOnError(frameNode, std::move(onEvent));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
