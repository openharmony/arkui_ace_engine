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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_H

#include <functional>
#include <mutex>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/resource/shared_image_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_application_info.h"
#include "core/common/frontend.h"
#include "core/common/page_url_checker.h"
#include "core/common/platform_res_register.h"
#include "core/common/settings.h"
#include "core/common/window.h"
#include "core/components_ng/base/distributed_ui.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

using PageTask = std::function<void()>;
using TouchEventCallback = std::function<void(const TouchEvent&, const std::function<void()>&)>;
using KeyEventCallback = std::function<bool(const KeyEvent&)>;
using MouseEventCallback = std::function<void(const MouseEvent&, const std::function<void()>&)>;
using AxisEventCallback = std::function<void(const AxisEvent&, const std::function<void()>&)>;
using RotationEventCallBack = std::function<bool(const RotationEvent&)>;
using CardViewPositionCallBack = std::function<void(int id, float offsetX, float offsetY)>;
using DragEventCallBack = std::function<void(int32_t x, int32_t y, const DragEventAction& action)>;

constexpr int32_t INSTANCE_ID_UNDEFINED = -1;
constexpr int32_t INSTANCE_ID_PLATFORM = -2;
constexpr int32_t MIN_PLUGIN_SUBCONTAINER_ID = 2000000;

class ACE_FORCE_EXPORT Container : public virtual AceType {
    DECLARE_ACE_TYPE(Container, AceType);

public:
    Container() = default;
    ~Container() override = default;

    virtual void Initialize() = 0;

    virtual void Destroy() = 0;

    virtual void DestroyView() {}

    // Get the instance id of this container
    virtual int32_t GetInstanceId() const = 0;

    // Get the ability name of this container
    virtual std::string GetHostClassName() const = 0;

    // Get the frontend of container
    virtual RefPtr<Frontend> GetFrontend() const = 0;

    // Get task executor.
    virtual RefPtr<TaskExecutor> GetTaskExecutor() const = 0;

    // Get assert manager.
    virtual RefPtr<AssetManager> GetAssetManager() const = 0;

    // Get platform resource register.
    virtual RefPtr<PlatformResRegister> GetPlatformResRegister() const = 0;

    // Get the pipelineContext of container.
    virtual RefPtr<PipelineBase> GetPipelineContext() const = 0;

    // Dump container.
    virtual bool Dump(const std::vector<std::string>& params, std::vector<std::string>& info);

    // Get the width/height of the view
    virtual int32_t GetViewWidth() const = 0;
    virtual int32_t GetViewHeight() const = 0;
    virtual int32_t GetViewPosX() const = 0;
    virtual int32_t GetViewPosY() const = 0;

    virtual uint32_t GetWindowId() const = 0;
    virtual void SetWindowId(uint32_t windowId) {}
    virtual bool WindowIsShow() const
    {
        return false;
    }

    virtual void* GetView() const = 0;

    // Trigger garbage collection
    virtual void TriggerGarbageCollection() {}

    virtual void DumpHeapSnapshot(bool isPrivate) {}

    virtual void NotifyFontNodes() {}

    virtual void NotifyAppStorage(const std::string& key, const std::string& value) {}

    virtual void SetCardFrontend(WeakPtr<Frontend> frontend, int64_t cardId) {}

    virtual WeakPtr<Frontend> GetCardFrontend(int64_t cardId) const
    {
        return nullptr;
    }

    virtual void SetCardPipeline(WeakPtr<PipelineBase>, int64_t cardId) {}

    virtual WeakPtr<PipelineBase> GetCardPipeline(int64_t cardId) const
    {
        return nullptr;
    }

    // Get MultiModal ptr.
    virtual uintptr_t GetMutilModalPtr() const
    {
        return 0;
    }

    virtual void ProcessScreenOnEvents() {}

    virtual void ProcessScreenOffEvents() {}

    virtual std::string GetHapPath() const
    {
        return {};
    }

    virtual std::string GetWebHapPath() const
    {
        return {};
    }

    void SetCreateTime(std::chrono::time_point<std::chrono::high_resolution_clock> time)
    {
        createTime_ = time;
    }

    bool IsFirstUpdate() const
    {
        return firstUpdateData_;
    }

    void AlreadyFirstUpdate()
    {
        firstUpdateData_ = false;
    }

    void SetModuleName(const std::string& moduleName)
    {
        moduleName_ = moduleName;
    }

    std::string GetModuleName() const
    {
        return moduleName_;
    }

    virtual bool IsMainWindow() const
    {
        return false;
    }

