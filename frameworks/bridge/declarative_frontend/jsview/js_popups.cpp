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
#include "core/common/resource/resource_parse_utils.h"

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
constexpr int32_t OUTER_BORDER_WIDTH = 0;
constexpr int32_t INNER_BORDER_WIDTH = 1;
constexpr int32_t OUTER_BORDER_LINEAR_GRADIENT = 0;
constexpr int32_t INNER_BORDER_LINEAR_GRADIENT = 1;
const std::vector<std::string> BORDER_WIDTH_TYPE = {"outlineWidth", "borderWidth"};
const std::vector<std::string> BORDER_LINEAR_GRADIENT_TYPE = {"outlineLinearGradient", "borderLinearGradient"};

const char* START_PROPERTY = "start";
const char* END_PROPERTY = "end";
const char* TOP_PROPERTY = "top";
const char* BOTTOM_PROPERTY = "bottom";
const char* LEFT_PROPERTY = "left";
const char* RIGHT_PROPERTY = "right";
const char* TOP_START_PROPERTY = "topStart";
const char* TOP_END_PROPERTY = "topEnd";
const char* TOP_LEFT_PROPERTY = "topLeft";
const char* TOP_RIGHT_PROPERTY = "topRight";
const char* BOTTOM_START_PROPERTY = "bottomStart";
const char* BOTTOM_END_PROPERTY = "bottomEnd";
const char* BOTTOM_LEFT_PROPERTY = "bottomLeft";
const char* BOTTOM_RIGHT_PROPERTY = "bottomRight";

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
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (JSViewAbstract::ParseJsColor(colorValue, textColor, resObj)) {
            if (popupParam) {
                popupParam->SetTextColorResourceObject(resObj);
                popupParam->SetTextColor(textColor);
            }
        }
    } else {
        if (JSViewAbstract::ParseJsColor(colorValue, textColor)) {
            if (popupParam) {
                popupParam->SetTextColor(textColor);
            }
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
    PopupLinearGradientProperties& popupBorderLinearGradient)
{
    popupBorderLinearGradient.popupDirection = GradientDirection::BOTTOM;
    auto directionValue = obj->GetProperty("direction");
    if (directionValue->IsNumber()) {
        auto gradientDirection = directionValue->ToNumber<int32_t>();
        if (gradientDirection >= static_cast<int32_t>(GradientDirection::LEFT) &&
            gradientDirection <= static_cast<int32_t>(GradientDirection::END_TO_START)) {
            popupBorderLinearGradient.popupDirection = static_cast<GradientDirection>(gradientDirection);
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
    PopupLinearGradientProperties& popupBorderLinearGradient)
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
        popupBorderLinearGradient.gradientColors.push_back(gradientColor);
    }
}

void SetPopupBorderWidthInfo(
    const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam, const int32_t& borderWidthParamFlag)
{
    auto popupBorderWidthVal = popupObj->GetProperty(BORDER_WIDTH_TYPE[borderWidthParamFlag].c_str());
    if (popupBorderWidthVal->IsNull()) {
        return;
    }
    CalcDimension popupBorderWidth;
    RefPtr<ResourceObject> widthResObj = nullptr;
    if (SystemProperties::ConfigChangePerform()) {
        if (!JSViewAbstract::ParseJsDimensionVp(popupBorderWidthVal, popupBorderWidth, widthResObj)) {
            return;
        }
    } else {
        if (!JSViewAbstract::ParseJsDimensionVp(popupBorderWidthVal, popupBorderWidth)) {
            return;
        }
    }

    if (popupBorderWidth.Value() < 0) {
        return;
    }
    if (OUTER_BORDER_WIDTH == borderWidthParamFlag) {
        popupParam->SetOutlineWidthObject(widthResObj);
        popupParam->SetOutlineWidth(popupBorderWidth);
    } else {
        popupParam->SetBorderWidthObject(widthResObj);
        popupParam->SetInnerBorderWidth(popupBorderWidth);
    }
}

void SetPopupBorderLinearGradientInfo(const JSRef<JSObject>& popupObj, const RefPtr<PopupParam>& popupParam,
    const int32_t& borderColorParamFlag)
{
    PopupLinearGradientProperties popupBorderLinearGradient;
    auto borderLinearGradientVal = popupObj->GetProperty(BORDER_LINEAR_GRADIENT_TYPE[borderColorParamFlag].c_str());
    if (borderLinearGradientVal->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(borderLinearGradientVal);
        SetBorderLinearGradientDirection(obj, popupBorderLinearGradient);
        SetBorderLinearGradientColors(obj, popupBorderLinearGradient);
        if (OUTER_BORDER_LINEAR_GRADIENT == borderColorParamFlag) {
            popupParam->SetOutlineLinearGradient(popupBorderLinearGradient);
        } else {
            popupParam->SetInnerBorderLinearGradient(popupBorderLinearGradient);
        }
    }
}

void ParsePopupMask(const RefPtr<PopupParam>& popupParam, bool maskValueBool, JSRef<JSVal>& maskValue)
{
    if (!popupParam) {
        return;
    }
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (JSViewAbstract::ParseJsBool(maskValue, maskValueBool, resObj)) {
            popupParam->SetMaskResourceObject(resObj);
            popupParam->SetBlockEvent(maskValueBool);
        }
    } else {
        if (maskValue->IsBoolean()) {
            popupParam->SetBlockEvent(maskValue->ToBoolean());
        }
    }
}

void ParsePopupChildWidth(const RefPtr<PopupParam>& popupParam, JSRef<JSVal>& childWidthVal)
{
    if (!popupParam) {
        return;
    }

    CalcDimension width;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> widthResObj = nullptr;
        if (JSViewAbstract::ParseJsDimensionVp(childWidthVal, width, widthResObj)) {
            popupParam->SetWidthResourceObject(widthResObj);
            if (width.Value() > 0) {
                popupParam->SetChildWidth(width);
            }
        }
    } else {
        if (JSViewAbstract::ParseJsDimensionVp(childWidthVal, width)) {
            if (width.Value() > 0) {
                popupParam->SetChildWidth(width);
            }
        }
    }
}

void ParseArrowWidth(const RefPtr<PopupParam>& popupParam, JSRef<JSVal>& arrowWidthVal)
{
    bool setError = true;
    CalcDimension arrowWidth;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> arrowWidthhResObj = nullptr;
        if (JSViewAbstract::ParseJsDimensionVp(arrowWidthVal, arrowWidth, arrowWidthhResObj)) {
            popupParam->SetArrowWidthResourceObject(arrowWidthhResObj);
            if (arrowWidth.Value() > 0 && arrowWidth.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowWidth(arrowWidth);
                setError = false;
            }
        }
    } else {
        if (JSViewAbstract::ParseJsDimensionVp(arrowWidthVal, arrowWidth)) {
            if (arrowWidth.Value() > 0 && arrowWidth.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowWidth(arrowWidth);
                setError = false;
            }
        }
    }

    popupParam->SetErrorArrowWidth(setError);
}

void ParseArrowHeight(const RefPtr<PopupParam>& popupParam, JSRef<JSVal>& arrowHeightVal)
{
    bool setError = true;
    CalcDimension arrowHeight;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> arrowHeighthResObj = nullptr;
        if (JSViewAbstract::ParseJsDimensionVp(arrowHeightVal, arrowHeight, arrowHeighthResObj)) {
            popupParam->SetArrowHeightResourceObject(arrowHeighthResObj);
            if (arrowHeight.Value() > 0 && arrowHeight.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowHeight(arrowHeight);
                setError = false;
            }
        }
    } else {
        if (JSViewAbstract::ParseJsDimensionVp(arrowHeightVal, arrowHeight)) {
            if (arrowHeight.Value() > 0 && arrowHeight.Unit() != DimensionUnit::PERCENT) {
                popupParam->SetArrowHeight(arrowHeight);
                setError = false;
            }
        }
    }

    popupParam->SetErrorArrowHeight(setError);
}

