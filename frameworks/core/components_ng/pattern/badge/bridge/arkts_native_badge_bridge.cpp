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

#include "core/components_ng/pattern/badge/bridge/arkts_native_badge_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/badge/badge_theme.h"
#include "core/components/common/properties/text_enums.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_BADGE_POSITION = 0;
constexpr Dimension UNDEFINED_DIMENSION(-1.0, DimensionUnit::VP);
const uint32_t DEFAULT_TEXT_COLOR = Color::WHITE.GetValue();
const uint32_t DEFAULT_BADGE_COLOR = Color::RED.GetValue();

struct BadgeResource {
    RefPtr<ResourceObject> positionX;
    RefPtr<ResourceObject> positionY;
    RefPtr<ResourceObject> fontColor;
    RefPtr<ResourceObject> fontWeight;
    RefPtr<ResourceObject> badgeColor;
    RefPtr<ResourceObject> badgeSize;
    RefPtr<ResourceObject> fontSize;
    RefPtr<ResourceObject> borderColor;
    RefPtr<ResourceObject> borderWidth;
    RefPtr<ResourceObject> outerBorderColor;
    RefPtr<ResourceObject> outerBorderWidth;
    RefPtr<ResourceObject> badgeValue;
};
bool InitBadgeParam(const RefPtr<BadgeTheme>& badgeTheme, ArkUIBadgeParam& param)
{
    CHECK_NULL_RETURN(badgeTheme, false);
    auto positionX = badgeTheme->GetBadgePositionX();
    auto positionY = badgeTheme->GetBadgePositionY();
    auto fontSize = badgeTheme->GetBadgeFontSize();
    auto circleSize = badgeTheme->GetBadgeCircleSize();
    auto borderWidth = badgeTheme->GetBadgeBorderWidth();
    auto outerBorderWidth = badgeTheme->GetBadgeOuterBorderWidth();
    auto themeColors = Framework::JSThemeUtils::GetThemeColors();
    param.position = DEFAULT_BADGE_POSITION;
    param.isPositionXy = false;
    param.positionX.value = positionX.Value();
    param.positionX.units = static_cast<int32_t>(positionX.Unit());
    param.positionY.value = positionY.Value();
    param.positionY.units = static_cast<int32_t>(positionY.Unit());
    if (themeColors.has_value()) {
        param.textColor = themeColors->FontOnPrimary().GetValue();
        param.badgeColor = themeColors->Warning().GetValue();
    } else {
        param.textColor = DEFAULT_TEXT_COLOR;
        param.badgeColor = DEFAULT_BADGE_COLOR;
    }
    param.fontSize.value = fontSize.Value();
    param.fontSize.units = static_cast<int32_t>(fontSize.Unit());
    param.badgeSize.value = circleSize.Value();
    param.badgeSize.units = static_cast<int32_t>(fontSize.Unit());
    param.borderColor = themeColors ? themeColors->Warning().GetValue() : badgeTheme->GetBadgeBorderColor().GetValue();
    param.outerBorderColor = badgeTheme->GetBadgeOuterBorderColor().GetValue();
    param.borderWidth.value = borderWidth.Value();
    param.borderWidth.units = static_cast<int32_t>(borderWidth.Unit());
    param.outerBorderWidth.value = outerBorderWidth.Value();
    param.outerBorderWidth.units = static_cast<int32_t>(outerBorderWidth.Unit());
    param.enableAutoAvoidance = false;
    param.fontWeight = static_cast<int32_t>(FontWeight::NORMAL);
    param.isDefaultFontSize = true;
    param.isDefaultBadgeSize = true;
    return true;
}

void ParsePosition(const EcmaVM* vm, const ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIBadgeParam& param)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(runtimeCallInfo);
    Local<JSValueRef> position = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> positionX = runtimeCallInfo->GetCallArgRef(2);    // 2: parameter index
    Local<JSValueRef> positionY = runtimeCallInfo->GetCallArgRef(3);    // 3: parameter index
    Local<JSValueRef> positionObj = runtimeCallInfo->GetCallArgRef(11); // 11: parameter index
    if (!position->IsNull() && position->IsNumber()) {
        param.isPositionXy = false;
        param.position = position->Int32Value(vm);
    } else if (!positionX->IsUndefined() || !positionY->IsUndefined() ||
               (positionObj->IsBoolean() && positionObj->ToBoolean(vm)->Value())) {
        param.isPositionXy = true;
        CalcDimension dimenX;
        CalcDimension dimenY;
        bool xResult = ArkTSUtils::ParseJsDimensionVp(vm, positionX, dimenX);
        bool yResult = ArkTSUtils::ParseJsDimensionVp(vm, positionY, dimenY);
        if (xResult || yResult) {
            param.positionX.value = dimenX.Value();
            param.positionX.units = static_cast<int32_t>(dimenX.Unit());
            param.positionY.value = dimenY.Value();
            param.positionY.units = static_cast<int32_t>(dimenY.Unit());
        }
    }
}

