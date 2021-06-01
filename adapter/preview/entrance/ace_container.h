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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_CONTAINER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_CONTAINER_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "adapter/preview/entrance/ace_run_args.h"
#include "adapter/preview/entrance/flutter_ace_view.h"
#include "base/resource/asset_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/js_message_dispatcher.h"
#include "core/common/platform_bridge.h"

namespace OHOS::Ace::Platform {

// AceContainer is the instance have its own pipeline and thread models, it can contains multiple pages.
class AceContainer : public Container, public JsMessageDispatcher {
    DECLARE_ACE_TYPE(AceContainer, Container, JsMessageDispatcher);

public:
    static void CreateContainer(int32_t instanceId, FrontendType type);
    static void DestroyContainer(int32_t instanceId);

    static void AddAssetPath(int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths);
    static void SetResourcesPathAndThemeStyle(int32_t instanceId, const std::string& resourcesPath,
                                              const ThemeId& themeId, const ColorMode& colorMode);
    static void SetView(FlutterAceView* view, double density, int32_t width, int32_t height);
    static bool RunPage(int32_t instanceId, int32_t pageId, const std::string& url, const std::string& params);
    static RefPtr<AceContainer> GetContainerInstance(int32_t instanceId);

    AceContainer(int32_t instanceId, FrontendType type);
    ~AceContainer() override = default;

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

    RefPtr<PipelineContext> GetPipelineContext() const override
    {
        return pipelineContext_;
    }

    FlutterAceView* GetAceView() const
    {
        return aceView_;
    }

    void SetWindowModal(WindowModal windowModal)
    {
        windowModal_ = windowModal;
    }

    void SetColorScheme(ColorScheme colorScheme)
    {
        colorScheme_ = colorScheme;
    }

    void Dispatch(
        const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const override;

    void DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override;

    bool Dump(const std::vector<std::string>& params) override;

private:
    void InitializeFrontend();
    void InitializeCallback();

    void AttachView(
        std::unique_ptr<Window> window, FlutterAceView* view, double density, int32_t width, int32_t height);

    int32_t instanceId_;
    FlutterAceView* aceView_ = nullptr;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<PlatformResRegister> resRegister_;
    RefPtr<PipelineContext> pipelineContext_;
    RefPtr<Frontend> frontend_;
    FrontendType type_ { FrontendType::JSON };
    WindowModal windowModal_ { WindowModal::NORMAL };
    ColorScheme colorScheme_ { ColorScheme::SCHEME_LIGHT };
    DeviceResourceInfo deviceResourceInfo_;
    static std::once_flag onceFlag_;

    ACE_DISALLOW_COPY_AND_MOVE(AceContainer);
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_CONTAINER_H