void ParseRadius(const RefPtr<PopupParam>& popupParam, JSRef<JSVal>& radiusVal)
{
    bool setError = true;
    CalcDimension radius;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> radiusResObj = nullptr;
        if (JSViewAbstract::ParseJsDimensionVp(radiusVal, radius, radiusResObj)) {
            popupParam->SetRadiusResourceObject(radiusResObj);
            if (radius.Value() >= 0) {
                popupParam->SetRadius(radius);
                setError = false;
            }
        }
    } else {
        if (JSViewAbstract::ParseJsDimensionVp(radiusVal, radius)) {
            if (radius.Value() >= 0) {
                popupParam->SetRadius(radius);
                setError = false;
            }
        }
    }

    popupParam->SetErrorRadius(setError);
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

    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (targetNode) {
        bool isWithTheme = targetNode->GetLocalColorMode() != ColorMode::COLOR_MODE_UNDEFINED;
        popupParam->SetIsWithTheme(isWithTheme);
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
            popupParam->SetHasPlacement(true);
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
    bool maskValueBool = false;
    ParsePopupMask(popupParam, maskValueBool, maskValue);

    if (maskValue->IsObject()) {
        auto maskObj = JSRef<JSObject>::Cast(maskValue);
        auto colorValue = maskObj->GetProperty("color");
        Color maskColor;
        if (SystemProperties::ConfigChangePerform()) {
            RefPtr<ResourceObject> resObj;
            if (JSViewAbstract::ParseJsColor(colorValue, maskColor, resObj)) {
                popupParam->SetMaskColorResourceObject(resObj);
                popupParam->SetMaskColor(maskColor);
            }
        } else {
            if (JSViewAbstract::ParseJsColor(colorValue, maskColor)) {
                popupParam->SetMaskColor(maskColor);
            }
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
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (JSViewAbstract::ParseJsColor(popupColorVal, backgroundColor, resObj)) {
            popupParam->SetPopupColorResourceObject(resObj);
            popupParam->SetBackgroundColor(backgroundColor);
        }
    } else {
        if (JSViewAbstract::ParseJsColor(popupColorVal, backgroundColor)) {
            popupParam->SetBackgroundColor(backgroundColor);
        }
    }

    auto autoCancelVal = popupObj->GetProperty("autoCancel");
    if (autoCancelVal->IsBoolean()) {
        popupParam->SetHasAction(!autoCancelVal->ToBoolean());
    }

    auto childWidthVal = popupObj->GetProperty("width");
    if (!childWidthVal->IsNull()) {
        ParsePopupChildWidth(popupParam, childWidthVal);
    }

    auto arrowWidthVal = popupObj->GetProperty("arrowWidth");
    if (!arrowWidthVal->IsNull()) {
        ParseArrowWidth(popupParam, arrowWidthVal);
    }

    auto arrowHeightVal = popupObj->GetProperty("arrowHeight");
    if (!arrowHeightVal->IsNull()) {
        ParseArrowHeight(popupParam, arrowHeightVal);
    }

    auto radiusVal = popupObj->GetProperty("radius");
    if (!radiusVal->IsNull()) {
        ParseRadius(popupParam, radiusVal);
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
    auto avoidTargetValue = popupObj->GetProperty("avoidTarget");
    if (avoidTargetValue->IsNumber()) {
        auto avoidTargetNumValue = avoidTargetValue->ToNumber<int32_t>();
        if (avoidTargetNumValue >= static_cast<int>(AvoidanceMode::COVER_TARGET) &&
            avoidTargetNumValue <= static_cast<int>(AvoidanceMode::AVOID_AROUND_TARGET)) {
            popupParam->SetAvoidTarget(static_cast<AvoidanceMode>(avoidTargetNumValue));
        }
    }
    SetPopupBorderWidthInfo(popupObj, popupParam, OUTER_BORDER_WIDTH);
    SetPopupBorderWidthInfo(popupObj, popupParam, INNER_BORDER_WIDTH);
    SetPopupBorderLinearGradientInfo(popupObj, popupParam, OUTER_BORDER_LINEAR_GRADIENT);
    SetPopupBorderLinearGradientInfo(popupObj, popupParam, INNER_BORDER_LINEAR_GRADIENT);
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
    auto showAtAnchor = tipsObj->GetProperty("showAtAnchor");
    if (showAtAnchor->IsNumber()) {
        auto type = static_cast<TipsAnchorType>(showAtAnchor->ToNumber<int32_t>());
        if (type == TipsAnchorType::TARGET || type == TipsAnchorType::CURSOR) {
            tipsParam->SetAnchorType(type);
        }
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
    RefPtr<ResourceObject> borderRadiusResObj;
    if (JSViewAbstract::ParseJsDimensionVp(borderRadiusValue, borderRadius, borderRadiusResObj)) {
        if (GreatOrEqual(borderRadius.Value(), 0.0f)) {
            menuBorderRadius.SetRadius(borderRadius);
            menuBorderRadius.multiValued = false;
            ParseMenuBorderRadiusWithResourceObj(borderRadiusResObj, menuBorderRadius);
            menuParam.borderRadius = menuBorderRadius;
        };
    } else if (borderRadiusValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(borderRadiusValue);
        JSViewAbstract::ParseAllBorderRadiuses(object, menuBorderRadius);
        menuParam.borderRadius = menuBorderRadius;
    }
}

void JSViewPopups::ParseMenuBorderRadiusWithResourceObj(const RefPtr<ResourceObject>& borderRadiusResObj,
    NG::BorderRadiusProperty& menuBorderRadius)
{
    if (borderRadiusResObj) {
        auto&& updateFunc =
        [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& borderRadiusProp) {
            CalcDimension radius;
            ResourceParseUtils::ParseResDimensionVp(resObj, radius);
            borderRadiusProp.SetRadius(radius);
            borderRadiusProp.multiValued = false;
        };
        menuBorderRadius.AddResource("borderRadius.radius", borderRadiusResObj, std::move(updateFunc));
    }
}

void JSViewPopups::ParseMenuArrowParam(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto enableArrowValue = menuOptions->GetProperty("enableArrow");
    if (enableArrowValue->IsBoolean()) {
        menuParam.enableArrow = enableArrowValue->ToBoolean();
    }
    auto enableArrow = menuParam.enableArrow.has_value() && menuParam.enableArrow.value();
    RefPtr<ResourceObject> arrowOffsetResObj;
    auto arrowOffset = menuOptions->GetProperty("arrowOffset");
    CalcDimension offset;
    if (enableArrow && JSViewAbstract::ParseJsDimensionVp(arrowOffset, offset, arrowOffsetResObj)) {
        menuParam.arrowOffset = offset;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MenuParam& menuParam) {
        CalcDimension offset;
        if (ResourceParseUtils::ParseResDimensionVp(resObj, offset)) {
            menuParam.arrowOffset = offset;
        }
    };
    if (enableArrow && arrowOffsetResObj) {
        menuParam.AddResource("arrowOffset", arrowOffsetResObj, std::move(updateFunc));
    }
    // if enableArrow is true and placement not set, set placement default value to top.
    if (menuParam.enableArrow.has_value() && !menuParam.placement.has_value() && menuParam.enableArrow.value()) {
        menuParam.placement = Placement::TOP;
    }
}

void JSViewPopups::ParseMenuShowInSubWindowParam(
    const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam, bool isCheckThemeValue)
{
    auto showInSubWindowValue = menuOptions->GetProperty("showInSubWindow");
    if (isCheckThemeValue) {
        JSViewPopups::GetMenuShowInSubwindow(menuParam);
        if (!menuParam.isShowInSubWindow) {
            return;
        }
    }
    if (showInSubWindowValue->IsBoolean()) {
        menuParam.isShowInSubWindow = showInSubWindowValue->ToBoolean();
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

void JSViewPopups::ParseLayoutRegionMargin(const JSRef<JSVal>& jsValue, std::optional<CalcDimension>& calcDimension,
    RefPtr<ResourceObject>& resObj)
{
    CalcDimension dimension;
    if (!JSViewAbstract::ParseJsDimensionVpNG(jsValue, dimension, resObj, true)) {
        return;
    }

    if (dimension.IsNonNegative() && dimension.CalcValue().find("calc") == std::string::npos) {
        calcDimension = dimension;
    }
}

void JSViewPopups::ParseResLayoutRegionMargin(const RefPtr<ResourceObject>& resObj,
    std::optional<CalcDimension>& calcDimension)
{
    CHECK_NULL_VOID(resObj);
    CalcDimension dimension;
    if (!ResourceParseUtils::ParseResDimensionVpNG(resObj, dimension, true)) {
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
    CommonCalcDimension calcDimension;
    auto object = JSRef<JSObject>::Cast(marginVal);
    RefPtr<ResourceObject> dimensionTopResObj;
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("top"), calcDimension.top, dimensionTopResObj);
    RefPtr<ResourceObject> dimensionBottomResObj;
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("bottom"), calcDimension.bottom, dimensionBottomResObj);
    RefPtr<ResourceObject> dimensionLeftResObj;
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("left"), calcDimension.left, dimensionLeftResObj);
    RefPtr<ResourceObject> dimensionRightResObj;
    JSViewPopups::ParseLayoutRegionMargin(object->GetProperty("right"), calcDimension.right, dimensionRightResObj);
    if (calcDimension.left.has_value() || calcDimension.right.has_value() ||
        calcDimension.top.has_value() || calcDimension.bottom.has_value()) {
        menuParam.layoutRegionMargin = JSViewAbstract::GetLocalizedPadding(
            calcDimension.top, calcDimension.bottom, calcDimension.left, calcDimension.right);
    }
    auto&& nullFunc = [](const RefPtr<ResourceObject>& resObj, NG::MenuParam& menuParam) {
    };
    menuParam.AddResource("layoutRegionMargin.top", dimensionTopResObj, std::move(nullFunc));
    menuParam.AddResource("layoutRegionMargin.bottom", dimensionBottomResObj, std::move(nullFunc));
    menuParam.AddResource("layoutRegionMargin.left", dimensionLeftResObj, std::move(nullFunc));
    menuParam.AddResource("layoutRegionMargin.right", dimensionRightResObj, std::move(nullFunc));
    RefPtr<ResourceObject> commonCalcDimensionResObj;
    for (const auto& obj : {dimensionTopResObj, dimensionBottomResObj, dimensionLeftResObj, dimensionRightResObj}) {
        if (obj) {
            commonCalcDimensionResObj = obj;
            break;
        }
    }
    if (commonCalcDimensionResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& commonCalcDimensionResObj, NG::MenuParam& menuParam) {
            CommonCalcDimension calcDimension;
            ParseResLayoutRegionMargin(menuParam.GetResource("layoutRegionMargin.top"), calcDimension.top);
            ParseResLayoutRegionMargin(menuParam.GetResource("layoutRegionMargin.bottom"), calcDimension.bottom);
            ParseResLayoutRegionMargin(menuParam.GetResource("layoutRegionMargin.left"), calcDimension.left);
            ParseResLayoutRegionMargin(menuParam.GetResource("layoutRegionMargin.right"), calcDimension.right);
            if (calcDimension.left.has_value() || calcDimension.right.has_value() ||
                calcDimension.top.has_value() || calcDimension.bottom.has_value()) {
                    menuParam.layoutRegionMargin = JSViewAbstract::GetLocalizedPadding(
                        calcDimension.top, calcDimension.bottom, calcDimension.left, calcDimension.right);
            }
        };
        menuParam.AddResource("layoutRegionMargin", commonCalcDimensionResObj, std::move(updateFunc));
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

void JSViewPopups::ParseMenuModalMode(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto modalModeProperty = menuOptions->GetProperty("modalMode");
    if (!modalModeProperty->IsNumber()) {
        return;
    }
    auto modalMode = modalModeProperty->ToNumber<int32_t>();
    if (modalMode == static_cast<int32_t>(ModalMode::TARGET_WINDOW)) {
        menuParam.modalMode = ModalMode::TARGET_WINDOW;
    } else if (modalMode == static_cast<int32_t>(ModalMode::NONE)) {
        menuParam.modalMode = ModalMode::NONE;
    } else if (modalMode == static_cast<int32_t>(ModalMode::AUTO)) {
        menuParam.modalMode = ModalMode::AUTO;
    }
}

void JSViewPopups::ParseMenuPreviewScaleMode(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto previewScaleModeProperty = menuOptions->GetProperty("previewScaleMode");
    if (!previewScaleModeProperty->IsNumber()) {
        return;
    }
    auto previewScaleMode = previewScaleModeProperty->ToNumber<int32_t>();
    if (previewScaleMode == static_cast<int32_t>(NG::PreviewScaleMode::AUTO)) {
        menuParam.previewScaleMode = NG::PreviewScaleMode::AUTO;
    } else if (previewScaleMode == static_cast<int32_t>(NG::PreviewScaleMode::CONSTANT)) {
        menuParam.previewScaleMode = NG::PreviewScaleMode::CONSTANT;
    } else if (previewScaleMode == static_cast<int32_t>(NG::PreviewScaleMode::MAINTAIN)) {
        menuParam.previewScaleMode = NG::PreviewScaleMode::MAINTAIN;
    }
}

void JSViewPopups::ParseMenuAvailableLayoutArea(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto availableLayoutAreaModeProperty = menuOptions->GetProperty("availableLayoutArea");
    if (!availableLayoutAreaModeProperty->IsNumber()) {
        return;
    }
    auto availableLayoutAreaMode = availableLayoutAreaModeProperty->ToNumber<int32_t>();
    if (availableLayoutAreaMode == static_cast<int32_t>(NG::AvailableLayoutAreaMode::SAFE_AREA)) {
        menuParam.availableLayoutAreaMode = NG::AvailableLayoutAreaMode::SAFE_AREA;
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

void JSViewPopups::ParseMenuMaskType(const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto maskValue = menuOptions->GetProperty("mask");
    if (maskValue->IsBoolean()) {
        menuParam.maskEnable = maskValue->ToBoolean();
    } else if (maskValue->IsObject()) {
        menuParam.maskEnable = true;
        if (!menuParam.maskType.has_value()) {
            menuParam.maskType.emplace();
        }
        auto maskObj = JSRef<JSObject>::Cast(maskValue);
        auto colorValue = maskObj->GetProperty("color");
        Color maskColor;
        if (JSViewAbstract::ParseJsColor(colorValue, maskColor)) {
            menuParam.maskType->maskColor = maskColor;
        }
        auto backgroundBlurStyleValue = maskObj->GetProperty("backgroundBlurStyle");
        if (backgroundBlurStyleValue->IsNumber()) {
            auto blurStyle = backgroundBlurStyleValue->ToNumber<int32_t>();
            if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
                blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
                menuParam.maskType->maskBackGroundBlurStyle = static_cast<BlurStyle>(blurStyle);
            }
        }
    }
}

void JSViewPopups::ParseMenuAppearLifeCycleParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onWillAppearValue = menuOptions->GetProperty("onWillAppear");
    if (onWillAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnWillAppearValue =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillAppearValue));
        auto onWillAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnWillAppearValue),
                                    node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onWillAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onWillAppear = std::move(onWillAppear);
    }

    auto onDidAppearValue = menuOptions->GetProperty("onDidAppear");
    if (onDidAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnDidAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidAppearValue));
        auto onDidAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDidAppearFunc),
                                    node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDidAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onDidAppear = std::move(onDidAppear);
    }
}

