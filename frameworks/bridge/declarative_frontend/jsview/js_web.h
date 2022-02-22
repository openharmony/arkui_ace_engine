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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WEB_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WEB_H

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
class JSWeb : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void OnPageStart(const JSCallbackInfo& args);
    static void OnPageFinish(const JSCallbackInfo& args);
    static void OnRequestFocus(const JSCallbackInfo& args);
    static void OnError(const JSCallbackInfo& args);
    static void OnMessage(const JSCallbackInfo& args);
    static void OnDownloadStart(const JSCallbackInfo& args);
    static void JsEnabled(bool isJsEnabled);
    static void ContentAccessEnabled(bool isContentAccessEnabled);
    static void FileAccessEnabled(bool isFileAccessEnabled);
    static void OnFocus(const JSCallbackInfo& args);
};
}
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WEB_H