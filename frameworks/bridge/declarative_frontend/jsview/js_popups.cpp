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

#include "base/utils/utils.h"
#include "base/utils/string_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_view_context.h"
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/text/span/span_string.h"

#include "bridge/declarative_frontend/jsview/js_popups.h"
#include "bridge/declarative_frontend/style_string/js_span_string.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t PARAMETER_LENGTH_ZERO = 0;
constexpr int32_t PARAMETER_LENGTH_FIRST = 1;
constexpr int32_t PARAMETER_LENGTH_SECOND = 2;
constexpr int32_t PARAMETER_LENGTH_THIRD = 3;
constexpr int NUM_ZERO = 0;
constexpr int NUM_FIRST = 1;
constexpr int NUM_SECOND = 2;
constexpr int32_t TRANSITION_NUM_ZERO = 0;
constexpr int32_t TRANSITION_NUM_TWO = 2;
constexpr uint32_t ON_WILL_DISMISS_FIELD_COUNT = 2;
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
constexpr Dimension ARROW_ZERO_PERCENT_VALUE = 0.0_pct;
constexpr Dimension ARROW_HALF_PERCENT_VALUE = 0.5_pct;
constexpr Dimension ARROW_ONE_HUNDRED_PERCENT_VALUE = 1.0_pct;
const std::string SHEET_HEIGHT_MEDIUM = "medium";
const std::string SHEET_HEIGHT_LARGE = "large";
const std::string SHEET_HEIGHT_AUTO = "auto";
const std::string SHEET_HEIGHT_FITCONTENT = "fit_content";
constexpr int HAPTIC_FEEDBACK_MODE_ENABLED = 1;
constexpr int HAPTIC_FEEDBACK_MODE_AUTO = 2;
const std::vector<HoverModeAreaType> HOVER_MODE_AREA_TYPE = { HoverModeAreaType::TOP_SCREEN,
    HoverModeAreaType::BOTTOM_SCREEN };
}

using DoubleBindCallback = std::function<void(const std::string&)>;

#ifndef WEARABLE_PRODUCT
DoubleBindCallback JSViewPopups::ParseDoubleBindCallback(const JSCallbackInfo& info, const JSRef<JSObject>& callbackObj,
    const char* arrowFuncName)
{
    JSRef<JSVal> arrowFunc = callbackObj->GetProperty(arrowFuncName);
    if (!arrowFunc->IsFunction()) {
        return {};
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(arrowFunc));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        if (param != "true" && param != "false") {
            return;
        }
        PipelineContext::SetCallBackNode(node);
        bool newValue = StringToBool(param);
        JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(newValue));
        func->ExecuteJS(1, &newJSVal);
    };
    return callback;
}

void SetPopupMessageOptions(const JSRef<JSObject> messageOptionsObj, const RefPtr<PopupParam>& popupParam)
{
    auto colorValue = messageOptionsObj->GetProperty("textColor");
    Color textColor;
    if (JSViewAbstract::ParseJsColor(colorValue, textColor)) {
        if (popupParam) {
            popupParam->SetTextColor(textColor);
        }
    }

    auto font = messageOptionsObj->GetProperty("font");
    if (!font->IsNull() && font->IsObject()) {
        JSRef<JSObject> fontObj = JSRef<JSObject>::Cast(font);
        auto fontSizeValue = fontObj->GetProperty(static_cast<int32_t>(ArkUIIndex::SIZE));
        CalcDimension fontSize;
        if (JSViewAbstract::ParseJsDimensionFp(fontSizeValue, fontSize)) {
            if (popupParam && fontSize.IsValid()) {
                popupParam->SetFontSize(fontSize);
            }
        }
        auto fontWeightValue = fontObj->GetProperty(static_cast<int32_t>(ArkUIIndex::WEIGHT));
        if (fontWeightValue->IsString()) {
            if (popupParam) {
                popupParam->SetFontWeight(ConvertStrToFontWeight(fontWeightValue->ToString()));
            }
        }
        auto fontStyleValue = fontObj->GetProperty(static_cast<int32_t>(ArkUIIndex::STYLE));
        if (fontStyleValue->IsNumber()) {
            int32_t value = fontStyleValue->ToNumber<int32_t>();
            if (value < 0 || value >= static_cast<int32_t>(FONT_STYLES.size())) {
                return;
            }
            if (popupParam) {
                popupParam->SetFontStyle(FONT_STYLES[value]);
            }
        }
    }
}

void SetPlacementOnTopVal(const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    JSRef<JSVal> placementOnTopVal = popupObj->GetProperty("placementOnTop");
    if (placementOnTopVal->IsBoolean() && popupParam) {
        popupParam->SetPlacement(placementOnTopVal->ToBoolean() ? Placement::TOP : Placement::BOTTOM);
    }
}

bool IsPopupCreated()
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(targetNode, false);
    auto targetId = targetNode->GetId();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_RETURN(context, false);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    auto popupInfo = overlayManager->GetPopupInfo(targetId);
    if (popupInfo.popupId == -1 || !popupInfo.popupNode) {
        return false;
    }
    return true;
}

ShadowStyle GetPopupDefaultShadowStyle()
{
    auto shadowStyle = ShadowStyle::OuterDefaultMD;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, shadowStyle);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, shadowStyle);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, shadowStyle);
    return popupTheme->GetPopupShadowStyle();
}

static void GetBlurStyleFromTheme(const RefPtr<PopupParam>& popupParam)
{
    CHECK_NULL_VOID(popupParam);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(theme);
    auto blurStyle = static_cast<BlurStyle>(theme->GetPopupBackgroundBlurStyle());
    popupParam->SetBlurStyle(blurStyle);
}

void SetBorderLinearGradientDirection(const JSRef<JSObject>& obj,
    PopupLinearGradientProperties& popupBorberLinearGradient)
{
    popupBorberLinearGradient.popupDirection = GradientDirection::BOTTOM;
    auto directionValue = obj->GetProperty("direction");
    if (directionValue->IsNumber()) {
        auto gradientDirection = directionValue->ToNumber<int32_t>();
        if (gradientDirection >= static_cast<int32_t>(GradientDirection::LEFT) &&
            gradientDirection <= static_cast<int32_t>(GradientDirection::END_TO_START)) {
            popupBorberLinearGradient.popupDirection = static_cast<GradientDirection>(gradientDirection);
        }
    }
}

void ParseGradientColor(const JSRef<JSArray>& colorArray, PopupGradientColor& gradientColor)
{
    Color gradientColorItem;
    auto colorVal = colorArray->GetValueAt(0);
    if (JSViewAbstract::ParseJsColor(colorVal, gradientColorItem)) {
        gradientColor.gradientColor = gradientColorItem;
    }
    if (colorArray->GetValueAt(1)->IsNumber()) {
        gradientColor.gradientNumber = colorArray->GetValueAt(1)->ToNumber<double>();
    }
}

void SetBorderLinearGradientColors(const JSRef<JSObject>& obj,
    PopupLinearGradientProperties& popupBorberLinearGradient)
{
    auto colorsValues = obj->GetProperty("colors");
    if (!colorsValues->IsArray()) {
        return;
    }
    auto colorsArray = JSRef<JSArray>::Cast(colorsValues);
    for (size_t i = 0; i < colorsArray->Length(); i++) {
        auto colorInfo = colorsArray->GetValueAt(i);
        if (!colorInfo->IsArray()) {
            continue;
        }
        auto colorArray = JSRef<JSArray>::Cast(colorInfo);
        PopupGradientColor gradientColor;
        ParseGradientColor(colorArray, gradientColor);
        popupBorberLinearGradient.gradientColors.push_back(gradientColor);
    }
}

void SetPopupBorderWidthInfo(const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam,
    const char* borderWidthParam)
{
    std::string outlineWidth = "outlineWidth";
    auto popupBorderWidthVal = popupObj->GetProperty(borderWidthParam);
    if (popupBorderWidthVal->IsNull()) {
        return;
    }
    CalcDimension popupBorderWidth;
    if (!JSViewAbstract::ParseJsDimensionVp(popupBorderWidthVal, popupBorderWidth)) {
        return;
    }
    if (popupBorderWidth.Value() < 0) {
        return;
    }
    if (borderWidthParam == outlineWidth) {
        popupParam->SetOutlineWidth(popupBorderWidth);
    } else {
        popupParam->SetInnerBorderWidth(popupBorderWidth);
    }
}

void SetPopupBorderInfo(const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam,
    const char* borderWidthParam, const char* borderColorParam)
{
    std::string outlineLinearGradient = "outlineLinearGradient";
    PopupLinearGradientProperties popupBorberLinearGradient;
    auto borderLinearGradientVal = popupObj->GetProperty(borderColorParam);
    if (borderLinearGradientVal->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(borderLinearGradientVal);
        SetBorderLinearGradientDirection(obj, popupBorberLinearGradient);
        SetBorderLinearGradientColors(obj, popupBorberLinearGradient);
        if (borderColorParam == outlineLinearGradient) {
            popupParam->SetOutlineLinearGradient(popupBorberLinearGradient);
        } else {
            popupParam->SetInnerBorderLinearGradient(popupBorberLinearGradient);
        }
    }
    SetPopupBorderWidthInfo(popupObj, popupParam, borderWidthParam);
}

