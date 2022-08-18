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
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

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
    RefPtr<AbilityComponent> component;
    auto obj = JSRef<JSObject>::Cast(info[0]);
    // Parse want
    JSRef<JSVal> wantValue = obj->GetProperty("want");
    if (wantValue->IsObject()) {
        component = AceType::MakeRefPtr<OHOS::Ace::AbilityComponent>();
        component->SetWant(wantValue->ToString());
    } else {
        RefPtr<V2::AbilityComponent> ability = AceType::MakeRefPtr<OHOS::Ace::V2::AbilityComponent>();
        auto jsonStr = JsonUtil::Create(true);
        if (obj->GetProperty("bundleName")->IsNull() || obj->GetProperty("bundleName")->IsUndefined() ||
            obj->GetProperty("abilityName")->IsNull() || obj->GetProperty("abilityName")->IsUndefined()) {
            LOGI("bundleName or abilityName is undefined");
            return;
        }
        jsonStr->Put("bundle", obj->GetProperty("bundleName")->ToString().c_str());
        jsonStr->Put("ability", obj->GetProperty("abilityName")->ToString().c_str());
        ability->SetWant(jsonStr->ToString());
        ViewStackProcessor::GetInstance()->Push(ability);
        return;
    }

    // Parse controller
    auto controllerObj = obj->GetProperty("controller");
    if (controllerObj->IsObject()) {
        auto controller = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSAbilityComponentController>();
        if (controller) {
            component->SetController(controller->GetController());
        }
    }

    ViewStackProcessor::GetInstance()->Push(component);
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
    JSViewBindEvent(&V2::AbilityComponent::SetOnConnected, info);
}

void JSAbilityComponent::JsOnDisconnect(const JSCallbackInfo& info)
{
    JSViewBindEvent(&V2::AbilityComponent::SetOnDisconnected, info);
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
    auto component = AceType::DynamicCast<V2::AbilityComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        Dimension value;
        if (!ParseJsDimensionVp(info[0], value)) {
            return;
        }
        component->SetWidth(value);
    }
}

void JSAbilityComponent::Height(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    auto component = AceType::DynamicCast<V2::AbilityComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        Dimension value;
        if (!ParseJsDimensionVp(info[0], value)) {
            return;
        }
        component->SetHeight(value);
    }
}

} // namespace OHOS::Ace::Framework
