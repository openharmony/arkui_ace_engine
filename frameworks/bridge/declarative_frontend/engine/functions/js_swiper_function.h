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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SWIPER_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SWIPER_FUNCTION_H

#include <cstdint>

#include "core/components_ng/pattern/swiper/swiper_content_transition_proxy.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {
class JsSwiperFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsSwiperFunction, JsFunction)

public:
    explicit JsSwiperFunction(const JSRef<JSFunc>& jsFunction) : JsFunction(JSRef<JSObject>(), jsFunction) {}
    static void JSBind(BindingTarget globalObj);

    ~JsSwiperFunction() override {};

    void Execute() override
    {
        ExecuteJS();
    }

    void Execute(int32_t index, int32_t targetIndex, const AnimationCallbackInfo& animationCallbackInfo);
    void Execute(int32_t index, const AnimationCallbackInfo& animationCallbackInfo);
    void Execute(int32_t errorCode);
    void Execute(const RefPtr<SwiperContentTransitionProxy>& proxy);
    void Execute(int32_t selectedIndex, int32_t index, float position, float mainAxisLength);
};

class JsSwiperContentTransitionProxy : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);
    void SetSelectedIndex(const JSCallbackInfo& args);
    void GetSelectedIndex(const JSCallbackInfo& args);
    void SetIndex(const JSCallbackInfo& args);
    void GetIndex(const JSCallbackInfo& args);
    void SetPosition(const JSCallbackInfo& args);
    void GetPosition(const JSCallbackInfo& args);
    void SetMainAxisLength(const JSCallbackInfo& args);
    void GetMainAxisLength(const JSCallbackInfo& args);
    void FinishTransition(const JSCallbackInfo& args);

    void SetProxy(const RefPtr<SwiperContentTransitionProxy>& proxy)
    {
        proxy_ = proxy;
    }

    RefPtr<SwiperContentTransitionProxy> GetProxy() const
    {
        return proxy_;
    }

private:
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JsSwiperContentTransitionProxy* proxy);
    RefPtr<SwiperContentTransitionProxy> proxy_;
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SWIPER_FUNCTION_H