void ParsePopupCommonParam(const JSCallbackInfo& info, const JSRef<JSObject>& popupObj,
    const RefPtr<PopupParam>& popupParam, const RefPtr<NG::FrameNode> popupTargetNode = nullptr)
{
    auto arrowOffset = popupObj->GetProperty("arrowOffset");
    CalcDimension offset;
    if (JSViewAbstract::ParseJsDimensionVp(arrowOffset, offset)) {
        if (popupParam) {
            popupParam->SetArrowOffset(offset);
        }
    }

    auto arrowPointPosition = popupObj->GetProperty("arrowPointPosition");
    if (arrowPointPosition->IsString()) {
        char* pEnd = nullptr;
        auto arrowString = arrowPointPosition->ToString();
        std::strtod(arrowString.c_str(), &pEnd);
        if (pEnd != nullptr) {
            if (std::strcmp(pEnd, "Start") == 0) {
                offset = ARROW_ZERO_PERCENT_VALUE;
            }
            if (std::strcmp(pEnd, "Center") == 0) {
                offset = ARROW_HALF_PERCENT_VALUE;
            }
            if (std::strcmp(pEnd, "End") == 0) {
                offset = ARROW_ONE_HUNDRED_PERCENT_VALUE;
            }
            if (popupParam) {
                popupParam->SetArrowOffset(offset);
            }
        }
    }

    auto targetSpace = popupObj->GetProperty("targetSpace");
    if (!targetSpace->IsNull()) {
        CalcDimension space;
        if (JSViewAbstract::ParseJsDimensionVp(targetSpace, space)) {
            if (popupParam) {
                popupParam->SetTargetSpace(space);
            }
        }
    }

    JSRef<JSVal> showInSubWindowValue = popupObj->GetProperty("showInSubWindow");
    if (showInSubWindowValue->IsBoolean()) {
        bool showInSubBoolean = showInSubWindowValue->ToBoolean();
#if defined(PREVIEW)
        if (showInSubBoolean) {
            LOGI("[Engine Log] Unable to use the SubWindow in the Previewer. Use normal type instead.");
            showInSubBoolean = false;
        }
#endif
        if (popupParam) {
            popupParam->SetShowInSubWindow(showInSubBoolean);
        }
    }

    auto placementValue = popupObj->GetProperty("placement");
    if (placementValue->IsNumber()) {
        auto placement = placementValue->ToNumber<int32_t>();
        if (placement >= 0 && placement < static_cast<int32_t>(Placement::NONE)) {
            popupParam->SetPlacement(static_cast<Placement>(placement));
        }
    } else {
        SetPlacementOnTopVal(popupObj, popupParam);
    }

    auto enableArrowValue = popupObj->GetProperty("enableArrow");
    if (enableArrowValue->IsBoolean()) {
        popupParam->SetEnableArrow(enableArrowValue->ToBoolean());
    }

    auto enableHoverModeValue = popupObj->GetProperty("enableHoverMode");
    if (enableHoverModeValue->IsBoolean()) {
        popupParam->SetEnableHoverMode(enableHoverModeValue->ToBoolean());
    }

    auto followTransformOfTargetValue = popupObj->GetProperty("followTransformOfTarget");
    if (followTransformOfTargetValue->IsBoolean()) {
        popupParam->SetFollowTransformOfTarget(followTransformOfTargetValue->ToBoolean());
    }

    JSRef<JSVal> maskValue = popupObj->GetProperty("mask");
    if (maskValue->IsBoolean()) {
        if (popupParam) {
            popupParam->SetBlockEvent(maskValue->ToBoolean());
        }
    }
    if (maskValue->IsObject()) {
        auto maskObj = JSRef<JSObject>::Cast(maskValue);
        auto colorValue = maskObj->GetProperty("color");
        Color maskColor;
        if (JSViewAbstract::ParseJsColor(colorValue, maskColor)) {
            popupParam->SetMaskColor(maskColor);
        }
    }

    JSRef<JSVal> onStateChangeVal = popupObj->GetProperty("onStateChange");
    if (onStateChangeVal->IsFunction()) {
        std::vector<std::string> keys = { "isVisible" };
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onStateChangeVal));
        WeakPtr<NG::FrameNode> targetNode = nullptr;
        if (popupTargetNode) {
            targetNode = AceType::WeakClaim(AceType::RawPtr(popupTargetNode));
        } else {
            targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        }
        if (popupParam) {
            auto onStateChangeCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), keys,
                                             node = targetNode](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("Popup.onStateChange");
                PipelineContext::SetCallBackNode(node);
                func->Execute(keys, param);
            };
            popupParam->SetOnStateChange(onStateChangeCallback);
        }
    }

    auto offsetVal = popupObj->GetProperty("offset");
    if (offsetVal->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetVal);
        auto xVal = offsetObj->GetProperty("x");
        auto yVal = offsetObj->GetProperty("y");
        Offset popupOffset;
        CalcDimension dx;
        CalcDimension dy;
        if (JSViewAbstract::ParseJsDimensionVp(xVal, dx)) {
            popupOffset.SetX(dx.ConvertToPx());
        }
        if (JSViewAbstract::ParseJsDimensionVp(yVal, dy)) {
            popupOffset.SetY(dy.ConvertToPx());
        }
        if (popupParam) {
            popupParam->SetTargetOffset(popupOffset);
        }
    }

    Color backgroundColor;
    auto popupColorVal = popupObj->GetProperty("popupColor");
    if (JSViewAbstract::ParseJsColor(popupColorVal, backgroundColor)) {
        popupParam->SetBackgroundColor(backgroundColor);
    }

    auto autoCancelVal = popupObj->GetProperty("autoCancel");
    if (autoCancelVal->IsBoolean()) {
        popupParam->SetHasAction(!autoCancelVal->ToBoolean());
    }

    auto childWidthVal = popupObj->GetProperty("width");
    if (!childWidthVal->IsNull()) {
        CalcDimension width;
        if (JSViewAbstract::ParseJsDimensionVp(childWidthVal, width)) {
            if (width.Value() > 0) {
                popupParam->SetChildWidth(width);
            }
        }
    }

    auto arrowWidthVal = popupObj->GetProperty("arrowWidth");
    if (!arrowWidthVal->IsNull()) {
        bool setError = true;
        CalcDimension arrowWidth;
        if (JSViewAbstract::ParseJsDimensionVp(arrowWidthVal, arrowWidth)) {
            if (arrowWidth.Value() > 0 && arrowWidth.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowWidth(arrowWidth);
                setError = false;
            }
        }
        popupParam->SetErrorArrowWidth(setError);
    }

    auto arrowHeightVal = popupObj->GetProperty("arrowHeight");
    if (!arrowHeightVal->IsNull()) {
        bool setError = true;
        CalcDimension arrowHeight;
        if (JSViewAbstract::ParseJsDimensionVp(arrowHeightVal, arrowHeight)) {
            if (arrowHeight.Value() > 0 && arrowHeight.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowHeight(arrowHeight);
                setError = false;
            }
        }
        popupParam->SetErrorArrowHeight(setError);
    }

    auto radiusVal = popupObj->GetProperty("radius");
    if (!radiusVal->IsNull()) {
        bool setError = true;
        CalcDimension radius;
        if (JSViewAbstract::ParseJsDimensionVp(radiusVal, radius)) {
            if (radius.Value() >= 0) {
                popupParam->SetRadius(radius);
                setError = false;
            }
        }
        popupParam->SetErrorRadius(setError);
    }

    auto defaultShadowStyle = GetPopupDefaultShadowStyle();
    Shadow shadow;
    auto shadowVal = popupObj->GetProperty("shadow");
    if (shadowVal->IsObject() || shadowVal->IsNumber()) {
        auto ret = JSViewAbstract::ParseShadowProps(shadowVal, shadow);
        if (!ret) {
            if (!(popupParam->GetIsPartialUpdate().has_value() && popupParam->GetIsPartialUpdate().value())) {
                JSViewAbstract::GetShadowFromTheme(defaultShadowStyle, shadow);
                popupParam->SetShadow(shadow);
            }
        } else {
            popupParam->SetShadow(shadow);
        }
    } else {
        if (!(popupParam->GetIsPartialUpdate().has_value() && popupParam->GetIsPartialUpdate().value())) {
            JSViewAbstract::GetShadowFromTheme(defaultShadowStyle, shadow);
            popupParam->SetShadow(shadow);
        }
    }

    auto blurStyleValue = popupObj->GetProperty("backgroundBlurStyle");
    if (blurStyleValue->IsNumber()) {
        auto blurStyle = blurStyleValue->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            popupParam->SetBlurStyle(static_cast<BlurStyle>(blurStyle));
        } else {
            if (!(popupParam->GetIsPartialUpdate().has_value() && popupParam->GetIsPartialUpdate().value())) {
                GetBlurStyleFromTheme(popupParam);
            }
        }
    } else {
        if (!(popupParam->GetIsPartialUpdate().has_value() && popupParam->GetIsPartialUpdate().value())) {
            GetBlurStyleFromTheme(popupParam);
        }
    }

    auto popupTransition = popupObj->GetProperty("transition");
    if (popupTransition->IsObject()) {
        popupParam->SetHasTransition(true);
        auto obj = JSRef<JSObject>::Cast(popupTransition);
        if (popupTargetNode) {
            auto effects = JSViewAbstract::ParseChainedTransition(obj, info.GetExecutionContext(), popupTargetNode);
            popupParam->SetTransitionEffects(effects);
        } else {
            auto effects = JSViewAbstract::ParseChainedTransition(obj, info.GetExecutionContext());
            popupParam->SetTransitionEffects(effects);
        }
    }
    auto keyboardAvoidMode = popupObj->GetProperty("keyboardAvoidMode");
    if (keyboardAvoidMode->IsNumber()) {
        auto popupKeyboardAvoidMode = keyboardAvoidMode->ToNumber<int32_t>();
        if (popupKeyboardAvoidMode >= static_cast<int>(PopupKeyboardAvoidMode::DEFAULT) &&
            popupKeyboardAvoidMode <= static_cast<int>(PopupKeyboardAvoidMode::NONE)) {
            popupParam->SetKeyBoardAvoidMode(static_cast<PopupKeyboardAvoidMode>(popupKeyboardAvoidMode));
        }
    }

    const char* outlineLinearGradient = "outlineLinearGradient";
    const char* outlineWidth = "outlineWidth";
    SetPopupBorderInfo(popupObj, popupParam, outlineWidth, outlineLinearGradient);
    const char* borderLinearGradient = "borderLinearGradient";
    const char* borderWidth = "borderWidth";
    SetPopupBorderInfo(popupObj, popupParam, borderWidth, borderLinearGradient);
}

void ParsePopupParam(const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    ParsePopupCommonParam(info, popupObj, popupParam);
    JSRef<JSVal> messageVal = popupObj->GetProperty("message");
    if (popupParam) {
        popupParam->SetMessage(messageVal->ToString());
    }

    auto messageOptions = popupObj->GetProperty("messageOptions");
    JSRef<JSObject> messageOptionsObj;
    if (!messageOptions->IsNull() && messageOptions->IsObject()) {
        messageOptionsObj = JSRef<JSObject>::Cast(messageOptions);
        SetPopupMessageOptions(messageOptionsObj, popupParam);
    }

    JSRef<JSVal> primaryButtonVal = popupObj->GetProperty("primaryButton");
    if (primaryButtonVal->IsObject()) {
        ButtonProperties properties;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(primaryButtonVal);
        JSRef<JSVal> value = obj->GetProperty("value");
        if (value->IsString()) {
            properties.value = value->ToString();
        }

        JSRef<JSVal> actionValue = obj->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(actionValue));
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            if (popupParam) {
                auto clickCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc),
                                         node = targetNode](GestureEvent& info) {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("primaryButton.action");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute(info);
                };
                properties.action = AceType::MakeRefPtr<NG::ClickEvent>(clickCallback);
            }
        }
        properties.showButton = true;
        if (popupParam) {
            popupParam->SetPrimaryButtonProperties(properties);
        }
    }

    JSRef<JSVal> secondaryButtonVal = popupObj->GetProperty("secondaryButton");
    if (secondaryButtonVal->IsObject()) {
        ButtonProperties properties;
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(secondaryButtonVal);
        JSRef<JSVal> value = obj->GetProperty("value");
        if (value->IsString()) {
            properties.value = value->ToString();
        }

        JSRef<JSVal> actionValue = obj->GetProperty("action");
        if (actionValue->IsFunction()) {
            auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(actionValue));
            auto targetNode =
                AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            if (popupParam) {
                auto clickCallback = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc),
                                         node = targetNode](GestureEvent& info) {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("secondaryButton.action");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute(info);
                };
                properties.action = AceType::MakeRefPtr<NG::ClickEvent>(clickCallback);
            }
        }
        properties.showButton = true;
        if (popupParam) {
            popupParam->SetSecondaryButtonProperties(properties);
        }
    }
}

void ParseCustomPopupParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    auto builderValue = popupObj->GetProperty("builder");
    if (!builderValue->IsObject()) {
        return;
    }
    if (!builderValue->IsFunction()) {
        JSRef<JSObject> builderObj;
        builderObj = JSRef<JSObject>::Cast(builderValue);
        auto builder = builderObj->GetProperty("builder");
        if (!builder->IsFunction()) {
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        if (!builderFunc) {
            return;
        }
    }
    if (popupParam) {
        popupParam->SetUseCustomComponent(true);
    }

    auto focusableValue = popupObj->GetProperty("focusable");
    if (focusableValue->IsBoolean()) {
        popupParam->SetFocusable(focusableValue->ToBoolean());
    }

    ParsePopupCommonParam(info, popupObj, popupParam);
}

