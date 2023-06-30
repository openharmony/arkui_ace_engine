/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/button/button_component.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/button_model_impl.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {
std::unique_ptr<ButtonModel> ButtonModel::instance_ = nullptr;
std::mutex ButtonModel::mutex_;

ButtonModel* ButtonModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ButtonModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ButtonModelNG());
            } else {
                instance_.reset(new Framework::ButtonModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };

bool JSButton::isLabelButton_ = false;

void JSButton::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }

    ButtonModel::GetInstance()->SetFontSize(fontSize);
}

void JSButton::SetFontWeight(const std::string& value)
{
    ButtonModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSButton::SetFontStyle(int32_t value)
{
    const std::vector<FontStyle> fontStyles = { FontStyle::NORMAL, FontStyle::ITALIC };
    if (value < 0 || value >= static_cast<int32_t>(fontStyles.size())) {
        LOGE("Text fontStyle(%d) is invalid value", value);
        return;
    }

    ButtonModel::GetInstance()->SetFontStyle(fontStyles[value]);
}

void JSButton::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGE("Parse FontFamilies failed");
        return;
    }

    ButtonModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSButton::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        LOGI("Set text color is invalid, use default text color.");
        auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
        textColor = buttonTheme->GetTextStyle().GetTextColor();
    }

    ButtonModel::GetInstance()->SetFontColor(textColor);
}

void JSButton::SetType(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    int32_t value = 1;
    if (info[0]->IsNumber()) {
        value = info[0]->ToNumber<int32_t>();
    }
    if ((ButtonType)value == ButtonType::CAPSULE || (ButtonType)value == ButtonType::CIRCLE ||
        (ButtonType)value == ButtonType::ARC || (ButtonType)value == ButtonType::NORMAL) {
        ButtonModel::GetInstance()->SetType(value);
    } else {
        LOGE("Setting button to non valid ButtonType %d", value);
    }
}

void JSButton::SetStateEffect(bool stateEffect)
{
    ButtonModel::GetInstance()->SetStateEffect(stateEffect);
}

void JSButton::HandleDifferentRadius(const JSRef<JSVal>& args)
{
    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;
    if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        CalcDimension topLeft;
        if (ParseJsDimensionVp(object->GetProperty("topLeft"), topLeft)) {
            radiusTopLeft = topLeft;
        }
        CalcDimension topRight;
        if (ParseJsDimensionVp(object->GetProperty("topRight"), topRight)) {
            radiusTopRight = topRight;
        }
        CalcDimension bottomLeft;
        if (ParseJsDimensionVp(object->GetProperty("bottomLeft"), bottomLeft)) {
            radiusBottomLeft = bottomLeft;
        }
        CalcDimension bottomRight;
        if (ParseJsDimensionVp(object->GetProperty("bottomRight"), bottomRight)) {
            radiusBottomRight = bottomRight;
        }
        if (!radiusTopLeft.has_value() && !radiusTopRight.has_value() && !radiusBottomLeft.has_value() &&
            !radiusBottomRight.has_value()) {
            return;
        }
        ButtonModel::GetInstance()->SetBorderRadius(radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
    }
}

void JSButton::GetFontContent(JSRef<JSVal>& font, ButtonParameters& buttonParameters)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(font);
    JSRef<JSVal> size = obj->GetProperty("size");
    CalcDimension fontSize;
    if (ParseJsDimensionFp(size, fontSize)) {
        buttonParameters.fontSize = fontSize;
    }

    JSRef<JSVal> weight = obj->GetProperty("weight");
    if (weight->IsString()) {
        buttonParameters.fontWeight = ConvertStrToFontWeight(weight->ToString());
    }

    JSRef<JSVal> family = obj->GetProperty("family");
    std::vector<std::string> fontFamilies;
    if (ParseJsFontFamilies(family, fontFamilies)) {
        buttonParameters.fontFamily = fontFamilies;
    }

    JSRef<JSVal> style = obj->GetProperty("style");
    if (style->IsNumber()) {
        auto value = style->ToNumber<int32_t>();
        if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
            buttonParameters.fontStyle = FONT_STYLES[value];
        }
    }
}

