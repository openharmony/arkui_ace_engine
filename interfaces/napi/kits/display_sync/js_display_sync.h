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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_JS_DISPLAY_SYNC_H_
#define FOUNDATION_ACE_INTERFACE_INNERKITS_JS_DISPLAY_SYNC_H_

#include <cstddef>
#include <cstdint>
#include <memory>
#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/memory/referenced.h"
#include "core/components_ng/manager/display_sync/ui_display_sync.h"

namespace OHOS::Ace::Napi {
enum class CallbackType {
    ONFRAME = 0,
    UNKNOW,
};

class DisplaySync final {
public:
    DisplaySync() = delete;
    explicit DisplaySync(RefPtr<UIDisplaySync>& uiDisplaySync)
        : uiDisplaySync_(uiDisplaySync) {}

    ~DisplaySync()
    {
        if (uiDisplaySync_) {
            uiDisplaySync_->DelFromPipelineOnContainer();
        }
    }

    void Initialize(napi_env env, napi_value thisVar);
    void NapiSerializer(napi_env& env, napi_value& result);
    void RegisterOnFrameCallback(napi_value cb, napi_ref& onFrameRef, CallbackType callbackType, napi_env env);
    void UnregisterOnFrameCallback(napi_env env, size_t argc, napi_ref& onFrameRef);
    void Destroy(napi_env env);

    RefPtr<UIDisplaySync> GetUIDisplaySync() const
    {
        return uiDisplaySync_;
    }

    napi_ref GetOnframeRef() const
    {
        return onFrameRef_;
    }

    void SetOnframeRef(const napi_ref& onframe)
    {
        onFrameRef_ = onframe;
    }

    napi_ref thisVarRef_ = nullptr;
    napi_ref onFrameRef_ = nullptr;

private:
    RefPtr<UIDisplaySync> uiDisplaySync_;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_JS_DISPLAY_SYNC_H_
