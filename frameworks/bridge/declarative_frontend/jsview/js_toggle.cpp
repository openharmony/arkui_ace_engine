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
#include <utility>

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components/button/render_button.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/toggle/toggle_component.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/button/toggle_button_view.h"
#include "core/components_ng/pattern/checkbox/checkbox_view.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/render/render_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::Framework {

void JSToggle::JSBind(BindingTarget globalObj)
{
    JSClass<JSToggle>::Declare("Toggle");
    JSClass<JSToggle>::StaticMethod("create", &JSToggle::Create);
    JSClass<JSToggle>::StaticMethod("onChange", &JSToggle::OnChange);
    JSClass<JSToggle>::StaticMethod("selectedColor", &JSToggle::SelectedColor);
    JSClass<JSToggle>::StaticMethod("width", &JSToggle::JsWidth);
    JSClass<JSToggle>::StaticMethod("height", &JSToggle::JsHeight);
    JSClass<JSToggle>::StaticMethod("size", &JSToggle::JsSize);
    JSClass<JSToggle>::StaticMethod("padding", &JSToggle::JsPadding);
    JSClass<JSToggle>::StaticMethod("switchPointColor", &JSToggle::SwitchPointColor);
    JSClass<JSToggle>::StaticMethod("backgroundColor", &JSToggle::SetBackgroundColor);

    JSClass<JSToggle>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSToggle>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSToggle>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSToggle>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSToggle>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSToggle>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSToggle>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSToggle>::Inherit<JSViewAbstract>();
    JSClass<JSToggle>::Bind(globalObj);
}

void JSToggle::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("toggle create error, info is non-valid");
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto type = paramObject->GetProperty("type");
    if (!type->IsNumber()) {
        LOGE("toggle create error, type is non-valid");
        return;
    }

    auto tempIsOn = paramObject->GetProperty("isOn");
    bool isOn = tempIsOn->IsBoolean() ? tempIsOn->ToBoolean() : false;
    auto toggleType = static_cast<ToggleType>(type->ToNumber<int32_t>());

    auto toggleTypeInt = static_cast<int32_t>(toggleType);
    if (Container::IsCurrentUseNewPipeline()) {
        switch (toggleTypeInt) {
            case 0:
                NG::CheckBoxView::Create(std::nullopt, std::nullopt, V2::CHECKBOX_ETS_TAG);
                NG::CheckBoxView::SetSelect(isOn);
                break;
            case 1:
                NG::ToggleView::Create(NG::ToggleType(toggleTypeInt), isOn);
                break;
            case 2:
                NG::ToggleButtonView::Create(V2::TOGGLE_ETS_TAG);
                NG::ToggleButtonView::SetIsOn(isOn);
                break;
            default:
                break;
        }
        return;
    }

    RefPtr<Component> component;
    if (toggleType == ToggleType::CHECKBOX) {
        RefPtr<CheckboxTheme> checkBoxTheme = GetTheme<CheckboxTheme>();
        if (!checkBoxTheme) {
            return;
        }
        RefPtr<CheckboxComponent> checkboxComponent = AceType::MakeRefPtr<OHOS::Ace::CheckboxComponent>(checkBoxTheme);
        checkboxComponent->SetValue(isOn);
        checkboxComponent->SetMouseAnimationType(HoverAnimationType::NONE);
        auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
        auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
        checkboxComponent->SetWidth(checkBoxTheme->GetWidth() - horizontalPadding * 2);
        checkboxComponent->SetHeight(checkBoxTheme->GetHeight() - verticalPadding * 2);
        component = checkboxComponent;
    } else if (toggleType == ToggleType::SWITCH) {
        RefPtr<SwitchTheme> switchTheme = GetTheme<SwitchTheme>();
        if (!switchTheme) {
            return;
        }
        RefPtr<SwitchComponent> switchComponent = AceType::MakeRefPtr<OHOS::Ace::SwitchComponent>(switchTheme);
        switchComponent->SetValue(isOn);
        switchComponent->SetMouseAnimationType(HoverAnimationType::NONE);
        auto horizontalPadding = switchTheme->GetHotZoneHorizontalPadding();
        auto verticalPadding = switchTheme->GetHotZoneVerticalPadding();
        switchComponent->SetWidth(switchTheme->GetWidth() - horizontalPadding * 2);
        switchComponent->SetHeight(switchTheme->GetHeight() - verticalPadding * 2);
        component = switchComponent;
    } else {
        RefPtr<ToggleTheme> toggleTheme = GetTheme<ToggleTheme>();
        if (!toggleTheme) {
            return;
        }
        RefPtr<ToggleComponent> toggleComponent = AceType::MakeRefPtr<ToggleComponent>();
        toggleComponent->SetBackgroundColor(toggleTheme->GetBackgroundColor());
        toggleComponent->SetCheckedColor(toggleTheme->GetCheckedColor());
        toggleComponent->SetPressedBlendColor(toggleTheme->GetPressedBlendColor());
        toggleComponent->SetCheckedState(isOn);
        component = toggleComponent;
    }

    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetDeliverMinToChild(true);
    if (toggleType == ToggleType::CHECKBOX) {
        RefPtr<CheckboxTheme> checkBoxTheme = GetTheme<CheckboxTheme>();
        if (!checkBoxTheme) {
            return;
        }
        box->SetWidth(checkBoxTheme->GetWidth());
        box->SetHeight(checkBoxTheme->GetHeight());
    } else if (toggleType == ToggleType::SWITCH) {
        RefPtr<SwitchTheme> switchTheme = GetTheme<SwitchTheme>();
        if (!switchTheme) {
            return;
        }
        box->SetWidth(switchTheme->GetWidth());
        box->SetHeight(switchTheme->GetHeight());
    } else {
        RefPtr<ToggleTheme> toggleTheme = GetTheme<ToggleTheme>();
        if (!toggleTheme) {
            return;
        }
        box->SetHeight(toggleTheme->GetHeight().Value(), toggleTheme->GetHeight().Unit());
    }
}