void JSButton::CompleteParameters(ButtonParameters& buttonParameters)
{
    auto buttonTheme = GetTheme<ButtonTheme>();
    if (!buttonTheme) {
        return;
    }
    auto textStyle = buttonTheme->GetTextStyle();
    if (!buttonParameters.maxLines.has_value()) {
        buttonParameters.maxLines = buttonTheme->GetTextMaxLines();
    }
    if (!buttonParameters.minFontSize.has_value()) {
        buttonParameters.minFontSize = buttonTheme->GetMinFontSize();
    }
    if (!buttonParameters.maxFontSize.has_value()) {
        buttonParameters.maxFontSize = buttonTheme->GetMaxFontSize();
    }
    if (!buttonParameters.fontSize.has_value()) {
        buttonParameters.fontSize = textStyle.GetFontSize();
    }
    if (!buttonParameters.fontWeight.has_value()) {
        buttonParameters.fontWeight = textStyle.GetFontWeight();
    }
    if (!buttonParameters.fontStyle.has_value()) {
        buttonParameters.fontStyle = textStyle.GetFontStyle();
    }
    if (!buttonParameters.heightAdaptivePolicy.has_value()) {
        buttonParameters.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (!buttonParameters.textOverflow.has_value()) {
        buttonParameters.textOverflow = TextOverflow::CLIP;
    }
}

void JSButton::SetLableStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        LOGE("info[0] not is Object");
        return;
    }

    ButtonParameters buttonParameters;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> overflowValue = obj->GetProperty("overflow");
    buttonParameters.textOverflow = TextOverflow::ELLIPSIS;
    if (!overflowValue->IsNull() && overflowValue->IsNumber()) {
        auto overflow = overflowValue->ToNumber<int32_t>();
        if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size()) &&
            TEXT_OVERFLOWS[overflow] != TextOverflow::MARQUEE) {
            buttonParameters.textOverflow = TEXT_OVERFLOWS[overflow];
        }
    }

    JSRef<JSVal> maxLines = obj->GetProperty("maxLines");
    if (!maxLines->IsNull() && maxLines->IsNumber()) {
        buttonParameters.maxLines = Positive(maxLines->ToNumber<int32_t>()) ? maxLines->ToNumber<int32_t>() : 1;
    }

    JSRef<JSVal> minFontSizeValue = obj->GetProperty("minFontSize");
    CalcDimension minFontSize;
    if (ParseJsDimensionFp(minFontSizeValue, minFontSize)) {
        buttonParameters.minFontSize = minFontSize;
    }

    JSRef<JSVal> maxFontSizeValue = obj->GetProperty("maxFontSize");
    CalcDimension maxFontSize;
    if (ParseJsDimensionFp(maxFontSizeValue, maxFontSize)) {
        buttonParameters.maxFontSize = maxFontSize;
    }

    JSRef<JSVal> adaptHeightValue = obj->GetProperty("heightAdaptivePolicy");
    if (!adaptHeightValue->IsNull() && adaptHeightValue->IsNumber()) {
        auto adaptHeight = adaptHeightValue->ToNumber<int32_t>();
        if (adaptHeight >= 0 && adaptHeight < static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
            buttonParameters.heightAdaptivePolicy = HEIGHT_ADAPTIVE_POLICY[adaptHeight];
        }
    }

    JSRef<JSVal> font = obj->GetProperty("font");
    if (!font->IsNull() && font->IsObject()) {
        GetFontContent(font, buttonParameters);
    }

    CompleteParameters(buttonParameters);
    ButtonModel::GetInstance()->SetLableStyle(buttonParameters);
}

void JSButton::JsRemoteMessage(const JSCallbackInfo& info)
{
    RemoteCallback remoteCallback;
    JSInteractableView::JsRemoteMessage(info, remoteCallback);
    ButtonModel::GetInstance()->SetRemoteMessage(std::move(remoteCallback));
}

void JSButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSButton>::Declare("Button");
    JSClass<JSButton>::StaticMethod("fontColor", &JSButton::SetTextColor, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontSize", &JSButton::SetFontSize, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontWeight", &JSButton::SetFontWeight, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontStyle", &JSButton::SetFontStyle, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("fontFamily", &JSButton::SetFontFamily, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("type", &JSButton::SetType, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("stateEffect", &JSButton::SetStateEffect, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("labelStyle", &JSButton::SetLableStyle, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("onClick", &JSButton::JsOnClick);
    JSClass<JSButton>::StaticMethod("remoteMessage", &JSButton::JsRemoteMessage);
    JSClass<JSButton>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSButton>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSButton>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSButton>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSButton>::StaticMethod("backgroundColor", &JSButton::JsBackgroundColor);
    JSClass<JSButton>::StaticMethod("width", &JSButton::JsWidth);
    JSClass<JSButton>::StaticMethod("height", &JSButton::JsHeight);
    JSClass<JSButton>::StaticMethod("aspectRatio", &JSButton::JsAspectRatio);
    JSClass<JSButton>::StaticMethod("borderRadius", &JSButton::JsRadius);
    JSClass<JSButton>::StaticMethod("border", &JSButton::JsBorder);
    JSClass<JSButton>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSButton>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSButton>::StaticMethod("size", &JSButton::JsSize);
    JSClass<JSButton>::StaticMethod("padding", &JSButton::JsPadding);
    JSClass<JSButton>::StaticMethod("hoverEffect", &JSButton::JsHoverEffect);

    JSClass<JSButton>::StaticMethod("createWithLabel", &JSButton::CreateWithLabel, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("createWithChild", &JSButton::CreateWithChild, MethodOptions::NONE);
    JSClass<JSButton>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSButton::CreateWithLabel(const JSCallbackInfo& info)
{
    std::list<RefPtr<Component>> buttonChildren;
    std::string label;
    bool labelSet = false;
    CreateWithPara para;
    para.parseSuccess = ParseJsString(info[0], label);
    para.label = label;
    if (info[0]->IsObject() && JSRef<JSObject>::Cast(info[0])->GetProperty("type")->IsNumber()) {
        para.typeFirst =
            static_cast<ButtonType>(JSRef<JSObject>::Cast(info[0])->GetProperty("type")->ToNumber<int32_t>());
    }
    if (info[1]->IsObject() && JSRef<JSObject>::Cast(info[1])->GetProperty("type")->IsNumber()) {
        para.typeSecond =
            static_cast<ButtonType>(JSRef<JSObject>::Cast(info[1])->GetProperty("type")->ToNumber<int32_t>());
    }
    if (info[0]->IsObject() && JSRef<JSObject>::Cast(info[0])->GetProperty("stateEffect")->IsBoolean()) {
        para.stateEffectFirst = JSRef<JSObject>::Cast(info[0])->GetProperty("stateEffect")->ToBoolean();
    }
    if (info[1]->IsObject() && JSRef<JSObject>::Cast(info[1])->GetProperty("stateEffect")->IsBoolean()) {
        para.stateEffectSecond = JSRef<JSObject>::Cast(info[1])->GetProperty("stateEffect")->ToBoolean();
    }
    if (para.parseSuccess.value()) {
        labelSet = true;
    }

    para.labelSetInfoFirst = !labelSet && info[0]->IsObject();
    para.labelSetInfoSecond = (info.Length() > 1) && info[1]->IsObject();
    ButtonModel::GetInstance()->CreateWithLabel(para, buttonChildren);
    ButtonModel::GetInstance()->Create(para, buttonChildren);
    isLabelButton_ = true;
}

void JSButton::CreateWithChild(const JSCallbackInfo& info)
{
    CreateWithPara para;
    para.labelSetInfoFirst = info[0]->IsObject();
    para.labelSetInfoSecond = (info.Length() > 1) && info[1]->IsObject();
    if (info[0]->IsObject() && JSRef<JSObject>::Cast(info[0])->GetProperty("type")->IsNumber()) {
        para.typeFirst =
            static_cast<ButtonType>(JSRef<JSObject>::Cast(info[0])->GetProperty("type")->ToNumber<int32_t>());
    }

    if (info[1]->IsObject() && JSRef<JSObject>::Cast(info[1])->GetProperty("type")->IsNumber()) {
        para.typeSecond =
            static_cast<ButtonType>(JSRef<JSObject>::Cast(info[1])->GetProperty("type")->ToNumber<int32_t>());
    }

    if (info[0]->IsObject() && JSRef<JSObject>::Cast(info[0])->GetProperty("stateEffect")->IsBoolean()) {
        para.stateEffectFirst = JSRef<JSObject>::Cast(info[0])->GetProperty("stateEffect")->ToBoolean();
    }

    if (info[1]->IsObject() && JSRef<JSObject>::Cast(info[1])->GetProperty("stateEffect")->IsBoolean()) {
        para.stateEffectSecond = JSRef<JSObject>::Cast(info[1])->GetProperty("stateEffect")->ToBoolean();
    }
    ButtonModel::GetInstance()->CreateWithChild(para);
    isLabelButton_ = false;
}

void JSButton::JsPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty paddingNew = GetNewPadding(info);
    Edge paddingOld = Edge(GetOldPadding(info));
    ButtonModel::GetInstance()->Padding(paddingNew, paddingOld);
}

Edge JSButton::GetOldPadding(const JSCallbackInfo& info)
{
    Edge padding;
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not a string, number or object.");
        return padding;
    }

    if (info[0]->IsNumber()) {
        CalcDimension edgeValue;
        if (ParseJsDimensionVp(info[0], edgeValue)) {
            padding = Edge(edgeValue);
        }
    } else if (info[0]->IsObject()) {
        auto object = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!object) {
            LOGE("Js Parse object failed. argsPtr is null.");
            return padding;
        }
        CalcDimension left = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension top = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension right = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension bottom = CalcDimension(0.0, DimensionUnit::VP);
        if (object->Contains("top") || object->Contains("bottom") || object->Contains("left") ||
            object->Contains("right")) {
            ParseJsonDimensionVp(object->GetValue("left"), left);
            ParseJsonDimensionVp(object->GetValue("top"), top);
            ParseJsonDimensionVp(object->GetValue("right"), right);
            ParseJsonDimensionVp(object->GetValue("bottom"), bottom);
        }
        padding = Edge(left, top, right, bottom);
    }

    return padding;
}

