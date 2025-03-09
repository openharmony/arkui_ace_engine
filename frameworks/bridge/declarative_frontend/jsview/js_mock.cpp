/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/js_mock.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_bindings.h"
#include "bridge/declarative_frontend/engine/jsi/modules/jsi_curves_module.h"
#include "bridge/js_frontend/engine/jsi/ark_js_value.h"

namespace OHOS::Ace::Framework {
void JSMockBaseNode::JSBind(BindingTarget globalObj)
{
    JSClass<JSMockBaseNode>::Declare("__JSBaseNode__");

    JSClass<JSMockBaseNode>::CustomMethod("create", &JSMockBaseNode::Create);
    JSClass<JSMockBaseNode>::CustomMethod("finishUpdateFunc", &JSMockBaseNode::FinishUpdateFunc);
    JSClass<JSMockBaseNode>::CustomMethod("postTouchEvent", &JSMockBaseNode::PostTouchEvent);
    JSClass<JSMockBaseNode>::CustomMethod("disposeNode", &JSMockBaseNode::Dispose);
    JSClass<JSMockBaseNode>::CustomMethod("updateStart", &JSMockBaseNode::UpdateStart);
    JSClass<JSMockBaseNode>::CustomMethod("updateEnd", &JSMockBaseNode::UpdateEnd);

    JSClass<JSMockBaseNode>::Bind(globalObj, JSMockBaseNode::ConstructorCallback, JSMockBaseNode::DestructorCallback);
}

void JSMockViewPU::JSBind(BindingTarget globalObj, std::string name)
{
    JSClass<JSMockViewPU>::Declare(name.c_str());

    JSClass<JSMockViewPU>::CustomMethod("id__", &JSMockViewPU::Id);
    JSClass<JSMockViewPU>::CustomMethod("updateStateVars", &JSMockViewPU::UpdateStateVars);
    JSClass<JSMockViewPU>::CustomMethod("aboutToReuseInternal", &JSMockViewPU::AboutToReuseInternal);
    JSClass<JSMockViewPU>::CustomMethod("aboutToRecycleInternal", &JSMockViewPU::AboutToRecycleInternal);
    JSClass<JSMockViewPU>::CustomMethod("updateDirtyElements", &JSMockViewPU::UpdateDirtyElements);

    JSClass<JSMockViewPU>::Bind(globalObj);
}

void JSMockScopeUtil::JSBind(BindingTarget globalObj)
{
    JSClass<JSMockScopeUtil>::Declare("__JSScopeUtil__");
    JSClass<JSMockScopeUtil>::StaticMethod("syncInstanceId", &JSMockScopeUtil::SyncInstanceId);
    JSClass<JSMockScopeUtil>::StaticMethod("restoreInstanceId", &JSMockScopeUtil::RestoreInstanceId);

    JSClass<JSMockScopeUtil>::Bind(globalObj);
}

void MockCustomDialogController::JSBind(BindingTarget globalObj)
{
    JSClass<MockCustomDialogController>::Declare("CustomDialogController");

    JSClass<MockCustomDialogController>::CustomMethod("open", &MockCustomDialogController::Open);
    JSClass<MockCustomDialogController>::CustomMethod("close", &MockCustomDialogController::Close);

    JSClass<JSMockBaseNode>::Bind(globalObj);
}

void JSMockNativeCustomSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSMockNativeCustomSpan>::Declare("NativeCustomSpan");
    JSClass<JSMockNativeCustomSpan>::CustomMethod("invalidate", &JSMockNativeCustomSpan::Invalidate);
    JSClass<JSMockNativeCustomSpan>::Bind(globalObj);
}

void setAbstractPropertyFunc(Local<ObjectRef>& objRef, EcmaVM* vm)
{
    objRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "get"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockAbstractProperty::get));
    objRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "set"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockAbstractProperty::set));
    objRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "info"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockAbstractProperty::info));
}