void ParseTipsParam(const JSRef<JSObject>& tipsObj, const RefPtr<PopupParam>& tipsParam)
{
    CHECK_NULL_VOID(tipsParam);
    auto appearingTimeVal = tipsObj->GetProperty("appearingTime");
    if (appearingTimeVal->IsNumber()) {
        auto appearingTime = appearingTimeVal->ToNumber<int32_t>();
        if (appearingTime >= 0) {
            tipsParam->SetAppearingTime(appearingTime);
        }
    }

    auto disappearingTimeVal = tipsObj->GetProperty("disappearingTime");
    if (disappearingTimeVal->IsNumber()) {
        auto disappearingTime = disappearingTimeVal->ToNumber<int32_t>();
        if (disappearingTime >= 0) {
            tipsParam->SetDisappearingTime(disappearingTime);
        }
    }

    auto appearingTimeWithContinuousOperationVal = tipsObj->GetProperty("appearingTimeWithContinuousOperation");
    if (appearingTimeWithContinuousOperationVal->IsNumber()) {
        auto appearingTimeWithContinuousOperation = appearingTimeWithContinuousOperationVal->ToNumber<int32_t>();
        if (appearingTimeWithContinuousOperation >= 0) {
            tipsParam->SetAppearingTimeWithContinuousOperation(appearingTimeWithContinuousOperation);
        }
    }

    auto disappearingTimeWithContinuousOperationVal = tipsObj->GetProperty("disappearingTimeWithContinuousOperation");
    if (disappearingTimeWithContinuousOperationVal->IsNumber()) {
        auto disappearingTimeWithContinuousOperation = disappearingTimeWithContinuousOperationVal->ToNumber<int32_t>();
        if (disappearingTimeWithContinuousOperation >= 0) {
            tipsParam->SetDisappearingTimeWithContinuousOperation(disappearingTimeWithContinuousOperation);
        }
    }

    auto enableArrowValue = tipsObj->GetProperty("enableArrow");
    if (enableArrowValue->IsBoolean()) {
        tipsParam->SetEnableArrow(enableArrowValue->ToBoolean());
    }
    tipsParam->SetBlockEvent(false);
    tipsParam->SetTipsFlag(true);
    tipsParam->SetShowInSubWindow(true);
    tipsParam->SetKeyBoardAvoidMode(PopupKeyboardAvoidMode::DEFAULT);
}

void ParseTipsArrowPositionParam(const JSRef<JSObject>& tipsObj, const RefPtr<PopupParam>& tipsParam)
{
    CalcDimension offset;
    auto arrowPointPosition = tipsObj->GetProperty("arrowPointPosition");
    if (arrowPointPosition->IsString()) {
        char* pEnd = nullptr;
        auto arrowString = arrowPointPosition->ToString();
        std::strtod(arrowString.c_str(), &pEnd);
        if (pEnd != nullptr) {
            if (std::strcmp(pEnd, "Start") == 0) {
                offset = ARROW_ZERO_PERCENT_VALUE;
            }
            if (std::strcmp(pEnd, "Center") == 0) {
                offset = ARROW_HALF_PERCENT_VALUE;
            }
            if (std::strcmp(pEnd, "End") == 0) {
                offset = ARROW_ONE_HUNDRED_PERCENT_VALUE;
            }
            if (tipsParam) {
                tipsParam->SetArrowOffset(offset);
            }
        }
    }
}

void ParseTipsArrowSizeParam(const JSRef<JSObject>& tipsObj, const RefPtr<PopupParam>& tipsParam)
{
    auto arrowWidthVal = tipsObj->GetProperty("arrowWidth");
    if (!arrowWidthVal->IsNull()) {
        bool setError = true;
        CalcDimension arrowWidth;
        if (JSViewAbstract::ParseJsDimensionVp(arrowWidthVal, arrowWidth)) {
            if (arrowWidth.Value() > 0 && arrowWidth.Unit() != DimensionUnit::PERCENT) {
                tipsParam->SetArrowWidth(arrowWidth);
                setError = false;
            }
        }
        tipsParam->SetErrorArrowWidth(setError);
    }

    auto arrowHeightVal = tipsObj->GetProperty("arrowHeight");
    if (!arrowHeightVal->IsNull()) {
        bool setError = true;
        CalcDimension arrowHeight;
        if (JSViewAbstract::ParseJsDimensionVp(arrowHeightVal, arrowHeight)) {
            if (arrowHeight.Value() > 0 && arrowHeight.Unit() != DimensionUnit::PERCENT) {
                tipsParam->SetArrowHeight(arrowHeight);
                setError = false;
            }
        }
        tipsParam->SetErrorArrowHeight(setError);
    }
}
#endif

uint32_t ParseBindContextMenuShow(const JSCallbackInfo& info, NG::MenuParam& menuParam)
{
    size_t builderIndex = 0;
    if (info[0]->IsBoolean()) {
        menuParam.isShow = info[0]->ToBoolean();
        menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
        menuParam.placement = Placement::BOTTOM_LEFT;
        builderIndex = 1;
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(info[0]);
        menuParam.onStateChange = JSViewPopups::ParseDoubleBindCallback(info, callbackObj, "$value");
        auto isShowObj = callbackObj->GetProperty("value");
        if (isShowObj->IsBoolean()) {
            menuParam.isShow = isShowObj->ToBoolean();
            menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
            menuParam.placement = Placement::BOTTOM_LEFT;
            builderIndex = 1;
        }
    }
    return builderIndex;
}

void JSViewAbstract::ParseOverlayCallback(const JSRef<JSObject>& paramObj, std::function<void()>& onAppear,
    std::function<void()>& onDisappear, std::function<void()>& onWillAppear, std::function<void()>& onWillDisappear,
    std::function<void(const int32_t& info)>& onWillDismiss)
{
    auto showCallback = paramObj->GetProperty("onAppear");
    auto dismissCallback = paramObj->GetProperty("onDisappear");
    auto willShowCallback = paramObj->GetProperty("onWillAppear");
    auto willDismissCallback = paramObj->GetProperty("onWillDisappear");
    auto onWillDismissFunc = paramObj->GetProperty("onWillDismiss");
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (showCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(showCallback));
        onAppear = [func = std::move(jsFunc), node = frameNode]() {
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    if (dismissCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(dismissCallback));
        onDisappear = [func = std::move(jsFunc), node = frameNode]() {
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
    if (willShowCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(willShowCallback));
        onWillAppear = [func = std::move(jsFunc)]() { func->Execute(); };
    }
    if (willDismissCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(willDismissCallback));
        onWillDisappear = [func = std::move(jsFunc)]() { func->Execute(); };
    }
    if (onWillDismissFunc->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDismissFunc));
        onWillDismiss = [func = std::move(jsFunc), node = frameNode](const int32_t& info) {
            ACE_SCORING_EVENT("contentCover.dismiss");
            PipelineContext::SetCallBackNode(node);
            JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
            objectTemplate->SetInternalFieldCount(1);
            JSRef<JSObject> dismissObj = objectTemplate->NewInstance();
            dismissObj->SetPropertyObject(
                "dismiss", JSRef<JSFunc>::New<FunctionCallback>(JSViewAbstract::JsDismissContentCover));
            dismissObj->SetProperty<int32_t>("reason", info);
            JSRef<JSVal> newJSVal = dismissObj;
            func->ExecuteJS(1, &newJSVal);
        };
    }
}

std::vector<NG::OptionParam> JSViewPopups::ParseBindOptionParam(const JSCallbackInfo& info, size_t optionIndex)
{
    JSRef<JSVal> arg = info[optionIndex];
    if (!arg->IsArray()) {
        return std::vector<NG::OptionParam>();
    }
    auto paramArray = JSRef<JSArray>::Cast(arg);
    auto paramArrayLength = paramArray->Length();
    std::vector<NG::OptionParam> params(paramArrayLength);
    // parse paramArray
    for (size_t i = 0; i < paramArrayLength; ++i) {
        if (!paramArray->GetValueAt(i)->IsObject()) {
            return std::vector<NG::OptionParam>();
        }
        auto indexObject = JSRef<JSObject>::Cast(paramArray->GetValueAt(i));
        JSViewAbstract::ParseJsString(indexObject->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE)),
            params[i].value);
        auto actionFunc = indexObject->GetProperty(static_cast<int32_t>(ArkUIIndex::ACTION));
        if (!actionFunc->IsFunction()) {
            return params;
        }
        auto action = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(actionFunc));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        // set onClick function
        params[i].action = [func = std::move(action), context = info.GetExecutionContext(), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(context);
            ACE_SCORING_EVENT("menu.action");
            PipelineContext::SetCallBackNode(node);
            if (func) {
                func->Execute();
            }
        };
        std::string iconPath;
        if (JSViewAbstract::ParseJsMedia(indexObject->GetProperty(static_cast<int32_t>(ArkUIIndex::ICON)), iconPath)) {
            params[i].icon = iconPath;
        }
        if (indexObject->GetProperty(static_cast<int32_t>(ArkUIIndex::SYMBOL_ICON))->IsObject()) {
            std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
            JSViewAbstract::SetSymbolOptionApply(info, symbolApply,
                indexObject->GetProperty(static_cast<int32_t>(ArkUIIndex::SYMBOL_ICON)));
            params[i].symbol = symbolApply;
        }
        auto enabled = indexObject->GetProperty(static_cast<int32_t>(ArkUIIndex::ENABLED));
        if (enabled->IsBoolean()) {
            params[i].enabled = enabled->ToBoolean();
        }
    }
    return params;
}

void JSViewPopups::ParseMenuBorderRadius(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto borderRadiusValue = menuOptions->GetProperty(static_cast<int32_t>(ArkUIIndex::BORDER_RADIUS));
    NG::BorderRadiusProperty menuBorderRadius;
    CalcDimension borderRadius;
    if (JSViewAbstract::ParseJsDimensionVp(borderRadiusValue, borderRadius)) {
        if (GreatOrEqual(borderRadius.Value(), 0.0f)) {
            menuBorderRadius.SetRadius(borderRadius);
            menuBorderRadius.multiValued = false;
            menuParam.borderRadius = menuBorderRadius;
        };
    } else if (borderRadiusValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(borderRadiusValue);
        CalcDimension topLeft;
        CalcDimension topRight;
        CalcDimension bottomLeft;
        CalcDimension bottomRight;
        bool hasSetBorderRadius =
            JSViewAbstract::ParseAllBorderRadiuses(object, topLeft, topRight, bottomLeft, bottomRight);
        if (LessNotEqual(topLeft.Value(), 0.0f)) {
            topLeft.Reset();
        }
        if (LessNotEqual(topRight.Value(), 0.0f)) {
            topRight.Reset();
        }
        if (LessNotEqual(bottomLeft.Value(), 0.0f)) {
            bottomLeft.Reset();
        }
        if (LessNotEqual(bottomRight.Value(), 0.0f)) {
            bottomRight.Reset();
        }
        auto isRtl = hasSetBorderRadius && AceApplicationInfo::GetInstance().IsRightToLeft();
        menuBorderRadius.radiusTopLeft = isRtl ? topRight : topLeft;
        menuBorderRadius.radiusTopRight = isRtl ? topLeft : topRight;
        menuBorderRadius.radiusBottomLeft = isRtl ? bottomRight : bottomLeft;
        menuBorderRadius.radiusBottomRight = isRtl ? bottomLeft : bottomRight;
        menuBorderRadius.multiValued = true;
        menuParam.borderRadius = menuBorderRadius;
    }
}

void JSViewPopups::ParseMenuArrowParam(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto enableArrowValue = menuOptions->GetProperty("enableArrow");
    if (enableArrowValue->IsBoolean()) {
        menuParam.enableArrow = enableArrowValue->ToBoolean();
    }

    auto arrowOffset = menuOptions->GetProperty("arrowOffset");
    CalcDimension offset;
    if (JSViewAbstract::ParseJsDimensionVp(arrowOffset, offset)) {
        menuParam.arrowOffset = offset;
    }

    // if enableArrow is true and placement not set, set placement default value to top.
    if (menuParam.enableArrow.has_value() && !menuParam.placement.has_value() && menuParam.enableArrow.value()) {
        menuParam.placement = Placement::TOP;
    }
}

void JSViewPopups::ParseLayoutRegionMargin(const JSRef<JSVal>& jsValue, std::optional<CalcDimension>& calcDimension)
{
    CalcDimension dimension;
    if (!JSViewAbstract::ParseJsDimensionVpNG(jsValue, dimension, true)) {
        return;
    }

    if (dimension.IsNonNegative() && dimension.CalcValue().find("calc") == std::string::npos) {
        calcDimension = dimension;
    }
}

void JSViewPopups::ParseMenuLayoutRegionMarginParam(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto marginVal = menuOptions->GetProperty("layoutRegionMargin");
    if (!marginVal->IsObject()) {
        return;
    }

    CommonCalcDimension commonCalcDimension;
    auto object = JSRef<JSObject>::Cast(marginVal);
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("top"), commonCalcDimension.top);
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("bottom"), commonCalcDimension.bottom);
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("left"), commonCalcDimension.left);
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("right"), commonCalcDimension.right);

    if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
        commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
        menuParam.layoutRegionMargin = JSViewAbstract::GetLocalizedPadding(
            commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left, commonCalcDimension.right);
    }
}

