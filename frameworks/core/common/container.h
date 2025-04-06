/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include <atomic>
#include <functional>
#include <mutex>
#include <unordered_map>

#include "interfaces/inner_api/ace/ace_forward_compatibility.h"
#include "interfaces/inner_api/ace/constants.h"
#include "interfaces/inner_api/ace/navigation_controller.h"

#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/resource/shared_image_manager.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "base/view_data/ace_auto_fill_error.h"
#include "base/view_data/hint_to_type_wrap.h"
#include "core/common/ace_application_info.h"
#include "core/common/container_consts.h"
#include "core/common/container_handler.h"
#include "core/common/display_info.h"
#include "core/common/display_info_utils.h"
#include "core/common/frontend.h"
#include "core/common/page_url_checker.h"
#include "core/common/page_viewport_config.h"
#include "core/common/platform_res_register.h"
#include "core/common/resource/resource_configuration.h"
#include "core/common/settings.h"
#include "core/common/window.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/distributed_ui.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/navigation/navigation_route.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/event/non_pointer_event.h"
#include "core/event/pointer_event.h"

namespace OHOS::Ace {

using PageTask = std::function<void()>;
using TouchEventCallback = std::function<void(const TouchEvent&, const std::function<void()>&,
    const RefPtr<NG::FrameNode>&)>;
using KeyEventCallback = std::function<bool(const KeyEvent&)>;
using NonPointerEventCallback = std::function<bool(const NonPointerEvent&, const std::function<void()>&)>;
using MouseEventCallback = std::function<void(const MouseEvent&, const std::function<void()>&,
    const RefPtr<NG::FrameNode>&)>;
using AxisEventCallback = std::function<void(const AxisEvent&, const std::function<void()>&,
    const RefPtr<NG::FrameNode>&)>;
using RotationEventCallBack = std::function<bool(const RotationEvent&)>;
using CardViewPositionCallBack = std::function<void(int id, float offsetX, float offsetY)>;
using DragEventCallBack = std::function<void(const DragPointerEvent&, const DragEventAction&,
    const RefPtr<NG::FrameNode>&)>;
using StopDragCallback = std::function<void()>;
using CrownEventCallback = std::function<bool(const CrownEvent&, const std::function<void()>&)>;

class PipelineBase;

class ACE_FORCE_EXPORT Container : public virtual AceType {
    DECLARE_ACE_TYPE(Container, AceType);

public:
    Container() = default;
    ~Container() override = default;

    virtual void Initialize() = 0;

    virtual void Destroy() = 0;

    virtual void SetAppRunningUniqueId(const std::string& uniqueId) {};

    virtual const std::string& GetAppRunningUniqueId() const
    {
        static const std::string res;
        return res;
    }

    virtual bool IsKeyboard()
    {
        return false;
    }

    virtual void DestroyView() {}
    virtual bool UpdatePopupUIExtension(const RefPtr<NG::FrameNode>& node,
        uint32_t autoFillSessionId, bool isNative = true)
    {
        return false;
    }

    virtual bool ClosePopupUIExtension(uint32_t autoFillSessionId)
    {
        return false;
    }

    virtual HintToTypeWrap PlaceHolderToType(const std::string& onePlaceHolder)
    {
        HintToTypeWrap hintToTypeWrap;
        return hintToTypeWrap;
    }

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

    virtual RefPtr<AceView> GetAceView() const = 0;

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

    virtual void SetParentId(int32_t parentId) {}

    virtual int32_t GetParentId() const
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

    void SetCurrentDisplayOrientation(DisplayOrientation orientation)
    {
        displayOrientation_ = orientation;
    }
    DisplayOrientation GetCurrentDisplayOrientation() const
    {
        return displayOrientation_;
    }
    virtual RefPtr<PageViewportConfig> GetCurrentViewportConfig() const
    {
        return nullptr;
    }
    virtual RefPtr<PageViewportConfig> GetTargetViewportConfig(Orientation orientation,
        bool enableStatusBar, bool statusBarAnimated, bool enableNavigationIndicator)
    {
        return nullptr;
    }
    virtual void SetRequestedOrientation(
        Orientation orientation, bool needAnimation = true) {}
    virtual Orientation GetRequestedOrientation()
    {
        return Orientation::UNSPECIFIED;
    }
    virtual bool IsPcOrPadFreeMultiWindowMode() const { return false; }
    virtual bool IsFullScreenWindow() const { return true; }
    virtual bool SetSystemBarEnabled(SystemBarType type, bool enable, bool animation) { return true; }

    virtual RefPtr<DisplayInfo> GetDisplayInfo();

    virtual void InitIsFoldable();

    virtual bool IsFoldable();

    virtual FoldStatus GetCurrentFoldStatus();

    virtual FoldStatus GetFoldStatusFromListener()
    {
        return GetCurrentFoldStatus();
    }

    virtual void InitFoldStatusFromListener() {}

    virtual NG::SafeAreaInsets GetKeyboardSafeArea();

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

    void SetBundleName(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }

    const std::string& GetBundleName() const
    {
        return bundleName_;
    }

    void SetModuleName(const std::string& moduleName)
    {
        moduleName_ = moduleName;
    }

    std::string GetModuleName() const
    {
        return moduleName_;
    }

    virtual bool IsMainWindow() const { return false; }
    virtual bool IsSubWindow() const { return false; }
    virtual bool IsDialogWindow() const { return false; }
    virtual bool IsSystemWindow() const { return false; }
    virtual bool IsHostMainWindow() const { return false; }
    virtual bool IsHostSubWindow() const { return false; }
    virtual bool IsHostDialogWindow() const { return false; }
    virtual bool IsHostSystemWindow() const { return false; }
    virtual bool IsHostSceneBoardWindow() const { return false; }
    virtual bool IsSubContainer() const { return false; }
    virtual bool IsFormRender() const { return false; }
    virtual uint32_t GetParentMainWindowId(uint32_t currentWindowId) const
    {
        return 0;
    }

    virtual void SetIsFormRender(bool isFormRender) {};

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

    static int32_t SafelyId();
    static int32_t CurrentId();
    static int32_t CurrentIdSafely();
    static int32_t CurrentIdSafelyWithCheck();
    static RefPtr<Container> Current();
    static RefPtr<Container> CurrentSafely();
    static RefPtr<Container> CurrentSafelyWithCheck();
    static RefPtr<Container> GetContainer(int32_t containerId);
    static RefPtr<Container> GetActive();
    static RefPtr<Container> GetDefault();
    static RefPtr<Container> GetFoucsed();
    static RefPtr<Container> GetByWindowId(uint32_t windowId);
    static RefPtr<TaskExecutor> CurrentTaskExecutor();
    static RefPtr<TaskExecutor> CurrentTaskExecutorSafely();
    static RefPtr<TaskExecutor> CurrentTaskExecutorSafelyWithCheck();
    static void UpdateCurrent(int32_t id);
    static ColorMode CurrentColorMode();

    void SetUseNewPipeline()
    {
        useNewPipeline_ = true;
    }

