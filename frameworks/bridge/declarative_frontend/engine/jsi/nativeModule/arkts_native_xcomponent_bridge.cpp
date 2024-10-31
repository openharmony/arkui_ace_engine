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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_xcomponent_bridge.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/models/indexer_model_impl.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"

namespace OHOS::Ace::NG {

enum ArgIndices {
    ARG_FIRST = 0,
    ARG_ID = 1,
    ARG_TYPE = 2,
    ARG_IMAGE_AI_OPTIONS = 3,
    ARG_LIBRARY_NAME = 4,
    ARG_CONTROLLER = 5
};

XComponentType XComponentBridge::ConvertToXComponentType(const std::string& type)
{
    if (type == "surface") {
        return XComponentType::SURFACE;
    }
    if (type == "component") {
        return XComponentType::COMPONENT;
    }
    if (type == "node") {
        return XComponentType::NODE;
    }
    return XComponentType::SURFACE;
}

void XComponentBridge::ParseParams(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Params& params)
{
    ArkUI_XComponent_Params* xcParams = (ArkUI_XComponent_Params*)(&params);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);
    auto idStr = panda::StringRef::NewFromUtf8(vm, "id");
    auto typeStr = panda::StringRef::NewFromUtf8(vm, "type");
    auto librarynameStr = panda::StringRef::NewFromUtf8(vm, "libraryname");
    auto controllerStr = panda::StringRef::NewFromUtf8(vm, "controller");
    auto imageAIOptionsStr = panda::StringRef::NewFromUtf8(vm, "imageAIOptions");

    auto idArg = obj->Get(vm, idStr);
    auto typeArg = obj->Get(vm, typeStr);
    auto libraryNameArg = obj->Get(vm, librarynameStr);
    auto controllerArg = obj->Get(vm, controllerStr);
    auto imageAIOptionsArg = obj->Get(vm, imageAIOptionsStr);

    xcParams->id = idArg->IsString(vm) ? idArg->ToString(vm)->ToString(vm) : "";
    if (libraryNameArg->IsString(vm)) {
        xcParams->libraryName = libraryNameArg->ToString(vm)->ToString(vm);
    }
    if (typeArg->IsString(vm)) {
        xcParams->type = ConvertToXComponentType(typeArg->ToString(vm)->ToString(vm));
    } else if (typeArg->IsNumber()) {
        xcParams->type = static_cast<XComponentType>(typeArg->Int32Value(vm));
    }
    xcParams->controller = nullptr;
    if (controllerArg->IsObject(vm)) {
        Framework::JSXComponentController* jsXComponentController = static_cast<Framework::JSXComponentController*>(
            Local<panda::ObjectRef>(controllerArg)->GetNativePointerField(vm, 0));
        if (jsXComponentController) {
            jsXComponentController->SetInstanceId(Container::CurrentId());
            Framework::XComponentClient::GetInstance().AddControllerToJSXComponentControllersMap(
                xcParams->id, jsXComponentController);
            xcParams->controller = jsXComponentController->GetController();
        }
    }
    xcParams->aiOptions = nullptr;
    if (imageAIOptionsArg->IsObject(vm)) {
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        Local<JSValueRef> value = imageAIOptionsArg;
        JSValueWrapper valueWrapper = value;
        Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
        napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
        xcParams->aiOptions = optionsValue;
    }
}

void XComponentBridge::SetControllerOnCreated(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);
    auto controllerStr = panda::StringRef::NewFromUtf8(vm, "controller");
    auto controllerArg = obj->Get(vm, controllerStr);
    CHECK_NULL_VOID(controllerArg->IsObject(vm));
    auto object = controllerArg->ToObject(vm);
    auto createdFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceCreated"));
    if (createdFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = createdFunc;
        auto onSurfaceCreated = [vm, func = panda::CopyableGlobal(vm, func), frameNode](const std::string& surfaceId) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, func.ToLocal(), para, 1);
        };
        XComponentModelNG::SetControllerOnCreated(frameNode, std::move(onSurfaceCreated));
    }
}

void XComponentBridge::SetControllerOnChanged(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);
    auto controllerStr = panda::StringRef::NewFromUtf8(vm, "controller");
    auto controllerArg = obj->Get(vm, controllerStr);
    CHECK_NULL_VOID(controllerArg->IsObject(vm));
    auto object = controllerArg->ToObject(vm);
    auto changedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceChanged"));
    if (changedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = changedFunc;
        auto onSurfaceChanged = [vm, func = panda::CopyableGlobal(vm, func), frameNode](
                                    const std::string& surfaceId, const NG::RectF& rect) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "offsetX", "offsetY", "surfaceWidth", "surfaceHeight" };
            Local<JSValueRef> rectValues[] = { panda::NumberRef::New(vm, rect.Left()),
                panda::NumberRef::New(vm, rect.Top()), panda::NumberRef::New(vm, rect.Width()),
                panda::NumberRef::New(vm, rect.Height()) };
            auto rectObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, rectValues);
            panda::Local<panda::JSValueRef> para[2] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()), rectObj };
            func->Call(vm, func.ToLocal(), para, 2);
        };
        XComponentModelNG::SetControllerOnChanged(frameNode, std::move(onSurfaceChanged));
    }
}

