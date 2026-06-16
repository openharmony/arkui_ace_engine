/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/text/span/bridge/image_span/image_span_custom_modifier.h"
#include "core/components_ng/pattern/text/span/image_span_view.h"
#include "core/components_ng/pattern/text/span/image_span_view_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int DEFAULT_LENGTH = 4;
constexpr uint32_t MAX_COLOR_FILTER_SIZE = 20;
constexpr VerticalAlign DEFAULT_VERTICAL_ALIGN = VerticalAlign::BOTTOM;
constexpr ImageFit DEFAULT_OBJECT_FIT = ImageFit::COVER;
constexpr Dimension DEFAULT_BASELINE_OFFSET { 0.0, DimensionUnit::FP };
const std::vector<float> DEFAULT_COLOR_FILTER = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
};

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetImageSpanVerticalAlign(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetVerticalAlign(frameNode, static_cast<VerticalAlign>(value));
}

int32_t GetImageSpanVerticalAlign(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, static_cast<int32_t>(DEFAULT_VERTICAL_ALIGN));
    return static_cast<int32_t>(ImageSpanView::GetVerticalAlign(frameNode));
}

void ResetImageSpanVerticalAlign(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetVerticalAlign(frameNode, DEFAULT_VERTICAL_ALIGN);
}

void SetImageSpanObjectFit(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, static_cast<ImageFit>(value));
}

int32_t GetImageSpanObjectFit(ArkUINodeHandle node)
{
    int32_t defaultObjectFit = static_cast<int32_t>(DEFAULT_OBJECT_FIT);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, defaultObjectFit);
    return static_cast<int32_t>(ImageModelNG::GetObjectFit(frameNode));
}

void ResetImageSpanObjectFit(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, DEFAULT_OBJECT_FIT);
}

void SetImageSpanTextBackgroundStyle(ArkUINodeHandle node, void* option)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto* parseOption = reinterpret_cast<TextBackgroundStyleParseOption*>(option);
    CHECK_NULL_VOID(parseOption);
    if (parseOption->radiusValues.size() != DEFAULT_LENGTH || parseOption->radiusUnits.size() != DEFAULT_LENGTH) {
        return;
    }
    if (SystemProperties::ConfigChangePerform() && parseOption->style) {
        ImageSpanView::SetPlaceHolderStyle(frameNode, *(parseOption->style));
        return;
    }
    TextBackgroundStyle font;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(
        parseOption->radiusValues[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(parseOption->radiusUnits[NUM_0]));
    borderRadius.radiusTopRight = Dimension(
        parseOption->radiusValues[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(parseOption->radiusUnits[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(
        parseOption->radiusValues[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(parseOption->radiusUnits[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(
        parseOption->radiusValues[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(parseOption->radiusUnits[NUM_3]));
    font.backgroundColor = parseOption->color;
    font.backgroundRadius = borderRadius;
    font.backgroundRadius->multiValued = true;
    ImageSpanView::SetPlaceHolderStyle(frameNode, font);
}

void ResetImageSpanTextBackgroundStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto styleOptions = ImageSpanView::GetSpanTextBackgroundStyle(frameNode);
    options->color = styleOptions.backgroundColor->GetValue();
    options->topLeft = styleOptions.backgroundRadius->radiusTopLeft->Value();
    options->topRight = styleOptions.backgroundRadius->radiusTopRight->Value();
    options->bottomLeft = styleOptions.backgroundRadius->radiusBottomLeft->Value();
    options->bottomRight = styleOptions.backgroundRadius->radiusBottomRight->Value();
}

void SetImageSpanBaselineOffset(
    ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_Bool isJsView, void* colorResObj)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetBaselineOffset(frameNode, CalcDimension(value, (DimensionUnit)unit));
    if (!isJsView) {
        return;
    }
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && colorResObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorResObj));
        pattern->RegisterResource<CalcDimension>("BaselineOffset", resObj,
            CalcDimension(value, (DimensionUnit)unit));
    } else {
        pattern->UnRegisterResource("BaselineOffset");
    }
}
void ResetImageSpanBaselineOffset(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetBaselineOffset(frameNode, DEFAULT_BASELINE_OFFSET);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("BaselineOffset");
    }
}

float GetImageSpanBaselineOffset(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return ImageSpanView::GetBaselineOffset(frameNode, unit);
}

void SetImageSpanOnComplete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetOnComplete(frameNode, nullptr);
}

void SetImageSpanOnError(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::ResetBorderRadius(frameNode);
}

void SetImageSpanColorFilter(ArkUINodeHandle node, const ArkUI_Float32* array, int length)
{
    CHECK_NULL_VOID(array);
    if (length != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, std::vector<float>(array, array + length));
}

void ResetImageSpanColorFilter(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, DEFAULT_COLOR_FILTER);
}

void SetImageSpanSrc(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName,
    ArkUI_Bool isUriPureNumber)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageSpanView::SetSrc(frameNode, src, bundleName, moduleName, isUriPureNumber);
}

