/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_progress.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "bridge/declarative_frontend/jsview/models/progress_model_impl.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_progress_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ProgressModel> ProgressModel::instance_ = nullptr;
std::mutex ProgressModel::mutex_;
ProgressType g_progressType = ProgressType::LINEAR;

ProgressModel* ProgressModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ProgressModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ProgressModelNG());
            } else {
                instance_.reset(new Framework::ProgressModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSProgress::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    auto value = 0;
    auto jsValue = paramObject->GetProperty("value");
    if (jsValue->IsNumber()) {
        value = jsValue->ToNumber<double>();
    }

    auto total = 100;
    auto jsTotal = paramObject->GetProperty("total");
    if (jsTotal->IsNumber() && jsTotal->ToNumber<int>() > 0) {
        total = jsTotal->ToNumber<int>();
    }

    if (value > total) {
        value = total;
    } else if (value < 0) {
        value = 0;
    }

    auto jsStyle = paramObject->GetProperty("type");
    if (jsStyle->IsNull() || jsStyle->IsUndefined()) {
        jsStyle = paramObject->GetProperty("style");
    }

    auto progressStyle = static_cast<ProgressStyle>(jsStyle->ToNumber<int32_t>());
    if (progressStyle == ProgressStyle::Eclipse) {
        g_progressType = ProgressType::MOON;
    } else if (progressStyle == ProgressStyle::Ring) {
        g_progressType = ProgressType::RING;
    } else if (progressStyle == ProgressStyle::ScaleRing) {
        g_progressType = ProgressType::SCALE;
    } else if (progressStyle == ProgressStyle::Capsule) {
        g_progressType = ProgressType::CAPSULE;
    } else {
        g_progressType = ProgressType::LINEAR;
    }

    ProgressModel::GetInstance()->Create(0.0, value, 0.0, total, static_cast<NG::ProgressType>(g_progressType));
    JSProgressTheme::ApplyTheme(progressStyle);
}

void JSProgress::JSBind(BindingTarget globalObj)
{
    JSClass<JSProgress>::Declare("Progress");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSProgress>::StaticMethod("create", &JSProgress::Create, opt);
    JSClass<JSProgress>::StaticMethod("value", &JSProgress::SetValue, opt);
    JSClass<JSProgress>::StaticMethod("color", &JSProgress::SetColor, opt);
    JSClass<JSProgress>::StaticMethod("style", &JSProgress::SetCircularStyle, opt);
    JSClass<JSProgress>::StaticMethod("backgroundColor", &JSProgress::JsBackgroundColor, opt);
    JSClass<JSProgress>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSProgress>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSProgress>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSProgress>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSProgress>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSProgress>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSProgress>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSProgress>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSProgress>::StaticMethod("borderColor", &JSProgress::JsBorderColor, opt);
    JSClass<JSProgress>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSProgress::SetValue(double value)
{
    if (std::isnan(value)) {
        return;
    }
    if (value < 0) {
        value = 0;
    }
    ProgressModel::GetInstance()->SetValue(value);
}

void JSProgress::SetColor(const JSCallbackInfo& info)
{
    Color colorVal;
    NG::Gradient gradient;
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
    if (ConvertGradientColor(info[0], gradient)) {
        ProgressModel::GetInstance()->SetGradientColor(gradient);
    } else {
        Color endColor;
        Color beginColor;
        if (info[0]->IsNull() || info[0]->IsUndefined() || !ParseJsColor(info[0], colorVal)) {
            endColor = theme->GetRingProgressEndSideColor();
            beginColor = theme->GetRingProgressBeginSideColor();
            if (g_progressType == ProgressType::CAPSULE) {
                colorVal = theme->GetCapsuleSelectColor();
            } else {
                colorVal = theme->GetTrackSelectedColor();
            }
        } else {
            endColor = colorVal;
            beginColor = colorVal;
        }

        NG::GradientColor endSideColor;
        NG::GradientColor beginSideColor;
        endSideColor.SetLinearColor(LinearColor(endColor));
        endSideColor.SetDimension(Dimension(0.0f));
        beginSideColor.SetLinearColor(LinearColor(beginColor));
        beginSideColor.SetDimension(Dimension(1.0f));
        gradient.AddColor(endSideColor);
        gradient.AddColor(beginSideColor);
        ProgressModel::GetInstance()->SetGradientColor(gradient);
        ProgressModel::GetInstance()->SetColor(colorVal);
    }
}

void JSProgress::SetCircularStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        JsSetProgressStyleOptions(info);
        return;
    }

    JsSetCommonOptions(info);

    switch (g_progressType) {
        case ProgressType::LINEAR:
            JsSetLinearStyleOptions(info);
            break;
        case ProgressType::RING:
            JsSetRingStyleOptions(info);
            break;
        case ProgressType::CAPSULE:
            JsSetCapsuleStyle(info);
            break;
        default:
            JsSetProgressStyleOptions(info);
            break;
    }
}

