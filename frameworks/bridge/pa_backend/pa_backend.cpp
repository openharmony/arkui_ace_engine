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

#include "iremote_object.h"

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
                                const std::string &url, const OHOS::AAFwk::Want& want) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->LoadJs(url, want);
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

    builder.insertCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value) -> int32_t {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return 0;
            }
            return jsBackendEngine->Insert(uri, value);
        };

    builder.queryCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const std::vector<std::string>& columns,
         const OHOS::NativeRdb::DataAbilityPredicates& predicates)-> std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return nullptr;
            }
            return jsBackendEngine->Query(uri, columns, predicates);
        };

    builder.updateCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
         const OHOS::NativeRdb::DataAbilityPredicates& predicates) -> int32_t {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return 0;
            }
            return jsBackendEngine->Update(uri, value, predicates);
        };

    builder.deleteCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates) -> int32_t {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return 0;
            }
            return jsBackendEngine->Delete(uri, predicates);
        };

    builder.batchInsertCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values) -> int32_t {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return 0;
            }
            return jsBackendEngine->BatchInsert(uri, values);
        };

    builder.getTypeCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri) -> std::string {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return std::string();
            }
            return jsBackendEngine->GetType(uri);
        };

    builder.getFileTypesCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const std::string& mimeTypeFilter) -> std::vector<std::string> {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return std::vector<std::string>();
            }
            return jsBackendEngine->GetFileTypes(uri, mimeTypeFilter);
        };

    builder.openFileCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const std::string& mode) -> int32_t {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return 0;
            }
            return jsBackendEngine->OpenFile(uri, mode);
        };

    builder.openRawFileCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri, const std::string& mode) -> int32_t {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return 0;
            }
            return jsBackendEngine->OpenRawFile(uri, mode);
        };

    builder.normalizeUriCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri) -> Uri {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return Uri("");
            }
            return jsBackendEngine->NormalizeUri(uri);
        };

    builder.denormalizeUriCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)]
        (const Uri& uri) -> Uri {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (!jsBackendEngine) {
                return Uri("");
            }
            return jsBackendEngine->DenormalizeUri(uri);
        };

    builder.destroyApplicationCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
                                             const std::string &packageName) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->DestroyApplication(packageName);
    };

    builder.connectCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const OHOS::AAFwk::Want &want) -> sptr<IRemoteObject> {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return nullptr;
        }
        return jsBackendEngine->OnConnectService(want);
    };

    builder.disConnectCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const OHOS::AAFwk::Want &want) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnDisconnectService(want);
    };

    builder.deleteFormCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const int64_t formId) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnDelete(formId);
    };

    builder.triggerEventCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const int64_t formId, const std::string &message) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnTriggerEvent(formId, message);
    };

    builder.updateFormCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const int64_t formId) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnUpdate(formId);
    };

    builder.castTemptoNormalCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const int64_t formId) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnCastTemptoNormal(formId);
    };

    builder.visibilityChangedCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const std::map<int64_t, int32_t>& formEventsMap) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnVisibilityChanged(formEventsMap);
    };

    builder.acquireStateCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const OHOS::AAFwk::Want &want) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnAcquireState(want);
    };

    builder.commandCallback = [weakEngine = WeakPtr<Framework::JsBackendEngine>(jsBackendEngine_)](
            const OHOS::AAFwk::Want &want, int startId) {
        auto jsBackendEngine = weakEngine.Upgrade();
        if (!jsBackendEngine) {
            return;
        }
        jsBackendEngine->OnCommand(want, startId);
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

int32_t PaBackend::Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value)
{
    return delegate_->Insert(uri, value);
}

std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> PaBackend::Query(
    const Uri& uri, const std::vector<std::string>& columns,
    const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    return delegate_->Query(uri, columns, predicates);
}

int32_t PaBackend::Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
    const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    return delegate_->Update(uri, value, predicates);
}

int32_t PaBackend::Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    return delegate_->Delete(uri, predicates);
}

int32_t PaBackend::BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values)
{
    return delegate_->BatchInsert(uri, values);
}

std::string PaBackend::GetType(const Uri& uri)
{
    return delegate_->GetType(uri);
}

std::vector<std::string> PaBackend::GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter)
{
    return delegate_->GetFileTypes(uri, mimeTypeFilter);
}

int32_t PaBackend::OpenFile(const Uri& uri, const std::string& mode)
{
    return delegate_->OpenFile(uri, mode);
}

int32_t PaBackend::OpenRawFile(const Uri& uri, const std::string& mode)
{
    return delegate_->OpenRawFile(uri, mode);
}

Uri PaBackend::NormalizeUri(const Uri& uri)
{
    return delegate_->NormalizeUri(uri);
}

Uri PaBackend::DenormalizeUri(const Uri& uri)
{
    return delegate_->DenormalizeUri(uri);
}

void PaBackend::RunPa(const std::string &url, const OHOS::AAFwk::Want &want)
{
    delegate_->RunPa(url, want);
}

void PaBackend::OnDelete(const int64_t formId)
{
    delegate_->OnDelete(formId);
}

void PaBackend::OnTriggerEvent(const int64_t formId, const std::string &message)
{
    delegate_->OnTriggerEvent(formId, message);
}

void PaBackend::OnUpdate(const int64_t formId)
{
    delegate_->OnUpdate(formId);
}

void PaBackend::OnCastTemptoNormal(const int64_t formId)
{
    delegate_->OnCastTemptoNormal(formId);
}

void PaBackend::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    delegate_->OnVisibilityChanged(formEventsMap);
}

void PaBackend::OnAcquireState(const OHOS::AAFwk::Want &want)
{
    delegate_->OnAcquireState(want);
}

void PaBackend::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const
{
    delegate_->SetJsMessageDispatcher(dispatcher);
}

void PaBackend::SetAssetManager(const RefPtr<AssetManager> &assetManager)
{
    delegate_->SetAssetManager(assetManager);
}

sptr<IRemoteObject> PaBackend::OnConnect(const OHOS::AAFwk::Want &want)
{
    return delegate_->OnConnect(want);
}

void PaBackend::OnDisConnect(const OHOS::AAFwk::Want &want)
{
    delegate_->OnDisConnect(want);
}

void PaBackend::OnCommand(const OHOS::AAFwk::Want &want, int startId)
{
    delegate_->OnCommand(want, startId);
}

} // namespace OHOS::Ace
