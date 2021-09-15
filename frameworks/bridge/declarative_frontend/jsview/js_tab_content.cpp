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

#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"

#include "base/log/ace_trace.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components/padding/padding_component.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr Dimension DEFAULT_SMALL_TEXT_FONT_SIZE = 10.0_fp;
constexpr Dimension DEFAULT_SMALL_IMAGE_WIDTH = 24.0_vp;
constexpr Dimension DEFAULT_SMALL_IMAGE_HEIGHT = 26.0_vp;
constexpr Dimension DEFAULT_SINGLE_TEXT_FONT_SIZE = 16.0_fp;
constexpr Dimension DEFAULT_SINGLE_IMAGE_SIZE = 32.0_vp;
constexpr char DEFAULT_TAB_BAR_NAME[] = "TabBar";

} // namespace

void JSTabContent::Create()
{
    auto component = AceType::DynamicCast<TabsComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (component) {
        auto tabBar = component->GetTabBarChild();
        std::list<RefPtr<Component>> components;
        auto tabContentItemComponent =
            AceType::MakeRefPtr<TabContentItemComponent>(components);
        tabContentItemComponent->SetCrossAxisSize(CrossAxisSize::MAX);
        tabContentItemComponent->SetTabsComponent(AceType::WeakClaim(AceType::RawPtr(component)));
        auto text = AceType::MakeRefPtr<TextComponent>(DEFAULT_TAB_BAR_NAME);
        auto textStyle = text->GetTextStyle();
        textStyle.SetFontSize(DEFAULT_SINGLE_TEXT_FONT_SIZE);
        text->SetTextStyle(textStyle);
        tabBar->AppendChild(text);
        ViewStackProcessor::GetInstance()->Push(tabContentItemComponent);
    }
}

void JSTabContent::SetTabBar(const JSCallbackInfo& info)
{
    auto tabContentItemComponent =
        AceType::DynamicCast<OHOS::Ace::TabContentItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!tabContentItemComponent) {
        return;
    }
    auto tabs = tabContentItemComponent->GetTabsComponent();
    ProcessTabBarData(tabs, tabContentItemComponent, info);
}

void JSTabContent::ProcessTabBarData(const WeakPtr<TabsComponent>& weakTabs,
    const RefPtr<TabContentItemComponent>& tabContentItem, const JSCallbackInfo& info)
{
    auto tabs = weakTabs.Upgrade();
    if (!tabs) {
        return;
    }
    auto tabBar = tabs->GetTabBarChild();
    if (!tabBar) {
        return;
    }
    auto text = AceType::DynamicCast<TextComponent>(tabBar->GetChildren().back());
    if (!text) {
        return;
    }
    if (info[0]->IsString()) {
        std::string infoStr = info[0]->ToString();
        text->SetData(infoStr.empty() ? DEFAULT_TAB_BAR_NAME : infoStr);
        tabContentItem->SetBarText(text->GetData());
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> iconVal = obj->GetProperty("icon");
        JSRef<JSVal> textVal = obj->GetProperty("text");
        std::string iconUri = iconVal->IsString() ? iconVal->ToString() : "";
        std::string textStr = textVal->IsString() ? textVal->ToString() : "";
        tabContentItem->SetBarIcon(iconUri);
        tabContentItem->SetBarText(textStr.empty() ? DEFAULT_TAB_BAR_NAME : textStr);
        if (iconUri.empty()) {
            text->SetData(textStr.empty() ? DEFAULT_TAB_BAR_NAME : textStr);
            return;
        }
        if (textStr.empty()) {
            tabBar->RemoveChildDirectly(text);
            auto box = AceType::MakeRefPtr<BoxComponent>();
            box->SetChild(AceType::MakeRefPtr<ImageComponent>(iconUri));
            box->SetWidth(DEFAULT_SINGLE_IMAGE_SIZE);
            box->SetHeight(DEFAULT_SINGLE_IMAGE_SIZE);
            tabBar->AppendChild(box);
            return;
        }
        CombineImageAndTextLayout(tabBar, text, iconUri, textStr);
    }
}

void JSTabContent::CombineImageAndTextLayout(const RefPtr<TabBarComponent>& tabBar, const RefPtr<TextComponent>& text,
    const std::string& iconUri, const std::string& textStr)
{
    tabBar->RemoveChildDirectly(text);
    auto imageComponent = AceType::MakeRefPtr<ImageComponent>(iconUri);
    auto box = AceType::MakeRefPtr<BoxComponent>();
    auto padding = AceType::MakeRefPtr<PaddingComponent>();
    padding->SetPadding(Edge(0, 0, 0, 2, DimensionUnit::VP));
    padding->SetChild(imageComponent);
    box->SetChild(padding);
    box->SetWidth(DEFAULT_SMALL_IMAGE_WIDTH);
    box->SetHeight(DEFAULT_SMALL_IMAGE_HEIGHT);
    auto textComponent = AceType::MakeRefPtr<TextComponent>(textStr);
    auto textStyle = textComponent->GetTextStyle();
    textStyle.SetFontSize(DEFAULT_SMALL_TEXT_FONT_SIZE);
    textComponent->SetTextStyle(textStyle);
    std::list<RefPtr<Component>> children;
    children.emplace_back(box);
    children.emplace_back(textComponent);
    auto columnComponent = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER,
        children);
    columnComponent->SetMainAxisSize(MainAxisSize::MIN);
    tabBar->AppendChild(columnComponent);
}

void JSTabContent::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabContent>::Declare("TabContent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTabContent>::StaticMethod("create", &JSTabContent::Create, opt);
    JSClass<JSTabContent>::StaticMethod("tabBar", &JSTabContent::SetTabBar, opt);
    JSClass<JSTabContent>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabContent>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabContent>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabContent>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabContent>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabContent>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabContent>::StaticMethod("width", &JSTabContent::SetTabContentWidth, opt);
    JSClass<JSTabContent>::StaticMethod("height", &JSTabContent::SetTabContentHeight, opt);
    JSClass<JSTabContent>::StaticMethod("size", &JSTabContent::SetTabContentSize, opt);
    JSClass<JSTabContent>::Inherit<JSContainerBase>();
    JSClass<JSTabContent>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