void ParseFontSize(const EcmaVM* vm, const ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIBadgeParam& param)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(runtimeCallInfo);
    Local<JSValueRef> fontSize = runtimeCallInfo->GetCallArgRef(9); // 9: parameter index
    CalcDimension fontSizeVal;
    if (ArkTSUtils::ParseJsDimensionNG(vm, fontSize, fontSizeVal, DimensionUnit::FP)) {
        if (fontSizeVal.IsNonNegative() && fontSizeVal.Unit() != DimensionUnit::PERCENT) {
            param.fontSize.value = fontSizeVal.Value();
            param.fontSize.units = static_cast<int32_t>(fontSizeVal.Unit());
            param.isDefaultFontSize = false;
        }
    } else if (fontSize->IsUndefined()) {
        param.fontSize.value = UNDEFINED_DIMENSION.Value();
        param.fontSize.units = static_cast<int32_t>(UNDEFINED_DIMENSION.Unit());
    }
}

void ParseBadgeSize(const EcmaVM* vm, const ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUIBadgeParam& param)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(runtimeCallInfo);
    Local<JSValueRef> badgeSize = runtimeCallInfo->GetCallArgRef(5); // 5: parameter index
    CalcDimension badgeSizeVal;
    if (ArkTSUtils::ParseJsDimensionNG(vm, badgeSize, badgeSizeVal, DimensionUnit::FP)) {
        if (badgeSizeVal.IsNonNegative() && badgeSizeVal.Unit() != DimensionUnit::PERCENT) {
            param.badgeSize.value = badgeSizeVal.Value();
            param.badgeSize.units = static_cast<int32_t>(badgeSizeVal.Unit());
            param.isDefaultBadgeSize = false;
        }
    }
}

void ParseBadgeOuterBorder(const EcmaVM* vm, const Local<JSValueRef>& outerBorderColor,
    const Local<JSValueRef>& outerBorderWidth, const Local<JSValueRef>& enableAutoAvoidance, ArkUIBadgeParam& param)
{
    Color outerBorderColorVal;
    if (!(outerBorderColor->IsNull() || outerBorderColor->IsUndefined()) &&
        ArkTSUtils::ParseJsColorAlpha(vm, outerBorderColor, outerBorderColorVal)) {
        param.outerBorderColor = outerBorderColorVal.GetValue();
    }
    CalcDimension outerBorderWidthVal;
    if (!(outerBorderWidth->IsNull() || outerBorderWidth->IsUndefined()) &&
        ArkTSUtils::ParseJsLengthMetrics(vm, outerBorderWidth, outerBorderWidthVal)) {
        param.outerBorderWidth.value = outerBorderWidthVal.Value();
        param.outerBorderWidth.units = static_cast<int32_t>(outerBorderWidthVal.Unit());
    }
    if (enableAutoAvoidance->IsBoolean()) {
        param.enableAutoAvoidance = enableAutoAvoidance->ToBoolean(vm)->Value();
    }
}