void XComponentBridge::SetControllerOnDestroyed(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> paramsArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    CHECK_NULL_VOID(paramsArg->IsObject(vm));
    auto obj = Local<panda::ObjectRef>(paramsArg);
    auto controllerStr = panda::StringRef::NewFromUtf8(vm, "controller");
    auto controllerArg = obj->Get(vm, controllerStr);
    CHECK_NULL_VOID(controllerArg->IsObject(vm));
    auto object = controllerArg->ToObject(vm);
    auto destroyedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceDestroyed"));
    if (destroyedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = destroyedFunc;
        auto ondestroyed = [vm, func = panda::CopyableGlobal(vm, func), frameNode](const std::string& surfaceId) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, func.ToLocal(), para, 1);
        };
        XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(ondestroyed));
    }
}

void XComponentBridge::SetControllerCallback(ArkUIRuntimeCallInfo* runtimeCallInfo, FrameNode* frameNode)
{
    SetControllerOnCreated(runtimeCallInfo, frameNode);
    SetControllerOnChanged(runtimeCallInfo, frameNode);
    SetControllerOnDestroyed(runtimeCallInfo, frameNode);
}

void XComponentBridge::SetControllerCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> controllerArg = runtimeCallInfo->GetCallArgRef(ARG_CONTROLLER);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    auto object = controllerArg->ToObject(vm);
    auto createdFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceCreated"));
    if (createdFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = createdFunc;
        auto onSurfaceCreated = [vm, func = panda::CopyableGlobal(vm, func), frameNode](const std::string& surfaceId) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, func.ToLocal(), para, 1);
        };
        XComponentModelNG::SetControllerOnCreated(frameNode, std::move(onSurfaceCreated));
    }
    auto changedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceChanged"));
    if (changedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = changedFunc;
        auto onSurfaceChanged = [vm, func = panda::CopyableGlobal(vm, func), frameNode](
                                    const std::string& surfaceId, const NG::RectF& rect) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "offsetX", "offsetY", "surfaceWidth", "surfaceHeight" };
            Local<JSValueRef> rectValues[] = { panda::NumberRef::New(vm, rect.Left()),
                panda::NumberRef::New(vm, rect.Top()), panda::NumberRef::New(vm, rect.Width()),
                panda::NumberRef::New(vm, rect.Height()) };
            auto rectObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, rectValues);
            panda::Local<panda::JSValueRef> para[2] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()), rectObj };
            func->Call(vm, func.ToLocal(), para, 2);
        };
        XComponentModelNG::SetControllerOnChanged(frameNode, std::move(onSurfaceChanged));
    }
    auto destroyedFunc = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "onSurfaceDestroyed"));
    if (destroyedFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = destroyedFunc;
        auto ondestroyed = [vm, func = panda::CopyableGlobal(vm, func), frameNode](const std::string& surfaceId) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> para[1] = { panda::StringRef::NewFromUtf8(vm, surfaceId.c_str()) };
            func->Call(vm, func.ToLocal(), para, 1);
        };
        XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(ondestroyed));
    }
}

