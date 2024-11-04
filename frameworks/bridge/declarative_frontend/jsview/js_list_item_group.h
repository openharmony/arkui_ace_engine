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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_GROUP_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_GROUP_H

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/functions/js_mouse_function.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::Framework {

class JSListItemGroup : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& args);
    static void SetDivider(const JSCallbackInfo& args);
    static void SetAspectRatio(const JSCallbackInfo& args);
    static void SetChildrenMainSize(const JSCallbackInfo& args);
    static void SetChildrenMainSize(const JSRef<JSObject>& childrenSizeObj);
    static bool ParseHeaderAndFooterContent(const JSRef<JSVal>& contentParam, bool isHeader);
    static bool SetHeaderBuilder(const JSRef<JSObject>& obj);
    static bool SetFooterBuilder(const JSRef<JSObject>& obj);
    static V2::ListItemGroupStyle GetListItemGroupStyle(const JSCallbackInfo& args);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_GROUP_H