bool ParseBadgeBaseParam(const EcmaVM* vm, const ArkUIRuntimeCallInfo* runtimeCallInfo,
    const RefPtr<BadgeTheme>& badgeTheme, ArkUIBadgeParam& param)
{
    CHECK_NULL_RETURN(vm, false);
    CHECK_NULL_RETURN(runtimeCallInfo, false);
    CHECK_NULL_RETURN(badgeTheme, false);
    Local<JSValueRef> badgeColor = runtimeCallInfo->GetCallArgRef(4);  // 4: parameter index
    Local<JSValueRef> borderColor = runtimeCallInfo->GetCallArgRef(6); // 6: parameter index
    Local<JSValueRef> borderWidth = runtimeCallInfo->GetCallArgRef(7); // 7: parameter index
    Local<JSValueRef> textColor = runtimeCallInfo->GetCallArgRef(8);   // 8: parameter index
    Local<JSValueRef> fontWeight = runtimeCallInfo->GetCallArgRef(10); // 10: parameter index
    if (!InitBadgeParam(badgeTheme, param)) {
        return false;
    }
    ParsePosition(vm, runtimeCallInfo, param);
    ParseFontSize(vm, runtimeCallInfo, param);
    ParseBadgeSize(vm, runtimeCallInfo, param);

    Color badgeColorVal, textColorVal, borderColorVal;
    if (ArkTSUtils::ParseJsColor(vm, badgeColor, badgeColorVal)) {
        param.badgeColor = badgeColorVal.GetValue();
    }
    if (ArkTSUtils::ParseJsColorAlpha(vm, textColor, textColorVal)) {
        param.textColor = textColorVal.GetValue();
    }
    if (ArkTSUtils::ParseJsColorAlpha(vm, borderColor, borderColorVal)) {
        param.borderColor = borderColorVal.GetValue();
    }
    std::string fontWeightVal;
    if (fontWeight->IsNumber()) {
        fontWeightVal = std::to_string(fontWeight->Int32Value(vm));
    } else {
        ArkTSUtils::ParseJsString(vm, fontWeight, fontWeightVal);
    }
    CalcDimension borderWidthVal;
    if (ArkTSUtils::ParseJsDimensionVp(vm, borderWidth, borderWidthVal)) {
        if (borderWidthVal.IsNonNegative() && borderWidthVal.Unit() != DimensionUnit::PERCENT) {
            param.borderWidth.value = borderWidthVal.Value();
            param.borderWidth.units = static_cast<int32_t>(borderWidthVal.Unit());
        }
    }
    param.fontWeight = static_cast<ArkUI_Int32>(Framework::ConvertStrToFontWeight(fontWeightVal));
    return true;
}

void TransformCalcDimensionValue(ArkUIDimensionType& position, const CalcDimension& sourcePosition)
{
    position.value = sourcePosition.Value();
    position.units = static_cast<ArkUI_Int32>(sourcePosition.Unit());
}

void ParsePositionJS(const EcmaVM* vm, Local<panda::ObjectRef> paramObj, ArkUIBadgeJSParam& JSParam,
    const RefPtr<BadgeTheme>& badgeTheme, BadgeResource& resObj)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(badgeTheme);
    Local<JSValueRef> position = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "position"));
    if (position->IsNumber()) {
        JSParam.isPositionXy = false;
        JSParam.position = position->Int32Value(vm);
        JSParam.hasPosition = true;
    } else if (position->IsObject(vm)) {
        JSParam.isPositionXy = true;
        JSParam.hasPosition = true;
        auto positionObj = position->ToObject(vm);
        Local<JSValueRef> xVal = positionObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "x"));
        Local<JSValueRef> yVal = positionObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "y"));
        CalcDimension dimenX;
        CalcDimension dimenY;
        if (SystemProperties::ConfigChangePerform()) {
            bool xState = ArkTSUtils::ParseJsDimensionVp(vm, xVal, dimenX, resObj.positionX);
            bool yState = ArkTSUtils::ParseJsDimensionVp(vm, yVal, dimenY, resObj.positionY);
            JSParam.resourceBadgePositionXObject = AceType::RawPtr(resObj.positionX);
            JSParam.resourceBadgePositionYObject = AceType::RawPtr(resObj.positionY);
            JSParam.badgePositionXByUser = true;
            JSParam.badgePositionYByUser = true;
            bool hasX = resObj.positionX || xState;
            bool hasY = resObj.positionY || yState;
            if (!(hasX || hasY)) {
                TransformCalcDimensionValue(JSParam.positionX, badgeTheme->GetBadgePositionX());
                TransformCalcDimensionValue(JSParam.positionY, badgeTheme->GetBadgePositionY());
                JSParam.resourceBadgePositionXObject = nullptr;
                JSParam.resourceBadgePositionYObject = nullptr;
                JSParam.badgePositionXByUser = false;
                JSParam.badgePositionYByUser = false;
            } else {
                TransformCalcDimensionValue(JSParam.positionX, dimenX);
                TransformCalcDimensionValue(JSParam.positionY, dimenY);
            }
        } else {
            bool xResult = ArkTSUtils::ParseJsDimensionVp(vm, xVal, dimenX);
            bool yResult = ArkTSUtils::ParseJsDimensionVp(vm, yVal, dimenY);
            if (!(xResult || yResult)) {
                TransformCalcDimensionValue(JSParam.positionX, badgeTheme->GetBadgePositionX());
                TransformCalcDimensionValue(JSParam.positionY, badgeTheme->GetBadgePositionY());
            } else {
                TransformCalcDimensionValue(JSParam.positionX, dimenX);
                TransformCalcDimensionValue(JSParam.positionY, dimenY);
            }
        }
    }
}

