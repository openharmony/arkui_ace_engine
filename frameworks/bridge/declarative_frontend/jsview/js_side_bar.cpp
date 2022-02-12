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

#include "frameworks/bridge/declarative_frontend/jsview/js_side_bar.h"

#include "base/geometry/dimension.h"
#include "core/components/button/button_component.h"
#include "core/components/side_bar/render_side_bar_container.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void JSSideBar::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
    }

    if (!info[0]->IsObject()) {
        LOGE("The arg is wrong, it is supposed to be an object");
    }

    std::list<RefPtr<Component>> children;
    auto sideBarContainer = AceType::MakeRefPtr<OHOS::Ace::SideBarContainerComponent>(children);
    sideBarContainer->SetMainStackSize(MainStackSize::MAX);

    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> showValue = obj->GetProperty("showSideBarContainer");
        JSRef<JSVal> styleValue = obj->GetProperty("style");
        JSRef<JSVal> btnAtt = obj->GetProperty("buttonAttr");

        SetButtonAttribute(btnAtt, sideBarContainer);

        if (!styleValue->IsNull() && styleValue->IsNumber()) {
            SideBarContainerStyle style = static_cast<SideBarContainerStyle>(styleValue->ToNumber<int>());
            sideBarContainer->SetSideBarContainerStyle(style);
        }

        if (!showValue->IsNull() && showValue->IsBoolean()) {
            sideBarContainer->SetShowSideBar(showValue->ToBoolean());
        }
    }
    auto stack = ViewStackProcessor::GetInstance();

    stack->Push(sideBarContainer);
    JSInteractableView::SetFocusNode(true);
}

void JSSideBar::SetShowControlButton(bool isShow)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }

    component->SetShowControlButton(isShow);
}

void JSSideBar::JSBind(BindingTarget globalObj)
{
    JSClass<JSSideBar>::Declare("SideBarContainer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSideBar>::StaticMethod("create", &JSSideBar::Create, opt);
    JSClass<JSSideBar>::StaticMethod("showControlButton", &JSSideBar::SetShowControlButton);
    JSClass<JSSideBar>::StaticMethod("onChange", &JSSideBar::OnChange);
    JSClass<JSSideBar>::StaticMethod("sideBarWidth", &JSSideBar::JsSideBarWidth);
    JSClass<JSSideBar>::StaticMethod("minSideBarWidth", &JSSideBar::JsMinSideBarWidth);
    JSClass<JSSideBar>::StaticMethod("maxSideBarWidth", &JSSideBar::JsMaxSideBarWidth);
    JSClass<JSSideBar>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSideBar>::StaticMethod("width", SetWidth);
    JSClass<JSSideBar>::StaticMethod("height", SetHeight);
    JSClass<JSSideBar>::StaticMethod("size", SetSize);
    JSClass<JSSideBar>::StaticMethod("width", &JSStack::SetWidth);
    JSClass<JSSideBar>::StaticMethod("height", &JSStack::SetHeight);
    JSClass<JSSideBar>::StaticMethod("size", &JSStack::SetSize);
    JSClass<JSSideBar>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSideBar>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSideBar>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSideBar>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSideBar>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSideBar>::Inherit<JSContainerBase>();
    JSClass<JSSideBar>::Inherit<JSViewAbstract>();
    JSClass<JSSideBar>::Bind(globalObj);
}

void JSSideBar::OnChange(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&SideBarContainerComponent::SetOnChange, info)) {
        LOGE("Failed to bind event");
    }
    info.ReturnSelf();
}

void JSSideBar::JsSideBarWidth(double length)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }
    component->SetSideBarWidth(Dimension(length, DimensionUnit::VP));
}

void JSSideBar::JsMaxSideBarWidth(double length)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }
    component->SetSideBarMaxWidth(Dimension(length, DimensionUnit::VP));
}

void JSSideBar::JsMinSideBarWidth(double length)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::SideBarContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("side bar is null");
        return;
    }
    component->SetSideBarMinWidth(Dimension(length, DimensionUnit::VP));
}

void JSSideBar::SetButtonAttribute(const JSRef<JSVal>& btnAtt,
                                   OHOS::Ace::RefPtr<OHOS::Ace::SideBarContainerComponent>& sidebar)
{
    if (!btnAtt->IsNull() && btnAtt->IsObject()) {
        JSRef<JSObject> value = JSRef<JSObject>::Cast(btnAtt);
        JSRef<JSVal> width = value->GetProperty("width");
        JSRef<JSVal> height = value->GetProperty("height");
        JSRef<JSVal> left = value->GetProperty("left");
        JSRef<JSVal> top = value->GetProperty("top");
        JSRef<JSVal> icons = value->GetProperty("icons");

        if (!width->IsNull() && width->IsNumber()) {
            sidebar->SetButtonWidth(width->ToNumber<double>());
        }

        if (!height->IsNull() && height->IsNumber()) {
            sidebar->SetButtonHeight(height->ToNumber<double>());
        }

        if (!left->IsNull() && left->IsNumber()) {
            sidebar->SetButtonLeft(left->ToNumber<double>());
        }

        if (!top->IsNull() && top->IsNumber()) {
            sidebar->SetButtonTop(top->ToNumber<double>());
        }

        if (!icons->IsNull() && icons->IsObject()) {
            JSRef<JSObject> iconsVal = JSRef<JSObject>::Cast(icons);
            JSRef<JSVal> showIcon = iconsVal->GetProperty("shown");
            JSRef<JSVal> switchingIcon = iconsVal->GetProperty("switching");
            JSRef<JSVal> hiddenIcon = iconsVal->GetProperty("hidden");
            std::string showIconStr;
            if (!showIcon->IsNull() && ParseJsMedia(showIcon, showIconStr)) {
                sidebar->SetShowIcon(showIconStr);
            }
            std::string hiddenIconStr;
            if (!hiddenIcon->IsNull() && ParseJsMedia(hiddenIcon, hiddenIconStr)) {
                sidebar->SetHiddenIcon(hiddenIconStr);
            }
            std::string switchingIconStr;
            if (!switchingIcon->IsNull() && ParseJsMedia(switchingIcon, switchingIconStr)) {
                sidebar->SetSwitchIcon(switchingIconStr);
            }
        }
    }
}

} // namespace OHOS::Ace::Framework