/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_reader/bridge/arkts_native_container_reader_bridge.h"

#include "base/geometry/dimension.h"
#include "base/log/log.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/common/container_scope.h"
#include "core/common/window_size_breakpoint.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

constexpr size_t MAX_NUMBER_WIDTH_BREAKPOINT = 4;
constexpr size_t MAX_NUMBER_HEIGHT_BREAKPOINT = 2;
constexpr int32_t MIN_WIDTH_BREAKPOINT_VALUE = 0;
constexpr int32_t MAX_WIDTH_BREAKPOINT_VALUE = static_cast<int32_t>(WidthBreakpoint::WIDTH_XL);
constexpr int32_t MIN_HEIGHT_BREAKPOINT_VALUE = 0;
constexpr int32_t MAX_HEIGHT_BREAKPOINT_VALUE = static_cast<int32_t>(HeightBreakpoint::HEIGHT_LG);
constexpr double INITIAL_BREAKPOINT_COMPARE_VALUE = -1.0;
constexpr int32_t CREATE_ARGC_ONE = 1;
constexpr int32_t CREATE_ARGC_TWO = 2;
constexpr size_t ARG_INDEX_FIRST = 0;
constexpr size_t ARG_INDEX_SECOND = 1;

bool ParseSortedArrayElements(EcmaVM* vm, const Local<panda::ArrayRef>& arr,
    uint32_t len, std::vector<double>& breakpoints)
{
    double preValue = INITIAL_BREAKPOINT_COMPARE_VALUE;
    for (uint32_t i = 0; i < len; i++) {
        auto elem = panda::ArrayRef::GetValueAt(vm, arr, i);
        if (!elem->IsNumber()) {
            continue;
        }
        double value = elem->ToNumber(vm)->Value();
        if (GreatNotEqual(preValue, value)) {
            return false;
        }
        preValue = value;
        breakpoints.push_back(value);
    }
    return true;
}

bool ParseBreakpointArray(EcmaVM* vm, const Local<panda::JSValueRef>& arrayVal,
    std::vector<double>& breakpoints, size_t maxCount)
{
    if (!arrayVal->IsArray(vm)) {
        return true;
    }
    auto arr = panda::Local<panda::ArrayRef>(arrayVal);
    uint32_t len = arr->Length(vm);
    if (len > maxCount) {
        return false;
    }
    return ParseSortedArrayElements(vm, arr, len, breakpoints);
}

void ParseBreakPointConfigFromJs(EcmaVM* vm, const Local<panda::ObjectRef>& jsObj,
    std::vector<double>& widthBreakpoints, std::vector<double>& heightBreakpoints)
{
    auto widthVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    ParseBreakpointArray(vm, widthVal, widthBreakpoints, MAX_NUMBER_WIDTH_BREAKPOINT);

    auto heightVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    ParseBreakpointArray(vm, heightVal, heightBreakpoints, MAX_NUMBER_HEIGHT_BREAKPOINT);
}

SizeF ParseSizeObjectFromJs(EcmaVM* vm, const Local<panda::JSValueRef>& sizeVal)
{
    SizeF size;
    if (!sizeVal->IsObject(vm)) {
        return size;
    }
    auto sizeObj = sizeVal->ToObject(vm);
    auto widthVal = sizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto heightVal = sizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    CalcDimension width;
    CalcDimension height;
    if (ArkTSUtils::ParseJsDimensionVp(vm, widthVal, width)) {
        size.SetWidth(static_cast<float>(width.ConvertToPx()));
    }
    if (ArkTSUtils::ParseJsDimensionVp(vm, heightVal, height)) {
        size.SetHeight(static_cast<float>(height.ConvertToPx()));
    }
    return size;
}

WidthBreakpoint ParseWidthBreakpointFromJs(EcmaVM* vm, const Local<panda::JSValueRef>& val)
{
    if (val->IsNumber()) {
        int32_t bpValue = val->Int32Value(vm);
        if (bpValue >= MIN_WIDTH_BREAKPOINT_VALUE && bpValue <= MAX_WIDTH_BREAKPOINT_VALUE) {
            return static_cast<WidthBreakpoint>(bpValue);
        }
    }
    return WidthBreakpoint::UNDEFINED;
}

