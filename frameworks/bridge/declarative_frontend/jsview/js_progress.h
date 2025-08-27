/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PROGRESS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PROGRESS_H

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/pattern/progress/progress_model.h"

namespace OHOS::Ace::Framework {

enum class ProgressStyle {
    Linear,
    Ring,
    Eclipse,
    ScaleRing,
    Capsule,
};

class JSProgress : public JSViewAbstract {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);

    static void SetValue(double value);
    static void SetColor(const JSCallbackInfo& info);
    static void SetCircularStyle(const JSCallbackInfo& info);
    static void JsBackgroundColor(const JSCallbackInfo& info);
    static void JsBorderColor(const JSCallbackInfo& info);

private:
    static bool ConvertGradientColor(const JsiRef<JsiValue>& param, NG::Gradient& gradient);
    static NG::ProgressStatus ConvertStrToProgressStatus(const std::string& value);
    static void JsSetProgressStyleOptions(const JSCallbackInfo& info);
    static void JsSetLinearStyleOptions(const JSCallbackInfo& info);
    static void JsSetRingStyleOptions(const JSCallbackInfo& info);
    static void JsSetCapsuleStyle(const JSCallbackInfo& info);
    static void JsSetFontStyle(const JSCallbackInfo& info);
    static void JsSetFontDefault();
    static void JsSetFont(const JSRef<JSObject>& info);
    static void JsSetCommonOptions(const JSCallbackInfo& info);
    static void JsSetBorderRadius(const JSRef<JSObject>& paramObject);
    static void ProcessLinearStrokeWidth(const JSRef<JSObject>& paramObject);
    static void ProcessRingStrokeWidth(const JSRef<JSObject>& paramObject);
    static void ProcessCapsuleBorderWidth(const JSRef<JSObject>& paramObject);
    static void ProcessCapsuleBorderColor(const JSRef<JSObject>& paramObject);
    static void ProcessFontSizeOption(const JSRef<JSObject>& textObject);
    static void ProcessCapsuleContent(const JSRef<JSObject>& paramObject);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PROGRESS_H