void JSViewPopups::ParseMenuDisappearLifeCycleParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onWillDisappearValue = menuOptions->GetProperty("onWillDisappear");
    if (onWillDisappearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnWillDisappearValueFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onWillDisappearValue));
        auto onWillDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnWillDisappearValueFunc),
                                    node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onWillDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onWillDisappear = std::move(onWillDisappear);
    }

    auto onDidDisappearValue = menuOptions->GetProperty("onDidDisappear");
    if (onDidDisappearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnDidDisappearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDidDisappearValue));
        auto onDidDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDidDisappearFunc),
                                    node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDidDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onDidDisappear = std::move(onDidDisappear);
    }
}

void JSViewPopups::ParseMenuParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto offsetVal = menuOptions->GetProperty("offset");
    if (offsetVal->IsObject()) {
        auto offsetObj = JSRef<JSObject>::Cast(offsetVal);
        JSViewPopups::ParseMenuoffsetParam(offsetObj, menuParam);
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
    RefPtr<ResourceObject> backgroundColorResObj;
    if (JSViewAbstract::ParseJsColor(backgroundColorValue, backgroundColor, backgroundColorResObj)) {
        menuParam.backgroundColor = backgroundColor;
    }
    if (backgroundColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, NG::MenuParam& menuParam) {
            Color backgroundColor;
            if (ResourceParseUtils::ParseResColor(colorResObj, backgroundColor)) {
                menuParam.backgroundColor = backgroundColor;
            }
        };
        menuParam.AddResource("backgroundColor", backgroundColorResObj, std::move(updateFunc));
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
    JSViewPopups::ParseMenuAppearLifeCycleParam(info, menuOptions, menuParam);
    JSViewPopups::ParseMenuDisappearLifeCycleParam(info, menuOptions, menuParam);

    auto menuTransition = menuOptions->GetProperty("transition");
    menuParam.hasTransitionEffect = false;
    if (menuTransition->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(menuTransition);
        menuParam.hasTransitionEffect = true;
        menuParam.transition = JSViewAbstract::ParseChainedTransition(obj, info.GetExecutionContext());
    }
    JSViewPopups::ParseMenuShowInSubWindowParam(menuOptions, menuParam);
    JSViewPopups::ParseMenuArrowParam(menuOptions, menuParam);
    JSViewPopups::ParseMenuBorderRadius(menuOptions, menuParam);
    JSViewPopups::ParseMenuLayoutRegionMarginParam(menuOptions, menuParam);
    JSViewPopups::ParseMenuBlurStyleOption(menuOptions, menuParam);
    JSViewPopups::ParseMenuEffectOption(menuOptions, menuParam);
    JSViewPopups::ParseMenuHapticFeedbackMode(menuOptions, menuParam);
    JSViewPopups::ParseMenuModalMode(menuOptions, menuParam);
    JSViewPopups::ParseMenuPreviewScaleMode(menuOptions, menuParam);
    JSViewPopups::ParseMenuAvailableLayoutArea(menuOptions, menuParam);
    auto outlineWidthValue = menuOptions->GetProperty("outlineWidth");
    JSViewPopups::ParseMenuOutlineWidth(outlineWidthValue, menuParam);
    auto outlineColorValue = menuOptions->GetProperty("outlineColor");
    JSViewPopups::ParseMenuOutlineColor(outlineColorValue, menuParam);
    JSViewPopups::ParseMenuMaskType(menuOptions, menuParam);

    auto anchorPositionVal = menuOptions->GetProperty("anchorPosition");
    if (anchorPositionVal->IsObject()) {
        auto anchorPositionObj = JSRef<JSObject>::Cast(anchorPositionVal);
        JSRef<JSVal> xVal = anchorPositionObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X));
        JSRef<JSVal> yVal = anchorPositionObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y));
        CalcDimension dx;
        CalcDimension dy;
        if (JSViewAbstract::ParseJsDimensionVp(xVal, dx)) {
            menuParam.anchorPosition.SetX(dx.ConvertToPx());
        }
        if (JSViewAbstract::ParseJsDimensionVp(yVal, dy)) {
            menuParam.anchorPosition.SetY(dy.ConvertToPx());
        }
        menuParam.isAnchorPosition = true;
        if (LessNotEqual(menuParam.anchorPosition.GetX(), 0.0f) &&
            LessNotEqual(menuParam.anchorPosition.GetY(), 0.0f)) {
            menuParam.isAnchorPosition = false;
            menuParam.placement = Placement::BOTTOM_LEFT;
        }
    }
}