void ParseBadgeFontJS(const EcmaVM* vm, Local<panda::ObjectRef> paramObj, ArkUIBadgeJSParam& JSParam,
    const RefPtr<BadgeTheme>& badgeTheme, BadgeResource& resObj)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(badgeTheme);
    Local<JSValueRef> fontColor = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
    Local<JSValueRef> fontWeight = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontWeight"));
    auto themeColors = Framework::JSThemeUtils::GetThemeColors();
    Color fontColorVal;
    if (SystemProperties::ConfigChangePerform()) {
        JSParam.badgeTextColorByUser = true;
        NodeInfo badgeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED, true };
        bool state = ArkTSUtils::ParseJsColorAlpha(vm, fontColor, fontColorVal, resObj.fontColor, badgeInfo);
        JSParam.resourceColorObject = AceType::RawPtr(resObj.fontColor);
        if (state) {
            JSParam.textColor = fontColorVal.GetValue();
            JSParam.hasTextColor = true;
        } else if (themeColors.has_value()) {
            JSParam.textColor = themeColors->FontOnPrimary().GetValue();
            JSParam.hasTextColor = true;
            JSParam.badgeTextColorByUser = false;
        } else {
            JSParam.badgeTextColorByUser = false;
        }
    } else {
        if (ArkTSUtils::ParseJsColorAlpha(vm, fontColor, fontColorVal)) {
            JSParam.textColor = fontColorVal.GetValue();
            JSParam.hasTextColor = true;
        } else if (themeColors.has_value()) {
            JSParam.textColor = themeColors->FontOnPrimary().GetValue();
            JSParam.hasTextColor = true;
        }
    }

    std::string fontWeightVal;
    if (fontWeight->IsNumber()) {
        fontWeightVal = std::to_string(fontWeight->Int32Value(vm));
        JSParam.fontWeight = static_cast<ArkUI_Int32>(Framework::ConvertStrToFontWeight(fontWeightVal));
    } else if (SystemProperties::ConfigChangePerform()) {
        ArkTSUtils::ParseJsString(vm, fontWeight, fontWeightVal, resObj.fontWeight);
        JSParam.resourceFontWeightObject = AceType::RawPtr(resObj.fontWeight);
        JSParam.fontWeight = static_cast<ArkUI_Int32>(Framework::ConvertStrToFontWeight(fontWeightVal));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, fontWeight, fontWeightVal)) {
            JSParam.fontWeight = static_cast<ArkUI_Int32>(FontWeight::NORMAL);
        }
        JSParam.fontWeight = static_cast<ArkUI_Int32>(Framework::ConvertStrToFontWeight(fontWeightVal));
    }
    JSParam.hasFontWeight = true;
}

