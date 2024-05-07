/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/functions/js_navigation_function.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_nav_path_stack.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/navigation_model_impl.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"

namespace OHOS::Ace {
std::unique_ptr<NavigationModel> NavigationModel::instance_ = nullptr;
std::mutex NavigationModel::mutex_;
constexpr int32_t NAVIGATION_ANIMATION_TIMEOUT = 1000; // ms

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
constexpr Dimension DEFAULT_MIN_NAV_BAR_WIDTH = 240.0_vp;
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
        ParseJsMedia(itemIconObject, icon);
        toolBarItem->icon = icon;
        auto itemActionValue = itemObject->GetProperty("action");
        if (itemActionValue->IsFunction()) {
            auto onClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            toolBarItem->action = EventMarker([func = std::move(onClickFunc), node = targetNode]() {
                ACE_SCORING_EVENT("Navigation.toolBarItemClick");
                PipelineContext::SetCallBackNode(node);
                func->Execute();
            });
            auto onClickWithParamFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            toolBarItem->actionWithParam =
                EventMarker([func = std::move(onClickWithParamFunc), node = targetNode](const BaseEventInfo* info) {
                    ACE_SCORING_EVENT("Navigation.menuItemButtonClick");
                    PipelineContext::SetCallBackNode(node);
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
            continue;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        NG::BarItem toolBarItem;
        auto itemValueObject = itemObject->GetProperty("value");
        if (itemValueObject->IsString()) {
            toolBarItem.text = itemValueObject->ToString();
        }

        auto itemSymbolIconObject = itemObject->GetProperty("symbolIcon");
        if (!itemSymbolIconObject->IsUndefined()) {
            std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol;
            SetSymbolOptionApply(info, iconSymbol, itemSymbolIconObject);
            toolBarItem.iconSymbol = iconSymbol;
        }
        auto itemIconObject = itemObject->GetProperty("icon");
        if (itemIconObject->IsString()) {
            toolBarItem.icon = itemIconObject->ToString();
        }

        auto itemEnabledObject = itemObject->GetProperty("isEnabled");
        if (itemEnabledObject->IsBoolean()) {
            toolBarItem.isEnabled = itemEnabledObject->ToBoolean();
        }

        auto itemActionValue = itemObject->GetProperty("action");
        if (itemActionValue->IsFunction()) {
            RefPtr<JsFunction> onClickFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto onItemClick = [execCtx = info.GetExecutionContext(), func = std::move(onClickFunc),
                                   node = targetNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                if (func) {
                    PipelineContext::SetCallBackNode(node);
                    func->ExecuteJS();
                }
            };
            toolBarItem.action = onItemClick;
        }
        items.push_back(toolBarItem);
    }
}

void JSNavigation::ParseSymbolAndIcon(const JSCallbackInfo& info, NG::BarItem& toolBarItem,
    const JSRef<JSObject>& itemObject)
{
    std::string icon;
    std::string activeIcon;
    auto itemSymbolIconObject = itemObject->GetProperty("symbolIcon");
    if (!itemSymbolIconObject->IsUndefined()) {
        std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol;
        SetSymbolOptionApply(info, iconSymbol, itemSymbolIconObject);
        toolBarItem.iconSymbol = iconSymbol;
    }
    auto itemIconObject = itemObject->GetProperty("icon");
    if (ParseJsMedia(itemIconObject, icon)) {
        toolBarItem.icon = icon;
    }

    auto itemActiveSymbolIconObject = itemObject->GetProperty("activeSymbolIcon");
    if (!itemActiveSymbolIconObject->IsUndefined()) {
        std::function<void(WeakPtr<NG::FrameNode>)> activeSymbol;
        SetSymbolOptionApply(info, activeSymbol, itemActiveSymbolIconObject);
        toolBarItem.activeIconSymbol = activeSymbol;
    }
    auto itemActiveIconObject = itemObject->GetProperty("activeIcon");
    if (ParseJsMedia(itemActiveIconObject, activeIcon)) {
        toolBarItem.activeIcon = activeIcon;
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

        auto itemObject = JSRef<JSObject>::Cast(item);
        auto itemValueObject = itemObject->GetProperty("value");
        if (ParseJsString(itemValueObject, text)) {
            toolBarItem.text = text;
        }

        auto itemActionValue = itemObject->GetProperty("action");
        if (itemActionValue->IsFunction()) {
            RefPtr<JsFunction> onClickFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto onItemClick = [execCtx = info.GetExecutionContext(), func = std::move(onClickFunc),
                                   node = targetNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                if (func) {
                    PipelineContext::SetCallBackNode(node);
                    func->ExecuteJS();
                }
            };
            toolBarItem.action = onItemClick;
        }

        auto itemStatusValue = itemObject->GetProperty("status");
        if (itemStatusValue->IsNumber()) {
            toolBarItem.status = static_cast<NG::NavToolbarItemStatus>(itemStatusValue->ToNumber<int32_t>());
        }
        ParseSymbolAndIcon(info, toolBarItem, itemObject);
        items.push_back(toolBarItem);
    }
}

bool JSNavigation::ParseCommonTitle(const JSRef<JSObject>& jsObj)
{
    JSRef<JSVal> subtitle = jsObj->GetProperty("sub");
    JSRef<JSVal> title = jsObj->GetProperty("main");
    bool hasSub = subtitle->IsString();
    bool hasMain = title->IsString();
    if (hasSub || hasMain) {
        return NavigationModel::GetInstance()->ParseCommonTitle(
            hasSub, hasMain, subtitle->ToString(), title->ToString());
    }
    return false;
}

void JSNavigation::Create(const JSCallbackInfo& info)
{
    JSRef<JSObject> newObj;
    if (info.Length() > 0) {
        if (!info[0]->IsObject()) {
            return;
        }
        newObj = JSRef<JSObject>::Cast(info[0]);
        auto value = newObj->GetProperty("type");
        if (value->ToString() != "NavPathStack") {
            return;
        }
    }

    NavigationModel::GetInstance()->Create();
    auto stackCreator = []() -> RefPtr<JSNavigationStack> { return AceType::MakeRefPtr<JSNavigationStack>(); };
    auto stackUpdater = [&newObj, &info](RefPtr<NG::NavigationStack> stack) {
        NavigationModel::GetInstance()->SetNavigationStackProvided(!newObj->IsEmpty());
        auto jsStack = AceType::DynamicCast<JSNavigationStack>(stack);
        CHECK_NULL_VOID(jsStack);
        const auto& oldObj = jsStack->GetDataSourceObj();
        if (oldObj->IsEmpty()) {
            if (newObj->IsEmpty()) {
                newObj = JSNavPathStack::CreateNewNavPathStackJSObject();
            }
            auto nativeObj = JSClass<JSNavPathStack>::NewInstance();
            JSNavPathStack::SetNativeNavPathStack(newObj, nativeObj);
            jsStack->SetDataSourceObj(newObj);
        } else if (!newObj->IsEmpty()) {
            auto objStrictEqual = [](const JSRef<JSVal>& obja, const JSRef<JSVal>& objb) -> bool {
                return obja->GetLocalHandle()->IsStrictEquals(obja->GetEcmaVM(), objb->GetLocalHandle());
            };
            if (objStrictEqual(newObj, oldObj)) {
                return;
            }
            auto nativeObj = JSClass<JSNavPathStack>::NewInstance();
            JSNavPathStack::SetNativeNavPathStack(newObj, nativeObj);
            jsStack->SetDataSourceObj(newObj);
        }
        jsStack->SetJSExecutionContext(info.GetExecutionContext());
    };
    NavigationModel::GetInstance()->SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
}

void JSNavigation::JSBind(BindingTarget globalObj)
{
    JsNavigationTransitionProxy::JSBind(globalObj);
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
    JSClass<JSNavigation>::StaticMethod("onNavigationModeChange", &JSNavigation::SetOnNavigationModeChange);
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
    JSClass<JSNavigation>::StaticMethod("customNavContentTransition", &JSNavigation::SetCustomNavContentTransition);
    JSClass<JSNavigation>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSNavigation::SetTitle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    // Resource and string type.
    std::string title;
    if (ParseJsString(info[0], title)) {
        NavigationModel::GetInstance()->ParseCommonTitle(false, true, "", title);
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        do {
            // NavigationCommonTitle
            if (ParseCommonTitle(jsObj)) {
                break;
            }
            // CustomBuilder | NavigationCustomTitle
            CalcDimension titleHeight;
            if (!jsObj->HasProperty("height")) {
                NavigationModel::GetInstance()->SetTitleHeight(titleHeight, false);
                break;
            }
            JSRef<JSVal> height = jsObj->GetProperty("height");
            bool isValid = JSContainerBase::ParseJsDimensionVpNG(height, titleHeight);
            if (height->IsString()) {
                std::string heightValue;
                ParseJsString(height, heightValue);
                if (heightValue == NG::TITLE_MAIN_WITH_SUB) {
                    NavigationModel::GetInstance()->SetTitleHeight(NG::DOUBLE_LINE_TITLEBAR_HEIGHT);
                    break;
                }
                if (heightValue == NG::TITLE_MAIN) {
                    NavigationModel::GetInstance()->SetTitleHeight(NG::SINGLE_LINE_TITLEBAR_HEIGHT);
                    break;
                }
            }
            if (!isValid || titleHeight.Value() < 0) {
                NavigationModel::GetInstance()->SetTitleHeight(Dimension(), true);
                break;
            }
            NavigationModel::GetInstance()->SetTitleHeight(titleHeight);
        } while (0);
        JSRef<JSVal> builderObject = jsObj->GetProperty("builder");
        if (builderObject->IsFunction()) {
            ViewStackModel::GetInstance()->NewScope();
            JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
            ACE_SCORING_EVENT("Navigation.title.builder");
            jsBuilderFunc.Execute();
            auto customNode = ViewStackModel::GetInstance()->Finish();
            NavigationModel::GetInstance()->SetCustomTitle(customNode);
        }
    } else {
        NavigationModel::GetInstance()->ParseCommonTitle(false, false, "", "");
        return;
    }

    NG::NavigationTitlebarOptions options;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<NavigationBarTheme>();
        CHECK_NULL_VOID(theme);
        auto blurStyle = static_cast<BlurStyle>(theme->GetTitlebarBackgroundBlurStyle());
        if (blurStyle != BlurStyle::NO_MATERIAL) {
            options.bgOptions.blurStyle = blurStyle;
            options.bgOptions.color = Color::TRANSPARENT;
        }
    }
    if (info.Length() > 1) {
        ParseBackgroundOptions(info[1], options.bgOptions);
    }
    NavigationModel::GetInstance()->SetTitlebarOptions(std::move(options));
}

void JSNavigation::SetTitleMode(int32_t value)
{
    if (value >= 0 && value <= TITLE_MODE_RANGE) {
        NavigationModel::GetInstance()->SetTitleMode(static_cast<NG::NavigationTitleMode>(value));
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
    std::vector<std::string> nameList;
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(info[0], bundleName, moduleName);
    nameList.emplace_back(bundleName);
    nameList.emplace_back(moduleName);

    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol;
    if (src.empty() && pixMap == nullptr) {
        SetSymbolOptionApply(info, iconSymbol, info[0]);
    }

    NavigationModel::GetInstance()->SetBackButtonIcon(iconSymbol, src, noPixMap, pixMap, nameList);
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
        return;
    }
    if (!info[0]->IsObject() && !info[0]->IsUndefined()) {
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
        } else {
            std::list<RefPtr<AceType>> items;
            NavigationModel::GetInstance()->GetToolBarItems(items);
            ParseToolBarItems(JSRef<JSArray>::Cast(info[0]), items);
        }
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

    NG::NavigationToolbarOptions options;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<NavigationBarTheme>();
        CHECK_NULL_VOID(theme);
        auto blurStyle = static_cast<BlurStyle>(theme->GetToolbarBackgroundBlurStyle());
        if (blurStyle != BlurStyle::NO_MATERIAL) {
            options.bgOptions.blurStyle = blurStyle;
            options.bgOptions.color = Color::TRANSPARENT;
        }
    }
    if (info.Length() > 1) {
        ParseBackgroundOptions(info[1], options.bgOptions);
    }
    NavigationModel::GetInstance()->SetToolbarOptions(std::move(options));
}

