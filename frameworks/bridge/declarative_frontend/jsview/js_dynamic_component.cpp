/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_dynamic_component.h"

#include <cstdint>
#include <functional>
#include <string>

#include "commonlibrary/ets_utils/js_concurrent_module/worker/worker.h"
#include "jsnapi.h"
#include "native_engine.h"

#include "base/log/ace_scoring_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_ref.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"

using namespace Commonlibrary::Concurrent::WorkerModule;

namespace OHOS::Ace::Framework {

void JSDynamicComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSDynamicComponent>::Declare("DynamicComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSDynamicComponent>::StaticMethod("create", &JSDynamicComponent::Create, opt);
    JSClass<JSDynamicComponent>::StaticMethod("onSizeChanged", &JSDynamicComponent::SetOnSizeChanged, opt);
    JSClass<JSDynamicComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSDynamicComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "DynamicComponent argument is invalid");
        return;
    }
    auto dynamicComponentArg = JSRef<JSObject>::Cast(info[0]);
    auto hapPathValue = dynamicComponentArg->GetProperty("hapPath");
    auto abcPathValue = dynamicComponentArg->GetProperty("abcPath");
    auto entryPointValue = dynamicComponentArg->GetProperty("entryPoint");
    if (!hapPathValue->IsString() || !abcPathValue->IsString() || !entryPointValue->IsString()) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "DynamicComponent argument type is invalid");
        return;
    }

    auto hostEngine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(hostEngine);
    NativeEngine* hostNativeEngine = hostEngine->GetNativeEngine();
    auto jsWorker = dynamicComponentArg->GetProperty("worker");
    panda::Local<JsiValue> value = jsWorker.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value nativeValue = hostNativeEngine->ValueToNapiValue(valueWrapper);
    Worker* worker = nullptr;
    napi_unwrap(reinterpret_cast<napi_env>(hostNativeEngine), nativeValue, reinterpret_cast<void**>(&worker));
    TAG_LOGD(AceLogTag::ACE_DYNAMIC_COMPONENT, "worker running=%{public}d,  worker name=%{public}s",
        worker->IsRunning(), worker->GetName().c_str());
    auto hapPath = hapPathValue->ToString();
    auto abcPath = abcPathValue->ToString();
    auto entryPoint = entryPointValue->ToString();

    UIExtensionModel::GetInstance()->Create();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();

    worker->RegisterCallbackForWorkerEnv([instanceId, weak = AceType::WeakClaim(AceType::RawPtr(frameNode)), hapPath,
                                             abcPath, entryPoint](napi_env env) {
        ContainerScope scope(instanceId);
        auto container = Container::Current();
        container->GetTaskExecutor()->PostTask(
            [weak, hapPath, abcPath, entryPoint, env]() {
                auto frameNode = weak.Upgrade();
                CHECK_NULL_VOID(frameNode);
                UIExtensionModel::GetInstance()->InitializeDynamicComponent(
                    frameNode, hapPath, abcPath, entryPoint, env);
            },
            TaskExecutor::TaskType::UI);
    });
}

void JSDynamicComponent::SetOnSizeChanged(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "OnSizeChanged argument is invalid");
        return;
    }
    auto execCtx = info.GetExecutionContext();
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onCardSizeChanged = [execCtx, func = std::move(jsFunc)](int32_t width, int32_t height) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("DynamicComponent.onSizeChanged");
        JSRef<JSObject> obj = JSRef<JSObject>::New();
        obj->SetProperty<int32_t>("width", width);
        obj->SetProperty<int32_t>("height", height);
        auto returnValue = JSRef<JSVal>::Cast(obj);
        func->ExecuteJS(1, &returnValue);
    };
    UIExtensionModel::GetInstance()->SetOnSizeChanged(std::move(onCardSizeChanged));
}
} // namespace OHOS::Ace::Framework
