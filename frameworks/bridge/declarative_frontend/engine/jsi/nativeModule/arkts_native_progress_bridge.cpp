/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_progress_bridge.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_progress.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"

namespace OHOS::Ace::NG {
constexpr int32_t ARG_NUM_NATIVE_NODE = 0;
constexpr int32_t ARG_NUM_VALUE = 1;
constexpr int32_t ARG_COLOR_INDEX_VALUE = 1;
constexpr int32_t ARG_NUM_STYLE_STROKE_WIDTH = 1;
constexpr int32_t ARG_NUM_STYLE_BORDER_WIDTH = 6;
constexpr int32_t ARG_NUM_STYLE_PROGRESS_STATUS = 16;
constexpr int32_t ARG_NUM_STYLE_FONT_STYLE = 11;
constexpr int32_t ARG_NUM_STYLE_SCALE_COUNT = 2;
constexpr int32_t ARG_NUM_STYLE_SCALE_WIDTH = 3;
constexpr int32_t ARG_NUM_STYLE_FONT_SIZE = 8;
constexpr int32_t ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT = 4;
constexpr int32_t ARG_NUM_STYLE_BORDER_COLOR = 5;
constexpr int32_t ARG_NUM_STYLE_CONTENT = 7;
constexpr int32_t ARG_NUM_STYLE_FONT_WEIGHT = 9;
constexpr int32_t ARG_NUM_STYLE_FONT_COLOR = 12;
constexpr int32_t ARG_NUM_STYLE_ENABLE_SCAN_EFFECT = 13;
constexpr int32_t ARG_NUM_STYLE_SHADOW = 15;
constexpr int32_t ARG_NUM_STYLE_SHOW_DEFAULT_PERCENTAGE = 14;
constexpr int32_t ARG_NUM_STYLE_FONT_FAMILY = 10;
constexpr int32_t ARG_NUM_STYLE_STROKE_RADIUS = 17;
constexpr int32_t ARG_NUM_STYLE_BORDER_RADIUS = 18;
constexpr int32_t ARG_SECOND = 2;
const char* PROGRESS_NODEPTR_OF_UINODE = "nodePtr_";
constexpr double DEFAULT_PROGRESS_VALUE = 0;
constexpr double DEFAULT_STROKE_WIDTH = 4;
constexpr double DEFAULT_BORDER_WIDTH = 1;
constexpr double DEFAULT_SCALE_WIDTH = 2;
constexpr double DEFAULT_STROKE_RADIUS = 0;
constexpr int32_t DEFAULT_SCALE_COUNT = 120;
constexpr Color DEFAULT_BORDER_COLOR = Color(0x33006cde);
constexpr Color DEFAULT_FONT_COLOR = Color(0xff182431);
constexpr double DEFAULT_CAPSULE_FONT_SIZE = 12;
constexpr NG::ProgressStatus DEFAULT_PROGRESS_STATUS = NG::ProgressStatus::PROGRESSING;
constexpr DimensionUnit DEFAULT_CAPSULE_FONT_UNIT = DimensionUnit::FP;
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<NG::ProgressStatus> STATUS_STYLES = { NG::ProgressStatus::PROGRESSING, NG::ProgressStatus::LOADING };
constexpr double DEFAULT_BORDER_RADIUS = 0;

namespace {
bool ConvertProgressRResourceColor(const EcmaVM* vm, const Local<JSValueRef>& item, OHOS::Ace::NG::Gradient& gradient)
{
    Color color;
    if (!ArkTSUtils::ParseJsColor(vm, item, color)) {
        return false;
    }
    OHOS::Ace::NG::GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor(color));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(color));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    return true;
}

