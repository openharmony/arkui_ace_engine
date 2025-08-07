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

#include "frameworks/bridge/declarative_frontend/jsview/js_linear_indicator.h"

#include "base/log/ace_scoring_log.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_model.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_model_ng.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_theme.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_linear_indicator_controller.h"

namespace OHOS::Ace {

std::unique_ptr<LinearIndicatorModel> LinearIndicatorModel::instance_ = nullptr;

LinearIndicatorModel* LinearIndicatorModel::GetInstance()
{
    if (!instance_) {
        instance_.reset(new NG::LinearIndicatorModelNG());
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSLinearIndicator::Create(const JSCallbackInfo& info)
{
    const int32_t length = info.Length();
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    int32_t progressCount = theme->GetDefaultProgressCount();
    int32_t defaultProgressMin = theme->GetDefaultProgressMin();

    if (length > 0) {
        auto arg0 = info[0];
        if (arg0->IsNumber()) {
            progressCount = arg0->ToNumber<int32_t>();
            if (progressCount < defaultProgressMin) {
                progressCount = defaultProgressMin;
            }
        }
    }
    RefPtr<NG::LinearIndicatorController> controller = LinearIndicatorModel::GetInstance()->Create(progressCount);
    if (length > 1) {
        auto arg1 = info[1];
        if (arg1->IsObject()) {
            auto* jsController = JSRef<JSObject>::Cast(arg1)->Unwrap<JSLinearIndicatorController>();
            if (jsController) {
                jsController->SetController(controller);
            }
        }
    }
}

void JSLinearIndicator::SetStyle(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto arg0 = info[0];
    if (!arg0->IsObject()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    auto paramObject = JSRef<JSObject>::Cast(arg0);
    SetSpace(paramObject, theme);
    SetStrokeWidth(paramObject, theme);
    SetStrokeRadius(paramObject, theme);
    SetTrackBackgroundColor(paramObject, theme);
    SetTrackColor(paramObject, theme);
}

void JSLinearIndicator::Loop(const JSCallbackInfo& info)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    bool value = theme->GetDefaultLoop();
    if (info.Length() > 0) {
        auto arg0 = info[0];
        if (arg0->IsBoolean()) {
            value = arg0->ToBoolean();
        }
    }
    LinearIndicatorModel::GetInstance()->Loop(value);
}

void JSLinearIndicator::OnChange(const JSCallbackInfo& info)
{
    if ((info.Length() == 0)) {
        return;
    }
    auto arg0 = info[0];
    if (!arg0->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(arg0));
    auto onChangeCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                                int32_t index, float progress) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("LinearIndicator::onChange");
        JSRef<JSVal> params[2] = { JSRef<JSVal>::Make(ToJSValue(index)), JSRef<JSVal>::Make(ToJSValue(progress)) };
        func->ExecuteJS(2, params);
    };
    LinearIndicatorModel::GetInstance()->OnChange(std::move(onChangeCallback));
}

void JSLinearIndicator::JSBind(BindingTarget globalObj)
{
    JSClass<JSLinearIndicator>::Declare("LinearIndicator");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSLinearIndicator>::StaticMethod("create", &JSLinearIndicator::Create, opt);
    JSClass<JSLinearIndicator>::StaticMethod("indicatorStyle", &JSLinearIndicator::SetStyle, opt);
    JSClass<JSLinearIndicator>::StaticMethod("indicatorLoop", &JSLinearIndicator::Loop, opt);
    JSClass<JSLinearIndicator>::StaticMethod("onChange", &JSLinearIndicator::OnChange, opt);
    JSClass<JSLinearIndicator>::StaticMethod("height", &JSLinearIndicator::JsHeight, opt);
    JSClass<JSLinearIndicator>::StaticMethod("padding", &JSLinearIndicator::JsPadding, opt);
    JSClass<JSLinearIndicator>::StaticMethod("paddingLeft", &JSLinearIndicator::SetPaddingLeft, opt);
    JSClass<JSLinearIndicator>::StaticMethod("paddingRight", &JSLinearIndicator::SetPaddingRight, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingTop", &JSLinearIndicator::JsIgnore, opt);
    JSClass<JSViewAbstract>::StaticMethod("paddingBottom", &JSLinearIndicator::JsIgnore, opt);
    JSClass<JSLinearIndicator>::Inherit<JSViewAbstract>();
    JSClass<JSLinearIndicator>::Inherit<JSInteractableView>();
    JSClass<JSLinearIndicator>::Bind<>(globalObj);
}

void JSLinearIndicator::SetSpace(const JSRef<JSObject>& paramObject, const RefPtr<NG::LinearIndicatorTheme>& theme)
{
    CalcDimension spaceDimension;
    CalcDimension defaultSpace = theme->GetDefaultSpace();
    auto space = paramObject->GetProperty("space");
    if (space->IsUndefined() || space->IsNull() || !ParseLengthMetricsToDimension(space, spaceDimension)) {
        spaceDimension = defaultSpace;
    }
    if (LessNotEqual(spaceDimension.Value(), 0.0f) || spaceDimension.Unit() == DimensionUnit::PERCENT) {
        spaceDimension = defaultSpace;
    }
    LinearIndicatorModel::GetInstance()->SetSpace(spaceDimension);
}

void JSLinearIndicator::SetStrokeWidth(
    const JSRef<JSObject>& paramObject, const RefPtr<NG::LinearIndicatorTheme>& theme)
{
    CalcDimension strokeWidthDimension;
    CalcDimension defaultStrokeWidth = theme->GetDefaultStrokeWidth();
    CalcDimension defaultStrokeWidthMin = theme->GetDefaultStrokeWidthMin();
    auto strokeWidth = paramObject->GetProperty("strokeWidth");
    if (strokeWidth->IsUndefined() || strokeWidth->IsNull() ||
        !ParseLengthMetricsToDimension(strokeWidth, strokeWidthDimension)) {
        strokeWidthDimension = defaultStrokeWidth;
    }
    if (LessNotEqual(strokeWidthDimension.Value(), 0.0f) || strokeWidthDimension.Unit() == DimensionUnit::PERCENT) {
        strokeWidthDimension = defaultStrokeWidth;
    }
    if (strokeWidthDimension.ConvertToVp() < defaultStrokeWidthMin.ConvertToVp()) {
        strokeWidthDimension = defaultStrokeWidthMin;
    }
    LinearIndicatorModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);
}

void JSLinearIndicator::SetStrokeRadius(
    const JSRef<JSObject>& paramObject, const RefPtr<NG::LinearIndicatorTheme>& theme)
{
    CalcDimension strokeRadiusDimension;
    CalcDimension defaultStrokeRadius = theme->GetDefaultStrokeRadius();
    auto strokeRadius = paramObject->GetProperty("strokeRadius");
    if (strokeRadius->IsUndefined() || strokeRadius->IsNull() ||
        !ParseLengthMetricsToDimension(strokeRadius, strokeRadiusDimension)) {
        strokeRadiusDimension = defaultStrokeRadius;
    }
    if (LessNotEqual(strokeRadiusDimension.Value(), 0.0f) || strokeRadiusDimension.Unit() == DimensionUnit::PERCENT) {
        strokeRadiusDimension = defaultStrokeRadius;
    }
    LinearIndicatorModel::GetInstance()->SetStrokeRadius(strokeRadiusDimension);
}

void JSLinearIndicator::SetTrackBackgroundColor(
    const JSRef<JSObject>& paramObject, const RefPtr<NG::LinearIndicatorTheme>& theme)
{
    Color trackBackgroundColorValue;
    auto trackBackgroundColor = paramObject->GetProperty("trackBackgroundColor");
    if (trackBackgroundColor->IsUndefined() || trackBackgroundColor->IsNull() ||
        !ParseColorMetricsToColor(trackBackgroundColor, trackBackgroundColorValue)) {
        trackBackgroundColorValue = theme->GetTrackBackgroundColor();
    }
    LinearIndicatorModel::GetInstance()->SetTrackBackgroundColor(trackBackgroundColorValue);
}

void JSLinearIndicator::SetTrackColor(const JSRef<JSObject>& paramObject, const RefPtr<NG::LinearIndicatorTheme>& theme)
{
    Color trackColorValue;
    auto trackColor = paramObject->GetProperty("trackColor");
    if (trackColor->IsUndefined() || trackColor->IsNull() || !ParseColorMetricsToColor(trackColor, trackColorValue)) {
        trackColorValue = theme->GetTrackColor();
    }
    LinearIndicatorModel::GetInstance()->SetTrackColor(trackColorValue);
}

void JSLinearIndicator::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    Dimension defaultHeight = theme->GetDefaultHeight();

