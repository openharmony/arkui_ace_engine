/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MENU_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MENU_H

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
namespace OHOS::Ace::Framework {

enum class SubMenuExpandingMode {
    SIDE = 0,
    EMBEDDED,
    STACK
};

class JSMenu : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void FontSize(const JSCallbackInfo& info);
    static void Font(const JSCallbackInfo& info);
    static void FontColor(const JSCallbackInfo& info);
    static void SetWidth(const JSCallbackInfo& info);
    static void SetRadius(const JSCallbackInfo& info);
    static void SetExpandingMode(const JSCallbackInfo& info);
    static void SetItemDivider(const JSCallbackInfo& args);
    static void SetItemGroupDivider(const JSCallbackInfo& args);

private:
    static void HandleDifferentRadius(const JSRef<JSVal>& args);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MENU_H