bool ConvertProgressResourceColor(
    const EcmaVM* vm, const Local<JSValueRef>& itemParam, OHOS::Ace::NG::Gradient& gradient)
{
    if (!itemParam->IsObject(vm)) {
        return ConvertProgressRResourceColor(vm, itemParam, gradient);
    }
    Framework::JSLinearGradient* jsLinearGradient =
        static_cast<Framework::JSLinearGradient*>(itemParam->ToObject(vm)->GetNativePointerField(vm, 0));
    if (!jsLinearGradient) {
        return ConvertProgressRResourceColor(vm, itemParam, gradient);
    }

    size_t colorLength = jsLinearGradient->GetGradient().size();
    if (colorLength == 0) {
        return false;
    }
    for (size_t colorIndex = 0; colorIndex < colorLength; ++colorIndex) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}
} // namespace

ArkUINativeModuleValue ProgressBridge::ResetProgressValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressValue(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_VALUE);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        ArkUI_Float32 value = secondArg->ToNumber(vm)->Value();
        if (value < DEFAULT_PROGRESS_VALUE) {
            value = DEFAULT_PROGRESS_VALUE;
        }
        nodeModifiers->getProgressModifier()->setProgressValue(nativeNode, value);
    } else {
        nodeModifiers->getProgressModifier()->resetProgressValue(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(ARG_COLOR_INDEX_VALUE);
    auto nativeNode = nodePtr(nativeArg->ToNativePointer(vm)->Value());
    Color color;
    OHOS::Ace::NG::Gradient gradient;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        nodeModifiers->getProgressModifier()->setProgressColor(nativeNode, color.GetValue());
    } else if (ConvertProgressResourceColor(vm, colorArg, gradient)) {
        ArkUIGradientType gradientObj;
        auto colorlength = gradient.GetColors().size();
        std::vector<uint32_t> colorValues;
        std::vector<ArkUILengthType> offsetValues;
        if (colorlength <= 0) {
            nodeModifiers->getProgressModifier()->resetProgressColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }

        for (int32_t i = 0; i < static_cast<int32_t>(colorlength); i++) {
            colorValues.push_back(gradient.GetColors()[i].GetLinearColor().GetValue());
            offsetValues.push_back(ArkUILengthType { .number = gradient.GetColors()[i].GetDimension().Value(),
                .unit = static_cast<int8_t>(gradient.GetColors()[i].GetDimension().Unit()) });
        }

        gradientObj.color = &(*colorValues.begin());
        gradientObj.offset = &(*offsetValues.begin());
        nodeModifiers->getProgressModifier()->setProgressGradientColor(
            nativeNode, &gradientObj, colorlength);
    } else {
        nodeModifiers->getProgressModifier()->resetProgressColor(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseStrokeWidth(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension strokeWidth = CalcDimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP);
    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();

    if (strokeWidthArg->IsString(vm)) {
        const std::string& value = strokeWidthArg->ToString(vm)->ToString(vm);
        strokeWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, DEFAULT_STROKE_WIDTH);
    } else {
        ArkTSUtils::ParseJsDimension(vm, strokeWidthArg, strokeWidth, DimensionUnit::VP, false);
    }

    if ((LessOrEqual(strokeWidth.Value(), 0.0f) || strokeWidth.Unit() == DimensionUnit::PERCENT) && theme) {
        strokeWidth = theme->GetTrackThickness();
    }
    if (strokeWidth.IsNegative()) {
        progressStyle.strokeWidthValue = DEFAULT_STROKE_WIDTH;
        progressStyle.strokeWidthUnit = static_cast<uint8_t>(DimensionUnit::VP);
    } else {
        progressStyle.strokeWidthValue = strokeWidth.Value();
        progressStyle.strokeWidthUnit = static_cast<uint8_t>(strokeWidth.Unit());
    }
}

void ParseBorderWidth(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> borderWidthArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension borderWidth = CalcDimension(DEFAULT_BORDER_WIDTH, DimensionUnit::VP);

    if (borderWidthArg->IsString(vm)) {
        const std::string& value = borderWidthArg->ToString(vm)->ToString(vm);
        borderWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, DEFAULT_BORDER_WIDTH);
    } else {
        ArkTSUtils::ParseJsDimension(vm, borderWidthArg, borderWidth, DimensionUnit::VP, false);
    }
    if (borderWidth.IsNegative()) {
        progressStyle.borderWidthValue = DEFAULT_BORDER_WIDTH;
        progressStyle.borderWidthUnit = static_cast<uint8_t>(DimensionUnit::VP);
    } else {
        progressStyle.borderWidthValue = borderWidth.Value();
        progressStyle.borderWidthUnit = static_cast<uint8_t>(borderWidth.Unit());
    }
}

