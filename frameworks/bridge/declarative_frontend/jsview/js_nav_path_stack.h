/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAV_PATH_STACK_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAV_PATH_STACK_H

#include <functional>
#include <string>

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"

namespace OHOS::Ace::Framework {
class JSNavPathStack final : public Referenced {
public:
    JSNavPathStack()
    {
        containerCurrentId_ = Container::CurrentId();
    };
    ~JSNavPathStack() override = default;

    static void JSBind(BindingTarget globalObj);

    void OnStateChanged()
    {
        if (onStateChangedCallback_) {
            onStateChangedCallback_();
        }
    }

    void SetOnStateChangedCallback(std::function<void()> callback)
    {
        onStateChangedCallback_ = callback;
    }

    static JSRef<JSObject> CreateNewNavPathStackJSObject();
    static void SetNativeNavPathStack(JSRef<JSObject> jsStack, JSRef<JSObject> nativeStack);

    static bool CheckIsValid(JSValueWrapper object);

    void SetOnPopCallback(const std::function<void(const JSRef<JSVal>)>& popCallback)
    {
        onPopCallback_ = popCallback;
    }

    void OnPopCallback(const JSCallbackInfo& info);

private:
    static void Constructor(const JSCallbackInfo& info);
    static void Destructor(JSNavPathStack* stack);

    std::function<void()> onStateChangedCallback_;
    std::function<void(const JSRef<JSVal>)> onPopCallback_;
    int32_t containerCurrentId_;
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAV_PATH_STACK_H