void JSProgress::JsSetProgressStyleOptions(const JSCallbackInfo& info)
{
    static const char attrsProgressStrokeWidth[] = "strokeWidth";
    static const char attrsProgressScaleWidth[] = "scaleWidth";
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension strokeWidthDimension;
    auto jsStrokeWidth = paramObject->GetProperty(attrsProgressStrokeWidth);
    if (!CheckLength(jsStrokeWidth, strokeWidthDimension, V2::PROGRESS_ETS_TAG, attrsProgressStrokeWidth)) {
        strokeWidthDimension = theme->GetTrackThickness();
    }

    if (strokeWidthDimension.Value() <= 0.0 || strokeWidthDimension.Unit() == DimensionUnit::PERCENT) {
        strokeWidthDimension = theme->GetTrackThickness();
    }

    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);

    auto jsScaleCount = paramObject->GetProperty("scaleCount");
    auto scaleCount = jsScaleCount->IsNumber() ? jsScaleCount->ToNumber<int32_t>() : theme->GetScaleNumber();
    if (scaleCount > 1.0) {
        ProgressModel::GetInstance()->SetScaleCount(scaleCount);
    } else {
        ProgressModel::GetInstance()->SetScaleCount(theme->GetScaleNumber());
    }

    CalcDimension scaleWidthDimension;
    auto jsScaleWidth = paramObject->GetProperty(attrsProgressScaleWidth);
    if (!CheckLength(jsScaleWidth, scaleWidthDimension, V2::PROGRESS_ETS_TAG, attrsProgressScaleWidth)) {
        scaleWidthDimension = theme->GetScaleWidth();
    }

    if ((scaleWidthDimension.Value() <= 0.0) || (scaleWidthDimension.Value() > strokeWidthDimension.Value()) ||
        scaleWidthDimension.Unit() == DimensionUnit::PERCENT) {
        scaleWidthDimension = theme->GetScaleWidth();
    }

    ProgressModel::GetInstance()->SetScaleWidth(scaleWidthDimension);
}

NG::ProgressStatus JSProgress::ConvertStrToProgressStatus(const std::string& value)
{
    if (value.compare("LOADING") == 0) {
        return NG::ProgressStatus::LOADING;
    } else {
        return NG::ProgressStatus::PROGRESSING;
    }
}

void JSProgress::JsSetRingStyleOptions(const JSCallbackInfo& info)
{
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();

    // Parse stroke width
    CalcDimension strokeWidthDimension;
    auto versionTenOrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    auto strokeWidth = paramObject->GetProperty("strokeWidth");
    if (strokeWidth->IsUndefined() || strokeWidth->IsNull() ||
        (versionTenOrLarger ? !ParseJsDimensionVpNG(strokeWidth, strokeWidthDimension)
                            : !ParseJsDimensionVp(strokeWidth, strokeWidthDimension))) {
        strokeWidthDimension = theme->GetTrackThickness();
    }

    if (LessOrEqual(strokeWidthDimension.Value(), 0.0f) || strokeWidthDimension.Unit() == DimensionUnit::PERCENT) {
        strokeWidthDimension = theme->GetTrackThickness();
    }

    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);

    // Parse shadow
    bool paintShadow = false;
    auto shadow = paramObject->GetProperty("shadow");
    if (shadow->IsUndefined() || shadow->IsNull() || !ParseJsBool(shadow, paintShadow)) {
        paintShadow = false;
    }

    ProgressModel::GetInstance()->SetPaintShadow(paintShadow);

    // Parse progress status
    std::string statusStr;
    NG::ProgressStatus progressStatus;
    auto status = paramObject->GetProperty("status");
    if (status->IsUndefined() || status->IsNull() || !ParseJsString(status, statusStr)) {
        progressStatus = NG::ProgressStatus::PROGRESSING;
    } else {
        progressStatus = ConvertStrToProgressStatus(statusStr);
    }

    ProgressModel::GetInstance()->SetProgressStatus(static_cast<NG::ProgressStatus>(progressStatus));

    auto jsSweepingEffect = paramObject->GetProperty("enableScanEffect");
    bool sweepingEffect = false;
    if (!ParseJsBool(jsSweepingEffect, sweepingEffect)) {
        sweepingEffect = false;
    }
    ProgressModel::GetInstance()->SetRingSweepingEffect(sweepingEffect);
}