void ParseScaleCount(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> scaleCountArg = runtimeCallInfo->GetCallArgRef(index);
    int32_t scaleCount = DEFAULT_SCALE_COUNT;
    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();
    if (theme) {
        scaleCount = theme->GetScaleNumber();
    }

    if (scaleCountArg->IsNull() || !ArkTSUtils::ParseJsInteger(vm, scaleCountArg, scaleCount)) {
        scaleCount = DEFAULT_SCALE_COUNT;
    }
    if (scaleCount > 1) {
        progressStyle.scaleCount = scaleCount;
    } else if (theme) {
        progressStyle.scaleCount = theme->GetScaleNumber();
    }
}

void ParseProgressStatus(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> ProgressStatusArg = runtimeCallInfo->GetCallArgRef(index);
    NG::ProgressStatus progressStatus = DEFAULT_PROGRESS_STATUS;
    std::string statusStr;
    if (ProgressStatusArg->IsUndefined() || ProgressStatusArg->IsNull() ||
        !ArkTSUtils::ParseJsString(vm, ProgressStatusArg, statusStr)) {
        progressStatus = DEFAULT_PROGRESS_STATUS;
    } else {
        if (statusStr.compare("LOADING") == 0) {
            progressStatus = NG::ProgressStatus::LOADING;
        } else {
            progressStatus = NG::ProgressStatus::PROGRESSING;
        }
    }
    progressStyle.status = static_cast<int8_t>(progressStatus);
}

void ParseScaleWidth(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> scaleWidthArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension scaleWidth = CalcDimension(DEFAULT_SCALE_WIDTH, DimensionUnit::VP);

    if (scaleWidthArg->IsString(vm)) {
        const std::string& value = scaleWidthArg->ToString(vm)->ToString(vm);
        scaleWidth = StringUtils::StringToDimensionWithUnit(value, DimensionUnit::VP, DEFAULT_SCALE_WIDTH);
    } else {
        ArkTSUtils::ParseJsDimension(vm, scaleWidthArg, scaleWidth, DimensionUnit::VP, false);
    }
    if (scaleWidth.IsNegative()) {
        scaleWidth = CalcDimension(DEFAULT_SCALE_WIDTH, DimensionUnit::VP);
    }

    progressStyle.scaleWidthValue = scaleWidth.Value();
    progressStyle.scaleWidthUnit = static_cast<uint8_t>(scaleWidth.Unit());
}

void ParseStrokeRadius(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> strokeRadiusArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension strokeRadius = CalcDimension(DEFAULT_STROKE_RADIUS, DimensionUnit::PERCENT);
    if (strokeRadiusArg->IsNull() ||
        !ArkTSUtils::ParseJsDimension(vm, strokeRadiusArg, strokeRadius, DimensionUnit::VP, true)) {
        strokeRadius.SetUnit(DimensionUnit::PERCENT);
    }

    progressStyle.strokeRadiusValue = strokeRadius.Value();
    progressStyle.strokeRadiusUnit = static_cast<uint8_t>(strokeRadius.Unit());
}

void ParseBorderColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> borderColorArg = runtimeCallInfo->GetCallArgRef(index);
    Color borderColor = DEFAULT_BORDER_COLOR;

    if (borderColorArg->IsNull() || !ArkTSUtils::ParseJsColorAlpha(vm, borderColorArg, borderColor)) {
        borderColor = DEFAULT_BORDER_COLOR;
    }

    progressStyle.borderColor = borderColor.GetValue();
}

