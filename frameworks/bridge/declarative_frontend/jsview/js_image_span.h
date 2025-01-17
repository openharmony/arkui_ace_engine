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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_SPAN_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_SPAN_H

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
class JSImageSpan : public JSViewAbstract {
public:
    static void Create(const JSCallbackInfo& info);
    static void SetAlt(const JSCallbackInfo& info);
    static void SetObjectFit(const JSCallbackInfo& info);
    static void SetVerticalAlign(int32_t verticalAlign);
    static void SetTextBackgroundStyle(const JSCallbackInfo& info);
    static void SetBaselineOffset(const JSCallbackInfo& info);
    static void GetJsMediaBundleInfo(const JSRef<JSVal>& jsValue, std::string& bundleName, std::string& moduleName);
    static void OnComplete(const JSCallbackInfo& args);
    static void OnError(const JSCallbackInfo& args);
    static void JSBind(BindingTarget globalObj);
    static void SetColorFilter(const JSCallbackInfo& info);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_SPAN_H