void setSubAbstractPropertyFunc(Local<ObjectRef>& objRef, EcmaVM* vm)
{
    objRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "get"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockSubAbstractProperty::get));
    objRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "set"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockSubAbstractProperty::set));
    objRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "info"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockSubAbstractProperty::info));
    objRef->Set(vm, panda::StringRef::NewFromUtf8(vm, "aboutToBeDeleted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockSubAbstractProperty::aboutToBeDeleted));
}

Local<JSValueRef> JSMockLocalStorage::ref(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<ObjectRef> objRef = ObjectRef::New(vm);
    setAbstractPropertyFunc(objRef, vm);
    return objRef;
}

Local<JSValueRef> JSMockLocalStorage::setAndRef(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<ObjectRef> objRef = ObjectRef::New(vm);
    setAbstractPropertyFunc(objRef, vm);
    return objRef;
}

Local<JSValueRef> JSMockLocalStorage::link(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<ObjectRef> objRef = ObjectRef::New(vm);
    setSubAbstractPropertyFunc(objRef, vm);
    return objRef;
}

Local<JSValueRef> JSMockLocalStorage::setAndLink(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<ObjectRef> objRef = ObjectRef::New(vm);
    setSubAbstractPropertyFunc(objRef, vm);
    return objRef;
}

Local<JSValueRef> JSMockLocalStorage::prop(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<ObjectRef> objRef = ObjectRef::New(vm);
    setSubAbstractPropertyFunc(objRef, vm);
    return objRef;
}

Local<JSValueRef> JSMockLocalStorage::setAndProp(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<ObjectRef> objRef = ObjectRef::New(vm);
    setSubAbstractPropertyFunc(objRef, vm);
    return objRef;
}

void JSMockLocalStorage::JSBind(BindingTarget globalObj)
{
    JSClass<JSMockLocalStorage>::Declare("LocalStorage");

    JSClass<JSMockLocalStorage>::CustomMethod("has", &JSMockLocalStorage::has);
    JSClass<JSMockLocalStorage>::CustomMethod("get", &JSMockLocalStorage::get);
    JSClass<JSMockLocalStorage>::CustomMethod("set", &JSMockLocalStorage::set);
    JSClass<JSMockLocalStorage>::CustomMethod("setOrCreate", &JSMockLocalStorage::setOrCreate);
    JSClass<JSMockLocalStorage>::CustomMethod("ref", &JSMockLocalStorage::ref);
    JSClass<JSMockLocalStorage>::CustomMethod("setAndRef", &JSMockLocalStorage::setAndRef);
    JSClass<JSMockLocalStorage>::CustomMethod("link", &JSMockLocalStorage::link);
    JSClass<JSMockLocalStorage>::CustomMethod("setAndLink", &JSMockLocalStorage::setAndLink);
    JSClass<JSMockLocalStorage>::CustomMethod("prop", &JSMockLocalStorage::prop);
    JSClass<JSMockLocalStorage>::CustomMethod("setAndProp", &JSMockLocalStorage::setAndProp);
    JSClass<JSMockLocalStorage>::CustomMethod("delete", &JSMockLocalStorage::deleteKeys);
    JSClass<JSMockLocalStorage>::CustomMethod("keys", &JSMockLocalStorage::keys);
    JSClass<JSMockLocalStorage>::CustomMethod("size", &JSMockLocalStorage::size);
    JSClass<JSMockLocalStorage>::CustomMethod("clear", &JSMockLocalStorage::clear);

    JSClass<JSMockLocalStorage>::Bind(globalObj);
}

void JSMock::JSBind(BindingTarget globalObj)
{
    JSMockBaseNode::JSBind(globalObj);
    JSMockViewPU::JSBind(globalObj, "ViewPU");
    JSMockViewPU::JSBind(globalObj, "ViewV2");
    JSMockViewPU::JSBind(globalObj, "PUV2ViewBase");
    JSMockScopeUtil::JSBind(globalObj);
    MockCustomDialogController::JSBind(globalObj);
    JSMockLocalStorage::JSBind(globalObj);
    JSMockNativeCustomSpan::JSBind(globalObj);
}

void JSLoadV2Decorator(const shared_ptr<JsValue> globalPtr, const shared_ptr<JsRuntime> runtime)
{
    shared_ptr<JsValue> decoratorPtr = runtime->NewFunction(JsMockFunc::CreatFunction);
    globalPtr->SetProperty(runtime, "Provider", decoratorPtr);
    globalPtr->SetProperty(runtime, "Consumer", decoratorPtr);
    globalPtr->SetProperty(runtime, "Monitor", decoratorPtr);
    globalPtr->SetProperty(runtime, "__Type__", decoratorPtr);
}

void JSLoadPersistentStorage(const shared_ptr<JsValue> globalPtr, const shared_ptr<JsRuntime> runtime)
{
    shared_ptr<JsValue> persistObj = runtime->NewObject();
    persistObj->SetProperty(runtime, "persistProp", runtime->NewFunction(JSMockPersistStorage::persistProp));
    persistObj->SetProperty(runtime, "deleteProp", runtime->NewFunction(JSMockPersistStorage::deleteProp));
    persistObj->SetProperty(runtime, "persistProps", runtime->NewFunction(JSMockPersistStorage::persistProps));
    persistObj->SetProperty(runtime, "keys", runtime->NewFunction(JSMockPersistStorage::keys));
    globalPtr->SetProperty(runtime, "PersistentStorage", persistObj);
}

void setAbstractPropertyFunc(shared_ptr<JsValue>& Obj, const shared_ptr<JsRuntime>& runtime)
{
    Obj->SetProperty(runtime, "get", runtime->NewFunction(JSMockAppStorage::get));
    Obj->SetProperty(runtime, "set", runtime->NewFunction(JSMockAppStorage::set));
    Obj->SetProperty(runtime, "info", runtime->NewFunction(JSMockAppStorage::info));
}

void setSubAbstractPropertyFunc(shared_ptr<JsValue>& Obj, const shared_ptr<JsRuntime>& runtime)
{
    Obj->SetProperty(runtime, "get", runtime->NewFunction(JSMockAppStorage::get));
    Obj->SetProperty(runtime, "set", runtime->NewFunction(JSMockAppStorage::set));
    Obj->SetProperty(runtime, "info", runtime->NewFunction(JSMockAppStorage::info));
    Obj->SetProperty(runtime, "aboutToBeDeleted", runtime->NewFunction(JSMockAppStorage::aboutToBeDeleted));
}

shared_ptr<JsValue> JSMockAppStorage::ref(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> refImpl_ = runtime->NewObject();
    setAbstractPropertyFunc(refImpl_, runtime);
    return refImpl_;
}

shared_ptr<JsValue> JSMockAppStorage::setAndRef(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> setAndRefImpl_ = runtime->NewObject();
    setAbstractPropertyFunc(setAndRefImpl_, runtime);
    return setAndRefImpl_;
}

shared_ptr<JsValue> JSMockAppStorage::link(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> linkImpl_ = runtime->NewObject();
    setSubAbstractPropertyFunc(linkImpl_, runtime);
    return linkImpl_;
}

shared_ptr<JsValue> JSMockAppStorage::setAndLink(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> setAndLinkImpl_ = runtime->NewObject();
    setSubAbstractPropertyFunc(setAndLinkImpl_, runtime);
    return setAndLinkImpl_;
}

shared_ptr<JsValue> JSMockAppStorage::prop(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> propImpl_ = runtime->NewObject();
    setSubAbstractPropertyFunc(propImpl_, runtime);
    return propImpl_;
}

shared_ptr<JsValue> JSMockAppStorage::setAndProp(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> setAndPropImpl_ = runtime->NewObject();
    setSubAbstractPropertyFunc(setAndPropImpl_, runtime);
    return setAndPropImpl_;
}

void JSLoadAppStorage(const shared_ptr<JsValue> globalPtr, const shared_ptr<JsRuntime> runtime)
{
    shared_ptr<JsValue> appObj = runtime->NewObject();
    appObj->SetProperty(runtime, "ref", runtime->NewFunction(JSMockAppStorage::ref));
    appObj->SetProperty(runtime, "setAndRef", runtime->NewFunction(JSMockAppStorage::setAndRef));
    appObj->SetProperty(runtime, "link", runtime->NewFunction(JSMockAppStorage::link));
    appObj->SetProperty(runtime, "setAndLink", runtime->NewFunction(JSMockAppStorage::setAndLink));
    appObj->SetProperty(runtime, "prop", runtime->NewFunction(JSMockAppStorage::prop));
    appObj->SetProperty(runtime, "setAndProp", runtime->NewFunction(JSMockAppStorage::setAndProp));
    appObj->SetProperty(runtime, "has", runtime->NewFunction(JSMockAppStorage::has));
    appObj->SetProperty(runtime, "get", runtime->NewFunction(JSMockAppStorage::get));
    appObj->SetProperty(runtime, "set", runtime->NewFunction(JSMockAppStorage::set));
    appObj->SetProperty(runtime, "setOrCreate", runtime->NewFunction(JSMockAppStorage::setOrCreate));
    appObj->SetProperty(runtime, "delete", runtime->NewFunction(JSMockAppStorage::deleteKeys));
    appObj->SetProperty(runtime, "keys", runtime->NewFunction(JSMockAppStorage::keys));
    appObj->SetProperty(runtime, "clear", runtime->NewFunction(JSMockAppStorage::clear));
    appObj->SetProperty(runtime, "size", runtime->NewFunction(JSMockAppStorage::size));
    globalPtr->SetProperty(runtime, "AppStorage", appObj);
}

void JSLoadEnvironment(const shared_ptr<JsValue> globalPtr, const shared_ptr<JsRuntime> runtime)
{
    shared_ptr<JsValue> envObj = runtime->NewObject();
    envObj->SetProperty(runtime, "envProp", runtime->NewFunction(JSMockEnvironment::envProp));
    envObj->SetProperty(runtime, "envProps", runtime->NewFunction(JSMockEnvironment::envProps));
    envObj->SetProperty(runtime, "keys", runtime->NewFunction(JSMockEnvironment::keys));
    globalPtr->SetProperty(runtime, "Environment", envObj);
}

shared_ptr<JsValue> JSMockPersistenceV2::instanceFunc(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> persistV2ObjImpl = runtime->NewObject();
    persistV2ObjImpl->SetProperty(runtime, "connect", runtime->NewFunction(JSMockPersistenceV2::connect));
    persistV2ObjImpl->SetProperty(runtime, "globalConnect", runtime->NewFunction(JSMockPersistenceV2::globalConnect));
    persistV2ObjImpl->SetProperty(runtime, "remove", runtime->NewFunction(JSMockPersistenceV2::remove));
    persistV2ObjImpl->SetProperty(runtime, "keys", runtime->NewFunction(JSMockPersistenceV2::keys));
    persistV2ObjImpl->SetProperty(runtime, "save", runtime->NewFunction(JSMockPersistenceV2::save));
    persistV2ObjImpl->SetProperty(runtime, "notifyOnError", runtime->NewFunction(JSMockPersistenceV2::notifyOnError));
    return persistV2ObjImpl;
}

void JSLoadPersistenceV2(const shared_ptr<JsValue> globalPtr, const shared_ptr<JsRuntime> runtime)
{
    shared_ptr<JsValue> persistV2Obj = runtime->NewObject();
    persistV2Obj->SetProperty(runtime, "instance", runtime->NewFunction(JSMockPersistenceV2::instanceFunc));
    globalPtr->SetProperty(runtime, "PersistenceV2Impl", persistV2Obj);
}

shared_ptr<JsValue> JSMockAppStorageV2::instanceFunc(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> appV2ObjImpl = runtime->NewObject();
    appV2ObjImpl->SetProperty(runtime, "connect", runtime->NewFunction(JSMockAppStorageV2::connect));
    appV2ObjImpl->SetProperty(runtime, "remove", runtime->NewFunction(JSMockAppStorageV2::remove));
    appV2ObjImpl->SetProperty(runtime, "getMemoryKeys", runtime->NewFunction(JSMockAppStorageV2::getMemoryKeys));
    return appV2ObjImpl;
}

void JSLoadAppStorageV2(const shared_ptr<JsValue> globalPtr, const shared_ptr<JsRuntime> runtime)
{
    shared_ptr<JsValue> appV2Obj = runtime->NewObject();
    appV2Obj->SetProperty(runtime, "instance", runtime->NewFunction(JSMockAppStorageV2::instanceFunc));
    globalPtr->SetProperty(runtime, "AppStorageV2Impl", appV2Obj);
}

shared_ptr<JsValue> JSMockUIUtils::instanceFunc(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> uiUtilsObjImpl = runtime->NewObject();
    uiUtilsObjImpl->SetProperty(runtime, "getTarget", runtime->NewFunction(JSMockUIUtils::getTarget));
    uiUtilsObjImpl->SetProperty(runtime, "makeObserved", runtime->NewFunction(JSMockUIUtils::makeObserved));
    uiUtilsObjImpl->SetProperty(runtime, "makeV1Observed", runtime->NewFunction(JSMockUIUtils::makeV1Observed));
    uiUtilsObjImpl->SetProperty(runtime, "enableV2Compatibility",
        runtime->NewFunction(JSMockUIUtils::enableV2Compatibility));
    return uiUtilsObjImpl;
}

void JSLoadUiUtils(const shared_ptr<JsValue> globalPtr, const shared_ptr<JsRuntime> runtime)
{
    shared_ptr<JsValue> uiUtilsObj = runtime->NewObject();
    uiUtilsObj->SetProperty(runtime, "instance", runtime->NewFunction(JSMockUIUtils::instanceFunc));
    globalPtr->SetProperty(runtime, "UIUtilsImpl", uiUtilsObj);
}

void JSMock::JSBind(BindingTarget globalObj, const shared_ptr<JsRuntime> runtime,
    const shared_ptr<JsValue> globalPtr)
{
    auto vm = runtime->GetEcmaVm();

    //@Entry
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerNamedRoute"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::RegisterNamedRoute));
    
    // V1 Decorator
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Observed"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Observed));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Track"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Track));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Reusable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Reusable));
      
    // V2 Decorator
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ObservedV2"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::ObservedV2));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Trace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Trace));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Local"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Local));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Param"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Param));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Once"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Once));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Event"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Event));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Computed"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::Computed));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ReusableV2"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSMockDecorator::ReusableV2));
    JSLoadV2Decorator(globalPtr, runtime);
    
    // V1 global instance
    JSLoadPersistentStorage(globalPtr, runtime);
    JSLoadAppStorage(globalPtr, runtime);
    JSLoadEnvironment(globalPtr, runtime);

    // V2 global instance
    JSLoadPersistenceV2(globalPtr, runtime);
    JSLoadAppStorageV2(globalPtr, runtime);
    JSLoadUiUtils(globalPtr, runtime);
}