void JSNavigation::SetMenus(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
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
    }
}

void JSNavigation::SetMenuCount(int32_t menuCount)
{
    NavigationModel::GetInstance()->SetMenuCount(menuCount);
}

void JSNavigation::SetOnTitleModeChanged(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsFunction()) {
        auto onTitleModeChangeCallback =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onTitleModeChange = [execCtx = info.GetExecutionContext(), func = std::move(onTitleModeChangeCallback),
                                     node = targetNode](NG::NavigationTitleMode mode) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("OnTitleModeChange");
            PipelineContext::SetCallBackNode(node);
            JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(mode));
            func->ExecuteJS(1, &param);
        };
        auto changeHandler = AceType::MakeRefPtr<JsEventFunction<NavigationTitleModeChangeEvent, 1>>(
            JSRef<JSFunc>::Cast(info[0]), TitleModeChangeEventToJSValue);
        auto eventInfo = [executionContext = info.GetExecutionContext(), func = std::move(changeHandler),
                             node = targetNode](const BaseEventInfo* baseInfo) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
            auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(baseInfo);
            if (!eventInfo) {
                return;
            }
            ACE_SCORING_EVENT("Navigation.onTitleModeChanged");
            PipelineContext::SetCallBackNode(node);
            func->Execute(*eventInfo);
        };
        NavigationModel::GetInstance()->SetOnTitleModeChange(std::move(onTitleModeChange), std::move(eventInfo));
    }
    info.ReturnSelf();
}