HeightBreakpoint ParseHeightBreakpointFromJs(EcmaVM* vm, const Local<panda::JSValueRef>& val)
{
    if (val->IsNumber()) {
        int32_t bpValue = val->Int32Value(vm);
        if (bpValue >= MIN_HEIGHT_BREAKPOINT_VALUE && bpValue <= MAX_HEIGHT_BREAKPOINT_VALUE) {
            return static_cast<HeightBreakpoint>(bpValue);
        }
    }
    return HeightBreakpoint::HEIGHT_SM;
}

bool ParseBindableObject(EcmaVM* vm, const Local<panda::JSValueRef>& propVal,
    Local<panda::JSValueRef>& outCallback, Local<panda::JSValueRef>& outActualValue)
{
    if (!propVal->IsObject(vm)) {
        return false;
    }
    auto obj = propVal->ToObject(vm);
    auto onChangeVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "onChange"));
    if (onChangeVal->IsFunction(vm)) {
        outCallback = onChangeVal;
        outActualValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        return true;
    }
    return false;
}

bool ParseTwoWayProperty(EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, const char* propName,
    Local<panda::JSValueRef>& outCallback, Local<panda::JSValueRef>& outActualValue)
{
    auto propVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, propName));
    // Pattern 1: {value, changeEvent}
    if (propVal->IsObject(vm)) {
        auto propObj = propVal->ToObject(vm);
        auto changeEventVal = propObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        if (changeEventVal->IsFunction(vm)) {
            outCallback = changeEventVal;
            outActualValue = propObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
            return true;
        }
    }
    // Pattern 2: $propName
    std::string dollarProp = std::string("$") + propName;
    auto dollarVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, dollarProp.c_str()));
    if (dollarVal->IsFunction(vm)) {
        outCallback = dollarVal;
        outActualValue = propVal;
        return true;
    }
    return false;
}

bool TryParseSizeChangeEvent(EcmaVM* vm, const Local<panda::JSValueRef>& sizeVal,
    Local<panda::JSValueRef>& sizeCallback, SizeF& outSize)
{
    if (!sizeVal->IsObject(vm)) {
        return false;
    }
    auto sizeObj = sizeVal->ToObject(vm);
    auto changeEventVal = sizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
    if (!changeEventVal->IsFunction(vm)) {
        return false;
    }
    sizeCallback = changeEventVal;
    auto valueProp = sizeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
    outSize = ParseSizeObjectFromJs(vm, valueProp);
    return true;
}

SizeF ParseSizeWithBinding(EcmaVM* vm, const Local<panda::ObjectRef>& paramObj,
    Local<panda::JSValueRef>& sizeCallback)
{
    auto sizeVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));

    // Pattern 1: {value, changeEvent}
    SizeF size;
    if (TryParseSizeChangeEvent(vm, sizeVal, sizeCallback, size)) {
        return size;
    }

    // Pattern 2: Bindable {value, onChange}
    Local<panda::JSValueRef> bindableCallback = panda::JSValueRef::Undefined(vm);
    Local<panda::JSValueRef> actualSizeVal = panda::JSValueRef::Undefined(vm);
    if (ParseBindableObject(vm, sizeVal, bindableCallback, actualSizeVal)) {
        sizeCallback = bindableCallback;
        return ParseSizeObjectFromJs(vm, actualSizeVal);
    }

    // Pattern 3: $size
    auto dollarSize = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$size"));
    if (dollarSize->IsFunction(vm)) {
        sizeCallback = dollarSize;
        return ParseSizeObjectFromJs(vm, sizeVal);
    }

    // Pattern 4: plain object
    return ParseSizeObjectFromJs(vm, sizeVal);
}

