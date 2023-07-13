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

#include <vector>

#include "base/log/ace_scoring_log.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/navigation_model_impl.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<NavigationModel> NavigationModel::instance_ = nullptr;
std::mutex NavigationModel::mutex_;

NavigationModel* NavigationModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::NavigationModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::NavigationModelNG());
            } else {
                instance_.reset(new Framework::NavigationModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t TITLE_MODE_RANGE = 2;
constexpr int32_t NAVIGATION_MODE_RANGE = 2;
constexpr int32_t NAV_BAR_POSITION_RANGE = 1;
constexpr int32_t DEFAULT_NAV_BAR_WIDTH = 240;
constexpr Dimension DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;

JSRef<JSVal> TitleModeChangeEventToJSValue(const NavigationTitleModeChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.IsMiniBar() ? static_cast<int32_t>(NavigationTitleMode::MINI)
                                                              : static_cast<int32_t>(NavigationTitleMode::FULL)));
}

} // namespace

void JSNavigation::ParseToolBarItems(const JSRef<JSArray>& jsArray, std::list<RefPtr<AceType>>& items)
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
        std::string icon;
        if (!ParseJsMedia(itemIconObject, icon)) {
            LOGE("iconValue is null");
        }
        toolBarItem->icon = icon;

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

void JSNavigation::ParseBarItems(
    const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::vector<NG::BarItem>& items)
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

void JSNavigation::ParseToolbarItemsConfiguration(
    const JSCallbackInfo& info, const JSRef<JSArray>& jsArray, std::vector<NG::BarItem>& items)
{
    auto length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = jsArray->GetValueAt(i);
        if (!item->IsObject()) {
            continue;
        }
        NG::BarItem toolBarItem;
        std::string text;
        std::string icon;
        std::string activeIcon;

        auto itemObject = JSRef<JSObject>::Cast(item);
        auto itemValueObject = itemObject->GetProperty("value");
        if (ParseJsString(itemValueObject, text)) {
            toolBarItem.text = text;
        }

        auto itemIconObject = itemObject->GetProperty("icon");
        if (ParseJsMedia(itemIconObject, icon)) {
            toolBarItem.icon = icon;
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

        auto itemStatusValue = itemObject->GetProperty("status");
        if (itemStatusValue->IsNumber()) {
            toolBarItem.status = static_cast<NG::ToolbarItemStatus>(itemStatusValue->ToNumber<int32_t>());
        }

        auto itemActiveIconObject = itemObject->GetProperty("activeIcon");
        if (ParseJsMedia(itemActiveIconObject, activeIcon)) {
            toolBarItem.activeIcon = activeIcon;
        }

        items.push_back(toolBarItem);
    }
}

bool JSNavigation::ParseCommonTitle(const JSRef<JSVal>& jsValue)
{
    bool isCommonTitle = false;
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> subtitle = jsObj->GetProperty("sub");
    JSRef<JSVal> title = jsObj->GetProperty("main");
    bool sub = subtitle->IsString();
    bool main = title->IsString();
    if (subtitle->IsString() || title->IsString()) {
        NavigationModel::GetInstance()->ParseCommonTitle(sub, main, subtitle->ToString(), title->ToString());
    }
    return isCommonTitle;
}