void JSNavigation::SetUsrNavigationMode(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        NavigationModel::GetInstance()->SetUsrNavigationMode(NG::NavigationMode::AUTO);
        return;
    }
    int32_t value = info[0]->ToNumber<int32_t>();
    if (value >= 0 && value <= NAVIGATION_MODE_RANGE) {
        NavigationModel::GetInstance()->SetUsrNavigationMode(static_cast<NG::NavigationMode>(value));
    }
}

void JSNavigation::SetNavBarPosition(int32_t value)
{
    if (value >= 0 && value <= NAV_BAR_POSITION_RANGE) {
        NavigationModel::GetInstance()->SetNavBarPosition(static_cast<NG::NavBarPosition>(value));
    }
}

void JSNavigation::SetNavBarWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
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
        return;
    }
    if (!info[0]->IsArray()) {
        return;
    }
    auto rangeArray = JSRef<JSArray>::Cast(info[0]);
    JSRef<JSVal> min = rangeArray->GetValueAt(0);
    JSRef<JSVal> max = rangeArray->GetValueAt(1);

    CalcDimension minNavBarWidth;

    CalcDimension maxNavBarWidth;
    ParseJsDimensionVp(max, maxNavBarWidth);

    if (!ParseJsDimensionVp(min, minNavBarWidth)) {
        minNavBarWidth.SetValue(DEFAULT_MIN_NAV_BAR_WIDTH.Value());
    }
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
        return;
    }

    if (info[0]->IsFunction()) {
        auto onNavBarStateChangeCallback =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onNavBarStateChange = [execCtx = info.GetExecutionContext(), func = std::move(onNavBarStateChangeCallback),
                                       node = targetNode](bool isVisible) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("OnNavBarStateChange");
            PipelineContext::SetCallBackNode(node);
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
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto builder = obj->GetProperty("builder");
    if (!builder->IsFunction()) {
        return;
    }

    auto navigationStack = NavigationModel::GetInstance()->GetNavigationStack();
    auto jsNavigationStack = AceType::DynamicCast<JSNavigationStack>(navigationStack);
    if (jsNavigationStack) {
        jsNavigationStack->SetNavDestBuilderFunc(JSRef<JSFunc>::Cast(builder));
    }
}

