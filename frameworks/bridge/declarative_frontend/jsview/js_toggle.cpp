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

#include "frameworks/bridge/declarative_frontend/jsview/js_toggle.h"

#include <string>

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

#include "core/components/toggle/toggle_component.h"
#include "core/components/toggle/toggle_theme.h"

namespace OHOS::Ace::Framework {

void JSToggle::JSBind(BindingTarget globalObj)
{
    JSClass<JSToggle>::Declare("Toggle");
    JSClass<JSToggle>::StaticMethod("create", &JSToggle::Create);
    JSClass<JSToggle>::StaticMethod("onChange", &JSToggle::OnChange);
    JSClass<JSToggle>::StaticMethod("width", &JSToggle::JsWidth);
    JSClass<JSToggle>::StaticMethod("height", &JSToggle::JsHeight);
    JSClass<JSToggle>::Inherit<JSContainerBase>();
    JSClass<JSToggle>::Inherit<JSViewAbstract>();
    JSClass<JSToggle>::Bind(globalObj);
}

void JSToggle::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("toggle create error, info is non-vaild");
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto type = paramObject->GetProperty("type");
    if (!type->IsNumber()) {
        LOGI("toggle create error, type is non-vaild");
        return;
    }

    auto tempIsOn = paramObject->GetProperty("isOn");
    bool isOn = tempIsOn->IsBoolean() ? tempIsOn->ToBoolean() : false;
    auto toggleType = static_cast<ToggleType>(type->ToNumber<int32_t>());
    RefPtr<Component> component;
    if (toggleType == ToggleType::CHECKBOX) {
        RefPtr<CheckboxTheme> checkBoxTheme = GetTheme<CheckboxTheme>();
        RefPtr<CheckboxComponent> checkboxComponent = AceType::MakeRefPtr<OHOS::Ace::CheckboxComponent>(checkBoxTheme);
        checkboxComponent->SetValue(isOn);
        component = checkboxComponent;
    } else if (toggleType == ToggleType::SWITCH) {
        RefPtr<SwitchTheme> switchTheme = GetTheme<SwitchTheme>();
        RefPtr<SwitchComponent> switchComponent = AceType::MakeRefPtr<OHOS::Ace::SwitchComponent>(switchTheme);
        switchComponent->SetValue(isOn);
        component = switchComponent;
    } else {
        RefPtr<ToggleTheme> toggleTheme = GetTheme<ToggleTheme>();
        RefPtr<ToggleComponent> toggleComponent = AceType::MakeRefPtr<ToggleComponent>();
        toggleComponent->SetBackgroundColor(toggleTheme->GetBackgroundColor());
        toggleComponent->SetCheckedColor(toggleTheme->GetCheckedColor());
        toggleComponent->SetPressedBlendColor(toggleTheme->GetPressedBlendColor());
        toggleComponent->SetCheckedState(isOn);
        component = toggleComponent;
    }

    ViewStackProcessor::GetInstance()->Push(component);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetDeliverMinToChild(true);
    if (toggleType == ToggleType::CHECKBOX) {
        RefPtr<CheckboxTheme> checkBoxTheme = GetTheme<CheckboxTheme>();
        box->SetWidth(checkBoxTheme->GetWidth().Value(), checkBoxTheme->GetWidth().Unit());
        box->SetHeight(checkBoxTheme->GetHeight().Value(), checkBoxTheme->GetHeight().Unit());
    } else if (toggleType == ToggleType::SWITCH) {
        RefPtr<SwitchTheme> switchTheme = GetTheme<SwitchTheme>();
        box->SetWidth(switchTheme->GetWidth().Value(), switchTheme->GetWidth().Unit());
        box->SetHeight(switchTheme->GetHeight().Value(), switchTheme->GetHeight().Unit());
    } else {
        RefPtr<ToggleTheme> toggleTheme = GetTheme<ToggleTheme>();
        box->SetHeight(toggleTheme->GetHeight().Value(), toggleTheme->GetHeight().Unit());
    }
}

void JSToggle::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto checkboxComponent = AceType::DynamicCast<CheckboxComponent>(stack->GetMainComponent());
    if (checkboxComponent) {
        checkboxComponent->SetWidth(value);
    }

    auto switchComponent = AceType::DynamicCast<SwitchComponent>(stack->GetMainComponent());
    if (switchComponent) {
        switchComponent->SetWidth(value);
    }

    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    if (toggleComponent) {
        toggleComponent->SetWidth(value);
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetWidth(value);
}

void JSToggle::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }

    Dimension value;
    if (info[0]->IsNumber()) {
        value = Dimension(info[0]->ToNumber<double>(), DimensionUnit::VP);
    } else {
        value = StringUtils::StringToDimension(info[0]->ToString(), true);
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto checkboxComponent = AceType::DynamicCast<CheckboxComponent>(stack->GetMainComponent());
    if (checkboxComponent) {
        checkboxComponent->SetHeight(value);
    }

    auto switchComponent = AceType::DynamicCast<SwitchComponent>(stack->GetMainComponent());
    if (switchComponent) {
        switchComponent->SetHeight(value);
    }

    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    if (toggleComponent) {
        toggleComponent->SetHeight(value);
    }
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetHeight(value);
}

void JSToggle::OnChange(const JSCallbackInfo& args)
{
    if (JSViewBindEvent(&ToggleComponent::SetOnChange, args) ||
        JSViewBindEvent(&CheckboxComponent::SetOnChange, args)) {
    } else {
        LOGW("Failed to bind event");
    }

    args.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
