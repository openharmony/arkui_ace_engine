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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_swiper_function.h"


namespace OHOS::Ace::Framework {
void JsSwiperFunction::Execute(int32_t index, int32_t targetIndex, const AnimationCallbackInfo& animationCallbackInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    float currentOffset = animationCallbackInfo.currentOffset.value_or(0.0f);
    float targetOffset = animationCallbackInfo.targetOffset.value_or(0.0f);
    float velocity = animationCallbackInfo.velocity.value_or(0.0f);

    obj->SetProperty<float>("currentOffset", currentOffset);
    obj->SetProperty<float>("targetOffset", targetOffset);
    obj->SetProperty<float>("velocity", velocity);

    int32_t paramCount = 3;
    JSRef<JSVal> params[paramCount];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    params[1] = JSRef<JSVal>::Make(ToJSValue(targetIndex));
    params[2] = obj;
    JsFunction::ExecuteJS(paramCount, params);
}

void JsSwiperFunction::Execute(int32_t index, const AnimationCallbackInfo& animationCallbackInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    float currentOffset = animationCallbackInfo.currentOffset.value_or(0.0f);
    float targetOffset = animationCallbackInfo.targetOffset.value_or(0.0f);
    float velocity = animationCallbackInfo.velocity.value_or(0.0f);

    obj->SetProperty<float>("currentOffset", currentOffset);
    obj->SetProperty<float>("targetOffset", targetOffset);
    obj->SetProperty<float>("velocity", velocity);

    int32_t paramCount = 2;
    JSRef<JSVal> params[paramCount];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    params[1] = obj;
    JsFunction::ExecuteJS(paramCount, params);
}
} // namespace OHOS::Ace::Framework
