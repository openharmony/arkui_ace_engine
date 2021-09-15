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
#include "form_provider_info.h"
#include "want.h"

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

    void RunPa(const std::string &url, const OHOS::AAFwk::Want &want);
    void OnDelete(const int64_t formId);
    void OnTriggerEvent(const int64_t formId, const std::string &message);
    void OnUpdate(const int64_t formId);
    void OnCastTemptoNormal(const int64_t formId);
    void OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap);
    void OnAcquireState(const OHOS::AAFwk::Want &want);

    void SetJsEngine(const RefPtr<Framework::JsBackendEngine> &jsBackEngine)
    {
        jsBackendEngine_ = jsBackEngine;
    }

    void SetAbility(void *ability)
    {
        ability_ = ability;
    }

    void SetAssetManager(const RefPtr<AssetManager> &assetManager);
    sptr<IRemoteObject> OnConnect(const OHOS::AAFwk::Want &want);
    void OnDisConnect(const OHOS::AAFwk::Want &want);

    int32_t Insert(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value) override;
    std::shared_ptr<OHOS::NativeRdb::AbsSharedResultSet> Query(
        const Uri& uri, const std::vector<std::string>& columns,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates) override;
    int32_t Update(const Uri& uri, const OHOS::NativeRdb::ValuesBucket& value,
        const OHOS::NativeRdb::DataAbilityPredicates& predicates) override;
    int32_t Delete(const Uri& uri, const OHOS::NativeRdb::DataAbilityPredicates& predicates) override;

    int32_t BatchInsert(const Uri& uri, const std::vector<OHOS::NativeRdb::ValuesBucket>& values) override;
    std::string GetType(const Uri& uri) override;
    std::vector<std::string> GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter) override;
    int32_t OpenFile(const Uri& uri, const std::string& mode) override;
    int32_t OpenRawFile(const Uri& uri, const std::string& mode) override;
    Uri NormalizeUri(const Uri& uri) override;
    Uri DenormalizeUri(const Uri& uri) override;
    AppExecFwk::FormProviderData GetFormData() const
    {
        if (jsBackendEngine_) {
            return jsBackendEngine_->GetFormData();
        } else {
            LOGE("PA: PaBackend::jsBackendEngine_ is null");
            return AppExecFwk::FormProviderData("");
        }
    }

private:
    void InitializeBackendDelegate(const RefPtr<TaskExecutor>& taskExecutor);
    BackendType type_ = BackendType::SERVICE;

    RefPtr<Framework::BackendDelegateImpl> delegate_;
    RefPtr<Framework::JsBackendEngine> jsBackendEngine_;
    void *ability_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_PA_BACKEND_H