    virtual bool IsSubContainer() const
    {
        return false;
    }

    const std::string& GetCardHapPath() const
    {
        return cardHapPath_;
    }

    bool UpdateState(const Frontend::State& state);

    Settings& GetSettings()
    {
        return settings_;
    }

    void SetBundlePath(const std::string& path)
    {
        bundlePath_ = path;
    }

    const std::string& GetBundlePath() const
    {
        return bundlePath_;
    }

    void SetFilesDataPath(const std::string& path)
    {
        filesDataPath_ = path;
    }

    const std::string& GetFilesDataPath() const
    {
        return filesDataPath_;
    }

    virtual void SetViewFirstUpdating(std::chrono::time_point<std::chrono::high_resolution_clock> time) {}

    virtual void UpdateResourceConfiguration(const std::string& jsonStr) {}

    static int32_t CurrentId();
    static RefPtr<Container> Current();
    static RefPtr<Container> GetActive();
    static RefPtr<TaskExecutor> CurrentTaskExecutor();
    static void UpdateCurrent(int32_t id);

    void SetUseNewPipeline()
    {
        useNewPipeline_ = true;
    }

    bool IsUseNewPipeline() const
    {
        return useNewPipeline_;
    }

    static bool IsCurrentUseNewPipeline()
    {
        auto container = Current();
        return container ? container->useNewPipeline_ : false;
    }

    // SetCurrentUsePartialUpdate is called when initial render on a page
    // starts, see zyz_view_register loadDocument() implementation
    static bool IsCurrentUsePartialUpdate()
    {
        auto container = Current();
        return container ? container->usePartialUpdate_ : false;
    }

    static void SetCurrentUsePartialUpdate(bool useIt = false)
    {
        auto container = Current();
        if (container) {
            container->usePartialUpdate_ = useIt;
        }
    }

    Window* GetWindow() const
    {
        auto context = GetPipelineContext();
        return context ? context->GetWindow() : nullptr;
    }

    virtual bool IsUseStageModel() const
    {
        return false;
    }

    virtual void GetCardFrontendMap(std::unordered_map<int64_t, WeakPtr<Frontend>>& cardFrontendMap) const {}

    virtual void SetSharedRuntime(void* runtime) {}
    virtual void* GetSharedRuntime()
    {
        return nullptr;
    }

    bool IsFRSCardContainer() const
    {
        return isFRSCardContainer_;
    }

    void SetIsFRSCardContainer(bool isFRSCardContainer)
    {
        isFRSCardContainer_ = isFRSCardContainer;
    }

    void SetPageUrlChecker(const RefPtr<PageUrlChecker>& pageUrlChecker)
    {
        pageUrlChecker_ = pageUrlChecker;
    }

    const RefPtr<PageUrlChecker>& GetPageUrlChecker()
    {
        return pageUrlChecker_;
    }

    virtual bool IsDialogContainer() const
    {
        return false;
    }

    static bool IsForeground()
    {
        auto container = Current();
        return container ? container->state_ == Frontend::State::ON_SHOW : false;
    }

    virtual void NotifyConfigurationChange(bool, const OnConfigurationChange& configurationChange = {false, false}) {}
    virtual void HotReload() {}

    void SetIsModule(bool isModule)
    {
        isModule_ = isModule;
    }

    bool IsModule() const
    {
        return isModule_;
    }

    void SetDistributedUI(std::shared_ptr<NG::DistributedUI>& distributedUI)
    {
        distributedUI_ = distributedUI;
    }

    std::shared_ptr<NG::DistributedUI>& GetDistributedUI()
    {
        return distributedUI_;
    }

    virtual bool IsLauncherContainer()
    {
        return false;
    }

    virtual bool IsScenceBoardWindow()
    {
        return false;
    }

    virtual void GetCurPointerEventInfo(int32_t pointerId, int32_t& globalX, int32_t& globalY, int32_t& sourceType) {}

protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> createTime_;
    bool firstUpdateData_ = true;
    std::string cardHapPath_;
    bool useNewPipeline_ = false;
    std::mutex stateMutex_;
    Frontend::State state_ = Frontend::State::UNDEFINE;
    bool isFRSCardContainer_ = false;

private:
    std::string moduleName_;
    std::string bundlePath_;
    std::string filesDataPath_;
    bool usePartialUpdate_ = false;
    Settings settings_;
    RefPtr<PageUrlChecker> pageUrlChecker_;
    bool isModule_ = false;
    std::shared_ptr<NG::DistributedUI> distributedUI_;
    ACE_DISALLOW_COPY_AND_MOVE(Container);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_H
