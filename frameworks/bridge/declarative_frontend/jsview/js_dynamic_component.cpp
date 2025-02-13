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

#include "worker.h"
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
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_model.h"

using namespace Commonlibrary::Concurrent::WorkerModule;
namespace OHOS::Ace {
NG::DynamicModelNG* NG::DynamicModelNG::GetInstance()
{
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGE("Get DynamicModelNG in non NewPipeline.");
    }
    static NG::DynamicModelNG instance;
    return &instance;
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
const CalcDimension DYNAMIC_COMPONENT_MIN_WIDTH(10.0f, DimensionUnit::VP);
const CalcDimension DYNAMIC_COMPONENT_MIN_HEIGHT(10.0f, DimensionUnit::VP);

void JSDynamicComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSDynamicComponent>::Declare("DynamicComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSDynamicComponent>::StaticMethod("create", &JSDynamicComponent::Create, opt);
    JSClass<JSDynamicComponent>::StaticMethod("onSizeChanged", &JSDynamicComponent::SetOnSizeChanged, opt);
    JSClass<JSDynamicComponent>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSDynamicComponent>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSDynamicComponent>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSDynamicComponent>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSDynamicComponent>::StaticMethod("width", &JSDynamicComponent::Width, opt);
    JSClass<JSDynamicComponent>::StaticMethod("height", &JSDynamicComponent::Height, opt);
    JSClass<JSDynamicComponent>::StaticMethod("onError", &JSDynamicComponent::JsOnError, opt);
    JSClass<JSDynamicComponent>::StaticMethod("isReportFrameEvent",
        &JSDynamicComponent::SetIsReportFrameEvent, opt);
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
    auto backgroundTransparentValue = dynamicComponentArg->GetProperty("backgroundTransparent");
    if (!entryPointValue->IsString()) {
        TAG_LOGW(AceLogTag::ACE_DYNAMIC_COMPONENT, "DynamicComponent argument type is invalid");
        return;
    }
    auto entryPoint = entryPointValue->ToString();
    bool backgroundTransparent = true;
    if (backgroundTransparentValue->IsBoolean()) {
        backgroundTransparent = backgroundTransparentValue->ToBoolean();
    }
    NG::UIExtensionConfig config;
    config.sessionType = NG::SessionType::DYNAMIC_COMPONENT;
    config.backgroundTransparent = backgroundTransparent;
    NG::DynamicModelNG::GetInstance()->Create(config);
    ViewAbstractModel::GetInstance()->SetWidth(DYNAMIC_COMPONENT_MIN_WIDTH);
    ViewAbstractModel::GetInstance()->SetHeight(DYNAMIC_COMPONENT_MIN_HEIGHT);
    ViewAbstractModel::GetInstance()->SetMinWidth(DYNAMIC_COMPONENT_MIN_WIDTH);
    ViewAbstractModel::GetInstance()->SetMinHeight(DYNAMIC_COMPONENT_MIN_HEIGHT);
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto hostEngine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(hostEngine);
    NativeEngine* hostNativeEngine = hostEngine->GetNativeEngine();
    auto jsWorker = dynamicComponentArg->GetProperty("worker");
    panda::Local<JsiValue> value = jsWorker.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value nativeValue = hostNativeEngine->ValueToNapiValue(valueWrapper);
    Worker* worker = nullptr;
    napi_unwrap(reinterpret_cast<napi_env>(hostNativeEngine), nativeValue, reinterpret_cast<void**>(&worker));
    if (worker == nullptr) {
        TAG_LOGE(AceLogTag::ACE_DYNAMIC_COMPONENT, "worker is nullptr");
        NG::DynamicModelNG::GetInstance()->InitializeDynamicComponent(
            AceType::Claim(frameNode), "", "", entryPoint, nullptr);
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "worker running=%{public}d, worker name=%{public}s",
        worker->IsRunning(), worker->GetName().c_str());
    auto instanceId = Container::CurrentId();
    worker->RegisterCallbackForWorkerEnv([instanceId,
        weak = AceType::WeakClaim(frameNode), entryPoint](napi_env env) {
        ContainerScope scope(instanceId);
        auto container = Container::Current();
        container->GetTaskExecutor()->PostTask(
            [weak, entryPoint, env]() {
                auto frameNode = weak.Upgrade();
                CHECK_NULL_VOID(frameNode);
                NG::DynamicModelNG::GetInstance()->InitializeDynamicComponent(
                    frameNode, "", "", entryPoint, env);
            },
            TaskExecutor::TaskType::UI, "ArkUIDynamicComponentInitialize");
    });
}

void JSDynamicComponent::SetIsReportFrameEvent(const JSCallbackInfo& info)
{
    bool isReportFrameEvent = false;
    if (info[0]->IsBoolean()) {
        isReportFrameEvent = info[0]->ToBoolean();
    }

    NG::DynamicModelNG::GetInstance()->SetIsReportFrameEvent(isReportFrameEvent);
}

void JSDynamicComponent::JsOnError(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_ISOLATED_COMPONENT, "onError argument is invalid");
        return;
    }

    WeakPtr<NG::FrameNode> frameNode =
        AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto execCtx = info.GetExecutionContext();
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = Container::CurrentId();
    auto onError = [execCtx, func = std::move(jsFunc), instanceId, node = frameNode]
        (int32_t code, const std::string& name, const std::string& message) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("DynamicComponent.onError");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            JSRef<JSObject> obj = JSRef<JSObject>::New();
            obj->SetProperty<int32_t>("code", code);
            obj->SetProperty<std::string>("name", name);
            obj->SetProperty<std::string>("message", message);
            auto returnValue = JSRef<JSVal>::Cast(obj);
            func->ExecuteJS(1, &returnValue);
        };
    NG::DynamicModelNG::GetInstance()->SetPlatformOnError(std::move(onError));
}

void JSDynamicComponent::SetOnSizeChanged(const JSCallbackInfo& info)
{
}

void JSDynamicComponent::Width(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        return;
    }

    CalcDimension value;
    if (JSViewAbstract::ParseJsDimensionVpNG(info[0], value)) {
        ViewAbstractModel::GetInstance()->SetWidth(value);
    }
}

void JSDynamicComponent::Height(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        return;
    }

    CalcDimension value;
    if (JSViewAbstract::ParseJsDimensionVpNG(info[0], value)) {
        ViewAbstractModel::GetInstance()->SetHeight(value);
    }
}
} // namespace OHOS::Ace::Framework
