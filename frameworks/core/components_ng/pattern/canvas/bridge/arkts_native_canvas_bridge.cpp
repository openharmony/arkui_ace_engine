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
#include "frameworks/core/components_ng/pattern/canvas/bridge/arkts_native_canvas_bridge.h"

#include "base/error/error_code.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

extern "C" void OHOS_ACE_CreateDrawingRenderingContext(
    void* vmRaw, void** outJsHandle, void** outCppPtr);

// Local definition of JSRenderingContextBase to avoid including js_rendering_context_base.h,
// which transitively includes bindings_defines.h (requires USE_ARK_ENGINE).
// The canvas bridge .so is compiled with USE_ARK_ENGINE but does not link
// js_rendering_context_base.cpp.
namespace OHOS::Ace::Framework {
class JSRenderingContextBase : public virtual AceType {
    DECLARE_ACE_TYPE(JSRenderingContextBase, AceType);
public:
    JSRenderingContextBase() = default;
    virtual ~JSRenderingContextBase() = default;

    virtual void SetAntiAlias() = 0;
    virtual void SetDensity() = 0;
    virtual void SetCanvasPattern(const RefPtr<AceType>& canvas) = 0;
    virtual void SetInstanceId(int32_t id) = 0;
    virtual int32_t GetInstanceId() = 0;
    virtual void SetUnit(CanvasUnit unit) = 0;

    bool IsBuiltIn() const
    {
        return builtIn_;
    }

    void SetBuiltIn(bool builtIn)
    {
        builtIn_ = builtIn;
    }

    ACE_DISALLOW_COPY_AND_MOVE(JSRenderingContextBase);

private:
    bool builtIn_ = false;
};
} // namespace OHOS::Ace::Framework

namespace OHOS::Ace::NG {
using namespace OHOS::Ace::Framework;

void CanvasBridge::RegisterCanvasAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create",
        "setCanvasOnReady", "resetCanvasOnReady",
        "setCanvasEnableAnalyzer", "resetCanvasEnableAnalyzer",
        "setCanvasImmediateRender", "resetCanvasImmediateRender",
        "setCanvasUpdateUnit", "resetCanvasUpdateUnit" };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::CreateCanvas),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::SetCanvasOnReady),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::ResetCanvasOnReady),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::SetCanvasEnableAnalyzer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::ResetCanvasEnableAnalyzer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::SetCanvasImmediateRender),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::ResetCanvasImmediateRender),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::SetCanvasUpdateUnit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CanvasBridge::ResetCanvasUpdateUnit),
    };
    auto canvas = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "canvas"), canvas);
}

namespace {
// Read the C++ binding pointer stored in internal field 0 of a Panda ObjectRef.
// Mirrors what JsiObject::Unwrap<T>() does, but without dragging in jsi_types.cpp
// (which is not linked into libarkui_canvas.z.so).
template<typename T>
T* UnwrapNativePointer(EcmaVM* vm, const Local<panda::ObjectRef>& obj)
{
    if (obj->GetNativePointerFieldCount(vm) < 1) {
        return nullptr;
    }
    return static_cast<T*>(obj->GetNativePointerField(vm, 0));
}

// Inlined ArkTSUtils::ThrowBusinessError — its .cpp lives in the main libace.z.so
// and isn't linked into the canvas dynamic module.
void ThrowBusinessErrorInline(EcmaVM* vm, const std::string& msg, int32_t code)
{
    auto errorVal = panda::Exception::Error(vm, panda::StringRef::NewFromUtf8(vm, msg.c_str()));
    auto codeVal = panda::NumberRef::New(vm, code);
    Local<panda::StringRef> codeKey = panda::StringRef::NewFromUtf8(vm, "code");
    Local<panda::ObjectRef> errorObj(errorVal);
    errorObj->Set(vm, codeKey, codeVal);
    panda::JSNApi::ThrowException(vm, errorObj);
}

// RAII wrapper for napi handle scope — avoids including js_utils.h.
class ScopeRAII {
public:
    explicit ScopeRAII(napi_env env) : env_(env)
    {
        napi_open_handle_scope(env_, &scope_);
    }
    ~ScopeRAII()
    {
        napi_close_handle_scope(env_, scope_);
    }
private:
    napi_env env_;
    napi_handle_scope scope_;
};

// Convert a Panda Local<JSValueRef> into a napi_value, then forward it to
// CanvasPattern::SetImageAIOptions. Mirrors the napi conversion that the old
// JSCanvas::ParseCanvasParams performed via EngineHelper + ValueToNapiValue.
void ApplyImageAIOptions(EcmaVM* vm, const Local<JSValueRef>& optionsArg, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    CHECK_NULL_VOID(pattern);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    JSValueWrapper valueWrapper = optionsArg;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
    pattern->SetImageAIOptions(optionsValue);
}

// Parse a CanvasParams { unit, imageAIOptions } object — only entered when the
// first argument is NOT a JSRenderingContext binding.
void ParseCanvasParams(EcmaVM* vm, const Local<panda::ObjectRef>& paramsObj, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto unitVal = paramsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "unit"));
    if (unitVal->IsNumber()) {
        int32_t unit = unitVal->ToNumber(vm)->Value();
        CanvasModelNG::UpdateUnit(frameNode, static_cast<CanvasUnit>(unit));
    } else {
        CanvasModelNG::UpdateUnit(frameNode, CanvasUnit::DEFAULT);
    }
    auto aiOptionsVal = paramsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "imageAIOptions"));
    if (aiOptionsVal->IsObject(vm)) {
        ApplyImageAIOptions(vm, aiOptionsVal, frameNode);
    }
}
} // namespace

