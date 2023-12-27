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
    static void SetHideTitleBar(bool hide);
    static void SetTitle(const JSCallbackInfo& info);
    static void SetBackButtonIcon(const JSCallbackInfo& info);
    static void SetOnShown(const JSCallbackInfo& info);
    static void SetOnHidden(const JSCallbackInfo& info);
    static void SetOnBackPressed(const JSCallbackInfo& info);
    static void SetMode(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

private:
    JSWeak<JSFunc> jsShownFunc_;
    JSWeak<JSFunc> jsHiddenFunc_;
    JSWeak<JSFunc> jsBackPressedFunc_;
    static void CreateForPartialUpdate(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVDESTINATION_H