void JSViewPopups::ParseMenuoffsetParam(const JSRef<JSObject>& offsetObj, NG::MenuParam& menuParam)
{
    JSRef<JSVal> xVal = offsetObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X));
    JSRef<JSVal> yVal = offsetObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y));
    CalcDimension dx;
    CalcDimension dy;
    RefPtr<ResourceObject> offsetDxResObj;
    if (JSViewAbstract::ParseJsDimensionVp(xVal, dx, offsetDxResObj)) {
        menuParam.positionOffset.SetX(dx.ConvertToPx());
    }
    RefPtr<ResourceObject> offsetDyResObj;
    if (JSViewAbstract::ParseJsDimensionVp(yVal, dy, offsetDyResObj)) {
        menuParam.positionOffset.SetY(dy.ConvertToPx());
    }
    if (offsetDxResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MenuParam& menuParam) {
            CalcDimension dx;
            ResourceParseUtils::ParseResDimensionVp(resObj, dx);
            menuParam.positionOffset.SetX(dx.ConvertToPx());
        };
        menuParam.AddResource("offset.dx", offsetDxResObj, std::move(updateFunc));
    }
    if (offsetDyResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MenuParam& menuParam) {
            CalcDimension dy;
            ResourceParseUtils::ParseResDimensionVp(resObj, dy);
            menuParam.positionOffset.SetY(dy.ConvertToPx());
        };
        menuParam.AddResource("offset.dy", offsetDyResObj, std::move(updateFunc));
    }
}

void JSViewPopups::InitMenuParamColorMode(NG::MenuParam& menuParam)
{
    auto node = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(node);
    auto localColorMode = node->GetLocalColorMode();
    menuParam.isWithTheme = (localColorMode != ColorMode::COLOR_MODE_UNDEFINED);
    auto colorMode = Container::CurrentColorMode();
    menuParam.isDarkMode = (colorMode == ColorMode::DARK);
}