void JSProgress::JsBackgroundColor(const JSCallbackInfo& info)
{
    Color colorVal;
    if (!CheckColor(info[0], colorVal, V2::PROGRESS_ETS_TAG, V2::ATTRS_COMMON_BACKGROUND_COLOR)) {
        RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(theme);
        if (g_progressType == ProgressType::CAPSULE) {
            colorVal = theme->GetCapsuleBgColor();
        } else if (g_progressType == ProgressType::RING) {
            colorVal = theme->GetRingProgressBgColor();
        } else {
            colorVal = theme->GetTrackBgColor();
        }
    }

    ProgressModel::GetInstance()->SetBackgroundColor(colorVal);
}

void JSProgress::JsBorderColor(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderColor(info);
}

void JSProgress::JsSetCapsuleStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();

    auto jsBorderWidth = paramObject->GetProperty("borderWidth");
    CalcDimension borderWidth;
    if (!ParseJsDimensionVpNG(jsBorderWidth, borderWidth)) {
        borderWidth = theme->GetBorderWidth();
    }
    if (LessNotEqual(borderWidth.Value(), 0.0) || borderWidth.Unit() == DimensionUnit::PERCENT) {
        borderWidth = theme->GetBorderWidth();
    }
    ProgressModel::GetInstance()->SetBorderWidth(borderWidth);

    auto jsBorderColor = paramObject->GetProperty("borderColor");
    Color colorVal;
    if (!ParseJsColor(jsBorderColor, colorVal)) {
        colorVal = theme->GetBorderColor();
    }
    ProgressModel::GetInstance()->SetBorderColor(colorVal);

    auto jsSweepingEffect = paramObject->GetProperty("enableScanEffect");
    bool sweepingEffect = false;
    if (!ParseJsBool(jsSweepingEffect, sweepingEffect)) {
        sweepingEffect = false;
    }
    ProgressModel::GetInstance()->SetSweepingEffect(sweepingEffect);

    auto jsShowDefaultPercentage = paramObject->GetProperty("showDefaultPercentage");
    bool showDefaultPercentage = false;
    if (!ParseJsBool(jsShowDefaultPercentage, showDefaultPercentage)) {
        showDefaultPercentage = false;
    }
    ProgressModel::GetInstance()->SetShowText(showDefaultPercentage);

    auto jsContext = paramObject->GetProperty("content");
    std::string text;
    if (jsContext->IsUndefined() || jsContext->IsNull() || (!ParseJsString(jsContext, text))) {
        ProgressModel::GetInstance()->SetText(std::nullopt);
    } else {
        ProgressModel::GetInstance()->SetText(text);
    }

    JsSetFontStyle(info);
}

void JSProgress::JsSetCommonOptions(const JSCallbackInfo& info)
{
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    // Parse smooth effect
    auto jsSmoothEffect = paramObject->GetProperty("enableSmoothEffect");
    bool enable = true;
    if (!ParseJsBool(jsSmoothEffect, enable)) {
        enable = true;
    }
    ProgressModel::GetInstance()->SetSmoothEffect(enable);
}

void JSProgress::JsSetFontStyle(const JSCallbackInfo& info)
{
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
    RefPtr<TextTheme> textTheme = GetTheme<TextTheme>();
    auto jsFontColor = paramObject->GetProperty("fontColor");
    Color fontColorVal;
    if (!ParseJsColor(jsFontColor, fontColorVal)) {
        fontColorVal = theme->GetTextColor();
    }

    ProgressModel::GetInstance()->SetFontColor(fontColorVal);

    auto textStyle = paramObject->GetProperty("font");
    if (!textStyle->IsObject()) {
        JsSetFontDefault();
    } else {
        auto textObject = JSRef<JSObject>::Cast(textStyle);
        JsSetFont(textObject);
    }
}

void JSProgress::JsSetFontDefault()
{
    RefPtr<TextTheme> textTheme = GetTheme<TextTheme>();
    RefPtr<ProgressTheme> progressTheme = GetTheme<ProgressTheme>();
    ProgressModel::GetInstance()->SetFontSize(progressTheme->GetTextSize());
    ProgressModel::GetInstance()->SetFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    ProgressModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
    ProgressModel::GetInstance()->SetItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
}

