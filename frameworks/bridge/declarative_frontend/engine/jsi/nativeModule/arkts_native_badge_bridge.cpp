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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_badge_bridge.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/badge/badge_theme.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_BADGE_POSITION = 0;
constexpr Dimension UNDEFINED_DIMENSION(-1.0, DimensionUnit::VP);
const uint32_t DEFAULT_TEXT_COLOR = Color::WHITE.GetValue();
const uint32_t DEFAULT_BADGE_COLOR = Color::RED.GetValue();
bool InitBadgeParam(const RefPtr<BadgeTheme>& badgeTheme, ArkUIBadgeParam& param)
{
    CHECK_NULL_RETURN(badgeTheme, false);
    auto positionX = badgeTheme->GetBadgePositionX();
    auto positionY = badgeTheme->GetBadgePositionY();
    auto fontSize = badgeTheme->GetBadgeFontSize();
    auto circleSize = badgeTheme->GetBadgeCircleSize();
    auto borderWidth = badgeTheme->GetBadgeBorderWidth();
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
    param.borderWidth.value = borderWidth.Value();
    param.borderWidth.units = static_cast<int32_t>(borderWidth.Unit());
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
} // namespace

ArkUINativeModuleValue BadgeBridge::SetBadgeParamWithNumber(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> countArg = runtimeCallInfo->GetCallArgRef(12);    // 12: parameter index
    Local<JSValueRef> maxCountArg = runtimeCallInfo->GetCallArgRef(13); // 13: parameter index
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

    GetArkUINodeModifiers()->getBadgeModifier()->setBadgeParamWithNumber(nativeNode, &style, count, hasValue, maxCount);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue BadgeBridge::SetBadgeParamWithString(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(12); // 12: parameter index
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    ArkUIBadgeParam style;
    const char* value = nullptr;
    auto badgeTheme = ArkTSUtils::GetTheme<BadgeTheme>();
    CHECK_NULL_RETURN(badgeTheme, panda::JSValueRef::Undefined(vm));
    if (!ParseBadgeBaseParam(vm, runtimeCallInfo, badgeTheme, style)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!valueArg->IsNull() && valueArg->IsString(vm)) {
        value = valueArg->ToString(vm)->ToString(vm).c_str();
    }

    GetArkUINodeModifiers()->getBadgeModifier()->setBadgeParamWithString(nativeNode, &style, value);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