NG::PaddingProperty JSButton::GetNewPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding = { NG::CalcLength(0.0), NG::CalcLength(0.0), NG::CalcLength(0.0),
        NG::CalcLength(0.0) };
    if (isLabelButton_) {
        auto buttonTheme = GetTheme<ButtonTheme>();
        auto defaultPadding = buttonTheme->GetPadding();
        padding = { NG::CalcLength(defaultPadding.Left()), NG::CalcLength(defaultPadding.Right()),
            NG::CalcLength(defaultPadding.Top()), NG::CalcLength(defaultPadding.Bottom()) };
    }
    if (info[0]->IsObject()) {
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension leftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), leftDimen)) {
            left = leftDimen;
        }
        CalcDimension rightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), rightDimen)) {
            right = rightDimen;
        }
        CalcDimension topDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), topDimen)) {
            top = topDimen;
        }
        CalcDimension bottomDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottomDimen)) {
            bottom = bottomDimen;
        }
        if (left.has_value() || right.has_value() || top.has_value() || bottom.has_value()) {
            padding = SetPaddings(top, bottom, left, right);
            return padding;
        }
    }

    CalcDimension length(-1);
    ParseJsDimensionVp(info[0], length);
    if (length.IsNonNegative()) {
        padding.SetEdges(NG::CalcLength(length));
    }
    return padding;
}

NG::PaddingProperty JSButton::SetPaddings(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left =
                NG::CalcLength(left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right =
                NG::CalcLength(right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }

    return paddings;
}

void JSButton::JsOnClick(const JSCallbackInfo& info)
{
    LOGD("JSButton JsOnClick");
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        LOGD("JsOnClick callback is undefined");
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return;
    }
    if (!info[0]->IsFunction()) {
        LOGE("OnClick parameter need a function.");
        return;
    }

    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(info);
    };

    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(*info);
    };

    ButtonModel::GetInstance()->OnClick(std::move(onTap), std::move(onClick));
}

void JSButton::JsBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color backgroundColor;
    bool colorFlag = ParseJsColor(info[0], backgroundColor);
    if (!colorFlag) {
        auto buttonTheme = GetTheme<ButtonTheme>();
        if (buttonTheme) {
            backgroundColor = buttonTheme->GetBgColor();
        }
    }

    ButtonModel::GetInstance()->BackgroundColor(backgroundColor, colorFlag);
    info.ReturnSelf();
}

void JSButton::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    CalcDimension value = GetSizeValue(info);
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }

    ButtonModel::GetInstance()->SetWidth(value);
}

void JSButton::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    CalcDimension value = GetSizeValue(info);
    if (LessNotEqual(value.Value(), 0.0)) {
        return;
    }

    ButtonModel::GetInstance()->SetHeight(value);
}

void JSButton::JsAspectRatio(const JSCallbackInfo& info)
{
    JSViewAbstract::JsAspectRatio(info);
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        return;
    }

    ButtonModel::GetInstance()->SetAspectRatio(value);
}

void JSButton::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 0) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    std::optional<CalcDimension> widthInfo;
    std::optional<CalcDimension> heightInfo;
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    CalcDimension width;
    if (ParseJsDimensionVp(sizeObj->GetProperty("width"), width)) {
        widthInfo = width;
    }
    CalcDimension height;
    if (ParseJsDimensionVp(sizeObj->GetProperty("height"), height)) {
        heightInfo = height;
    }

    ButtonModel::GetInstance()->SetSize(widthInfo, heightInfo);
}

void JSButton::JsRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension radius;
    ParseJsDimensionVp(info[0], radius);
    ButtonModel::GetInstance()->SetBorderRadius(radius);
    HandleDifferentRadius(info[0]);
}

void JSButton::JsBorder(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorder(info);
    if (!info[0]->IsObject()) {
        LOGE("args is not a object. %s", info[0]->ToString().c_str());
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    CalcDimension borderRadius;
    auto valueRadius = object->GetProperty("radius");
    ParseJsDimensionVp(valueRadius, borderRadius);
    ButtonModel::GetInstance()->SetBorderRadius(borderRadius);
    HandleDifferentRadius(valueRadius);
}

CalcDimension JSButton::GetSizeValue(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return { -1.0 };
    }
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return { -1.0 };
    }
    return value;
}

void JSButton::JsHoverEffect(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        LOGE("The arg is not a number");
        return;
    }

    auto hoverEffectNum = info[0]->ToNumber<int32_t>();
    ButtonModel::GetInstance()->SetHoverEffect(hoverEffectNum);
}
} // namespace OHOS::Ace::Framework