void ParseFontColor(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> fontColorArg = runtimeCallInfo->GetCallArgRef(index);
    Color fontColor = DEFAULT_FONT_COLOR;

    if (fontColorArg->IsNull() || !ArkTSUtils::ParseJsColorAlpha(vm, fontColorArg, fontColor)) {
        fontColor = DEFAULT_FONT_COLOR;
    }

    progressStyle.fontColor = fontColor.GetValue();
}

void ParseEnableSmoothEffect(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> enableSmoothEffectArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.enableSmoothEffect =
        (enableSmoothEffectArg->IsBoolean()) ? enableSmoothEffectArg->ToBoolean(vm)->Value() : true;
}

void ParseContent(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> contentArg = runtimeCallInfo->GetCallArgRef(index);
    std::string content = contentArg->ToString(vm)->ToString(vm);
    progressStyle.content = (contentArg->IsString(vm)) ? content.c_str() : nullptr;
}

void ParseEnableScanEffect(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> enableScanEffectArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.enableScanEffect =
        (enableScanEffectArg->IsBoolean()) ? enableScanEffectArg->ToBoolean(vm)->Value() : false;
}

void ParseShadow(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> shadowArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.shadow = (shadowArg->IsBoolean()) ? shadowArg->ToBoolean(vm)->Value() : false;
}

void ParseShowDefaultPercentage(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> showDefaultPercentageArg = runtimeCallInfo->GetCallArgRef(index);
    progressStyle.showDefaultPercentage =
        (showDefaultPercentageArg->IsBoolean()) ? showDefaultPercentageArg->ToBoolean(vm)->Value() : false;
}

void ParseCapsuleFontSize(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(index);

    CalcDimension fontSize;
    if (sizeArg->IsNull() || !ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize) || fontSize.IsNegative() ||
        fontSize.Unit() == DimensionUnit::PERCENT) {
        progressStyle.fontInfo.fontSizeNumber = DEFAULT_CAPSULE_FONT_SIZE;
        progressStyle.fontInfo.fontSizeUnit = static_cast<int8_t>(DEFAULT_CAPSULE_FONT_UNIT);
    } else {
        progressStyle.fontInfo.fontSizeNumber = fontSize.Value();
        progressStyle.fontInfo.fontSizeUnit = static_cast<int8_t>(fontSize.Unit());
    }
}

void ParseCapsuleFontWeight(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(index);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();

    std::string weight;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else if (weightArg->IsString(vm)) {
            weight = weightArg->ToString(vm)->ToString(vm);
        }
        progressStyle.fontInfo.fontWeight = static_cast<uint8_t>(Framework::ConvertStrToFontWeight(weight));
    } else {
        progressStyle.fontInfo.fontWeight = static_cast<uint8_t>(theme->GetTextStyle().GetFontWeight());
    }
}

void ParseCapsuleFontStyle(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(index);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();

    uint8_t style = static_cast<uint8_t>(theme->GetTextStyle().GetFontStyle());
    if (!styleArg->IsNull() && styleArg->IsInt()) {
        style = static_cast<uint8_t>(styleArg->Int32Value(vm));
        if (style <= 0 || style > static_cast<uint8_t>(FONT_STYLES.size())) {
            style = static_cast<uint8_t>(theme->GetTextStyle().GetFontStyle());
        }
    }

    progressStyle.fontInfo.fontStyle = style;
}

void ParseCapsuleFontFamily(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(index);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();

    std::vector<std::string> fontFamilies;
    if (familyArg->IsNull() || !ArkTSUtils::ParseJsFontFamilies(vm, familyArg, fontFamilies)) {
        fontFamilies = theme->GetTextStyle().GetFontFamilies();
    }

    auto families = std::make_unique<const char* []>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = fontFamilies[i].c_str();
    }

    progressStyle.fontInfo.fontFamilies = families.get();
    progressStyle.fontInfo.familyLength = fontFamilies.size();
}

