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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_APP_BAR_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_APP_BAR_VIEW_H

#include <functional>
#include <optional>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

class JSAppBar : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void CallNative(const JSCallbackInfo& info);

private:
    static void OnMenuClick(const JSCallbackInfo& info);
    static void OnCloseClick(const JSCallbackInfo& info);
    static void RequestAtomicServiceTerminate(const JSCallbackInfo& info);
    static void OnDidBuild(const JSCallbackInfo& info);
    static void OnCreateServicePanel(const JSCallbackInfo& info);
    static std::string GetStringValueFromJSObject(const JSRef<JSObject>& object, const char* prop);
    static void GetParamsFromJSArray(const JSRef<JSArray>& jsArray, std::map<std::string, std::string>& params);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_APP_BAR_VIEW_H