void JSNavigation::SetOnNavigationModeChange(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsFunction()) {
        info.ReturnSelf();
        return;
    }
    auto onModeChangeCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onModeChange = [execCtx = info.GetExecutionContext(), func = std::move(onModeChangeCallback),
                            node = targetNode](NG::NavigationMode mode) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("OnNavigationModeChange");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(static_cast<int8_t>(mode)));
        func->ExecuteJS(1, &param);
    };
    NavigationModel::GetInstance()->SetOnNavigationModeChange(std::move(onModeChange));
    info.ReturnSelf();
}

void JSNavigation::SetCustomNavContentTransition(const JSCallbackInfo& info)
{
    if (info.Length() == 0 || !info[0]->IsFunction()) {
        NavigationModel::GetInstance()->SetIsCustomAnimation(false);
        return;
    }
    RefPtr<JsNavigationFunction> jsNavigationFunction =
        AceType::MakeRefPtr<JsNavigationFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onNavigationAnimation = [execCtx = info.GetExecutionContext(), func = std::move(jsNavigationFunction)](
                                     NG::NavContentInfo from, NG::NavContentInfo to,
                                     NG::NavigationOperation operation) -> NG::NavigationTransition {
        NG::NavigationTransition transition;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, transition);
        auto ret = func->Execute(from, to, operation);
        if (!ret->IsObject()) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "custom transition is invalid, do default animation");
            transition.isValid = false;
            return transition;
        }

        auto transitionObj = JSRef<JSObject>::Cast(ret);
        JSRef<JSVal> time = transitionObj->GetProperty("timeout");
        if (time->IsNumber()) {
            auto timeout = time->ToNumber<int32_t>();
            transition.timeout = (timeout >= 0) ? timeout : NAVIGATION_ANIMATION_TIMEOUT;
        } else {
            transition.timeout = NAVIGATION_ANIMATION_TIMEOUT;
        }
        JSRef<JSVal> transitionContext = transitionObj->GetProperty("transition");
        auto jsOnTransition = AceType::MakeRefPtr<JsNavigationFunction>(JSRef<JSFunc>::Cast(transitionContext));
        if (transitionContext->IsFunction()) {
            auto onTransition = [execCtx, func = std::move(jsOnTransition)](
                                    const RefPtr<NG::NavigationTransitionProxy>& proxy) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("transition");
                func->Execute(proxy);
            };
            transition.transition = std::move(onTransition);
        }
        JSRef<JSVal> endCallback = transitionObj->GetProperty("onTransitionEnd");
        if (endCallback->IsFunction()) {
            auto onEndedCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(endCallback));
            auto onEndTransition = [execCtx, func = std::move(onEndedCallback)](bool isSuccess) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("onTransitionEnded");
                JSRef<JSVal> successVal = JSRef<JSVal>::Make(ToJSValue(isSuccess));
                func->ExecuteJS(1, &successVal);
            };
            transition.endCallback = std::move(onEndTransition);
        }
        return transition;
    };
    NavigationModel::GetInstance()->SetIsCustomAnimation(true);
    NavigationModel::GetInstance()->SetCustomTransition(onNavigationAnimation);
}
} // namespace OHOS::Ace::Framework
