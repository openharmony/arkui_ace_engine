/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEDN_COMMON_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEDN_COMMON_H

#include <memory>

#include "cj_page_router_abstract.h"

#include "base/memory/ace_type.h"
#include "base/utils/measure_util.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/common/manifest/manifest_parser.h"
#include "bridge/common/utils/pipeline_context_holder.h"
#include "core/common/frontend.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

#if defined(PREVIEW)
#include "adapter/preview/osal/response_data.h"
#endif

namespace OHOS::Ace {

class ACE_EXPORT CJFrontendAbstract : public Frontend {
    DECLARE_ACE_TYPE(CJFrontendAbstract, Frontend)
public:
    // page lifecycle
    bool OnBackPressed() override;
    void OnShow() override;
    void OnHide() override;

protected:
    virtual void InternalInitialize() = 0;

public:
    ~CJFrontendAbstract() override;
    bool Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor) override;
    void Destroy() override;
    void FlushReload() override;
    bool CheckLoadAppLibrary();

    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;
    void SetAssetManager(const RefPtr<AssetManager>& assetManager) override;
    UIContentErrorCode RunPage(const std::string& url, const std::string& params) override;
    void ReplacePage(const std::string& url, const std::string& params) override;
    void PushPage(const std::string& url, const std::string& params) override;
    void Back(const std::string& uri, const std::string& params);
    void Replace(const std::string& url, const std::string& params, CJPageRouterAbstract::RouterMode modeValue);
    void CallRouterBack() override;

    std::string GetParams() const
    {
        return pageRouterManager_->GetParams();
    }

    RefPtr<AccessibilityManager> GetAccessibilityManager() const override
    {
        return accessibilityManager_;
    }
    WindowConfig& GetWindowConfig() override
    {
        return manifestParser_->GetWindowConfig();
    }
    bool IsForeground() override
    {
        return foregroundFrontend_;
    }
    RefPtr<CJPageRouterAbstract> GetPageRouterManager() const
    {
        return pageRouterManager_;
    }
    void SetStageModel(bool isStageModel)
    {
        isStageModel_ = isStageModel;
    }
    bool IsStageModel() const
    {
        return isStageModel_;
    }
    void SetRuntimeContext(std::weak_ptr<void> context)
    {
        runtimeContext_ = context;
    }
    std::weak_ptr<void> GetRuntimeContext() const
    {
        return runtimeContext_;
    }
    void SetAceAbility(std::weak_ptr<void> aceAbility)
    {
        aceAbility_ = aceAbility;
    }
    std::weak_ptr<void> GetAceAbility() const
    {
        return aceAbility_;
    }
    const RefPtr<PipelineBase>& GetPipelineContext()
    {
        return pipelineContextHolder_.Get();
    }

    // ----------------
    // Measure
    // ----------------
    double MeasureText(const MeasureContext& context);
    Size MeasureTextSize(const MeasureContext& context);

    // ----------------
    // promptAction
    // ----------------
    void ShowToast(const std::string& message, int32_t duration, const std::string& bottom,
        const NG::ToastShowMode& showMode = NG::ToastShowMode::DEFAULT);

    void OpenCustomDialog(const PromptDialogAttr& dialogAttr, std::function<void(int32_t)>&& callback);

    void CloseCustomDialog(int32_t id);

    // todo: support new params
    void ShowDialog(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks);
    void ShowDialogInner(DialogProperties& dialogProperties, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);

