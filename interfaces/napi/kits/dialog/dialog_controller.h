/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef INTERFACE_SDK_JS_DIALOG_CONTROLLER_H
#define INTERFACE_SDK_JS_DIALOG_CONTROLLER_H

#include "core/components_ng/base/frame_node.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace {
class DialogControllerImpl {
public:
    DialogControllerImpl() = default;
    ~DialogControllerImpl() = default;

    void SetDialogNode(const WeakPtr<NG::FrameNode>& dialogNode);
    void Close();
    PromptActionCommonState GetState();
    static napi_value Define(napi_env env, napi_value exports);

private:
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static napi_value Close(napi_env env, napi_callback_info info);
    static napi_value GetState(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void* data, void* hint);

    WeakPtr<NG::FrameNode> dialogNode_;
    bool hasBind_ = false;
};
} // namespace OHOS::Ace

#endif // INTERFACE_SDK_JS_DIALOG_CONTROLLER_H
