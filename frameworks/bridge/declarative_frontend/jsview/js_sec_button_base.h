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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SEC_BUTTON_BASE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SEC_BUTTON_BASE_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"
#include "core/event/mouse_event.h"
#include "core/gestures/click_recognizer.h"

namespace OHOS::Ace::Framework {
class JSSecButtonBase : public JSViewAbstract, public JSInteractableView {
public:
    static void SetIconSize(const JSCallbackInfo& info);
    static void SetIconColor(const JSCallbackInfo& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontStyle(const JSCallbackInfo& info);
    static void SetFontWeight(const JSCallbackInfo& info);
    static void SetFontFamily(const JSCallbackInfo& info);
    static void SetFontColor(const JSCallbackInfo& info);
    static void SetLayoutDirection(const JSCallbackInfo& info);
    static void SetBackgroundColor(const JSCallbackInfo& info);
    static void SetBackgroundPadding(const JSCallbackInfo& info);
    static void SetTextIconSpace(const JSCallbackInfo& info);
    static void SetBackgroundBorderStyle(const JSCallbackInfo& info);
    static void SetBackgroundBorderWidth(const JSCallbackInfo& info);
    static void SetBackgroundBorderColor(const JSCallbackInfo& info);
    static void SetBackgroundBorderRadius(const JSCallbackInfo& info);
    static void SetAlign(const JSCallbackInfo& info);
    static void SetMaxFontScale(const JSCallbackInfo& info);
    static void SetMinFontScale(const JSCallbackInfo& info);
    static void SetMaxLines(const JSCallbackInfo& info);
    static void SetMaxFontSize(const JSCallbackInfo& info);
    static void SetMinFontSize(const JSCallbackInfo& info);
    static void SetHeightAdaptivePolicy(int32_t value);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SEC_BUTTON_BASE_H
