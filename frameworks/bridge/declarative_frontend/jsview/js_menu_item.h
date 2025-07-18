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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MENU_ITEM_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MENU_ITEM_H

#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
class JSMenuItem : public JSContainerBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

    static void IsSelected(const JSCallbackInfo& info);
    static void SelectIcon(const JSCallbackInfo& info);
    static void OnChange(const JSCallbackInfo& info);

    static void ContentFont(const JSCallbackInfo& info);
    static void ContentFontColor(const JSCallbackInfo& info);
    static void LabelFont(const JSCallbackInfo& info);
    static void LabelFontColor(const JSCallbackInfo& info);

private:
    static void ParseMenuItemOptionsResource(
        const JSCallbackInfo& info, const JSRef<JSObject>& menuItemObj, MenuItemProperties& menuItemProps);
    static void AddMenuItemOptionsResource(const RefPtr<ResourceObject>& contentStrObj,
        const RefPtr<ResourceObject>& labelStrObj, const RefPtr<ResourceObject>& startIconObj,
        const RefPtr<ResourceObject>& endIconObj, MenuItemProperties& menuItemProps);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MENU_ITEM_H
