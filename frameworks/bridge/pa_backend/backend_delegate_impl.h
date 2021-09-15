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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_IMPL_H

#include <future>
#include <mutex>
#include <unordered_map>

#include "iremote_object.h"

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "core/common/js_message_dispatcher.h"
#include "core/pipeline/pipeline_context.h"
#include "core/common/backend.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
#include "frameworks/bridge/common/accessibility/js_accessibility_manager.h"
#else
#include "frameworks/bridge/common/inspector/js_inspector_manager.h"
#endif
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/pa_backend/backend_delegate.h"
#include "want.h"

namespace OHOS::Ace::Framework {
using LoadJsCallback = std::function<void(const std::string& url, const OHOS::AAFwk::Want& want)>;
using JsMessageDispatcherSetterCallback = std::function<void(const RefPtr<JsMessageDispatcher>&)>;
using EventCallback = std::function<void(const std::string &, const std::string &)>;
using DestroyApplicationCallback = std::function<void(const std::string &packageName)>;
using InsertCallback = std::function<int32_t(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value)>;
using QueryCallback = std::function<std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet>(
    const Uri& uri, const std::vector<std::string>& columns, const OHOS::NativeRdb::DataAbilityPredicates& predicates)>;
using UpdateCallback = std::function<int32_t(
    const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
    const OHOS::NativeRdb::DataAbilityPredicates& predicates)>;
using DeleteCallback = std::function<int32_t(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates)>;
using BatchInsertCallback =
    std::function<int32_t(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values)>;
using GetTypeCallback = std::function<std::string(const Uri& uri)>;
using GetFileTypesCallback =
    std::function<std::vector<std::string>(const Uri& uri, const std::string& mimeTypeFilter)>;
using OpenFileCallback = std::function<int32_t(const Uri& uri, const std::string& mode)>;
using OpenRawFileCallback = std::function<int32_t(const Uri& uri, const std::string& mode)>;
using NormalizeUriCallback = std::function<Uri(const Uri& uri)>;
using DenormalizeUriCallback = std::function<Uri(const Uri& uri)>;
using ConnectCallback = std::function<sptr<IRemoteObject>(const OHOS::AAFwk::Want &want)>;
using DisConnectCallback = std::function<void(const OHOS::AAFwk::Want &want)>;
using DeleteFormCallback = std::function<void(const int64_t formId)>;
using TriggerEventCallback = std::function<void(const int64_t formId, const std::string &message)>;
using UpdateFormCallback = std::function<void(const int64_t formId)>;
using CastTemptoNormalCallback = std::function<void(const int64_t formId)>;
using VisibilityChangedCallback = std::function<void(const std::map<int64_t, int32_t>& formEventsMap)>;
using AcquireStateCallback = std::function<void(const OHOS::AAFwk::Want &want)>;

struct BackendDelegateImplBuilder {
    RefPtr<TaskExecutor> taskExecutor;
    LoadJsCallback loadCallback;
    EventCallback asyncEventCallback;
    EventCallback syncEventCallback;
    JsMessageDispatcherSetterCallback transferCallback;
    DestroyApplicationCallback destroyApplicationCallback;
    InsertCallback insertCallback;
    QueryCallback queryCallback;
    UpdateCallback updateCallback;
    DeleteCallback deleteCallback;
    BatchInsertCallback batchInsertCallback;
    GetTypeCallback getTypeCallback;
    GetFileTypesCallback getFileTypesCallback;
    OpenFileCallback openFileCallback;
    OpenRawFileCallback openRawFileCallback;
    NormalizeUriCallback normalizeUriCallback;
    DenormalizeUriCallback denormalizeUriCallback;
    ConnectCallback connectCallback;
    DisConnectCallback disConnectCallback;
    DeleteFormCallback deleteFormCallback;
    TriggerEventCallback triggerEventCallback;
    UpdateFormCallback updateFormCallback;
    CastTemptoNormalCallback castTemptoNormalCallback;
    VisibilityChangedCallback visibilityChangedCallback;
    AcquireStateCallback acquireStateCallback;
    void* ability;
    BackendType type;
};

class BackendDelegateImpl : public BackendDelegate {
    DECLARE_ACE_TYPE(BackendDelegateImpl, BackendDelegate);

public:
    explicit BackendDelegateImpl(const BackendDelegateImplBuilder& builder);
    ~BackendDelegateImpl() override = default;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager);