void ParseBorderRadius(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> borderRadiusArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension borderRadius = CalcDimension(DEFAULT_BORDER_RADIUS, DimensionUnit::PERCENT);
    if (borderRadiusArg->IsNull() || !ArkTSUtils::ParseJsLengthMetrics(vm, borderRadiusArg, borderRadius)) {
        // Set illegal units, and the background will be handled according to the default value.
        borderRadius.SetUnit(DimensionUnit::PERCENT);
    }
    progressStyle.borderRadiusValue = borderRadius.Value();
    progressStyle.borderRadiusUnit = static_cast<uint8_t>(borderRadius.Unit());
}

void ParseLinearStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDTH);
    ParseStrokeRadius(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_RADIUS);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

void ParseRingStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDTH);
    ParseShadow(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SHADOW);
    ParseProgressStatus(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_PROGRESS_STATUS);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

void ParseCapsuleStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    ParseBorderColor(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_COLOR);
    ParseBorderWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_WIDTH);
    ParseFontColor(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_COLOR);
    ParseCapsuleFontSize(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_SIZE);
    ParseCapsuleFontWeight(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_WEIGHT);
    ParseCapsuleFontStyle(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_STYLE);
    ParseCapsuleFontFamily(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_FAMILY);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseShowDefaultPercentage(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SHOW_DEFAULT_PERCENTAGE);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
    ParseBorderRadius(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_RADIUS);
}

void ParseProgressStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    auto progressTheme = ArkTSUtils::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDTH);
    ParseScaleCount(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SCALE_COUNT);
    ParseScaleWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SCALE_WIDTH);
    if ((progressStyle.scaleWidthValue <= 0.0) || (progressStyle.scaleWidthValue > progressStyle.strokeWidthValue) ||
        progressStyle.scaleWidthUnit == static_cast<int8_t>(DimensionUnit::PERCENT)) {
        progressStyle.scaleWidthValue = progressTheme->GetScaleWidth().Value();
        progressStyle.scaleWidthUnit = static_cast<int8_t>(progressTheme->GetScaleWidth().Unit());
    }
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