void JSNavigation::Create(const JSCallbackInfo& info)
{
    if (info.Length() <= 0) {
        NavigationModel::GetInstance()->Create();
        NavigationModel::GetInstance()->SetNavigationStack();
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto value = obj->GetProperty("type");
    if (value->ToString() != "NavPathStack") {
        return;
    }

    NavigationModel::GetInstance()->Create();
    auto navigationStack = AceType::MakeRefPtr<JSNavigationStack>();
    navigationStack->SetDataSourceObj(obj);
    NavigationModel::GetInstance()->SetNavigationStackProvided(true);
    NavigationModel::GetInstance()->SetNavigationStack(std::move(navigationStack));
}

void JSNavigation::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavigation>::Declare("Navigation");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSNavigation>::StaticMethod("create", &JSNavigation::Create);
    JSClass<JSNavigation>::StaticMethod("title", &JSNavigation::SetTitle, opt);
    JSClass<JSNavigation>::StaticMethod("subTitle", &JSNavigation::SetSubTitle, opt);
    JSClass<JSNavigation>::StaticMethod("titleMode", &JSNavigation::SetTitleMode, opt);
    JSClass<JSNavigation>::StaticMethod("hideTitleBar", &JSNavigation::SetHideTitleBar, opt);
    JSClass<JSNavigation>::StaticMethod("hideBackButton", &JSNavigation::SetHideBackButton, opt);
    JSClass<JSNavigation>::StaticMethod("hideToolBar", &JSNavigation::SetHideToolBar, opt);
    JSClass<JSNavigation>::StaticMethod("toolBar", &JSNavigation::SetToolBar);
    JSClass<JSNavigation>::StaticMethod("toolbarConfiguration", &JSNavigation::SetToolbarConfiguration);
    JSClass<JSNavigation>::StaticMethod("menus", &JSNavigation::SetMenus);
    JSClass<JSNavigation>::StaticMethod("menuCount", &JSNavigation::SetMenuCount);
    JSClass<JSNavigation>::StaticMethod("onTitleModeChange", &JSNavigation::SetOnTitleModeChanged);
    JSClass<JSNavigation>::StaticMethod("mode", &JSNavigation::SetUsrNavigationMode);
    JSClass<JSNavigation>::StaticMethod("navBarWidth", &JSNavigation::SetNavBarWidth);
    JSClass<JSNavigation>::StaticMethod("minContentWidth", &JSNavigation::SetMinContentWidth);
    JSClass<JSNavigation>::StaticMethod("navBarWidthRange", &JSNavigation::SetNavBarWidthRange);
    JSClass<JSNavigation>::StaticMethod("navBarPosition", &JSNavigation::SetNavBarPosition);
    JSClass<JSNavigation>::StaticMethod("hideNavBar", &JSNavigation::SetHideNavBar);
    JSClass<JSNavigation>::StaticMethod("backButtonIcon", &JSNavigation::SetBackButtonIcon);
    JSClass<JSNavigation>::StaticMethod("onNavBarStateChange", &JSNavigation::SetOnNavBarStateChange);
    JSClass<JSNavigation>::StaticMethod("navDestination", &JSNavigation::SetNavDestination);
    JSClass<JSNavigation>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSNavigation>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSNavigation>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNavigation>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSNavigation::SetTitle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (info[0]->IsString() || info[0]->IsUndefined()) {
        std::string title;
        if (info[0]->IsUndefined()) {
            title = "";
        } else {
            title = info[0]->ToString();
        }
        NavigationModel::GetInstance()->SetTitle(title);
    } else if (info[0]->IsObject()) {
        if (ParseCommonTitle(info[0])) {
            return;
        }
        std::string title;
        if (ParseJsString(info[0], title)) {
            NavigationModel::GetInstance()->SetTitle(title);
        }
        // CustomBuilder | NavigationCustomTitle
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> builderObject = jsObj->GetProperty("builder");
        if (builderObject->IsFunction()) {
            ViewStackModel::GetInstance()->NewScope();
            JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
            ACE_SCORING_EVENT("Navigation.title.builder");
            jsBuilderFunc.Execute();
            auto customNode = ViewStackModel::GetInstance()->Finish();
            NavigationModel::GetInstance()->SetCustomTitle(customNode);
        }

        JSRef<JSVal> height = jsObj->GetProperty("height");
        if (height->IsNumber()) {
            if (height->ToNumber<int32_t>() == 0) {
                NavigationModel::GetInstance()->SetTitleHeight(NG::FULL_SINGLE_LINE_TITLEBAR_HEIGHT);
                return;
            }
            if (height->ToNumber<int32_t>() == 1) {
                NavigationModel::GetInstance()->SetTitleHeight(NG::FULL_DOUBLE_LINE_TITLEBAR_HEIGHT);
                return;
            }
            CalcDimension titleHeight;
            if (!JSContainerBase::ParseJsDimensionVp(height, titleHeight)) {
                return;
            }
            NavigationModel::GetInstance()->SetTitleHeight(titleHeight);
        }
    } else {
        LOGE("arg is not [String|Function].");
    }
}

void JSNavigation::SetTitleMode(int32_t value)
{
    if (value >= 0 && value <= TITLE_MODE_RANGE) {
        NavigationModel::GetInstance()->SetTitleMode(static_cast<NG::NavigationTitleMode>(value));
    } else {
        LOGE("invalid value for titleMode");
    }
}

void JSNavigation::SetSubTitle(const std::string& subTitle)
{
    NavigationModel::GetInstance()->SetSubtitle(subTitle);
}

void JSNavigation::SetHideTitleBar(bool hide)
{
    NavigationModel::GetInstance()->SetHideTitleBar(hide);
}

void JSNavigation::SetHideNavBar(bool hide)
{
    NavigationModel::GetInstance()->SetHideNavBar(hide);
}

void JSNavigation::SetBackButtonIcon(const JSCallbackInfo& info)
{
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
    NavigationModel::GetInstance()->SetBackButtonIcon(src, noPixMap, pixMap);
}

