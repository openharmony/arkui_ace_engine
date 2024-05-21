/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SIDE_BAR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SIDE_BAR_H

#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"
#include "core/components/side_bar/side_bar_container_component.h"

namespace OHOS::Ace::Framework {

enum class SideBarControlButtonType {
    SHOWN = 0,
    HIDDEN,
    SWITCHING,
};

class JSSideBar : public JSStack {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void SetShowControlButton(const JSCallbackInfo& info);
    static void OnChange(const JSCallbackInfo& info);
    static void JsSideBarWidth(const JSCallbackInfo& info);
    static void JsMaxSideBarWidth(const JSCallbackInfo& info);
    static void JsMinSideBarWidth(const JSCallbackInfo& info);
    static void JsShowSideBar(const JSCallbackInfo& info);
    static void JsControlButton(const JSCallbackInfo& info);
    static void JsDivider(const JSCallbackInfo& info);
    static void JsMinContentWidth(const JSCallbackInfo& info);
    static void JsAutoHide(bool autoHide);
    static void JsSideBarPosition(const JSCallbackInfo& info);
    static void CreateForNG(const JSCallbackInfo& info);
    static void JsControlButtonForNG(const JSCallbackInfo& info);
private:
    static void SetControlButtonIcon(SideBarControlButtonType iconType, JSRef<JSVal> icon);
    static void ParseControlButtonOG(JSRef<JSObject> value);
    static void ParseControlButtonNG(JSRef<JSObject> value);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SIDE_BAR_H