void ParseBadgeJS(const EcmaVM* vm, Local<panda::ObjectRef> paramObj, ArkUIBadgeJSParam& JSParam,
    const RefPtr<BadgeTheme>& badgeTheme, BadgeResource& resObj)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(badgeTheme);
    Local<JSValueRef> badgeColor = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "badgeColor"));
    Local<JSValueRef> badgeSize = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "badgeSize"));

    auto themeColors = Framework::JSThemeUtils::GetThemeColors();
    Color badgeColorVal;
    if (SystemProperties::ConfigChangePerform()) {
        NodeInfo badgeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED, true };
        bool state = ArkTSUtils::ParseJsColorAlpha(vm, badgeColor, badgeColorVal, resObj.badgeColor, badgeInfo);
        JSParam.resourceBadgeColorObject = AceType::RawPtr(resObj.badgeColor);
        if (state) {
            JSParam.badgeColor = badgeColorVal.GetValue();
            JSParam.badgeColorByUser = true;
            JSParam.hasBadgeColor = true;
        } else if (themeColors.has_value()) {
            JSParam.badgeColor = themeColors->Warning().GetValue();
            JSParam.hasBadgeColor = true;
        }
    } else {
        if (ArkTSUtils::ParseJsColorAlpha(vm, badgeColor, badgeColorVal)) {
            JSParam.badgeColor = badgeColorVal.GetValue();
            JSParam.hasBadgeColor = true;
        } else if (themeColors.has_value()) {
            JSParam.badgeColor = themeColors->Warning().GetValue();
            JSParam.hasBadgeColor = true;
        }
    }

    CalcDimension badgeSizeVal;
    if (SystemProperties::ConfigChangePerform()) {
        bool state = ArkTSUtils::ParseJsDimensionNG(vm, badgeSize, badgeSizeVal, DimensionUnit::FP, resObj.badgeSize);
        JSParam.resourceBadgeSizeObject = AceType::RawPtr(resObj.badgeSize);
        if (state && badgeSizeVal.IsNonNegative() && badgeSizeVal.Unit() != DimensionUnit::PERCENT) {
            TransformCalcDimensionValue(JSParam.badgeSize, badgeSizeVal);
            JSParam.isDefaultBadgeSize = false;
            JSParam.badgeCircleSizeByUser = true;
        } else {
            TransformCalcDimensionValue(JSParam.badgeSize, badgeTheme->GetBadgeCircleSize());
        }
    } else {
        if (ArkTSUtils::ParseJsDimensionNG(vm, badgeSize, badgeSizeVal, DimensionUnit::FP) &&
            badgeSizeVal.IsNonNegative() && badgeSizeVal.Unit() != DimensionUnit::PERCENT) {
            TransformCalcDimensionValue(JSParam.badgeSize, badgeSizeVal);
            JSParam.isDefaultBadgeSize = false;
        } else {
            TransformCalcDimensionValue(JSParam.badgeSize, badgeTheme->GetBadgeCircleSize());
        }
    }
    JSParam.hasBadgeSize = true;
}

void ParseBadgeBorderJS(const EcmaVM* vm, Local<panda::ObjectRef> paramObj, ArkUIBadgeJSParam& JSParam,
    const RefPtr<BadgeTheme>& badgeTheme, BadgeResource& resObj)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(badgeTheme);
    Local<JSValueRef> borderColor = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "borderColor"));
    Local<JSValueRef> borderWidth = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "borderWidth"));

    auto themeColors = Framework::JSThemeUtils::GetThemeColors();
    CalcDimension borderWidthVal;

    if (SystemProperties::ConfigChangePerform()) {
        JSParam.badgeBorderWidthByUser = true;
        bool state = ArkTSUtils::ParseJsDimensionVp(vm, borderWidth, borderWidthVal, resObj.borderWidth, false);
        JSParam.resourceBorderWidthObject = AceType::RawPtr(resObj.borderWidth);
        if (state && borderWidthVal.IsNonNegative() && borderWidthVal.Unit() != DimensionUnit::PERCENT) {
            TransformCalcDimensionValue(JSParam.borderWidth, borderWidthVal);
        } else {
            TransformCalcDimensionValue(JSParam.borderWidth, badgeTheme->GetBadgeBorderWidth());
            JSParam.badgeBorderWidthByUser = false;
        }
    } else {
        if (ArkTSUtils::ParseJsDimension(vm, borderWidth, borderWidthVal, DimensionUnit::VP, true, false) &&
            borderWidthVal.IsNonNegative() && borderWidthVal.Unit() != DimensionUnit::PERCENT) {
            TransformCalcDimensionValue(JSParam.borderWidth, borderWidthVal);
        } else {
            TransformCalcDimensionValue(JSParam.borderWidth, badgeTheme->GetBadgeBorderWidth());
        }
    }
    JSParam.hasBorderWidth = true;
    Color borderColorVal;
    if (SystemProperties::ConfigChangePerform()) {
        JSParam.badgeBorderColorByUser = false;
        NodeInfo badgeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED, true };
        bool state = ArkTSUtils::ParseJsColorAlpha(vm, borderColor, borderColorVal, resObj.borderColor, badgeInfo);
        JSParam.resourceBorderColorObject = AceType::RawPtr(resObj.borderColor);
        if (state) {
            JSParam.borderColor = borderColorVal.GetValue();
            JSParam.badgeBorderColorByUser = true;
        } else {
            JSParam.borderColor = themeColors.has_value() ? themeColors->Warning().GetValue()
                                                          : badgeTheme->GetBadgeBorderColor().GetValue();
        }
    } else {
        if (ArkTSUtils::ParseJsColorAlpha(vm, borderColor, borderColorVal)) {
            JSParam.borderColor = borderColorVal.GetValue();
        } else {
            JSParam.borderColor = themeColors.has_value() ? themeColors->Warning().GetValue()
                                                          : badgeTheme->GetBadgeBorderColor().GetValue();
        }
    }
    JSParam.hasBorderColor = true;
}

