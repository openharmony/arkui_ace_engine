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

#include "adapter/ohos/entrance/pa_engine/pa_backend.h"

#include "ability.h"
#include "adapter/ohos/entrance/pa_engine/engine/common/js_backend_engine_loader.h"
#include "base/log/event_report.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {
namespace {
const char PA_MANIFEST_JSON[] = "manifest.json";
} // namespace

RefPtr<Backend> Backend::Create()
{
    return AceType::MakeRefPtr<PaBackend>();
}

PaBackend::~PaBackend() noexcept
{
    LOGI("PaBackend destructor.");
}

bool PaBackend::Initialize(BackendType type, SrcLanguage language)
{
    LOGI("PaBackend initialize begin.");
    type_ = type;
    language_ = language;

    CHECK_NULL_RETURN(jsBackendEngine_, false);
    jsBackendEngine_->Initialize(type, language);
    return true;
}

void PaBackend::LoadEngine(const char* libName, int32_t instanceId)
{
    auto& loader = JsBackendEngineLoader::Get(libName);
    SetJsEngine(loader.CreateJsBackendEngine(instanceId));
}

void PaBackend::UpdateState(Backend::State state)
{
    LOGI("UpdateState");
    switch (state) {
        case Backend::State::ON_CREATE:
            break;
        case Backend::State::ON_DESTROY:
            if (jsBackendEngine_) {
                jsBackendEngine_->PostSyncTask(
                    [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_)] {
                        auto jsBackendEngine = weakEngine.Upgrade();
                        CHECK_NULL_VOID(jsBackendEngine);
                        jsBackendEngine->DestroyApplication("pa");
                    }, "ArkUIPaBackendDestroyApplication");
            }
            break;
        default:
            LOGE("error State: %d", state);
    }
}

void PaBackend::OnCommand(const OHOS::AAFwk::Want& want, int startId)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), want, startId] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnCommand(want, startId);
        }, "ArkUIPaBackendOnCommand");
}

void PaBackend::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    assetManager_ = assetManager;
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->SetAssetManager(assetManager);
}

int32_t PaBackend::Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value)
{
    int32_t ret = 0;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, value, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->Insert(uri, value, callingInfo);
            }
        }, "ArkUIPaBackendInsert");
    return ret;
}

std::shared_ptr<AppExecFwk::PacMap> PaBackend::Call(
    const Uri& uri, const std::string& method, const std::string& arg, const AppExecFwk::PacMap& pacMap)
{
    std::shared_ptr<AppExecFwk::PacMap> ret = nullptr;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, method, arg, pacMap, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->Call(method, arg, pacMap, callingInfo);
            }
        }, "ArkUIPaBackendCall");
    return ret;
}

std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> PaBackend::Query(
    const Uri& uri, const std::vector<std::string>& columns, const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> ret = nullptr;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, columns, predicates, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->Query(uri, columns, predicates, callingInfo);
            }
        }, "ArkUIPaBackendQuery");
    return ret;
}

int32_t PaBackend::Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
    const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    int32_t ret = 0;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, value, predicates, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->Update(uri, value, predicates, callingInfo);
            }
        }, "ArkUIPaBackendUpdate");
    return ret;
}

int32_t PaBackend::Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates)
{
    int32_t ret = 0;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, predicates, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->Delete(uri, predicates, callingInfo);
            }
        }, "ArkUIPaBackendDelete");
    return ret;
}

int32_t PaBackend::BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values)
{
    int32_t ret = 0;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, values, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->BatchInsert(uri, values, callingInfo);
            }
        }, "ArkUIPaBackendBatchInsert");
    return ret;
}

std::string PaBackend::GetType(const Uri& uri)
{
    std::string ret;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->GetType(uri, callingInfo);
            }
        }, "ArkUIPaBackendGetType");
    return ret;
}

std::vector<std::string> PaBackend::GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter)
{
    std::vector<std::string> ret;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, mimeTypeFilter, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->GetFileTypes(uri, mimeTypeFilter, callingInfo);
            }
        }, "ArkUIPaBackendGetFileTypes");
    return ret;
}

int32_t PaBackend::OpenFile(const Uri& uri, const std::string& mode)
{
    int32_t ret = 0;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, mode, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->OpenFile(uri, mode, callingInfo);
            }
        }, "ArkUIPaBackendOpenFile");
    return ret;
}

int32_t PaBackend::OpenRawFile(const Uri& uri, const std::string& mode)
{
    int32_t ret = 0;
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, mode, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->OpenRawFile(uri, mode, callingInfo);
            }
        }, "ArkUIPaBackendOpenRawFile");
    return ret;
}

Uri PaBackend::NormalizeUri(const Uri& uri)
{
    Uri ret("");
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->NormalizeUri(uri, callingInfo);
            }
        }, "ArkUIPaBackendNormalizeUri");
    return ret;
}

Uri PaBackend::DenormalizeUri(const Uri& uri)
{
    Uri ret("");
    CallingInfo callingInfo;
    NAPI_RemoteObject_getCallingInfo(callingInfo);
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, uri, callingInfo] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->DenormalizeUri(uri, callingInfo);
            }
        }, "ArkUIPaBackendDenormalizeUri");
    return ret;
}

