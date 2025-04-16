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

#include "bridge/declarative_frontend/jsview/js_embedded_component.h"

#include <cstdint>
#include <functional>
#include <string>

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
#include "bridge/declarative_frontend/jsview/js_ui_extension.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "frameworks/core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {

void JSEmbeddedComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSEmbeddedComponent>::Declare("EmbeddedComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSEmbeddedComponent>::StaticMethod("create", &JSEmbeddedComponent::Create, opt);
    JSClass<JSEmbeddedComponent>::StaticMethod("onTerminated", &JSEmbeddedComponent::OnTerminated);
    JSClass<JSEmbeddedComponent>::StaticMethod("onError", &JSEmbeddedComponent::OnError);
    JSClass<JSEmbeddedComponent>::StaticMethod("width", &JSEmbeddedComponent::JsWidth);
    JSClass<JSEmbeddedComponent>::StaticMethod("height", &JSEmbeddedComponent::JsHeight);
    JSClass<JSEmbeddedComponent>::StaticMethod("constraintSize", &JSEmbeddedComponent::JsConstraintSize);
    JSClass<JSEmbeddedComponent>::StaticMethod("aspectRatio", &JSEmbeddedComponent::JsAspectRatio);
    JSClass<JSEmbeddedComponent>::StaticMethod("layoutWeight", &JSEmbeddedComponent::JsLayoutWeight);
    JSClass<JSEmbeddedComponent>::StaticMethod("flexBasis", &JSEmbeddedComponent::JsFlexBasis);
    JSClass<JSEmbeddedComponent>::StaticMethod("flexGrow", &JSEmbeddedComponent::JsFlexGrow);
    JSClass<JSEmbeddedComponent>::StaticMethod("flexShrink", &JSEmbeddedComponent::JsFlexShrink);
    JSClass<JSEmbeddedComponent>::StaticMethod("opacity", &JSEmbeddedComponent::JsOpacity);
    JSClass<JSEmbeddedComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSEmbeddedComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto wantObj = JSRef<JSObject>::Cast(info[0]);
    RefPtr<OHOS::Ace::WantWrap> want = CreateWantWrapFromNapiValue(wantObj);

    NG::SessionType sessionType = NG::DEFAULT_EMBEDDED_SESSION_TYPE;
    if (info.Length() > 1 && info[1]->IsNumber()) {
        sessionType = static_cast<NG::SessionType>(info[1]->ToNumber<int32_t>());
    }

    UIExtensionModel::GetInstance()->Create(want, sessionType);
    ViewAbstractModel::GetInstance()->SetWidth(NG::EMBEDDED_COMPONENT_MIN_WIDTH);
    ViewAbstractModel::GetInstance()->SetHeight(NG::EMBEDDED_COMPONENT_MIN_HEIGHT);
    ViewAbstractModel::GetInstance()->SetMinWidth(NG::EMBEDDED_COMPONENT_MIN_WIDTH);
    ViewAbstractModel::GetInstance()->SetMinHeight(NG::EMBEDDED_COMPONENT_MIN_HEIGHT);
}

void JSEmbeddedComponent::OnTerminated(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onTerminated = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                            int32_t code, const RefPtr<WantWrap>& wantWrap) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("EmbeddedComponent.onTerminated");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        JSRef<JSObject> obj = JSRef<JSObject>::New();
        obj->SetProperty<int32_t>("code", code);
        if (wantWrap) {
            auto nativeWant =
                WantWrap::ConvertToNativeValue(wantWrap->GetWant(), reinterpret_cast<napi_env>(nativeEngine));
            auto wantJSVal = JsConverter::ConvertNapiValueToJsVal(nativeWant);
            obj->SetPropertyObject("want", wantJSVal);
        }
        auto returnValue = JSRef<JSVal>::Cast(obj);
        func->ExecuteJS(1, &returnValue);
    };
    UIExtensionModel::GetInstance()->SetOnTerminated(std::move(onTerminated));
}

void JSEmbeddedComponent::OnError(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                       int32_t code, const std::string& name, const std::string& message) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("EmbeddedComponent.onError");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        JSRef<JSObject> obj = JSRef<JSObject>::New();
        obj->SetProperty<int32_t>("code", code);
        obj->SetProperty<std::string>("name", name);
        obj->SetProperty<std::string>("message", message);
        auto returnValue = JSRef<JSVal>::Cast(obj);
        func->ExecuteJS(FUNC_ARGC_1, &returnValue);
    };
    UIExtensionModel::GetInstance()->SetOnError(std::move(onError));
}

void JSEmbeddedComponent::JsWidth(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        return;
    }

    CalcDimension value;
    if (JSViewAbstract::ParseJsDimensionVpNG(info[0], value)) {
        ViewAbstractModel::GetInstance()->SetWidth(value);
    }
}

void JSEmbeddedComponent::JsHeight(const JSCallbackInfo& info)
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