void JSViewPopups::ParseBindOptionParam(const JSCallbackInfo& info, NG::MenuParam& menuParam, size_t optionIndex)
{
    if (!info[optionIndex]->IsObject()) {
        return;
    }
    auto menuOptions = JSRef<JSObject>::Cast(info[optionIndex]);
    RefPtr<ResourceObject> titleResObj;
    JSViewAbstract::ParseJsString(menuOptions->GetProperty("title"), menuParam.title, titleResObj);
    if (titleResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::MenuParam& menuParam) {
            ResourceParseUtils::ParseResString(resObj, menuParam.title);
        };
        menuParam.AddResource("title", titleResObj, std::move(updateFunc));
    }
    JSViewPopups::InitMenuParamColorMode(menuParam);
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
        if (menuParam.previewMode != MenuPreviewMode::CUSTOM ||
            menuParam.hasPreviewTransitionEffect ||menuParam.hasTransitionEffect ||
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
        auto hoverInterruptValue = animationOptionsObj->GetProperty("hoverScaleInterruption");
        if (hoverInterruptValue->IsBoolean()) {
            menuParam.hoverScaleInterruption = hoverInterruptValue->ToBoolean();
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
    JSViewPopups::ParseMenuPreviewBorderRadius(previewBorderRadiusValue, previewBorderRadius);
    menuParam.previewBorderRadius = previewBorderRadius;
}

void ParseBindContentOptionParam(const JSCallbackInfo& info, const JSRef<JSVal>& args, NG::MenuParam& menuParam,
    std::function<void()>& previewBuildFunc)
{
    if (!args->IsObject()) {
        return;
    }
    auto menuContentOptions = JSRef<JSObject>::Cast(args);
    JSViewPopups::InitMenuParamColorMode(menuParam);
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
        auto infoParam = info[0];
        if (!infoParam->IsObject()) {
            return;
        }
        auto* spanString = JSRef<JSObject>::Cast(infoParam)->Unwrap<JSSpanString>();
        if (!spanString) {
            JSViewAbstract::ParseJsString(infoParam, value);
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
    if (menuParam.previewMode != MenuPreviewMode::NONE) {
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
            ParseEnableSafeArea(info[NUM_SECOND], contentCoverParam);
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
    auto modalTransitionValue = paramObj->GetProperty("modalTransition");
    ParseModalTransition(modalTransitionValue, modalStyle.modalTransition, NG::ModalTransition::DEFAULT);
    auto backgroundColor = paramObj->GetProperty("backgroundColor");
    Color color;
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the modal background color and its resource are parsed together.
        RefPtr<ResourceObject> resObj;
        if (ParseJsColor(backgroundColor, color, resObj)) {
            modalStyle.SetBackgroundColorResObj(resObj);
            modalStyle.backgroundColor = color;
        }
    } else {
        if (ParseJsColor(backgroundColor, color)) {
            modalStyle.backgroundColor = color;
        }
    }
}

void JSViewAbstract::ParseModalTransition(const JSRef<JSVal>& jsValue,
    std::optional<NG::ModalTransition>& modalTransition, NG::ModalTransition defaultTransition)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        modalTransition = defaultTransition;
    } else if (jsValue->IsNumber()) {
        auto transitionNumber = jsValue->ToNumber<int32_t>();
        if (transitionNumber >= TRANSITION_NUM_ZERO && transitionNumber <= TRANSITION_NUM_TWO) {
            modalTransition = static_cast<NG::ModalTransition>(transitionNumber);
        } else {
            modalTransition = defaultTransition;
        }
    }
}

void JSViewAbstract::ParseEnableSafeArea(const JSRef<JSObject>& paramObj, NG::ContentCoverParam& contentCoverParam)
{
    auto enableSafeArea = paramObj->GetProperty("enableSafeArea");
    if (enableSafeArea->IsBoolean()) {
        bool enable = enableSafeArea->ToBoolean();
        contentCoverParam.enableSafeArea = enable;
    }
}

bool JSViewAbstract::ParseSheetIsShow(const JSCallbackInfo& info, const std::string& name,
    std::function<void(const std::string&)>& callback)
{
    bool isShow = false;
    auto tmpInfo = info[0];
    if (tmpInfo->IsBoolean()) {
        isShow = tmpInfo->ToBoolean();
    } else if (tmpInfo->IsObject()) {
        JSRef<JSObject> callbackObj = JSRef<JSObject>::Cast(tmpInfo);
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
    sheetStyle.enableFloatingDragBar = false;
    sheetStyle.showDragBar = true;
    sheetStyle.showCloseIcon = true;
    sheetStyle.showInPage = false;
    std::function<void()> onAppearCallback;
    std::function<void()> onDisappearCallback;
    std::function<void()> onWillAppearCallback;
    std::function<void()> onWillDisappearCallback;
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
    auto floatingDragBar = paramObj->GetProperty("enableFloatingDragBar");
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
    if (ParseSheetDetents(sheetDetents, detents, sheetStyle)) {
        sheetStyle.detents = detents;
    }
    BlurStyleOption styleOption;
    if (ParseSheetBackgroundBlurStyle(backgroundBlurStyle, styleOption)) {
        sheetStyle.backgroundBlurStyle = styleOption;
    }

    if (showDragBar->IsBoolean()) {
        sheetStyle.showDragBar = showDragBar->ToBoolean();
    } else if (isPartialUpdate) {
        sheetStyle.showDragBar.reset();
    } else {
        sheetStyle.showDragBar = true;
    }

    if (floatingDragBar->IsBoolean()) {
        sheetStyle.enableFloatingDragBar = floatingDragBar->ToBoolean();
    } else if (isPartialUpdate) {
        sheetStyle.enableFloatingDragBar.reset();
    } else {
        sheetStyle.enableFloatingDragBar = false;
    }

    if (type->IsNull() || type->IsUndefined()) {
        sheetStyle.sheetType.reset();
    } else {
        if (type->IsNumber()) {
            auto sheetType = type->ToNumber<int32_t>();
            if (sheetType >= static_cast<int>(NG::SheetType::SHEET_BOTTOM) &&
                sheetType <= static_cast<int>(NG::SheetType::SHEET_CONTENT_COVER)) {
                sheetStyle.sheetType = static_cast<NG::SheetType>(sheetType);
            }
        }
    }

    bool isInteractive = false;
    if (ParseJsBool(interactive, isInteractive)) {
        sheetStyle.interactive = isInteractive;
    } else if (!isPartialUpdate && NG::SheetType::SHEET_CONTENT_COVER == sheetStyle.sheetType) {
        sheetStyle.interactive = true;
    }

    bool showClose = true;
    if (NG::SheetType::SHEET_CONTENT_COVER == sheetStyle.sheetType) {
        sheetStyle.showCloseIcon = false;
    } else if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet closeIcon and its resource are parsed together.
        RefPtr<ResourceObject> resObj;
        if (ParseJsBool(showCloseIcon, showClose, resObj)) {
            sheetStyle.showCloseIcon = showClose;
            sheetStyle.SetShowCloseResObj(resObj);
        } else if (!isPartialUpdate) {
            sheetStyle.showCloseIcon = true;
        }
    } else {
        if (ParseJsBool(showCloseIcon, showClose)) {
            sheetStyle.showCloseIcon = showClose;
        } else if (!isPartialUpdate) {
            sheetStyle.showCloseIcon = true;
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
            sheetKeyboardAvoidMode <= static_cast<int>(NG::SheetKeyboardAvoidMode::POPUP_SHEET)) {
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
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet background color and its resource are parsed together.
        RefPtr<ResourceObject> resObj;
        if (ParseJsColor(backgroundColor, color, resObj)) {
            sheetStyle.backgroundColor = color;
            sheetStyle.SetBackgroundColorResObj(resObj);
        }
    } else {
        if (ParseJsColor(backgroundColor, color)) {
            sheetStyle.backgroundColor = color;
        }
    }
    // parse maskColor
    Color parseMaskColor;
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet maskColor and its resource are parsed together.
        RefPtr<ResourceObject> resObj;
        if (!maskColor->IsNull() && !maskColor->IsUndefined() &&
            JSViewAbstract::ParseJsColor(maskColor, parseMaskColor, resObj)) {
            sheetStyle.maskColor = std::move(parseMaskColor);
            sheetStyle.SetMaskColorResObj(resObj);
        }
    } else {
        if (!maskColor->IsNull() && !maskColor->IsUndefined() &&
            JSViewAbstract::ParseJsColor(maskColor, parseMaskColor)) {
            sheetStyle.maskColor = std::move(parseMaskColor);
        }
    }

    // Parse border width
    auto borderWidthValue = paramObj->GetProperty("borderWidth");
    NG::BorderWidthProperty borderWidth;
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet borderWidth and its resource are parsed together.
        RefPtr<ResourceObject> borderWidthResObj;
        if (ParseBorderWidthProps(borderWidthValue, borderWidth, borderWidthResObj)) {
            sheetStyle.borderWidth = borderWidth;
            sheetStyle.SetBorderWidthResObj(borderWidthResObj);

            // When the switch is turned on, the sheet borderColor and its resource are parsed together,
            // when borderWidth and borderColor are set at the same time.
            auto colorValue = paramObj->GetProperty("borderColor");
            NG::BorderColorProperty borderColor;
            RefPtr<ResourceObject> borderColorResObj;
            if (ParseBorderColorProps(colorValue, borderColor, borderColorResObj)) {
                sheetStyle.borderColor = borderColor;
            } else {
                sheetStyle.borderColor =
                    NG::BorderColorProperty({ Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK });
            }
            sheetStyle.SetBorderColorResObj(borderColorResObj);
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
    } else {
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
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet width and its resource are parsed together.
        RefPtr<ResourceObject> resObj;
        if (ParseJsDimensionVpNG(widthValue, width, resObj, true)) {
            sheetStyle.SetSheetWidthResObj(resObj);
            sheetStyle.width = width;
        }
    } else {
        if (ParseJsDimensionVpNG(widthValue, width, true)) {
            sheetStyle.width = width;
        }
    }

    auto radiusValue = paramObj->GetProperty("radius");
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet radius and its resource are parsed together.
        RefPtr<ResourceObject> resObj;
        JSViewAbstract::ParseBindSheetBorderRadius(radiusValue, sheetStyle, resObj);
        sheetStyle.SetRadiusResObj(resObj);
    } else {
        JSViewAbstract::ParseBindSheetBorderRadius(radiusValue, sheetStyle);
    }

    ParseDetentSelection(paramObj, sheetStyle);

    NG::SheetHeight sheetStruct;
    bool parseResult = false;
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet height and its resource are parsed together.
        RefPtr<ResourceObject> heightResObj;
        parseResult = ParseSheetHeight(height, sheetStruct, isPartialUpdate, heightResObj);
        sheetStyle.SetSheetHeightResObj(heightResObj);
    } else {
        parseResult = ParseSheetHeight(height, sheetStruct, isPartialUpdate);
    }
    if (!parseResult) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "parse sheet height in unnormal condition");
    }
    sheetStyle.sheetHeight = sheetStruct;

    ParseSheetSubWindowValue(paramObj, sheetStyle);

    // parse ModalTransition
    auto modalTransitionValue = paramObj->GetProperty("modalTransition");
    ParseModalTransition(modalTransitionValue, sheetStyle.modalTransition, NG::ModalTransition::DEFAULT);
}

