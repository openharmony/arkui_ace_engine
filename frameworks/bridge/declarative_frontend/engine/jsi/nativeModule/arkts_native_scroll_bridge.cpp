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
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "core/components_ng/pattern/scroll/scroll_model.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr double FRICTION_DEFAULT = 0.6;
constexpr int32_t FROWARD_INITIAL_VALUE = 0;
constexpr int32_t BACKWARD_INITIAL_VALUE = 0;

bool ParsePagination(const EcmaVM* vm, const Local<JSValueRef>& paginationValue,
    std::vector<ArkUI_Float32>& vPaginationValue,
    std::vector<int32_t>& vPaginationUnit)
{
    uint32_t pLength = 0;
    if (paginationValue->IsArray(vm)) {
        auto paginationArray = panda::Local<panda::ArrayRef>(paginationValue);
        pLength = paginationArray->Length(vm);
        if (pLength <= 0) {
            return false;
        }
        for (uint32_t i = 0; i < pLength; i++) {
            CalcDimension dims;
            Local<JSValueRef> xValue = panda::ArrayRef::GetValueAt(vm, paginationArray, i);
            if (!ArkTSUtils::ParseJsDimensionVpNG(vm, xValue, dims, true)) {
                return false;
            }
            vPaginationValue.push_back(static_cast<ArkUI_Float32>(dims.Value()));
            vPaginationUnit.push_back(static_cast<int32_t>(dims.Unit()));
        }
    } else {
        CalcDimension intervalSize;
        if (!ArkTSUtils::ParseJsDimensionVp(vm, paginationValue, intervalSize) || intervalSize.IsNegative()) {
            intervalSize = CalcDimension(0.0);
        }
        vPaginationValue.push_back(static_cast<ArkUI_Float32>(intervalSize.Value()));
        vPaginationUnit.push_back(static_cast<int32_t>(intervalSize.Unit()));
    }

    return true;
}

bool ParsePaginationNG(const EcmaVM* vm, const Local<JSValueRef>& paginationValue,
    std::vector<ArkUI_Float32>& vPaginationValue, std::vector<RefPtr<ResourceObject>>& resObjs,
    std::vector<int32_t>& vPaginationUnit)
{
    uint32_t pLength = 0;
    resObjs.clear();
    if (paginationValue->IsArray(vm)) {
        auto paginationArray = panda::Local<panda::ArrayRef>(paginationValue);
        pLength = paginationArray->Length(vm);
        if (pLength <= 0) {
            return false;
        }
        resObjs.resize(pLength);
        for (uint32_t i = 0; i < pLength; i++) {
            CalcDimension dims;
            Local<JSValueRef> xValue = panda::ArrayRef::GetValueAt(vm, paginationArray, i);
            if (!ArkTSUtils::ParseJsDimensionVpNG(vm, xValue, dims, resObjs[i], true)) {
                continue;
            }
            vPaginationValue.push_back(static_cast<ArkUI_Float32>(dims.Value()));
            vPaginationUnit.push_back(static_cast<int32_t>(dims.Unit()));
        }
    } else {
        CalcDimension intervalSize;
        resObjs.resize(1);
        if (!ArkTSUtils::ParseJsDimensionVp(vm, paginationValue, intervalSize, resObjs[0]) ||
            intervalSize.IsNegative()) {
            intervalSize = CalcDimension(0.0);
        }
        vPaginationValue.push_back(static_cast<ArkUI_Float32>(intervalSize.Value()));
        vPaginationUnit.push_back(static_cast<int32_t>(intervalSize.Unit()));
    }

    return true;
}

