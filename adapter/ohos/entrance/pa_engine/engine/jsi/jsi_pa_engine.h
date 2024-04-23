/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_JSI_JSI_PA_ENGINE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_JSI_JSI_PA_ENGINE_H

#include <vector>

#include "abs_shared_result_set.h"
#include "data_ability_predicates.h"
#include "event_handler.h"
#include "event_runner.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "native_engine/impl/ark/ark_native_engine.h"
#include "result_set.h"
#include "uri.h"
#include "values_bucket.h"
#include "want.h"

#include "adapter/ohos/entrance/pa_engine/engine/common/js_backend_engine.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/common/js_message_dispatcher.h"
#include "frameworks/bridge/js_frontend/engine/jsi/js_runtime.h"
#include "js_backend_asset_manager.h"
#include "js_runtime.h"

namespace OHOS::Ace {
using namespace OHOS::Ace::Framework;
using RdbValueBucketNewInstance = napi_value (*)(napi_env env, OHOS::NativeRdb::ValuesBucket& valueBucket);
using RdbValueBucketGetNativeObject = OHOS::NativeRdb::ValuesBucket* (*)(napi_env env, napi_value& value);
using RdbResultSetProxyNewInstance =
    napi_value (*)(napi_env env, std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> resultSet);
using RdbResultSetProxyGetNativeObject = std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> (*)(napi_env env,
    napi_value arg);
using DataAbilityPredicatesNewInstance = napi_value (*)(
    napi_env env, OHOS::NativeRdb::DataAbilityPredicates* predicates);
using DataAbilityPredicatesGetNativeObject = OHOS::NativeRdb::DataAbilityPredicates* (*)(const napi_env env,
    const napi_value& arg);

class JsiPaEngine : public JsBackendEngine {
public:
    using EventRunner = AppExecFwk::EventRunner;
    using EventHandler = AppExecFwk::EventHandler;

    explicit JsiPaEngine(int32_t instanceId) : instanceId_(instanceId) {}
    ~JsiPaEngine() override;

    bool Initialize(BackendType type, SrcLanguage language) override;

    bool InitializeInner(BackendType type, SrcLanguage language) override;

    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;

    // Load and initialize a JS bundle into the JS Framework
    void LoadJs(const std::string& url, const OHOS::AAFwk::Want& want) override;

    // destroy application instance according packageName
    void DestroyApplication(const std::string& packageName) override;

    // data
    int32_t Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value, const CallingInfo& callingInfo) override;
    std::shared_ptr<AppExecFwk::PacMap> Call(const std::string& method, const std::string& arg,
        const AppExecFwk::PacMap& pacMap, const CallingInfo& callingInfo) override;

    int32_t BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values,
        const CallingInfo& callingInfo) override;
    std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> Query(const Uri& uri, const std::vector<std::string>& columns,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates, const CallingInfo& callingInfo) override;
    int32_t Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates, const CallingInfo& callingInfo) override;
    int32_t Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates,
        const CallingInfo& callingInfo) override;

    std::string GetType(const Uri& uri, const CallingInfo& callingInfo) override;
    std::vector<std::string> GetFileTypes(
        const Uri& uri, const std::string& mimeTypeFilter, const CallingInfo& callingInfo) override;
    int32_t OpenFile(const Uri& uri, const std::string& mode, const CallingInfo& callingInfo) override;
    int32_t OpenRawFile(const Uri& uri, const std::string& mode, const CallingInfo& callingInfo) override;
    Uri NormalizeUri(const Uri& uri, const CallingInfo& callingInfo) override;
    Uri DenormalizeUri(const Uri& uri, const CallingInfo& callingInfo) override;

    // service
    sptr<IRemoteObject> OnConnectService(const OHOS::AAFwk::Want& want) override;
    void OnDisconnectService(const OHOS::AAFwk::Want& want) override;
    void OnCommand(const OHOS::AAFwk::Want& want, int startId) override;

    // form
    void OnCreate(const OHOS::AAFwk::Want& want) override;
    void OnDelete(const int64_t formId) override;
    void OnTriggerEvent(const int64_t formId, const std::string& message) override;
    void OnUpdate(const int64_t formId) override;
    void OnCastTemptoNormal(const int64_t formId) override;
    void OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap) override;
    int32_t OnAcquireFormState(const OHOS::AAFwk::Want& want) override;
    bool OnShare(int64_t formId, OHOS::AAFwk::WantParams& wantParams) override;

    void PostTask(const std::function<void()>& task, const std::string& name, int64_t delayTime = 0) override;
    void PostSyncTask(const std::function<void()>& task, const std::string& name) override;
    void RemoveTask(const std::string& name) override;

    std::shared_ptr<JsRuntime> GetJsRuntime() const;
    NativeEngine* GetNativeEngine() const;

    bool GetBlockWaiting() const
    {
        return blockWaiting_;
    }

    void SetBlockWaiting(bool blockWaiting)
    {
        blockWaiting_ = blockWaiting;
    }

    shared_ptr<JsValue> GetAsyncResult() const
    {
        return asyncResult_;
    }

    void SetAsyncResult(shared_ptr<JsValue> asyncResult)
    {
        asyncResult_ = asyncResult;
    }

    void SetDebugMode(bool isDebugMode)
    {
        isDebugMode_ = isDebugMode;
    }

    bool GetDebugMode()
    {
        return isDebugMode_;
    }

