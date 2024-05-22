/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_navrouter.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"

namespace OHOS::Ace {
std::unique_ptr<NavRouterModel> NavRouterModel::instance_ = nullptr;
std::mutex NavRouterModel::mutex_;
NavRouterModel* NavRouterModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::NavRouterModelNG());
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t NAV_ROUTE_MODE_RANGE = 2;
} // namespace

void JSNavRouter::Create(const JSCallbackInfo& info)
{
    NavRouterModel::GetInstance()->Create();
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto jsObj = JSRef<JSObject>::Cast(info[0]);
        if (jsObj->IsEmpty()) {
            return;
        }
        JSRef<JSVal> name = jsObj->GetProperty("name");
        if (name->IsEmpty()) {
            return;
        }
        if (!name->IsString()) {
            return;
        }
        JSRef<JSVal> param = jsObj->GetProperty("param");
        auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto navRouterPattern = frameNode->GetPattern<NG::NavRouterPattern>();
        CHECK_NULL_VOID(navRouterPattern);

        auto jsRouteInfo = AceType::MakeRefPtr<JSRouteInfo>();
        jsRouteInfo->SetName(name->ToString());
        jsRouteInfo->SetParam(param);
        navRouterPattern->SetRouteInfo(jsRouteInfo);
    }
}

void JSNavRouter::SetOnStateChange(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsFunction()) {
        auto onStateChangeCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onStateChange = [execCtx = info.GetExecutionContext(), func = std::move(onStateChangeCallback),
                                 node = targetNode](bool isActivated) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("OnStateChange");
            PipelineContext::SetCallBackNode(node);
            JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(isActivated));
            func->ExecuteJS(1, &param);
        };
        NavRouterModel::GetInstance()->SetOnStateChange(std::move(onStateChange));
        return;
    }
    info.ReturnSelf();
}

void JSNavRouter::SetNavRouteMode(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        return;
    }
    auto value = info[0]->ToNumber<int32_t>();
    if (value >= 0 && value <= NAV_ROUTE_MODE_RANGE) {
        NavRouterModel::GetInstance()->SetNavRouteMode(value);
    }
}

void JSNavRouter::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavRouter>::Declare("NavRouter");
    JSClass<JSNavRouter>::StaticMethod("create", &JSNavRouter::Create);
    JSClass<JSNavRouter>::StaticMethod("onStateChange", &JSNavRouter::SetOnStateChange);
    JSClass<JSNavRouter>::StaticMethod("mode", &JSNavRouter::SetNavRouteMode);
    JSClass<JSNavRouter>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSNavRouter>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSNavRouter>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSNavRouter>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSNavRouter>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNavRouter>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
