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
#include "base/system_bar/system_bar_style.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_navigation_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_nav_path_stack.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/jsview/js_navigation_utils.h"
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
constexpr Dimension DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;
constexpr uint32_t SAFE_AREA_TYPE_LIMIT = 3;
constexpr uint32_t SAFE_AREA_EDGE_LIMIT = 4;
constexpr uint32_t SAFE_AREA_EDGE_SYSTEM = 0;
constexpr uint32_t SAFE_AREA_EDGE_TOP = 0;
constexpr uint32_t SAFE_AREA_EDGE_BOTTOM = 1;
constexpr int32_t PARAMETER_LENGTH_ONE  = 1;
constexpr int32_t PARAMETER_LENGTH_TWO  = 2;
constexpr int32_t FIRST_INDEX  = 0;
constexpr int32_t SECOND_INDEX  = 1;

JSRef<JSVal> TitleModeChangeEventToJSValue(const NavigationTitleModeChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.IsMiniBar() ? static_cast<int32_t>(NavigationTitleMode::MINI)
                                                              : static_cast<int32_t>(NavigationTitleMode::FULL)));
}
} // namespace

void JSNavigation::ParseToolBarItems(const JSCallbackInfo& info, std::list<RefPtr<AceType>>& items)
{
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(info[0]);
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
            toolBarItem->action =
                EventMarker([func = std::move(onClickFunc), node = targetNode, execCtx = info.GetExecutionContext()]() {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("Navigation.toolBarItemClick");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute();
                });
            auto onClickWithParamFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            toolBarItem->actionWithParam =
                EventMarker([func = std::move(onClickWithParamFunc), node = targetNode,
                                execCtx = info.GetExecutionContext()](const BaseEventInfo* info) {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("Navigation.menuItemButtonClick");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute();
                });
        }
        items.push_back(toolBarItem);
    }
}

bool JSNavigation::ParseCommonTitle(const JSRef<JSObject>& jsObj)
{
    JSRef<JSVal> subtitle = jsObj->GetProperty("sub");
    JSRef<JSVal> title = jsObj->GetProperty("main");
    std::string mainTitle;
    std::string subTitle;
    bool hasSub = ParseJsString(subtitle, subTitle);
    bool hasMain = ParseJsString(title, mainTitle);
    if (hasSub || hasMain) {
        return NavigationModel::GetInstance()->ParseCommonTitle(
            hasSub, hasMain, subTitle, mainTitle);
    }
    return false;
}

void JSNavigation::Create(const JSCallbackInfo& info)
{
    JSRef<JSObject> newObj;
    std::string moduleName;
    std::string pagePath;
    if (info.Length() == 1) {
        // input format: navPathStack/pathInfo
        if (!info[0]->IsObject()) {
            return;
        }
        // instance of NavPathStack
        JSValueWrapper valueWrapper = info[0].Get().GetLocalHandle();
        if (!JSNavPathStack::CheckIsValid(valueWrapper)) {
            // first parameter = pathInfo{'moduleName': stringA, 'pagePath': stringB, 'isUserCreateStack': bool}
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "current stack is not navPathStack");
            auto infoObj = JSRef<JSObject>::Cast(info[0]);
            if (!infoObj->GetProperty(NG::NAVIGATION_MODULE_NAME)->IsString() ||
                !infoObj->GetProperty(NG::NAVIGATION_PAGE_PATH)->IsString()) {
                TAG_LOGE(AceLogTag::ACE_NAVIGATION, "current pageInfo is invalid");
                return;
            }
            moduleName = infoObj->GetProperty(NG::NAVIGATION_MODULE_NAME)->ToString();
            pagePath = infoObj->GetProperty(NG::NAVIGATION_PAGE_PATH)->ToString();
        } else {
            // first parameter = navPathStack
            newObj = JSRef<JSObject>::Cast(info[0]);
        }
    } else if (info.Length() == 2) {
        // parameter = navPathStack(maybe empty) + pathInfo
        if (!info[0]->IsObject() || !info[1]->IsObject()) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "stack or pageInfo is invalid");
            return;
        }
        // instance of NavPathStack
        JSValueWrapper valueWrapper = info[0].Get().GetLocalHandle();
        if (!JSNavPathStack::CheckIsValid(valueWrapper)) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "current stack is not navPathStack");
            return;
        }
        // pathInfo{'moduleName': stringA, 'pagePath': stringB, 'isUserCreateStack': bool}
        auto infoObj = JSRef<JSObject>::Cast(info[1]);
        auto isUserCreateStack = infoObj->GetProperty(NG::IS_USER_CREATE_STACK);
        bool isUserDefined = true;
        if (isUserCreateStack->IsBoolean()) {
            isUserDefined = isUserCreateStack->ToBoolean();
        }
        if (isUserDefined) {
            newObj = JSRef<JSObject>::Cast(info[0]);
        }
        if (!infoObj->GetProperty(NG::NAVIGATION_MODULE_NAME)->IsString() ||
            !infoObj->GetProperty(NG::NAVIGATION_PAGE_PATH)->IsString()) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "current pageInfo is invalid");
            return;
        }
        moduleName = infoObj->GetProperty(NG::NAVIGATION_MODULE_NAME)->ToString();
        pagePath = infoObj->GetProperty(NG::NAVIGATION_PAGE_PATH)->ToString();
    }

    NavigationModel::GetInstance()->Create();
    auto stackCreator = []() -> RefPtr<JSNavigationStack> { return AceType::MakeRefPtr<JSNavigationStack>(); };
    auto stackUpdater = [&newObj, &info](RefPtr<NG::NavigationStack> stack) {
        NavigationModel::GetInstance()->SetNavigationStackProvided(!newObj->IsEmpty());
        auto jsStack = AceType::DynamicCast<JSNavigationStack>(stack);
        CHECK_NULL_VOID(jsStack);
        jsStack->SetJSExecutionContext(info.GetExecutionContext());
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
    };
    NavigationModel::GetInstance()->SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    NavigationModel::GetInstance()->SetNavigationPathInfo(moduleName, pagePath);
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
    JSClass<JSNavigation>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSNavigation>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSNavigation>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSNavigation>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSNavigation>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNavigation>::StaticMethod("customNavContentTransition", &JSNavigation::SetCustomNavContentTransition);
    JSClass<JSNavigation>::StaticMethod("ignoreLayoutSafeArea", &JSNavigation::SetIgnoreLayoutSafeArea);
    JSClass<JSNavigation>::StaticMethod("systemBarStyle", &JSNavigation::SetSystemBarStyle);
    JSClass<JSNavigation>::StaticMethod("recoverable", &JSNavigation::SetRecoverable);
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
            JsFunction jsBuilderFunc(info.This(), JSRef<JSFunc>::Cast(builderObject));
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
    JSNavigationUtils::ParseTitleBarOptions(info, true, options);
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