ArkUINativeModuleValue CanvasBridge::CreateCanvas(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    // 1. Create the FrameNode + CanvasPattern (matches CanvasModel::GetInstance()->Create()).
    auto* nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto* canvasModifier = nodeModifiers->getCanvasModifier();
    CHECK_NULL_RETURN(canvasModifier, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(canvasModifier->createModel, panda::JSValueRef::Undefined(vm));
    canvasModifier->createModel();
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(0);

    // 2. info[0] is undefined: detach render context and disable immediate render.
    if (paramsArg->IsUndefined()) {
        CanvasModelNG::DetachRenderContext(frameNode);
        CanvasModelNG::SetImmediateRender(frameNode, false);
    } else if (paramsArg->IsObject(vm)) {
        // 3. info[0] is an object — try to unwrap its internal field 0 as a
        //    JSRenderingContextBase*. If unwrap succeeds, it's a user-supplied
        //    context (canvas binds to it, immediate render is OFF). Otherwise
        //    it's a CanvasParams literal.
        auto paramsObj = paramsArg->ToObject(vm);
        auto* jsContext = UnwrapNativePointer<JSRenderingContextBase>(vm, paramsObj);
        CanvasModelNG::SetImmediateRender(frameNode, jsContext == nullptr);
        if (jsContext != nullptr) {
            if (jsContext->IsBuiltIn()) {
                ThrowBusinessErrorInline(vm,
                    "The context created in system cannot be bound to other canvas component.",
                    ERROR_CODE_CANVAS_ERROR_CONTEXT);
                return panda::JSValueRef::Undefined(vm);
            }
            jsContext->SetInstanceId(Container::CurrentId());
            jsContext->SetCanvasPattern(pattern);
            jsContext->SetAntiAlias();
            jsContext->SetDensity();
        } else {
            ParseCanvasParams(vm, paramsObj, frameNode);
        }
    }

    // 4. Optional second argument is also imageAIOptions (matches JSCanvas::Create
    //    info.Length() > 1 branch).
    if (runtimeCallInfo->GetArgsNumber() > 1) {
        Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(1);
        if (optionsArg->IsObject(vm)) {
            ApplyImageAIOptions(vm, optionsArg, frameNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::SetCanvasOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    if (!ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    FrameNode* frameNode = nativeNode ? reinterpret_cast<FrameNode*>(nativeNode)
                                      : ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        auto* nms = GetArkUINodeModifiers();
        if (nms && nms->getCanvasModifier()) {
            nms->getCanvasModifier()->resetCanvasOnReady(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(bool, CanvasUnit)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func), isJsView](
                                                         bool needDrawingContext, CanvasUnit unit) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        if (!needDrawingContext) {
            auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
            return;
        }
        if (!frameNode) {
            return;
        }
        auto pattern = frameNode->GetPattern<NG::CanvasPattern>();
        if (!pattern) {
            return;
        }

        // Create JSDrawingRenderingContext via exported interface from libace_compatible.z.so,
        // then set properties and invoke callback locally within canvas so.
        void* jsHandleRaw = nullptr;
        void* cppPtrRaw = nullptr;
        OHOS_ACE_CreateDrawingRenderingContext(
            reinterpret_cast<void*>(vm), &jsHandleRaw, &cppPtrRaw);
        if (!jsHandleRaw || !cppPtrRaw) {
            return;
        }
        auto* drawingContext = reinterpret_cast<Framework::JSRenderingContextBase*>(cppPtrRaw);
        drawingContext->SetInstanceId(Container::CurrentId());
        drawingContext->SetCanvasPattern(pattern);
        drawingContext->SetUnit(unit);
        auto* canvasModifier = GetArkUINodeModifiers()->getCanvasModifier();
        if (canvasModifier && canvasModifier->setUpdateContextCallback) {
            std::function<void(CanvasUnit)> cb =
                [drawingContext](CanvasUnit u) { drawingContext->SetUnit(u); };
            canvasModifier->setUpdateContextCallback(
                reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(pattern)), &cb);
        }
        if (canvasModifier && canvasModifier->setRSCanvasForDrawingContext) {
            canvasModifier->setRSCanvasForDrawingContext(
                reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(pattern)));
        }
        Local<panda::ObjectRef> jsDrawingContext(
            reinterpret_cast<uintptr_t>(jsHandleRaw));
        std::vector<Local<JSValueRef>> argv;
        argv.emplace_back(jsDrawingContext);
        func->Call(vm, func.ToLocal(), argv.data(), argv.size());

    };
    GetArkUINodeModifiers()->getCanvasModifier()->setCanvasOnReady(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::ResetCanvasOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasOnReady(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::SetCanvasEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> flagArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!flagArg->IsBoolean()) {
        GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasEnableAnalyzer(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = flagArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getCanvasModifier()->setCanvasEnableAnalyzer(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::ResetCanvasEnableAnalyzer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasEnableAnalyzer(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::SetCanvasImmediateRender(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!valueArg->IsBoolean()) {
        GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasImmediateRender(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool value = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getCanvasModifier()->setCanvasImmediateRender(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::ResetCanvasImmediateRender(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasImmediateRender(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::SetCanvasUpdateUnit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasUpdateUnit(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t unit = valueArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getCanvasModifier()->setCanvasUpdateUnit(nativeNode, unit);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CanvasBridge::ResetCanvasUpdateUnit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getCanvasModifier()->resetCanvasUpdateUnit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