    CalcDimension value = defaultHeight;
    auto jsValue = info[0];
    if (jsValue->IsUndefined()) {
        value = defaultHeight;
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVpNG(jsValue, value)) {
            value = defaultHeight;
        }
    } else if (!ParseJsDimensionVp(jsValue, value)) {
        value = defaultHeight;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        value = defaultHeight;
    }
    ViewAbstractModel::GetInstance()->SetHeight(value);
}

void JSLinearIndicator::JsPadding(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    Dimension defaultLeft = theme->GetPaddingLeft();
    Dimension defaultRight = theme->GetPaddingRight();

    auto jsVal = info[0];
    if ((!jsVal->IsObject()) && (!jsVal->IsString()) && (!jsVal->IsNumber())) {
        ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, std::nullopt, defaultLeft, defaultRight);
        return;
    }
    if (jsVal->IsObject()) {
        CommonCalcDimension commonCalcDimension;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(jsVal);
        ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (!commonCalcDimension.left.has_value() || LessNotEqual(commonCalcDimension.left.value().Value(), 0.0)) {
            commonCalcDimension.left = defaultLeft;
        }
        if (!commonCalcDimension.right.has_value() || LessNotEqual(commonCalcDimension.right.value().Value(), 0.0)) {
            commonCalcDimension.right = defaultRight;
        }
        ViewAbstractModel::GetInstance()->SetPaddings(
            std::nullopt, std::nullopt, commonCalcDimension.left, commonCalcDimension.right);
        return;
    }
    CalcDimension length;
    if (ParseJsDimensionVp(jsVal, length) && (!LessNotEqual(length.Value(), 0.0))) {
        ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, std::nullopt, length, length);
    } else {
        ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, std::nullopt, defaultLeft, defaultRight);
    }
}

void JSLinearIndicator::SetPaddingLeft(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    Dimension defaultLeft = theme->GetPaddingLeft();
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value = defaultLeft;
    }
    ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, std::nullopt, value, std::nullopt);
}

void JSLinearIndicator::SetPaddingRight(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    Dimension defaultRight = theme->GetPaddingRight();
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        value = defaultRight;
    }
    ViewAbstractModel::GetInstance()->SetPaddings(std::nullopt, std::nullopt, std::nullopt, value);
}

void JSLinearIndicator::JsIgnore(const JSCallbackInfo& info) {}

} // namespace OHOS::Ace::Framework