void JSNavigation::SetHideBackButton(bool hide)
{
    NavigationModel::GetInstance()->SetHideBackButton(hide);
}

void JSNavigation::SetHideToolBar(bool hide)
{
    NavigationModel::GetInstance()->SetHideToolBar(hide);
}

void JSNavigation::SetToolBar(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsUndefined()) {
        LOGE("arg is not a object or is not undefined.");
        return;
    }
    if (info[0]->IsUndefined()) {
        NavigationModel::GetInstance()->SetToolBarItems({});
        return;
    }
    auto builderFuncParam = JSRef<JSObject>::Cast(info[0])->GetProperty("builder");
    if (builderFuncParam->IsFunction()) {
        ViewStackModel::GetInstance()->NewScope();
        JsFunction jsBuilderFunc(builderFuncParam);
        jsBuilderFunc.Execute();
        auto customNode = ViewStackModel::GetInstance()->Finish();
        NavigationModel::GetInstance()->SetCustomToolBar(customNode);
    }

    auto itemsValue = JSRef<JSObject>::Cast(info[0])->GetProperty("items");
    if (!itemsValue->IsObject() || !itemsValue->IsArray()) {
        LOGE("arg format error: not find items");
        return;
    }
    if (NavigationModel::GetInstance()->NeedSetItems()) {
        std::vector<NG::BarItem> toolBarItems;
        ParseBarItems(info, JSRef<JSArray>::Cast(itemsValue), toolBarItems);
        NavigationModel::GetInstance()->SetToolBarItems(std::move(toolBarItems));
        return;
    }
    std::list<RefPtr<AceType>> items;
    NavigationModel::GetInstance()->GetToolBarItems(items);
    ParseToolBarItems(JSRef<JSArray>::Cast(itemsValue), items);
}

void JSNavigation::SetToolbarConfiguration(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || info[0]->IsArray()) {
        if (NavigationModel::GetInstance()->NeedSetItems()) {
            std::vector<NG::BarItem> toolbarItems;
            if (info[0]->IsUndefined()) {
                toolbarItems = {};
            } else {
                ParseToolbarItemsConfiguration(info, JSRef<JSArray>::Cast(info[0]), toolbarItems);
            }
            NavigationModel::GetInstance()->SetToolbarConfiguration(std::move(toolbarItems));
            return;
        }
        std::list<RefPtr<AceType>> items;
        NavigationModel::GetInstance()->GetToolBarItems(items);
        ParseToolBarItems(JSRef<JSArray>::Cast(info[0]), items);
    } else if (info[0]->IsObject()) {
        auto builderFuncParam = JSRef<JSObject>::Cast(info[0])->GetProperty("builder");
        if (builderFuncParam->IsFunction()) {
            ViewStackModel::GetInstance()->NewScope();
            JsFunction jsBuilderFunc(builderFuncParam);
            jsBuilderFunc.Execute();
            auto customNode = ViewStackModel::GetInstance()->Finish();
            NavigationModel::GetInstance()->SetCustomToolBar(customNode);
        }
    }
}

void JSNavigation::SetMenus(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }

    if (info[0]->IsUndefined() || info[0]->IsArray()) {
        if (NavigationModel::GetInstance()->NeedSetItems()) {
            std::vector<NG::BarItem> menuItems;
            if (info[0]->IsUndefined()) {
                menuItems = {};
            } else {
                ParseBarItems(info, JSRef<JSArray>::Cast(info[0]), menuItems);
            }
            NavigationModel::GetInstance()->SetMenuItems(std::move(menuItems));
            return;
        }
        std::list<RefPtr<AceType>> items;
        NavigationModel::GetInstance()->GetMenuItems(items);
        ParseToolBarItems(JSRef<JSArray>::Cast(info[0]), items);
    } else if (info[0]->IsObject()) {
        auto builderObject = JSRef<JSObject>::Cast(info[0])->GetProperty("builder");
        if (builderObject->IsFunction()) {
            ViewStackModel::GetInstance()->NewScope();
            JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
            ACE_SCORING_EVENT("Navigation.menu.builder");
            jsBuilderFunc.Execute();
            auto customNode = ViewStackModel::GetInstance()->Finish();
            NavigationModel::GetInstance()->SetCustomMenu(customNode);
        }
    } else {
        LOGE("arg is not [String|Function].");
    }
}

void JSNavigation::SetMenuCount(int32_t menuCount)
{
    NavigationModel::GetInstance()->SetMenuCount(menuCount);
}

