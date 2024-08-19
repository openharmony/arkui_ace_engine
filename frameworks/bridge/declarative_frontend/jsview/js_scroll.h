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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLL_H

#include "base/utils/noncopyable.h"
#include "bridge/declarative_frontend/jsview/js_scrollable_base.h"

namespace OHOS::Ace::Framework {

class JSScroll : public JSScrollableBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

    static void SetScrollable(int32_t value);

    static void OnScrollBeginCallback(const JSCallbackInfo& args);
    static void OnScrollFrameBeginCallback(const JSCallbackInfo& args);
    static void OnScrollCallback(const JSCallbackInfo& args);
    static void OnWillScrollCallback(const JSCallbackInfo& args);
    static void OnDidScrollCallback(const JSCallbackInfo& args);
    static void OnScrollEdgeCallback(const JSCallbackInfo& args);
    static void OnScrollEndCallback(const JSCallbackInfo& args);
    static void OnScrollStartCallback(const JSCallbackInfo& args);
    static void OnScrollStopCallback(const JSCallbackInfo& args);
    static void ReachStartCallback(const JSCallbackInfo& args);
    static void ReachEndCallback(const JSCallbackInfo& args);
    static void SetScrollBarColor(const JSCallbackInfo& args);
    static void SetScrollBarWidth(const JSCallbackInfo& args);
    static void SetScrollBar(const JSCallbackInfo& args);
    static void SetEdgeEffect(const JSCallbackInfo& args);
    static void JsWidth(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void SetNestedScroll(const JSCallbackInfo& args);
    static void SetScrollEnabled(const JSCallbackInfo& args);
    static void SetFriction(const JSCallbackInfo& info);
    static void SetScrollSnap(const JSCallbackInfo& args);
    static void SetEnablePaging(const JSCallbackInfo& args);
    static void SetInitialOffset(const JSCallbackInfo& args);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLL_H