void JSViewPopups::ParseMenuBlurStyleOption(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto blurStyle = menuOptions->GetProperty("backgroundBlurStyleOptions");
    if (blurStyle->IsObject()) {
        if (!menuParam.blurStyleOption.has_value()) {
            menuParam.blurStyleOption.emplace();
        }
        JSViewAbstract::ParseBlurStyleOption(blurStyle, menuParam.blurStyleOption.value());
    }
}

void JSViewPopups::ParseMenuEffectOption(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto effectOption = menuOptions->GetProperty("backgroundEffect");
    if (effectOption->IsObject()) {
        if (!menuParam.effectOption.has_value()) {
            menuParam.effectOption.emplace();
        }
        JSViewAbstract::ParseEffectOption(effectOption, menuParam.effectOption.value());
    }
}

void JSViewPopups::ParseMenuHapticFeedbackMode(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto hapticFeedbackMode = menuOptions->GetProperty("hapticFeedbackMode");
    if (!hapticFeedbackMode->IsNumber()) {
        return;
    }
    if (hapticFeedbackMode->ToNumber<int32_t>() == HAPTIC_FEEDBACK_MODE_ENABLED) {
        menuParam.hapticFeedbackMode = HapticFeedbackMode::ENABLED;
    } else if (hapticFeedbackMode->ToNumber<int32_t>() == HAPTIC_FEEDBACK_MODE_AUTO) {
        menuParam.hapticFeedbackMode = HapticFeedbackMode::AUTO;
    }
}

void JSViewPopups::GetMenuShowInSubwindow(NG::MenuParam& menuParam)
{
    menuParam.isShowInSubWindow = false;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    menuParam.isShowInSubWindow = theme->GetExpandDisplay();
}

void JSViewPopups::ParseMenuParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto offsetVal = menuOptions->GetProperty("offset");
    if (offsetVal->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetVal);
        JSRef<JSVal> xVal = offsetObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X));
        JSRef<JSVal> yVal = offsetObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y));
        CalcDimension dx;
        CalcDimension dy;
        if (JSViewAbstract::ParseJsDimensionVp(xVal, dx)) {
            menuParam.positionOffset.SetX(dx.ConvertToPx());
        }
        if (JSViewAbstract::ParseJsDimensionVp(yVal, dy)) {
            menuParam.positionOffset.SetY(dy.ConvertToPx());
        }
    }

    auto placementValue = menuOptions->GetProperty("placement");
    if (placementValue->IsNumber()) {
        auto placement = placementValue->ToNumber<int32_t>();
        if (placement >= 0 && placement < static_cast<int32_t>(Placement::NONE)) {
            menuParam.placement = static_cast<Placement>(placement);
        }
    }

    auto enableHoverModeValue = menuOptions->GetProperty("enableHoverMode");
    if (enableHoverModeValue->IsBoolean()) {
        menuParam.enableHoverMode = enableHoverModeValue->ToBoolean();
    }

    auto backgroundColorValue = menuOptions->GetProperty(static_cast<int32_t>(ArkUIIndex::BACKGROUND_COLOR));
    Color backgroundColor;
    if (JSViewAbstract::ParseJsColor(backgroundColorValue, backgroundColor)) {
        menuParam.backgroundColor = backgroundColor;
    }

    auto backgroundBlurStyle = menuOptions->GetProperty(static_cast<int32_t>(ArkUIIndex::BACKGROUND_BLUR_STYLE));
    if (backgroundBlurStyle->IsNumber()) {
        auto blurStyle = backgroundBlurStyle->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            menuParam.backgroundBlurStyle = blurStyle;
        }
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAppearValue = menuOptions->GetProperty("onAppear");
    if (onAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAppearValue));
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onAppear = std::move(onAppear);
    }

    auto onDisappearValue = menuOptions->GetProperty("onDisappear");
    if (onDisappearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDisappearValue));
        auto onDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc),
                               node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onDisappear = std::move(onDisappear);
    }
    auto aboutToAppearValue = menuOptions->GetProperty("aboutToAppear");
    if (aboutToAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsAboutToAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(aboutToAppearValue));
        auto aboutToAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToAppearFunc),
                                 node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("aboutToAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.aboutToAppear = std::move(aboutToAppear);
    }

    auto aboutToDisAppearValue = menuOptions->GetProperty("aboutToDisappear");
    if (aboutToDisAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsAboutToDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(aboutToDisAppearValue));
        auto aboutToDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsAboutToDisAppearFunc),
                                    node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("aboutToDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.aboutToDisappear = std::move(aboutToDisappear);
    }

    auto menuTransition = menuOptions->GetProperty("transition");
    menuParam.hasTransitionEffect = false;
    if (menuTransition->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(menuTransition);
        menuParam.hasTransitionEffect = true;
        menuParam.transition = JSViewAbstract::ParseChainedTransition(obj, info.GetExecutionContext());
    }

    JSRef<JSVal> showInSubWindowValue = menuOptions->GetProperty("showInSubWindow");
    JSViewPopups::GetMenuShowInSubwindow(menuParam);
    if (menuParam.isShowInSubWindow) {
        if (showInSubWindowValue->IsBoolean()) {
            menuParam.isShowInSubWindow = showInSubWindowValue->ToBoolean();
        }
    }
    JSViewPopups::ParseMenuArrowParam(menuOptions, menuParam);
    JSViewPopups::ParseMenuBorderRadius(menuOptions, menuParam);
    JSViewPopups::ParseMenuLayoutRegionMarginParam(menuOptions, menuParam);
    JSViewPopups::ParseMenuBlurStyleOption(menuOptions, menuParam);
    JSViewPopups::ParseMenuEffectOption(menuOptions, menuParam);
    JSViewPopups::ParseMenuHapticFeedbackMode(menuOptions, menuParam);
    auto outlineWidthValue = menuOptions->GetProperty("outlineWidth");
    JSViewPopups::ParseMenuOutlineWidth(outlineWidthValue, menuParam);
    auto outlineColorValue = menuOptions->GetProperty("outlineColor");
    JSViewPopups::ParseMenuOutlineColor(outlineColorValue, menuParam);
}

void JSViewPopups::ParseBindOptionParam(const JSCallbackInfo& info, NG::MenuParam& menuParam, size_t optionIndex)
{
    if (!info[optionIndex]->IsObject()) {
        return;
    }
    auto menuOptions = JSRef<JSObject>::Cast(info[optionIndex]);
    JSViewAbstract::ParseJsString(menuOptions->GetProperty("title"), menuParam.title);
    JSViewPopups::ParseMenuParam(info, menuOptions, menuParam);
}

void ParseAnimationScaleArray(const JSRef<JSArray>& scaleArray, MenuPreviewAnimationOptions& options)
{
    constexpr int scaleArraySize = 2;
    if (scaleArray->Length() == scaleArraySize) {
        auto scalePropertyFrom = scaleArray->GetValueAt(0);
        if (scalePropertyFrom->IsNumber()) {
            auto scaleFrom = scalePropertyFrom->ToNumber<float>();
            options.scaleFrom = LessOrEqual(scaleFrom, 0.0) ? -1.0f : scaleFrom;
        }
        auto scalePropertyTo = scaleArray->GetValueAt(1);
        if (scalePropertyTo->IsNumber()) {
            auto scaleTo = scalePropertyTo->ToNumber<float>();
            options.scaleTo = LessOrEqual(scaleTo, 0.0) ? -1.0f : scaleTo;
        }
    }
}

void ParseContentPreviewAnimationOptionsParam(const JSCallbackInfo& info, const JSRef<JSObject>& menuContentOptions,
    NG::MenuParam& menuParam)
{
    menuParam.previewAnimationOptions.scaleFrom = -1.0f;
    menuParam.previewAnimationOptions.scaleTo = -1.0f;

    auto animationOptions = menuContentOptions->GetProperty("previewAnimationOptions");
    if (!animationOptions->IsEmpty() && animationOptions->IsObject()) {
        auto animationOptionsObj = JSRef<JSObject>::Cast(animationOptions);
        auto scaleProperty = animationOptionsObj->GetProperty("scale");
        if (!scaleProperty->IsEmpty() && scaleProperty->IsArray()) {
            JSRef<JSArray> scaleArray = JSRef<JSArray>::Cast(scaleProperty);
            ParseAnimationScaleArray(scaleArray, menuParam.previewAnimationOptions);
        }
        auto previewTransition = animationOptionsObj->GetProperty("transition");
        menuParam.hasPreviewTransitionEffect = false;
        if (previewTransition->IsObject()) {
            auto obj = JSRef<JSObject>::Cast(previewTransition);
            menuParam.hasPreviewTransitionEffect = true;
            menuParam.previewTransition = JSViewAbstract::ParseChainedTransition(obj, info.GetExecutionContext());
        }
        if (menuParam.previewMode.value_or(MenuPreviewMode::NONE) != MenuPreviewMode::CUSTOM ||
            menuParam.hasPreviewTransitionEffect || menuParam.hasTransitionEffect ||
            menuParam.contextMenuRegisterType == NG::ContextMenuRegisterType::CUSTOM_TYPE) {
            return;
        }
        auto hoverScaleProperty = animationOptionsObj->GetProperty("hoverScale");
        menuParam.isShowHoverImage = false;
        menuParam.hoverImageAnimationOptions.scaleFrom = -1.0f;
        menuParam.hoverImageAnimationOptions.scaleTo = -1.0f;
        if (!hoverScaleProperty->IsEmpty() && hoverScaleProperty->IsArray()) {
            JSRef<JSArray> hoverScaleArray = JSRef<JSArray>::Cast(hoverScaleProperty);
            ParseAnimationScaleArray(hoverScaleArray, menuParam.hoverImageAnimationOptions);
            menuParam.isShowHoverImage = true;
        }
    }
}

void ParsePreviewBorderRadiusParam(const JSRef<JSObject>& menuContentOptions, NG::MenuParam& menuParam)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    auto previewBorderRadiusValue = menuContentOptions->GetProperty("previewBorderRadius");
    NG::BorderRadiusProperty previewBorderRadius;
    JSViewAbstract::ParseBorderRadius(previewBorderRadiusValue, previewBorderRadius, false);
    menuParam.previewBorderRadius = previewBorderRadius;
}

void ParseBindContentOptionParam(const JSCallbackInfo& info, const JSRef<JSVal>& args, NG::MenuParam& menuParam,
    std::function<void()>& previewBuildFunc)
{
    if (!args->IsObject()) {
        return;
    }
    auto menuContentOptions = JSRef<JSObject>::Cast(args);
    JSViewPopups::ParseMenuParam(info, menuContentOptions, menuParam);
    RefPtr<JsFunction> previewBuilderFunc;
    auto preview = menuContentOptions->GetProperty("preview");
    if (!preview->IsFunction() && !preview->IsNumber()) {
        return;
    }

    if (preview->IsNumber()) {
        if (preview->ToNumber<int32_t>() == 1) {
            menuParam.previewMode = MenuPreviewMode::IMAGE;
            ParseContentPreviewAnimationOptionsParam(info, menuContentOptions, menuParam);
            ParsePreviewBorderRadiusParam(menuContentOptions, menuParam);
        }
    } else {
        previewBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(preview));
        CHECK_NULL_VOID(previewBuilderFunc);
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        previewBuildFunc = [execCtx = info.GetExecutionContext(), func = std::move(previewBuilderFunc),
                               node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("BuildContextMenuPreviwer");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.previewMode = MenuPreviewMode::CUSTOM;
        ParseContentPreviewAnimationOptionsParam(info, menuContentOptions, menuParam);
        ParsePreviewBorderRadiusParam(menuContentOptions, menuParam);
    }
}

