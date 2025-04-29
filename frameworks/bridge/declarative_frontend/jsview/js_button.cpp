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
#include <limits>
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components/button/button_component.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_button_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/button_model_impl.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {
ButtonModel* ButtonModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ButtonModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ButtonModelNG instance;
        return &instance;
    } else {
        static Framework::ButtonModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

constexpr int32_t UNKNOWN_RESOURCE_TYPE = -1;

bool ParseJsLengthMetrics(const JSRef<JSObject>& obj, std::optional<CalcDimension>& result)
{
    auto value = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
    if (!value->IsNumber()) {
        return false;
    }
    auto unit = DimensionUnit::VP;
    auto jsUnit = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::UNIT));
    if (jsUnit->IsNumber()) {
        unit = static_cast<DimensionUnit>(jsUnit->ToNumber<int32_t>());
    }
    CalcDimension dimension(value->ToNumber<double>(), unit);
    result = dimension;
    return true;
}

void GetBorderRadiusByLengthMetrics(
    const char* key, const JSRef<JSObject>& object, std::optional<CalcDimension>& radius)
{
    if (object->HasProperty(key) && object->GetProperty(key)->IsObject()) {
        JSRef<JSObject> startObj = JSRef<JSObject>::Cast(object->GetProperty(key));
        ParseJsLengthMetrics(startObj, radius);
    }
}

void GetNormalBorderRadius(const char* key, const JSRef<JSObject>& object, std::optional<CalcDimension>& radius)
{
    CalcDimension calcDimension;
    auto jsVal = object->GetProperty(key);
    if (!jsVal->IsUndefined() && JSViewAbstract::ParseJsDimensionVp(jsVal, calcDimension)) {
        radius = calcDimension;
    }
}

bool ParseAllBorderRadius(const JSRef<JSObject>& object, std::optional<CalcDimension>& topLeft,
    std::optional<CalcDimension>& topRight, std::optional<CalcDimension>& bottomLeft,
    std::optional<CalcDimension>& bottomRight)
{
    if (object->HasProperty("topStart") || object->HasProperty("topEnd") || object->HasProperty("bottomStart") ||
        object->HasProperty("bottomEnd")) {
        GetBorderRadiusByLengthMetrics("topStart", object, topLeft);
        GetBorderRadiusByLengthMetrics("topEnd", object, topRight);
        GetBorderRadiusByLengthMetrics("bottomStart", object, bottomLeft);
        GetBorderRadiusByLengthMetrics("bottomEnd", object, bottomRight);
        return true;
    }
    GetNormalBorderRadius("topLeft", object, topLeft);
    GetNormalBorderRadius("topRight", object, topRight);
    GetNormalBorderRadius("bottomLeft", object, bottomLeft);
    GetNormalBorderRadius("bottomRight", object, bottomRight);
    return false;
}
} // namespace
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };

bool JSButton::isLabelButton_ = false;

void JSButton::SetFontSize(const JSCallbackInfo& info)
{
    auto buttonTheme = GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    CalcDimension fontSize = buttonTheme->GetTextStyle().GetFontSize();
    if (ParseJsDimensionVpNG(info[0], fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        ParseJsDimensionFp(info[0], fontSize);
    } else {
        fontSize = buttonTheme->GetTextStyle().GetFontSize();
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
        return;
    }

    ButtonModel::GetInstance()->SetFontStyle(fontStyles[value]);
}

void JSButton::SetFontFamily(const JSCallbackInfo& info)
{
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies) || fontFamilies.empty()) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto textTheme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(textTheme);
        fontFamilies = textTheme->GetTextStyle().GetFontFamilies();
    }

    ButtonModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSButton::SetTextColor(const JSCallbackInfo& info)
{
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
        textColor = buttonTheme->GetTextStyle().GetTextColor();
    }

    ButtonModel::GetInstance()->SetFontColor(textColor);
}

void JSButton::SetType(const JSCallbackInfo& info)
{
    int32_t value = static_cast<int32_t>(ButtonType::CAPSULE);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        value = static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE);
    }
    if (info[0]->IsNumber()) {
        value = info[0]->ToNumber<int32_t>();
    }
    if ((ButtonType)value == ButtonType::CAPSULE || (ButtonType)value == ButtonType::CIRCLE ||
        (ButtonType)value == ButtonType::ARC || (ButtonType)value == ButtonType::NORMAL ||
        (ButtonType)value == ButtonType::ROUNDED_RECTANGLE) {
        ButtonModel::GetInstance()->SetType(value);
    }
}