void JSNavigation::SetHideTitleBar(bool isHide, bool animated)
{
    NavigationModel::GetInstance()->SetHideTitleBar(isHide, animated);
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
    auto isValidImage = false;
    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!noPixMap) {
        pixMap = CreatePixelMapFromNapiValue(info[0]);
    }
#endif
    if (noPixMap || pixMap != nullptr) {
        isValidImage = true;
    }
    std::vector<std::string> nameList;
    NG::ImageOption imageOption;
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(info[0], bundleName, moduleName);
    nameList.emplace_back(bundleName);
    nameList.emplace_back(moduleName);
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = isValidImage;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    auto isSymbol = info[0]->IsObject() && src.empty() && pixMap == nullptr;
    if (isSymbol) {
        SetSymbolOptionApply(info, iconSymbol, info[0]);
    }
    NavigationModel::GetInstance()->SetBackButtonIcon(iconSymbol, src, imageOption, pixMap, nameList);
}

void JSNavigation::SetHideBackButton(bool hide)
{
    NavigationModel::GetInstance()->SetHideBackButton(hide);
}

void JSNavigation::SetHideToolBar(bool isHide, bool animated)
{
    NavigationModel::GetInstance()->SetHideToolBar(isHide, animated);
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
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        JSNavigationUtils::ParseBarItems(targetNode, info, JSRef<JSArray>::Cast(itemsValue), toolBarItems);
        NavigationModel::GetInstance()->SetToolBarItems(std::move(toolBarItems));
        return;
    }
    std::list<RefPtr<AceType>> items;
    NavigationModel::GetInstance()->GetToolBarItems(items);
    ParseToolBarItems(info, items);
}