void JSNavigation::SetOnTitleModeChanged(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (info[0]->IsFunction()) {
        auto onTitleModeChangeCallback =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onTitleModeChange = [execCtx = info.GetExecutionContext(), func = std::move(onTitleModeChangeCallback)](
                                     NG::NavigationTitleMode mode) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("OnTitleModeChange");
            JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(mode));
            func->ExecuteJS(1, &param);
        };
        auto changeHandler = AceType::MakeRefPtr<JsEventFunction<NavigationTitleModeChangeEvent, 1>>(
            JSRef<JSFunc>::Cast(info[0]), TitleModeChangeEventToJSValue);
        auto eventInfo = [executionContext = info.GetExecutionContext(), func = std::move(changeHandler)](
                             const BaseEventInfo* baseInfo) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
            auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(baseInfo);
            if (!eventInfo) {
                LOGE("HandleChangeEvent eventInfo == nullptr");
                return;
            }
            ACE_SCORING_EVENT("Navigation.onTitleModeChanged");
            func->Execute(*eventInfo);
        };
        NavigationModel::GetInstance()->SetOnTitleModeChange(std::move(onTitleModeChange), std::move(eventInfo));
    }
    info.ReturnSelf();
}

void JSNavigation::SetUsrNavigationMode(int32_t value)
{
    if (value >= 0 && value <= NAVIGATION_MODE_RANGE) {
        NavigationModel::GetInstance()->SetUsrNavigationMode(static_cast<NG::NavigationMode>(value));
    } else {
        LOGE("invalid value for navigationMode");
    }
}

void JSNavigation::SetNavBarPosition(int32_t value)
{
    if (value >= 0 && value <= NAV_BAR_POSITION_RANGE) {
        NavigationModel::GetInstance()->SetNavBarPosition(static_cast<NG::NavBarPosition>(value));
    } else {
        LOGE("invalid value for navBarPosition");
    }
}

void JSNavigation::SetNavBarWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    CalcDimension navBarWidth;
    if (!ParseJsDimensionVp(info[0], navBarWidth)) {
        return;
    }

    if (navBarWidth.Value() <= 0) {
        navBarWidth.SetValue(DEFAULT_NAV_BAR_WIDTH);
    }

    NavigationModel::GetInstance()->SetNavBarWidth(navBarWidth);
}

void JSNavigation::SetMinContentWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    CalcDimension minContentWidth;
    if (!ParseJsDimensionVp(info[0], minContentWidth)) {
        NavigationModel::GetInstance()->SetMinContentWidth(DEFAULT_MIN_CONTENT_WIDTH);
        return;
    }

    if (LessNotEqual(minContentWidth.Value(), 0.0)) {
        minContentWidth = DEFAULT_MIN_CONTENT_WIDTH;
    }

    NavigationModel::GetInstance()->SetMinContentWidth(minContentWidth);
}

void JSNavigation::SetNavBarWidthRange(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    auto rangeArray = JSRef<JSArray>::Cast(info[0]);
    JSRef<JSVal> min = rangeArray->GetValueAt(0);
    JSRef<JSVal> max = rangeArray->GetValueAt(1);

    CalcDimension minNavBarWidth;
    CalcDimension maxNavBarWidth;
    ParseJsDimensionVp(min, minNavBarWidth);
    ParseJsDimensionVp(max, maxNavBarWidth);

    if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
        minNavBarWidth.SetValue(0);
    }
    NavigationModel::GetInstance()->SetMinNavBarWidth(minNavBarWidth);

    if (LessNotEqual(maxNavBarWidth.Value(), 0.0)) {
        maxNavBarWidth.SetValue(0);
    }
    NavigationModel::GetInstance()->SetMaxNavBarWidth(maxNavBarWidth);
}

void JSNavigation::SetOnNavBarStateChange(const JSCallbackInfo& info)
{
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
        NavigationModel::GetInstance()->SetOnNavBarStateChange(std::move(onNavBarStateChange));
    }
    info.ReturnSelf();
}

void JSNavigation::SetNavDestination(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction()) {
        LOGE("JSNavigation::SetNavDestination builder param is not a function.");
        return;
    }

    auto navigationStack = NavigationModel::GetInstance()->GetNavigationStack();
    auto jsNavigationStack = AceType::DynamicCast<JSNavigationStack>(navigationStack);
    if (jsNavigationStack) {
        jsNavigationStack->SetJSExecutionContext(info.GetExecutionContext());
        jsNavigationStack->SetNavDestBuilderFunc(JSRef<JSFunc>::Cast(builder));
    }
}
} // namespace OHOS::Ace::Framework