void JSViewAbstract::ParseSheetSubWindowValue(const JSRef<JSObject>& paramObj, NG::SheetStyle& sheetStyle)
{
    // parse sheet showInSubWindow
    sheetStyle.showInSubWindow = false;
    // content cover is not shown in sub window
    if (sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == NG::SheetType::SHEET_CONTENT_COVER) {
        sheetStyle.showInSubWindow = false;
        return;
    }
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
    bool parseResult = false;
    if (SystemProperties::ConfigChangePerform()) {
        // When the switch is turned on, the sheet detentSelection and its resource are parsed together.
        RefPtr<ResourceObject> resObj;
        parseResult = ParseSheetHeight(detentSelection, sheetStruct, true, resObj);
        sheetStyle.SetDetentSelectionResObj(resObj);
    } else {
        parseResult = ParseSheetHeight(detentSelection, sheetStruct, true);
    }
    if (!parseResult) {
        sheetStruct.height.reset();
        sheetStruct.sheetMode.reset();
        TAG_LOGD(AceLogTag::ACE_SHEET, "parse sheet detent selection in unnormal condition");
    }
    sheetStyle.detentSelection = sheetStruct;
}
 
bool JSViewAbstract::ParseSheetDetents(const JSRef<JSVal>& args,
    std::vector<NG::SheetHeight>& sheetDetents, NG::SheetStyle& sheetStyle)
{
    if (!args->IsArray()) {
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(args);
    NG::SheetHeight sheetDetent;
    std::vector<RefPtr<ResourceObject>> detentsResObj;
    for (size_t i = 0; i < array->Length(); i++) {
        bool parseResult = false;
        if (SystemProperties::ConfigChangePerform()) {
            // When the switch is turned on, the sheet detents and its resource are parsed together.
            RefPtr<ResourceObject> resObj;
            parseResult = ParseSheetHeight(array->GetValueAt(i), sheetDetent, false, resObj);
            detentsResObj.push_back(resObj);
        } else {
            parseResult = ParseSheetHeight(array->GetValueAt(i), sheetDetent, false);
        }
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
    if (SystemProperties::ConfigChangePerform()) {
        sheetStyle.SetDetentsResObjs(std::move(detentsResObj));
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
        if (SystemProperties::ConfigChangePerform()) {
            // When the switch is turned on, the sheet title and its resource are parsed together.
            RefPtr<ResourceObject> mainTitleResObj;
            if (ParseJsString(sheetTitle, mainTitle, mainTitleResObj)) {
                sheetStyle.sheetTitle = mainTitle;
                sheetStyle.SetMainTitleResObj(mainTitleResObj);
            }

            // When the switch is turned on, the sheet subtitle and its resource are parsed together,
            // when title and subtitle are set at the same time.
            RefPtr<ResourceObject> subTitleResObj;
            if (ParseJsString(sheetSubtitle, subtitle, subTitleResObj)) {
                sheetStyle.sheetSubtitle = subtitle;
                sheetStyle.SetSubTitleResObj(subTitleResObj);
            }
        } else {
            if (ParseJsString(sheetTitle, mainTitle)) {
                sheetStyle.sheetTitle = mainTitle;
            }
            if (ParseJsString(sheetSubtitle, subtitle)) {
                sheetStyle.sheetSubtitle = subtitle;
            }
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
    RefPtr<ResourceObject> resObj;
    return ParseSheetHeight(args, detent, isReset, resObj);
}

bool JSViewAbstract::ParseSheetHeight(const JSRef<JSVal>& args, NG::SheetHeight& detent,
    bool isReset, RefPtr<ResourceObject>& resObj)
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
    if (!ParseJsDimensionVpNG(args, sheetHeight, resObj)) {
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
    JSViewPopups::GetMenuShowInSubwindow(menuParam);
    CHECK_EQUAL_VOID(menuObj->IsEmpty(), true);
    JSViewPopups::InitMenuParamColorMode(menuParam);
    JSViewPopups::ParseMenuParam(info, menuObj, menuParam);
    JSViewPopups::ParseMenuShowInSubWindowParam(menuObj, menuParam, false);
    auto preview = menuObj->GetProperty("preview");
    if (preview->IsNumber()) {
        auto previewMode = preview->ToNumber<int32_t>();
        if (previewMode == static_cast<int32_t>(MenuPreviewMode::IMAGE)) {
            menuParam.previewMode = static_cast<MenuPreviewMode>(previewMode);
            ParseContentPreviewAnimationOptionsParam(info, menuObj, menuParam);
            menuParam.enableArrow = false;
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
    RefPtr<ResourceObject> borderWidthResObj;
    if (JSViewAbstract::ParseJsDimensionVp(outlineWidthValue, borderWidth, borderWidthResObj)) {
        if (borderWidth.IsNegative() || borderWidth.Unit() == DimensionUnit::PERCENT) {
            outlineWidth.SetBorderWidth(Dimension { -1 });
            menuParam.outlineWidth = outlineWidth;
            return;
        }
        outlineWidth.SetBorderWidth(borderWidth);
        ParseMenuOutlineWidthWithResourceObj(borderWidthResObj, outlineWidth);
        menuParam.outlineWidth = outlineWidth;
        return;
    }
    if (!outlineWidthValue->IsObject()) {
        outlineWidth.SetBorderWidth(Dimension { -1 });
        menuParam.outlineWidth = outlineWidth;
        return;
    }
    ParseMenuOutlineWidthObject(outlineWidthValue, menuParam, outlineWidth);
}

void JSViewPopups::ParseMenuOutlineWidthObject(const JSRef<JSVal>& outlineWidthValue, NG::MenuParam& menuParam,
    NG::BorderWidthProperty& outlineWidth)
{
    JSRef<JSObject> object = JSRef<JSObject>::Cast(outlineWidthValue);
    CalcDimension left;
    RefPtr<ResourceObject> leftResObj;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("left"), left, leftResObj) && left.IsNonNegative()) {
        if (left.Unit() == DimensionUnit::PERCENT) {
            left.Reset();
        }
        outlineWidth.leftDimen = left;
    }
    CalcDimension right;
    RefPtr<ResourceObject> rightResObj;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("right"), right, rightResObj) &&
            right.IsNonNegative()) {
        if (right.Unit() == DimensionUnit::PERCENT) {
            right.Reset();
        }
        outlineWidth.rightDimen = right;
    }
    CalcDimension top;
    RefPtr<ResourceObject> topResObj;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("top"), top, topResObj) && top.IsNonNegative()) {
        if (top.Unit() == DimensionUnit::PERCENT) {
            top.Reset();
        }
        outlineWidth.topDimen = top;
    }
    CalcDimension bottom;
    RefPtr<ResourceObject> bottomResObj;
    if (JSViewAbstract::ParseJsDimensionVp(object->GetProperty("bottom"), bottom, bottomResObj) &&
            bottom.IsNonNegative()) {
        if (bottom.Unit() == DimensionUnit::PERCENT) {
            bottom.Reset();
        }
        outlineWidth.bottomDimen = bottom;
    }
    ParseMenuOutlineWidthWithResourceObj(leftResObj, rightResObj, topResObj, bottomResObj, outlineWidth);
    menuParam.outlineWidth = outlineWidth;
}