ArkUINativeModuleValue XComponentBridge::SetXComponentInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> idArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(ARG_TYPE);
    Local<JSValueRef> librarynameArg = runtimeCallInfo->GetCallArgRef(ARG_LIBRARY_NAME);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!idArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSRef<Framework::JSVal> args = info[ARG_CONTROLLER];
    Framework::JSRef<Framework::JSObject> controllerObj;
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    if (args->IsObject()) {
        controllerObj = Framework::JSRef<Framework::JSObject>::Cast(args);
        Framework::JSXComponentController* jsXComponentController =
            controllerObj->Unwrap<Framework::JSXComponentController>();
        if (jsXComponentController) {
            jsXComponentController->SetInstanceId(Container::CurrentId());
            Framework::XComponentClient::GetInstance().AddControllerToJSXComponentControllersMap(
                idArg->ToString(vm)->ToString(vm), jsXComponentController);
            xcomponentController = jsXComponentController->GetController();
        }
    }
    XComponentType xcomponentType = XComponentType::SURFACE;
    if (typeArg->IsString(vm)) {
        xcomponentType = ConvertToXComponentType(typeArg->ToString(vm)->ToString(vm));
    } else if (typeArg->IsNumber()) {
        xcomponentType = static_cast<XComponentType>(typeArg->Int32Value(vm));
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentId(
        nativeNode, idArg->ToString(vm)->ToString(vm).c_str());
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentType(
        nativeNode, static_cast<int32_t>(xcomponentType));
    if (librarynameArg->IsString(vm)) {
        auto libraryName = librarynameArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentLibraryname(nativeNode, libraryName.c_str());
    }
    if ((librarynameArg->IsNull() || librarynameArg->IsUndefined()) && xcomponentController &&
        !controllerObj->IsUndefined()) {
        SetControllerCallback(runtimeCallInfo);
    }
    HandleDetachCallback(runtimeCallInfo);
    HandleImageAIOptions(runtimeCallInfo);
    GetArkUINodeModifiers()->getXComponentModifier()->initXComponent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void XComponentBridge::HandleDetachCallback(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto detachCallback = [](const std::string& xcomponentId) {
        Framework::XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(xcomponentId);
        Framework::XComponentClient::GetInstance().DeleteFromJsValMapById(xcomponentId);
    };
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    XComponentModelNG::SetDetachCallback(frameNode, std::move(detachCallback));
}

void XComponentBridge::HandleImageAIOptions(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> imageAIOptionsArg = runtimeCallInfo->GetCallArgRef(ARG_IMAGE_AI_OPTIONS);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (imageAIOptionsArg->IsObject(vm)) {
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        Local<JSValueRef> value = imageAIOptionsArg;
        JSValueWrapper valueWrapper = value;
        Framework::ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
        napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
        GetArkUINodeModifiers()->getXComponentModifier()->setImageAIOptions(nativeNode, optionsValue);
    }
}

ArkUINativeModuleValue XComponentBridge::ResetXComponentInitialize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetOpacity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double opacity;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, opacity)) {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentOpacity(nativeNode);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentOpacity(nativeNode, opacity);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetOpacity(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentOpacity(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetLinearGradientBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetLinearGradientBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetPixelStretchEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetPixelStretchEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetLightUpEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetLightUpEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSphericalEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetSphericalEffect(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetColorBlend(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetColorBlend(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetHueRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetHueRotate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSepia(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetSepia(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetInvert(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetInvert(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetContrast(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetContrast(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetSaturate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetSaturate(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBrightness(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBrightness(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetGrayscale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetGrayscale(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackdropBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackdropBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBlur(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImagePosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundImagePosition(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImageSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundImageSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetBackgroundImage(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetBackgroundImage(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetOnLoad(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    CHECK_NULL_RETURN(secondArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto obj = secondArg->ToObject(vm);
    panda::Local<panda::FunctionRef> func = obj;
    auto onLoad = [vm, func = panda::CopyableGlobal(vm, func), frameNode](const std::string& xcomponentId) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        std::vector<Local<JSValueRef>> argv;
        Framework::JSRef<Framework::JSVal> jsVal;
        if (Framework::XComponentClient::GetInstance().GetJSVal(xcomponentId, jsVal)) {
            argv.emplace_back(jsVal->GetLocalHandle());
        }
        func->Call(vm, func.ToLocal(), argv.data(), argv.size());
    };
    XComponentModelNG::SetOnLoad(frameNode, std::move(onLoad));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetOnLoad(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetOnDestroy(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    CHECK_NULL_RETURN(secondArg->IsFunction(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto obj = secondArg->ToObject(vm);
    panda::Local<panda::FunctionRef> func = obj;
    auto onDestroy = [vm, func = panda::CopyableGlobal(vm, func), frameNode]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    XComponentModelNG::SetOnDestroy(frameNode, std::move(onDestroy));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetOnDestroy(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetEnableAnalyzer(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentEnableAnalyzer(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableAnalyzer(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetEnableAnalyzer(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableAnalyzer(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetEnableSecure(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool boolValue = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getXComponentModifier()->setXComponentEnableSecure(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableSecure(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetEnableSecure(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentEnableSecure(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::SetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto fitModeArg = runtimeCallInfo->GetCallArgRef(ARG_ID);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto renderFit = static_cast<int32_t>(RenderFit::TOP_LEFT);
    if (fitModeArg->IsNumber()) {
        renderFit = fitModeArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getXComponentModifier()->setXComponentRenderFit(nativeNode, renderFit);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentBridge::ResetRenderFit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(ARG_FIRST);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getXComponentModifier()->resetXComponentRenderFit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