void ParseBadgeOuterBorderJS(const EcmaVM* vm, Local<panda::ObjectRef> paramObj, ArkUIBadgeJSParam& JSParam,
    const RefPtr<BadgeTheme>& badgeTheme, BadgeResource& resObj)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(badgeTheme);
    Local<JSValueRef> outerBorderColor = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "outerBorderColor"));
    Local<JSValueRef> outerBorderWidth = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "outerBorderWidth"));
    Local<JSValueRef> enableAutoAvoidance = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableAutoAvoidance"));

    CalcDimension outerBorderWidthVal;
    if (SystemProperties::ConfigChangePerform()) {
        JSParam.badgeOuterBorderWidthByUser = true;
        JSParam.badgeOuterBorderColorByUser = true;
    }

    if (ArkTSUtils::ParseJsLengthMetrics(vm, outerBorderWidth, outerBorderWidthVal, resObj.outerBorderWidth)) {
        JSParam.outerBorderWidth.value = outerBorderWidthVal.Value();
        JSParam.outerBorderWidth.units = static_cast<int32_t>(outerBorderWidthVal.Unit());
        JSParam.resourceOuterBorderWidthObject = AceType::RawPtr(resObj.outerBorderWidth);
    } else {
        JSParam.outerBorderWidth.value = badgeTheme->GetBadgeOuterBorderWidth().Value();
        JSParam.outerBorderWidth.units = static_cast<int32_t>(badgeTheme->GetBadgeOuterBorderWidth().Unit());
        JSParam.badgeOuterBorderWidthByUser = false;
    }
    JSParam.hasOuterBorderWidth = true;

    Color outerBorderColorVal;
    NodeInfo badgeInfo = { "", ColorMode::COLOR_MODE_UNDEFINED, true };
    if (ArkTSUtils::ParseJsColorAlpha(vm, outerBorderColor, outerBorderColorVal, resObj.outerBorderColor, badgeInfo)) {
        JSParam.outerBorderColor = outerBorderColorVal.GetValue();
        JSParam.resourceOuterBorderColorObject = AceType::RawPtr(resObj.outerBorderColor);
    } else {
        JSParam.outerBorderColor = badgeTheme->GetBadgeOuterBorderColor().GetValue();
        JSParam.badgeOuterBorderColorByUser = false;
    }
    JSParam.hasOuterBorderColor = true;

    if (enableAutoAvoidance->IsBoolean()) {
        JSParam.enableAutoAvoidance = enableAutoAvoidance->ToBoolean(vm)->Value();
    } else {
        JSParam.enableAutoAvoidance = false;
    }
    JSParam.hasEnableAutoAvoidance = true;
}

