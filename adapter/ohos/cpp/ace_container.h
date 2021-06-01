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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_CONTAINER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_CONTAINER_H

#include <memory>

#include "adapter/ohos/cpp/ace_ability.h"
#include "adapter/ohos/cpp/platform_event_callback.h"
#include "base/resource/asset_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/js_message_dispatcher.h"

namespace OHOS::Ace::Platform {
class AceContainer : public Container, public JsMessageDispatcher {
    DECLARE_ACE_TYPE(AceContainer, Container, JsMessageDispatcher);

public:
    AceContainer(int32_t instanceId, FrontendType type, AceAbility* aceAbility,
        std::unique_ptr<PlatformEventCallback> callback);
    ~AceContainer() override = default;

    static bool Register();

    int32_t GetInstanceId() const override
    {
        if (aceView_) {
            return aceView_->GetInstanceId();
        }
        return 0;
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

    AceView* GetAceView() const
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

    void OnFinish()
    {
        if (platformEventCallback_) {
            platformEventCallback_->OnFinish();
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

    static void CreateContainer(int32_t instanceId, FrontendType type, AceAbility* aceAbility,
        std::unique_ptr<PlatformEventCallback> callback);
    static void DestroyContainer(int32_t instanceId);
    static bool RunPage(int32_t instanceId, int32_t pageId, const std::string& content, const std::string& params);
    static bool PushPage(int32_t instanceId, const std::string& content, const std::string& params);
    static bool OnBackPressed(int32_t instanceId);
    static void OnShow(int32_t instanceId);
    static void OnHide(int32_t instanceId);
    static void OnActive(int32_t instanceId);
    static void OnInactive(int32_t instanceId);
    static std::string OnSaveData(int32_t instanceId);
    static bool OnRestoreData(int32_t instanceId, const std::string& data);
    static void OnNewRequest(int32_t instanceId, const std::string& data);
    static void AddAssetPath(int32_t instanceId, const std::string& packagePath, const std::vector<std::string>& paths);
    static void SetView(AceView* view, double density, int32_t width, int32_t height);
    static void SetFontScale(int32_t instanceId, float fontScale);
    static void SetWindowStyle(int32_t instanceId, WindowModal windowModal, ColorScheme colorScheme);

    static RefPtr<AceContainer> GetContainer(int32_t instanceId);
    static bool UpdatePage(int32_t instanceId, int32_t pageId, const std::string& content);

private:
    void InitializeFrontend();
    void InitializeCallback();

    void AttachView(std::unique_ptr<Window> window, AceView* view, double density, int32_t width, int32_t height);
    int32_t instanceId_ = 0;
    AceView* aceView_ = nullptr;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<PlatformResRegister> resRegister_;
    RefPtr<PipelineContext> pipelineContext_;
    RefPtr<Frontend> frontend_;
    FrontendType type_ = FrontendType::JS;
    std::unique_ptr<PlatformEventCallback> platformEventCallback_;
    WindowModal windowModal_ { WindowModal::NORMAL };
    ColorScheme colorScheme_ { ColorScheme::FIRST_VALUE };
    AceAbility* aceAbility_ = nullptr;
    int32_t pageId_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(AceContainer);
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_CONTAINER_H
