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

void JSMockViewBuildNodeBase::JSBind(BindingTarget globalObj)
{
    JSClass<JSMockViewBuildNodeBase>::Declare("ViewBuildNodeBase");

    JSClass<JSMockViewBuildNodeBase>::StaticMethod(
        "setArkThemeScopeManager", &JSMockViewBuildNodeBase::SetArkThemeScopeManager);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod("id__", &JSMockViewBuildNodeBase::Id);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod("debugInfo__", &JSMockViewBuildNodeBase::DebugInfo);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod("debugInfoElmtId", &JSMockViewBuildNodeBase::DebugInfoElmtId);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod("getChildById", &JSMockViewBuildNodeBase::GetChildById);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod("addChild", &JSMockViewBuildNodeBase::AddChild);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod(
        "purgeDeletedElmtIds", &JSMockViewBuildNodeBase::PurgeDeletedElmtIds);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod(
        "updateStateVarsOfChildByElmtId", &JSMockViewBuildNodeBase::UpdateStateVarsOfChildByElmtId);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod("createOrGetNode", &JSMockViewBuildNodeBase::CreateOrGetNode);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod(
        "ifElseBranchUpdateFunction", &JSMockViewBuildNodeBase::IfElseBranchUpdateFunction);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod(
        "onWillApplyThemeInternally", &JSMockViewBuildNodeBase::OnWillApplyThemeInternally);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod("onWillApplyTheme", &JSMockViewBuildNodeBase::OnWillApplyTheme);
    JSClass<JSMockViewBuildNodeBase>::CustomMethod(
        "onGlobalThemeChanged", &JSMockViewBuildNodeBase::OnGlobalThemeChanged);

    JSClass<JSMockViewBuildNodeBase>::Bind(
        globalObj, JSMockViewBuildNodeBase::ConstructorCallback, JSMockViewBuildNodeBase::DestructorCallback);
}

void JSMock::JSBind(BindingTarget globalObj)
{
    JSMockBaseNode::JSBind(globalObj);
    JSMockViewPU::JSBind(globalObj, "ViewPU");
    JSMockViewPU::JSBind(globalObj, "PUV2ViewBase");
    JSMockScopeUtil::JSBind(globalObj);
    MockCustomDialogController::JSBind(globalObj);
    JSMockNativeCustomSpan::JSBind(globalObj);
    JSMockViewBuildNodeBase::JSBind(globalObj);
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