void ParseBadgeFontSizeJS(const EcmaVM* vm, Local<panda::ObjectRef> paramObj, ArkUIBadgeJSParam& JSParam,
    const RefPtr<BadgeTheme>& badgeTheme, BadgeResource& resObj)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(badgeTheme);
    Local<JSValueRef> fontSize = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontSize"));
    bool isDefaultFontSize = true;

    CalcDimension fontSizeVal;
    if (SystemProperties::ConfigChangePerform()) {
        JSParam.badgeFontSizeByUser = true;
        bool state = ArkTSUtils::ParseJsDimensionNG(vm, fontSize, fontSizeVal, DimensionUnit::FP, resObj.fontSize);
        JSParam.resourceFontSizeObject = AceType::RawPtr(resObj.fontSize);
        if (state && fontSizeVal.IsNonNegative() && fontSizeVal.Unit() != DimensionUnit::PERCENT) {
            JSParam.fontSize.value = fontSizeVal.Value();
            JSParam.fontSize.units = static_cast<int32_t>(fontSizeVal.Unit());
            isDefaultFontSize = false;
            JSParam.hasFontSize = true;
        } else {
            JSParam.badgeFontSizeByUser = false;
            if (!fontSize->IsUndefined()) {
                JSParam.fontSize.value = badgeTheme->GetBadgeFontSize().Value();
                JSParam.fontSize.units = static_cast<int32_t>(badgeTheme->GetBadgeFontSize().Unit());
            } else {
                JSParam.fontSize.value = UNDEFINED_DIMENSION.Value();
                JSParam.fontSize.units = static_cast<int32_t>(UNDEFINED_DIMENSION.Unit());
            }
            JSParam.hasFontSize = true;
        }
    } else {
        if (ArkTSUtils::ParseJsDimensionNG(vm, fontSize, fontSizeVal, DimensionUnit::FP) &&
            fontSizeVal.IsNonNegative() && fontSizeVal.Unit() != DimensionUnit::PERCENT) {
            JSParam.fontSize.value = fontSizeVal.Value();
            JSParam.fontSize.units = static_cast<int32_t>(fontSizeVal.Unit());
            isDefaultFontSize = false;
            JSParam.hasFontSize = true;
        } else {
            JSParam.badgeFontSizeByUser = false;
            if (!fontSize->IsUndefined()) {
                JSParam.fontSize.value = badgeTheme->GetBadgeFontSize().Value();
                JSParam.fontSize.units = static_cast<int32_t>(badgeTheme->GetBadgeFontSize().Unit());
            } else {
                JSParam.fontSize.value = UNDEFINED_DIMENSION.Value();
                JSParam.fontSize.units = static_cast<int32_t>(UNDEFINED_DIMENSION.Unit());
            }
            JSParam.hasFontSize = true;
        }
    }
    JSParam.isDefaultFontSize = isDefaultFontSize;
}
void ParseValueJS(const EcmaVM* vm, Local<panda::ObjectRef> paramObj, ArkUIBadgeJSParam& JSParam,
    std::string& badgeValue, BadgeResource& resObj)
{
    CHECK_NULL_VOID(vm);
    auto valueArg = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
    if (!valueArg->IsNull() && valueArg->IsString(vm)) {
        if (ArkTSUtils::ParseJsString(vm, valueArg, badgeValue)) {
            JSParam.badgeValue = badgeValue.c_str();
            JSParam.hasBadgeValue = true;
        }
    } else if (!valueArg->IsNull() && valueArg->IsObject(vm)) {
        if (SystemProperties::ConfigChangePerform()) {
            ArkTSUtils::ParseJsString(vm, valueArg, badgeValue, resObj.badgeValue);
            JSParam.resourceBadgeValueObject = AceType::RawPtr(resObj.badgeValue);
            JSParam.badgeValue = badgeValue.c_str();
            JSParam.hasBadgeValue = true;
        } else {
            ArkTSUtils::ParseJsString(vm, valueArg, badgeValue);
            JSParam.badgeValue = badgeValue.c_str();
            JSParam.hasBadgeValue = true;
        }
    }
}
} // namespace

void BadgeBridge::RegisterBadgeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setBadgeParamWithNumber", "setBadgeParamWithString" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BadgeBridge::CreateBadge),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BadgeBridge::SetBadgeParamWithNumber),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BadgeBridge::SetBadgeParamWithString),
    };

    auto badge =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "badge"), badge);
}

