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
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (arg_columnsTemplate->IsUndefined() || !arg_columnsTemplate->IsString()) {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridColumnsTemplate(nativeNode);
    } else {
        std::string columnsTemplate = arg_columnsTemplate->ToString(vm)->ToString();
        GetArkUIInternalNodeAPI()->GetGridModifier().SetGridColumnsTemplate(nativeNode, columnsTemplate.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_rowsTemplate = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (arg_rowsTemplate->IsUndefined() || !arg_rowsTemplate->IsString()) {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridRowsTemplate(nativeNode);
    } else {
        std::string rowsTemplate = arg_rowsTemplate->ToString(vm)->ToString();
        GetArkUIInternalNodeAPI()->GetGridModifier().SetGridRowsTemplate(nativeNode, rowsTemplate.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetRowsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridRowsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength columnGap = { 0.0, 0, nullptr };
    if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, arg_size, size, true)) {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridColumnsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            columnGap.Uint = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            columnGap.string = calcStr.c_str();
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridColumnsGap(nativeNode, &columnGap);
        } else {
            columnGap.value = size.Value();
            columnGap.Uint = static_cast<int32_t>(size.Unit());
            columnGap.string = calcStr.c_str();
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridColumnsGap(nativeNode, &columnGap);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();

    CalcDimension size;
    std::string calcStr;
    struct ArkUIResourceLength rowsGap = { 0.0, 0, nullptr };
    if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, arg_size, size, true)) {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridRowsGap(nativeNode);
    } else {
        if (size.Unit() == DimensionUnit::CALC) {
            rowsGap.Uint = static_cast<int32_t>(DimensionUnit::CALC);
            calcStr = size.CalcValue();
            rowsGap.string = calcStr.c_str();
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridRowsGap(nativeNode, &rowsGap);
        } else {
            rowsGap.value = size.Value();
            rowsGap.Uint = static_cast<int32_t>(size.Unit());
            rowsGap.string = calcStr.c_str();
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridRowsGap(nativeNode, &rowsGap);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_scrollBar = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (!arg_scrollBar->IsNull() && arg_scrollBar->IsNumber()) {
        int32_t scrollBar = arg_scrollBar->Int32Value(vm);
        if (scrollBar < 0) {
            GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBar(nativeNode);
        } else {
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridScrollBar(nativeNode, scrollBar);
        }
    } else {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();

    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, scrollBarArg, scrollBarWidth, false)) {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBarWidth(nativeNode);
    } else {
        if (LessNotEqual(scrollBarWidth.Value(), 0.0f)) {
            GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBarWidth(nativeNode);
        } else {
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridScrollBarWidth(
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
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_color = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (arg_color->IsNull() || arg_color->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBarColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (arg_color->IsNumber()) {
        auto colorNum = arg_color->ToNumber(vm)->Value();
        if (colorNum <= 0) {
            GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBarColor(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    }
    Color color;
    if (ArkTSUtils::ParseJsColorAlpha(vm, arg_color, color)) {
        GetArkUIInternalNodeAPI()->GetGridModifier().SetGridScrollBarColor(
            nativeNode, color.GetValue());
    } else {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBarColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_cachedCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    auto value = DEFAULT_CACHED_COUNT;
    if (!arg_cachedCount->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, arg_cachedCount, value);
        if (value < 0) {
            value = DEFAULT_CACHED_COUNT;
        }
    }
    GetArkUIInternalNodeAPI()->GetGridModifier().SetGridCachedCount(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridCachedCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_editMode = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    bool editMode = arg_editMode->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().SetGridEditMode(nativeNode, editMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridEditMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_multiSelectable = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    bool multiSelectable = arg_multiSelectable->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().SetGridMultiSelectable(nativeNode, multiSelectable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridMultiSelectable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_maxCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (!arg_maxCount->IsNull() && arg_maxCount->IsNumber()) {
        int32_t maxCount = arg_maxCount->Int32Value(vm);
        if (maxCount < 1) {
            GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridMaxCount(nativeNode);
        } else {
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridMaxCount(nativeNode, maxCount);
        }
    } else {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridMaxCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridMaxCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetMinCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_minCount = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (!arg_minCount->IsNull() && arg_minCount->IsNumber()) {
        int32_t minCount = arg_minCount->Int32Value(vm);
        if (minCount < 1) {
            GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridMinCount(nativeNode);
        } else {
            GetArkUIInternalNodeAPI()->GetGridModifier().SetGridMinCount(nativeNode, minCount);
        }
    } else {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridMinCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetMinCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridMinCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetCellLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_cellLength = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (!arg_cellLength->IsNull() && arg_cellLength->IsNumber()) {
        int32_t cellLength = arg_cellLength->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetGridModifier().SetGridCellLength(nativeNode, cellLength);
    } else {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridCellLength(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetCellLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridCellLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_layoutDirection = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (!arg_layoutDirection->IsNull() && arg_layoutDirection->IsNumber()) {
        int32_t layoutDirection = arg_layoutDirection->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetGridModifier().SetGridLayoutDirection(nativeNode, layoutDirection);
    } else {
        GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridLayoutDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetLayoutDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridLayoutDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetSupportAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_supportAnimation = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    bool supportAnimation = arg_supportAnimation->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().SetGridSupportAnimation(nativeNode, supportAnimation);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::ResetSupportAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetGridSupportAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridBridge::SetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_effect = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> arg_edgeEffectOptions = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);

    void* nativeNode = node->ToNativePointer(vm)->Value();
    int32_t effect = static_cast<int32_t>(EdgeEffect::NONE);
    if (!arg_effect->IsUndefined() && !arg_effect->IsNull()) {
        effect = arg_effect->Int32Value(vm);
    }

    if (effect != static_cast<int32_t>(EdgeEffect::SPRING) && effect != static_cast<int32_t>(EdgeEffect::NONE) &&
        effect != static_cast<int32_t>(EdgeEffect::FADE)) {
        effect = static_cast<int32_t>(EdgeEffect::NONE);
    }

    if (arg_edgeEffectOptions->IsNull() || arg_edgeEffectOptions->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetGridModifier().SetEdgeEffect(nativeNode, effect, false);
    } else {
        GetArkUIInternalNodeAPI()->GetGridModifier().SetEdgeEffect(
            nativeNode, effect, arg_edgeEffectOptions->ToBoolean(vm)->Value());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetEdgeEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_forward = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> arg_backward = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);

    void* nativeNode = node->ToNativePointer(vm)->Value();
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

    GetArkUIInternalNodeAPI()->GetGridModifier().SetNestedScroll(nativeNode, forward, backward);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_enableScrool = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    void* nativeNode = node->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetGridModifier().SetEnableScroll(
        nativeNode, arg_enableScrool->IsBoolean() ? arg_enableScrool->ToBoolean(vm)->Value() : true);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetEnableScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::SetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> arg_friction = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);

    double friction = -1.0;
    void* nativeNode = node->ToNativePointer(vm)->Value();
    if (!ArkTSUtils::ParseJsDouble(vm, arg_friction, friction)) {
        friction = -1.0;
    }
    GetArkUIInternalNodeAPI()->GetGridModifier().SetFriction(nativeNode, friction);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridBridge::ResetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = node->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGridModifier().ResetFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
