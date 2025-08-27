/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_DIALOG_JS_CUSTOM_DIALOG_CONTROLLER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_DIALOG_JS_CUSTOM_DIALOG_CONTROLLER_H

#include "core/components/dialog/dialog_component.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/core/components_ng/pattern/dialog/custom_dialog_controller_model.h"

namespace OHOS::Ace::Framework {

class JSCustomDialogController : public virtual AceType {
    DECLARE_ACE_TYPE(JSCustomDialogController, AceType);

public:
    explicit JSCustomDialogController(JSView* ownerView) : ownerView_(ownerView) {}
    ~JSCustomDialogController() = default;

    static void JSBind(BindingTarget object);
    static void ConstructorCallback(const JSCallbackInfo& args);
    static void DestructorCallback(JSCustomDialogController* instance);
    void JsOpenDialog(const JSCallbackInfo& info);
    void JsCloseDialog(const JSCallbackInfo& info);
    void JsGetState(const JSCallbackInfo& info);

private:
    static bool ParseAnimation(
        const JsiExecutionContext& execContext, const JsiRef<JsiValue>& jsiValue, AnimationOption& result);
    JSView* ownerView_ = nullptr;
    bool isShown_ = false;
    bool pending_ = false;
    bool hasBind_ = false;

    // NG
    std::vector<WeakPtr<AceType>> dialogs_;

    DialogProperties dialogProperties_;
    RefPtr<JsWeakFunction> jsBuilderFunction_;
    RefPtr<JsWeakFunction> jsCancelFunction_;
    RefPtr<AceType> customDialog_;
    RefPtr<AceType> dialogComponent_;
    std::list<DialogOperation> dialogOperation_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_DIALOG_JS_CUSTOM_DIALOG_CONTROLLER_H
