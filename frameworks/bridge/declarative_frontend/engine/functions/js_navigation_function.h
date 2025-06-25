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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_NAVIGATION_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_NAVIGATION_FUNCTION_H

#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_declaration.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_transition_proxy.h"

namespace OHOS::Ace::Framework {

class JsNavigationFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsNavigationFunction, JsFunction)

public:
    explicit JsNavigationFunction(const JSRef<JSFunc>& jsFunction) : JsFunction(JSRef<JSObject>(), jsFunction) {}

    static void JSBind(BindingTarget globalObj);

    ~JsNavigationFunction() override {};

    void Execute()
    {
        ExecuteJS();
    }

    JSRef<JSVal> Execute(RefPtr<NG::NavDestinationContext> from,
        RefPtr<NG::NavDestinationContext> to, NG::NavigationOperation operation);

    void Execute(const RefPtr<NG::NavigationTransitionProxy>& proxy);
};

class JsNavigationTransitionProxy : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);

    void SetFromContentInfo(const JSCallbackInfo& info);

    void GetFromContentInfo(const JSCallbackInfo& info);

    void SetToContentInfo(const JSCallbackInfo& info);

    void GetToContentInfo(const JSCallbackInfo& info);

    void SetProxy(const RefPtr<NG::NavigationTransitionProxy>& proxy)
    {
        proxy_ = proxy;
    }

    RefPtr<NG::NavigationTransitionProxy> GetProxy() const
    {
        return proxy_;
    }

    void FinishTransition(const JSCallbackInfo& info);

    static JSRef<JSVal> ConvertContentInfo(RefPtr<NG::NavDestinationContext> info);

    void SetInteractive(const JSCallbackInfo& info);

    void GetInteractive(const JSCallbackInfo& info);

    void CancelAnimation(const JSCallbackInfo& info);

    void UpdateTransition(const JSCallbackInfo& info);

private:
    static void Constructor(const JSCallbackInfo& args);

    static void Destructor(JsNavigationTransitionProxy* proxy);

    RefPtr<NG::NavigationTransitionProxy> proxy_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_NAVIGATION_FUNCTION_H