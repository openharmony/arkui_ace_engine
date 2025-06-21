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

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/engine/functions/js_tabs_function.h"
#include "bridge/declarative_frontend/jsview/js_tabs.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "core/components/common/properties/color.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/tab_bar/tabs_event.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

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
constexpr int32_t DEFAULT_CUSTOM_ANIMATION_TIMEOUT = 1000;
constexpr int ANIMATION_CURVE_TYPE_DEFAULT = 0;
constexpr int ANIMATION_CURVE_TYPE_STR = 1;
constexpr int ANIMATION_CURVE_TYPE_FUNC = 2;
namespace {
void GetAnimationCurveInfo(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Uint32& type, std::string& aniTimFunc,
    std::function<float(float)>& customCallBack)
{
    type = ANIMATION_CURVE_TYPE_DEFAULT;
    aniTimFunc.clear();
    customCallBack = nullptr;
    CHECK_NULL_VOID(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    if (!valueArg->IsObject(vm)) {
        return;
    }
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    auto object = Framework::JSRef<Framework::JSObject>::Cast(info[TABS_ARG_INDEX_1]);
    Framework::JSRef<Framework::JSVal> onCallBack = object->GetProperty("__curveCustomFunc");
    if (onCallBack->IsFunction()) {
        RefPtr<Framework::JsFunction> jsFuncCallBack =
            AceType::MakeRefPtr<Framework::JsFunction>(Framework::JSRef<Framework::JSObject>(),
            Framework::JSRef<Framework::JSFunc>::Cast(onCallBack));
        customCallBack = [func = std::move(jsFuncCallBack), id = Container::CurrentId()](float time) -> float {
            ContainerScope scope(id);
            Framework::JSRef<Framework::JSVal> params[1];
            params[0] = Framework::JSRef<Framework::JSVal>::Make(Framework::ToJSValue(time));
            auto result = func->ExecuteJS(1, params);
            auto resultValue = result->IsNumber() ? result->ToNumber<float>() : 1.0f;
            return resultValue;
        };
    }
    auto jsCurveString = object->GetProperty("__curveString");
    if (jsCurveString->IsString()) {
        aniTimFunc = jsCurveString->ToString();
        if (aniTimFunc == DOM_ANIMATION_TIMING_FUNCTION_CUSTOM && customCallBack) {
            type = ANIMATION_CURVE_TYPE_FUNC;
        } else if (aniTimFunc != DOM_ANIMATION_TIMING_FUNCTION_CUSTOM) {
            type = ANIMATION_CURVE_TYPE_STR;
        }
    }
}
} // namespace

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

    GetArkUINodeModifiers()->getTabsModifier()->createScrollableBarModeOptionsWithResourceObj(nativeNode, nullptr);
    if (tabBarMode == TABBARMODE_SCROLLABLE) {
        if (marginArg->IsNull() || marginArg->IsUndefined() || nonScrollableLayoutStyleArg->IsNull() ||
            nonScrollableLayoutStyleArg->IsUndefined()) {
            GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        int barModeStyle = nonScrollableLayoutStyleArg->Int32Value(vm);
        CalcDimension margin(0.0, DimensionUnit::VP);
        RefPtr<ResourceObject> marginResObj;
        if (!ArkTSUtils::ParseJsDimensionVp(vm, marginArg, margin, marginResObj)) {
            margin.Reset();
        }

        GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
            nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
        GetArkUINodeModifiers()->getTabsModifier()->createScrollableBarModeOptionsWithResourceObj(
            nativeNode, AceType::RawPtr(marginResObj));
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
    RefPtr<ResourceObject> marginResObj;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, margin, marginResObj)) {
        margin.Reset();
    }

    GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
        nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
    GetArkUINodeModifiers()->getTabsModifier()->createScrollableBarModeOptionsWithResourceObj(
        nativeNode, AceType::RawPtr(marginResObj));
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
    RefPtr<ResourceObject> columnGutterResObj;
    RefPtr<ResourceObject> columnMarginResObj;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, gutterArg, columnGutter, columnGutterResObj) ||
        !NonNegative(columnGutter.Value()) ||
        columnGutter.Unit() == DimensionUnit::PERCENT) {
        columnGutter.Reset();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, marginArg, columnMargin, columnMarginResObj) ||
        !NonNegative(columnMargin.Value()) ||
        columnMargin.Unit() == DimensionUnit::PERCENT) {
        columnMargin.Reset();
    }

    ArkUI_Float32 values[SIZE_OF_VALUES] = { static_cast<ArkUI_Float32>(columnGutter.Value()),
        static_cast<ArkUI_Float32>(columnMargin.Value()) };
    int unitsAndColumn[SIZE_OF_FIVE] = { static_cast<int>(columnGutter.Unit()), static_cast<int>(columnMargin.Unit()),
        sm, md, lg };

    GetArkUINodeModifiers()->getTabsModifier()->setBarGridAlign(
        nativeNode, values, SIZE_OF_VALUES, unitsAndColumn, SIZE_OF_FIVE);
    GetArkUINodeModifiers()->getTabsModifier()->createBarGridAlignWithResourceObj(
        nativeNode, AceType::RawPtr(columnGutterResObj), AceType::RawPtr(columnMarginResObj));
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

    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    if (isDividerStrokeWidthArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerStrokeWidthArgs, dividerStrokeWidth, strokeWidthResObj) ||
        LessNotEqual(dividerStrokeWidth.Value(), 0.0f) || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
        dividerStrokeWidth.Reset();
    }
    Color colorObj;
    if (isColorArgInvalid || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj, colorResObj)) {
        color = tabTheme->GetDividerColor().GetValue();
        GetArkUINodeModifiers()->getTabsModifier()->setDividerColorByUser(nativeNode, false);
    } else {
        color = colorObj.GetValue();
        GetArkUINodeModifiers()->getTabsModifier()->setDividerColorByUser(nativeNode, true);
    }
    if (isDividerStartMarginArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerStartMarginArgs, dividerStartMargin, startMarginResObj) ||
        LessNotEqual(dividerStartMargin.Value(), 0.0f) || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
        dividerStartMargin.Reset();
    }
    if (isDividerEndMarginArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerEndMarginArgs, dividerEndMargin, endMarginResObj) ||
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
    GetArkUINodeModifiers()->getTabsModifier()->createDividerWithResourceObj(nativeNode,
        AceType::RawPtr(strokeWidthResObj), AceType::RawPtr(colorResObj), AceType::RawPtr(startMarginResObj),
        AceType::RawPtr(endMarginResObj));
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

ArkUINativeModuleValue TabsBridge::SetTabOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabOnUnselected(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs  OnUnselected callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, tabsInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabOnUnselected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabOnUnselected(nativeNode);
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
    RefPtr<ResourceObject> backgroundColorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, backgroundColorResObj)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundColor(nativeNode, color.GetValue());
        auto bgColorRawPtr = AceType::RawPtr(backgroundColorResObj);
        GetArkUINodeModifiers()->getTabsModifier()->createBarBackgroundColorWithResourceObj(nativeNode, bgColorRawPtr);
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

RefPtr<ResourceObject> SetBarBackgroundBlurStyleParam(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Bool& isValidColor,
    Color& inactiveColor, ArkUI_Int32& policy, ArkUI_Int32& blurType)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> policyArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_6);
    Local<JSValueRef> inactiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_7);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_8);
    RefPtr<ResourceObject> inactiveColorResObj;
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor, inactiveColorResObj)) {
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
    return inactiveColorResObj;
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
        1.0, blurOption.grayscale.data(), static_cast<ArkUI_Int32>(blurOption.grayscale.size()),
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
    auto inactiveColorResObj = SetBarBackgroundBlurStyleParam(runtimeCallInfo, styleOption.isValidColor, inactiveColor,
        styleOption.policy, styleOption.blurType);
    styleOption.inactiveColor = inactiveColor.GetValue();
    GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundBlurStyle(nativeNode, &styleOption);
    GetArkUINodeModifiers()->getTabsModifier()->createBarBackgroundBlurStyleWithResourceObj(nativeNode,
        AceType::RawPtr(inactiveColorResObj));
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

RefPtr<ResourceObject> SetBarBackgroundEffectParam(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Int32& policy,
    ArkUI_Int32& blurType, Color& inactiveColor, ArkUI_Bool& isValidColor)
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
    RefPtr<ResourceObject> inactiveColorResObj;
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor, inactiveColorResObj)) {
        isValidColor = true;
    }
    return inactiveColorResObj;
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