void JSButton::SetButtonStyle(const JSCallbackInfo& info)
{
    int32_t value = static_cast<int32_t>(ButtonStyleMode::EMPHASIZE);
    if (info[0]->IsNumber()) {
        auto valueT = info[0]->ToNumber<int32_t>();
        if (valueT >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            valueT <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            value = valueT;
        }
    }
    auto buttonStyleMode = static_cast<ButtonStyleMode>(value);
    if (!JSButtonTheme::ApplyTheme(buttonStyleMode, isLabelButton_)) {
        ButtonModel::GetInstance()->SetButtonStyle(buttonStyleMode);
    }
}

void JSButton::SetControlSize(const JSCallbackInfo& info)
{
    int32_t value = static_cast<int32_t>(ControlSize::NORMAL);
    if (info[0]->IsNumber()) {
        auto valueT = info[0]->ToNumber<int32_t>();
        if (valueT >= static_cast<int32_t>(ControlSize::SMALL) && valueT <= static_cast<int32_t>(ControlSize::NORMAL)) {
            value = valueT;
        }
    }
    ButtonModel::GetInstance()->SetControlSize(static_cast<ControlSize>(value));
}

void JSButton::SetRole(const JSCallbackInfo& info)
{
    int32_t value = static_cast<int32_t>(ButtonRole::NORMAL);
    if (info[0]->IsNumber()) {
        auto valueT = info[0]->ToNumber<int32_t>();
        if (valueT >= static_cast<int32_t>(ButtonRole::NORMAL) && valueT <= static_cast<int32_t>(ButtonRole::ERROR)) {
            value = valueT;
        }
    }
    auto buttonRole = static_cast<ButtonRole>(value);
    if (!JSButtonTheme::ApplyTheme(buttonRole, isLabelButton_)) {
        ButtonModel::GetInstance()->SetRole(buttonRole);
    }
}

void JSButton::SetMinFontScale(const JSCallbackInfo& info)
{
    double minFontScale;
    if (info.Length() < 1 || !ParseJsDouble(info[0], minFontScale)) {
        return;
    }
    if (LessOrEqual(minFontScale, 0.0f)) {
        ButtonModel::GetInstance()->SetMinFontScale(0.0f);
        return;
    }
    if (GreatOrEqual(minFontScale, 1.0f)) {
        ButtonModel::GetInstance()->SetMinFontScale(1.0f);
        return;
    }
    ButtonModel::GetInstance()->SetMinFontScale(static_cast<float>(minFontScale));
}

void JSButton::SetMaxFontScale(const JSCallbackInfo& info)
{
    double maxFontScale;
    if (info.Length() < 1 || !ParseJsDouble(info[0], maxFontScale)) {
        return;
    }
    if (LessOrEqual(maxFontScale, 1.0f)) {
        ButtonModel::GetInstance()->SetMaxFontScale(1.0f);
        return;
    }
    ButtonModel::GetInstance()->SetMaxFontScale(static_cast<float>(maxFontScale));
}

void JSButton::SetStateEffect(const JSCallbackInfo& info)
{
    bool value = info[0]->IsBoolean() ? info[0]->ToBoolean() : true;
    ButtonModel::GetInstance()->SetStateEffect(value);
}