bool JSMock::InitModule(
    const shared_ptr<JsRuntime>& runtime, shared_ptr<JsValue>& thisObj, const std::string& moduleName)
{
    static const std::unordered_map<std::string,
        void (*)(const shared_ptr<JsRuntime>& runtime, shared_ptr<JsValue>& thisObj)>
        MODULE_LIST = {
            { "ohos.curves", [](const shared_ptr<JsRuntime>& runtime,
                                 shared_ptr<JsValue>& thisObj) { InitCurvesModule(runtime, thisObj); } },
        };
    auto iter = MODULE_LIST.find(moduleName);
    if (iter != MODULE_LIST.end()) {
        iter->second(runtime, thisObj);
        return true;
    } else {
        return false;
    }
}

shared_ptr<JsValue> MockRequireNativeModule(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string moduleName = argv[0]->ToString(runtime);

    // has already init module object
    shared_ptr<JsValue> global = runtime->GetGlobal();
    shared_ptr<JsValue> moduleObject = global->GetProperty(runtime, moduleName);
    if (moduleObject != nullptr && moduleObject->IsObject(runtime)) {
        return moduleObject;
    }

    // init module object first time
    shared_ptr<JsValue> newObject = runtime->NewObject();
    if (JSMock::InitModule(runtime, newObject, moduleName)) {
        global->SetProperty(runtime, moduleName, newObject);
        return newObject;
    }

    return runtime->NewNull();
}

bool JSMock::PreloadWorkerRequireNative(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global)
{
    return global->SetProperty(runtime, "requireNativeModule", runtime->NewFunction(MockRequireNativeModule));
}
} // namespace OHOS::Ace::Framework
