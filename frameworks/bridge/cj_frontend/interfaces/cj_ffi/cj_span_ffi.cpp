/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_span_ffi.h"
#include "cj_lambda.h"

#include "base/utils/utf_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/text/span_model.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

namespace {
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
const std::vector<TextDecoration> TEXT_DECRATIONS = { TextDecoration::NONE, TextDecoration::UNDERLINE,
    TextDecoration::OVERLINE, TextDecoration::LINE_THROUGH };
} // namespace

static TextBackgroundStyle ParseSpanTextBackgroundStyle(uint32_t color, double radiusDouble, int32_t unit)
{
    TextBackgroundStyle textBackgroundStyle;
    Color colorVal = Color(color);
    Dimension value(radiusDouble, static_cast<DimensionUnit>(unit));
    CalcDimension radius = CalcDimension(value);
    if (radius.Unit() == DimensionUnit::PERCENT) {
        radius.Reset();
    }
    textBackgroundStyle.backgroundColor = colorVal;
    textBackgroundStyle.backgroundRadius = { radius, radius, radius, radius };
    textBackgroundStyle.backgroundRadius->multiValued = false;
    return textBackgroundStyle;
}

static TextBackgroundStyle ParseSpanTextBackgroundStyle(uint32_t color, CBorderRadiuses radiusValue)
{
    TextBackgroundStyle textBackgroundStyle;
    Color colorVal = Color(color);
    Dimension topLeftValue(radiusValue.topLeftRadiuses, static_cast<DimensionUnit>(radiusValue.topLeftUnit));
    CalcDimension topLeft = CalcDimension(topLeftValue);
    Dimension topRightValue(radiusValue.topRightRadiuses, static_cast<DimensionUnit>(radiusValue.topRightUnit));
    CalcDimension topRight = CalcDimension(topRightValue);
    Dimension bottomLeftValue(radiusValue.bottomLeftRadiuses, static_cast<DimensionUnit>(radiusValue.bottomLeftUnit));
    CalcDimension bottomLeft = CalcDimension(bottomLeftValue);
    Dimension bottomRightValue(
        radiusValue.bottomRightRadiuses, static_cast<DimensionUnit>(radiusValue.bottomRightUnit));
    CalcDimension bottomRight = CalcDimension(bottomRightValue);
    textBackgroundStyle.backgroundColor = colorVal;
    textBackgroundStyle.backgroundRadius = { topLeft, topRight, bottomRight, bottomLeft };
    textBackgroundStyle.backgroundRadius->multiValued = false;
    return textBackgroundStyle;
}

extern "C" {
VectorNativeTextShadows FFICJCreateVectorNativeTextShadows(int64_t size)
{
    LOGI("Create NativeTextShadows Vector");
    return new std::vector<NativeTextShadow>(size);
}

void FFICJVectorNativeTextShadowsSetElement(VectorNativeTextShadows vec, int64_t index, NativeTextShadows textShadow)
{
    LOGI("NativeTextShadows Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<NativeTextShadows>*>(vec);
    (*actualVec)[index] = textShadow;
    LOGI("NativeTextShadows Vector Set Element Success");
}

void FFICJVectorNativeTextShadowsDelete(VectorNativeTextShadows vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeTextShadows>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkSpanCreate(const char* content)
{
    SpanModel::GetInstance()->Create(UtfUtils::Str8DebugToStr16(content));
}

void FfiOHOSAceFrameworkSpanSetDecoration(int32_t type, uint32_t color)
{
    if (!Utils::CheckParamsValid(type, TEXT_DECRATIONS.size())) {
        LOGE("invalid value for scrollDirection");
        return;
    }
    SpanModel::GetInstance()->SetTextDecoration(TEXT_DECRATIONS[type]);
    SpanModel::GetInstance()->SetTextDecorationColor(Color(color));
}

void FfiOHOSAceFrameworkSpanSetTextCase(int32_t textCase)
{
    if (!Utils::CheckParamsValid(textCase, TEXT_CASES.size())) {
        LOGE("invalid value for scrollDirection");
        return;
    }
    SpanModel::GetInstance()->SetTextCase(TEXT_CASES[textCase]);
}

void FfiOHOSAceFrameworkSpanSetFontSize(double fontSize, int32_t unit)
{
    Dimension value(fontSize, static_cast<DimensionUnit>(unit));
    SpanModel::GetInstance()->SetFontSize(value);
}

void FfiOHOSAceFrameworkSpanSetOnClick(void (*callback)(CJClickInfo clickInfo))
{
    auto lambda = [ffiOnClick = CJLambda::Create(callback)](const GestureEvent& event) -> void {
        CJClickInfo cjClickInfo {};
        CJEventTarget cjEventTarget {};
        CJArea cjArea {};
        CJPosition cjPosition {};
        CJPosition cjGlobalPosition {};
        AssambleCJClickInfo(event, cjClickInfo, cjEventTarget, cjArea, cjPosition, cjGlobalPosition);
        ffiOnClick(cjClickInfo);
    };

    auto onClick = [lambda](const BaseEventInfo* info) {
        const auto* clickInfo = TypeInfoHelper::DynamicCast<GestureEvent>(info);
        auto newInfo = *clickInfo;
        lambda(newInfo);
    };
    SpanModel::GetInstance()->SetOnClick(onClick);
    return;
}

void FfiOHOSAceFrameworkSpanSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    SpanModel::GetInstance()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkSpanSetFontWeight(const char* fontWeight)
{
    SpanModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkSpanSetFontColor(uint32_t textColor)
{
    SpanModel::GetInstance()->SetTextColor(Color(textColor));
}

void FfiOHOSAceFrameworkSpanSetFontStyle(int32_t fontStyle)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLES.size())) {
        LOGE("invalid value for scrollDirection");
        return;
    }
    SpanModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[fontStyle]);
}

