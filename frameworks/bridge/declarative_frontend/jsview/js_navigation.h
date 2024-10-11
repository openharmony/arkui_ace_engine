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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_VIEW_H

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/core/components/navigation_bar/navigation_container_component.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::Framework {

class JSNavigation : public JSContainerBase {
public:
    static void Create();
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void SetTitleMode(int32_t value);
    static void SetTitle(const JSCallbackInfo& info);
    static void SetSubTitle(const std::string& subTitle);
    static void SetHideTitleBar(bool isHide, bool animated);
    static void SetHideBackButton(bool hide);
    static void SetHideToolBar(bool isHide, bool animated);
    static void SetToolBar(const JSCallbackInfo& info);
    static void SetToolbarConfiguration(const JSCallbackInfo& info);
    static void SetMenus(const JSCallbackInfo& info);
    static void SetMenuCount(int32_t menuCount);
    static void SetOnTitleModeChanged(const JSCallbackInfo& info);
    static void SetUsrNavigationMode(const JSCallbackInfo& info);
    static void SetOnNavigationModeChange(const JSCallbackInfo& info);
    static void SetNavBarWidth(const JSCallbackInfo& info);
    static void SetNavBarWidthRange(const JSCallbackInfo& info);
    static void SetMinContentWidth(const JSCallbackInfo& info);
    static void SetNavBarPosition(int32_t value);
    static void SetHideNavBar(bool hide);
    static void SetBackButtonIcon(const JSCallbackInfo& info);
    static void SetOnNavBarStateChange(const JSCallbackInfo& info);
    static void SetNavDestination(const JSCallbackInfo& info);

    static void ParseToolBarItems(const JSCallbackInfo& info, std::list<RefPtr<AceType>>& items);
    static bool ParseCommonTitle(const JSRef<JSObject>& jsObj);

    static void SetCustomNavContentTransition(const JSCallbackInfo& info);

    static void SetIgnoreLayoutSafeArea(const JSCallbackInfo& info);
    static void SetSystemBarStyle(const JSCallbackInfo& info);
    static void SetRecoverable(const JSCallbackInfo& info);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATION_VIEW_H