ArkUINativeModuleValue ScrollBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scrollForwardValue = runtimeCallInfo->GetCallArgRef(1);  // 1: index of scroll forward value
    Local<JSValueRef> scrollBackwardValue = runtimeCallInfo->GetCallArgRef(2); // 2: index of scroll backward value
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
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
    GetArkUINodeModifiers()->getScrollModifier()->setScrollNestedScroll(nativeNode, froward, backward);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> isEnabledArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    bool isEnabled = isEnabledArg->IsBoolean() ? isEnabledArg->ToBoolean(vm)->Value() : true;
    GetArkUINodeModifiers()->getScrollModifier()->setScrollEnableScroll(nativeNode, isEnabled);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetEnableScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollEnableScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scrollFrictionArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    double friction = FRICTION_DEFAULT;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDouble(vm, scrollFrictionArg, friction, resObj)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollFriction(nativeNode);
    } else {
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getScrollModifier()->createWithResourceObjFriction(
                nativeNode, reinterpret_cast<void*>(AceType::RawPtr(resObj)));
        }
        GetArkUINodeModifiers()->getScrollModifier()->setScrollFriction(
            nativeNode, static_cast<ArkUI_Float32>(friction));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetFriction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollFriction(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getScrollModifier()->createWithResourceObjFriction(nativeNode, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollSnap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> snapAlignValue = runtimeCallInfo->GetCallArgRef(1);         // 1: index of snap align value
    Local<JSValueRef> paginationValue = runtimeCallInfo->GetCallArgRef(2);        // 2: index of pagination value
    Local<JSValueRef> enableSnapToStartValue = runtimeCallInfo->GetCallArgRef(3); // 3: index of enableSnapToStart value
    Local<JSValueRef> enableSnapToEndValue = runtimeCallInfo->GetCallArgRef(4);   // 4: index of enableSnapToEnd value
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto snapAlign = static_cast<int32_t>(ScrollSnapAlign::NONE);
    if (snapAlignValue->IsNull() || snapAlignValue->IsUndefined() ||
        !ArkTSUtils::ParseJsInteger(vm, snapAlignValue, snapAlign) ||
        snapAlign < static_cast<int32_t>(ScrollSnapAlign::NONE) ||
        snapAlign > static_cast<int32_t>(ScrollSnapAlign::END)) {
        snapAlign = static_cast<int32_t>(ScrollSnapAlign::NONE);
    }
    std::vector<ArkUI_Float32> vPaginationValue;
    std::vector<int32_t> vPaginationUnit;
    std::vector<RefPtr<ResourceObject>> resObjs;
    auto parseOK = ParsePaginationNG(vm, paginationValue, vPaginationValue, resObjs, vPaginationUnit);
    bool isArray = true;
    if (!paginationValue->IsArray(vm)) {
        isArray = false;
    }
    auto pLength = vPaginationValue.size();
    vPaginationUnit.push_back(snapAlign);
    vPaginationUnit.push_back(static_cast<int32_t>(enableSnapToStartValue->ToBoolean(vm)->Value()));
    vPaginationUnit.push_back(static_cast<int32_t>(enableSnapToEndValue->ToBoolean(vm)->Value()));
    vPaginationUnit.push_back(static_cast<int32_t>(isArray));
    auto uLength = pLength + 4;

    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getScrollModifier()->createWithResourceObjSnap(
            nativeNode, vPaginationValue.data(), pLength, vPaginationUnit.data(), &resObjs);
    }
    if (!parseOK) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollSnap(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getScrollModifier()->setScrollScrollSnap(
        nativeNode, vPaginationValue.data(), pLength, vPaginationUnit.data(), uLength);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollSnap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollSnap(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getScrollModifier()->createWithResourceObjSnap(
            nativeNode, nullptr, 0, nullptr, nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto value = static_cast<int32_t>(DisplayMode::AUTO);
    if (!jsValue->IsUndefined()) {
        ArkTSUtils::ParseJsInteger(vm, jsValue, value);
    }
    GetArkUINodeModifiers()->getScrollModifier()->setScrollScrollBar(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scrollDirectionArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (scrollDirectionArg->IsUndefined() || scrollDirectionArg->IsNull()) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollable(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    int32_t scrollDirection = scrollDirectionArg->Int32Value(vm);
    if (scrollDirection != static_cast<int32_t>(Axis::VERTICAL) &&
        scrollDirection != static_cast<int32_t>(Axis::HORIZONTAL) &&
        scrollDirection != static_cast<int32_t>(Axis::FREE) && scrollDirection != static_cast<int32_t>(Axis::NONE)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollable(nativeNode);
    } else {
        GetArkUINodeModifiers()->getScrollModifier()->setScrollScrollable(nativeNode, scrollDirection);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> barcolorArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, barcolorArg, color)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollBarColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getScrollModifier()->setScrollScrollBarColor(nativeNode, color.GetValue());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollBarColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollBarColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scrollBarArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension scrollBarWidth;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, scrollBarArg, scrollBarWidth, false)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollBarWidth(nativeNode);
    } else {
        if (LessNotEqual(scrollBarWidth.Value(), 0.0)) {
            GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollBarWidth(nativeNode);
        } else {
            GetArkUINodeModifiers()->getScrollModifier()->setScrollScrollBarWidth(
                nativeNode, scrollBarWidth.Value(), static_cast<int32_t>(scrollBarWidth.Unit()));
        }
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollScrollBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetEnablePaging(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> enablePagingArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    bool enablePaging;
    if (enablePagingArg->IsBoolean()) {
        enablePaging = enablePagingArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getScrollModifier()->setScrollEnablePaging(nativeNode, enablePaging);
    } else {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollEnablePaging(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetEnablePaging(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollEnablePaging(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetInitialOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> xOffsetArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> yOffsetArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    CalcDimension x;
    ArkTSUtils::ParseJsDimensionVpNG(vm, xOffsetArg, x, false);
    CalcDimension y;
    ArkTSUtils::ParseJsDimensionVpNG(vm, yOffsetArg, y, false);

    GetArkUINodeModifiers()->getScrollModifier()->setScrollInitialOffset(nativeNode, x.Value(),
        static_cast<int32_t>(x.Unit()), y.Value(), static_cast<int32_t>(y.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetInitialOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollInitialOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsNull() && info[1]->IsObject()) {
        Framework::JSScroller* jsScroller =
            Framework::JSRef<Framework::JSObject>::Cast(info[1])->Unwrap<Framework::JSScroller>();
        if (jsScroller) {
            jsScroller->SetInstanceId(Container::CurrentId());
            auto positionController = GetArkUINodeModifiers()->getScrollModifier()->getScroll(nativeNode);
            auto nodePositionController =
                AceType::Claim(reinterpret_cast<OHOS::Ace::ScrollControllerBase*>(positionController));
            jsScroller->SetController(nodePositionController);
            // Init scroll bar proxy.
            auto proxy = jsScroller->GetScrollBarProxy();
            if (!proxy) {
                proxy = ScrollModel::GetInstance()->CreateScrollBarProxy();
                jsScroller->SetScrollBarProxy(proxy);
            }
            auto proxyPtr = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(proxy));
            GetArkUINodeModifiers()->getScrollModifier()->setScrollBarProxy(nativeNode, proxyPtr);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnScrollStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollStart(nativeNode);
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
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnScrollStart(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnScrollStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnScrollEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollEnd(nativeNode);
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
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnScrollEnd(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnScrollEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollStop(nativeNode);
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
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnScrollStop(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnScrollStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollStop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(OHOS::Ace::Dimension, OHOS::Ace::Dimension)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
        OHOS::Ace::Dimension xOffset, OHOS::Ace::Dimension yOffset) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> xOffsetParam = panda::NumberRef::New(
            vm, static_cast<int32_t>(xOffset.ConvertToVp()));
        panda::Local<panda::NumberRef> yOffsetParam = panda::NumberRef::New(
            vm, static_cast<int32_t>(yOffset.ConvertToVp()));
        panda::Local<panda::JSValueRef> params[2] = { xOffsetParam, yOffsetParam }; // 2: Array .length
        func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
    };
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnScroll(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnScrollEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollEdge(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(OHOS::Ace::NG::ScrollEdge)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
        OHOS::Ace::NG::ScrollEdge edge) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> edgeParam = panda::NumberRef::New(vm, static_cast<int32_t>(edge));
        panda::Local<panda::JSValueRef> params[1] = { edgeParam }; // 1: Array length
        func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
    };
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnScrollEdge(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnScrollEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnScrollEdge(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnDidScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(Dimension, Dimension, ScrollState)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
        Dimension xOffset, Dimension yOffset, ScrollState state) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> xOffsetParam = panda::NumberRef::New(
            vm, static_cast<double>(xOffset.ConvertToVp()));
        panda::Local<panda::NumberRef> yOffsetParam = panda::NumberRef::New(
            vm, static_cast<double>(yOffset.ConvertToVp()));
        panda::Local<panda::NumberRef> stateParam = panda::NumberRef::New(vm, static_cast<int32_t>(state));
         // 3: Array length
        panda::Local<panda::JSValueRef> params[3] = { xOffsetParam, yOffsetParam, stateParam };
        func->Call(vm, func.ToLocal(), params, 3); // 3: Array length
    };
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnDidScrollCallBack(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnDidScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnWillScrollCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<TwoDimensionScrollResult(Dimension, Dimension, ScrollState, ScrollSource)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](Dimension xOffset,
            Dimension yOffset, ScrollState state, ScrollSource scrollState) -> TwoDimensionScrollResult {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> xOffsetParam = panda::NumberRef::New(
            vm, static_cast<double>(xOffset.ConvertToVp()));
        panda::Local<panda::NumberRef> yOffsetParam = panda::NumberRef::New(
            vm, static_cast<double>(yOffset.ConvertToVp()));
        panda::Local<panda::NumberRef> stateParam = panda::NumberRef::New(vm, static_cast<double>(state));
        panda::Local<panda::NumberRef> sourceParam = panda::NumberRef::New(vm, static_cast<double>(scrollState));
         // 4: Array length
        panda::Local<panda::JSValueRef> params[4] = { xOffsetParam, yOffsetParam, stateParam, sourceParam};
        auto result = func->Call(vm, func.ToLocal(), params, 4); // 4: Array length
        NG::TwoDimensionScrollResult scrollRes { .xOffset = xOffset, .yOffset = yOffset };

        if (result->IsObject(vm)) {
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> x = resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "xOffset"));
            panda::Local<panda::JSValueRef> y = resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "yOffset"));
            if (x->IsNumber()) {
                scrollRes.xOffset = Dimension(x->ToNumber(vm)->Value(), DimensionUnit::VP);
            }
            if (y->IsNumber()) {
                scrollRes.yOffset = Dimension(y->ToNumber(vm)->Value(), DimensionUnit::VP);
            }
        }
        return scrollRes;
    };
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnWillScrollCallBack(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetScrollOnWillScrollCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnScrollFrameBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetOnScrollFrameBeginCallBack(nativeNode);
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
    GetArkUINodeModifiers()->getScrollModifier()->setOnScrollFrameBeginCallBack(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnScrollFrameBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetOnScrollFrameBeginCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetMaxZoomScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scaleArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    double scale = 1.0;
    if (!ArkTSUtils::ParseJsDouble(vm, scaleArg, scale)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetMaxZoomScale(nativeNode);
    } else {
        GetArkUINodeModifiers()->getScrollModifier()->setMaxZoomScale(nativeNode, scale);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetMaxZoomScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetMaxZoomScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetMinZoomScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scaleArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    double scale = 1.0;
    if (!ArkTSUtils::ParseJsDouble(vm, scaleArg, scale)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetMinZoomScale(nativeNode);
    } else {
        GetArkUINodeModifiers()->getScrollModifier()->setMinZoomScale(nativeNode, scale);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetMinZoomScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetMinZoomScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetZoomScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> scaleArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    double scale = 1.0;
    if (!ArkTSUtils::ParseJsDouble(vm, scaleArg, scale)) {
        GetArkUINodeModifiers()->getScrollModifier()->resetZoomScale(nativeNode);
    } else {
        GetArkUINodeModifiers()->getScrollModifier()->setZoomScale(nativeNode, scale);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetZoomScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetZoomScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetEnableBouncesZoom(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> isEnabledArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    bool isEnabled = isEnabledArg->IsBoolean() ? isEnabledArg->ToBoolean(vm)->Value() : true;
    GetArkUINodeModifiers()->getScrollModifier()->setEnableBouncesZoom(nativeNode, isEnabled);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetEnableBouncesZoom(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->resetEnableBouncesZoom(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnDidZoom(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->setScrollOnDidZoom(nativeNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(float)> callback =
        [vm, weak = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)](float scale) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weak);
        panda::Local<panda::NumberRef> scaleParam = panda::NumberRef::New(vm, static_cast<double>(scale));
        panda::Local<panda::JSValueRef> params[1] = { scaleParam };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnDidZoom(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnDidZoom(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnDidZoom(nativeNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnZoomStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->setScrollOnZoomStart(nativeNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> callback =
        [vm, weak = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weak);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnZoomStart(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnZoomStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnZoomStart(nativeNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::SetScrollOnZoomStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getScrollModifier()->setScrollOnZoomStop(nativeNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback =
        [vm, weak = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weak);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnZoomStop(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollBridge::ResetScrollOnZoomStop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollModifier()->setScrollOnZoomStop(nativeNode, nullptr);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
