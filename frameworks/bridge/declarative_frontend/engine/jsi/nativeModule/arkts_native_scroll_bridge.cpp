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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scroll_bridge.h"

#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/interfaces/native/node/api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr double FRICTION_DEFAULT = 0.6;
constexpr int32_t CALLARGS_INDEX_0 = 0;
constexpr int32_t CALLARGS_INDEX_1 = 1;
constexpr int32_t CALLARGS_INDEX_2 = 2;
constexpr int32_t CALLARGS_INDEX_3 = 3;
constexpr int32_t CALLARGS_INDEX_4 = 4;
constexpr int32_t FROWARD_INITIAL_VALUE = 0;
constexpr int32_t BACKWARD_INITIAL_VALUE = 0;

bool ParsePagination(const EcmaVM* vm, const Local<JSValueRef>& paginationValue, std::vector<double>& vPaginationValue,
    std::vector<int32_t>& vPaginationUnit)
{
    int32_t pLength = 0;
    if (paginationValue->IsArray(vm)) {
        auto paginationArray = panda::Local<panda::ArrayRef>(paginationValue);
        pLength = paginationArray->Length(vm);
        if (pLength <= 0) {
            return false;
        }
        for (int32_t i = 0; i < pLength; i++) {
            CalcDimension dims;
            Local<JSValueRef> xValue = panda::ArrayRef::GetValueAt(vm, paginationArray, i);
            if (!ArkTSUtils::ParseJsDimensionVpNG(vm, xValue, dims, true)) {
                return false;
            }
            vPaginationValue.push_back(dims.Value());
            vPaginationUnit.push_back(static_cast<int32_t>(dims.Unit()));
        }
    } else {
        CalcDimension intervalSize;
        if (!ArkTSUtils::ParseJsDimensionVp(vm, paginationValue, intervalSize) || intervalSize.IsNegative()) {
            intervalSize = CalcDimension(0.0);
        }
        vPaginationValue.push_back(intervalSize.Value());
        vPaginationUnit.push_back(static_cast<int32_t>(intervalSize.Unit()));
    }

    return true;
}

ArkUINativeModuleValue ScrollBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> scrollForwardValue = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    Local<JSValueRef> scrollBackwardValue = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_2);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    auto froward = 0;
    auto backward = 0;
    ArkTSUtils::ParseJsInteger(vm, scrollForwardValue, froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        froward = FROWARD_INITIAL_VALUE;
    }
    ArkTSUtils::ParseJsInteger(vm, scrollBackwardValue, backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = BACKWARD_INITIAL_VALUE;
    }
    GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollNestedScroll(nativeNode, froward, backward);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> isEnabledArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    bool isEnabled = isEnabledArg->IsBoolean() ? isEnabledArg->ToBoolean(vm)->Value() : true;
    GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollEnableScroll(nativeNode, isEnabled);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollEnableScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> scrollFrictionArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    double friction = FRICTION_DEFAULT;
    if (!ArkTSUtils::ParseJsDouble(vm, scrollFrictionArg, friction)) {
        GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollFriction(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollFriction(nativeNode, friction);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollFriction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollSnap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> snapAlignValue = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    Local<JSValueRef> paginationValue = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_2);
    Local<JSValueRef> enableSnapToStartValue = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_3);
    Local<JSValueRef> enableSnapToEndValue = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_4);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    auto snapAlign = static_cast<int32_t>(ScrollSnapAlign::NONE);
    if (snapAlignValue->IsNull() || snapAlignValue->IsUndefined() ||
        !ArkTSUtils::ParseJsInteger(vm, snapAlignValue, snapAlign) ||
        snapAlign < static_cast<int32_t>(ScrollSnapAlign::NONE) ||
        snapAlign > static_cast<int32_t>(ScrollSnapAlign::END)) {
        snapAlign = static_cast<int32_t>(ScrollSnapAlign::NONE);
    }
    std::vector<double> vPaginationValue;
    std::vector<int32_t> vPaginationUnit;
    if (!ParsePagination(vm, paginationValue, vPaginationValue, vPaginationUnit)) {
        GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollSnap(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isArray = true;
    if (!paginationValue->IsArray(vm)) {
        isArray = false;
    }
    int32_t pLength = vPaginationValue.size();
    vPaginationUnit.push_back(snapAlign);
    vPaginationUnit.push_back(static_cast<int32_t>(enableSnapToStartValue->ToBoolean(vm)->Value()));
    vPaginationUnit.push_back(static_cast<int32_t>(enableSnapToEndValue->ToBoolean(vm)->Value()));
    vPaginationUnit.push_back(static_cast<int32_t>(isArray));
    auto uLength = pLength + 4;
    GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollScrollSnap(
        nativeNode, vPaginationValue.data(), pLength, vPaginationUnit.data(), uLength);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollSnap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollSnap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    auto value = static_cast<int32_t>(DisplayMode::AUTO);
    if (!jsValue->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, jsValue, value);
    }
    GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollScrollBar(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> scrollDirectionArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    if (scrollDirectionArg->IsUndefined() || scrollDirectionArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollable(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    int32_t scrollDirection = scrollDirectionArg->Int32Value(vm);
    if (scrollDirection != static_cast<int32_t>(Axis::VERTICAL) &&
        scrollDirection != static_cast<int32_t>(Axis::HORIZONTAL) &&
        scrollDirection != static_cast<int32_t>(Axis::FREE) && scrollDirection != static_cast<int32_t>(Axis::NONE)) {
        GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollable(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollScrollable(nativeNode, scrollDirection);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> barcolorArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, barcolorArg, color)) {
        GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollBarColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollScrollBarColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, scrollBarArg, scrollBarWidth, false)) {
        GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollBarWidth(nativeNode);
    } else {
        if (LessNotEqual(scrollBarWidth.Value(), 0.0)) {
            GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollBarWidth(nativeNode);
        } else {
            GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollScrollBarWidth(
                nativeNode, scrollBarWidth.Value(), static_cast<int32_t>(scrollBarWidth.Unit()));
        }
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollScrollBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    Local<JSValueRef> effectArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_1);
    Local<JSValueRef> isEffectArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_2);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    int32_t effect = static_cast<int32_t>(EdgeEffect::NONE);
    if (!effectArg->IsUndefined() && !effectArg->IsNull()) {
        effect = effectArg->Int32Value(vm);
    }

    if (effect != static_cast<int32_t>(EdgeEffect::SPRING) && effect != static_cast<int32_t>(EdgeEffect::NONE) &&
        effect != static_cast<int32_t>(EdgeEffect::FADE)) {
        effect = static_cast<int32_t>(EdgeEffect::NONE);
    }

    if (isEffectArg->IsUndefined() || isEffectArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollEdgeEffect(nativeNode, effect, true);
    } else {
        GetArkUIInternalNodeAPI()->GetScrollModifier().SetScrollEdgeEffect(
            nativeNode, effect, isEffectArg->ToBoolean(vm)->Value());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALLARGS_INDEX_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetScrollModifier().ResetScrollEdgeEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
