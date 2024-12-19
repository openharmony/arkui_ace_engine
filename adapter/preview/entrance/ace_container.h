/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_CONTAINER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_CONTAINER_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "adapter/preview/entrance/ace_run_args.h"
#include "adapter/preview/entrance/ace_view_preview.h"
#include "adapter/preview/external/ability/stage/stage_pkg_context_info.h"
#include "adapter/preview/osal/fetch_manager.h"
#include "base/resource/asset_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/js_message_dispatcher.h"
#include "core/common/platform_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"


#include <refbase.h>

namespace OHOS::Rosen {
    class Window;
}

namespace OHOS::Ace::Platform {

namespace {
// Different with mobile, we don't support multi-instances in Windows, because we only want
// preview UI effect, it doesn't make sense to create multi ability in one process.
constexpr int32_t ACE_INSTANCE_ID = 0;
} // namespace

using UIEnvCallback = std::function<void(const OHOS::Ace::RefPtr<PipelineContext>& context)>;
using OnRouterChangeCallback = bool (*)(const std::string currentRouterPath);

// AceContainer is the instance have its own pipeline and thread models, it can contains multiple pages.
class AceContainer : public Container, public JsMessageDispatcher {
    DECLARE_ACE_TYPE(AceContainer, Container, JsMessageDispatcher);

public:
    static void CreateContainer(
        int32_t instanceId, FrontendType type, bool useNewPipeline, bool useCurrentEventRunner = false);
    static void DestroyContainer(int32_t instanceId);

    static void AddAssetPath(int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths);
    static void SetResourcesPathAndThemeStyle(int32_t instanceId, const std::string& systemResourcesPath,
        const std::string& hmsResourcesPath, const std::string& appResourcesPath, const int32_t& themeId,
        const ColorMode& colorMode);

#ifndef ENABLE_ROSEN_BACKEND
    static void SetView(AceViewPreview* view, double density, int32_t width, int32_t height);
#else
    static void SetView(AceViewPreview* view, sptr<Rosen::Window> rsWindow, double density, int32_t width,
        int32_t height, UIEnvCallback callback);
#endif

    static UIContentErrorCode RunPage(
        int32_t instanceId, const std::string& url, const std::string& params, bool isNamedRouter = false);
    static RefPtr<AceContainer> GetContainerInstance(int32_t instanceId);
    static void AddRouterChangeCallback(int32_t instanceId, const OnRouterChangeCallback& onRouterChangeCallback);
    static void NativeOnConfigurationUpdated(int32_t instanceId);

    AceContainer(int32_t instanceId, FrontendType type, bool useNewPipeline, bool useCurrentEventRunner = false);
    ~AceContainer() override = default;

    void Initialize() override;

    void Destroy() override;

    void DestroyView() override;

    int32_t GetInstanceId() const override
    {
        return instanceId_;
    }

    std::string GetHostClassName() const override
    {
        return "";
    }

    RefPtr<Frontend> GetFrontend() const override
    {
        return frontend_;
    }

