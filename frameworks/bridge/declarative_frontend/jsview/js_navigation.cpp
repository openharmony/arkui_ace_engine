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

#include "frameworks/bridge/declarative_frontend/jsview/js_navigation.h"

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components/navigation_bar/navigation_bar_component_v2.h"
#include "core/components/navigation_bar/navigation_container_component.h"
#include "core/components/option/option_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_view.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t TITLE_MODE_RANGE = 2;
constexpr int32_t NAVIGATION_MODE_RANGE = 2;
constexpr int32_t NAV_BAR_POSITION_RANGE = 1;
JSRef<JSVal> TitleModeChangeEventToJSValue(const NavigationTitleModeChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.IsMiniBar() ? static_cast<int32_t>(NavigationTitleMode::MINI)
                                                              : static_cast<int32_t>(NavigationTitleMode::FULL)));
}

void ParseToolBarItems(const JSRef<JSArray>& jsArray, std::list<RefPtr<ToolBarItem>>& items)
{
    auto length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = jsArray->GetValueAt(i);
        if (!item->IsObject()) {
            LOGE("tool bar item is not object");
            continue;
        }

        auto itemObject = JSRef<JSObject>::Cast(item);
        auto toolBarItem = AceType::MakeRefPtr<ToolBarItem>();
        auto itemValueObject = itemObject->GetProperty("value");
        if (itemValueObject->IsString()) {
            toolBarItem->value = itemValueObject->ToString();
        }

        auto itemIconObject = itemObject->GetProperty("icon");
        if (itemIconObject->IsString()) {
            toolBarItem->icon = itemIconObject->ToString();
        }

        auto itemActionValue = itemObject->GetProperty("action");
        if (itemActionValue->IsFunction()) {
            auto onClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            toolBarItem->action = EventMarker([func = std::move(onClickFunc)]() {
                ACE_SCORING_EVENT("Navigation.toolBarItemClick");
                func->Execute();
            });
            auto onClickWithParamFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            toolBarItem->actionWithParam =
                EventMarker([func = std::move(onClickWithParamFunc)](const BaseEventInfo* info) {
                    ACE_SCORING_EVENT("Navigation.menuItemButtonClick");
                    func->Execute();
                });
        }
        items.push_back(toolBarItem);
    }
}

void ParseBarItems(const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::list<NG::BarItem>& items)
{
    auto length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = jsArray->GetValueAt(i);
        if (!item->IsObject()) {
            LOGE("tool bar item is not object");
            continue;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        NG::BarItem toolBarItem;
        auto itemValueObject = itemObject->GetProperty("value");
        if (itemValueObject->IsString()) {
            toolBarItem.text = itemValueObject->ToString();
        }

        auto itemIconObject = itemObject->GetProperty("icon");
        if (itemIconObject->IsString()) {
            toolBarItem.icon = itemIconObject->ToString();
        }

        auto itemActionValue = itemObject->GetProperty("action");
        if (itemActionValue->IsFunction()) {
            RefPtr<JsFunction> onClickFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            auto onItemClick = [execCtx = info.GetExecutionContext(), func = std::move(onClickFunc)]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                if (func) {
                    func->ExecuteJS();
                }
            };
            toolBarItem.action = onItemClick;
        }
        items.push_back(toolBarItem);
    }
}

bool ParseCommonTitle(const JSRef<JSVal>& jsValue)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return false;
    }

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> title = jsObj->GetProperty("main");
    bool isCommonTitle = false;
    if (title->IsString()) {
        NG::NavigationView::SetTitle(title->ToString());
        isCommonTitle = true;
    }
    JSRef<JSVal> subtitle = jsObj->GetProperty("sub");
    if (subtitle->IsString()) {
        NG::NavigationView::SetSubtitle(subtitle->ToString());
        isCommonTitle = true;
    }
    return isCommonTitle;
}

} // namespace

void JSNavigation::Create()
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::NavigationView::Create();
        return;
    }
    auto navigationContainer = AceType::MakeRefPtr<NavigationContainerComponent>();
    ViewStackProcessor::GetInstance()->Push(navigationContainer);
}

