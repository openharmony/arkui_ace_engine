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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INTERACTABLE_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INTERACTABLE_VIEW_H

#include "frameworks/bridge/declarative_frontend/jsview/js_pan_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/gestures/tap_gesture.h"
#include "frameworks/core/gestures/tap_gesture.h"
#include "frameworks/core/pipeline/base/component.h"

namespace OHOS::Ace::Framework {

using RemoteCallback = std::function<void(const BaseEventInfo* info)>;

class JSInteractableView {
public:
    static void JsOnTouch(const JSCallbackInfo& args);
    static void JsOnPan(const JSCallbackInfo& args);
    static void JsOnClick(const JSCallbackInfo& info);
    static void JsTouchable(const JSCallbackInfo& info);
    static void JsOnHover(const JSCallbackInfo& info);
    static void JsOnKey(const JSCallbackInfo& args);
    static void JsOnKeyPreIme(const JSCallbackInfo& args);
    static void SetFocusable(bool focusable);
    static void SetFocusNode(bool isFocusNode);
    static void JsMonopolizeEvents(const JSCallbackInfo& info);

    static void JsOnAppear(const JSCallbackInfo& info);
    static void JsOnDisAppear(const JSCallbackInfo& info);
    static void JsOnAttach(const JSCallbackInfo& info);
    static void JsOnDetach(const JSCallbackInfo& info);
    static void JsOnDelete(const JSCallbackInfo& info);
    static void JsOnAccessibility(const JSCallbackInfo& info);
    static void JsCommonRemoteMessage(const JSCallbackInfo& info);

    static std::function<void()> GetRemoteMessageEventCallback(const JSCallbackInfo& info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
    static void ReportClickEvent(const WeakPtr<NG::FrameNode>& node, const std::string text = "");
#endif

protected:
    static void JsRemoteMessage(const JSCallbackInfo& info, RemoteCallback& remoteCallback);

private:
    static void SplitString(const std::string& str, char tag, std::vector<std::string>& strList);
}; // class JSInteractableView

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INTERACTABLE_VIEW_H