    RefPtr<PlatformBridge> GetMessageBridge() const
    {
        return messageBridge_;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const override
    {
        return taskExecutor_;
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
        return 0;
    }

    int32_t GetViewPosY() const override
    {
        return 0;
    }

    uint32_t GetWindowId() const override
    {
        return 0;
    }

    void SetWindowId(uint32_t windowId) override {}

    bool WindowIsShow() const override
    {
        return true;
    }

    RefPtr<AceView> GetAceView() const override
    {
        return aceView_;
    }

    void* GetView() const override
    {
        return static_cast<void*>(AceType::RawPtr(aceView_));
    }

    void SetWindowModal(WindowModal windowModal)
    {
        windowModal_ = windowModal;
    }

    void SetColorScheme(ColorScheme colorScheme)
    {
        colorScheme_ = colorScheme;
    }

    FrontendType GetType() const
    {
        return type_;
    }

    ResourceConfiguration GetResourceConfiguration() const override
    {
        return resourceInfo_.GetResourceConfiguration();
    }

    void SetResourceConfiguration(const ResourceConfiguration& config)
    {
        resourceInfo_.SetResourceConfiguration(config);
    }

    void UpdateResourceConfiguration(const std::string& jsonStr) override;

    void FetchResponse(const ResponseData responseData, const int32_t callbackId) const;

    void CallCurlFunction(const RequestData requestData, const int32_t callbackId) const override;

    void Dispatch(
        const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const override;

    void DispatchSync(
        const std::string& group, std::vector<uint8_t>&& data, uint8_t** resData, int64_t& position) const override
    {}

    void DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override;

    void UpdateDeviceConfig(const DeviceConfig& deviceConfig);

    void LoadDocument(const std::string& url, const std::string& componentName);

    void RunNativeEngineLoop();

    void SetStageCardConfig(const std::string& pageProfile, const std::string& selectUrl);

    void SetPkgContextInfo(const RefPtr<StagePkgContextInfo>& PkgContextInfo);

    void SetPageProfile(const std::string& pageProfile)
    {
        pageProfile_ = pageProfile;
    }

    void InitializeAppConfig(const std::string& assetPath, const std::string& bundleName,
        const std::string& moduleName, const std::string& compileMode);

    void SetCardFrontend(WeakPtr<Frontend> frontend, int64_t cardId) override
    {
        std::lock_guard<std::mutex> lock(cardFrontMutex_);
        cardFrontendMap_.try_emplace(cardId, frontend);
    }

    WeakPtr<Frontend> GetCardFrontend(int64_t cardId) const override
    {
        std::lock_guard<std::mutex> lock(cardFrontMutex_);
        auto it = cardFrontendMap_.find(cardId);
        if (it != cardFrontendMap_.end()) {
            return it->second;
        }
        return nullptr;
    }

    void GetCardFrontendMap(std::unordered_map<int64_t, WeakPtr<Frontend>>& cardFrontendMap) const override
    {
        cardFrontendMap = cardFrontendMap_;
    }

    void SetCardPipeline(WeakPtr<PipelineBase> pipeline, int64_t cardId) override
    {
        std::lock_guard<std::mutex> lock(cardPipelineMutex_);
        cardPipelineMap_.try_emplace(cardId, pipeline);
    }

    WeakPtr<PipelineBase> GetCardPipeline(int64_t cardId) const override
    {
        std::lock_guard<std::mutex> lock(cardPipelineMutex_);
        auto it = cardPipelineMap_.find(cardId);
        if (it == cardPipelineMap_.end()) {
            return nullptr;
        }
        return it->second;
    }

    static std::string GetContentInfo(int32_t instanceId, ContentInfoType type);
    void SetSharedRuntime(void* runtime) override
    {
        sharedRuntime_ = runtime;
    }
    void SetInstallationFree(bool installationFree)
    {
        installationFree_ = installationFree;
    }

    void SetLabelId(int32_t labelId)
    {
        labelId_ = labelId;
    }
    static void SetComponentModeFlag(bool isComponentMode)
    {
        isComponentMode_ = isComponentMode;
    }

    void SetContainerSdkPath(const std::string& containerSdkPath)
    {
        containerSdkPath_ = containerSdkPath;
    }

    void NotifyConfigurationChange(bool, const ConfigurationChange& configurationChange) override;

    // Support to execute the ets code mocked by developer
    void SetMockModuleList(const std::map<std::string, std::string>& mockJsonInfo)
    {
        mockJsonInfo_ = mockJsonInfo;
    }

    void SetBundleName(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }

    void SetModuleName(const std::string& moduleName)
    {
        moduleName_ = moduleName;
    }

private:
    void InitializeFrontend();
    void InitializeCallback();
    void SetHspBufferTrackerCallback();
    // Support to execute the ets code mocked by developer
    void SetMockModuleListToJsEngine();

#ifndef ENABLE_ROSEN_BACKEND
    void AttachView(
        std::shared_ptr<Window> window, AceViewPreview* view, double density, int32_t width, int32_t height);
#else
    void AttachView(std::shared_ptr<Window> window, AceViewPreview* view, double density, int32_t width, int32_t height,
        UIEnvCallback callback);
#endif

    RefPtr<AceViewPreview> aceView_ = nullptr;
    int32_t instanceId_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<PlatformResRegister> resRegister_;
    RefPtr<PipelineBase> pipelineContext_;
    RefPtr<Frontend> frontend_;
    RefPtr<PlatformBridge> messageBridge_;
    FrontendType type_ { FrontendType::JSON };
    WindowModal windowModal_ { WindowModal::NORMAL };
    ColorScheme colorScheme_ { ColorScheme::SCHEME_LIGHT };
    ResourceInfo resourceInfo_;
    static std::once_flag onceFlag_;
    std::string pageProfile_;
    std::unordered_map<int64_t, WeakPtr<Frontend>> cardFrontendMap_;
    std::unordered_map<int64_t, WeakPtr<PipelineBase>> cardPipelineMap_;
    mutable std::mutex cardFrontMutex_;
    mutable std::mutex cardPipelineMutex_;
    void* sharedRuntime_ = nullptr;
    std::string bundleName_;
    std::string moduleName_;
    RefPtr<StagePkgContextInfo> PkgContextInfo_;

    // Support to execute the ets code mocked by developer
    std::map<std::string, std::string> mockJsonInfo_;

    // app bar to use
    bool installationFree_ = false;
    int32_t labelId_;
    static bool isComponentMode_;
    std::string containerSdkPath_;

    ACE_DISALLOW_COPY_AND_MOVE(AceContainer);
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_CONTAINER_H