void JSNavigation::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavigation>::Declare("Navigation");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSNavigation>::StaticMethod("create", &JSNavigation::Create, opt);
    JSClass<JSNavigation>::StaticMethod("title", &JSNavigation::SetTitle, opt);
    JSClass<JSNavigation>::StaticMethod("subTitle", &JSNavigation::SetSubTitle, opt);
    JSClass<JSNavigation>::StaticMethod("titleMode", &JSNavigation::SetTitleMode, opt);
    JSClass<JSNavigation>::StaticMethod("hideTitleBar", &JSNavigation::SetHideTitleBar, opt);
    JSClass<JSNavigation>::StaticMethod("hideBackButton", &JSNavigation::SetHideBackButton, opt);
    JSClass<JSNavigation>::StaticMethod("hideToolBar", &JSNavigation::SetHideToolBar, opt);
    JSClass<JSNavigation>::StaticMethod("toolBar", &JSNavigation::SetToolBar);
    JSClass<JSNavigation>::StaticMethod("menus", &JSNavigation::SetMenus);
    JSClass<JSNavigation>::StaticMethod("menuCount", &JSNavigation::SetMenuCount);
    JSClass<JSNavigation>::StaticMethod("onTitleModeChange", &JSNavigation::SetOnTitleModeChanged);
    JSClass<JSNavigation>::StaticMethod("mode", &JSNavigation::SetNavigationMode);
    JSClass<JSNavigation>::StaticMethod("navBarWidth", &JSNavigation::SetNavBarWidth);
    JSClass<JSNavigation>::StaticMethod("navBarPosition", &JSNavigation::SetNavBarPosition);
    JSClass<JSNavigation>::StaticMethod("hideNavBar", &JSNavigation::SetHideNavBar);
    JSClass<JSNavigation>::StaticMethod("backButtonIcon", &JSNavigation::SetBackButtonIcon);
    JSClass<JSNavigation>::StaticMethod("onNavBarStateChange", &JSNavigation::SetOnNavBarStateChange);
    JSClass<JSNavigation>::Inherit<JSContainerBase>();
    JSClass<JSNavigation>::Inherit<JSViewAbstract>();
    JSClass<JSNavigation>::Bind(globalObj);
}

void JSNavigation::SetTitle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (info[0]->IsString()) {
        if (Container::IsCurrentUseNewPipeline()) {
            NG::NavigationView::SetTitle(info[0]->ToString());
            return;
        }
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
        if (!navigationContainer) {
            LOGI("component is not navigationContainer.");
            return;
        }
        navigationContainer->GetDeclaration()->title = info[0]->ToString();
    } else if (info[0]->IsObject()) {
        if (ParseCommonTitle(info[0])) {
            return;
        }

        // CustomBuilder | NavigationCustomTitle
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> builderObject = jsObj->GetProperty("builder");
        if (builderObject->IsFunction()) {
            if (Container::IsCurrentUseNewPipeline()) {
                RefPtr<NG::UINode> customNode;
                {
                    NG::ScopedViewStackProcessor builderViewStackProcessor;
                    JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
                    ACE_SCORING_EVENT("Navigation.title.builder");
                    jsBuilderFunc.Execute();
                    customNode = NG::ViewStackProcessor::GetInstance()->Finish();
                }
                NG::NavigationView::SetCustomTitle(customNode);
            } else {
                auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
                auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
                if (!navigationContainer) {
                    LOGI("component is not navigationContainer.");
                    return;
                }
                {
                    ScopedViewStackProcessor builderViewStackProcessor;
                    JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
                    ACE_SCORING_EVENT("Navigation.title.builder");
                    jsBuilderFunc.Execute();
                    navigationContainer->GetDeclaration()->customTitle = ViewStackProcessor::GetInstance()->Finish();
                }
            }
        }

        if (Container::IsCurrentUseNewPipeline()) {
            return;
        }
        JSRef<JSVal> height = jsObj->GetProperty("height");
        if (height->IsNumber()) {
            if (height->ToNumber<int32_t>() == 0) {
                NG::NavigationView::SetTitleHeight(NG::FULL_SINGLE_LINE_TITLEBAR_HEIGHT);
            }
            if (height->ToNumber<int32_t>() == 1) {
                NG::NavigationView::SetTitleHeight(NG::FULL_DOUBLE_LINE_TITLEBAR_HEIGHT);
            }
            Dimension titleHeight;
            if (!JSContainerBase::ParseJsDimensionVp(height, titleHeight)) {
                return;
            }
            NG::NavigationView::SetTitleHeight(titleHeight);
        }
    } else {
        LOGE("arg is not [String|Function].");
    }
}