struct NativeHandle {
    std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter> value = nullptr;
};

void SetImageSpanDrawingColorFilter(ArkUINodeHandle node, void* colorFilter)
{
    ViewAbstract::CheckMainThread();
    CHECK_NULL_VOID(colorFilter);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto handle = reinterpret_cast<NativeHandle*>(colorFilter);
    auto filterPtr = handle->value;
    CHECK_NULL_VOID(filterPtr);
    auto drawingColorFilter = DrawingColorFilter::CreateDrawingColorFilterFromNative(static_cast<void*>(&filterPtr));
    ImageModelNG::SetDrawingColorFilter(frameNode, drawingColorFilter);
}

void* GetImageSpanDrawingColorFilter(ArkUINodeHandle node)
{
    ViewAbstract::CheckMainThread();
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto drawingColorFilter = ImageModelNG::GetDrawingColorFilter(frameNode);
    CHECK_NULL_RETURN(drawingColorFilter, nullptr);
    auto filterSptr = reinterpret_cast<std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter>*>(
        drawingColorFilter->GetDrawingColorFilterSptrAddr());
    CHECK_NULL_RETURN(filterSptr, nullptr);
    return reinterpret_cast<void*>(filterSptr);
}

void SetSupportSvg2(ArkUINodeHandle node, ArkUI_Bool supportSvg2)
{
    ViewAbstract::CheckMainThread();
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSupportSvg2(frameNode, supportSvg2);
}

void ResetSupportSvg2(ArkUINodeHandle node)
{
    ViewAbstract::CheckMainThread();
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::ResetSupportSvg2(frameNode);
}

int32_t GetSupportSvg2(ArkUINodeHandle node)
{
    ViewAbstract::CheckMainThread();
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return ImageModelNG::GetSupportSvg2(frameNode);
}

void GetImageSpanColorFilter(ArkUINodeHandle node, ArkUIFilterColorType* colorFilter)
{
    ViewAbstract::CheckMainThread();
    CHECK_NULL_VOID(colorFilter);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto filterFloatArray = ImageModelNG::GetColorFilter(frameNode);
    colorFilter->filterSize = filterFloatArray.size() < MAX_COLOR_FILTER_SIZE
                                  ? static_cast<int32_t>(filterFloatArray.size())
                                  : static_cast<int32_t>(MAX_COLOR_FILTER_SIZE);
    for (size_t i = 0; i < static_cast<size_t>(colorFilter->filterSize) && i < MAX_COLOR_FILTER_SIZE; i++) {
        *(colorFilter->filterArray+i) = filterFloatArray[i];
    }
}
ArkUINodeHandle CreateImageSpanFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = ImageSpanView::CreateFrameNode(static_cast<int32_t>(nodeId));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void SetImageSpanPlaceHolderStyle(ArkUINodeHandle node, void* style)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto placeHolderStyle = reinterpret_cast<TextBackgroundStyle*>(style);
    ImageSpanView::SetPlaceHolderStyle(frameNode, *placeHolderStyle);
}

void CreateImageSpan()
{
    ImageSpanView::Create();
}


void SetStaticBaselineOffset(Ark_NativePointer node, const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonPercent(convValue);
    ImageSpanViewStatic::SetBaselineOffset(frameNode, convValue);
}

} // namespace

namespace NodeModifier {
const ArkUIImageSpanModifier* GetImageSpanDynamicModifier()
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
        .getImageSpanColorFilter = GetImageSpanColorFilter,
        .getImageSpanBaselineOffset = GetImageSpanBaselineOffset,
        .setImageSpanSrc = SetImageSpanSrc,
        .setImageSpanDrawingColorFilter = SetImageSpanDrawingColorFilter,
        .getImageSpanDrawingColorFilter = GetImageSpanDrawingColorFilter,
        .setSupportSvg2 = SetSupportSvg2,
        .resetSupportSvg2 = ResetSupportSvg2,
        .getSupportSvg2 = GetSupportSvg2,
        .createImageSpanFrameNode = CreateImageSpanFrameNode,
        .setImageSpanPlaceHolderStyle = SetImageSpanPlaceHolderStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIImageSpanModifier* GetCJUIImageSpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIImageSpanModifier modifier = {
        .createImageSpan = CreateImageSpan,
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
        .setImageSpanPlaceHolderStyle = SetImageSpanPlaceHolderStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIImageSpanCustomModifier* GetImageSpanCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIImageSpanCustomModifier modifier = {
        .setStaticBaselineOffset = SetStaticBaselineOffset,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
