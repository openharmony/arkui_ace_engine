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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_CONTAINER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_CONTAINER_H

#include <memory>
#include <mutex>

#include "ability_context.h"
#include "native_engine/native_reference.h"
#include "native_engine/native_value.h"
#include "wm/wm_common.h"

#include "adapter/ohos/entrance/ace_ability.h"
#include "adapter/ohos/entrance/platform_event_callback.h"
#include "base/resource/asset_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/js_message_dispatcher.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::Platform {
using UIEnvCallback = std::function<void(const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context)>;
class ACE_FORCE_EXPORT AceContainer : public Container, public JsMessageDispatcher {
    DECLARE_ACE_TYPE(AceContainer, Container, JsMessageDispatcher);

public:
    AceContainer(int32_t instanceId, FrontendType type, bool isArkApp,
        std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility, std::unique_ptr<PlatformEventCallback> callback,
        bool useCurrentEventRunner = false, bool useNewPipeline = false);
    AceContainer(int32_t instanceId, FrontendType type, bool isArkApp,
        std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
        std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
        bool useCurrentEventRunner = false, bool isSubContainer = false, bool useNewPipeline = false);
    ~AceContainer() override = default;

    void Initialize() override;

    void Destroy() override;

    void DestroyView() override;

    static bool Register();

    int32_t GetInstanceId() const override
    {
        if (aceView_) {
            return aceView_->GetInstanceId();
        }
        return -1;
    }

    RefPtr<Frontend> GetFrontend() const override
    {
        return frontend_;
    }

    void SetCardFrontend(WeakPtr<Frontend> frontend, uint64_t cardId) override
    {
        std::lock_guard<std::mutex> lock(cardFrontMutex_);
        cardFrontendMap_.try_emplace(cardId, frontend);
    }

    WeakPtr<Frontend> GetCardFrontend(uint64_t cardId) const override
    {
        std::lock_guard<std::mutex> lock(cardFrontMutex_);
        auto it = cardFrontendMap_.find(cardId);
        if (it != cardFrontendMap_.end()) {
            return it->second;
        }
        return nullptr;
    }

    void SetCardPipeline(WeakPtr<PipelineBase> pipeline, uint64_t cardId) override
    {
        std::lock_guard<std::mutex> lock(cardPipelineMutex_);
        cardPipelineMap_.try_emplace(cardId, pipeline);
    }