#ifndef WEARABLE_PRODUCT
void JSViewAbstract::JsBindPopup(const JSCallbackInfo& info)
{
    if (info.Length() < PARAMETER_LENGTH_SECOND) {
        return;
    }
    if ((!info[NUM_ZERO]->IsBoolean() && !info[NUM_ZERO]->IsObject()) || !info[NUM_FIRST]->IsObject()) {
        return;
    }
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    // Set IsShow to popupParam
    if (info[NUM_ZERO]->IsBoolean()) {
        popupParam->SetIsShow(info[NUM_ZERO]->ToBoolean());
    } else {
        JSRef<JSObject> showObj = JSRef<JSObject>::Cast(info[NUM_ZERO]);
        auto callback = JSViewPopups::ParseDoubleBindCallback(info, showObj, "$value");
        popupParam->SetDoubleBindCallback(std::move(callback));
        popupParam->SetIsShow(showObj->GetProperty("value")->ToBoolean());
    }
    // Set popup to popupParam
    auto popupObj = JSRef<JSObject>::Cast(info[NUM_FIRST]);
    SetPopupDismiss(info, popupObj, popupParam);
    if (popupObj->GetProperty("message")->IsString()) {
        ParsePopupParam(info, popupObj, popupParam); // Parse PopupOptions param
        ViewAbstractModel::GetInstance()->BindPopup(popupParam, nullptr);
    } else if (!popupObj->GetProperty("builder").IsEmpty()) {
        ParseCustomPopupParam(info, popupObj, popupParam); // Parse CustomPopupOptions param
        auto builderValue = popupObj->GetProperty("builder");
        auto builder = builderValue;
        if (!builderValue->IsObject()) {
            return;
        }
        if (!builderValue->IsFunction()) {
            JSRef<JSObject> builderObj;
            builderObj = JSRef<JSObject>::Cast(builderValue);
            builder = builderObj->GetProperty("builder");
            if (!builder->IsFunction()) {
                return;
            }
        }
        RefPtr<NG::UINode> customNode;
        if (popupParam->IsShow() && !IsPopupCreated()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
            CHECK_NULL_VOID(builderFunc);
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            builderFunc->Execute();
            customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        }
        ViewAbstractModel::GetInstance()->BindPopup(popupParam, customNode);
    } else {
        return;
    }
}

void JSViewAbstract::JsBindTips(const JSCallbackInfo& info)
{
    if (info.Length() < PARAMETER_LENGTH_FIRST || (!info[NUM_ZERO]->IsString() && !info[NUM_ZERO]->IsObject())) {
        return;
    }
    auto tipsParam = AceType::MakeRefPtr<PopupParam>();
    CHECK_NULL_VOID(tipsParam);
    // Set message to tipsParam
    std::string value;
    RefPtr<SpanString> styledString;
    if (info[0]->IsString()) {
        value = info[0]->ToString();
    } else {
        if (!info[0]->IsObject()) {
            return;
        }
        auto* spanString = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSpanString>();
        if (!spanString) {
            JSViewAbstract::ParseJsString(info[0], value);
        } else {
            styledString = spanString->GetController();
        }
    }
    tipsParam->SetMessage(value);
    // Set bindTipsOptions to tipsParam
    JSRef<JSObject> tipsObj;
    if (info.Length() > PARAMETER_LENGTH_FIRST && info[1]->IsObject()) {
        tipsObj = JSRef<JSObject>::Cast(info[1]);
    } else {
        tipsObj = JSRef<JSObject>::New();
    }
    // Parse bindTipsOptions param
    ParseTipsParam(tipsObj, tipsParam);
    if (tipsParam->EnableArrow()) {
        ParseTipsArrowPositionParam(tipsObj, tipsParam);
        ParseTipsArrowSizeParam(tipsObj, tipsParam);
    }
    ViewAbstractModel::GetInstance()->BindTips(tipsParam, styledString);
}

void JSViewAbstract::SetPopupDismiss(
    const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    auto onWillDismissFunc = popupObj->GetProperty("onWillDismiss");
    if (onWillDismissFunc->IsBoolean()) {
        bool onWillDismissBool = onWillDismissFunc->ToBoolean();
        popupParam->SetInteractiveDismiss(onWillDismissBool);
        popupParam->SetOnWillDismiss(nullptr);
        if (onWillDismissBool) {
            TAG_LOGI(AceLogTag::ACE_FORM, "popup register onWillDismiss");
        }
    } else if (onWillDismissFunc->IsFunction()) {
        auto onWillDismissCallback = ParsePopupCallback(info, popupObj);
        popupParam->SetOnWillDismiss(std::move(onWillDismissCallback));
        popupParam->SetInteractiveDismiss(true);
        if (onWillDismissCallback != nullptr) {
            TAG_LOGI(AceLogTag::ACE_FORM, "popup register onWillDismiss");
        }
    }
}

PopupOnWillDismiss JSViewAbstract::ParsePopupCallback(const JSCallbackInfo& info, const JSRef<JSObject>& paramObj)
{
    auto onWillDismissFunc = paramObj->GetProperty("onWillDismiss");
    if (!onWillDismissFunc->IsFunction()) {
        return PopupOnWillDismiss();
    }
    RefPtr<JsFunction> jsFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDismissFunc));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onWillDismiss = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                          node = frameNode](int32_t reason) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Bindpopup.dismiss");
        PipelineContext::SetCallBackNode(node);

        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(ON_WILL_DISMISS_FIELD_COUNT);
        JSRef<JSObject> dismissObj = objectTemplate->NewInstance();
        dismissObj->SetPropertyObject("dismiss", JSRef<JSFunc>::New<FunctionCallback>(JSViewAbstract::JsDismissPopup));
        dismissObj->SetProperty<int32_t>("reason", reason);
        JSRef<JSVal> newJSVal = dismissObj;
        func->ExecuteJS(1, &newJSVal);
    };
    return onWillDismiss;
}

panda::Local<panda::JSValueRef> JSViewAbstract::JsDismissPopup(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ViewAbstractModel::GetInstance()->DismissPopup();
    return JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

void JSViewAbstract::ParseContentPopupCommonParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam)
{
    CHECK_EQUAL_VOID(popupObj->IsEmpty(), true);
    CHECK_NULL_VOID(popupParam);
    int32_t targetId = StringUtils::StringToInt(popupParam->GetTargetId(), -1);
    if (targetId < 0) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetId is error.");
        return;
    }
    auto targetNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(targetId);
    if (!targetNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "The targetNode does not exist.");
        return;
    }
    SetPopupDismiss(info, popupObj, popupParam);
    ParsePopupCommonParam(info, popupObj, popupParam, targetNode);
    auto focusableValue = popupObj->GetProperty("focusable");
    if (focusableValue->IsBoolean()) {
        popupParam->SetFocusable(focusableValue->ToBoolean());
    }
}

int32_t JSViewAbstract::OpenPopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode)
{
    return ViewAbstractModel::GetInstance()->OpenPopup(param, customNode);
}

int32_t JSViewAbstract::UpdatePopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode)
{
    return ViewAbstractModel::GetInstance()->UpdatePopup(param, customNode);
}

int32_t JSViewAbstract::ClosePopup(const RefPtr<NG::UINode>& customNode)
{
    return ViewAbstractModel::GetInstance()->ClosePopup(customNode);
}

int32_t JSViewAbstract::GetPopupParam(RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode)
{
    return ViewAbstractModel::GetInstance()->GetPopupParam(param, customNode);
}

void JSViewAbstract::JsBindContextMenu(const JSCallbackInfo& info)
{
    NG::MenuParam menuParam;
    // Check the parameters
    if (info.Length() <= PARAMETER_LENGTH_ZERO) {
        return;
    }
    size_t builderIndex = ParseBindContextMenuShow(info, menuParam);
    if (!info[builderIndex]->IsObject()) {
        return;
    }

    JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[builderIndex]);
    auto builder = menuObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);

    ResponseType responseType = ResponseType::LONG_PRESS;
    if (!info[NUM_ZERO]->IsBoolean() && info.Length() >= PARAMETER_LENGTH_SECOND && info[NUM_FIRST]->IsNumber()) {
        auto response = info[NUM_FIRST]->ToNumber<int32_t>();
        responseType = static_cast<ResponseType>(response);
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void()> buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc),
                                          node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BuildContextMenu");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    menuParam.previewMode = MenuPreviewMode::NONE;
    std::function<void()> previewBuildFunc = nullptr;
    if (info.Length() >= PARAMETER_LENGTH_THIRD && info[NUM_SECOND]->IsObject()) {
        ParseBindContentOptionParam(info, info[NUM_SECOND], menuParam, previewBuildFunc);
    }
    if (responseType != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
        menuParam.isShowHoverImage = false;
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    }
    // arrow is disabled for contextMenu with preview
    if (menuParam.previewMode.value_or(MenuPreviewMode::NONE) != MenuPreviewMode::NONE) {
        menuParam.enableArrow = false;
    }
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    ViewAbstractModel::GetInstance()->BindContextMenu(responseType, buildFunc, menuParam, previewBuildFunc);
    ViewAbstractModel::GetInstance()->BindDragWithContextMenuParams(menuParam);
}
#endif