void SetSaturationAndBrightnessEffectOptionParam(const EcmaVM* vm, const Local<JSValueRef>& saturationArg,
    const Local<JSValueRef>& brightnessArg, ArkUITabBarBackgroundEffect& effectOption)
{
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
        static_cast<int32_t>(AdaptiveColor::DEFAULT), blurOption.grayscale.data(),
        static_cast<int32_t>(blurOption.grayscale.size()),
        static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE), static_cast<int32_t>(BlurType::WITHIN_WINDOW),
        static_cast<ArkUI_Bool>(Color::TRANSPARENT.GetValue()), false };
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    effectOption.radius = static_cast<ArkUI_Float32>(radius.Value());
    SetSaturationAndBrightnessEffectOptionParam(vm, saturationArg, brightnessArg, effectOption);
    RefPtr<ResourceObject> colorResObj;
    Color color = Color::TRANSPARENT;
    if (!ArkTSUtils::ParseJsColor(vm, colorArg, color, colorResObj)) {
        color.SetValue(Color::TRANSPARENT.GetValue());
    }
    effectOption.color = color.GetValue();
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    SetAdaptiveColorAndBlurOptionParam(runtimeCallInfo, adaptiveColor, blurOption);
    effectOption.adaptiveColor = static_cast<ArkUI_Int32>(adaptiveColor);
    effectOption.blurValues = blurOption.grayscale.data();
    effectOption.blurValuesSize = static_cast<ArkUI_Int32>(blurOption.grayscale.size());
    Color inactiveColor = Color::TRANSPARENT;
    auto inactiveColorResObj = SetBarBackgroundEffectParam(runtimeCallInfo, effectOption.policy, effectOption.blurType,
        inactiveColor, effectOption.isValidColor);
    effectOption.inactiveColor = inactiveColor.GetValue();
    GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundEffect(nativeNode, &effectOption);
    GetArkUINodeModifiers()->getTabsModifier()->createBarBackgroundEffectWithResourceObj(nativeNode,
        AceType::RawPtr(colorResObj), AceType::RawPtr(inactiveColorResObj));
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

ArkUINativeModuleValue TabsBridge::SetTabsOptionsBarModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::function<void(WeakPtr<NG::FrameNode>)> onApply;
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSTabs::SetBarModifierApply(runtimeCallInfo, onApply, info[1]);
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsBarModifier(
        nativeNode, reinterpret_cast<void*>(&onApply));
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

ArkUINativeModuleValue TabsBridge::ResetTabsOptionsBarModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOptionsBarModifier(nativeNode);
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

    RefPtr<ResourceObject> widthResObj;
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width,
        widthResObj)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarWidth(nativeNode);
        return undefinedRes;
    }

    GetArkUINodeModifiers()->getTabsModifier()->setTabBarWidth(
        nativeNode, width.Value(), static_cast<int>(width.Unit()));
    auto widthRawPtr = AceType::RawPtr(widthResObj);
    GetArkUINodeModifiers()->getTabsModifier()->createTabBarWidthWithResourceObj(nativeNode, widthRawPtr);
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

    RefPtr<ResourceObject> heightResObj;
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height,
        heightResObj)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarHeight(nativeNode);
        return undefinedRes;
    }

    GetArkUINodeModifiers()->getTabsModifier()->setTabBarHeight(
        nativeNode, height.Value(), static_cast<int>(height.Unit()));
    auto heightRawPtr = AceType::RawPtr(heightResObj);
    GetArkUINodeModifiers()->getTabsModifier()->createTabBarHeightWithResourceObj(nativeNode, heightRawPtr);
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

