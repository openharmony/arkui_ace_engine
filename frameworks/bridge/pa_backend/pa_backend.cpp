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

#include "frameworks/bridge/pa_backend/pa_backend.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"

namespace OHOS::Ace {
RefPtr<Backend> Backend::Create()
{
    return AceType::MakeRefPtr<PaBackend>();
}

PaBackend::~PaBackend() noexcept
{
    // To guarantee the jsBackendEngine_ and delegate_ released in js thread
    auto jsTaskExecutor = delegate_->GetAnimationJsTask();
    RefPtr<Framework::JsBackendEngine> jsBackendEngine;
    jsBackendEngine.Swap(jsBackendEngine_);
    RefPtr<Framework::BackendDelegateImpl> delegate;
    delegate.Swap(delegate_);
    jsTaskExecutor.PostTask([jsBackendEngine, delegate] {});
}

bool PaBackend::Initialize(BackendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    LOGI("PaBackend initialize begin.");
    type_ = type;
    ACE_DCHECK(type_ == BackendType::SERVICE);
    InitializeBackendDelegate(taskExecutor);

    taskExecutor->PostTask(
        [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_), delegate = delegate_] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return;
            }
            jsBackendEngine->Initialize(delegate);
        },
        TaskExecutor::TaskType::JS);

    LOGI("PaBackend initialize end.");
    return true;
}

void PaBackend::InitializeBackendDelegate(const RefPtr<TaskExecutor> &taskExecutor)
{
    // builder callback
    Framework::BackendDelegateImplBuilder builder;
    builder.loadCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
                                const std::string &url) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->LoadJs(url);
    };

    builder.transferCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
                                   const RefPtr<JsMessageDispatcher> &dispatcher) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->SetJsMessageDispatcher(dispatcher);
    };

    builder.asyncEventCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
                                         const std::string& eventId, const std::string& param) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->FireAsyncEvent(eventId, param);
    };

    builder.syncEventCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
                                        const std::string& eventId, const std::string& param) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->FireSyncEvent(eventId, param);
    };

    builder.destroyApplicationCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
                                             const std::string &packageName) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->DestroyApplication(packageName);
    };

    builder.taskExecutor = taskExecutor;
    builder.ability = ability_;
    builder.type = type_;

    delegate_ = AceType::MakeRefPtr<Framework::BackendDelegateImpl>(builder);
}

void PaBackend::UpdateState(Backend::State state)
{
    LOGI("UpdateState");
    switch (state) {
        case Backend::State::ON_CREATE:
            break;
        case Backend::State::ON_DESTROY:
            delegate_->OnApplicationDestroy("pa");
            break;
        default:
            LOGE("error State: %d", state);
    }
}

void PaBackend::RunPa(const std::string &url, const std::string &params)
{
    delegate_->RunPa(url, params);
}

void PaBackend::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const
{
    delegate_->SetJsMessageDispatcher(dispatcher);
}

void PaBackend::SetAssetManager(const RefPtr<AssetManager> &assetManager)
{
    delegate_->SetAssetManager(assetManager);
}
} // namespace OHOS::Ace