void JSViewAbstract::JsBindContentCover(const JSCallbackInfo& info)
{
    // parse isShow
    DoubleBindCallback callback = nullptr;
    bool isShow = ParseSheetIsShow(info, "ContentCover", callback);

    // parse builder
    if (!info[NUM_FIRST]->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[NUM_FIRST]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindContentCover");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    // parse ModalTransition
    NG::ModalStyle modalStyle;
    modalStyle.modalTransition = NG::ModalTransition::DEFAULT;
    std::function<void()> onShowCallback;
    std::function<void()> onDismissCallback;
    std::function<void()> onWillShowCallback;
    std::function<void()> onWillDismissCallback;
    NG::ContentCoverParam contentCoverParam;
    std::function<void(const int32_t&)> onWillDismissFunc;
    if (info.Length() == PARAMETER_LENGTH_THIRD) {
        if (info[NUM_SECOND]->IsObject()) {
            ParseOverlayCallback(info[NUM_SECOND], onShowCallback, onDismissCallback, /* 2:args index */
                onWillShowCallback, onWillDismissCallback, onWillDismissFunc);
            ParseModalStyle(info[NUM_SECOND], modalStyle);
            contentCoverParam.onWillDismiss = std::move(onWillDismissFunc);
            ParseModalTransitonEffect(info[NUM_SECOND], contentCoverParam, /* 2:args index */
                info.GetExecutionContext());
        } else if (info[NUM_SECOND]->IsNumber()) {
            auto transitionNumber = info[NUM_SECOND]->ToNumber<int32_t>();
            if (transitionNumber >= TRANSITION_NUM_ZERO && transitionNumber <= TRANSITION_NUM_TWO) {
                modalStyle.modalTransition = static_cast<NG::ModalTransition>(transitionNumber);
            }
        }
    }
    ViewAbstractModel::GetInstance()->BindContentCover(isShow, std::move(callback), std::move(buildFunc), modalStyle,
        std::move(onShowCallback), std::move(onDismissCallback), std::move(onWillShowCallback),
        std::move(onWillDismissCallback), contentCoverParam);
}

void JSViewAbstract::ParseModalTransitonEffect(
    const JSRef<JSObject>& paramObj, NG::ContentCoverParam& contentCoverParam, const JSExecutionContext& context)
{
    auto transitionEffectValue = paramObj->GetProperty("transition");
    if (transitionEffectValue->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(transitionEffectValue);
        contentCoverParam.transitionEffect = ParseChainedTransition(obj, context);
    }
}

void JSViewAbstract::ParseModalStyle(const JSRef<JSObject>& paramObj, NG::ModalStyle& modalStyle)
{
    auto modalTransition = paramObj->GetProperty("modalTransition");
    auto backgroundColor = paramObj->GetProperty("backgroundColor");
    if (modalTransition->IsNumber()) {
        auto transitionNumber = modalTransition->ToNumber<int32_t>();
        if (transitionNumber >= TRANSITION_NUM_ZERO && transitionNumber <= TRANSITION_NUM_TWO) {
            modalStyle.modalTransition = static_cast<NG::ModalTransition>(transitionNumber);
        }
    }
    Color color;
    if (ParseJsColor(backgroundColor, color)) {
        modalStyle.backgroundColor = color;
    }
}

bool JSViewAbstract::ParseSheetIsShow(const JSCallbackInfo& info, const std::string& name,
    std::function<void(const std::string&)>& callback)
{
    bool isShow = false;
    if (info[0]->IsBoolean()) {
        isShow = info[0]->ToBoolean();
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(info[0]);
        auto isShowObj = callbackObj->GetProperty("value");
        isShow = isShowObj->IsBoolean() ? isShowObj->ToBoolean() : false;
        callback = JSViewPopups::ParseDoubleBindCallback(info, callbackObj, "changeEvent");
        if (!callback && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            TAG_LOGD(AceLogTag::ACE_SHEET, "Try %{public}s another parsing", name.c_str());
            callback = JSViewPopups::ParseDoubleBindCallback(info, callbackObj, "$value");
        }
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "%{public}s get isShow is: %{public}d", name.c_str(), isShow);
    return isShow;
}

void JSViewAbstract::JsBindSheet(const JSCallbackInfo& info)
{
    // parse isShow and builder
    DoubleBindCallback callback = nullptr;
    bool isShow = ParseSheetIsShow(info, "Sheet", callback);
    if (!info[NUM_FIRST]->IsObject())
        return;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[NUM_FIRST]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction())
        return;
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindSheet");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };
    // parse SheetStyle and callbacks
    NG::SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showCloseIcon = true;
    sheetStyle.showInPage = false;
    std::function<void()> onAppearCallback;
    std::function<void()> onDisappearCallback;
    std::function<void()> onWillAppearCallback;
    std::function<void()> onWillDisappearCallback  ;
    std::function<void()> shouldDismissFunc;
    std::function<void(const int32_t)> onWillDismissCallback;
    std::function<void(const float)> onHeightDidChangeCallback;
    std::function<void(const float)> onDetentsDidChangeCallback;
    std::function<void(const float)> onWidthDidChangeCallback;
    std::function<void(const float)> onTypeDidChangeCallback;
    std::function<void()> titleBuilderFunction;
    std::function<void()> sheetSpringBackFunc;
    if (info.Length() == PARAMETER_LENGTH_THIRD && info[NUM_SECOND]->IsObject()) {
        ParseSheetCallback(info[NUM_SECOND], onAppearCallback, onDisappearCallback, shouldDismissFunc,
            onWillDismissCallback, onWillAppearCallback, onWillDisappearCallback, onHeightDidChangeCallback,
            onDetentsDidChangeCallback, onWidthDidChangeCallback, onTypeDidChangeCallback, sheetSpringBackFunc);
        ParseSheetStyle(info[NUM_SECOND], sheetStyle);
        ParseSheetTitle(info[NUM_SECOND], sheetStyle, titleBuilderFunction);
    }
    ViewAbstractModel::GetInstance()->BindSheet(isShow, std::move(callback), std::move(buildFunc),
        std::move(titleBuilderFunction), sheetStyle, std::move(onAppearCallback), std::move(onDisappearCallback),
        std::move(shouldDismissFunc), std::move(onWillDismissCallback),  std::move(onWillAppearCallback),
        std::move(onWillDisappearCallback), std::move(onHeightDidChangeCallback), std::move(onDetentsDidChangeCallback),
        std::move(onWidthDidChangeCallback), std::move(onTypeDidChangeCallback), std::move(sheetSpringBackFunc));
}

NG::SheetEffectEdge JSViewAbstract::ParseSheetEffectEdge(const JSRef<JSObject>& paramObj)
{
    auto sheetEffectEdge = static_cast<int32_t>(NG::SheetEffectEdge::ALL);
    JSRef<JSVal> effectEdgedParam = paramObj->GetProperty("effectEdge");
    if (effectEdgedParam->IsNull() || effectEdgedParam->IsUndefined() ||
        !JSViewAbstract::ParseJsInt32(effectEdgedParam, sheetEffectEdge) ||
        sheetEffectEdge < static_cast<int32_t>(NG::SheetEffectEdge::NONE) ||
        sheetEffectEdge > static_cast<int32_t>(NG::SheetEffectEdge::END)) {
        sheetEffectEdge = static_cast<int32_t>(NG::SheetEffectEdge::ALL);
    }
    return static_cast<NG::SheetEffectEdge>(sheetEffectEdge);
}

void JSViewAbstract::ParseSheetStyle(
    const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle, bool isPartialUpdate)
{
    auto height = paramObj->GetProperty("height");
    auto showDragBar = paramObj->GetProperty("dragBar");
    auto backgroundColor = paramObj->GetProperty("backgroundColor");
    auto maskColor = paramObj->GetProperty("maskColor");
    auto sheetDetents = paramObj->GetProperty("detents");
    auto backgroundBlurStyle = paramObj->GetProperty("blurStyle");
    auto showCloseIcon = paramObj->GetProperty("showClose");
    auto type = paramObj->GetProperty("preferType");
    auto interactive = paramObj->GetProperty("enableOutsideInteractive");
    auto showMode = paramObj->GetProperty("mode");
    auto offsetVal = paramObj->GetProperty("offset");
    auto scrollSizeMode = paramObj->GetProperty("scrollSizeMode");
    auto keyboardAvoidMode = paramObj->GetProperty("keyboardAvoidMode");
    auto uiContextObj = paramObj->GetProperty("uiContext");
    if (uiContextObj->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(uiContextObj);
        auto prop = obj->GetProperty("instanceId_");
        if (prop->IsNumber()) {
            sheetStyle.instanceId = prop->ToNumber<int32_t>();
        }
    }

    if (offsetVal->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetVal);
        auto xVal = offsetObj->GetProperty("x");
        auto yVal = offsetObj->GetProperty("y");
        NG::OffsetF bottomOffset;
        CalcDimension dx;
        CalcDimension dy;
        if (JSViewAbstract::ParseJsDimensionVp(xVal, dx)) {
            bottomOffset.SetX(dx.ConvertToPx());
        }
        if (JSViewAbstract::ParseJsDimensionVp(yVal, dy) && dy.IsNegative()) {
            bottomOffset.SetY(dy.ConvertToPx());
        }
        sheetStyle.bottomOffset = bottomOffset;
    }

    NG::SheetLevel sheetLevel = NG::SheetLevel::OVERLAY;
    if (ParseSheetLevel(showMode, sheetLevel) || !isPartialUpdate) {
        sheetStyle.showInPage = (sheetLevel == NG::SheetLevel::EMBEDDED);
    }

    std::vector<NG::SheetHeight> detents;
    if (ParseSheetDetents(sheetDetents, detents)) {
        sheetStyle.detents = detents;
    }
    BlurStyleOption styleOption;
    if (ParseSheetBackgroundBlurStyle(backgroundBlurStyle, styleOption)) {
        sheetStyle.backgroundBlurStyle = styleOption;
    }
    bool showClose = true;
    if (ParseJsBool(showCloseIcon, showClose)) {
        sheetStyle.showCloseIcon = showClose;
    } else if (!isPartialUpdate) {
        sheetStyle.showCloseIcon = true;
    }

    bool isInteractive = false;
    if (ParseJsBool(interactive, isInteractive)) {
        sheetStyle.interactive = isInteractive;
    }

    if (showDragBar->IsBoolean()) {
        sheetStyle.showDragBar = showDragBar->ToBoolean();
    } else if (isPartialUpdate) {
        sheetStyle.showDragBar.reset();
    } else {
        sheetStyle.showDragBar = true;
    }

    if (type->IsNull() || type->IsUndefined()) {
        sheetStyle.sheetType.reset();
    } else {
        if (type->IsNumber()) {
            auto sheetType = type->ToNumber<int32_t>();
            if (sheetType >= static_cast<int>(NG::SheetType::SHEET_BOTTOM) &&
                sheetType <= static_cast<int>(NG::SheetType::SHEET_POPUP)) {
                sheetStyle.sheetType = static_cast<NG::SheetType>(sheetType);
            }
        }
    }
    if (scrollSizeMode->IsNull() || scrollSizeMode->IsUndefined()) {
        sheetStyle.scrollSizeMode.reset();
    } else if (scrollSizeMode->IsNumber()) {
        auto sheetScrollSizeMode = scrollSizeMode->ToNumber<int32_t>();
        if (sheetScrollSizeMode >= static_cast<int>(NG::ScrollSizeMode::FOLLOW_DETENT) &&
            sheetScrollSizeMode <= static_cast<int>(NG::ScrollSizeMode::CONTINUOUS)) {
            sheetStyle.scrollSizeMode = static_cast<NG::ScrollSizeMode>(sheetScrollSizeMode);
        }
    }

    if (keyboardAvoidMode->IsNull() || keyboardAvoidMode->IsUndefined()) {
        sheetStyle.sheetKeyboardAvoidMode.reset();
    } else if (keyboardAvoidMode->IsNumber()) {
        auto sheetKeyboardAvoidMode = keyboardAvoidMode->ToNumber<int32_t>();
        if (sheetKeyboardAvoidMode >= static_cast<int>(NG::SheetKeyboardAvoidMode::NONE) &&
            sheetKeyboardAvoidMode <= static_cast<int>(NG::SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL)) {
            sheetStyle.sheetKeyboardAvoidMode = static_cast<NG::SheetKeyboardAvoidMode>(sheetKeyboardAvoidMode);
        }
    }

    auto placement = paramObj->GetProperty("placement");
    sheetStyle.placement.reset();
    if (placement->IsNumber()) {
        auto placementValue = placement->ToNumber<int32_t>();
        if (placementValue >= static_cast<int>(Placement::LEFT) &&
            placementValue <= static_cast<int>(Placement::RIGHT_BOTTOM)) {
            sheetStyle.placement = static_cast<Placement>(placementValue);
        }
    }

    auto placementOnTarget = paramObj->GetProperty("placementOnTarget");
    sheetStyle.placementOnTarget.reset();
    if (placementOnTarget->IsBoolean()) {
        sheetStyle.placementOnTarget = placementOnTarget->ToBoolean();
    }

    Color color;
    if (ParseJsColor(backgroundColor, color)) {
        sheetStyle.backgroundColor = color;
    }
    // parse maskColor
    Color parseMaskColor;
    if (!maskColor->IsNull() && !maskColor->IsUndefined() && JSViewAbstract::ParseJsColor(maskColor, parseMaskColor)) {
        sheetStyle.maskColor = std::move(parseMaskColor);
    }

    // Parse border width
    auto borderWidthValue = paramObj->GetProperty("borderWidth");
    NG::BorderWidthProperty borderWidth;
    if (ParseBorderWidthProps(borderWidthValue, borderWidth)) {
        sheetStyle.borderWidth = borderWidth;
        // Parse border color
        auto colorValue = paramObj->GetProperty("borderColor");
        NG::BorderColorProperty borderColor;
        if (ParseBorderColorProps(colorValue, borderColor)) {
            sheetStyle.borderColor = borderColor;
        } else {
            sheetStyle.borderColor =
                NG::BorderColorProperty({ Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK });
        }
        // Parse border style
        auto styleValue = paramObj->GetProperty("borderStyle");
        NG::BorderStyleProperty borderStyle;
        if (ParseBorderStyleProps(styleValue, borderStyle)) {
            sheetStyle.borderStyle = borderStyle;
        } else {
            sheetStyle.borderStyle = NG::BorderStyleProperty(
                { BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID });
        }
    }
    if (isPartialUpdate) {
        auto colorValue = paramObj->GetProperty("borderColor");
        NG::BorderColorProperty borderColor;
        if (ParseBorderColorProps(colorValue, borderColor)) {
            sheetStyle.borderColor = borderColor;
        } else {
            sheetStyle.borderColor.reset();
        }
        auto styleValue = paramObj->GetProperty("borderStyle");
        NG::BorderStyleProperty borderStyle;
        if (ParseBorderStyleProps(styleValue, borderStyle)) {
            sheetStyle.borderStyle = borderStyle;
        } else {
            sheetStyle.borderStyle.reset();
        }
    }

    // Parse shadow
    Shadow shadow;
    auto shadowValue = paramObj->GetProperty("shadow");
    if ((shadowValue->IsObject() || shadowValue->IsNumber()) && ParseShadowProps(shadowValue, shadow)) {
        sheetStyle.shadow = shadow;
    }

    //parse effectEdge
    sheetStyle.sheetEffectEdge = ParseSheetEffectEdge(paramObj);

    // Parse hoverMode
    auto enableHoverModeValue = paramObj->GetProperty("enableHoverMode");
    if (enableHoverModeValue->IsBoolean()) {
        sheetStyle.enableHoverMode = enableHoverModeValue->ToBoolean();
    }
    auto hoverModeAreaValue = paramObj->GetProperty("hoverModeArea");
    if (hoverModeAreaValue->IsNumber()) {
        auto hoverModeArea = hoverModeAreaValue->ToNumber<int32_t>();
        if (hoverModeArea >= 0 && hoverModeArea < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
            sheetStyle.hoverModeArea = HOVER_MODE_AREA_TYPE[hoverModeArea];
        }
    }

    auto widthValue = paramObj->GetProperty("width");
    CalcDimension width;
    if (ParseJsDimensionVpNG(widthValue, width, true)) {
        sheetStyle.width = width;
    }

    auto radiusValue = paramObj->GetProperty("radius");
    JSViewAbstract::ParseBindSheetBorderRadius(radiusValue, sheetStyle);

    ParseDetentSelection(paramObj, sheetStyle);

    NG::SheetHeight sheetStruct;
    bool parseResult = ParseSheetHeight(height, sheetStruct, isPartialUpdate);
    if (!parseResult) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "parse sheet height in unnormal condition");
    }
    sheetStyle.sheetHeight = sheetStruct;

    ParseSheetSubWindowValue(paramObj, sheetStyle);
}