void JSNavigation::SetToolbarConfiguration(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() || info[0]->IsArray()) {
        if (NavigationModel::GetInstance()->NeedSetItems()) {
            std::vector<NG::BarItem> toolbarItems;
            if (info[0]->IsUndefined()) {
                toolbarItems = {};
            } else {
                auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
                JSNavigationUtils::ParseToolbarItemsConfiguration(
                    targetNode, info, JSRef<JSArray>::Cast(info[0]), toolbarItems);
            }
            NavigationModel::GetInstance()->SetToolbarConfiguration(std::move(toolbarItems));
        } else {
            std::list<RefPtr<AceType>> items;
            NavigationModel::GetInstance()->GetToolBarItems(items);
            ParseToolBarItems(info, items);
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
    JSNavigationUtils::ParseToolbarOptions(info, options);
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
                auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
                JSNavigationUtils::ParseBarItems(targetNode, info, JSRef<JSArray>::Cast(info[0]), menuItems);
            }
            NavigationModel::GetInstance()->SetMenuItems(std::move(menuItems));
            return;
        }
        std::list<RefPtr<AceType>> items;
        NavigationModel::GetInstance()->GetMenuItems(items);
        ParseToolBarItems(info, items);
    } else if (info[0]->IsObject()) {
        auto builderObject = JSRef<JSObject>::Cast(info[0])->GetProperty("builder");
        if (builderObject->IsFunction()) {
            ViewStackModel::GetInstance()->NewScope();
            JsFunction jsBuilderFunc(info.This(), JSRef<JSFunc>::Cast(builderObject));
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
    if (info[0]->IsNull() || info[0]->IsUndefined()) {
        NavigationModel::GetInstance()->SetMinNavBarWidth(NG::DEFAULT_MIN_NAV_BAR_WIDTH);
        NavigationModel::GetInstance()->SetMaxNavBarWidth(NG::DEFAULT_MAX_NAV_BAR_WIDTH);
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
    if (min->IsNull() || min->IsUndefined() || !ParseJsDimensionVp(min, minNavBarWidth)) {
        minNavBarWidth = NG::DEFAULT_MIN_NAV_BAR_WIDTH;
    }
    if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
        minNavBarWidth.SetValue(0);
    }
    NavigationModel::GetInstance()->SetMinNavBarWidth(minNavBarWidth);

    if (max->IsNull() || max->IsUndefined() || !ParseJsDimensionVp(max, maxNavBarWidth)) {
        maxNavBarWidth = NG::DEFAULT_MAX_NAV_BAR_WIDTH;
    }
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

    if (!info[0]->IsObject()) {
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
                                     RefPtr<NG::NavDestinationContext> from, RefPtr<NG::NavDestinationContext> to,
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
        JSRef<JSVal> interactive = transitionObj->GetProperty("isInteractive");
        if (interactive->IsBoolean()) {
            transition.interactive = interactive->ToBoolean();
        } else {
            transition.interactive = false;
        }
        int32_t timeout = -1;
        JSRef<JSVal> time = transitionObj->GetProperty("timeout");
        if (time->IsNumber()) {
            timeout = time->ToNumber<int32_t>();
        }
        if (!transition.interactive) {
            timeout = timeout < 0 ? NAVIGATION_ANIMATION_TIMEOUT : timeout;
        }
        transition.timeout = timeout;
        JSRef<JSVal> transitionContext = transitionObj->GetProperty("transition");
        if (!transitionContext->IsFunction()) {
            return transition;
        }
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

void JSNavigation::SetIgnoreLayoutSafeArea(const JSCallbackInfo& info)
{
    NG::SafeAreaExpandOpts opts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL};
    if (info.Length() >= PARAMETER_LENGTH_ONE && info[FIRST_INDEX]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[0]);
        uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            auto value = paramArray->GetValueAt(i);
            if (!value->IsNumber() ||
                value->ToNumber<uint32_t>() >= SAFE_AREA_TYPE_LIMIT ||
                value->ToNumber<uint32_t>() == SAFE_AREA_EDGE_SYSTEM) {
                safeAreaType = NG::SAFE_AREA_TYPE_SYSTEM;
                break;
            }
        }
        opts.type = safeAreaType;
    }

    if (info.Length() >= PARAMETER_LENGTH_TWO && info[SECOND_INDEX]->IsArray()) {
        auto paramArray = JSRef<JSArray>::Cast(info[1]);
        uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
        for (size_t i = 0; i < paramArray->Length(); ++i) {
            auto value = paramArray->GetValueAt(i);
            if (!value->IsNumber() ||
                value->ToNumber<uint32_t>() >= SAFE_AREA_EDGE_LIMIT) {
                safeAreaEdge = NG::SAFE_AREA_EDGE_ALL;
                break;
            }
            if (value->ToNumber<uint32_t>() == SAFE_AREA_EDGE_TOP ||
                value->ToNumber<uint32_t>() == SAFE_AREA_EDGE_BOTTOM) {
                    safeAreaEdge |= (1 << value->ToNumber<uint32_t>());
                }
        }
        opts.edges = safeAreaEdge;
    }
    NavigationModel::GetInstance()->SetIgnoreLayoutSafeArea(opts);
}

void JSNavigation::SetSystemBarStyle(const JSCallbackInfo& info)
{
    RefPtr<SystemBarStyle> style = nullptr;
    if (info.Length() == 1 && info[0]->IsObject()) {
        auto styleObj = JsConverter::ConvertJsValToNapiValue(info[0]);
        auto env = GetCurrentEnv();
        if (env) {
            style = SystemBarStyle::CreateStyleFromJsObj(env, styleObj);
        }
    }
    NavigationModel::GetInstance()->SetSystemBarStyle(style);
}

void JSNavigation::SetRecoverable(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        // the default value of navigation's recoverable is false
        NavigationModel::GetInstance()->SetRecoverable(false);
        return;
    }
    auto recoverable = info[0]->ToBoolean();
    NavigationModel::GetInstance()->SetRecoverable(recoverable);
}
} // namespace OHOS::Ace::Framework