void PaBackend::ParseManifest()
{
    std::call_once(onceFlag_, [this]() {
        std::string jsonContent;
        if (!Framework::GetAssetContentImpl(assetManager_, PA_MANIFEST_JSON, jsonContent)) {
            LOGE("RunPa parse manifest.json failed.");
            EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
            return;
        }

        if (manifestParser_ != nullptr) {
            manifestParser_->Parse(jsonContent);
        }
    });
}

void PaBackend::LoadPa(const std::string& url, const OHOS::AAFwk::Want& want)
{
    CHECK_NULL_VOID(jsBackendEngine_);

    std::unique_lock<std::mutex> lock(LoadPaMutex_);
    if (isStagingPageExist_) {
        if (condition_.wait_for(lock, std::chrono::seconds(1)) == std::cv_status::timeout) {
            LOGE("Load page failed, waiting for current page loading finish.");
            return;
        }
    }

    isStagingPageExist_ = true;

    if (type_ == BackendType::FORM) {
        jsBackendEngine_->PostSyncTask(
            [weak = WeakPtr<JsBackendEngine>(jsBackendEngine_), url, want] {
                auto jsBackendEngine = weak.Upgrade();
                CHECK_NULL_VOID(jsBackendEngine);
                jsBackendEngine->LoadJs(url, want);
            }, "ArkUIPaBackendFormLoadPa");
    } else {
        jsBackendEngine_->PostTask(
            [weak = WeakPtr<JsBackendEngine>(jsBackendEngine_), url, want] {
                auto jsBackendEngine = weak.Upgrade();
                CHECK_NULL_VOID(jsBackendEngine);
                jsBackendEngine->LoadJs(url, want);
            }, "ArkUIPaBackendLoadPa");
    }
}

void PaBackend::RunPa(const std::string& url, const OHOS::AAFwk::Want& want)
{
    ACE_SCOPED_TRACE("PaBackend::RunPa");
    ParseManifest();
    // if mutli pa in one hap should parse manifest get right url
    LoadPa(url, want);
}

void PaBackend::OnCreate(const OHOS::AAFwk::Want& want)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), want] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnCreate(want);
        }, "ArkUIPaBackendOnCreate");
}

void PaBackend::OnDelete(const int64_t formId)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), formId] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnDelete(formId);
        }, "ArkUIPaBackendOnDelete");
}

void PaBackend::OnTriggerEvent(const int64_t formId, const std::string& message)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), formId, message] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnTriggerEvent(formId, message);
        }, "ArkUIPaBackendOnTriggerEvent");
}

void PaBackend::OnUpdate(const int64_t formId)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), formId] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnUpdate(formId);
        }, "ArkUIPaBackendOnUpdate");
}

void PaBackend::OnCastTemptoNormal(const int64_t formId)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), formId] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnCastTemptoNormal(formId);
        }, "ArkUIPaBackendOnCastTempToNormal");
}

void PaBackend::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), formEventsMap] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnVisibilityChanged(formEventsMap);
        }, "ArkUIPaBackendOnVisibilityChanged");
}

int32_t PaBackend::OnAcquireFormState(const OHOS::AAFwk::Want& want)
{
    auto ret = (int32_t)AppExecFwk::FormState::UNKNOWN;
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, want] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->OnAcquireFormState(want);
            }
        }, "ArkUIPaBackendOnAcquireFormState");
    return ret;
}

sptr<IRemoteObject> PaBackend::OnConnect(const OHOS::AAFwk::Want& want)
{
    sptr<IRemoteObject> ret = nullptr;
    CHECK_NULL_RETURN(jsBackendEngine_, ret);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &ret, want] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                ret = jsBackendEngine->OnConnectService(want);
            }
        }, "ArkUIPaBackendConnectService");
    return ret;
}

void PaBackend::OnDisConnect(const OHOS::AAFwk::Want& want)
{
    CHECK_NULL_VOID(jsBackendEngine_);
    jsBackendEngine_->PostTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), want] {
            auto jsBackendEngine = weakEngine.Upgrade();
            CHECK_NULL_VOID(jsBackendEngine);
            jsBackendEngine->OnDisconnectService(want);
        }, "ArkUIPaBackendDisconnectService");
}

bool PaBackend::OnShare(int64_t formId, OHOS::AAFwk::WantParams& wantParams)
{
    bool result = false;
    CHECK_NULL_RETURN(jsBackendEngine_, result);
    jsBackendEngine_->PostSyncTask(
        [weakEngine = WeakPtr<JsBackendEngine>(jsBackendEngine_), &result, formId, &wantParams] {
            auto jsBackendEngine = weakEngine.Upgrade();
            if (jsBackendEngine != nullptr) {
                result = jsBackendEngine->OnShare(formId, wantParams);
            }
        }, "ArkUIPaBackendOnShare");
    return result;
}
} // namespace OHOS::Ace
