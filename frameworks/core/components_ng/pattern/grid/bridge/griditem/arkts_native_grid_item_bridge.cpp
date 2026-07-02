/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/components_ng/pattern/grid/bridge/griditem/arkts_native_grid_item_bridge.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/grid/grid_item_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int PARAM_STYLE = 2;
constexpr int32_t DEFAULT_GRIDITEM_STYLE = static_cast<int32_t>(GridItemStyle::NONE);

void CreateForPartialUpdate(const EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    if (runtimeCallInfo->GetArgsNumber() < PARAM_STYLE || runtimeCallInfo->GetCallArgRef(NUM_0).IsEmpty() ||
        !runtimeCallInfo->GetCallArgRef(NUM_0)->IsFunction(vm) || runtimeCallInfo->GetCallArgRef(NUM_1).IsEmpty() ||
        !runtimeCallInfo->GetCallArgRef(NUM_1)->IsBoolean()) {
        LOGE("parameter not valid");
        GetArkUINodeModifiers()->getGridItemModifier()->createStyle(static_cast<ArkUI_Int32>(NG::GridItemStyle::NONE));
        return;
    }
    NG::GridItemStyle gridItemStyle = NG::GridItemStyle::NONE;
    if (runtimeCallInfo->GetArgsNumber() > PARAM_STYLE) {
        bool versionControl = !Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN);
        Local<JSValueRef> obj = runtimeCallInfo->GetCallArgRef(PARAM_STYLE);
        if (!versionControl && !obj.IsEmpty() && obj->IsObject(vm)) {
            Local<JSValueRef> styleObj = ArkTSUtils::GetProperty(vm, obj->ToObject(vm), "style");
            gridItemStyle = styleObj->IsNumber() ? static_cast<NG::GridItemStyle>(styleObj->Int32Value(vm))
                                                 : NG::GridItemStyle::NONE;
        }
    }

    auto isLazy = runtimeCallInfo->GetCallArgRef(NUM_1)->BooleaValue(vm);
    if (isLazy) {
        Local<panda::FunctionRef> jsDeepRender = runtimeCallInfo->GetCallArgRef(NUM_0);
        std::function<void(int32_t)> gridItemDeepRenderFunc =
            [jsDeepRenderFunc = panda::CopyableGlobal(vm, jsDeepRender)](int32_t elmtId) {
                ACE_SCOPED_TRACE("JSGridItem::ExecuteDeepRender");
                ACE_DCHECK(componentsStack_.empty());
                auto vm = jsDeepRenderFunc.GetEcmaVM();
                panda::LocalScope scope(vm);
                panda::TryCatch trycatch(vm);
                Local<JSValueRef> jsParams[] = { ArkTSUtils::ToJsValueWithVM(vm, elmtId),
                    ArkTSUtils::ToJsValueWithVM(vm, true) };
                auto res = jsDeepRenderFunc->Call(vm, jsDeepRenderFunc.ToLocal(), jsParams, 2);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, res);
            };

        GetArkUINodeModifiers()->getGridItemModifier()->create(
            &gridItemDeepRenderFunc, isLazy, static_cast<ArkUI_Int32>(gridItemStyle));
        return;
    }
    GetArkUINodeModifiers()->getGridItemModifier()->createStyle(static_cast<ArkUI_Int32>(gridItemStyle));
}
} // namespace