template<typename T>
T ParseBreakpointWithBinding(EcmaVM* vm, const Local<panda::ObjectRef>& paramObj, const char* propName,
    T (*parser)(EcmaVM*, const Local<panda::JSValueRef>&), Local<panda::JSValueRef>& outCallback)
{
    auto bpVal = paramObj->Get(vm, panda::StringRef::NewFromUtf8(vm, propName));

    // Pattern 1: Bindable {value, onChange}
    Local<panda::JSValueRef> bindableCallback = panda::JSValueRef::Undefined(vm);
    Local<panda::JSValueRef> actualVal = panda::JSValueRef::Undefined(vm);
    if (ParseBindableObject(vm, bpVal, bindableCallback, actualVal)) {
        outCallback = bindableCallback;
        return parser(vm, actualVal);
    }

    // Pattern 2: TwoWay property
    Local<panda::JSValueRef> twoWayCallback = panda::JSValueRef::Undefined(vm);
    Local<panda::JSValueRef> twoWayActual = panda::JSValueRef::Undefined(vm);
    if (ParseTwoWayProperty(vm, paramObj, propName, twoWayCallback, twoWayActual)) {
        outCallback = twoWayCallback;
        return parser(vm, twoWayActual);
    }

    // Pattern 3: Object with value
    if (bpVal->IsObject(vm)) {
        auto obj = bpVal->ToObject(vm);
        auto valueProp = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        return parser(vm, valueProp);
    }

    // Pattern 4: Direct value
    return parser(vm, bpVal);
}

void SetupSizeChangeCallback(EcmaVM* vm, const Local<panda::JSValueRef>& sizeCallback)
{
    if (!sizeCallback->IsFunction(vm)) {
        return;
    }
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> sizeFunc = sizeCallback;
    std::function<void(const SizeF&)> onSizeChange =
        [vm, node = targetNode, func = panda::CopyableGlobal(vm, sizeFunc)](const SizeF& sz) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        const char* keys[] = { "width", "height" };
        Local<JSValueRef> values[] = {
            panda::NumberRef::New(vm, sz.Width()),
            panda::NumberRef::New(vm, sz.Height())
        };
        Local<JSValueRef> sizeObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        auto result = func->Call(vm, func.ToLocal(), &sizeObj, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getContainerReaderModifier()->setOnSizeChange(
        nullptr, reinterpret_cast<void*>(&onSizeChange));
}

void SetupWidthBreakpointCallback(EcmaVM* vm, const Local<panda::JSValueRef>& widthBpCallback)
{
    if (!widthBpCallback->IsFunction(vm)) {
        return;
    }
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> widthBpFunc = widthBpCallback;
    std::function<void(WidthBreakpoint)> onWidthBpChange =
        [vm, node = targetNode, func = panda::CopyableGlobal(vm, widthBpFunc)](WidthBreakpoint breakpoint) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[1] = {
            panda::NumberRef::New(vm, static_cast<int32_t>(breakpoint))
        };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getContainerReaderModifier()->setOnWidthBreakpointChange(
        nullptr, reinterpret_cast<void*>(&onWidthBpChange));
}

void SetupHeightBreakpointCallback(EcmaVM* vm, const Local<panda::JSValueRef>& heightBpCallback)
{
    if (!heightBpCallback->IsFunction(vm)) {
        return;
    }
    auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> heightBpFunc = heightBpCallback;
    std::function<void(HeightBreakpoint)> onHeightBpChange =
        [vm, node = targetNode, func = panda::CopyableGlobal(vm, heightBpFunc)](HeightBreakpoint breakpoint) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[1] = {
            panda::NumberRef::New(vm, static_cast<int32_t>(breakpoint))
        };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getContainerReaderModifier()->setOnHeightBreakpointChange(
        nullptr, reinterpret_cast<void*>(&onHeightBpChange));
}

void SetupRenderFunction(EcmaVM* vm, const Local<panda::JSValueRef>& renderFuncArg)
{
    if (!renderFuncArg->IsFunction(vm)) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    panda::Local<panda::FunctionRef> renderFuncRef = renderFuncArg;
    std::function<RefPtr<UINode>(int64_t, bool&)> renderFunc =
        [vm, node = frameNode, func = panda::CopyableGlobal(vm, renderFuncRef),
            instanceId = Container::CurrentId()](
            int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(instanceId);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(node));
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        CHECK_NULL_RETURN(node, nullptr);
        return AceType::Claim(reinterpret_cast<NG::UINode *>(node));
    };
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getContainerReaderModifier()->setRenderFunction(
        nullptr, reinterpret_cast<void*>(&renderFunc));
}

} // namespace