    void SetUsePartialUpdate()
    {
        usePartialUpdate_ = true;
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

    static bool IsInFormContainer() {
        auto container = Current();
        return container ? container->isFRSCardContainer_ : false;
    }

    static bool IsInSubContainer()
    {
        auto container = Current();
        return container ? container->IsSubContainer() : false;
    }

    Window* GetWindow() const;

    virtual uint64_t GetDisplayId() const
    {
        return -1;
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

    virtual std::vector<std::string> GetRegisterComponents() { return {}; };

    void SetPageUrlChecker(const RefPtr<PageUrlChecker>& pageUrlChecker)
    {
        pageUrlChecker_ = pageUrlChecker;
    }

    const RefPtr<PageUrlChecker>& GetPageUrlChecker()
    {
        return pageUrlChecker_;
    }

    void SetNavigationRoute(const RefPtr<NG::NavigationRoute>& navigationRoute)
    {
        navigationRoute_ = navigationRoute;
    }

    RefPtr<NG::NavigationRoute> GetNavigationRoute() const
    {
        return navigationRoute_;
    }

    virtual bool IsDialogContainer() const
    {
        return false;
    }

    virtual void SetWindowScale(float windowScale) {}

    virtual float GetWindowScale() const
    {
        return 1.0f;
    }

    virtual void NotifyConfigurationChange(bool, const ConfigurationChange& configurationChange = { false, false }) {}

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

    virtual bool IsSceneBoardWindow()
    {
        return false;
    }

    virtual bool IsCrossAxisWindow()
    {
        return false;
    }

    virtual bool IsUIExtensionWindow()
    {
        return false;
    }

    virtual bool IsSceneBoardEnabled()
    {
        return false;
    }

    virtual bool GetCurPointerEventInfo(DragPointerEvent& dragPointerEvent, StopDragCallback&& stopDragCallback)
    {
        return false;
    }

    virtual bool GetCurPointerEventSourceType(int32_t& sourceType)
    {
        return false;
    }

    virtual int32_t RequestAutoFill(const RefPtr<NG::FrameNode>& node, AceAutoFillType autoFillType, bool isNewPassWord,
        bool& isPopup, uint32_t& autoFillSessionId, bool isNative = true,
        const std::function<void()>& onFinish = nullptr,
        const std::function<void()>& onUIExtNodeBindingCompleted = nullptr)
    {
        return AceAutoFillError::ACE_AUTO_FILL_DEFAULT;
    }

    virtual bool IsNeedToCreatePopupWindow(const AceAutoFillType& autoFillType)
    {
        return false;
    }

    virtual bool RequestAutoSave(const RefPtr<NG::FrameNode>& node, const std::function<void()>& onFinish = nullptr,
        const std::function<void()>& onUIExtNodeBindingCompleted = nullptr, bool isNative = true,
        int32_t instanceId = -1)
    {
        return false;
    }


    virtual std::shared_ptr<NavigationController> GetNavigationController(const std::string& navigationId)
    {
        return nullptr;
    }

    /**
     * @description: [Deprecated]. Compare whether the min compatible api version of the application is less than the
     * incoming target version. This interface is just use before api12(not include api12), after api12 when you judge
     * version, use LessThanAPITargetVersion(PlatformVersion version).
     * @param: Target version to be isolated.
     * @return: return the compare result.
     */
    static bool LessThanAPIVersion(PlatformVersion version);

    /**
     * @description: [Deprecated]. Compare whether the min compatible api version of the application is less than the
     * incoming target version. This interface is just use before api12(not include api12), after api12 when you judge
     * version, use GreatOrEqualAPITargetVersion(PlatformVersion version).
     * @param: Target version to be isolated.
     * @return: return the compare result.
     */
    static bool GreatOrEqualAPIVersion(PlatformVersion version);

    /**
     * @description: Compare whether the min compatible api version of the application is less than the incoming target
     * version. This interface is just for when you use LessThanAPIVersion in instance does not exist situation.
     * @param: Target version to be isolated.
     * @return: return the compare result.
     */
    static bool LessThanAPIVersionWithCheck(PlatformVersion version);

    /**
     * @description: Compare whether the min compatible api version of the application is greater than or equal to the
     * incoming target version. This interface is just for when you use GreatOrEqualAPIVersion in instance does not
     * exist situation.
     * @param: Target version to be isolated.
     * @return: return the compare result.
     */
    static bool GreatOrEqualAPIVersionWithCheck(PlatformVersion version);

    /**
     * @description: Compare whether the target api version of the application is less than the incoming target
     * version.
     * @param: Target version to be isolated.
     * @return: return the compare result.
     */
    static bool LessThanAPITargetVersion(PlatformVersion version)
    {
        auto container = Current();
        CHECK_NULL_RETURN(container, false);
        auto apiTargetVersion = container->GetApiTargetVersion();
        return apiTargetVersion < static_cast<int32_t>(version);
    }

    /**
     * @description: Compare whether the target api version of the application is greater than or equal to the incoming
     * target.
     * @param: Target version to be isolated.
     * @return: return the compare result.
     */
    static bool GreatOrEqualAPITargetVersion(PlatformVersion version)
    {
        auto container = Current();
        if (!container) {
            auto apiTargetVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion() % 1000;
            return apiTargetVersion >= static_cast<int32_t>(version);
        }
        auto apiTargetVersion = container->GetApiTargetVersion();
        return apiTargetVersion >= static_cast<int32_t>(version);
    }

    static int32_t GetCurrentApiTargetVersion()
    {
        auto container = Current();
        if (!container) {
            return AceApplicationInfo::GetInstance().GetApiTargetVersion() % 1000;
        }
        return container->GetApiTargetVersion();
    }

    void SetAppBar(const RefPtr<NG::AppBarView>& appBar)
    {
        appBar_ = appBar;
    }

    RefPtr<NG::AppBarView> GetAppBar() const
    {
        return appBar_;
    }

    virtual void TerminateUIExtension() {}
    virtual bool UIExtensionIsHalfScreen()
    {
        return false;
    }
    template<ContainerType type>
    static int32_t GenerateId();
    static void SetFontScale(int32_t instanceId, float fontScale);
    static void SetFontWeightScale(int32_t instanceId, float fontScale);

    /**
     * @description: Get the target api version of the application.
     * @return: The target api version of the application.
     */
    int32_t GetApiTargetVersion() const
    {
        return apiTargetVersion_;
    }

    /**
     * @description: Set the target api version of the application.
     * @param: The target api version of the application.
     */
    void SetApiTargetVersion(int32_t apiTargetVersion)
    {
        apiTargetVersion_ = apiTargetVersion % 1000;
    }

    UIContentType GetUIContentType() const
    {
        return uIContentType_;
    }

    void SetUIContentType(UIContentType uIContentType)
    {
        uIContentType_ = uIContentType;
    }

    void DestroyToastSubwindow(int32_t instanceId);

    virtual void CheckAndSetFontFamily() {};

    virtual bool IsFreeMultiWindow() const
    {
        return false;
    }

    virtual bool IsWaterfallWindow() const
    {
        return false;
    }

    virtual Rect GetUIExtensionHostWindowRect(int32_t instanceId)
    {
        return Rect();
    }

    virtual bool IsFloatingWindow() const
    {
        return false;
    }

    void RegisterContainerHandler(const RefPtr<ContainerHandler>& containerHandler)
    {
        containerHandler_ = containerHandler;
    }

    RefPtr<ContainerHandler> GetContainerHandler()
    {
        return containerHandler_;
    }

    void SetCurrentDisplayId(uint64_t displayId)
    {
        currentDisplayId_ = displayId;
    }

    uint64_t GetCurrentDisplayId() const
    {
        return currentDisplayId_;
    }

    virtual void SetColorMode(ColorMode mode)
    {
        colorMode_ = mode;
    }

    virtual ColorMode GetColorMode() const
    {
        return colorMode_;
    }

    virtual ResourceConfiguration GetResourceConfiguration() const = 0;

    void DestroySelectOverlaySubwindow(int32_t instanceId);

    static bool IsNodeInKeyGuardWindow(const RefPtr<NG::FrameNode>& node);

    virtual bool GetLastMovingPointerPosition(DragPointerEvent& dragPointerEvent)
    {
        return false;
    }

    virtual std::vector<Rect> GetCurrentFoldCreaseRegion();

    virtual Rect GetDisplayAvailableRect() const
    {
        return Rect();
    }

    static bool CheckRunOnThreadByThreadId(int32_t currentId, bool defaultRes);

protected:
    bool IsFontFileExistInPath(const std::string& path);
    std::vector<std::string> GetFontFamilyName(const std::string& path);
    bool endsWith(std::string str, std::string suffix);

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
    // for common handler
    RefPtr<ContainerHandler> containerHandler_;
    RefPtr<DisplayInfoUtils> displayManager_ = AceType::MakeRefPtr<DisplayInfoUtils>();

private:
    std::string bundleName_;
    std::string moduleName_;
    std::string bundlePath_;
    std::string filesDataPath_;
    std::string tempDir_;
    bool usePartialUpdate_ = false;
    DisplayOrientation displayOrientation_ = DisplayOrientation::PORTRAIT;
    Settings settings_;
    RefPtr<PageUrlChecker> pageUrlChecker_;
    RefPtr<NG::NavigationRoute> navigationRoute_;
    bool isModule_ = false;
    std::shared_ptr<NG::DistributedUI> distributedUI_;
    RefPtr<NG::AppBarView> appBar_;
    int32_t apiTargetVersion_ = 0;
    // Define the type of UI Content, for example, Security UIExtension.
    UIContentType uIContentType_ = UIContentType::UNDEFINED;
    uint64_t currentDisplayId_ = 0;
    ColorMode colorMode_ = ColorMode::LIGHT;
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