void FfiOHOSAceFrameworkSpanSetLetterSpacing(double space, int32_t unit)
{
    Dimension value(space, static_cast<DimensionUnit>(unit));
    SpanModel::GetInstance()->SetLetterSpacing(value);
}

void FfiOHOSAceFrameworkSpanSetBaselineOffset(double offset, int32_t unit)
{
    Dimension value(offset, static_cast<DimensionUnit>(unit));
    SpanModel::GetInstance()->SetBaselineOffset(value);
}

void FfiOHOSAceFrameworkSpanSetLineHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    SpanModel::GetInstance()->SetLineHeight(value);
}

void FfiOHOSAceFrameworkSpanSetFont(const char* family, double size, int32_t unit, const char* weight, int32_t style)
{
    Font font;
    if (family) {
        font.fontFamilies = ConvertStrToFontFamilies(family);
    }
    if (size > 0) {
        font.fontSize = Dimension(size, static_cast<DimensionUnit>(unit));
    }
    if (weight) {
        font.fontWeight = ConvertStrToFontWeight(weight);
    }
    if (Utils::CheckParamsValid(style, FONT_STYLES.size())) {
        font.fontStyle = FONT_STYLES[style];
    }
    SpanModel::GetInstance()->SetFont(font);
}

void FfiOHOSAceFrameworkSpanSetTextShadow(VectorStringPtr vecContent)
{
    auto nativeTextShadowVec = *reinterpret_cast<std::vector<NativeTextShadow>*>(vecContent);
    std::vector<Shadow> shadows(nativeTextShadowVec.size());
    for (size_t i = 0; i < nativeTextShadowVec.size(); i++) {
        Dimension dOffsetX(nativeTextShadowVec[i].offsetX, DimensionUnit::VP);
        Dimension dOffsetY(nativeTextShadowVec[i].offsetY, DimensionUnit::VP);

        shadows[i].SetBlurRadius(nativeTextShadowVec[i].radius);
        shadows[i].SetOffsetX(dOffsetX.Value());
        shadows[i].SetOffsetY(dOffsetY.Value());
        shadows[i].SetColor(Color(nativeTextShadowVec[i].color));
        shadows[i].SetIsFilled(nativeTextShadowVec[i].isFilled);
        shadows[i].SetShadowType(nativeTextShadowVec[i].type == 0 ? ShadowType::COLOR : ShadowType::BLUR);
    }
    SpanModel::GetInstance()->SetTextShadow(shadows);
}

void FfiOHOSAceFrameworkSpanSetTextBackgroundStyle(uint32_t color, double radius, int32_t unit)
{
    TextBackgroundStyle textBackgroundStyle = ParseSpanTextBackgroundStyle(color, radius, unit);
    SpanModel::GetInstance()->SetTextBackgroundStyle(textBackgroundStyle);
}

void FfiOHOSAceFrameworkSpanSetTextBackgroundStyleBorder(uint32_t color, CBorderRadiuses radius)
{
    TextBackgroundStyle textBackgroundStyle = ParseSpanTextBackgroundStyle(color, radius);
    SpanModel::GetInstance()->SetTextBackgroundStyle(textBackgroundStyle);
}
}
