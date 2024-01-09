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
#include <atomic>

#include "interfaces/inner_api/ace/ace_forward_compatibility.h"
#include "interfaces/inner_api/ace/navigation_controller.h"

#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/resource/shared_image_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "core/common/display_info.h"
#include "core/common/frontend.h"
#include "core/common/page_url_checker.h"
#include "core/common/platform_res_register.h"
#include "core/common/settings.h"
#include "core/common/window.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/distributed_ui.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/event/pointer_event.h"
#include "core/pipeline/pipeline_base.h"
#include "core/common/container_consts.h"

namespace OHOS::Ace {

using PageTask = std::function<void()>;
using TouchEventCallback = std::function<void(const TouchEvent&, const std::function<void()>&,
    const RefPtr<NG::FrameNode>&)>;
using KeyEventCallback = std::function<bool(const KeyEvent&)>;
using MouseEventCallback = std::function<void(const MouseEvent&, const std::function<void()>&,
    const RefPtr<NG::FrameNode>&)>;
using AxisEventCallback = std::function<void(const AxisEvent&, const std::function<void()>&,
    const RefPtr<NG::FrameNode>&)>;
using RotationEventCallBack = std::function<bool(const RotationEvent&)>;
using CardViewPositionCallBack = std::function<void(int id, float offsetX, float offsetY)>;
using DragEventCallBack = std::function<void(const PointerEvent& pointerEvent, const DragEventAction& action)>;
using StopDragCallback = std::function<void()>;

class ACE_FORCE_EXPORT Container : public virtual AceType {
    DECLARE_ACE_TYPE(Container, AceType);

public:
    Container() = default;
    ~Container() override = default;

    virtual void Initialize() = 0;

    virtual void Destroy() = 0;

    virtual bool IsKeyboard()
    {
        return false;
    }

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

    virtual void DestroyHeapProfiler() {}

    virtual void ForceFullGC() {}

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

    virtual void SetOrientation(Orientation orientation) {}

    virtual Orientation GetOrientation()
    {
        return Orientation::UNSPECIFIED;
    }

    virtual RefPtr<DisplayInfo> GetDisplayInfo()
    {
        return {};
    }

    virtual NG::SafeAreaInsets GetKeyboardSafeArea()
    {
        return {};
    }

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

    void SetTempDir(const std::string& path)
    {
        tempDir_ = path;
    }

    const std::string& GetTempDir() const
    {
        return tempDir_;
    }

    virtual void SetViewFirstUpdating(std::chrono::time_point<std::chrono::high_resolution_clock> time) {}

    virtual void UpdateResourceConfiguration(const std::string& jsonStr) {}

    static int32_t CurrentId();
    static RefPtr<Container> Current();
    static RefPtr<Container> GetContainer(int32_t containerId);
    static RefPtr<Container> GetActive();
    static RefPtr<Container> GetDefault();
    static RefPtr<Container> GetFoucsed();
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
        return container ? container->useNewPipeline_ : AceForwardCompatibility::IsUseNG();
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

    bool IsDynamicRender() const
    {
        return isDynamicRender_;
    }

    void SetIsDynamicRender(bool isDynamicRender)
    {
        isDynamicRender_ = isDynamicRender;
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

    virtual float GetSmallWindowScale() const
    {
        return 1.0f;
    }

    virtual void NotifyConfigurationChange(bool, const OnConfigurationChange& configurationChange = { false, false }) {}
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

    virtual bool IsSceneBoardEnabled()
    {
        return false;
    }

    virtual bool GetCurPointerEventInfo(
        int32_t pointerId, int32_t& globalX, int32_t& globalY, int32_t& sourceType, StopDragCallback&& stopDragCallback)
    {
        return false;
    }

    virtual bool RequestAutoFill(const RefPtr<NG::FrameNode>& node, AceAutoFillType autoFillType)
    {
        return false;
    }

    virtual bool RequestAutoSave(const RefPtr<NG::FrameNode>& node)
    {
        return false;
    }

    virtual std::shared_ptr<NavigationController> GetNavigationController(const std::string& navigationId)
    {
        return nullptr;
    }

    static bool LessThanAPIVersion(PlatformVersion version)
    {
        return PipelineBase::GetCurrentContext() &&
               PipelineBase::GetCurrentContext()->GetMinPlatformVersion() < static_cast<int32_t>(version);
    }

    static bool GreatOrEqualAPIVersion(PlatformVersion version)
    {
        return PipelineBase::GetCurrentContext() &&
               PipelineBase::GetCurrentContext()->GetMinPlatformVersion() >= static_cast<int32_t>(version);
    }

    void SetAppBar(const RefPtr<NG::AppBarView>& appBar)
    {
        appBar_ = appBar;
    }

    RefPtr<NG::AppBarView> GetAppBar() const
    {
        return appBar_;
    }

    template<ContainerType type>
    static int32_t GenerateId();

private:
    static bool IsIdAvailable(int32_t id);

protected:
    std::chrono::time_point<std::chrono::high_resolution_clock> createTime_;
    bool firstUpdateData_ = true;
    std::string cardHapPath_;
    bool useNewPipeline_ = false;
    std::mutex stateMutex_;
    Frontend::State state_ = Frontend::State::UNDEFINE;
    bool isFRSCardContainer_ = false;
    bool isDynamicRender_ = false;

private:
    std::string moduleName_;
    std::string bundlePath_;
    std::string filesDataPath_;
    std::string tempDir_;
    bool usePartialUpdate_ = false;
    Settings settings_;
    RefPtr<PageUrlChecker> pageUrlChecker_;
    bool isModule_ = false;
    std::shared_ptr<NG::DistributedUI> distributedUI_;
    RefPtr<NG::AppBarView> appBar_;
    ACE_DISALLOW_COPY_AND_MOVE(Container);
};

template<ContainerType type>
int32_t Container::GenerateId()
{
    static std::atomic<int32_t> gInstanceId;
    int32_t id;
    do {
        id = type * CONTAINER_ID_DIVIDE_SIZE + gInstanceId.fetch_add(1) % CONTAINER_ID_DIVIDE_SIZE;
    } while (!IsIdAvailable(id));
    return id;
}

template<>
int32_t Container::GenerateId<PLUGIN_SUBCONTAINER>();

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_H
