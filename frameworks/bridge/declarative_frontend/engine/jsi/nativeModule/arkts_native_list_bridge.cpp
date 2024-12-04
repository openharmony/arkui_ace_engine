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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_list_bridge.h"

#include "core/interfaces/native/node/node_api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/list/list_theme.h"
#include "frameworks/core/components_ng/pattern/list/list_model.h"
#include "frameworks/core/components_ng/pattern/list/list_model_ng.h"
#include "frameworks/core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "frameworks/core/components_ng/base/view_stack_model.h"
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
constexpr int32_t LIST_ARG_INDEX_0 = 0;
constexpr int32_t LIST_ARG_INDEX_1 = 1;
constexpr int32_t LIST_ARG_INDEX_2 = 2;
constexpr int32_t LIST_ARG_INDEX_3 = 3;
constexpr int32_t LIST_ARG_INDEX_4 = 4;
constexpr int32_t LIST_ARG_INDEX_5 = 5;
constexpr int32_t LIST_ARG_INDEX_6 = 6;
constexpr int32_t LIST_ARG_INDEX_7 = 7;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;

constexpr int32_t ARG_LENGTH = 3;

ArkUINativeModuleValue ListBridge::SetListLanes(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0); // 0: index of parameter frameNode
    Local<JSValueRef> laneNumArg = runtimeCallInfo->GetCallArgRef(1);   // 1: index of parameter laneNum
    Local<JSValueRef> minLengthArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of parameter minLength
    Local<JSValueRef> maxLengthArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of parameter maxLength
    Local<JSValueRef> gutterArg = runtimeCallInfo->GetCallArgRef(4);    // 4: index of parameter gutter
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    ArkUIDimensionType gutterType;
    ArkUIDimensionType minLengthType;
    ArkUIDimensionType maxLengthType;

    CalcDimension gutter = Dimension(0.0);
    int32_t laneNum = 1;
    CalcDimension minLength = -1.0_vp;
    CalcDimension maxLength = -1.0_vp;
    if (!gutterArg->IsUndefined() && ArkTSUtils::ParseJsDimensionVp(vm, gutterArg, gutter)) {
        if (gutter.IsNegative()) {
            gutter.Reset();
        }
        gutterType.value = gutter.Value();
        gutterType.units = static_cast<int32_t>(gutter.Unit());
    }
    if (!laneNumArg->IsUndefined() && ArkTSUtils::ParseJsInteger(vm, laneNumArg, laneNum)) {
        minLengthType.value = minLength.Value();
        minLengthType.units = static_cast<int32_t>(minLength.Unit());
        maxLengthType.value = maxLength.Value();
        maxLengthType.units = static_cast<int32_t>(maxLength.Unit());
    }
    if (!minLengthArg->IsUndefined() && !maxLengthArg->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVp(vm, minLengthArg, minLength) &&
        ArkTSUtils::ParseJsDimensionVp(vm, maxLengthArg, maxLength)) {
        laneNum = -1;
        minLengthType.value = minLength.Value();
        minLengthType.units = static_cast<int32_t>(minLength.Unit());
        maxLengthType.value = maxLength.Value();
        maxLengthType.units = static_cast<int32_t>(maxLength.Unit());
    }
    GetArkUINodeModifiers()->getListModifier()->setListLanes(
        nativeNode, laneNum, &minLengthType, &maxLengthType, &gutterType);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListLanes(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListLanes(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ListBridge::SetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->resetEditMode(nativeNode);
    } else {
        bool editMode = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getListModifier()->setEditMode(nativeNode, editMode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetEditMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetEditMode(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->resetMultiSelectable(nativeNode);
    } else {
        bool selectable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getListModifier()->setMultiSelectable(nativeNode, selectable);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetMultiSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetMultiSelectable(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetChainAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool chainAnimation = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getListModifier()->setChainAnimation(nativeNode, chainAnimation);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetChainAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetChainAnimation(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> cacheCountArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    Local<JSValueRef> cacheShowArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_2);

    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    auto cacheCount = DEFAULT_CACHED_COUNT;
    if (!cacheCountArg->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, cacheCountArg, cacheCount);
        if (cacheCount < 0) {
            cacheCount = DEFAULT_CACHED_COUNT;
        }
    }
    GetArkUINodeModifiers()->getListModifier()->setCachedCount(nativeNode, cacheCount);

    bool show = !cacheShowArg.IsNull() && cacheShowArg->IsTrue();
    GetArkUINodeModifiers()->getListModifier()->setShowCached(nativeNode, show);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetCachedCount(nativeNode);
    GetArkUINodeModifiers()->getListModifier()->resetShowCached(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enableScrollInteraction = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getListModifier()->setEnableScrollInteraction(nativeNode, enableScrollInteraction);
    } else {
        GetArkUINodeModifiers()->getListModifier()->resetEnableScrollInteraction(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetEnableScrollInteraction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetEnableScrollInteraction(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetSticky(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->resetSticky(nativeNode);
    } else {
        int32_t stickyStyle = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getListModifier()->setSticky(nativeNode, stickyStyle);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetSticky(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetSticky(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->resetListDirection(nativeNode);
    } else {
        int32_t direction = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getListModifier()->setListDirection(nativeNode, direction);
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ListBridge::ResetListDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListDirection(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);

    double friction = -1.0;
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined() || secondArg->IsNull() || !ArkTSUtils::ParseJsDouble(vm, secondArg, friction)) {
        friction = -1.0;
    }
    GetArkUINodeModifiers()->getListModifier()->setListFriction(nativeNode, friction);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListMaintainVisibleContentPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        bool enabled = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getListModifier()->setListMaintainVisibleContentPosition(nativeNode, enabled);
    } else {
        GetArkUINodeModifiers()->getListModifier()->resetListMaintainVisibleContentPosition(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListMaintainVisibleContentPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListMaintainVisibleContentPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_2);

    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t forward = 0;
    int32_t backward = 0;
    if (!secondArg->IsUndefined()) {
        forward = secondArg->Int32Value(vm);
    }
    if (!thirdArg->IsUndefined()) {
        backward = thirdArg->Int32Value(vm);
    }

    if (forward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        forward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        forward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    }

    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    }

    GetArkUINodeModifiers()->getListModifier()->setListNestedScroll(nativeNode, forward, backward);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->resetListScrollBar(nativeNode);
    } else {
        int32_t barState = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getListModifier()->setListScrollBar(nativeNode, barState);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListScrollBar(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimension(vm, scrollBarArg, scrollBarWidth, DimensionUnit::VP) || scrollBarArg->IsNull() ||
        scrollBarArg->IsUndefined() || (scrollBarArg->IsString(vm) && scrollBarWidth.ToString().empty()) ||
        LessNotEqual(scrollBarWidth.Value(), 0.0) || scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        GetArkUINodeModifiers()->getListModifier()->resetListScrollBarWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getListModifier()->setListScrollBarWidth(
            nativeNode, scrollBarWidth.ToString().c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListScrollBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> argColor = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    std::string color = "";
    if (!ArkTSUtils::ParseJsString(vm, argColor, color) || argColor->IsUndefined() || color.empty()) {
        GetArkUINodeModifiers()->getListModifier()->resetListScrollBarColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getListModifier()->setListScrollBarColor(nativeNode, color.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetFlingSpeedLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> argSpeed = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    double limitSpeed = -1.0;
    if (!ArkTSUtils::ParseJsDouble(vm, argSpeed, limitSpeed)) {
        GetArkUINodeModifiers()->getListModifier()->resetListFlingSpeedLimit(nativeNode);
    } else {
        GetArkUINodeModifiers()->getListModifier()->setListFlingSpeedLimit(
            nativeNode, static_cast<ArkUI_Float32>(limitSpeed));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetFlingSpeedLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> argNode = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(argNode->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListFlingSpeedLimit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetAlignListItem(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t listItemAlign = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getListModifier()->setAlignListItem(nativeNode, listItemAlign);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetAlignListItem(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetAlignListItem(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetScrollSnapAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->resetScrollSnapAlign(nativeNode);
    } else {
        int32_t scrollSnapAlign = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getListModifier()->setScrollSnapAlign(nativeNode, scrollSnapAlign);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetScrollSnapAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetScrollSnapAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetContentStartOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> startOffsetArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    double startOffset = 0.0;
    ArkTSUtils::ParseJsDouble(vm, startOffsetArg, startOffset);

    GetArkUINodeModifiers()->getListModifier()->setContentStartOffset(nativeNode, startOffset);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetContentStartOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetContentStartOffset(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetContentEndOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> endOffsetArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    double endOffset = 0.0;
    ArkTSUtils::ParseJsDouble(vm, endOffsetArg, endOffset);

    GetArkUINodeModifiers()->getListModifier()->setContentEndOffset(nativeNode, endOffset);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetContentEndOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(frameNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetContentEndOffset(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_2);
    Local<JSValueRef> dividerStartMarginArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_3);
    Local<JSValueRef> dividerEndMarginArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_4);
    if (dividerStrokeWidthArgs->IsUndefined() && dividerStartMarginArgs->IsUndefined() &&
        dividerEndMarginArgs->IsUndefined() && colorArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->listResetDivider(nativeNode);
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
    auto listTheme = themeManager->GetTheme<ListTheme>();
    CHECK_NULL_RETURN(listTheme, panda::NativePointerRef::New(vm, nullptr));

    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, dividerStrokeWidthArgs, dividerStrokeWidth) ||
        LessNotEqual(dividerStrokeWidth.Value(), 0.0f) || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
        dividerStrokeWidth.Reset();
    }
    Color colorObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj)) {
        color = listTheme->GetDividerColor().GetValue();
    } else {
        color = colorObj.GetValue();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerStartMarginArgs, dividerStartMargin) ||
        LessNotEqual(dividerStartMargin.Value(), 0.0f) || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
        dividerStartMargin.Reset();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerEndMarginArgs, dividerEndMargin) ||
        LessNotEqual(dividerEndMargin.Value(), 0.0f) || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
        dividerEndMargin.Reset();
    }
    uint32_t size = ARG_LENGTH;
    ArkUI_Float32 values[size];
    int32_t units[size];
    values[LIST_ARG_INDEX_0] = static_cast<ArkUI_Float32>(dividerStrokeWidth.Value());
    values[LIST_ARG_INDEX_1] = static_cast<ArkUI_Float32>(dividerStartMargin.Value());
    values[LIST_ARG_INDEX_2] = static_cast<ArkUI_Float32>(dividerEndMargin.Value());
    units[LIST_ARG_INDEX_0] = static_cast<int32_t>(dividerStrokeWidth.Unit());
    units[LIST_ARG_INDEX_1] = static_cast<int32_t>(dividerStartMargin.Unit());
    units[LIST_ARG_INDEX_2] = static_cast<int32_t>(dividerEndMargin.Unit());
    GetArkUINodeModifiers()->getListModifier()->listSetDivider(nativeNode, color, values, units, size);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->listResetDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetChainAnimationOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    Local<JSValueRef> minSpaceArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_1);
    Local<JSValueRef> maxSpaceArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_2);
    Local<JSValueRef> conductivityArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_3);
    Local<JSValueRef> intensityArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_4);
    Local<JSValueRef> edgeEffectArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_5);
    Local<JSValueRef> stiffnessArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_6);
    Local<JSValueRef> dampingArgs = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_7);

    CalcDimension minSpace;
    CalcDimension maxSpace;

    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (minSpaceArgs->IsUndefined() && maxSpaceArgs->IsUndefined() && conductivityArgs->IsUndefined() &&
        intensityArgs->IsUndefined() && edgeEffectArgs->IsUndefined() && stiffnessArgs->IsUndefined() &&
        dampingArgs->IsUndefined()) {
        GetArkUINodeModifiers()->getListModifier()->resetChainAnimationOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        RefPtr<ListTheme> listTheme = ArkTSUtils::GetTheme<ListTheme>();
        CHECK_NULL_RETURN(listTheme, panda::NativePointerRef::New(vm, nullptr));

        minSpace = listTheme->GetChainMinSpace();
        maxSpace = listTheme->GetChainMaxSpace();
        ArkUIChainAnimationOptionsType chainAnimationOptions;

        double conductivity;
        double intensity;

        chainAnimationOptions.conductivity = listTheme->GetChainConductivity();
        chainAnimationOptions.intensity = listTheme->GetChainIntensity();
        chainAnimationOptions.edgeEffect = 0;
        chainAnimationOptions.stiffness = listTheme->GetChainStiffness();
        chainAnimationOptions.damping = listTheme->GetChainDamping();

        ArkTSUtils::ParseJsDimension(vm, minSpaceArgs, minSpace, DimensionUnit::VP);
        ArkTSUtils::ParseJsDimension(vm, maxSpaceArgs, maxSpace, DimensionUnit::VP);
        ArkTSUtils::ParseJsDouble(vm, conductivityArgs, conductivity);
        chainAnimationOptions.conductivity = static_cast<ArkUI_Float32>(conductivity);

        ArkTSUtils::ParseJsDouble(vm, intensityArgs, intensity);
        chainAnimationOptions.intensity = static_cast<ArkUI_Float32>(intensity);

        if (edgeEffectArgs->IsNumber()) {
            chainAnimationOptions.edgeEffect = edgeEffectArgs->ToNumber(vm)->Value();
        }
        
        double stiffness;
        double damping;

        ArkTSUtils::ParseJsDouble(vm, stiffnessArgs, stiffness);
        chainAnimationOptions.stiffness = static_cast<ArkUI_Float32>(stiffness);

        ArkTSUtils::ParseJsDouble(vm, dampingArgs, damping);
        chainAnimationOptions.damping = static_cast<ArkUI_Float32>(damping);

        chainAnimationOptions.minSpace = minSpace.Value();
        chainAnimationOptions.minSpaceUnits = static_cast<int32_t>(minSpace.Unit());
        chainAnimationOptions.maxSpace = maxSpace.Value();
        chainAnimationOptions.maxSpaceUnits = static_cast<int32_t>(maxSpace.Unit());

        GetArkUINodeModifiers()->getListModifier()->setChainAnimationOptions(nativeNode, &chainAnimationOptions);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetChainAnimationOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetChainAnimationOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetListChildrenMainSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    // 2: argument count.
    if (info.Length() != 2 || !(info[1]->IsObject())) {
        return panda::JSValueRef::Undefined(vm);
    }
    JSList::SetChildrenMainSize(Framework::JSRef<Framework::JSObject>::Cast(info[1]));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetListChildrenMainSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(LIST_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListChildrenMainSize(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetInitialIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    int32_t index = secondArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getListModifier()->setInitialIndex(nativeNode, index);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetInitialIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetInitialIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    float space = secondArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getListModifier()->setListSpace(nativeNode, space);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetListSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetInitialScroller(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSRef<Framework::JSVal> args = info[1];
    if (args->IsObject()) {
        Framework::JSScroller* scroller =
            Framework::JSRef<Framework::JSObject>::Cast(args)->Unwrap<Framework::JSScroller>();
        RefPtr<Framework::JSScroller> jsScroller = Referenced::Claim(scroller);
        jsScroller->SetInstanceId(Container::CurrentId());
        SetScroller(runtimeCallInfo, jsScroller);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetInitialScroller(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetInitialScroller(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ListBridge::SetScroller(ArkUIRuntimeCallInfo* runtimeCallInfo, RefPtr<Framework::JSScroller> jsScroller)
{
    if (jsScroller) {
        EcmaVM* vm = runtimeCallInfo->GetVM();
        Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
        auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        RefPtr<ScrollControllerBase> listController = ListModel::GetInstance()->CreateScrollController();
        jsScroller->SetController(listController);
        auto proxy = jsScroller->GetScrollBarProxy();
        if (!proxy) {
            proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
            jsScroller->SetScrollBarProxy(proxy);
        }
        auto controller = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(listController));
        auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(proxy));
        GetArkUINodeModifiers()->getListModifier()->setInitialScroller(nativeNode, controller, proxyPtr);
    }
}

ArkUINativeModuleValue ListBridge::SetOnScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListScrollIndex(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int32_t, int32_t, int32_t)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           const int32_t start, const int32_t end,
                                                           const int32_t center) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, start);
        panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, end);
        panda::Local<panda::NumberRef> centerParam = panda::NumberRef::New(vm, center);
        // 3: Array length
        panda::Local<panda::JSValueRef> params[3] = { startParam, endParam, centerParam };
        func->Call(vm, func.ToLocal(), params, 3); // 3: Array length
    };
    GetArkUINodeModifiers()->getListModifier()->setOnListScrollIndexCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> SetListItemIndex(const EcmaVM* vm, const ListItemIndex indexInfo)
{
    const char* keys[] = { "index", "itemIndexInGroup", "itemGroupArea" };
    auto indexInGroup = panda::NumberRef::Undefined(vm);
    if (indexInfo.indexInGroup != -1) {
        indexInGroup = panda::NumberRef::New(vm, static_cast<int32_t>(indexInfo.indexInGroup));
    }
    auto area = panda::NumberRef::Undefined(vm);
    if (indexInfo.area != -1) {
        area = panda::NumberRef::New(vm, static_cast<int32_t>(indexInfo.area));
    }
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(indexInfo.index)), indexInGroup,
        area };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

ArkUINativeModuleValue ListBridge::SetOnScrollVisibleContentChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnScrollVisibleContentChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(ListItemIndex, ListItemIndex)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const ListItemIndex start, const ListItemIndex end) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        auto startParam = SetListItemIndex(vm, start);
        auto endParam = SetListItemIndex(vm, end);
        startParam->SetNativePointerFieldCount(vm, 1);
        startParam->SetNativePointerField(vm, 0, static_cast<void*>(&startParam));
        endParam->SetNativePointerFieldCount(vm, 1);
        endParam->SetNativePointerField(vm, 0, static_cast<void*>(&endParam));
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { startParam, endParam };
        func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
    };
    GetArkUINodeModifiers()->getListModifier()->setOnScrollVisibleContentChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnItemMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnItemMove(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<bool(int32_t, int32_t)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                         int32_t start, int32_t end) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, start);
        panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, end);
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { startParam, endParam};
        auto result =  func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (result->IsBoolean()) {
            return result->ToBoolean(vm)->Value();
        }
        return false;
    };
    GetArkUINodeModifiers()->getListModifier()->setOnItemMove(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnItemDragStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsFunction()) {
        return panda::JSValueRef::Undefined(vm);
    }

    RefPtr<JsDragFunction> jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[1]));
    std::function<RefPtr<AceType>(const ItemDragInfo&, int32_t)> callback =
        [vm, frameNode, func = std::move(jsOnDragFunc), execCtx = info.GetExecutionContext()](
            const ItemDragInfo& dragInfo, int32_t itemIndex) -> RefPtr<AceType> {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);

        auto ret = func->ItemDragStartExecute(dragInfo, itemIndex);
        if (!ret->IsFunction()) {
            return nullptr;
        }

        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(ret));
        if (!builderFunc) {
            return nullptr;
        }
        // use another VSP instance while executing the builder function
        ViewStackModel::GetInstance()->NewScope();
        {
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            builderFunc->Execute();
        }
        return ViewStackModel::GetInstance()->Finish();
    };
    GetArkUINodeModifiers()->getListModifier()->setOnItemDragStart(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnItemDragEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsFunction()) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[1]));

    std::function<void(const ItemDragInfo&)> callback = [vm, frameNode, func = std::move(jsOnDragFunc),
                                                      execCtx = info.GetExecutionContext()](
                                                      const ItemDragInfo& dragInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->ItemDragEnterExecute(dragInfo);
    };
    GetArkUINodeModifiers()->getListModifier()->setOnItemDragEnter(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnItemDragMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsFunction()) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[1]));

    std::function<void(const ItemDragInfo&, int32_t, int32_t)> callback =
        [vm, frameNode, func = std::move(jsOnDragFunc), execCtx = info.GetExecutionContext()](
            const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);

            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            func->ItemDragMoveExecute(dragInfo, itemIndex, insertIndex);
        };
    GetArkUINodeModifiers()->getListModifier()->setOnItemDragMove(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnItemDragLeave(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsFunction()) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[1]));

    std::function<void(const ItemDragInfo&, int32_t)> callback = [vm, frameNode, func = std::move(jsOnDragFunc)](
                               const ItemDragInfo& dragInfo, int32_t itemIndex) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->ItemDragLeaveExecute(dragInfo, itemIndex);
    };
    GetArkUINodeModifiers()->getListModifier()->setOnItemDragLeave(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnItemDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsFunction()) {
        return panda::JSValueRef::Undefined(vm);
    }
    RefPtr<JsDragFunction> jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[1]));

    std::function<void(const ItemDragInfo&, int32_t, int32_t, bool)> callback =
        [vm, frameNode, func = std::move(jsOnDragFunc)](
            const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);

            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            func->ItemDropExecute(dragInfo, itemIndex, insertIndex, isSuccess);
        };
    GetArkUINodeModifiers()->getListModifier()->setOnItemDrop(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnListScrollStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListScrollStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getListModifier()->setOnListScrollStartCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnListScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListScrollStop(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getListModifier()->setOnListScrollStopCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnListScrollFrameBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListScrollFrameBegin(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<ScrollFrameResult(Dimension, ScrollState)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](Dimension offset, ScrollState state) -> ScrollFrameResult {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> offsetParam = panda::NumberRef::New(
            vm, static_cast<double>(offset.ConvertToVp()));
        panda::Local<panda::NumberRef> stateParam = panda::NumberRef::New(vm, static_cast<double>(state));
         // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { offsetParam, stateParam };
        auto value = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length

        OHOS::Ace::ScrollFrameResult scrollRes { .offset = offset };
        if (value->IsNumber()) {
            scrollRes.offset = Dimension(value->ToNumber(vm)->Value(), DimensionUnit::VP);
        }
        if (value->IsObject(vm)) {
            auto resultObj = value->ToObject(vm);
            panda::Local<panda::JSValueRef> remain = resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm,
                "offsetRemain"));
            if (remain->IsNumber()) {
                scrollRes.offset = Dimension(remain->ToNumber(vm)->Value(), DimensionUnit::VP);
            }
        }
        return scrollRes;
    };
    GetArkUINodeModifiers()->getListModifier()->setOnListScrollFrameBeginCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnListWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListWillScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<ScrollFrameResult(CalcDimension, ScrollState, ScrollSource)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
            const CalcDimension& scrollOffset, const ScrollState& scrollState, ScrollSource scrollSource) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> offsetParam = panda::NumberRef::New(
            vm, static_cast<double>(scrollOffset.ConvertToVp()));
        panda::Local<panda::NumberRef> stateParam = panda::NumberRef::New(vm, static_cast<int32_t>(scrollState));
        panda::Local<panda::NumberRef> sourceParam = panda::NumberRef::New(vm, static_cast<int32_t>(scrollSource));
        // 3: Array length
        panda::Local<panda::JSValueRef> params[3] = { offsetParam, stateParam, sourceParam };
        auto result = func->Call(vm, func.ToLocal(), params, 3); // 4: Array length
        ScrollFrameResult scrollRes { .offset = scrollOffset };

        if (result->IsObject(vm)) {
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> dxRemainValue =
                    resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "offsetRemain"));
            if (dxRemainValue->IsNumber()) {
                scrollRes.offset = Dimension(dxRemainValue->ToNumber(vm)->Value(), DimensionUnit::VP);
            }
        }
        return scrollRes;
    };
    GetArkUINodeModifiers()->getListModifier()->setOnListWillScrollCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnListDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListDidScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(Dimension, ScrollState)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                            const CalcDimension& scrollOffset, const ScrollState& scrollState) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> offsetParam =
            panda::NumberRef::New(vm, static_cast<double>(scrollOffset.ConvertToVp()));
        panda::Local<panda::NumberRef> stateParam = panda::NumberRef::New(vm, static_cast<int32_t>(scrollState));
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { offsetParam, stateParam };
        func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
    };
    GetArkUINodeModifiers()->getListModifier()->setOnListDidScrollCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnListReachStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListReachStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };

    GetArkUINodeModifiers()->getListModifier()->setOnListReachStartCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::SetOnListReachEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListModifier()->resetOnListReachEnd(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };

    GetArkUINodeModifiers()->getListModifier()->setOnListReachEndCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnScrollIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListScrollIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnScrollVisibleContentChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnScrollVisibleContentChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnItemMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnItemMove(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnItemDragStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnItemDragStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnItemDragEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnItemDragEnter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnItemDragMove(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnItemDragMove(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnItemDragLeave(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnItemDragLeave(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnItemDrop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnItemDrop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnListScrollStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListScrollStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnListScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListScrollStop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnListScrollFrameBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListScrollFrameBegin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnListWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListWillScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnListDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListDidScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnListReachStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListReachStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListBridge::ResetOnListReachEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListModifier()->resetOnListReachEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG