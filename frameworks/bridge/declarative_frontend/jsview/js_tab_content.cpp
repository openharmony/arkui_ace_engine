/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/tabs/tab_content_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr char DEFAULT_TAB_BAR_NAME[] = "TabBar";

} // namespace

void JSTabContent::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        CreateForNG(info);
        return;
    }

    bool usePartialUpdate = Container::IsCurrentUsePartialUpdate();
    std::list<RefPtr<Component>> components;
    auto tabContentItemComponent = AceType::MakeRefPtr<V2::TabContentItemComponent>(components);
    tabContentItemComponent->SetCrossAxisSize(CrossAxisSize::MAX);
    ViewStackProcessor::GetInstance()->ClaimElementId(tabContentItemComponent);

    RefPtr<V2::TabsComponent> tabsComponent = nullptr;
    if (!usePartialUpdate) {
        tabsComponent = AceType::DynamicCast<V2::TabsComponent>(ViewStackProcessor::GetInstance()->GetTopTabs());
        if (!tabsComponent) {
            LOGE("fail to create tab content due to tabs missing");
            return;
        }
        // GetTabsComponent used only by JSTabContent::SetTabBar
        // To Find TabBarComponent eventually
        tabContentItemComponent->SetTabsComponent(AceType::WeakClaim(AceType::RawPtr(tabsComponent)));

        auto tabBar = tabsComponent->GetTabBarChild();
        tabBar->AppendChild(CreateTabBarLabelComponent(tabContentItemComponent, std::string(DEFAULT_TAB_BAR_NAME)));
    }

    ViewStackProcessor::GetInstance()->Push(tabContentItemComponent);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (box) {
        box->SetBoxClipFlag(true);
    }

    if (usePartialUpdate && info.Length() > 0 && info[0]->IsFunction()) {
        JSRef<JSVal> builderFunctionJS = info[0];
        LOGD("We have a build function for a tab");
        auto jsWrapperFunc =
            [context = info.GetExecutionContext(), builder = builderFunctionJS]() -> RefPtr<Component> {
            JAVASCRIPT_EXECUTION_SCOPE(context)
            JSRef<JSFunc>::Cast(builder)->Call(JSRef<JSObject>());
            return ViewStackProcessor::GetInstance()->Finish();
        };
        tabContentItemComponent->SetBuilder(jsWrapperFunc);
        return;
    }
    LOGE("No build function for a tab provided");
}

void JSTabContent::CreateForNG(const JSCallbackInfo& info)
{
    bool usePartialUpdate = Container::IsCurrentUsePartialUpdate();
    if (!usePartialUpdate) {
        NG::TabContentView::Create();
        return;
    }

    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGW("Param should be a function.");
        return;
    }

    RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(info[0]));
    auto tabContentDeepRenderFunc = [execCtx = info.GetExecutionContext(),
                                    jsDeepRenderFunc = std::move(jsDeepRender)](int32_t nodeId) {
        if (!jsDeepRenderFunc) {
            LOGE("Func is null.");
            return;
        }

        ACE_SCOPED_TRACE("JSTabContent::ExecuteDeepRender");
        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        jsDeepRenderFunc->ExecuteJS();
    };
    NG::TabContentView::Create(std::move(tabContentDeepRenderFunc));
}

void JSTabContent::SetTabBar(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        SetTabBarForNG(info);
        return;
    }

    auto tabContentItemComponent =
        AceType::DynamicCast<V2::TabContentItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!tabContentItemComponent) {
        return;
    }

    auto weakTabs = tabContentItemComponent->GetTabsComponent();
    // Full update: tabs and tabBar always exist
    // Partial update: tabs and tabBar exist for initial render and nullptr for rerender
    auto tabs = weakTabs.Upgrade();
    auto tabBar = tabs ? tabs->GetTabBarChild() : nullptr;

    if (!Container::IsCurrentUsePartialUpdate()) {
        if (!tabs) {
            LOGE("can not get Tabs parent component error.");
            return;
        }
        if (!tabBar) {
            LOGE("can not get TabBar component error.");
            return;
        }
    }

    RefPtr<Component> tabBarChild = nullptr;
    std::string infoStr;
    if (ParseJsString(info[0], infoStr)) {
        auto textVal = infoStr.empty() ? DEFAULT_TAB_BAR_NAME : infoStr;
        if (!Container::IsCurrentUsePartialUpdate()) {
            tabBarChild = CreateTabBarLabelComponent(tabContentItemComponent, textVal);
        } else {
            tabContentItemComponent->SetBarText(textVal);
        }
    } else {
        // For Partial Update ProcessTabBarXXX methods
        // do not create any components for the tab bar items
        // and return nullptr.
        // Tab bar items created and added later by
        // TabContentItemElementProxy class.
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> builderFuncParam = paramObject->GetProperty("builder");
        JSRef<JSVal> textParam = paramObject->GetProperty("text");
        JSRef<JSVal> iconParam = paramObject->GetProperty("icon");
        auto isTextEmpty = textParam->IsEmpty() || textParam->IsUndefined() || textParam->IsNull();
        auto isIconEmpty = iconParam->IsEmpty() || iconParam->IsUndefined() || iconParam->IsNull();

        if (builderFuncParam->IsFunction()) {
            tabBarChild = ProcessTabBarBuilderFunction(info, tabContentItemComponent, builderFuncParam);
            // Update tabBar always for full update and for initial render only for partial update
            if (tabBar) {
                tabBar->ResetIndicator();
                tabBar->SetAlignment(Alignment::TOP_LEFT);
            }
        } else if (!isTextEmpty && !isIconEmpty) {
            tabBarChild = ProcessTabBarTextIconPair(tabContentItemComponent, textParam, iconParam);
        } else if (!isTextEmpty && isIconEmpty) {
            tabBarChild = ProcessTabBarLabel(tabContentItemComponent, textParam);
        }
    }

    if (!Container::IsCurrentUsePartialUpdate()) {
        auto defaultTabChild = tabBar->GetChildren().back();
        tabBar->RemoveChildDirectly(defaultTabChild);
        tabBar->AppendChild(tabBarChild);
        return;
    }

    // Partial Update only
    if (tabContentItemComponent->GetBarElementId() == ElementRegister::UndefinedElementId) {
        const auto id = ElementRegister::GetInstance()->MakeUniqueId();
        tabContentItemComponent->SetBarElementId(id);
        LOGD("Setting ID for tab bar item to %{public}d tabContentItemComponent id %{public}d",
            id, tabContentItemComponent->GetBarElementId());
    }
}

void JSTabContent::SetTabBarForNG(const JSCallbackInfo& info)
{
    if (info.Length() <= 0) {
        return;
    }

    std::string content;
    if (ParseJsString(info[0], content)) {
        auto textVal = content.empty() ? DEFAULT_TAB_BAR_NAME : content;
        NG::TabContentView::SetTabBar(textVal, "");
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> builderFuncParam = paramObject->GetProperty("builder");
    JSRef<JSVal> textParam = paramObject->GetProperty("text");
    JSRef<JSVal> iconParam = paramObject->GetProperty("icon");

    if (builderFuncParam->IsFunction()) {
        // TODO adapt builder
        return;
    }

    std::string text;
    std::string icon;
    ParseJsString(textParam, text);
    ParseJsString(iconParam, icon);
    NG::TabContentView::SetTabBar(text.empty() ? DEFAULT_TAB_BAR_NAME : text, icon);
}

RefPtr<Component> JSTabContent::ProcessTabBarBuilderFunction(const JSCallbackInfo& info,
    RefPtr<V2::TabContentItemComponent>& tabContent, JSRef<JSObject> builderFunc)
{
    tabContent->SetBarText("custom");
    if (Container::IsCurrentUsePartialUpdate()) {
        auto jsWrapperFunc = [context = info.GetExecutionContext(), builder = builderFunc]() -> RefPtr<Component> {
                ACE_SCORING_EVENT("TabContent.tabBarBuilder");
                JAVASCRIPT_EXECUTION_SCOPE(context)
                JSRef<JSFunc>::Cast(builder)->Call(JSRef<JSObject>());
                return ViewStackProcessor::GetInstance()->Finish();
            };

        tabContent->SetBarBuilder(jsWrapperFunc);
        return nullptr;
    }

    ScopedViewStackProcessor builderViewStackProcessor;
    JsFunction jsBuilderFunc(builderFunc);
    ACE_SCORING_EVENT("TabContent.tabBarBuilder");
    jsBuilderFunc.Execute();
    RefPtr<Component> builderGeneratedRootComponent = ViewStackProcessor::GetInstance()->Finish();
    return builderGeneratedRootComponent;

}

RefPtr<Component> JSTabContent::CreateTabBarLabelComponent(
    RefPtr<V2::TabContentItemComponent>& tabContent, const std::string& labelStr)
{
    tabContent->SetBarText(labelStr);
    return TabBarItemComponent::BuildWithTextIcon(labelStr, std::string());
}

RefPtr<Component> JSTabContent::ProcessTabBarLabel(
    RefPtr<V2::TabContentItemComponent>& tabContent, JSRef<JSVal> labelVal)
{
    std::string textStr;
    if (!ParseJsString(labelVal, textStr)) {
        textStr = DEFAULT_TAB_BAR_NAME;
    }
    tabContent->SetBarText(textStr);

    if (!Container::IsCurrentUsePartialUpdate()) {
        return CreateTabBarLabelComponent(tabContent, textStr);
    }
    return nullptr;
}

RefPtr<Component> JSTabContent::ProcessTabBarTextIconPair(
    RefPtr<V2::TabContentItemComponent>& tabContent, JSRef<JSVal> textVal, JSRef<JSVal> iconVal)
{
    std::string iconUri;
    if (!ParseJsMedia(iconVal, iconUri)) {
        return ProcessTabBarLabel(tabContent, textVal);
    }
    std::string textStr;
    if (!ParseJsString(textVal, textStr)) {
        textStr = DEFAULT_TAB_BAR_NAME;
    }
    tabContent->SetBarText(textStr);
    tabContent->SetBarIcon(iconUri);

    if (!Container::IsCurrentUsePartialUpdate()) {
        return TabBarItemComponent::BuildWithTextIcon(textStr, iconUri);
    }
    return nullptr;
}

void JSTabContent::Pop()
{
    JSContainerBase::Pop();
    NG::TabContentView::Pop();
}

void JSTabContent::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabContent>::Declare("TabContent");
    JSClass<JSTabContent>::StaticMethod("create", &JSTabContent::Create);
    JSClass<JSTabContent>::StaticMethod("pop", &JSTabContent::Pop);
    JSClass<JSTabContent>::StaticMethod("tabBar", &JSTabContent::SetTabBar);
    JSClass<JSTabContent>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabContent>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabContent>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabContent>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTabContent>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabContent>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabContent>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabContent>::StaticMethod("width", &JSTabContent::SetTabContentWidth);
    JSClass<JSTabContent>::StaticMethod("height", &JSTabContent::SetTabContentHeight);
    JSClass<JSTabContent>::StaticMethod("size", &JSTabContent::SetTabContentSize);
    JSClass<JSTabContent>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSTabContent>::Inherit<JSContainerBase>();
    JSClass<JSTabContent>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
