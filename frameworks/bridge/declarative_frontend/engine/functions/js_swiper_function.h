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

#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {
class JsSwiperFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsSwiperFunction, JsFunction)

public:
    explicit JsSwiperFunction(const JSRef<JSFunc>& jsFunction) : JsFunction(JSRef<JSObject>(), jsFunction) {}

    ~JsSwiperFunction() override
    {
        LOGD("Destroy: JsSwiperFunction");
    };

    void Execute() override
    {
        ExecuteJS();
    }

    void Execute(int32_t index, int32_t targetIndex, const AnimationCallbackInfo& animationCallbackInfo);
    void Execute(int32_t index, const AnimationCallbackInfo& animationCallbackInfo);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SWIPER_FUNCTION_H
