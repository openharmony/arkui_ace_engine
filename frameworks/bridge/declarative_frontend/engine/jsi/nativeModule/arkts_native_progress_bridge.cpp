

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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_progress_bridge.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int32_t ARG_NUM_NATIVE_NODE = 0;
constexpr int32_t ARG_NUM_VALUE = 1;
constexpr int32_t ARG_NUM_COLOR_RESOURCE_COLOR = 1;
constexpr int32_t ARG_NUM_COLOR_ANGLE = 1;
constexpr int32_t ARG_NUM_COLOR_DIRECTION = 2;
constexpr int32_t ARG_NUM_COLOR_COLOR_STOPS = 3;
constexpr int32_t ARG_NUM_COLOR_REPEATING = 4;
constexpr int32_t ARG_NUM_STYLE_STROKE_WIDHT = 1;
constexpr int32_t ARG_NUM_STYLE_BORDER_WIDHT = 6;
constexpr int32_t ARG_NUM_STYLE_PROGRESS_STATUS = 16;
constexpr int32_t ARG_NUM_STYLE_FONT_STYLE = 11;
constexpr int32_t ARG_NUM_STYLE_SCALE_COUNT = 2;
constexpr int32_t ARG_NUM_STYLE_SCALE_WIDHT = 3;
constexpr int32_t ARG_NUM_STYLE_FONT_SIZE = 8;
constexpr int32_t ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT = 4;
constexpr int32_t ARG_NUM_STYLE_BORDER_COLOR = 5;
constexpr int32_t ARG_NUM_STYLE_CONTENT = 7;
constexpr int32_t ARG_NUM_STYLE_FONT_WEIGHT = 9;
constexpr int32_t ARG_NUM_STYLE_FONT_COLOR = 12;
constexpr int32_t ARG_NUM_STYLE_ENABLE_SCAN_EFFECT = 13;
constexpr int32_t ARG_NUM_STYLE_SHADOW = 15;
constexpr int32_t ARG_NUM_STYLE_SHOW_DEFAULT_PERCENTAHE = 14;
constexpr int32_t ARG_NUM_STYLE_FONT_FAMILY = 10;
constexpr int32_t ARG_NUM_STYLE_STROKE_RADIUS = 17;
constexpr int32_t COLOR_STOPS_MIN_LENGTH = 1;
constexpr int32_t ARRAY_MIN_INDEX = 0;
constexpr double DEFAULT_PROGRESS_VALUE = 0;
constexpr double DEFAULT_COLOR_STOPS_DIMENSION = 0;
constexpr double DEFAULT_GRADIENT_ANGLE = 0;
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