ArkUINativeModuleValue BadgeBridge::CreateBadge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(0);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto badgeModifier = nodeModifiers->getBadgeModifier();
    CHECK_NULL_RETURN(badgeModifier, panda::JSValueRef::Undefined(vm));
    ArkUIBadgeJSParam badgeJSParam;
    BadgeResource resObj;
    if (paramArg->IsNull() || paramArg->IsUndefined() || !paramArg->IsObject(vm)) {
        badgeModifier->createBadge(&badgeJSParam);
        return panda::JSValueRef::Undefined(vm);
    }
    auto paramObject = paramArg->ToObject(vm);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    CHECK_NULL_RETURN(badgeTheme, panda::NativePointerRef::New(vm, nullptr));
    std::string badgeValue;
    ParseValueJS(vm, paramObject, badgeJSParam, badgeValue, resObj);
    ParsePositionJS(vm, paramObject, badgeJSParam, badgeTheme, resObj);

    auto styleArg = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
    if (!styleArg->IsNull() && styleArg->IsObject(vm)) {
        auto styleObject = styleArg->ToObject(vm);
        ParseBadgeFontJS(vm, styleObject, badgeJSParam, badgeTheme, resObj);
        ParseBadgeJS(vm, styleObject, badgeJSParam, badgeTheme, resObj);
        ParseBadgeFontSizeJS(vm, styleObject, badgeJSParam, badgeTheme, resObj);
        ParseBadgeBorderJS(vm, styleObject, badgeJSParam, badgeTheme, resObj);
        ParseBadgeOuterBorderJS(vm, styleObject, badgeJSParam, badgeTheme, resObj);
    }

    auto countArg = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "count"));
    auto maxCountArg = paramObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "maxCount"));

    if (!countArg->IsNull() && countArg->IsNumber()) {
        badgeJSParam.badgeCount = countArg->Int32Value(vm);
        badgeJSParam.hasBadgeCount = true;
    }
    if (!maxCountArg->IsNull() && maxCountArg->IsNumber()) {
        badgeJSParam.badgeMaxCount = maxCountArg->Int32Value(vm);
        badgeJSParam.hasBadgeMaxCount = true;
    } else {
        badgeJSParam.badgeMaxCount = badgeTheme->GetMaxCount();
        badgeJSParam.hasBadgeMaxCount = true;
    }

    badgeModifier->createBadge(&badgeJSParam);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BadgeBridge::SetBadgeParamWithNumber(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> countArg = runtimeCallInfo->GetCallArgRef(12);            // 12: parameter index
    Local<JSValueRef> maxCountArg = runtimeCallInfo->GetCallArgRef(13);         // 13: parameter index
    Local<JSValueRef> outerBorderColor = runtimeCallInfo->GetCallArgRef(14);    // 14: parameter index
    Local<JSValueRef> outerBorderWidth = runtimeCallInfo->GetCallArgRef(15);    // 15: parameter index
    Local<JSValueRef> enableAutoAvoidance = runtimeCallInfo->GetCallArgRef(16); // 16: parameter index
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    ArkUIBadgeParam style;
    int32_t count = 0;
    int32_t maxCount = 0;
    bool hasValue = false;
    auto badgeTheme = ArkTSUtils::GetTheme<BadgeTheme>();
    CHECK_NULL_RETURN(badgeTheme, panda::JSValueRef::Undefined(vm));
    if (!ParseBadgeBaseParam(vm, runtimeCallInfo, badgeTheme, style)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!countArg->IsNull() && countArg->IsNumber()) {
        count = countArg->Int32Value(vm);
        hasValue = true;
    }
    if (!maxCountArg->IsNull() && maxCountArg->IsNumber()) {
        maxCount = maxCountArg->Int32Value(vm);
    } else {
        maxCount = badgeTheme->GetMaxCount();
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    ParseBadgeOuterBorder(vm, outerBorderColor, outerBorderWidth, enableAutoAvoidance, style);
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getBadgeModifier()->setBadgeParamWithNumber(nativeNode, &style, count, hasValue, maxCount);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BadgeBridge::SetBadgeParamWithString(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(12);            // 12: parameter index
    Local<JSValueRef> outerBorderColor = runtimeCallInfo->GetCallArgRef(13);    // 13: parameter index
    Local<JSValueRef> outerBorderWidth = runtimeCallInfo->GetCallArgRef(14);    // 14: parameter index
    Local<JSValueRef> enableAutoAvoidance = runtimeCallInfo->GetCallArgRef(15); // 15: parameter index
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    ArkUIBadgeParam style;
    const char* value = nullptr;
    auto badgeTheme = ArkTSUtils::GetTheme<BadgeTheme>();
    CHECK_NULL_RETURN(badgeTheme, panda::JSValueRef::Undefined(vm));
    if (!ParseBadgeBaseParam(vm, runtimeCallInfo, badgeTheme, style)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string content;
    if (!valueArg->IsNull() && valueArg->IsString(vm)) {
        if (ArkTSUtils::ParseJsString(vm, valueArg, content)) {
            value = content.c_str();
        }
    } else if (!valueArg->IsNull() && valueArg->IsObject(vm)) {
        ArkTSUtils::ParseJsString(vm, valueArg, content);
        value = content.c_str();
    }
    ParseBadgeOuterBorder(vm, outerBorderColor, outerBorderWidth, enableAutoAvoidance, style);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getBadgeModifier()->setBadgeParamWithString(nativeNode, &style, value);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