    // JsBackend delegate functions.
    void RunPa(const std::string &url, const OHOS::AAFwk::Want &want);
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const;

    // BackendDelegate overrides.
    void PostJsTask(std::function<void()>&& task) override;

    RefPtr<PipelineContext> GetPipelineContext();

    SingleTaskExecutor GetAnimationJsTask() override;

    void AddTaskObserver(std::function<void()> &&task) override;
    void RemoveTaskObserver() override;

    void* GetAbility() override
    {
        return ability_;
    }

    BackendType GetType() override
    {
        return type_;
    }

    bool GetAssetContent(const std::string &url, std::string &content) override;
    bool GetAssetContent(const std::string &url, std::vector<uint8_t> &content) override;

    // JsEventHandler delegate functions.
    void FireAsyncEvent(const std::string &eventId, const std::string &param, const std::string &jsonArgs);
    bool FireSyncEvent(const std::string &eventId, const std::string &param, const std::string &jsonArgs);
    void FireSyncEvent(
        const std::string &eventId, const std::string &param, const std::string &jsonArgs, std::string &result);

    // special JsEventHandler
    void OnApplicationDestroy(const std::string &packageName);
    sptr<IRemoteObject> OnConnect(const OHOS::AAFwk::Want &want);
    void OnDisConnect(const OHOS::AAFwk::Want &want);

    int32_t Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value);
    std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> Query(
        const Uri& uri, const std::vector<std::string>& columns,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates);
    int32_t Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates);
    int32_t Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates);

    int32_t BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values);
    std::string GetType(const Uri& uri);
    std::vector<std::string> GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter);
    int32_t OpenFile(const Uri& uri, const std::string& mode);
    int32_t OpenRawFile(const Uri& uri, const std::string& mode);
    Uri NormalizeUri(const Uri& uri);
    Uri DenormalizeUri(const Uri& uri);

    void OnDelete(const int64_t formId);
    void OnTriggerEvent(const int64_t formId, const std::string &message);
    void OnUpdate(const int64_t formId);
    void OnCastTemptoNormal(const int64_t formId);
    void OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap);
    void OnAcquireState(const OHOS::AAFwk::Want &want);

private:
    void LoadPa(const std::string &url, const OHOS::AAFwk::Want &want);

    void ParseManifest();

    std::atomic<uint64_t> pageIdPool_ = 0;
    int32_t callbackCnt_ = 0;
    bool isRouteStackFull_ = false;
    bool isStagingPageExist_ = false;
    std::unordered_map<int32_t, std::string> jsCallBackResult_;

    LoadJsCallback loadJs_;
    JsMessageDispatcherSetterCallback dispatcherCallback_;

    EventCallback asyncEvent_;
    EventCallback syncEvent_;

    InsertCallback insert_;
    QueryCallback query_;
    UpdateCallback update_;
    DeleteCallback delete_;
    BatchInsertCallback batchInsert_;
    GetTypeCallback getType_;
    GetFileTypesCallback getFileTypes_;
    OpenFileCallback openFile_;
    OpenRawFileCallback openRawFile_;
    NormalizeUriCallback normalizeUri_;
    DenormalizeUriCallback denormalizeUri_;

    DestroyApplicationCallback destroyApplication_;

    ConnectCallback connectCallback_;
    DisConnectCallback disConnectCallback_;

    DeleteFormCallback deleteCallback_;
    TriggerEventCallback triggerEventCallback_;
    UpdateFormCallback updateCallback_;
    CastTemptoNormalCallback castTemptoNormalCallback_;
    VisibilityChangedCallback visibilityChangedCallback_;
    AcquireStateCallback acquireStateCallback_;

    RefPtr<Framework::ManifestParser> manifestParser_;
    void* ability_;
    BackendType type_ = BackendType::SERVICE;

    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;

    mutable std::mutex mutex_;
    mutable std::once_flag onceFlag_;

    std::mutex LoadPaMutex_;
    std::condition_variable condition_;
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_IMPL_H
