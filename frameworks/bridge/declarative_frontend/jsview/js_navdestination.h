/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVDESTINATION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVDESTINATION_H

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_navigation_stack.h"

namespace OHOS::Ace::Framework {

class JSNavDestination : public JSContainerBase {
public:
    static void Create();
    static void Create(const JSCallbackInfo& info);
    static void SetHideTitleBar(const JSCallbackInfo& info);
    static void SetTitle(const JSCallbackInfo& info);
    static void SetBackButtonIcon(const JSCallbackInfo& info);
    static void SetOnShown(const JSCallbackInfo& info);
    static void SetOnHidden(const JSCallbackInfo& info);
    static void SetOnBackPressed(const JSCallbackInfo& info);
    static void SetOnReady(const JSCallbackInfo& info);
    static void SetMode(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void SetMenus(const JSCallbackInfo& info);
    static void SetBackgroundColor(const JSCallbackInfo& info);
    static void SetWillAppear(const JSCallbackInfo& info);
    static void SetWillShow(const JSCallbackInfo& info);
    static void SetWillHide(const JSCallbackInfo& info);
    static void SetWillDisAppear(const JSCallbackInfo& info);
    static void SetToolBarConfiguration(const JSCallbackInfo& info);
    static void SetHideToolBar(const JSCallbackInfo& info);
    static void SetIgnoreLayoutSafeArea(const JSCallbackInfo& info);
    static void SetSystemBarStyle(const JSCallbackInfo& info);
    static void SetRecoverable(const JSCallbackInfo& info);
    static void SetSystemTransition(const JSCallbackInfo& info);
    static void BindToScrollable(const JSCallbackInfo& info);
    static void BindToNestedScrollable(const JSCallbackInfo& info);

private:
    static void CreateForPartialUpdate(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVDESTINATION_H