void JSViewPopups::ParseMenuOutlineWidthWithResourceObj(
    const RefPtr<ResourceObject>& borderWidthResObj, NG::BorderWidthProperty& outlineWidth)
{
    if (borderWidthResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& outlineWidthProp) {
            CalcDimension width;
            ResourceParseUtils::ParseResDimensionVp(resObj, width);
            outlineWidthProp.SetBorderWidth(width);
        };
        outlineWidth.AddResource("outlineWidth.width", borderWidthResObj, std::move(updateFunc));
    }
}

void JSViewPopups::ParseMenuOutlineWidthWithResourceObj(const RefPtr<ResourceObject>& leftResObj,
    const RefPtr<ResourceObject>& rightResObj, const RefPtr<ResourceObject>& topResObj,
    const RefPtr<ResourceObject>& bottomResObj, NG::BorderWidthProperty& outlineWidth)
{
    if (leftResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& outlineWidth) {
            CalcDimension left;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, left) ||
                left.Unit() == DimensionUnit::PERCENT || left.IsNegative()) {
                left.Reset();
            }
            outlineWidth.leftDimen = left;
        };
        outlineWidth.AddResource("outlineWidth.left", leftResObj, std::move(updateFunc));
    }
    if (rightResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& outlineWidth) {
            CalcDimension right;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, right) ||
                right.Unit() == DimensionUnit::PERCENT || right.IsNegative()) {
                right.Reset();
            }
            outlineWidth.rightDimen = right;
        };
        outlineWidth.AddResource("outlineWidth.right", rightResObj, std::move(updateFunc));
    }
    if (topResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& outlineWidth) {
            CalcDimension top;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, top) ||
                top.Unit() == DimensionUnit::PERCENT || top.IsNegative()) {
                top.Reset();
            }
            outlineWidth.topDimen = top;
        };
        outlineWidth.AddResource("outlineWidth.top", topResObj, std::move(updateFunc));
    }
    if (bottomResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderWidthProperty& outlineWidth) {
            CalcDimension bottom;
            if (!ResourceParseUtils::ParseResDimensionVp(resObj, bottom) ||
                bottom.Unit() == DimensionUnit::PERCENT || bottom.IsNegative()) {
                bottom.Reset();
            }
            outlineWidth.bottomDimen = bottom;
        };
        outlineWidth.AddResource("outlineWidth.bottom", bottomResObj, std::move(updateFunc));
    }
}

void JSViewPopups::ParseMenuOutlineColor(const JSRef<JSVal>& outlineColorValue, NG::MenuParam& menuParam)
{
    NG::BorderColorProperty outlineColor;
    Color borderColor;
    RefPtr<ResourceObject> borderColorResObj;
    if (JSViewAbstract::ParseJsColor(outlineColorValue, borderColor, borderColorResObj)) {
        outlineColor.SetColor(borderColor);
        ViewAbstractModel::GetInstance()->SetOuterBorderColor(borderColor);
        ParseMenuOutlineColorWithResourceObj(borderColorResObj, outlineColor);
        menuParam.outlineColor = outlineColor;
    } else if (outlineColorValue->IsObject()) {
        ParseMenuOutlineColorObject(outlineColorValue, menuParam, outlineColor);
    } else {
        auto defaultColor = Color(0x19FFFFFF);
        outlineColor.SetColor(defaultColor);
        menuParam.outlineColor = outlineColor;
    }
}

void JSViewPopups::ParseMenuOutlineColorObject(const JSRef<JSVal>& outlineColorValue, NG::MenuParam& menuParam,
    NG::BorderColorProperty& outlineColor)
{
    JSRef<JSObject> object = JSRef<JSObject>::Cast(outlineColorValue);
    Color left;
    RefPtr<ResourceObject> leftColorResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT)), left, leftColorResObj)) {
        outlineColor.leftColor = left;
    }
    Color right;
    RefPtr<ResourceObject> rightColorResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT)), right, rightColorResObj)) {
        outlineColor.rightColor = right;
    }
    Color top;
    RefPtr<ResourceObject> topColorResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP)), top, topColorResObj)) {
        outlineColor.topColor = top;
    }
    Color bottom;
    RefPtr<ResourceObject> bottomColorResObj;
    if (JSViewAbstract::ParseJsColor(
        object->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM)), bottom, bottomColorResObj)) {
        outlineColor.bottomColor = bottom;
    }
    ParseMenuOutlineColorWithResourceObj(
        leftColorResObj, rightColorResObj, topColorResObj, bottomColorResObj, outlineColor);
    menuParam.outlineColor = outlineColor;
}

void JSViewPopups::ParseMenuOutlineColorWithResourceObj(const RefPtr<ResourceObject>& borderColorResObj,
    NG::BorderColorProperty& outlineColor)
{
    if (borderColorResObj) {
        auto&& updateFunc =
        [](const RefPtr<ResourceObject>& colorResObj, NG::BorderColorProperty& borderColorProp) {
            Color color;
            ResourceParseUtils::ParseResColor(colorResObj, color);
            borderColorProp.SetColor(color);
            ViewAbstractModel::GetInstance()->SetOuterBorderColor(color);
        };
        outlineColor.AddResource("outlineColor.border", borderColorResObj, std::move(updateFunc));
    }
}