void JSViewAbstract::ParseSheetSubWindowValue(const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle)
{
    // parse sheet showInSubWindow
    sheetStyle.showInSubWindow = false;
    if (sheetStyle.showInPage == NG::SheetLevel::EMBEDDED) {
        return;
    }
    auto showInSubWindowValue = paramObj->GetProperty("showInSubWindow");
    if (showInSubWindowValue->IsBoolean()) {
#if defined(PREVIEW)
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
                "emulator or a real device instead.");
#else
        sheetStyle.showInSubWindow = showInSubWindowValue->ToBoolean();
#endif
    }
}

void JSViewAbstract::ParseDetentSelection(const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle)
{
    auto detentSelection = paramObj->GetProperty("detentSelection");
    NG::SheetHeight sheetStruct;
    bool parseResult = ParseSheetHeight(detentSelection, sheetStruct, true);
    if (!parseResult) {
        sheetStruct.height.reset();
        sheetStruct.sheetMode.reset();
        TAG_LOGD(AceLogTag::ACE_SHEET, "parse sheet detent selection in unnormal condition");
    }
    sheetStyle.detentSelection = sheetStruct;
}
 
bool JSViewAbstract::ParseSheetDetents(const JSRef<JSVal>& args, std::vector<NG::SheetHeight>& sheetDetents)
{
    if (!args->IsArray()) {
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(args);
    NG::SheetHeight sheetDetent;
    for (size_t i = 0; i < array->Length(); i++) {
        bool parseResult = ParseSheetHeight(array->GetValueAt(i), sheetDetent, false);
        if (!parseResult) {
            TAG_LOGD(AceLogTag::ACE_SHEET, "parse sheet detent in unnormal condition");
        }
        if ((!sheetDetent.height.has_value()) && (!sheetDetent.sheetMode.has_value())) {
            continue;
        }
        sheetDetents.emplace_back(sheetDetent);
        sheetDetent.height.reset();
        sheetDetent.sheetMode.reset();
    }
    return true;
}

bool JSViewAbstract::ParseSheetBackgroundBlurStyle(const JSRef<JSVal>& args, BlurStyleOption& blurStyleOptions)
{
    if (args->IsNumber()) {
        auto sheetBlurStyle = args->ToNumber<int32_t>();
        if (sheetBlurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            sheetBlurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            blurStyleOptions.blurStyle = static_cast<BlurStyle>(sheetBlurStyle);
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool JSViewAbstract::ParseSheetLevel(const JSRef<JSVal>& args, NG::SheetLevel& sheetLevel)
{
    if (!args->IsNumber()) {
        return false;
    }
    auto sheetMode = args->ToNumber<int32_t>();
    if (sheetMode >= static_cast<int>(NG::SheetLevel::OVERLAY) &&
        sheetMode <= static_cast<int>(NG::SheetLevel::EMBEDDED)) {
        sheetLevel = static_cast<NG::SheetLevel>(sheetMode);
        return true;
    }
    return false;
}

void JSViewAbstract::ParseCallback(const JSRef<JSObject>& paramObj,
    std::function<void(const float)>& callbackDidChange, const char* prop)
{
    auto callBack = paramObj->GetProperty(prop);
    if (callBack->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(callBack));
        callbackDidChange = [func = std::move(jsFunc)](int32_t value) {
            JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(value));
            func->ExecuteJS(1, &param);
        };
    }
}

void JSViewAbstract::ParseLifeCycleCallback(const JSRef<JSObject>& paramObj,
    std::function<void()>& lifeCycleCallBack, const char* prop)
{
    auto callback = paramObj->GetProperty(prop);
    if (callback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(callback));
        lifeCycleCallBack = [func = std::move(jsFunc)]() { func->Execute(); };
    }
}

void JSViewAbstract::ParseSpringBackCallback(const JSRef<JSObject>& paramObj,
    std::function<void()>& sheetSpringBack, const char* prop)
{
    auto sheetSpringBackCallback = paramObj->GetProperty(prop);
    if (sheetSpringBackCallback->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(sheetSpringBackCallback));
        sheetSpringBack = [func = std::move(jsFunc)]() {
            JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
            objectTemplate->SetInternalFieldCount(1);
            JSRef<JSObject> dismissObj = objectTemplate->NewInstance();
            dismissObj->SetPropertyObject(
                "springBack", JSRef<JSFunc>::New<FunctionCallback>(JSViewAbstract::JsSheetSpringBack));
            JSRef<JSVal> newJSVal = dismissObj;
            func->ExecuteJS(1, &newJSVal);
        };
    }
}

void JSViewAbstract::ParseSheetCallback(const JSRef<JSObject>& paramObj, std::function<void()>& onAppear,
    std::function<void()>& onDisappear, std::function<void()>& shouldDismiss,
    std::function<void(const int32_t info)>& onWillDismiss, std::function<void()>& onWillAppear,
    std::function<void()>& onWillDisappear, std::function<void(const float)>& onHeightDidChange,
    std::function<void(const float)>& onDetentsDidChange,
    std::function<void(const float)>& onWidthDidChange,
    std::function<void(const float)>& onTypeDidChange, std::function<void()>& sheetSpringBack)
{
    auto shouldDismissFunc = paramObj->GetProperty("shouldDismiss");
    auto onWillDismissFunc = paramObj->GetProperty("onWillDismiss");
    ParseLifeCycleCallback(paramObj, onAppear, "onAppear");
    ParseLifeCycleCallback(paramObj, onDisappear, "onDisappear");
    ParseLifeCycleCallback(paramObj, onWillAppear, "onWillAppear");
    ParseLifeCycleCallback(paramObj, onWillDisappear, "onWillDisappear");
    if (shouldDismissFunc->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(shouldDismissFunc));
        shouldDismiss = [func = std::move(jsFunc)]() {
            JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
            objectTemplate->SetInternalFieldCount(1);
            JSRef<JSObject> dismissObj = objectTemplate->NewInstance();
            dismissObj->SetPropertyObject(
                "dismiss", JSRef<JSFunc>::New<FunctionCallback>(JSViewAbstract::JsDismissSheet));
            JSRef<JSVal> newJSVal = dismissObj;
            func->ExecuteJS(1, &newJSVal);
        };
    }
    if (onWillDismissFunc->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDismissFunc));
        onWillDismiss = [func = std::move(jsFunc)](const int32_t info) {
            JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
            objectTemplate->SetInternalFieldCount(1);
            JSRef<JSObject> dismissObj = objectTemplate->NewInstance();
            dismissObj->SetPropertyObject(
                "dismiss", JSRef<JSFunc>::New<FunctionCallback>(JSViewAbstract::JsDismissSheet));
            dismissObj->SetProperty<int32_t>("reason", info);
            JSRef<JSVal> newJSVal = dismissObj;
            func->ExecuteJS(1, &newJSVal);
        };
    }
    ParseSpringBackCallback(paramObj, sheetSpringBack, "onWillSpringBackWhenDismiss");
    ParseCallback(paramObj, onHeightDidChange, "onHeightDidChange");
    ParseCallback(paramObj, onDetentsDidChange, "onDetentsDidChange");
    ParseCallback(paramObj, onWidthDidChange, "onWidthDidChange");
    ParseCallback(paramObj, onTypeDidChange, "onTypeDidChange");
}

void JSViewAbstract::ParseSheetTitle(
    const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle, std::function<void()>& titleBuilderFunction)
{
    auto title = paramObj->GetProperty("title");
    std::string mainTitle;
    std::string subtitle;
    if (title->IsFunction()) {
        sheetStyle.isTitleBuilder = true;
        auto titleBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(title));
        CHECK_NULL_VOID(titleBuilderFunc);
        titleBuilderFunction = [func = std::move(titleBuilderFunc)]() {
            ACE_SCORING_EVENT("BindSheet");
            func->Execute();
        };
    } else if (title->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(title);
        sheetStyle.isTitleBuilder = false;
        auto sheetTitle = obj->GetProperty("title");
        auto sheetSubtitle = obj->GetProperty("subtitle");
        if (ParseJsString(sheetTitle, mainTitle)) {
            sheetStyle.sheetTitle = mainTitle;
        }
        if (ParseJsString(sheetSubtitle, subtitle)) {
            sheetStyle.sheetSubtitle = subtitle;
        }
    }
}

