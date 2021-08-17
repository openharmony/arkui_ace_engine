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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_PA_CONTAINER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_PA_CONTAINER_H

#include <memory>

#include "adapter/ohos/cpp/platform_event_callback.h"
#include "base/resource/asset_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/js_message_dispatcher.h"
#include "frameworks/core/common/backend.h"

namespace OHOS::Ace::Platform {
class PaContainer : public Container, public JsMessageDispatcher {
    DECLARE_ACE_TYPE(PaContainer, Container, JsMessageDispatcher);

public:
    PaContainer(int32_t instanceId, BackendType type, void* paAbility,
        std::unique_ptr<PlatformEventCallback> callback);
    ~PaContainer() override = default;

    void Initialize() override {}

    void Destroy() override {}

    int32_t GetInstanceId() const override
    {
        return instanceId_;
    }

    RefPtr<AssetManager> GetAssetManager() const override
    {
        return assetManager_;
    }

    RefPtr<Frontend> GetFrontend() const override
    {
        return nullptr;
    }

    RefPtr<PlatformResRegister> GetPlatformResRegister() const override
    {
        return nullptr;
    }

    RefPtr<PipelineContext> GetPipelineContext() const override
    {
        return nullptr;
    }

    RefPtr<Backend> GetBackend() const
    {
        return backend_;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const override
    {
        return taskExecutor_;
    }

    void Dispatch(
        const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const override;

    void DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override;

    void DispatchSync(
        const std::string &group, std::vector<uint8_t> &&data, uint8_t **resData, long &position) const override
    {}

    bool Dump(const std::vector<std::string>& params) override;

    void OnFinish()
    {
        if (platformEventCallback_) {
            platformEventCallback_->OnFinish();
        }
    }

    std::string GetHostClassName() const override
    {
        return "";
    }

    static bool Register();
    static void CreateContainer(int32_t instanceId, BackendType type, void* paAbility,
        std::unique_ptr<PlatformEventCallback> callback);
    static void DestroyContainer(int32_t instanceId);
    static RefPtr<PaContainer> GetContainer(int32_t instanceId);
    static bool RunPa(int32_t instanceId, const std::string &content, const std::string &params);
    static void AddAssetPath(int32_t instanceId, const std::string &packagePath, const std::vector<std::string> &paths);

private:
    void InitializeBackend();
    void InitializeCallback();

    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<Backend> backend_;

    int32_t instanceId_ = 0;
    BackendType type_ = BackendType::SERVICE;
    std::unique_ptr<PlatformEventCallback> platformEventCallback_;
    void *paAbility_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(PaContainer);
};
} // namespace OHOS::Ace::Platform
#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_PA_CONTAINER_H