ArkUINativeModuleValue TabsBridge::SetAnimationCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    if (valueArg->IsString(vm)) {
        std::string curve = valueArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setAnimationCurve(nativeNode,
            ANIMATION_CURVE_TYPE_STR, curve.c_str(), nullptr);
    } else if (valueArg->IsObject(vm)) {
        ArkUI_Uint32 type = ANIMATION_CURVE_TYPE_DEFAULT;
        std::string aniTimFunc;
        std::function<float(float)> customCallBack = nullptr;
        GetAnimationCurveInfo(runtimeCallInfo, type, aniTimFunc, customCallBack);
        GetArkUINodeModifiers()->getTabsModifier()->setAnimationCurve(nativeNode,
            type, aniTimFunc.c_str(), reinterpret_cast<void*>(&customCallBack));
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimationCurve(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetAnimationCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetAnimationCurve(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetNoMinHeightLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool value = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setNoMinHeightLimit(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetNoMinHeightLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetNoMinHeightLimit(nativeNode);
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

ArkUINativeModuleValue TabsBridge::SetTabsOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnSelected(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs onSelected callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, tabsInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnSelected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetCachedMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> countArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    int32_t count = 0;
    if (countArg->IsNumber() && countArg->Int32Value(vm) >= 0) {
        count = countArg->Int32Value(vm);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->resetCachedMaxCount(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t mode = 0;
    if (modeArg->IsNumber()) {
        mode = modeArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getTabsModifier()->setCachedMaxCount(nativeNode, count, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetCachedMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetCachedMaxCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabsBridge::SetTabsOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const BaseEventInfo* info)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                  const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs onChange callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onChange");
        ACE_SCOPED_TRACE("Tabs.onChange index %d", tabsInfo->GetIndex());
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, tabsInfo->GetIndex()) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnTabBarClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnTabBarClick(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const BaseEventInfo* info)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                  const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs onTabBarClick callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onTabBarClick");
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, tabsInfo->GetIndex()) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnTabBarClick(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnTabBarClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnTabBarClick(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int32_t, int32_t, const AnimationCallbackInfo&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
            int32_t index, int32_t targetIndex, const AnimationCallbackInfo& extraInfo) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
            panda::Local<panda::NumberRef> targetIndexParam = panda::NumberRef::New(vm, targetIndex);
            const char* keys[] = { "currentOffset", "targetOffset", "velocity" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value_or(0.0f)),
                panda::NumberRef::New(vm, extraInfo.targetOffset.value_or(0.0f)),
                panda::NumberRef::New(vm, extraInfo.velocity.value_or(0.0f)) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[3] = { indexParam, targetIndexParam,
                eventObject };                         // 3: Array length
            func->Call(vm, func.ToLocal(), params, 3); // 3: Array length
        };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnAnimationStart(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabsBridge::ResetTabsOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationEnd(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, const AnimationCallbackInfo&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](int32_t index, const AnimationCallbackInfo& extraInfo) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
            const char* keys[] = { "currentOffset", "targetOffset", "velocity" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value_or(0.0f)),
                panda::NumberRef::New(vm, 0), panda::NumberRef::New(vm, 0) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
            func->Call(vm, func.ToLocal(), params, 2);                               // 2: Array length
        };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnAnimationEnd(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnGestureSwipe(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int32_t, const AnimationCallbackInfo&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](int32_t index, const AnimationCallbackInfo& extraInfo) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
            const char* keys[] = { "currentOffset", "targetOffset", "velocity" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value_or(0.0f)),
                panda::NumberRef::New(vm, 0), panda::NumberRef::New(vm, 0) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
            func->Call(vm, func.ToLocal(), params, 2);                               // 2: Array length
        };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnGestureSwipe(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnGestureSwipe(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnContentWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnContentWillChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(int32_t, int32_t)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                         int32_t currentIndex, int32_t comingIndex) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> currentIndexParam = panda::NumberRef::New(vm, currentIndex);
        panda::Local<panda::NumberRef> comingIndexParam = panda::NumberRef::New(vm, comingIndex);
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { currentIndexParam, comingIndexParam };
        auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (result->IsBoolean()) {
            return result->ToBoolean(vm)->Value();
        }
        return false;
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnContentWillChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnContentWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnContentWillChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    using namespace OHOS::Ace::Framework;
    JsiCallbackInfo info = JsiCallbackInfo(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (info.Length() != 2) { // 2: Array length
        return panda::JSValueRef::Undefined(vm);
    }

    if (!info[1]->IsFunction()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsIsCustomAnimation(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto transitionFunc = JSRef<JSFunc>::Cast(info[1]);
    
    ParseCustomContentTransition(transitionFunc, info);

    GetArkUINodeModifiers()->getTabsModifier()->setTabsIsCustomAnimation(nativeNode, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsIsCustomAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void TabsBridge::ParseCustomContentTransition(
    const Framework::JSRef<Framework::JSFunc>& transitionFunc, const Framework::JsiCallbackInfo& info)
{
    using namespace OHOS::Ace::Framework;
    RefPtr<JsTabsFunction> jsCustomAnimationFunc =
        AceType::MakeRefPtr<JsTabsFunction>(transitionFunc);
    auto onCustomAnimation = [execCtx = info.GetExecutionContext(), func = std::move(jsCustomAnimationFunc)](
                                 int32_t from, int32_t to) -> TabContentAnimatedTransition {
        TabContentAnimatedTransition transitionInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, transitionInfo);

        auto ret = func->Execute(from, to);
        if (!ret->IsObject()) {
            return transitionInfo;
        }

        auto transitionObj = JSRef<JSObject>::Cast(ret);
        JSRef<JSVal> timeoutProperty = transitionObj->GetProperty("timeout");
        transitionInfo.timeout = DEFAULT_CUSTOM_ANIMATION_TIMEOUT;
        if (timeoutProperty->IsNumber()) {
            auto timeout = timeoutProperty->ToNumber<int32_t>();
            transitionInfo.timeout = timeout < 0 ? DEFAULT_CUSTOM_ANIMATION_TIMEOUT : timeout;
        }

        JSRef<JSVal> transition = transitionObj->GetProperty("transition");
        if (transition->IsFunction()) {
            RefPtr<JsTabsFunction> jsOnTransition =
                AceType::MakeRefPtr<JsTabsFunction>(transition);
            auto onTransition = [execCtx, func = std::move(jsOnTransition)](
                                    const RefPtr<TabContentTransitionProxy>& proxy) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("onTransition");
                func->Execute(proxy);
            };

            transitionInfo.transition = std::move(onTransition);
        }

        return transitionInfo;
    };

    TabsModel::GetInstance()->SetOnCustomAnimation(std::move(onCustomAnimation));
}
} // namespace OHOS::Ace::NG
