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

#ifndef INTERFACE_SDK_JS_DIALOG_PARAMS_H
#define INTERFACE_SDK_JS_DIALOG_PARAMS_H

#include <string>
#include <functional>
#include <memory>

#include "core/components/dialog/dialog_properties.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace {

struct DialogAsyncContext {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
    int32_t instanceId = -1;
};

napi_value CreateDialogPromise(napi_env env, std::shared_ptr<DialogAsyncContext>& context);

void RejectPromise(napi_env env, napi_deferred deferred, const std::string& message, int32_t errorCode);

std::function<void(int32_t, int32_t)> CreatePresentFinishCallback(
    std::shared_ptr<DialogAsyncContext> context);

std::function<void(int32_t, int32_t)> CreatePresentCustomFinishCallback(
    std::shared_ptr<DialogAsyncContext> context);

std::function<void(int32_t)> CreateUpdateFinishCallback(
    std::shared_ptr<DialogAsyncContext> context);

std::function<void(int32_t)> CreateDismissFinishCallback(
    std::shared_ptr<DialogAsyncContext> context);

void GetCustomBuilder(napi_env env, napi_value content, DialogProperties& dialogProps);

bool GetFrameNodePtr(napi_env env, napi_value content, WeakPtr<NG::UINode>& nodeWk);

bool GetDialogOptions(napi_env env, napi_value options, DialogProperties& dialogProps);

bool GetDialogBaseOptions(napi_env env, napi_value options, DialogProperties& dialogProps);

bool GetCustomDialogOptions(napi_env env, napi_value options, DialogProperties& dialogProps);

} // namespace OHOS::Ace

#endif // INTERFACE_SDK_JS_DIALOG_PARAMS_H