void JSToggle::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    JsWidth(info[0]);
}

void JSToggle::JsWidth(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsWidth(jsValue);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    Dimension padding;
    auto box = stack->GetBoxComponent();
    auto checkableComponent = AceType::DynamicCast<CheckableComponent>(stack->GetMainComponent());
    if (checkableComponent) {
        padding = checkableComponent->GetHotZoneHorizontalPadding();
        checkableComponent->SetWidth(value);
        box->SetWidth(value + padding * 2);
    }

    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    if (toggleComponent) {
        toggleComponent->SetWidth(value);
        box->SetWidth(value);
    }
}

void JSToggle::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    JsHeight(info[0]);
}

void JSToggle::JsHeight(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsHeight(jsValue);
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto box = stack->GetBoxComponent();
    Dimension padding;
    auto checkableComponent = AceType::DynamicCast<CheckableComponent>(stack->GetMainComponent());
    if (checkableComponent) {
        padding = checkableComponent->GetHotZoneVerticalPadding();
        checkableComponent->SetHeight(value);
        box->SetHeight(value + padding * 2);
    }

    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    if (toggleComponent) {
        toggleComponent->SetHeight(value);
        box->SetHeight(value);
    }
}

void JSToggle::JsSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JsWidth(sizeObj->GetProperty("width"));
    JsHeight(sizeObj->GetProperty("height"));
}

void JSToggle::OnChange(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](bool isOn) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Toggle.onChange");
            auto newJSVal = JSRef<JSVal>::Make(ToJSValue(isOn));
            func->ExecuteJS(1, &newJSVal);
        };
        NG::ToggleView::OnChange(std::move(onChange));
        return;
    }
    if (JSViewBindEvent(&ToggleComponent::SetOnChange, args) ||
        JSViewBindEvent(&CheckableComponent::SetOnChange, args)) {
    } else {
        LOGW("Failed to bind event");
    }

    args.ReturnSelf();
}

void JSToggle::SelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ToggleView::SetSelectedColor(selectedColor);
        return;
    }

    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto toggle = AceType::DynamicCast<ToggleComponent>(mainComponent);
    if (toggle) {
        toggle->SetCheckedColor(selectedColor);
        return;
    }
    auto checkable = AceType::DynamicCast<CheckableComponent>(mainComponent);
    if (checkable) {
        checkable->SetActiveColor(selectedColor);
        return;
    }
}

void JSToggle::SwitchPointColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Color color;
    if (!ParseJsColor(info[0], color)) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ToggleView::SetSwitchPointColor(color);
        return;
    }

    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto switchComponent = AceType::DynamicCast<SwitchComponent>(mainComponent);
    if (!switchComponent) {
        LOGE("pointstyle only support switch");
        return;
    }

    switchComponent->SetPointColor(color);
}

void JSToggle::JsPadding(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not a string, number or object.");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    auto box = stack->GetBoxComponent();
    if (toggleComponent) {
        JSViewAbstract::JsPadding(info);
        return;
    }
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        if (argsPtrItem->Contains("top") || argsPtrItem->Contains("bottom") || argsPtrItem->Contains("left") ||
            argsPtrItem->Contains("right")) {
            Dimension topDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension leftDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension rightDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension bottomDimen = Dimension(0.0, DimensionUnit::VP);
            ParseJsonDimensionVp(argsPtrItem->GetValue("top"), topDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("left"), leftDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("right"), rightDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("bottom"), bottomDimen);
            if (leftDimen == 0.0_vp) {
                leftDimen = rightDimen;
            }
            if (topDimen == 0.0_vp) {
                topDimen = bottomDimen;
            }
            if (leftDimen == 0.0_vp) {
                leftDimen = topDimen;
            }
            auto checkableComponent = AceType::DynamicCast<CheckableComponent>(stack->GetMainComponent());
            if (checkableComponent) {
                auto width = checkableComponent->GetWidth();
                auto height = checkableComponent->GetHeight();
                checkableComponent->SetHeight(height);
                checkableComponent->SetWidth(width);
                box->SetHeight(height + topDimen * 2);
                box->SetWidth(width + leftDimen * 2);
                checkableComponent->SetHotZoneVerticalPadding(topDimen);
                checkableComponent->SetHorizontalPadding(leftDimen);
            }
            return;
        }
    }
    Dimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        return;
    }
    auto checkableComponent = AceType::DynamicCast<CheckableComponent>(stack->GetMainComponent());
    if (checkableComponent) {
        auto width = checkableComponent->GetWidth();
        auto height = checkableComponent->GetHeight();
        checkableComponent->SetHeight(height);
        checkableComponent->SetWidth(width);
        box->SetHeight(height + length * 2);
        box->SetWidth(width + length * 2);
        checkableComponent->SetHotZoneVerticalPadding(length);
        checkableComponent->SetHorizontalPadding(length);
    }
}

void JSToggle::SetBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ToggleButtonView::SetBackgroundColor(backgroundColor);
        return;
    }
    JSViewAbstract::JsBackgroundColor(info);
}

} // namespace OHOS::Ace::Framework
