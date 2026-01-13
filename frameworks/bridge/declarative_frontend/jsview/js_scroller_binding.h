/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLLER_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLLER_BINDING_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"

namespace OHOS::Ace::Framework {

class JSScrollerBinding : public JSScroller {
public:
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSScroller* scroller);

    void ScrollTo(const JSCallbackInfo& args);
    void ScrollEdge(const JSCallbackInfo& args);
    void Fling(const JSCallbackInfo& args);
    void ScrollPage(const JSCallbackInfo& args);
    void CurrentOffset(const JSCallbackInfo& args);
    void Offset(const JSCallbackInfo& args);
    void ScrollToIndex(const JSCallbackInfo& args);
    void ScrollBy(const JSCallbackInfo& args);
    void IsAtEnd(const JSCallbackInfo& args);
    void GetItemRect(const JSCallbackInfo& args);
    void GetItemIndex(const JSCallbackInfo& args);
    void ContentSize(const JSCallbackInfo& args);

private:
    bool ParseCurveParams(RefPtr<Curve>& curve, const JSRef<JSVal>& jsValue);
    ACE_DISALLOW_COPY_AND_MOVE(JSScrollerBinding);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLLER_BINDING_H