private:
    void LoadLibrary();
    void UnloadLibrary();
    shared_ptr<JsValue> GetPaFunc(const std::string& funcName);
    shared_ptr<JsValue> CallFunc(const shared_ptr<JsValue>& func);
    shared_ptr<JsValue> CallFunc(const shared_ptr<JsValue>& func, const std::vector<shared_ptr<JsValue>>& argv);
    shared_ptr<JsValue> CallFunc(
        const shared_ptr<JsValue>& func, const std::vector<shared_ptr<JsValue>>& argv, const CallingInfo& callingInfo);
    shared_ptr<JsValue> CallFuncWithDefaultThis(
        const shared_ptr<JsValue>& func, const std::vector<shared_ptr<JsValue>>& argv);

    shared_ptr<JsValue> CallAsyncFunc(
        const shared_ptr<JsValue>& func, std::vector<shared_ptr<JsValue>>& argv, const CallingInfo& callingInfo);
    shared_ptr<JsValue> NapiValueToJsValue(napi_value nativeValue);
    shared_ptr<JsValue> WantToJsValue(const OHOS::AAFwk::Want& want);
    void StartService();
    void StartData();
    void StartForm(const OHOS::AAFwk::Want& want);

    bool InitJsEnv(bool debuggerMode, const std::unordered_map<std::string, void*>& extraNativeObject);
    void RegisterPaModule();
    void RegisterConsoleModule(ArkNativeEngine* engine);
    void RegisterUncaughtExceptionHandler();
    void EvaluateJsCode();
    void StartDebugMode(bool debuggerMode);
    panda::ecmascript::EcmaVM* GetEcmaVm() const;
    void InitJsRuntimeOptions(AbilityRuntime::Runtime::Options& options);
    bool CreateJsRuntime();

    std::string ExcludeTag(const std::string& jsonString, const std::string& tagString);
    std::string IncludeTag(const std::string& jsonString, const std::string& tagString);
    std::shared_ptr<AppExecFwk::PacMap> BuildPacMap(const napi_env& env, const napi_value& arg);
    void SetPacMapObject(
        std::shared_ptr<AppExecFwk::PacMap> pacMap, const napi_env& env, std::string keyStr, napi_value value);
    std::string UnwrapStringFromJS(napi_env env, napi_value param, const std::string& defaultValue = "");
    std::vector<std::string> ConvertStringVector(napi_env env, napi_value jsValue);

    int32_t instanceId_ = 0;
    std::unique_ptr<AbilityRuntime::JsRuntime> jsAbilityRuntime_ = nullptr;
    std::shared_ptr<EventRunner> eventRunner_ = nullptr;
    std::shared_ptr<EventHandler> eventHandler_ = nullptr;
    std::shared_ptr<JsRuntime> runtime_ = nullptr;
    RefPtr<JsBackendAssetManager> jsBackendAssetManager_ = nullptr;
    BackendType type_ = BackendType::SERVICE;
    SrcLanguage language_ = SrcLanguage::ETS;
    bool blockWaiting_ = false;
    shared_ptr<JsValue> asyncResult_ = nullptr;
    bool isDebugMode_ = true;

    void* libRdb_ = nullptr;
    void* libDataAbility_ = nullptr;
    RdbValueBucketNewInstance rdbValueBucketNewInstance_ = nullptr;
    RdbValueBucketGetNativeObject rdbValueBucketGetNativeObject_ = nullptr;
    RdbResultSetProxyNewInstance rdbResultSetProxyNewInstance_ = nullptr;
    RdbResultSetProxyGetNativeObject rdbResultSetProxyGetNativeObject_ = nullptr;
    DataAbilityPredicatesNewInstance dataAbilityPredicatesNewInstance_ = nullptr;
    DataAbilityPredicatesGetNativeObject dataAbilityPredicatesGetNativeObject_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(JsiPaEngine);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_JSI_JSI_PA_ENGINE_H