void JSButton::GetFontContent(JSRef<JSVal>& font, ButtonParameters& buttonParameters)
{
    if (font->IsNull() || !font->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(font);
    JSRef<JSVal> size = obj->GetProperty("size");
    CalcDimension fontSize;
    if (ParseJsDimensionFp(size, fontSize)) {
        buttonParameters.fontSize = fontSize;
    }

    JSRef<JSVal> weight = obj->GetProperty("weight");
    if (weight->IsString() || weight->IsNumber()) {
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
        return;
    }

    ButtonParameters buttonParameters;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> overflowValue = obj->GetProperty("overflow");
    buttonParameters.textOverflow = TextOverflow::ELLIPSIS;
    if (!overflowValue->IsNull() && overflowValue->IsNumber()) {
        auto overflow = overflowValue->ToNumber<int32_t>();
        if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
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
    GetFontContent(font, buttonParameters);

    CompleteParameters(buttonParameters);
    ButtonModel::GetInstance()->SetLabelStyle(buttonParameters);
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
    JSClass<JSButton>::StaticMethod("stateEffect", &JSButton::SetStateEffect);
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
    JSClass<JSButton>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSButton>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSButton>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSButton>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSButton>::StaticMethod("size", &JSButton::JsSize);
    JSClass<JSButton>::StaticMethod("padding", &JSButton::JsPadding);
    JSClass<JSButton>::StaticMethod("buttonStyle", &JSButton::SetButtonStyle);
    JSClass<JSButton>::StaticMethod("controlSize", &JSButton::SetControlSize);
    JSClass<JSButton>::StaticMethod("role", &JSButton::SetRole);
    JSClass<JSButton>::StaticMethod("createWithLabel", &JSButton::CreateWithLabel, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("createWithChild", &JSButton::CreateWithChild, MethodOptions::NONE);
    JSClass<JSButton>::StaticMethod("minFontScale", &JSButton::SetMinFontScale);
    JSClass<JSButton>::StaticMethod("maxFontScale", &JSButton::SetMaxFontScale);
    JSClass<JSButton>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSButton::CreateWithLabel(const JSCallbackInfo& info)
{
    std::list<RefPtr<Component>> buttonChildren;
    CreateWithPara para = ParseCreatePara(info, true);
    ButtonModel::GetInstance()->CreateWithLabel(para, buttonChildren);
    ButtonModel::GetInstance()->Create(para, buttonChildren);
    isLabelButton_ = true;
    auto buttonRole = para.buttonRole.value_or(ButtonRole::NORMAL);
    auto buttonStyleMode = para.buttonStyleMode.value_or(ButtonStyleMode::EMPHASIZE);
    JSButtonTheme::ApplyTheme(buttonRole, buttonStyleMode, isLabelButton_);
    ButtonModel::GetInstance()->SetCreateWithLabel(true);
}

void JSButton::CreateWithChild(const JSCallbackInfo& info)
{
    CreateWithPara para = ParseCreatePara(info, false);
    ButtonModel::GetInstance()->CreateWithChild(para);
    isLabelButton_ = false;
    auto buttonRole = para.buttonRole.value_or(ButtonRole::NORMAL);
    auto buttonStyleMode = para.buttonStyleMode.value_or(ButtonStyleMode::EMPHASIZE);
    JSButtonTheme::ApplyTheme(buttonRole, buttonStyleMode, isLabelButton_);
    ButtonModel::GetInstance()->SetCreateWithLabel(false);
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

    if (info[0]->IsNumber()) {
        CalcDimension edgeValue;
        if (ParseJsDimensionVp(info[0], edgeValue)) {
            padding = Edge(edgeValue);
        }
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        CalcDimension left = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension top = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension right = CalcDimension(0.0, DimensionUnit::VP);
        CalcDimension bottom = CalcDimension(0.0, DimensionUnit::VP);
        if (jsObj->HasProperty("top") || jsObj->HasProperty("bottom") || jsObj->HasProperty("left") ||
            jsObj->HasProperty("right")) {
            ParseJsDimensionVp(jsObj->GetProperty("left"), left);
            ParseJsDimensionVp(jsObj->GetProperty("top"), top);
            ParseJsDimensionVp(jsObj->GetProperty("right"), right);
            ParseJsDimensionVp(jsObj->GetProperty("bottom"), bottom);
        }
        padding = Edge(left, top, right, bottom);
    }

    return padding;
}

NG::PaddingProperty JSButton::GetNewPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding = { NG::CalcLength(0.0), NG::CalcLength(0.0), NG::CalcLength(0.0), NG::CalcLength(0.0),
        std::nullopt, std::nullopt };
    if (isLabelButton_) {
        auto buttonTheme = GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, padding);
        auto defaultPadding = buttonTheme->GetPadding();
        padding = { NG::CalcLength(defaultPadding.Left()), NG::CalcLength(defaultPadding.Right()),
            NG::CalcLength(defaultPadding.Top()), NG::CalcLength(defaultPadding.Bottom()), std::nullopt, std::nullopt };
    }
    if (info[0]->IsObject()) {
        CommonCalcDimension commonCalcDimension;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        JSViewAbstract::ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            return SetPaddings(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
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
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = targetNode](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        JSInteractableView::ReportClickEvent(node);
#endif
    };
    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = targetNode](
                       const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        JSInteractableView::ReportClickEvent(node);
#endif
    };

    double distanceThreshold = std::numeric_limits<double>::infinity();
    if (info.Length() > 1 && info[1]->IsNumber()) {
        distanceThreshold = info[1]->ToNumber<double>();
        distanceThreshold = Dimension(distanceThreshold, DimensionUnit::VP).ConvertToPx();
    }
    ButtonModel::GetInstance()->OnClick(std::move(onTap), std::move(onClick), distanceThreshold);
}

void JSButton::JsBackgroundColor(const JSCallbackInfo& info)
{
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
    double value = 0.0;
    if (!ParseJsDouble(info[0], value)) {
        return;
    }

    ButtonModel::GetInstance()->SetAspectRatio(value);
}

void JSButton::JsSize(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        JSViewAbstract::JsWidth(JSVal::Undefined());
        JSViewAbstract::JsHeight(JSVal::Undefined());
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSViewAbstract::JsWidth(sizeObj->GetProperty("width"));
    JSViewAbstract::JsHeight(sizeObj->GetProperty("height"));
}

void JSButton::JsRadius(const JSCallbackInfo& info)
{
    JsRadius(info[0]);
}

void JSButton::JsRadius(const JSRef<JSVal>& jsValue)
{
    CalcDimension radius;
    if (ParseJsDimensionVpNG(jsValue, radius)) {
        ButtonModel::GetInstance()->SetBorderRadius(radius);
    } else if (jsValue->IsObject() && ((JSRef<JSObject>::Cast(jsValue)->GetPropertyValue<int32_t>(
                                           "type", UNKNOWN_RESOURCE_TYPE)) == UNKNOWN_RESOURCE_TYPE)) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(jsValue);
        std::optional<CalcDimension> radiusTopLeft;
        std::optional<CalcDimension> radiusTopRight;
        std::optional<CalcDimension> radiusBottomLeft;
        std::optional<CalcDimension> radiusBottomRight;
        if (ParseAllBorderRadius(object, radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight)) {
            ButtonModel::GetInstance()->SetLocalizedBorderRadius(
                radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
        } else {
            ButtonModel::GetInstance()->SetBorderRadius(
                radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
        }
    } else {
        ButtonModel::GetInstance()->ResetBorderRadius();
    }
}

void JSButton::JsBorder(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorder(info);
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    CalcDimension borderRadius;
    auto valueRadius = object->GetProperty("radius");
    JsRadius(valueRadius);
}

CalcDimension JSButton::GetSizeValue(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return { -1.0 };
    }
    return value;
}

CreateWithPara JSButton::ParseCreatePara(const JSCallbackInfo& info, bool hasLabel)
{
    std::string label;
    CreateWithPara para;
    para.parseSuccess = false;
    para.optionSetFirst = false;
    if (info.Length() < 1) {
        para.label = label;
        return para;
    }
    uint32_t optionIndex = 0;
    if (hasLabel) {
        para.parseSuccess = ParseJsString(info[0], label);
        if (para.parseSuccess) {
            // resource string
            if (info[0]->IsObject() && JSRef<JSObject>::Cast(info[0])->HasProperty("id")) {
                optionIndex++;
                // string
            } else if (info[0]->IsString()) {
                optionIndex++;
            }
        }
        para.label = label;
    }
    if (optionIndex >= info.Length() || !info[optionIndex]->IsObject()) {
        return para;
    }
    if (optionIndex == 0) {
        para.optionSetFirst = true;
    }
    JSRef<JSObject> optionObj = JSRef<JSObject>::Cast(info[optionIndex]);
    if (optionObj->GetProperty(JSButton::TYPE)->IsNumber()) {
        para.type = static_cast<ButtonType>(optionObj->GetProperty(JSButton::TYPE)->ToNumber<int32_t>());
    }
    if (optionObj->GetProperty(JSButton::STATE_EFFECT)->IsBoolean()) {
        para.stateEffect = optionObj->GetProperty(JSButton::STATE_EFFECT)->ToBoolean();
    }
    if (optionObj->HasProperty(JSButton::BUTTON_STYLE)) {
        para.buttonStyleMode = ButtonStyleMode::EMPHASIZE;
    }
    if (optionObj->GetProperty(JSButton::BUTTON_STYLE)->IsNumber()) {
        auto styleModeIntValue = optionObj->GetProperty(JSButton::BUTTON_STYLE)->ToNumber<int32_t>();
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            para.buttonStyleMode = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }
    if (optionObj->HasProperty(JSButton::CONTROL_SIZE)) {
        para.controlSize = ControlSize::NORMAL;
    }
    if (optionObj->GetProperty(JSButton::CONTROL_SIZE)->IsNumber()) {
        auto controlSizeIntValue = optionObj->GetProperty(JSButton::CONTROL_SIZE)->ToNumber<int32_t>();
        if (controlSizeIntValue >= static_cast<int32_t>(ControlSize::SMALL) &&
            controlSizeIntValue <= static_cast<int32_t>(ControlSize::NORMAL)) {
            para.controlSize = static_cast<ControlSize>(controlSizeIntValue);
        }
    }
    ParseButtonRole(optionObj, para);
    return para;
}

void JSButton::ParseButtonRole(const JSRef<JSObject>& optionObj, CreateWithPara& param)
{
    if (optionObj->HasProperty(JSButton::ROLE)) {
        param.buttonRole = ButtonRole::NORMAL;
    }
    if (optionObj->GetProperty(JSButton::ROLE)->IsNumber()) {
        auto buttonRoleIntValue = optionObj->GetProperty(JSButton::ROLE)->ToNumber<int32_t>();
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            param.buttonRole = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }
}
} // namespace OHOS::Ace::Framework
