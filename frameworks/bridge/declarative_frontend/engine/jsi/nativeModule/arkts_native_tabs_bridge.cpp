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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_tabs_bridge.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_tabs.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "core/components/common/properties/color.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::NG {
constexpr int SIZE_OF_FIVE = 5;
constexpr int SIZE_OF_THREE = 3;
constexpr int SIZE_OF_VALUES = 2;
constexpr int TABS_ARG_INDEX_0 = 0;
constexpr int TABS_ARG_INDEX_1 = 1;
constexpr int TABS_ARG_INDEX_2 = 2;
constexpr int TABS_ARG_INDEX_3 = 3;
constexpr int TABS_ARG_INDEX_4 = 4;
constexpr int TABS_ARG_INDEX_5 = 5;
constexpr int TABS_ARG_INDEX_6 = 6;
constexpr int TABS_ARG_INDEX_7 = 7;
constexpr int TABS_ARG_INDEX_8 = 8;
constexpr int TABS_ARG_INDEX_9 = 9;
constexpr int32_t SM_COLUMN_NUM = 4;
constexpr int32_t MD_COLUMN_NUM = 8;
constexpr int32_t LG_COLUMN_NUM = 12;
constexpr int32_t DEFAULT_COLUMN = -1;
constexpr int REMAINDER = 2;
constexpr int TABBARMODE_SCROLLABLE = 1;
ArkUINativeModuleValue TabsBridge::SetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> barModeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> marginArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> nonScrollableLayoutStyleArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);

    if (barModeArg->IsNull() || barModeArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    TabBarMode barMode = TabBarMode::FIXED;
    barMode = Framework::ConvertStrToTabBarMode(barModeArg->ToString(vm)->ToString(vm));
    int32_t tabBarMode = static_cast<int32_t>(barMode);
    GetArkUINodeModifiers()->getTabsModifier()->setTabBarMode(nativeNode, tabBarMode);

    if (tabBarMode == TABBARMODE_SCROLLABLE) {
        if (marginArg->IsNull() || marginArg->IsUndefined() || nonScrollableLayoutStyleArg->IsNull() ||
            nonScrollableLayoutStyleArg->IsUndefined()) {
            GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        int barModeStyle = nonScrollableLayoutStyleArg->Int32Value(vm);
        CalcDimension margin(0.0, DimensionUnit::VP);
        if (!ArkTSUtils::ParseJsDimensionVp(vm, marginArg, margin)) {
            margin.Reset();
        }

        GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
            nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (thirdArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int barModeStyle = thirdArg->Int32Value(vm);

    CalcDimension margin(0.0, DimensionUnit::VP);
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, margin)) {
        margin.Reset();
    }

    GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
        nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> smArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> mdArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> lgArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> gutterArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    Local<JSValueRef> marginArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_5);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    int32_t sm = DEFAULT_COLUMN;
    int32_t md = DEFAULT_COLUMN;
    int32_t lg = DEFAULT_COLUMN;
    if (smArg->IsNumber() && smArg->Int32Value(vm) >= 0 && smArg->Int32Value(vm) <= SM_COLUMN_NUM &&
        smArg->Int32Value(vm) % REMAINDER == 0) {
        sm = smArg->Int32Value(vm);
    }
    if (mdArg->IsNumber() && mdArg->Int32Value(vm) >= 0 && mdArg->Int32Value(vm) <= MD_COLUMN_NUM &&
        mdArg->Int32Value(vm) % REMAINDER == 0) {
        md = mdArg->Int32Value(vm);
    }
    if (lgArg->IsNumber() && lgArg->Int32Value(vm) >= 0 && lgArg->Int32Value(vm) <= LG_COLUMN_NUM &&
        lgArg->Int32Value(vm) % REMAINDER == 0) {
        lg = lgArg->Int32Value(vm);
    }

    CalcDimension columnGutter;
    CalcDimension columnMargin;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, gutterArg, columnGutter) || !NonNegative(columnGutter.Value()) ||
        columnGutter.Unit() == DimensionUnit::PERCENT) {
        columnGutter.Reset();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, marginArg, columnMargin) || !NonNegative(columnMargin.Value()) ||
        columnMargin.Unit() == DimensionUnit::PERCENT) {
        columnMargin.Reset();
    }

    int unitsAndColumn[SIZE_OF_FIVE];
    ArkUI_Float32 values[SIZE_OF_VALUES];

    values[TABS_ARG_INDEX_0] = static_cast<ArkUI_Float32>(columnGutter.Value());
    values[TABS_ARG_INDEX_1] = static_cast<ArkUI_Float32>(columnMargin.Value());
    unitsAndColumn[TABS_ARG_INDEX_0] = static_cast<int>(columnGutter.Unit());
    unitsAndColumn[TABS_ARG_INDEX_1] = static_cast<int>(columnMargin.Unit());
    unitsAndColumn[TABS_ARG_INDEX_2] = sm;
    unitsAndColumn[TABS_ARG_INDEX_3] = md;
    unitsAndColumn[TABS_ARG_INDEX_4] = lg;

    GetArkUINodeModifiers()->getTabsModifier()->setBarGridAlign(
        nativeNode, values, SIZE_OF_VALUES, unitsAndColumn, SIZE_OF_FIVE);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarGridAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> dividerStartMarginArgs = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> dividerEndMarginArgs = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    auto isDividerStrokeWidthArgsInvalid = dividerStrokeWidthArgs->IsNull() || dividerStrokeWidthArgs->IsUndefined();
    auto isDividerStartMarginArgsInvalid = dividerStartMarginArgs->IsNull() || dividerStartMarginArgs->IsUndefined();
    auto isDividerEndMarginArgsInvalid = dividerEndMarginArgs->IsNull() || dividerEndMarginArgs->IsUndefined();
    auto isColorArgInvalid = colorArg->IsNull() || colorArg->IsUndefined();
    if (isDividerStrokeWidthArgsInvalid && isDividerStartMarginArgsInvalid && isDividerEndMarginArgsInvalid &&
        isColorArgInvalid) {
        GetArkUINodeModifiers()->getTabsModifier()->resetDivider(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension dividerStrokeWidth;
    CalcDimension dividerStartMargin;
    CalcDimension dividerEndMargin;
    uint32_t color;
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto tabTheme = themeManager->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, panda::NativePointerRef::New(vm, nullptr));

    if (isDividerStrokeWidthArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerStrokeWidthArgs, dividerStrokeWidth) ||
        LessNotEqual(dividerStrokeWidth.Value(), 0.0f) || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
        dividerStrokeWidth.Reset();
    }
    Color colorObj;
    if (isColorArgInvalid || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj)) {
        color = tabTheme->GetDividerColor().GetValue();
    } else {
        color = colorObj.GetValue();
    }
    if (isDividerStartMarginArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerStartMarginArgs, dividerStartMargin) ||
        LessNotEqual(dividerStartMargin.Value(), 0.0f) || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
        dividerStartMargin.Reset();
    }
    if (isDividerEndMarginArgsInvalid || !ArkTSUtils::ParseJsDimensionVp(vm, dividerEndMarginArgs, dividerEndMargin) ||
        LessNotEqual(dividerEndMargin.Value(), 0.0f) || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
        dividerEndMargin.Reset();
    }
    uint32_t size = SIZE_OF_THREE;
    ArkUI_Float32 values[size];
    int32_t units[size];
    values[TABS_ARG_INDEX_0] = static_cast<ArkUI_Float32>(dividerStrokeWidth.Value());
    values[TABS_ARG_INDEX_1] = static_cast<ArkUI_Float32>(dividerStartMargin.Value());
    values[TABS_ARG_INDEX_2] = static_cast<ArkUI_Float32>(dividerEndMargin.Value());
    units[TABS_ARG_INDEX_0] = static_cast<int32_t>(dividerStrokeWidth.Unit());
    units[TABS_ARG_INDEX_1] = static_cast<int32_t>(dividerStartMargin.Unit());
    units[TABS_ARG_INDEX_2] = static_cast<int32_t>(dividerEndMargin.Unit());
    GetArkUINodeModifiers()->getTabsModifier()->setDivider(nativeNode, color, values, units, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetFadingEdge(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool fadingEdge = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setFadingEdge(nativeNode, fadingEdge);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetFadingEdge(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool ParseJsInt32(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    if (value->IsString(vm)) {
        result = StringUtils::StringToInt(value->ToString(vm)->ToString(vm));
        return true;
    }

    return false;
}

void SetBarBackgroundBlurStyleParam(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Bool& isValidColor,
    Color& inactiveColor, ArkUI_Int32& policy, ArkUI_Int32& blurType)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> policyArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_6);
    Local<JSValueRef> inactiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_7);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_8);
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor)) {
        isValidColor = true;
    }
    ParseJsInt32(vm, policyArg, policy);
    if (policy < static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) ||
        policy > static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    }
    ParseJsInt32(vm, typeArg, blurType);
    if (blurType < static_cast<int32_t>(BlurType::WITHIN_WINDOW) ||
        blurType > static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    }
}