ArkUINativeModuleValue ProgressBridge::ResetProgressValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetProgressModifier().ResetProgressValue(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_VALUE);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsNumber()) {
        double value = secondArg->ToNumber(vm)->Value();
        if (value < DEFAULT_PROGRESS_VALUE) {
            value = DEFAULT_PROGRESS_VALUE;
        }
        GetArkUIInternalNodeAPI()->GetProgressModifier().SetProgressValue(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetProgressModifier().ResetProgressValue(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetProgressModifier().ResetProgressColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseGradientColorStops(const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<double>& colors)
{
    if (!value->IsArray(vm)) {
        return;
    }
    auto array = panda::Local<panda::ArrayRef>(value);
    auto length = array->Length(vm);
    for (uint32_t index = 0; index < length; index++) {
        auto item = panda::ArrayRef::GetValueAt(vm, array, index);
        if (!item->IsArray(vm)) {
            continue;
        }
        auto itemArray = panda::Local<panda::ArrayRef>(item);
        auto itemLength = itemArray->Length(vm);
        if (itemLength < COLOR_STOPS_MIN_LENGTH) {
            continue;
        }
        Color color;
        auto colorParams = panda::ArrayRef::GetValueAt(vm, itemArray, ARRAY_MIN_INDEX);
        if (!ArkTSUtils::ParseJsColorAlpha(vm, colorParams, color)) {
            continue;
        }
        bool hasDimension = false;
        double dimension = DEFAULT_COLOR_STOPS_DIMENSION;
        if (itemLength > COLOR_STOPS_MIN_LENGTH) {
            auto stopDimension = panda::ArrayRef::GetValueAt(vm, itemArray, COLOR_STOPS_MIN_LENGTH);
            if (ArkTSUtils::ParseJsDouble(vm, stopDimension, dimension)) {
                hasDimension = true;
            }
        }
        colors.push_back(static_cast<double>(color.GetValue()));
        colors.push_back(static_cast<double>(hasDimension));
        colors.push_back(dimension);
    }
}

bool ParseJsInt32(const EcmaVM* vm, const Local<JSValueRef>& value, int32_t& result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToInt(value->ToString(vm)->ToString());
        return true;
    }

    return false;
}

void ParseJsAngle(const EcmaVM* vm, const Local<JSValueRef>& value, std::optional<float>& angle)
{
    if (value->IsNumber()) {
        angle = static_cast<float>(value->ToNumber(vm)->Value());
        return;
    }
    if (value->IsString()) {
        angle = static_cast<float>(StringUtils::StringToDegree(value->ToString(vm)->ToString()));
        return;
    }
    return;
}

void ParseGradientAngle(const EcmaVM* vm, const Local<JSValueRef>& value, std::vector<double>& values)
{
    std::optional<float> degree;
    ParseJsAngle(vm, value, degree);
    auto angleHasValue = degree.has_value();
    auto angleValue = angleHasValue ? degree.value() : DEFAULT_GRADIENT_ANGLE;
    degree.reset();
    values.push_back(static_cast<double>(angleHasValue));
    values.push_back(static_cast<double>(angleValue));
}

ArkUINativeModuleValue ProgressBridge::SetProgressColorWithLinearGradient(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    Local<JSValueRef> angleArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_COLOR_ANGLE);
    Local<JSValueRef> directionArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_COLOR_DIRECTION);
    Local<JSValueRef> colorsArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_COLOR_COLOR_STOPS);
    Local<JSValueRef> repeatingArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_COLOR_REPEATING);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    std::vector<double> values;
    ParseGradientAngle(vm, angleArg, values);
    int32_t direction = static_cast<int32_t>(GradientDirection::NONE);
    ParseJsInt32(vm, directionArg, direction);
    values.push_back(static_cast<double>(direction));
    auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue() : false;
    values.push_back(static_cast<double>(repeating));

    std::vector<double> colors;
    ParseGradientColorStops(vm, colorsArg, colors);
    GetArkUIInternalNodeAPI()->GetProgressModifier().SetProgressColorWithArray(
        nativeNode, colors.data(), colors.size());

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::SetProgressColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_COLOR_RESOURCE_COLOR);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        GetArkUIInternalNodeAPI()->GetProgressModifier().SetProgressColorWithValue(nativeNode, color.GetValue());
    } else {
        GetArkUIInternalNodeAPI()->GetProgressModifier().ResetProgressColor(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ProgressBridge::ResetProgressStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_NUM_NATIVE_NODE);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetProgressModifier().ResetProgressStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseStrokeWidth(
    const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle, int32_t index)
{
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(index);
    CalcDimension strokeWidth = CalcDimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP);
    auto theme = ArkTSUtils::GetTheme<ProgressTheme>();

    if (strokeWidthArg->IsString()) {
        const std::string& value = strokeWidthArg->ToString(vm)->ToString();
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

    if (borderWidthArg->IsString()) {
        const std::string& value = borderWidthArg->ToString(vm)->ToString();
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

    if (scaleWidthArg->IsString()) {
        const std::string& value = scaleWidthArg->ToString(vm)->ToString();
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
    std::string contentstr = contentArg->ToString(vm)->ToString();
    progressStyle.content = (contentArg->IsString()) ? contentstr.c_str() : nullptr;
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
    auto theme = pipelineContext->GetTheme<TextTheme>();

    std::string weight;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else if (weightArg->IsString()) {
            weight = weightArg->ToString(vm)->ToString();
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

void ParseLinearStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDHT);
    ParseStrokeRadius(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_RADIUS);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

void ParseRingStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDHT);
    ParseShadow(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SHADOW);
    ParseProgressStatus(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_PROGRESS_STATUS);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

void ParseCapsuleStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    ParseBorderColor(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_COLOR);
    ParseBorderWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_BORDER_WIDHT);
    ParseContent(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_CONTENT);
    ParseFontColor(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_COLOR);
    ParseCapsuleFontSize(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_SIZE);
    ParseCapsuleFontWeight(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_WEIGHT);
    ParseCapsuleFontStyle(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_STYLE);
    ParseCapsuleFontFamily(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_FONT_FAMILY);
    ParseEnableScanEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SCAN_EFFECT);
    ParseShowDefaultPercentage(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SHOW_DEFAULT_PERCENTAHE);
    ParseEnableSmoothEffect(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_ENABLE_SMOOTH_EFFECT);
}

void ParseProgressStyle(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIProgressStyle& progressStyle)
{
    auto progressTheme = ArkTSUtils::GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    ParseStrokeWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_STROKE_WIDHT);
    ParseScaleCount(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SCALE_COUNT);
    ParseScaleWidth(vm, runtimeCallInfo, progressStyle, ARG_NUM_STYLE_SCALE_WIDHT);
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
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto pipelineContext = PipelineContext::GetCurrentContext();
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
    auto progresstype = progressLayoutProperty->GetType();
    if (progresstype == ProgressType::LINEAR) {
        ParseLinearStyle(vm, runtimeCallInfo, progressStyle);
    } else if (progresstype == ProgressType::RING) {
        ParseRingStyle(vm, runtimeCallInfo, progressStyle);
    } else if (progresstype == ProgressType::CAPSULE) {
        ParseCapsuleStyle(vm, runtimeCallInfo, progressStyle);
    } else {
        ParseProgressStyle(vm, runtimeCallInfo, progressStyle);
    }
    GetArkUIInternalNodeAPI()->GetProgressModifier().SetProgressStyle(nativeNode, &progressStyle);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
