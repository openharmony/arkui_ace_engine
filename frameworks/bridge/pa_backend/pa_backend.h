/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_PA_BACKEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_PA_BACKEND_H

#include <string>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "core/common/backend.h"

#include "frameworks/bridge/pa_backend/engine/common/js_backend_engine.h"
#include "frameworks/bridge/pa_backend/backend_delegate_impl.h"

namespace OHOS::Ace {
class PaBackend : public Backend {
    DECLARE_ACE_TYPE(PaBackend, Backend);

public:
    PaBackend() = default;
    ~PaBackend() override;

    bool Initialize(BackendType type, const RefPtr<TaskExecutor>& taskExecutor) override;

    void UpdateState(Backend::State state) override;

    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher> &dispatcher) const override;

    BackendType GetType() override
    {
        return type_;
    }

    void RunPa(const std::string &url, const std::string &params);

    void SetJsEngine(const RefPtr<Framework::JsBackendEngine> &jsBackEngine)
    {
        jsBackendEngine_ = jsBackEngine;
    }

    void SetAbility(void *ability)
    {
        ability_ = ability;
    }

    void SetAssetManager(const RefPtr<AssetManager> &assetManager);

private:
    void InitializeBackendDelegate(const RefPtr<TaskExecutor>& taskExecutor);
    BackendType type_ = BackendType::SERVICE;

    RefPtr<Framework::BackendDelegateImpl> delegate_;
    RefPtr<Framework::JsBackendEngine> jsBackendEngine_;
    void *ability_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_PA_BACKEND_H
