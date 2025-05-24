/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_REPEAT_VIRTUAL_SCROLL_2_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_REPEAT_VIRTUAL_SCROLL_2_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"

namespace OHOS::Ace::Framework {

class JSRepeatVirtualScroll2 {
public:
    static void JSBind(BindingTarget globalObj);

    static void Create(const JSCallbackInfo& info);

    static void IsInAnimation(const JSCallbackInfo& info);
    static void RemoveNode(const JSCallbackInfo& info);
    static void SetInvalid(const JSCallbackInfo& info);
    static void RequestContainerReLayout(const JSCallbackInfo& info);
    static void NotifyContainerLayoutChange(const JSCallbackInfo& info);
    static void UpdateL1Rid4Index(const JSCallbackInfo& info);

    static void OnMove(const JSCallbackInfo& info);
    static void SetCreateByTemplate(const JSCallbackInfo& info);
    static void JsParseItemDragEventHandler(
        const JsiExecutionContext& context, const JSRef<JSObject>& itemDragEventObj, int32_t repeatElmtId);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_REPEAT_VIRTUAL_SCROLL_2_H