ArkUINativeModuleValue TabsBridge::SetBarBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> blurStyleArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> colorModeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> adaptiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> scaleArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    Local<JSValueRef> blurOptionsArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_5);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    BlurOption blurOption;
    ArkUITabBarBackgroundBlurStyle styleOption = { static_cast<int32_t>(BlurStyle::NO_MATERIAL),
        static_cast<int32_t>(ThemeColorMode::SYSTEM), static_cast<int32_t>(AdaptiveColor::DEFAULT),
        1.0, blurOption.grayscale.data(), blurOption.grayscale.size(),
        static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE), Color::TRANSPARENT.GetValue(),
        false, static_cast<int32_t>(BlurType::WITHIN_WINDOW) };
    if (blurStyleArg->IsNumber()) {
        styleOption.blurStyle = blurStyleArg->Int32Value(vm);
    }
    bool isHasOptions = !(colorModeArg->IsUndefined() && adaptiveColorArg->IsUndefined() && scaleArg->IsUndefined() &&
                          blurOptionsArg->IsUndefined());
    if (isHasOptions) {
        ParseJsInt32(vm, colorModeArg, styleOption.colorMode);
        ParseJsInt32(vm, adaptiveColorArg, styleOption.adaptiveColor);
        if (scaleArg->IsNumber()) {
            styleOption.scale = scaleArg->ToNumber(vm)->Value();
        }
        if (blurOptionsArg->IsArray(vm)) {
            Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(blurOptionsArg);
            auto grey1 = params->GetValueAt(vm, blurOptionsArg, 0)->Uint32Value(vm);
            auto grey2 = params->GetValueAt(vm, blurOptionsArg, 1)->Uint32Value(vm);
            std::vector<float> greyVec = {0.0f, 0.0f};
            greyVec[0] = grey1;
            greyVec[1] = grey2;
            blurOption.grayscale = greyVec;
            styleOption.blurValues = blurOption.grayscale.data();
            styleOption.blurValuesSize = static_cast<ArkUI_Int32>(blurOption.grayscale.size());
        }
    }
    Color inactiveColor = Color::TRANSPARENT;
    SetBarBackgroundBlurStyleParam(runtimeCallInfo, styleOption.isValidColor, inactiveColor,
        styleOption.policy, styleOption.blurType);
    styleOption.inactiveColor = inactiveColor.GetValue();
    GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundBlurStyle(nativeNode, &styleOption);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundBlurStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetBarBackgroundEffectParam(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Int32& policy, ArkUI_Int32& blurType,
    Color& inactiveColor, ArkUI_Bool& isValidColor)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> policyArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_7);
    Local<JSValueRef> inactiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_8);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_9);
    ParseJsInt32(vm, policyArg, policy);
    if (policy < static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) ||
        policy > static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    }
    ParseJsInt32(vm, typeArg, blurType);
    if (blurType < static_cast<int32_t>(BlurType::WITHIN_WINDOW) ||
        blurType > static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    }
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor)) {
        isValidColor = true;
    }
}