ArkUINativeModuleValue ProgressBridge::SetProgressStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<TextTheme>();

    auto fontFamilies = theme->GetTextStyle().GetFontFamilies();
    auto families = std::make_unique<const char* []>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = fontFamilies[i].c_str();
    }

    ArkUIProgressStyle progressStyle = { DEFAULT_STROKE_WIDTH, static_cast<int8_t>(DimensionUnit::VP),
        DEFAULT_BORDER_WIDTH, static_cast<int8_t>(DimensionUnit::VP), DEFAULT_SCALE_COUNT,
        static_cast<uint8_t>(DEFAULT_PROGRESS_STATUS), DEFAULT_SCALE_WIDTH, static_cast<int8_t>(DimensionUnit::VP),
        DEFAULT_STROKE_RADIUS, static_cast<int8_t>(DimensionUnit::PERCENT), true,
        static_cast<double>(DEFAULT_BORDER_COLOR.GetValue()), nullptr,
        static_cast<double>(DEFAULT_FONT_COLOR.GetValue()), false, false, false,
        { DEFAULT_CAPSULE_FONT_SIZE, static_cast<int8_t>(DEFAULT_CAPSULE_FONT_UNIT),
            static_cast<uint8_t>(theme->GetTextStyle().GetFontWeight()),
            static_cast<uint8_t>(theme->GetTextStyle().GetFontStyle()), families.get(), fontFamilies.size() } };

    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto progressLayoutProperty = frameNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_RETURN(progressLayoutProperty, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> contentArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_STYLE_CONTENT);
    std::string content = contentArg->ToString(vm)->ToString(vm);
    auto progresstype = progressLayoutProperty->GetType();
    if (progresstype == ProgressType::LINEAR) {
        ParseLinearStyle(vm, runtimeCallInfo, progressStyle);
    } else if (progresstype == ProgressType::RING) {
        ParseRingStyle(vm, runtimeCallInfo, progressStyle);
    } else if (progresstype == ProgressType::CAPSULE) {
        ParseCapsuleStyle(vm, runtimeCallInfo, progressStyle);
        progressStyle.content = (contentArg->IsString(vm)) ? content.c_str() : nullptr;
    } else {
        ParseProgressStyle(vm, runtimeCallInfo, progressStyle);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->setProgressStyle(nativeNode, &progressStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    Color color;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        nodeModifiers->getProgressModifier()->resetProgressBackgroundColor(nativeNode);
    } else {
        nodeModifiers->getProgressModifier()->setProgressBackgroundColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        ProgressModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    ProgressModelNG::SetBuilderFunc(frameNode, [vm, frameNode, obj = std::move(obj),
        containerId = Container::CurrentId()](ProgressConfiguration config) -> RefPtr<FrameNode> {
        ContainerScope scope(containerId);
        auto context = ArkTSUtils::GetContext(vm);
        CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
        const char* keysOfProgress[] = { "value", "total", "enabled"};
        Local<JSValueRef> valuesOfProgress[] = { panda::NumberRef::New(vm, config.value_),
            panda::NumberRef::New(vm, config.total_), panda::BooleanRef::New(vm, config.enabled_)};
        auto progress = panda::ObjectRef::NewWithNamedProperties(vm,
            ArraySize(keysOfProgress), keysOfProgress, valuesOfProgress);
        progress->SetNativePointerFieldCount(vm, 1);
        progress->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
        panda::Local<panda::JSValueRef> params[ARG_SECOND] = { context, progress };
        LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto jsObject = obj.ToLocal();
        auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
        CHECK_NULL_RETURN(makeFunc->IsFunction(vm), nullptr);
        panda::Local<panda::FunctionRef> func = makeFunc;
        auto result = func->Call(vm, jsObject, params, 2);
        JSNApi::ExecutePendingJob(vm);
        if (result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm)) {
            return nullptr;
        }
        auto resultObj = result->ToObject(vm);
        panda::Local<panda::JSValueRef> nodeptr = resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm,
            PROGRESS_NODEPTR_OF_UINODE));
        if (nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull()) {
            return nullptr;
        }
        auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
        CHECK_NULL_RETURN(frameNode, nullptr);
        return AceType::Claim(frameNode);
    });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->resetProgressInitialize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> totalArg = runtimeCallInfo->GetCallArgRef(2);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(3);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(4);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto value = 0;
    if (valueArg->IsNumber()) {
        value = valueArg->ToNumber(vm)->Value();
    }
    auto total = 100;
    if (totalArg->IsNumber() && totalArg->ToNumber(vm)->Value() > 0) {
        total = totalArg->Int32Value(vm);
    }
    if (value > total) {
        value = total;
    } else if (value < 0) {
        value = 0;
    }
    auto type = 0;
    if (styleArg->IsNull() || styleArg->IsUndefined()) {
        if (typeArg->IsNumber()) {
            type = typeArg->Int32Value(vm);
        }
    } else if (styleArg->IsNumber()) {
        type = styleArg->Int32Value(vm);
    }
    auto progressStyle = static_cast<Framework::ProgressStyle>(type);
    ProgressType g_progressType = NG::ProgressType::LINEAR;
    if (progressStyle == Framework::ProgressStyle::Eclipse) {
        g_progressType = NG::ProgressType::MOON;
    } else if (progressStyle == Framework::ProgressStyle::Ring) {
        g_progressType = NG::ProgressType::RING;
    } else if (progressStyle == Framework::ProgressStyle::ScaleRing) {
        g_progressType = NG::ProgressType::SCALE;
    } else if (progressStyle == Framework::ProgressStyle::Capsule) {
        g_progressType = NG::ProgressType::CAPSULE;
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getProgressModifier()->setProgressInitialize(
        nativeNode, value, total, static_cast<int>(g_progressType));
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