void ContainerReaderBridge::RegisterContainerReaderAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    const char* functionNames[] = { "create", "breakpointConfig", "setBreakPointConfig", "resetBreakPointConfig" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ContainerReaderBridge::CreateContainerReader),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ContainerReaderBridge::BreakPointConfig),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ContainerReaderBridge::SetBreakPointConfig),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ContainerReaderBridge::ResetBreakPointConfig),
    };
    auto containerReader =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "containerreader"), containerReader);
}

ArkUINativeModuleValue ContainerReaderBridge::CreateContainerReader(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = panda::JSValueRef::Undefined(vm);
    Local<JSValueRef> secondArg = panda::JSValueRef::Undefined(vm);
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc == CREATE_ARGC_TWO) {
        firstArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_FIRST);
        secondArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_SECOND);
    } else if (argc == CREATE_ARGC_ONE) {
        firstArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_FIRST);
    }

    if (!firstArg->IsObject(vm)) {
        TAG_LOGI(AceLogTag::ACE_LAYOUT, "firstArg is not object, create with defaults");
        nodeModifiers->getContainerReaderModifier()->create();
        return panda::JSValueRef::Undefined(vm);
    }

    auto paramObj = firstArg->ToObject(vm);

    // Parse size with two-way binding
    Local<panda::JSValueRef> sizeCallback = panda::JSValueRef::Undefined(vm);
    ParseSizeWithBinding(vm, paramObj, sizeCallback);

    // Parse breakpoints with binding
    Local<panda::JSValueRef> widthBpCallback = panda::JSValueRef::Undefined(vm);
    ParseBreakpointWithBinding(vm, paramObj, "widthBreakpoint", ParseWidthBreakpointFromJs, widthBpCallback);

    Local<panda::JSValueRef> heightBpCallback = panda::JSValueRef::Undefined(vm);
    ParseBreakpointWithBinding(vm, paramObj, "heightBreakpoint", ParseHeightBreakpointFromJs, heightBpCallback);

    // Create node and register callbacks
    nodeModifiers->getContainerReaderModifier()->create();
    SetupSizeChangeCallback(vm, sizeCallback);
    SetupWidthBreakpointCallback(vm, widthBpCallback);
    SetupHeightBreakpointCallback(vm, heightBpCallback);
    SetupRenderFunction(vm, secondArg);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ContainerReaderBridge::BreakPointConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_FIRST);
    if (!firstArg->IsObject(vm)) {
        TAG_LOGI(AceLogTag::ACE_LAYOUT, "SetBreakPointConfig firstArg is not object, skip");
        return panda::JSValueRef::Undefined(vm);
    }

    auto configObj = firstArg->ToObject(vm);
    std::vector<double> widthBreakpoints;
    std::vector<double> heightBreakpoints;
    ParseBreakPointConfigFromJs(vm, configObj, widthBreakpoints, heightBreakpoints);

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getContainerReaderModifier()->setBreakPointConfig(
        nullptr, widthBreakpoints.data(), widthBreakpoints.size(),
        heightBreakpoints.data(), heightBreakpoints.size());

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ContainerReaderBridge::SetBreakPointConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_FIRST);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_SECOND);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (!firstArg->IsObject(vm)) {
        TAG_LOGI(AceLogTag::ACE_LAYOUT, "SetBreakPointConfig firstArg is not object, skip");
        return panda::JSValueRef::Undefined(vm);
    }

    auto configObj = firstArg->ToObject(vm);
    std::vector<double> widthBreakpoints;
    std::vector<double> heightBreakpoints;
    ParseBreakPointConfigFromJs(vm, configObj, widthBreakpoints, heightBreakpoints);

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getContainerReaderModifier()->setBreakPointConfig(
        nativeNode, widthBreakpoints.data(), widthBreakpoints.size(),
        heightBreakpoints.data(), heightBreakpoints.size());

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ContainerReaderBridge::ResetBreakPointConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(ARG_INDEX_FIRST);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getContainerReaderModifier()->resetBreakPointConfig(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