void SetAdaptiveColorAndBlurOptionParam(ArkUIRuntimeCallInfo* runtimeCallInfo, AdaptiveColor& adaptiveColor,
    BlurOption& blurOption)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> adaptiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_5);
    Local<JSValueRef> blurOptionsArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_6);
    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    if (adaptiveColorArg->IsNumber()) {
        adaptiveColorValue = adaptiveColorArg->Int32Value(vm);
        if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
        }
    }
    if (blurOptionsArg->IsArray(vm)) {
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(blurOptionsArg);
        auto grey1 = params->GetValueAt(vm, blurOptionsArg, 0)->Uint32Value(vm);
        auto grey2 = params->GetValueAt(vm, blurOptionsArg, 1)->Uint32Value(vm);
        std::vector<float> greyVec = {0.0f, 0.0f};
        greyVec[0] = grey1;
        greyVec[1] = grey2;
        blurOption.grayscale = greyVec;
    }
}

ArkUINativeModuleValue TabsBridge::SetBarBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> saturationArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> brightnessArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    CHECK_NULL_RETURN(frameNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    BlurOption blurOption;
    ArkUITabBarBackgroundEffect effectOption = { 0.0f, 1.0f, 1.0f, Color::TRANSPARENT.GetValue(),
        static_cast<int32_t>(AdaptiveColor::DEFAULT), blurOption.grayscale.data(), blurOption.grayscale.size(),
        static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE), static_cast<int32_t>(BlurType::WITHIN_WINDOW),
        Color::TRANSPARENT.GetValue(), false };
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    effectOption.radius = static_cast<ArkUI_Float32>(radius.Value());
    if (saturationArg->IsNumber()) {
        effectOption.saturation = saturationArg->ToNumber(vm)->Value();
        effectOption.saturation = (effectOption.saturation > 0.0f || NearZero(effectOption.saturation)) ?
                                    effectOption.saturation : 1.0f;
    }
    if (brightnessArg->IsNumber()) {
        effectOption.brightness = brightnessArg->ToNumber(vm)->Value();
        effectOption.brightness = (effectOption.brightness > 0.0f || NearZero(effectOption.brightness)) ?
                                    effectOption.brightness : 1.0f;
    }
    Color color = Color::TRANSPARENT;
    if (!ArkTSUtils::ParseJsColor(vm, colorArg, color)) {
        color.SetValue(Color::TRANSPARENT.GetValue());
    }
    effectOption.color = color.GetValue();
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    SetAdaptiveColorAndBlurOptionParam(runtimeCallInfo, adaptiveColor, blurOption);
    effectOption.adaptiveColor = static_cast<ArkUI_Int32>(adaptiveColor);
    effectOption.blurValues = blurOption.grayscale.data();
    effectOption.blurValuesSize = static_cast<ArkUI_Int32>(blurOption.grayscale.size());
    Color inactiveColor = Color::TRANSPARENT;
    SetBarBackgroundEffectParam(runtimeCallInfo, effectOption.policy, effectOption.blurType,
        inactiveColor, effectOption.isValidColor);
    effectOption.inactiveColor = inactiveColor.GetValue();
    GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundEffect(nativeNode, &effectOption);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> overlapArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (overlapArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetBarOverlap(nativeNode);
    } else {
        bool overlap = overlapArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getTabsModifier()->setBarOverlap(nativeNode, overlap);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarOverlap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabsBridge::SetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> isVerticalArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (isVerticalArg->IsNull() || isVerticalArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetIsVertical(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isVertical = isVerticalArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setIsVertical(nativeNode, isVertical);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetIsVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> barValArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (barValArg->IsNull() || barValArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarPosition(nativeNode);
    } else {
        int32_t barVal = barValArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setTabBarPosition(nativeNode, barVal);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOptionsIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> indexValArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (indexValArg->IsNull() || indexValArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOptionsIndex(nativeNode);
    } else {
        int32_t indexVal = indexValArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsIndex(nativeNode, indexVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOptionsIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOptionsIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOptionsController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    RefPtr<NG::TabsControllerNG> tabsController = AceType::MakeRefPtr<NG::TabsControllerNG>();
    if (info[1]->IsObject()) {
        auto* jsTabsController =
            Framework::JSRef<Framework::JSObject>::Cast(info[1])->Unwrap<Framework::JSTabsController>();
            if (jsTabsController) {
                jsTabsController->SetInstanceId(Container::CurrentId());
                jsTabsController->SetTabsController(tabsController);
            }
    }
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsController(nativeNode,
        reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(tabsController)));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOptionsController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    RefPtr<NG::TabsControllerNG> tabsController = AceType::MakeRefPtr<NG::TabsControllerNG>();
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsController(nativeNode,
        reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(tabsController)));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scrollableArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);

    if (scrollableArg->IsNull() || scrollableArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetScrollable(nativeNode);
        return undefinedRes;
    }

    bool scrollable = scrollableArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setScrollable(nativeNode, scrollable);
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetScrollable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension width;
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);

    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarWidth(nativeNode);
        return undefinedRes;
    }

    GetArkUINodeModifiers()->getTabsModifier()->setTabBarWidth(
        nativeNode, width.Value(), static_cast<int>(width.Unit()));
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);

    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarHeight(nativeNode);
        return undefinedRes;
    }

    GetArkUINodeModifiers()->getTabsModifier()->setTabBarHeight(
        nativeNode, height.Value(), static_cast<int>(height.Unit()));
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool value = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setBarAdaptiveHeight(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarAdaptiveHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> durationArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (durationArg->IsNull() || durationArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimationDuration(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    float duration = durationArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setAnimationDuration(nativeNode, duration);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetAnimationDuration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t barVal = secondArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setTabBarPosition(nativeNode, barVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info[TABS_ARG_INDEX_1]->IsUndefined()) {
        ViewAbstract::SetClipEdge(frameNode, false);
        return panda::JSValueRef::Undefined(vm);
    }
    if (info[TABS_ARG_INDEX_1]->IsObject()) {
        CommonBridge::SetClip(runtimeCallInfo);
    } else if (info[TABS_ARG_INDEX_1]->IsBoolean()) {
        GetArkUINodeModifiers()->getTabsModifier()->setTabClip(nativeNode, info[TABS_ARG_INDEX_1]->ToBoolean());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabClip(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    int32_t effect = static_cast<int32_t>(EdgeEffect::SPRING);
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        effect = static_cast<int32_t>(EdgeEffect::SPRING);
    } else {
        effect = secondArg->Int32Value(vm);
    }
    if (effect < static_cast<int32_t>(EdgeEffect::SPRING) || effect > static_cast<int32_t>(EdgeEffect::NONE)) {
        effect = static_cast<int32_t>(EdgeEffect::SPRING);
    }
    GetArkUINodeModifiers()->getTabsModifier()->setTabEdgeEffect(nativeNode, effect);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabEdgeEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    if (valueArg->IsNumber()) {
        int32_t pageFlipMode = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setTabPageFlipMode(nativeNode, pageFlipMode);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabPageFlipMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabPageFlipMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetWidthAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, width);
    if (width.Unit() == DimensionUnit::AUTO) {
        CommonBridge::SetWidth(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->setTabWidthAuto(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        CommonBridge::SetWidth(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->resetTabWidthAuto(nativeNode);
    }
    CommonBridge::SetWidth(runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetWidthAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetWidth(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabWidthAuto(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetHeightAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension height;
    ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, height);
    if (height.Unit() == DimensionUnit::AUTO) {
        CommonBridge::SetHeight(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->setTabHeightAuto(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        CommonBridge::SetHeight(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->resetTabHeightAuto(nativeNode);
    }
    CommonBridge::SetHeight(runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetHeightAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetHeight(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabHeightAuto(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetAnimateMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> animateModeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (!animateModeArg->IsNumber()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimateMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t animateModeValue = animateModeArg->Uint32Value(vm);
    if (animateModeValue >= static_cast<uint32_t>(TabAnimateMode::MAX_VALUE)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimateMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTabsModifier()->setAnimateMode(nativeNode, animateModeValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetAnimateMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetAnimateMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