void JSViewPopups::ParseMenuOutlineColorWithResourceObj(const RefPtr<ResourceObject>& leftColorResObj,
    const RefPtr<ResourceObject>& rightColorResObj, const RefPtr<ResourceObject>& topColorResObj,
    const RefPtr<ResourceObject>& bottomColorResObj, NG::BorderColorProperty& outlineColor)
{
    if (leftColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, NG::BorderColorProperty& outlineColor) {
            Color left;
            ResourceParseUtils::ParseResColor(colorResObj, left);
            outlineColor.leftColor = left;
        };
        outlineColor.AddResource("outlineColor.left", leftColorResObj, std::move(updateFunc));
    }
    if (rightColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, NG::BorderColorProperty& outlineColor) {
            Color right;
            ResourceParseUtils::ParseResColor(colorResObj, right);
            outlineColor.rightColor = right;
        };
        outlineColor.AddResource("outlineColor.right", rightColorResObj, std::move(updateFunc));
    }
    if (topColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, NG::BorderColorProperty& outlineColor) {
            Color top;
            ResourceParseUtils::ParseResColor(colorResObj, top);
            outlineColor.topColor = top;
        };
        outlineColor.AddResource("outlineColor.top", topColorResObj, std::move(updateFunc));
    }
    if (bottomColorResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, NG::BorderColorProperty& outlineColor) {
            Color bottom;
            ResourceParseUtils::ParseResColor(colorResObj, bottom);
            outlineColor.bottomColor = bottom;
        };
        outlineColor.AddResource("outlineColor.bottom", bottomColorResObj, std::move(updateFunc));
    }
}

bool JSViewPopups::ParseMenuPreviewBorderRadiusObject(const JSRef<JSVal>& args, NG::BorderRadiusProperty& props)
{
    CalcDimension borderRadius;
    RefPtr<ResourceObject> resObj;
    if (!JSViewAbstract::ParseJsDimensionVpNG(args, borderRadius, resObj)) {
        return false;
    }
    props.SetRadius(borderRadius);
    props.multiValued = false;
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& props) {
        CalcDimension radiusValue;
        ResourceParseUtils::ParseResDimensionVpNG(resObj, radiusValue);
        props.SetRadius(radiusValue);
        props.multiValued = false;
    };
    props.AddResource("menu.borderRadius", resObj, std::move(updateFunc));
    return true;
}

void JSViewPopups::SetBorderRadiusProps(
    const CalcDimension& dim, NG::BorderRadiusProperty& props, const char* propName)
{
    if (dim.IsNegative() || propName == nullptr) {
        return;
    }
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (propName == BOTTOM_LEFT_PROPERTY) {
        props.radiusBottomLeft = dim;
    } else if (propName == BOTTOM_RIGHT_PROPERTY) {
        props.radiusBottomRight = dim;
    } else if (propName == TOP_LEFT_PROPERTY) {
        props.radiusTopLeft = dim;
    } else if (propName == TOP_RIGHT_PROPERTY) {
        props.radiusTopRight = dim;
    } else if (propName == TOP_START_PROPERTY || propName == TOP_END_PROPERTY) {
        if (isRightToLeft) {
            props.radiusTopRight = dim;
            return;
        }
        props.radiusTopLeft = dim;
    } else if (propName == BOTTOM_START_PROPERTY || propName == BOTTOM_END_PROPERTY) {
        if (isRightToLeft) {
            props.radiusBottomRight = dim;
            return;
        }
        props.radiusBottomLeft = dim;
    }
}

void JSViewPopups::ParseBorderRadiusProps(
    const char* key, const JSRef<JSObject>& object, NG::BorderRadiusProperty& props)
{
    CHECK_NULL_VOID(key);
    if (!object->HasProperty(key)) {
        return;
    }
    CalcDimension radius;
    RefPtr<ResourceObject> resObj;
    if (JSViewAbstract::ParseJsDimensionVpNG(object->GetProperty(key), radius, resObj)) {
        SetBorderRadiusProps(radius, props, key);
    }
    if (!resObj) {
        return;
    }
    auto&& updateFunc = [key](const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& props) {
        CalcDimension value;
        if (ResourceParseUtils::ParseResDimensionVpNG(resObj, value)) {
            SetBorderRadiusProps(value, props, key);
        }
    };
    props.AddResource("menu.borderRadius." + std::string(key), resObj, std::move(updateFunc));
}

void CheckDimensionUnit(CalcDimension& checkDimension, bool notPercent)
{
    if (notPercent && checkDimension.Unit() == DimensionUnit::PERCENT) {
        checkDimension.Reset();
        return;
    }
}

void JSViewPopups::ParseBorderRadiusPropsByLengthMetrics(
    const char* key, const JSRef<JSObject>& object, NG::BorderRadiusProperty& props)
{
    CHECK_NULL_VOID(key);
    if (!object->HasProperty(key) || !object->GetProperty(key)->IsObject()) {
        return;
    }
    JSRef<JSObject> radiusObj = JSRef<JSObject>::Cast(object->GetProperty(key));
    CalcDimension radius;
    RefPtr<ResourceObject> resObj = nullptr;
    if (JSViewAbstract::ParseJsLengthMetricsVpWithResObj(radiusObj, radius, resObj)) {
        CheckDimensionUnit(radius, false);
        SetBorderRadiusProps(radius, props, key);
    }
    if (!resObj) {
        return;
    }
    auto unit = radius.Unit();
    auto&& updateFunc = [unit, key](
                            const RefPtr<ResourceObject>& resObj, NG::BorderRadiusProperty& props) {
        CalcDimension value;
        if (ResourceParseUtils::ParseResDimension(resObj, value, unit)) {
            CheckDimensionUnit(value, false);
            SetBorderRadiusProps(value, props, key);
        }
    };
    props.AddResource("menu.borderRadius." + std::string(key), resObj, std::move(updateFunc));
}

void JSViewPopups::ParseMenuPreviewBorderRadiusMultiObject(
    const JSRef<JSObject>& object, NG::BorderRadiusProperty& props)
{
    if (JSViewAbstract::CheckLengthMetrics(object)) {
        ParseBorderRadiusPropsByLengthMetrics(BOTTOM_START_PROPERTY, object, props);
        ParseBorderRadiusPropsByLengthMetrics(BOTTOM_END_PROPERTY, object, props);
        ParseBorderRadiusPropsByLengthMetrics(TOP_START_PROPERTY, object, props);
        ParseBorderRadiusPropsByLengthMetrics(TOP_END_PROPERTY, object, props);
        return;
    }
    ParseBorderRadiusProps(TOP_LEFT_PROPERTY, object, props);
    ParseBorderRadiusProps(TOP_RIGHT_PROPERTY, object, props);
    ParseBorderRadiusProps(BOTTOM_LEFT_PROPERTY, object, props);
    ParseBorderRadiusProps(BOTTOM_RIGHT_PROPERTY, object, props);
}

void JSViewPopups::ParseMenuPreviewBorderRadius(const JSRef<JSVal>& args, NG::BorderRadiusProperty& radius)
{
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        return;
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (ParseMenuPreviewBorderRadiusObject(args, radius)) {
            return;
        }
        if (args->IsObject()) {
            JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
            ParseMenuPreviewBorderRadiusMultiObject(object, radius);
            radius.multiValued = true;
            return;
        }
    }
    CalcDimension borderRadius;
    if (JSViewAbstract::ParseJsDimensionVpNG(args, borderRadius, true)) {
        radius = NG::BorderRadiusProperty(borderRadius);
        radius.multiValued = false;
    } else if (args->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(args);
        JSViewAbstract::ParseCommonBorderRadiusProps(object, radius, false);
    }
    return;
}
}
