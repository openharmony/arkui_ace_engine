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

#include "frameworks/bridge/declarative_frontend/jsview/js_tabs.h"

#include "base/log/ace_trace.h"
#include "core/components/tab_bar/tab_bar_component.h"
#include "core/components/tab_bar/tab_content_component.h"
#include "core/components/tab_bar/tab_controller.h"
#include "core/components/tab_bar/tabs_component.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr double DEFAULT_TAB_BAR_WIDTH = 200;
constexpr double DEFAULT_TAB_BAR_HEIGHT = 56;
const std::vector<BarPosition> BAR_POSITIONS = { BarPosition::START, BarPosition::END };

JSRef<JSVal> TabContentChangeEventToJSValue(const TabContentChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetIndex()));
}

} // namespace

void JSTabs::SetOnChange(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto changeHandler = AceType::MakeRefPtr<JsEventFunction<TabContentChangeEvent, 1>>(
            JSRef<JSFunc>::Cast(args[0]), TabContentChangeEventToJSValue);
        auto onChange = EventMarker([executionContext = args.GetExecutionContext(), func = std::move(changeHandler)](
                                        const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE(executionContext);
            auto TabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
            if (!TabsInfo) {
                LOGE("HandleChangeEvent TabsInfo == nullptr");
                return;
            }
            func->Execute(*TabsInfo);
        });
        auto component = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (component) {
            auto tabContent = component->GetTabContentChild();
            if (tabContent) {
                tabContent->SetChangeEventId(onChange);
            }
        }
    }
    args.ReturnSelf();
}

void JSTabs::Create(const JSCallbackInfo& info)
{
    BarPosition barVal = BarPosition::START;
    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> val = obj->GetProperty("barPosition");
        if (val->IsNumber()) {
            auto barPositionVal = val->ToNumber<int32_t>();
            if (barPositionVal >= 0 && barPositionVal < static_cast<int32_t>(BAR_POSITIONS.size())) {
                barVal = BAR_POSITIONS[barPositionVal];
            }
        }
    }
    std::list<RefPtr<Component>> children;
    RefPtr<TabsComponent> tabsComponent = AceType::MakeRefPtr<OHOS::Ace::TabsComponent>(FlexDirection::COLUMN,
        FlexAlign::FLEX_START, FlexAlign::CENTER, children, barVal);
    auto tabBar = tabsComponent->GetTabBarChild();
    if (tabBar) {
        auto box = AceType::DynamicCast<BoxComponent>(tabBar->GetParent().Upgrade());
        if (box) {
            box->SetWidth(DEFAULT_TAB_BAR_WIDTH, DimensionUnit::VP);
            box->SetHeight(DEFAULT_TAB_BAR_HEIGHT, DimensionUnit::VP);
        }
    }
    ViewStackProcessor::GetInstance()->Push(tabsComponent);
}

void JSTabs::SetIndex(const std::string& value)
{
    auto component = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        return;
    }
    auto tabsController = component->GetTabsController();
    if (tabsController) {
        tabsController->SetIndex(std::max(0, StringUtils::StringToInt(value)));
        component->SetTabsController(tabsController);
    }
}

void JSTabs::SetVertical(const std::string& value)
{
    auto tabsComponent = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!tabsComponent) {
        return;
    }
    bool isVertical = StringToBool(value);
    if (isVertical) {
        tabsComponent->SetDirection(FlexDirection::ROW);
    } else {
        tabsComponent->SetDirection(FlexDirection::COLUMN);
    }
    auto tabBar = tabsComponent->GetTabBarChild();
    if (tabBar) {
        tabBar->SetVertical(isVertical);
    }
    auto tabContent = tabsComponent->GetTabContentChild();
    if (tabContent) {
        tabContent->SetVertical(isVertical);
    }
}

void JSTabs::SetScrollable(const std::string& value)
{
    auto component = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        return;
    }
    auto tabContent = component->GetTabContentChild();
    if (tabContent) {
        tabContent->SetScrollable(StringToBool(value));
    }
}

void JSTabs::SetBarMode(const std::string& value)
{
    auto component = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        return;
    }
    auto tabBar = component->GetTabBarChild();
    if (tabBar) {
        tabBar->SetMode(ConvertStrToTabBarMode(value));
    }
}

void JSTabs::SetBarWidth(double width)
{
    auto component = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        return;
    }
    auto tabBar = component->GetTabBarChild();
    if (tabBar) {
        auto box = AceType::DynamicCast<BoxComponent>(tabBar->GetParent().Upgrade());
        if (box) {
            box->SetWidth(width, DimensionUnit::VP);
        }
    }
}

void JSTabs::SetBarHeight(double height)
{
    auto component = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        return;
    }
    auto tabBar = component->GetTabBarChild();
    if (tabBar) {
        auto box = AceType::DynamicCast<BoxComponent>(tabBar->GetParent().Upgrade());
        if (box) {
            box->SetHeight(height, DimensionUnit::VP);
        }
    }
}

void JSTabs::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabs>::Declare("Tabs");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTabs>::StaticMethod("create", &JSTabs::Create, opt);
    JSClass<JSTabs>::StaticMethod("index", &JSTabs::SetIndex, opt);
    JSClass<JSTabs>::StaticMethod("vertical", &JSTabs::SetVertical, opt);
    JSClass<JSTabs>::StaticMethod("scrollable", &JSTabs::SetScrollable, opt);
    JSClass<JSTabs>::StaticMethod("barMode", &JSTabs::SetBarMode, opt);
    JSClass<JSTabs>::StaticMethod("barWidth", &JSTabs::SetBarWidth, opt);
    JSClass<JSTabs>::StaticMethod("barHeight", &JSTabs::SetBarHeight, opt);
    JSClass<JSTabs>::StaticMethod("onChange", &JSTabs::SetOnChange);
    JSClass<JSTabs>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabs>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabs>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabs>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabs>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabs>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabs>::Inherit<JSContainerBase>();
    JSClass<JSTabs>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
