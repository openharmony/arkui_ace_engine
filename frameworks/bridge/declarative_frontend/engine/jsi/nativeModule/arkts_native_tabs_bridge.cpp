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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/properties/color.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/tab_bar/tab_theme.h"
#include "frameworks/core/components_ng/pattern/tabs/tabs_node.h"

namespace OHOS::Ace::NG {
constexpr int SIZE_OF_FIVE = 5;
constexpr int SIZE_OF_THREE = 3;
constexpr int SIZE_OF_VALUES = 2;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int32_t SM_COLUMN_NUM = 4;
constexpr int32_t MD_COLUMN_NUM = 8;
constexpr int32_t LG_COLUMN_NUM = 12;
constexpr int32_t DEFAULT_COLUMN = -1;
constexpr int REMAINDER = 2;
ArkUINativeModuleValue TabsBridge::SetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t tabBarMode = secondArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetTabBarMode(nativeNode, tabBarMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (thirdArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetTabsModifier().ResetScrollableBarModeOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int barModeStyle = thirdArg->Int32Value(vm);
    
    CalcDimension margin(0.0, DimensionUnit::VP);
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, margin)) {
        margin.Reset();
    }

    GetArkUIInternalNodeAPI()->GetTabsModifier().SetScrollableBarModeOptions(
        nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetScrollableBarModeOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> smArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> mdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> lgArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> gutterArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> marginArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

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

    CalcDimension columnGutter(0.0, DimensionUnit::VP);
    CalcDimension columnMargin(0.0, DimensionUnit::VP);
    if (!ArkTSUtils::ParseJsDimensionVp(vm, gutterArg, columnGutter) || !NonNegative(columnGutter.Value()) ||
        columnGutter.Unit() == DimensionUnit::PERCENT) {
        columnGutter.Reset();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, marginArg, columnMargin) || !NonNegative(columnMargin.Value()) ||
        columnMargin.Unit() == DimensionUnit::PERCENT) {
        columnMargin.Reset();
    }

    int unitsAndColumn[SIZE_OF_FIVE];
    double values[SIZE_OF_VALUES];

    values[NUM_0] = columnGutter.Value();
    values[NUM_1] = columnMargin.Value();
    unitsAndColumn[NUM_0] = static_cast<int>(columnGutter.Unit());
    unitsAndColumn[NUM_1] = static_cast<int>(columnMargin.Unit());
    unitsAndColumn[NUM_2] = sm;
    unitsAndColumn[NUM_3] = md;
    unitsAndColumn[NUM_4] = lg;

    GetArkUIInternalNodeAPI()->GetTabsModifier().SetBarGridAlign(
        nativeNode, values, SIZE_OF_VALUES, unitsAndColumn, SIZE_OF_FIVE);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetBarGridAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> dividerStartMarginArgs = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> dividerEndMarginArgs = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (dividerStrokeWidthArgs->IsUndefined() && dividerStartMarginArgs->IsUndefined() &&
        dividerEndMarginArgs->IsUndefined() && colorArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetTabsModifier().ResetDivider(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension dividerStrokeWidth(0.0, DimensionUnit::VP);
    CalcDimension dividerStartMargin(0.0, DimensionUnit::VP);
    CalcDimension dividerEndMargin(0.0, DimensionUnit::VP);
    uint32_t color;
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    auto context = frameNode->GetContext();
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto tabTheme = themeManager->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, panda::NativePointerRef::New(vm, nullptr));

    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerStrokeWidthArgs, dividerStrokeWidth) ||
        dividerStrokeWidth.Value() < 0.0f || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
        dividerStrokeWidth.Reset();
    }
    Color colorObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj)) {
        color = tabTheme->GetDividerColor().GetValue();
    } else {
        color = colorObj.GetValue();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerStartMarginArgs, dividerStartMargin) ||
        dividerStartMargin.Value() < 0.0f || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
        dividerStartMargin.Reset();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerEndMarginArgs, dividerEndMargin) ||
        dividerEndMargin.Value() < 0.0f || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
        dividerEndMargin.Reset();
    }
    uint32_t size = SIZE_OF_THREE;
    double values[size];
    int units[size];
    values[NUM_0] = dividerStrokeWidth.Value();
    values[NUM_1] = dividerStartMargin.Value();
    values[NUM_2] = dividerEndMargin.Value();
    units[NUM_0] = static_cast<int>(dividerStrokeWidth.Unit());
    units[NUM_1] = static_cast<int>(dividerStartMargin.Unit());
    units[NUM_2] = static_cast<int>(dividerEndMargin.Unit());
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetDivider(nativeNode, color, values, units, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool fadingEdge = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetFadingEdge(nativeNode, fadingEdge);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetFadingEdge(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetTabsModifier().ResetBarBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetTabsModifier().SetBarBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetBarBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool overlap = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetBarOverlap(nativeNode, overlap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetBarOverlap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabsBridge::SetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool isVertical = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetIsVertical(nativeNode, isVertical);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetIsVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t barVal = secondArg->Int32Value(vm);
    ;
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetTabBarPosition(nativeNode, barVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool scrollable = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetScrollable(nativeNode, scrollable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetScrollable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension width;
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);

    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width)) {
        GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarWidth(nativeNode);
        return undefinedRes;
    }

    CalcDimension invWidth;
    if (NearZero(width.Value()) &&
        ArkTSUtils::ParseJsDimensionFromResource(vm, jsValue, DimensionUnit::INVALID, invWidth) &&
        invWidth.Unit() == DimensionUnit::INVALID) {
        GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarWidth(nativeNode);
        return undefinedRes;
    }

    GetArkUIInternalNodeAPI()->GetTabsModifier().SetTabBarWidth(nativeNode, width.Value(),
        static_cast<int>(width.Unit()));
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CalcDimension height;
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);

    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height)) {
        GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarHeight(nativeNode);
        return undefinedRes;
    }

    CalcDimension invHeight;
    if (NearZero(height.Value()) &&
        ArkTSUtils::ParseJsDimensionFromResource(vm, jsValue, DimensionUnit::INVALID, invHeight) &&
        invHeight.Unit() == DimensionUnit::INVALID) {
        GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarHeight(nativeNode);
        return undefinedRes;
    }
    
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetTabBarHeight(
        nativeNode, height.Value(), static_cast<int>(height.Unit()));
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    bool value = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetBarAdaptiveHeight(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetBarAdaptiveHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float duration = secondArg->ToNumber(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetAnimationDuration(nativeNode, duration);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetAnimationDuration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t barVal = secondArg->ToNumber(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().SetTabBarPosition(nativeNode, barVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetTabsModifier().ResetTabBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