ArkUINativeModuleValue GridItemBridge::SetGridItemSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> selectableArg = runtimeCallInfo->GetCallArgRef(NUM_1); // selectable value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (selectableArg->IsBoolean()) {
        bool selectable = selectableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemSelectable(nativeNode, selectable);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelectable(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelectable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(NUM_1); // selected value
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (selectedArg->IsBoolean()) {
        bool selected = selectedArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemSelected(nativeNode, selected);
    } else {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelected(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridItemBridge::ResetGridItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemRowStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowStartArg = runtimeCallInfo->GetCallArgRef(NUM_1); // rowStart value
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (rowStartArg->IsNumber()) {
        int32_t stars = rowStartArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemRowStart(nativeNode, stars);
    } else if (!ArkTSUtils::IsJsView(firstArg, vm)) {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowStart(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemRowStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemRowEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> rowEndArg = runtimeCallInfo->GetCallArgRef(NUM_1); // rowEnd value
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (rowEndArg->IsNumber()) {
        int32_t end = rowEndArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemRowEnd(nativeNode, end);
    } else if (!ArkTSUtils::IsJsView(firstArg, vm)) {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowEnd(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemRowEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemRowEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemColumnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnStartArg = runtimeCallInfo->GetCallArgRef(NUM_1); // columnStart value
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (columnStartArg->IsNumber()) {
        int32_t stars = columnStartArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemColumnStart(nativeNode, stars);
    } else if (!ArkTSUtils::IsJsView(firstArg, vm)) {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnStart(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemColumnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemColumnEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> columnEndArg = runtimeCallInfo->GetCallArgRef(NUM_1); // columnEnd value
    CHECK_EQUAL_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), false, panda::JSValueRef::Undefined(vm));
    if (columnEndArg->IsNumber()) {
        int32_t columnEnd = columnEndArg->Int32Value(vm);
        GetArkUINodeModifiers()->getGridItemModifier()->setGridItemColumnEnd(nativeNode, columnEnd);
    } else if (!ArkTSUtils::IsJsView(firstArg, vm)) {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnEnd(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemColumnEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemColumnEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetGridItemOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeVal = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> styleVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeVal->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeVal->ToNativePointer(vm)->Value());

    int32_t gridItemStyle = DEFAULT_GRIDITEM_STYLE;
    if (styleVal->IsNumber() && styleVal->Int32Value(vm) >= static_cast<int32_t>(GridItemStyle::NONE) &&
        styleVal->Int32Value(vm) <= static_cast<int32_t>(GridItemStyle::PLAIN)) {
        gridItemStyle = styleVal->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getGridItemModifier()->setGridItemOptions(nativeNode, gridItemStyle);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridItemBridge::SetGridItemOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemOnSelect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool isSelected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, isSelected) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getGridItemModifier()->setGridItemOnSelect(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::ResetGridItemOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridItemModifier()->resetGridItemOnSelect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::CreateGridItem(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    if (Container::IsCurrentUsePartialUpdate()) {
        CreateForPartialUpdate(vm, runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getGridItemModifier()->createStyle(static_cast<ArkUI_Int32>(NG::GridItemStyle::NONE));
    return panda::JSValueRef::Undefined(vm);
}

void GridItemBridge::RegisterGridItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setGridItemSelectable",
        "resetGridItemSelectable",
        "setGridItemSelected",
        "resetGridItemSelected",
        "setGridItemRowStart",
        "resetGridItemRowStart",
        "setGridItemRowEnd",
        "resetGridItemRowEnd",
        "setGridItemColumnStart",
        "resetGridItemColumnStart",
        "setGridItemColumnEnd",
        "resetGridItemColumnEnd",
        "setGridItemOptions",
        "setGridItemOnSelected",
        "resetGridItemOnSelected",
        "setForceRebuild",
        "setJSSelectable",
        "setJSOnSelect",
        "setJSWidth",
        "setJSHeight",
        "setJSSelected",
        "setBindContextMenu",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(vm, GridItemBridge::CreateGridItem),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemSelectable),
        panda::FunctionRef::New(vm, GridItemBridge::ResetGridItemSelectable),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemSelected),
        panda::FunctionRef::New(vm, GridItemBridge::ResetGridItemSelected),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemRowStart),
        panda::FunctionRef::New(vm, GridItemBridge::ResetGridItemRowStart),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemRowEnd),
        panda::FunctionRef::New(vm, GridItemBridge::ResetGridItemRowEnd),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemColumnStart),
        panda::FunctionRef::New(vm, GridItemBridge::ResetGridItemColumnStart),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemColumnEnd),
        panda::FunctionRef::New(vm, GridItemBridge::ResetGridItemColumnEnd),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemOptions),
        panda::FunctionRef::New(vm, GridItemBridge::SetGridItemOnSelected),
        panda::FunctionRef::New(vm, GridItemBridge::ResetGridItemOnSelected),
        panda::FunctionRef::New(vm, GridItemBridge::SetForceRebuild),
        panda::FunctionRef::New(vm, GridItemBridge::SetJSSelectable),
        panda::FunctionRef::New(vm, GridItemBridge::SetJSOnSelect),
        panda::FunctionRef::New(vm, GridItemBridge::SetJSWidth),
        panda::FunctionRef::New(vm, GridItemBridge::SetJSHeight),
        panda::FunctionRef::New(vm, GridItemBridge::SetJSSelected),
        panda::FunctionRef::New(vm, GridItemBridge::SetBindContextMenu),
    };
    auto gridItem = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridItem"), gridItem);
}

ArkUINativeModuleValue GridItemBridge::SetForceRebuild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> forceRebuildArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    GetArkUINodeModifiers()->getGridItemModifier()->setForceRebuild(
        nullptr, static_cast<ArkUI_Bool>(forceRebuildArg->Uint32Value(vm)));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetJSSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(
        runtimeCallInfo->GetArgsNumber() < 2, true, panda::JSValueRef::Undefined(vm)); // 2: parameter number
    Local<JSValueRef> selectableArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    bool selectable = true;
    if (!selectableArg.IsEmpty() && selectableArg->IsBoolean()) {
        selectable = selectableArg->BooleaValue(vm);
    }
    GetArkUINodeModifiers()->getGridItemModifier()->setGridItemSelectable(nullptr, selectable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetJSOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (callbackArg.IsEmpty() || !callbackArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    FrameNode* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [weakNode = AceType::WeakClaim(frameNode),
                                             func = panda::CopyableGlobal(vm, func)](bool isSelected) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, isSelected) };
        auto res = func->Call(vm, func.ToLocal(), params, NUM_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, res);
    };
    GetArkUINodeModifiers()->getGridItemModifier()->setGridItemOnSelect(nullptr, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetJSWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(
        runtimeCallInfo->GetArgsNumber() < 2, true, panda::JSValueRef::Undefined(vm)); // 2: parameter number
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!ArkTSUtils::SetJSWidth(widthArg)) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetJSHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(
        runtimeCallInfo->GetArgsNumber() < 2, true, panda::JSValueRef::Undefined(vm)); // 2: parameter number
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!ArkTSUtils::SetJSHeight(heightArg)) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetJSSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(
        runtimeCallInfo->GetArgsNumber() < 2, true, panda::JSValueRef::Undefined(vm)); // 2: parameter number

    bool select = false;
    Local<panda::ObjectRef> changeEventVal;
    auto selectedVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!selectedVal.IsEmpty() && selectedVal->IsObject(vm)) {
        auto obj = selectedVal->ToObject(vm);
        selectedVal = ArkTSUtils::GetProperty(vm, obj, "value");
        changeEventVal = ArkTSUtils::GetProperty(vm, obj, "$value");
    } else if (runtimeCallInfo->GetArgsNumber() > 2) {      // 2: parameter number
        changeEventVal = runtimeCallInfo->GetCallArgRef(2); // 2: parameter number
    }
    if (!selectedVal.IsEmpty() && selectedVal->IsBoolean()) {
        select = selectedVal->BooleaValue(vm);
    }
    GetArkUINodeModifiers()->getGridItemModifier()->setGridItemSelected(nullptr, select);

    if (!changeEventVal.IsEmpty() && changeEventVal->IsFunction(vm)) {
        Local<panda::FunctionRef> jsFunc = changeEventVal->ToObject(vm);
        auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        std::function<void(bool)> changeEvent = [func = panda::CopyableGlobal(vm, jsFunc),
                                                    node = AceType::WeakClaim(targetNode)](bool param) {
            auto vm = func.GetEcmaVM();
            CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
            ACE_SCORING_EVENT("GridItem.ChangeEvent");
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto newJSVal = ArkTSUtils::ToJsValueWithVM(vm, param);
            PipelineContext::SetCallBackNode(node);
            auto res = func->Call(vm, func.ToLocal(), &newJSVal, 1);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, res);
        };
        GetArkUINodeModifiers()->getGridItemModifier()->setSelectChangeEvent(nullptr, &changeEvent);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridItemBridge::SetBindContextMenu(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkTSUtils::SetJsBindContextMenu(runtimeCallInfo);
    GetArkUINodeModifiers()->getGridItemModifier()->bindContextMenu(nullptr);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