void JSNavigation::SetTitleMode(int32_t value)
{
    if (value >= 0 && value <= TITLE_MODE_RANGE) {
        if (Container::IsCurrentUseNewPipeline()) {
            NG::NavigationView::SetTitleMode(static_cast<NG::NavigationTitleMode>(value));
            return;
        }
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
        if (navigationContainer) {
            navigationContainer->GetDeclaration()->titleMode = static_cast<NavigationTitleMode>(value);
        }
    } else {
        LOGE("invalid value for titleMode");
    }
}

void JSNavigation::SetSubTitle(const std::string& subTitle)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::NavigationView::SetSubtitle(subTitle);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (navigationContainer) {
        navigationContainer->GetDeclaration()->subTitle = subTitle;
    }
}

void JSNavigation::SetHideTitleBar(bool hide)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::NavigationView::SetHideTitleBar(hide);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (navigationContainer) {
        auto declaration = navigationContainer->GetDeclaration();
        declaration->hideBar = hide;
        declaration->animationOption = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    }
}

void JSNavigation::SetHideNavBar(bool hide)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    NG::NavigationView::SetHideNavBar(hide);
}

void JSNavigation::SetBackButtonIcon(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    std::string src;
    auto noPixMap = ParseJsMedia(info[0], src);

    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!noPixMap) {
        pixMap = CreatePixelMapFromNapiValue(info[0]);
    }
#endif
    NG::NavigationView::SetBackButtonIcon(src, noPixMap, pixMap);
}

void JSNavigation::SetHideBackButton(bool hide)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::NavigationView::SetHideBackButton(hide);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (navigationContainer) {
        navigationContainer->GetDeclaration()->hideBarBackButton = hide;
    }
}

void JSNavigation::SetHideToolBar(bool hide)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::NavigationView::SetHideToolBar(hide);
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (navigationContainer) {
        auto declaration = navigationContainer->GetDeclaration();
        declaration->hideToolbar = hide;
        declaration->animationOption = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    }
}

void JSNavigation::SetToolBar(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsObject()) {
        LOGE("arg is not a object.");
        return;
    }
    auto builderFuncParam = JSRef<JSObject>::Cast(info[0])->GetProperty("builder");
    if (builderFuncParam->IsFunction()) {
        if (Container::IsCurrentUseNewPipeline()) {
            RefPtr<NG::UINode> customNode;
            {
                NG::ScopedViewStackProcessor builderViewStackProcessor;
                JsFunction jsBuilderFunc(builderFuncParam);
                jsBuilderFunc.Execute();
                customNode = NG::ViewStackProcessor::GetInstance()->Finish();
            }
            NG::NavigationView::SetCustomToolBar(customNode);
            return;
        }
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
        if (!navigationContainer) {
            LOGI("component is not navigationContainer.");
            return;
        }
        {
            ScopedViewStackProcessor builderViewStackProcessor;
            JsFunction jsBuilderFunc(builderFuncParam);
            jsBuilderFunc.Execute();
            RefPtr<Component> builderGeneratedRootComponent = ViewStackProcessor::GetInstance()->Finish();
            navigationContainer->GetDeclaration()->toolBarBuilder = builderGeneratedRootComponent;
        }
        return;
    }

    auto itemsValue = JSRef<JSObject>::Cast(info[0])->GetProperty("items");
    if (!itemsValue->IsObject() || !itemsValue->IsArray()) {
        LOGE("arg format error: not find items");
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        std::list<NG::BarItem> toolBarItems;
        ParseBarItems(info, JSRef<JSArray>::Cast(itemsValue), toolBarItems);
        NG::NavigationView::SetToolBarItems(std::move(toolBarItems));
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (!navigationContainer) {
        LOGI("component is not navigationContainer.");
        return;
    }
    ParseToolBarItems(JSRef<JSArray>::Cast(itemsValue), navigationContainer->GetDeclaration()->toolbarItems);
}