panda::Local<panda::JSValueRef> JSViewAbstract::JsDismissSheet(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ViewAbstractModel::GetInstance()->DismissSheet();
    return JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

panda::Local<panda::JSValueRef> JSViewAbstract::JsDismissContentCover(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ViewAbstractModel::GetInstance()->DismissContentCover();
    return JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

panda::Local<panda::JSValueRef> JSViewAbstract::JsSheetSpringBack(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ViewAbstractModel::GetInstance()->SheetSpringBack();
    return JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

bool JSViewAbstract::ParseSheetMode(const std::string heightStr, NG::SheetHeight& detent)
{
    if (heightStr == SHEET_HEIGHT_MEDIUM) {
        detent.sheetMode = NG::SheetMode::MEDIUM;
        return true;
    }

    if (heightStr == SHEET_HEIGHT_LARGE) {
        detent.sheetMode = NG::SheetMode::LARGE;
        return true;
    }
    if (heightStr == SHEET_HEIGHT_FITCONTENT) {
        detent.sheetMode = NG::SheetMode::AUTO;
        return true;
    }
    return false;
}

bool JSViewAbstract::ParseSheetHeight(const JSRef<JSVal>& args, NG::SheetHeight& detent,
    bool isReset)
{
    detent.height.reset();
    detent.sheetMode.reset();
    CalcDimension sheetHeight;
    if (args->IsString()) {
        std::string heightStr = args->ToString();

        // Remove all " ".
        heightStr.erase(std::remove(heightStr.begin(), heightStr.end(), ' '), heightStr.end());
        std::transform(heightStr.begin(), heightStr.end(), heightStr.begin(), ::tolower);
        if (ParseSheetMode(heightStr, detent)) {
            return true;
        }
        if (heightStr.find("calc") != std::string::npos) {
            sheetHeight = CalcDimension(heightStr, DimensionUnit::CALC);
        } else {
            sheetHeight = StringUtils::StringToDimensionWithUnit(heightStr, DimensionUnit::VP, -1.0);
        }
        if (sheetHeight.Value() < 0) {
            detent.sheetMode = NG::SheetMode::LARGE;
            return false;
        }
    }
    if (!ParseJsDimensionVpNG(args, sheetHeight)) {
        if (!isReset) {
            auto sheetTheme = GetTheme<OHOS::Ace::NG::SheetTheme>();
            detent.sheetMode = sheetTheme != nullptr
                                   ? static_cast<NG::SheetMode>(sheetTheme->GetSheetHeightDefaultMode())
                                   : NG::SheetMode::LARGE;
        }
        return false;
    }
    detent.height = sheetHeight;
    return true;
}

void JSViewAbstract::JsBindMenu(const JSCallbackInfo& info)
{
    NG::MenuParam menuParam;
    MenuDefaultParam(menuParam);
    size_t builderIndex = 0;
    JSViewPopups::GetMenuShowInSubwindow(menuParam);
    if (info.Length() > PARAMETER_LENGTH_FIRST) {
        auto jsVal = info[0];
        if (jsVal->IsBoolean()) {
            menuParam.isShow = jsVal->ToBoolean();
            menuParam.setShow = true;
            builderIndex = 1;
            if (info.Length() > PARAMETER_LENGTH_SECOND) {
                JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        } else if (jsVal->IsUndefined()) {
            menuParam.setShow = true;
            menuParam.isShow = false;
            builderIndex = 1;
            if (info.Length() > PARAMETER_LENGTH_SECOND) {
                JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        } else if (jsVal->IsObject()) {
            JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(jsVal);
            menuParam.onStateChange = JSViewPopups::ParseDoubleBindCallback(info, callbackObj, "$value");
            auto isShowObj = callbackObj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
            if (isShowObj->IsBoolean()) {
                menuParam.isShow = isShowObj->ToBoolean();
                menuParam.setShow = true;
                builderIndex = 1;
                if (info.Length() > PARAMETER_LENGTH_SECOND) {
                    JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
                }
            } else {
                builderIndex = 0;
                JSViewPopups::ParseBindOptionParam(info, menuParam, builderIndex + 1);
            }
        }
    }

    if (info[builderIndex]->IsArray()) {
        std::vector<NG::OptionParam> optionsParam = JSViewPopups::ParseBindOptionParam(info, builderIndex);
        ViewAbstractModel::GetInstance()->BindMenu(std::move(optionsParam), nullptr, menuParam);
    } else if (info[builderIndex]->IsObject()) {
        // CustomBuilder
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[builderIndex]);
        auto builder = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::BUILDER));
        if (!builder->IsFunction()) {
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));

        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_VOID(builderFunc);
        auto buildFunc = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("BuildMenu");
            auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->BindMenu({}, std::move(buildFunc), menuParam);
    }
}

void JSViewAbstract::MenuDefaultParam(NG::MenuParam& menuParam)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        menuParam.placement = Placement::BOTTOM_LEFT;
    }
}

void JSViewAbstract::ParseContentMenuCommonParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuObj, NG::MenuParam& menuParam)
{
    if (!menuParam.placement.has_value()) {
        MenuDefaultParam(menuParam);
    }
    CHECK_EQUAL_VOID(menuObj->IsEmpty(), true);
    JSViewPopups::ParseMenuParam(info, menuObj, menuParam);
    auto preview = menuObj->GetProperty("preview");
    if (preview->IsNumber()) {
        auto previewMode = preview->ToNumber<int32_t>();
        menuParam.previewMode = static_cast<MenuPreviewMode>(previewMode);
        if (previewMode == static_cast<int32_t>(MenuPreviewMode::IMAGE)) {
            ParseContentPreviewAnimationOptionsParam(info, menuObj, menuParam);
        }
    }
}

int32_t JSViewAbstract::OpenMenu(
    NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode, const int32_t& targetId)
{
    return ViewAbstractModel::GetInstance()->OpenMenu(menuParam, customNode, targetId);
}

int32_t JSViewAbstract::UpdateMenu(const NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode)
{
    return ViewAbstractModel::GetInstance()->UpdateMenu(menuParam, customNode);
}

int32_t JSViewAbstract::CloseMenu(const RefPtr<NG::UINode>& customNode)
{
    return ViewAbstractModel::GetInstance()->CloseMenu(customNode);
}

void JSViewAbstract::ParseDialogCallback(const JSRef<JSObject>& paramObj,
    std::function<void(const int32_t& info, const int32_t& instanceId)>& onWillDismiss)
{
    auto onWillDismissFunc = paramObj->GetProperty("onWillDismiss");
    if (onWillDismissFunc->IsFunction()) {
        auto jsFunc =
            AceType::MakeRefPtr<JsWeakFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDismissFunc));
        onWillDismiss = [func = std::move(jsFunc)](const int32_t& info, const int32_t& instanceId) {
            JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
            objectTemplate->SetInternalFieldCount(ON_WILL_DISMISS_FIELD_COUNT);
            JSRef<JSObject> dismissObj = objectTemplate->NewInstance();
            dismissObj->SetPropertyObject(
                "dismiss", JSRef<JSFunc>::New<FunctionCallback>(JSViewAbstract::JsDismissDialog));
            dismissObj->SetProperty<int32_t>("reason", info);
            JSRef<JSVal> newJSVal = dismissObj;
            func->ExecuteJS(1, &newJSVal);
        };
    }
}

panda::Local<panda::JSValueRef> JSViewAbstract::JsDismissDialog(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ViewAbstractModel::GetInstance()->DismissDialog();
    return JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

void AppearDialogEvent(const JSCallbackInfo& info, DialogProperties& dialogProperties)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidAppear = paramObject->GetProperty("onDidAppear");
    if (!onDidAppear->IsUndefined() && onDidAppear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsWeakFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidAppear));
        auto didAppearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Popups.onDidAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogProperties.onDidAppear = std::move(didAppearId);
    }
    auto onWillAppear = paramObject->GetProperty("onWillAppear");
    if (!onWillAppear->IsUndefined() && onWillAppear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsWeakFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillAppear));
        auto willAppearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Popups.onWillAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogProperties.onWillAppear = std::move(willAppearId);
    }
}

void DisappearDialogEvent(const JSCallbackInfo& info, DialogProperties& dialogProperties)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDidDisappear = paramObject->GetProperty("onDidDisappear");
    if (!onDidDisappear->IsUndefined() && onDidDisappear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsWeakFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidDisappear));
        auto didDisappearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Popups.onDidDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogProperties.onDidDisappear = std::move(didDisappearId);
    }
    auto onWillDisappear = paramObject->GetProperty("onWillDisappear");
    if (!onWillDisappear->IsUndefined() && onWillDisappear->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsWeakFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDisappear));
        auto willDisappearId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Popups.onWillDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        dialogProperties.onWillDisappear = std::move(willDisappearId);
    }
}

void JSViewAbstract::ParseAppearDialogCallback(const JSCallbackInfo& info, DialogProperties& dialogProperties)
{
    if (!info[0]->IsObject()) {
        return ;
    }
    AppearDialogEvent(info, dialogProperties);
    DisappearDialogEvent(info, dialogProperties);
}

void JSViewAbstract::SetDialogHoverModeProperties(const JSRef<JSObject>& obj, DialogProperties& properties)
{
    auto enableHoverModeValue = obj->GetProperty("enableHoverMode");
    if (enableHoverModeValue->IsBoolean()) {
        properties.enableHoverMode = enableHoverModeValue->ToBoolean();
    }

    // Parse hoverModeArea
    auto hoverModeAreaValue = obj->GetProperty("hoverModeArea");
    if (hoverModeAreaValue->IsNumber()) {
        auto hoverModeArea = hoverModeAreaValue->ToNumber<int32_t>();
        if (hoverModeArea >= 0 && hoverModeArea < static_cast<int32_t>(HOVER_MODE_AREA_TYPE.size())) {
            properties.hoverModeArea = HOVER_MODE_AREA_TYPE[hoverModeArea];
        }
    }
}

void JSViewAbstract::SetDialogBlurStyleOption(const JSRef<JSObject>& obj, DialogProperties& properties)
{
    auto blurStyleValue = obj->GetProperty("backgroundBlurStyleOptions");
    if (blurStyleValue->IsObject()) {
        if (!properties.blurStyleOption.has_value()) {
            properties.blurStyleOption.emplace();
        }
        JSViewAbstract::ParseBlurStyleOption(blurStyleValue, properties.blurStyleOption.value());
    }
}

void JSViewAbstract::SetDialogEffectOption(const JSRef<JSObject>& obj, DialogProperties& properties)
{
    auto effectOptionValue = obj->GetProperty("backgroundEffect");
    if (effectOptionValue->IsObject()) {
        if (!properties.effectOption.has_value()) {
            properties.effectOption.emplace();
        }
        JSViewAbstract::ParseEffectOption(effectOptionValue, properties.effectOption.value());
    }
}

void JSViewPopups::ParseMenuOutlineWidth(const JSRef<JSVal>& outlineWidthValue, NG::MenuParam& menuParam)
{
    NG::BorderWidthProperty outlineWidth;
    CalcDimension borderWidth;
    if (JSViewAbstract::ParseJsDimensionVp(outlineWidthValue, borderWidth)) {
        if (borderWidth.IsNegative() || borderWidth.Unit() == DimensionUnit::PERCENT) {
            outlineWidth.SetBorderWidth(Dimension { -1 });
            menuParam.outlineWidth = outlineWidth;
            return;
        }
        outlineWidth.SetBorderWidth(borderWidth);
        menuParam.outlineWidth = outlineWidth;
        return;
    }
    if (!outlineWidthValue->IsObject()) {
        outlineWidth.SetBorderWidth(Dimension { -1 });
        menuParam.outlineWidth = outlineWidth;
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(outlineWidthValue);
    CalcDimension left;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("left"), left) && left.IsNonNegative()) {
        if (left.Unit() == DimensionUnit::PERCENT) {
            left.Reset();
        }
        outlineWidth.leftDimen = left;
    }
    CalcDimension right;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("right"), right) && right.IsNonNegative()) {
        if (right.Unit() == DimensionUnit::PERCENT) {
            right.Reset();
        }
        outlineWidth.rightDimen = right;
    }
    CalcDimension top;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("top"), top) && top.IsNonNegative()) {
        if (top.Unit() == DimensionUnit::PERCENT) {
            top.Reset();
        }
        outlineWidth.topDimen = top;
    }
    CalcDimension bottom;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottom"), bottom) && bottom.IsNonNegative()) {
        if (bottom.Unit() == DimensionUnit::PERCENT) {
            bottom.Reset();
        }
        outlineWidth.bottomDimen = bottom;
    }
    menuParam.outlineWidth = outlineWidth;
}

void JSViewPopups::ParseMenuOutlineColor(const JSRef<JSVal>& outlineColorValue, NG::MenuParam& menuParam)
{
    NG::BorderColorProperty outlineColor;
    Color borderColor;
    if (JSViewAbstract::ParseJsColor(outlineColorValue, borderColor)) {
        outlineColor.SetColor(borderColor);
        menuParam.outlineColor = outlineColor;
        ViewAbstractModel::GetInstance()->SetOuterBorderColor(borderColor);
    } else if (outlineColorValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(outlineColorValue);
        Color left;
        if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), left)) {
            outlineColor.leftColor = left;
        }
        Color right;
        if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), right)) {
            outlineColor.rightColor = right;
        }
        Color top;
        if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top)) {
            outlineColor.topColor = top;
        }
        Color bottom;
        if (JSViewAbstract::ParseJsColor(object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom)) {
            outlineColor.bottomColor = bottom;
        }
        menuParam.outlineColor = outlineColor;
    } else {
        auto defaultColor = Color(0x19FFFFFF);
        outlineColor.SetColor(defaultColor);
        menuParam.outlineColor = outlineColor;
    }
}
}