    void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);
    void ShowActionMenuInner(DialogProperties& dialogProperties, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);

    // ----------------
    // Font
    // ----------------
    void RegisterFont(const std::string& familyName, const std::string& familySrc, const std::string& bundleName = "",
        const std::string& moduleName = "");

    VectorStringHandle GetSystemFontList();
    NativeOptionFontInfo GetSystemFont(const std::string& fontName);
    void BackIndex(int32_t index, const std::string& params);
    void Clear();
    int32_t GetLength();
    void SetShowAlertBeforeBackPage(const char* msg, std::function<void(int32_t)>&& callback);
    void SetHideAlertBeforeBackPage();
    void GetState(CJPageRouterAbstract::RouterState* info);
    void GetStateByIndex(CJPageRouterAbstract::RouterState* info);
    CJPageRouterAbstract::RouterStateList GetStateByUrl(const char* url);
    void PushPageWithCallback(const std::string& url, const std::string& params, CJPageRouterAbstract::RouterMode& mode,
        std::function<void(int32_t)>&& callback);
    void ReplacePageWithCallback(const std::string& url, const std::string& params,
        CJPageRouterAbstract::RouterMode& mode, std::function<void(int32_t)>&& callback);

#if defined(PREVIEW)
    void TransferJsResponseDataPreview(int32_t callbackId, int32_t code, ResponseData responseData) const;
#endif

protected:
    friend class CJPageRouterAbstract;

    void InternalRunPage(const std::string& url, const std::string& params);

    // internal properties
    RefPtr<AccessibilityManager> accessibilityManager_;
    Framework::PipelineContextHolder pipelineContextHolder_;
    RefPtr<CJPageRouterAbstract> pageRouterManager_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<Framework::ManifestParser> manifestParser_;
    std::weak_ptr<void> runtimeContext_;
    std::weak_ptr<void> aceAbility_;

    bool foregroundFrontend_ = false;
    bool isStageModel_ = false;
    std::string pageProfile_;

public:
    // implement later
    void DumpFrontend() const override {}
    std::string GetPagePath() const override
    {
        return "";
    }
    void TriggerGarbageCollection() override {}
    void DumpHeapSnapshot(bool isPrivate) override {}
    void OnSurfaceChanged(int32_t width, int32_t height) override {};
    void SetColorMode(ColorMode colorMode) override {};
    void RebuildAllPages() override;

    void NavigatePage(uint8_t type, const PageTarget& target, const std::string& params) override;

    // discarded methods
    void AddPage(const RefPtr<AcePage>& page) override {}
    int32_t GetRouterSize() const override
    {
        return pageRouterManager_->GetStackSize();
    }
    RefPtr<AcePage> GetPage(int32_t pageId) const override
    {
        return nullptr;
    }
    void SendCallbackMessage(const std::string& callbackId, const std::string& data) const override {}
    void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const override {}
    void TransferComponentResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsResponseData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void TransferJsPluginGetError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override {}
    void TransferJsEventData(int32_t callbackId, int32_t code, std::vector<uint8_t>&& data) const override {}
    void LoadPluginJsCode(std::string&& jsCode) const override {}
    void LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen) const override {}
    void UpdateState(Frontend::State state) override {}
    void OnConfigurationUpdated(const std::string& data) override {}
    void OnSaveAbilityState(std::string& data) override {}
    void OnRestoreAbilityState(const std::string& data) override {}
    void OnNewWant(const std::string& data) override {}
    void OnActive() override {}
    void OnInactive() override {}
    bool OnStartContinuation() override
    {
        return false;
    }
    void OnCompleteContinuation(int32_t code) override {}
    void OnSaveData(std::string& data) override {}
    void GetPluginsUsed(std::string& data) override {}
    bool OnRestoreData(const std::string& data) override
    {
        return false;
    }
    void OnRemoteTerminated() override {}
    void OnNewRequest(const std::string& data) override {}
    void OnMemoryLevel(const int32_t level) override {}
    void NotifyAppStorage(const std::string& key, const std::string& value) override {}
    void OnLayoutCompleted(const std::string& componentId) override {}
    void OnDrawCompleted(const std::string& componentId) override {}
    void OnDrawChildrenCompleted(const std::string& componentId) override {}
    bool IsDrawChildrenCallbackFuncExist(const std::string& componentId) override
    {
        return false;
    }
    RefPtr<AceEventHandler> GetEventHandler() override
    {
        return nullptr;
    };
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEDN_COMMON_H
