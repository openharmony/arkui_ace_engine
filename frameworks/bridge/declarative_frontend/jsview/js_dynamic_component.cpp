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

#include "bridge/declarative_frontend/jsview/js_dynamic_component.h"

#include <functional>
#include <string>

#include "commonlibrary/ets_utils/js_concurrent_module/worker/worker.h"
#include "jsnapi.h"
#include "native_engine.h"

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
    JSClass<JSDynamicComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSDynamicComponent::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        LOGW("DynamicComponent arg is invalid");
        return;
    }
    auto dynamicComponentArg = JSRef<JSObject>::Cast(info[0]);
    auto hapPath = dynamicComponentArg->GetProperty("hapPath");
    if (!hapPath->IsString()) {
        LOGW("hap path is invalid");
        return;
    }
    auto abcPath = dynamicComponentArg->GetProperty("abcPath");
    if (!abcPath->IsString()) {
        LOGW("abc path is invalid");
        return;
    }
    auto entryPoint = dynamicComponentArg->GetProperty("entryPoint");
    if (!entryPoint->IsString()) {
        LOGW("entry point is invalid");
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
    LOGD("worker running=%{public}d,  worker name=%{public}s", worker->IsRunning(), worker->GetName().c_str());
    auto hapPathStr = hapPath->ToString();
    auto abcPathStr = abcPath->ToString();
    auto entryPointStr = entryPoint->ToString();

    UIExtensionModel::GetInstance()->Create();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto instanceId = Container::CurrentId();

    worker->RegisterCallbackForWorkerEnv([instanceId, weak = AceType::WeakClaim(AceType::RawPtr(frameNode)), hapPathStr,
                                             abcPathStr, entryPointStr](napi_env env) {
        ContainerScope scope(instanceId);
        auto container = Container::Current();
        container->GetTaskExecutor()->PostTask(
            [weak, hapPathStr, abcPathStr, entryPointStr, env]() {
                auto frameNode = weak.Upgrade();
                CHECK_NULL_VOID(frameNode);
                UIExtensionModel::GetInstance()->InitializeDynamicComponent(
                    frameNode, hapPathStr, abcPathStr, entryPointStr, env);
            },
            TaskExecutor::TaskType::UI);
    });
}
} // namespace OHOS::Ace::Framework