void JSProgress::JsSetFont(const JSRef<JSObject>& textObject)
{
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(theme);
    RefPtr<TextTheme> textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    auto size = textObject->GetProperty("size");
    CalcDimension fontSize;
    if (!ParseJsDimensionNG(size, fontSize, DimensionUnit::FP)) {
        fontSize = theme->GetTextSize();
    }
    if (LessNotEqual(fontSize.Value(), 0.0) || fontSize.Unit() == DimensionUnit::PERCENT) {
        fontSize = theme->GetTextSize();
    }
    ProgressModel::GetInstance()->SetFontSize(fontSize);

    auto fontWeight = textObject->GetProperty("weight");
    if (!fontWeight->IsNull()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(fontWeight, weight);
        }
        ProgressModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight));
    } else {
        ProgressModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
    }

    auto family = textObject->GetProperty("family");
    if (!family->IsNull() && family->IsString()) {
        auto familyVal = family->ToString();
        ProgressModel::GetInstance()->SetFontFamily(ConvertStrToFontFamilies(familyVal));
    } else {
        ProgressModel::GetInstance()->SetFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    }

    auto style = textObject->GetProperty("style");
    if (!style->IsNull() && style->IsNumber()) {
        auto styleVal = static_cast<FontStyle>(style->ToNumber<int32_t>());
        ProgressModel::GetInstance()->SetItalicFontStyle(styleVal);
    } else {
        ProgressModel::GetInstance()->SetItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
    }
}

bool JSProgress::ConvertGradientColor(const JsiRef<JsiValue>& param, NG::Gradient& gradient)
{
    if (param->IsNull() || param->IsUndefined() || !param->IsObject()) {
        return false;
    }

    JSLinearGradient* jsLinearGradient = JSRef<JSObject>::Cast(param)->Unwrap<JSLinearGradient>();
    auto proxy = param->GetLocalHandle();
    auto vm = param->GetEcmaVM();
    if (proxy->IsProxy(vm)) {
        panda::Local<panda::ProxyRef> thisProxiedObj =
            static_cast<panda::Local<panda::ProxyRef>>(proxy);
        jsLinearGradient = static_cast<JSLinearGradient *>(
            panda::Local<panda::ObjectRef>(thisProxiedObj->GetTarget(vm))
                ->GetNativePointerField(vm, 0));
    }

    if (!jsLinearGradient || jsLinearGradient->GetGradient().empty()) {
        return false;
    }

    size_t size = jsLinearGradient->GetGradient().size();
    if (size == 1) {
        // If there is only one color, then this color is used for both the begin and end side.
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().front().first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().front().second);
        gradient.AddColor(gradientColor);
        gradient.AddColor(gradientColor);
        return true;
    }

    for (size_t colorIndex = 0; colorIndex < size; colorIndex++) {
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}

void JSProgress::JsSetLinearStyleOptions(const JSCallbackInfo& info)
{
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();

    // Parse stroke width
    CalcDimension strokeWidthDimension;
    auto versionTenOrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    auto strokeWidth = paramObject->GetProperty("strokeWidth");
    if (strokeWidth->IsUndefined() || strokeWidth->IsNull() ||
        (versionTenOrLarger ? !ParseJsDimensionVpNG(strokeWidth, strokeWidthDimension)
                            : !ParseJsDimensionVp(strokeWidth, strokeWidthDimension))) {
        strokeWidthDimension = theme->GetTrackThickness();
    }

    if (LessOrEqual(strokeWidthDimension.Value(), 0.0f) || strokeWidthDimension.Unit() == DimensionUnit::PERCENT) {
        strokeWidthDimension = theme->GetTrackThickness();
    }

    ProgressModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);

    auto jsSweepingEffect = paramObject->GetProperty("enableScanEffect");
    bool sweepingEffect = false;
    if (!ParseJsBool(jsSweepingEffect, sweepingEffect)) {
        sweepingEffect = false;
    }
    ProgressModel::GetInstance()->SetLinearSweepingEffect(sweepingEffect);

    // Parse stroke radius
    CalcDimension strokeRadiusDimension;
    auto strokeRadius = paramObject->GetProperty("strokeRadius");
    if (strokeRadius->IsUndefined() || strokeRadius->IsNull() ||
        !ParseJsDimensionVpNG(strokeRadius, strokeRadiusDimension)) {
        ProgressModel::GetInstance()->ResetStrokeRadius();
        return;
    }

    if (LessNotEqual(strokeRadiusDimension.Value(), 0.0f) || strokeRadiusDimension.Unit() == DimensionUnit::PERCENT) {
        ProgressModel::GetInstance()->ResetStrokeRadius();
        return;
    }

    ProgressModel::GetInstance()->SetStrokeRadius(strokeRadiusDimension);
}

} // namespace OHOS::Ace::Framework
