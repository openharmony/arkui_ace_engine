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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_bridge.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
constexpr int32_t CALL_ARG_2 = 2;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;

ArkUINativeModuleValue GridBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_columnsTemplate = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (arg_columnsTemplate->IsUndefined() || !arg_columnsTemplate->IsString()) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsTemplate(nativeNode);
    } else {
        std::string columnsTemplate = arg_columnsTemplate->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getGridModifier()->setGridColumnsTemplate(nativeNode, columnsTemplate.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_rowsTemplate = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (arg_rowsTemplate->IsUndefined() || !arg_rowsTemplate->IsString()) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridRowsTemplate(nativeNode);
    } else {
        std::string rowsTemplate = arg_rowsTemplate->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getGridModifier()->setGridRowsTemplate(nativeNode, rowsTemplate.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridRowsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength columnGap = { 0.0, 0, nullptr };
    if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, arg_size, size, true)) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            columnGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            columnGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getGridModifier()->setGridColumnsGap(nativeNode, &columnGap);
        } else {
            columnGap.value = size.Value();
            columnGap.unit = static_cast<int32_t>(size.Unit());
            columnGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getGridModifier()->setGridColumnsGap(nativeNode, &columnGap);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength rowsGap = { 0.0, 0, nullptr };
    if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, arg_size, size, true)) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridRowsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            rowsGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            rowsGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getGridModifier()->setGridRowsGap(nativeNode, &rowsGap);
        } else {
            rowsGap.value = size.Value();
            rowsGap.unit = static_cast<int32_t>(size.Unit());
            rowsGap.string = calcStr.c_str();
            GetArkUINodeModifiers()->getGridModifier()->setGridRowsGap(nativeNode, &rowsGap);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_scrollBar = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!arg_scrollBar->IsNull() && arg_scrollBar->IsNumber()) {
        int32_t scrollBar = arg_scrollBar->Int32Value(vm);
        if (scrollBar < 0) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBar(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridScrollBar(nativeNode, scrollBar);
        }
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, scrollBarArg, scrollBarWidth, false)) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarWidth(nativeNode);
    } else {
        if (LessNotEqual(scrollBarWidth.Value(), 0.0f)) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarWidth(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridScrollBarWidth(
                nativeNode, scrollBarWidth.Value(), static_cast<int32_t>(scrollBarWidth.Unit()));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_color = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (arg_color->IsNull() || arg_color->IsUndefined()) {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (arg_color->IsNumber()) {
        auto colorNum = arg_color->ToNumber(vm)->Value();
        if (colorNum <= 0) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, arg_color, color)) {
        GetArkUINodeModifiers()->getGridModifier()->setGridScrollBarColor(
            nativeNode, color.GetValue());
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_cachedCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    auto value = DEFAULT_CACHED_COUNT;
    if (!arg_cachedCount->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, arg_cachedCount, value);
        if (value < 0) {
            value = DEFAULT_CACHED_COUNT;
        }
    }
    GetArkUINodeModifiers()->getGridModifier()->setGridCachedCount(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridCachedCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_editMode = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    bool editMode = arg_editMode->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getGridModifier()->setGridEditMode(nativeNode, editMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridEditMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_multiSelectable = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    bool multiSelectable = arg_multiSelectable->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getGridModifier()->setGridMultiSelectable(nativeNode, multiSelectable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridMultiSelectable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_maxCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!arg_maxCount->IsNull() && arg_maxCount->IsNumber()) {
        int32_t maxCount = arg_maxCount->Int32Value(vm);
        if (maxCount < 1) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridMaxCount(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridMaxCount(nativeNode, maxCount);
        }
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridMaxCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridMaxCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMinCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_minCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!arg_minCount->IsNull() && arg_minCount->IsNumber()) {
        int32_t minCount = arg_minCount->Int32Value(vm);
        if (minCount < 1) {
            GetArkUINodeModifiers()->getGridModifier()->resetGridMinCount(nativeNode);
        } else {
            GetArkUINodeModifiers()->getGridModifier()->setGridMinCount(nativeNode, minCount);
        }
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridMinCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMinCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridMinCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetCellLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_cellLength = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!arg_cellLength->IsNull() && arg_cellLength->IsNumber()) {
        int32_t cellLength = arg_cellLength->Int32Value(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridCellLength(nativeNode, cellLength);
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridCellLength(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetCellLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridCellLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_layoutDirection = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!arg_layoutDirection->IsNull() && arg_layoutDirection->IsNumber()) {
        int32_t layoutDirection = arg_layoutDirection->Int32Value(vm);
        GetArkUINodeModifiers()->getGridModifier()->setGridLayoutDirection(nativeNode, layoutDirection);
    } else {
        GetArkUINodeModifiers()->getGridModifier()->resetGridLayoutDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridLayoutDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetSupportAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_supportAnimation = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    bool supportAnimation = arg_supportAnimation->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getGridModifier()->setGridSupportAnimation(nativeNode, supportAnimation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetSupportAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetGridSupportAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_effect = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> arg_edgeEffectOptions = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);

    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    int32_t effect = static_cast<int32_t>(EdgeEffect::NONE);
    if (!arg_effect->IsUndefined() && !arg_effect->IsNull()) {
        effect = arg_effect->Int32Value(vm);
    }

    if (effect != static_cast<int32_t>(EdgeEffect::SPRING) && effect != static_cast<int32_t>(EdgeEffect::NONE) &&
        effect != static_cast<int32_t>(EdgeEffect::FADE)) {
        effect = static_cast<int32_t>(EdgeEffect::NONE);
    }

    if (arg_edgeEffectOptions->IsNull() || arg_edgeEffectOptions->IsUndefined()) {
        GetArkUINodeModifiers()->getGridModifier()->setEdgeEffect(nativeNode, effect, false);
    } else {
        GetArkUINodeModifiers()->getGridModifier()->setEdgeEffect(
            nativeNode, effect, arg_edgeEffectOptions->ToBoolean(vm)->Value());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetEdgeEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_forward = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> arg_backward = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);

    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    int32_t forward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    int32_t backward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    if (!arg_forward->IsUndefined()) {
        forward = arg_forward->Int32Value(vm);
    }
    if (!arg_backward->IsUndefined()) {
        backward = arg_backward->Int32Value(vm);
    }

    if (forward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        forward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        forward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    }

    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    }

    GetArkUINodeModifiers()->getGridModifier()->setNestedScroll(nativeNode, forward, backward);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_enableScroll = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getGridModifier()->setEnableScroll(
        nativeNode, arg_enableScroll->IsBoolean() ? arg_enableScroll->ToBoolean(vm)->Value() : true);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetEnableScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_friction = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    double friction = -1.0;
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!ArkTSUtils::ParseJsDouble(vm, arg_friction, friction)) {
        friction = -1.0;
    }
    GetArkUINodeModifiers()->getGridModifier()->setFriction(nativeNode, static_cast<ArkUI_Float32>(friction));

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetFlingSpeedLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_flingSpeedLimit = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    double flingSpeedLimit = -1.0f;
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    if (!ArkTSUtils::ParseJsDouble(vm, arg_flingSpeedLimit, flingSpeedLimit)) {
        flingSpeedLimit = -1.0f;
    }
    GetArkUINodeModifiers()->getGridModifier()->setFlingSpeedLimit(nativeNode, flingSpeedLimit);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetFlingSpeedLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridModifier()->resetFlingSpeedLimit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
