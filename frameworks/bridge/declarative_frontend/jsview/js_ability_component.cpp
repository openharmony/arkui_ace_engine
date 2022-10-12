/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component.h"

#include "frameworks/base/json/json_util.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_ability_component_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/ability_component_model_impl.h"
#include "frameworks/core/components_ng/pattern/ability_component/ability_component_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<AbilityComponentModel> AbilityComponentModel::instance_ = nullptr;

AbilityComponentModel* AbilityComponentModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::AbilityComponentModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::AbilityComponentModelNG());
        } else {
            instance_.reset(new Framework::AbilityComponentModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSAbilityComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSAbilityComponent>::Declare("AbilityComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSAbilityComponent>::StaticMethod("create", &JSAbilityComponent::Create, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onReady", &JSAbilityComponent::JsOnReady, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onDestroy", &JSAbilityComponent::JsOnDestroy, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onAbilityCreated", &JSAbilityComponent::JsOnAbilityCreated, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onAbilityMoveToFront", &JSAbilityComponent::JsOnAbilityMovedFront, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onAbilityWillRemove", &JSAbilityComponent::JsOnAbilityWillRemove, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onConnect", &JSAbilityComponent::JsOnConnect, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onDisconnect", &JSAbilityComponent::JsOnDisconnect, opt);
    JSClass<JSAbilityComponent>::StaticMethod("width", &JSAbilityComponent::Width, opt);
    JSClass<JSAbilityComponent>::StaticMethod("height", &JSAbilityComponent::Height, opt);
    JSClass<JSAbilityComponent>::Inherit<JSViewAbstract>();
    JSClass<JSAbilityComponent>::Bind<>(globalObj);
}

void JSAbilityComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    // Parse want
    JSRef<JSVal> wantValue = obj->GetProperty("want");
    if (wantValue->IsObject()) {
        AbilityComponentModel::GetInstance()->Create();
        AbilityComponentModel::GetInstance()->SetWant(wantValue->ToString());
    } else {
        auto jsonStr = JsonUtil::Create(true);
        if (obj->GetProperty("bundleName")->IsNull() || obj->GetProperty("bundleName")->IsUndefined() ||
            obj->GetProperty("abilityName")->IsNull() || obj->GetProperty("abilityName")->IsUndefined()) {
            LOGI("bundleName or abilityName is undefined");
            return;
        }
        jsonStr->Put("bundleName", obj->GetProperty("bundleName")->ToString().c_str());
        jsonStr->Put("abilityName", obj->GetProperty("abilityName")->ToString().c_str());
        AbilityComponentModel::GetInstance()->Create();
        AbilityComponentModel::GetInstance()->SetWant(jsonStr->ToString());
    }
}

void JSAbilityComponent::JsOnReady(const JSCallbackInfo& info)
{
    JSViewBindEvent(&AbilityComponent::SetOnReady, info);
}

void JSAbilityComponent::JsOnDestroy(const JSCallbackInfo& info)
{
    JSViewBindEvent(&AbilityComponent::SetOnDestroy, info);
}

void JSAbilityComponent::JsOnConnect(const JSCallbackInfo& info)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onConnect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("AbilityComponent.onConnect");
        auto newJSVal = JSRef<JSVal>::Make();
        func->ExecuteJS(1, &newJSVal);
    };
    AbilityComponentModel::GetInstance()->SetOnConnect(std::move(onConnect));
}

void JSAbilityComponent::JsOnDisconnect(const JSCallbackInfo& info)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onDisConnect = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("AbilityComponent.onDisConnect");
        auto newJSVal = JSRef<JSVal>::Make();
        func->ExecuteJS(1, &newJSVal);
    };
    AbilityComponentModel::GetInstance()->SetOnDisConnect(std::move(onDisConnect));
}

void JSAbilityComponent::JsOnAbilityCreated(const JSCallbackInfo& info)
{
    JSViewBindEvent(&AbilityComponent::SetOnAbilityCreated, info);
}

void JSAbilityComponent::JsOnAbilityMovedFront(const JSCallbackInfo& info)
{
    JSViewBindEvent(&AbilityComponent::SetOnAbilityMovedFront, info);
}

void JSAbilityComponent::JsOnAbilityWillRemove(const JSCallbackInfo& info)
{
    JSViewBindEvent(&AbilityComponent::SetOnAbilityWillRemove, info);
}

void JSAbilityComponent::Width(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    AbilityComponentModel::GetInstance()->SetWidth(value);
}

void JSAbilityComponent::Height(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    AbilityComponentModel::GetInstance()->SetHeight(value);
}

} // namespace OHOS::Ace::Framework