    WeakPtr<PipelineBase> GetCardPipeline(uint64_t cardId) const override
    {
        std::lock_guard<std::mutex> lock(cardPipelineMutex_);
        auto it = cardPipelineMap_.find(cardId);
        if (it == cardPipelineMap_.end()) {
            return nullptr;
        }
        return it->second;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const override
    {
        return taskExecutor_;
    }

    void SetAssetManager(const RefPtr<AssetManager>& assetManager)
    {
        assetManager_ = assetManager;
        if (frontend_) {
            frontend_->SetAssetManager(assetManager);
        }
    }

    RefPtr<AssetManager> GetAssetManager() const override
    {
        return assetManager_;
    }

    RefPtr<PlatformResRegister> GetPlatformResRegister() const override
    {
        return resRegister_;
    }

    RefPtr<PipelineBase> GetPipelineContext() const override
    {
        return pipelineContext_;
    }

    int32_t GetViewWidth() const override
    {
        return aceView_ ? aceView_->GetWidth() : 0;
    }

    int32_t GetViewHeight() const override
    {
        return aceView_ ? aceView_->GetHeight() : 0;
    }

    int32_t GetViewPosX() const override
    {
        return aceView_ ? aceView_->GetPosX() : 0;
    }

    int32_t GetViewPosY() const override
    {
        return aceView_ ? aceView_->GetPosY() : 0;
    }

    AceView* GetAceView() const
    {
        return aceView_;
    }

    void* GetView() const override
    {
        return static_cast<void*>(aceView_);
    }

    void SetWindowModal(WindowModal windowModal)
    {
        windowModal_ = windowModal;
    }

    void SetColorScheme(ColorScheme colorScheme)
    {
        colorScheme_ = colorScheme;
    }

    ResourceConfiguration GetResourceConfiguration() const
    {
        return resourceInfo_.GetResourceConfiguration();
    }

    void SetResourceConfiguration(const ResourceConfiguration& config)
    {
        resourceInfo_.SetResourceConfiguration(config);
    }

    std::string GetPackagePathStr() const
    {
        return resourceInfo_.GetPackagePath();
    }

    void SetPackagePathStr(const std::string& packagePath)
    {
        resourceInfo_.SetPackagePath(packagePath);
    }

    std::string GetHapPath() const
    {
        return resourceInfo_.GetHapPath();
    }

    void SetHapPath(const std::string& hapPath);

    void Dispatch(
        const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const override;

    void DispatchSync(
        const std::string& group, std::vector<uint8_t>&& data, uint8_t** resData, int64_t& position) const override
    {}

    void DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override;

    bool Dump(const std::vector<std::string>& params) override;

    void TriggerGarbageCollection() override;

    void DumpHeapSnapshot(bool isPrivate) override;

    void SetLocalStorage(NativeReference* storage, NativeReference* context);

    void OnFinish()
    {
        if (platformEventCallback_) {
            platformEventCallback_->OnFinish();
        }
    }

    void OnStartAbility(const std::string& address)
    {
        if (platformEventCallback_) {
            platformEventCallback_->OnStartAbility(address);
        }
    }

    int32_t GeneratePageId()
    {
        return pageId_++;
    }

    std::string GetHostClassName() const override
    {
        return "";
    }

    void SetSharedRuntime(void* runtime)
    {
        sharedRuntime_ = runtime;
    }

    void SetPageProfile(const std::string& pageProfile)
    {
        pageProfile_ = pageProfile;
    }

    bool IsSubContainer() const override
    {
        return isSubContainer_;
    }

    void* GetSharedRuntime()
    {
        return sharedRuntime_;
    }

    void SetParentId(int32_t parentId)
    {
        parentId_ = parentId;
    }

    int32_t GetParentId() const
    {
        return parentId_;
    }

    static void CreateContainer(int32_t instanceId, FrontendType type, bool isArkApp, const std::string& instanceName,
        std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility, std::unique_ptr<PlatformEventCallback> callback,
        bool useCurrentEventRunner = false, bool useNewPipeline = false);

    static void DestroyContainer(int32_t instanceId, const std::function<void()>& destroyCallback = nullptr);
    static bool RunPage(int32_t instanceId, int32_t pageId, const std::string& content, const std::string& params);
    static bool PushPage(int32_t instanceId, const std::string& content, const std::string& params);
    static bool OnBackPressed(int32_t instanceId);
    static void OnShow(int32_t instanceId);
    static void OnHide(int32_t instanceId);
    static void OnActive(int32_t instanceId);
    static void OnInactive(int32_t instanceId);
    static void OnNewWant(int32_t instanceId, const std::string& data);
    static bool OnStartContinuation(int32_t instanceId);
    static std::string OnSaveData(int32_t instanceId);
    static bool OnRestoreData(int32_t instanceId, const std::string& data);
    static void OnCompleteContinuation(int32_t instanceId, int result);
    static void OnRemoteTerminated(int32_t instanceId);
    static void OnConfigurationUpdated(int32_t instanceId, const std::string& configuration);
    static void OnNewRequest(int32_t instanceId, const std::string& data);
    static void OnDialogUpdated(int32_t instanceId, const std::string& data);
    static void AddAssetPath(int32_t instanceId, const std::string& packagePath, const std::string& hapPath,
        const std::vector<std::string>& paths);
    static void AddLibPath(int32_t instanceId, const std::vector<std::string>& libPath);
    static void SetView(AceView* view, double density, int32_t width, int32_t height,
        sptr<OHOS::Rosen::Window> rsWindow, UIEnvCallback callback = nullptr);
    static void SetViewNew(
        AceView* view, double density, int32_t width, int32_t height, sptr<OHOS::Rosen::Window> rsWindow);
    static void SetUIWindow(int32_t instanceId, sptr<OHOS::Rosen::Window> uiWindow);
    static sptr<OHOS::Rosen::Window> GetUIWindow(int32_t instanceId);
    static OHOS::AppExecFwk::Ability* GetAbility(int32_t instanceId);
    static void SetFontScale(int32_t instanceId, float fontScale);
    static void SetWindowStyle(int32_t instanceId, WindowModal windowModal, ColorScheme colorScheme);
    static std::string RestoreRouterStack(int32_t instanceId, const std::string& contentInfo);
    static std::string GetContentInfo(int32_t instanceId);

    static RefPtr<AceContainer> GetContainer(int32_t instanceId);
    static bool UpdatePage(int32_t instanceId, int32_t pageId, const std::string& content);

    void SetWindowName(const std::string& name)
    {
        windowName_ = name;
    }

    std::string& GetWindowName()
    {
        return windowName_;
    }

    void SetWindowId(uint32_t windowId) override
    {
        windowId_ = windowId;
    }

    uint32_t GetWindowId() const override
    {
        return windowId_;
    }

    void SetWindowPos(int32_t left, int32_t top);

    void SetIsSubContainer(bool isSubContainer)
    {
        isSubContainer_ = isSubContainer;
    }

    void InitializeSubContainer(int32_t parentContainerId);
    static void SetDialogCallback(int32_t instanceId, FrontendDialogCallback callback);

    std::shared_ptr<OHOS::AbilityRuntime::Context> GetAbilityContextByModule(const std::string& bundle,
        const std::string& module);

    void UpdateConfiguration(
        const std::string& colorMode, const std::string& inputDevice, const std::string& languageTag);

    void NotifyConfigurationChange(bool needReloadTransition);

    bool IsUseStageModel() const override
    {
        return useStageModel_;
    }

    void GetCardFrontendMap(std::unordered_map<uint64_t, WeakPtr<Frontend>>& cardFrontendMap) const override
    {
        cardFrontendMap = cardFrontendMap_;
    }

private:
    void InitializeFrontend();
    void InitializeCallback();
    void InitializeTask();
    void InitWindowCallback();

    void AttachView(std::unique_ptr<Window> window, AceView* view, double density, int32_t width, int32_t height,
        int32_t windowId, UIEnvCallback callback = nullptr);
    void SetUIWindowInner(sptr<OHOS::Rosen::Window> uiWindow);
    sptr<OHOS::Rosen::Window> GetUIWindowInner() const;
    std::weak_ptr<OHOS::AppExecFwk::Ability> GetAbilityInner() const;
    int32_t instanceId_ = 0;
    AceView* aceView_ = nullptr;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<PlatformResRegister> resRegister_;
    RefPtr<PipelineBase> pipelineContext_;
    RefPtr<Frontend> frontend_;
    std::unordered_map<uint64_t, WeakPtr<Frontend>> cardFrontendMap_;
    std::unordered_map<uint64_t, WeakPtr<PipelineBase>> cardPipelineMap_;

    FrontendType type_ = FrontendType::JS;
    bool isArkApp_ = false;
    std::unique_ptr<PlatformEventCallback> platformEventCallback_;
    WindowModal windowModal_ { WindowModal::NORMAL };
    ColorScheme colorScheme_ { ColorScheme::FIRST_VALUE };
    ResourceInfo resourceInfo_;
    std::weak_ptr<OHOS::AppExecFwk::Ability> aceAbility_;
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext_;
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo_;
    void* sharedRuntime_ = nullptr;
    std::string pageProfile_;
    int32_t pageId_ = 0;
    bool useCurrentEventRunner_ = false;
    sptr<OHOS::Rosen::Window> uiWindow_ = nullptr;
    std::string windowName_;
    uint32_t windowId_ = OHOS::Rosen::INVALID_WINDOW_ID;

    bool isSubContainer_ = false;
    int32_t parentId_ = 0;
    bool useStageModel_ = false;

    mutable std::mutex cardFrontMutex_;
    mutable std::mutex cardPipelineMutex_;

    ACE_DISALLOW_COPY_AND_MOVE(AceContainer);
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_CONTAINER_H
