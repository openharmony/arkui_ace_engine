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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_H

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/functions/js_mouse_function.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

class JSListItem : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& args);
    static void Pop();
    static void CreateForPartialUpdate(const JSCallbackInfo& args);
    static void SetSticky(int32_t sticky);
    static void SetEditable(const JSCallbackInfo& args);
    static void SetSelectable(const JSCallbackInfo& info);
    static void SetSelected(const JSCallbackInfo& info);
    static void SetSwiperAction(const JSCallbackInfo& args);
    static void ParseSwiperAction(const JSRef<JSObject>& obj, const JsiExecutionContext& context,
        NG::FrameNode* node = nullptr);
    static void SelectCallback(const JSCallbackInfo& args);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void JsOnDragStart(const JSCallbackInfo& info);
    static void JsParseDeleteArea(const JsiExecutionContext& context, const JSRef<JSVal>& jsValue,
        bool isStartArea, NG::FrameNode* node);
    static void ParseBuilderComponentContent(const JSRef<JSVal>& contentParam, RefPtr<NG::FrameNode>& refPtrFrameNode);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_H