void JSNavigation::SetMenus(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }

    if (info[0]->IsArray()) {
        if (Container::IsCurrentUseNewPipeline()) {
            std::list<NG::BarItem> menuItems;
            ParseBarItems(info, JSRef<JSArray>::Cast(info[0]), menuItems);
            NG::NavigationView::SetMenuItems(std::move(menuItems));
            return;
        }
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
        if (!navigationContainer) {
            LOGI("component is not navigationContainer.");
            return;
        }
        ParseToolBarItems(JSRef<JSArray>::Cast(info[0]), navigationContainer->GetDeclaration()->menuItems);
    } else if (info[0]->IsObject()) {
        auto builderObject = JSRef<JSObject>::Cast(info[0])->GetProperty("builder");
        if (builderObject->IsFunction()) {
            if (Container::IsCurrentUseNewPipeline()) {
                RefPtr<NG::UINode> customNode;
                {
                    NG::ScopedViewStackProcessor builderViewStackProcessor;
                    JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
                    ACE_SCORING_EVENT("Navigation.menu.builder");
                    jsBuilderFunc.Execute();
                    customNode = NG::ViewStackProcessor::GetInstance()->Finish();
                }
                NG::NavigationView::SetCustomMenu(customNode);
                return;
            }
            auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
            auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
            if (!navigationContainer) {
                LOGI("component is not navigationContainer.");
                return;
            }
            {
                ScopedViewStackProcessor builderViewStackProcessor;
                JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
                ACE_SCORING_EVENT("Navigation.menu.builder");
                jsBuilderFunc.Execute();
                navigationContainer->GetDeclaration()->customMenus = ViewStackProcessor::GetInstance()->Finish();
            }
        }
    } else {
        LOGE("arg is not [String|Function].");
    }
}

void JSNavigation::SetMenuCount(int32_t menuCount)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
    if (navigationContainer) {
        navigationContainer->SetMenuCount(menuCount);
    }
}

void JSNavigation::SetOnTitleModeChanged(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (info[0]->IsFunction()) {
        if (Container::IsCurrentUseNewPipeline()) {
            auto onTitleModeChangeCallback =
                AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
            auto onTitleModeChange = [execCtx = info.GetExecutionContext(),
                                         func = std::move(onTitleModeChangeCallback)](NG::NavigationTitleMode mode) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("OnTitleModeChange");
                JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(mode));
                func->ExecuteJS(1, &param);
            };
            NG::NavigationView::SetOnTitleModeChange(std::move(onTitleModeChange));
            return;
        }
        auto changeHandler = AceType::MakeRefPtr<JsEventFunction<NavigationTitleModeChangeEvent, 1>>(
            JSRef<JSFunc>::Cast(info[0]), TitleModeChangeEventToJSValue);
        auto eventMarker = EventMarker([executionContext = info.GetExecutionContext(), func = std::move(changeHandler)](
                                           const BaseEventInfo* baseInfo) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
            auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(baseInfo);
            if (!eventInfo) {
                LOGE("HandleChangeEvent eventInfo == nullptr");
                return;
            }
            ACE_SCORING_EVENT("Navigation.onTitleModeChanged");
            func->Execute(*eventInfo);
        });
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto navigationContainer = AceType::DynamicCast<OHOS::Ace::NavigationContainerComponent>(component);
        if (navigationContainer) {
            navigationContainer->GetDeclaration()->titleModeChangedEvent = eventMarker;
        }
    }
    info.ReturnSelf();
}

void JSNavigation::SetNavigationMode(int32_t value)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }

    if (value >= 0 && value <= NAVIGATION_MODE_RANGE) {
        NG::NavigationView::SetNavigationMode(static_cast<NG::NavigationMode>(value));
    } else {
        LOGE("invalid value for navigationMode");
    }
}

void JSNavigation::SetNavBarPosition(int32_t value)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }

    if (value >= 0 && value <= NAV_BAR_POSITION_RANGE) {
        NG::NavigationView::SetNavBarPosition(static_cast<NG::NavBarPosition>(value));
    } else {
        LOGE("invalid value for navBarPosition");
    }
}

void JSNavigation::SetNavBarWidth(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    Dimension navBarWidth;
    if (!ParseJsDimensionVp(info[0], navBarWidth)) {
        return;
    }
    NG::NavigationView::SetNavBarWidth(navBarWidth);
}

void JSNavigation::SetOnNavBarStateChange(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }

    if (info[0]->IsFunction()) {
        auto onNavBarStateChangeCallback =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onNavBarStateChange = [execCtx = info.GetExecutionContext(),
                                        func = std::move(onNavBarStateChangeCallback)](bool isVisible) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("OnNavBarStateChange");
            JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(isVisible));
            func->ExecuteJS(1, &param);
        };
        NG::NavigationView::SetOnNavBarStateChange(std::move(onNavBarStateChange));
    }
    info.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
