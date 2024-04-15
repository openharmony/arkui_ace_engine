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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_COLOR_METRICS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_COLOR_METRICS_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings.h"

namespace OHOS::Ace::Framework {
class JSColorMetrics final : public Referenced {
public:
    JSColorMetrics() = default;
    ~JSColorMetrics() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSColorMetrics* jsColorMetricsPtr);
    void JsSetColor(const JSCallbackInfo& info);
    void JsGetColor(const JSCallbackInfo& info);
    void JsSetRed(const JSCallbackInfo& info);
    void JsGetRed(const JSCallbackInfo& info);
    void JsSetBlue(const JSCallbackInfo& info);
    void JsGetBlue(const JSCallbackInfo& info);
    void JsSetGreen(const JSCallbackInfo& info);
    void JsGetGreen(const JSCallbackInfo& info);
    void JsSetAlpha(const JSCallbackInfo& info);
    void JsGetAlpha(const JSCallbackInfo& info);
    static void JsResourceColor(const JSCallbackInfo& info);
    static void JsNumericColor(const JSCallbackInfo& info);
    static void JsRGBAColor(const JSCallbackInfo& info);
    void JsBlendColor(const JSCallbackInfo& info);
    void SetColor(const Color& color)
    {
        color_ = color;
    }

private:
    Color color_;
    ACE_DISALLOW_COPY_AND_MOVE(JSColorMetrics);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_COLOR_METRICS_H