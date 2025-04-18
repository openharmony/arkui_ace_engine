/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <list>
#include <memory>
#include <mutex>
#include <optional>

#include "display_manager.h"
#include "dm_common.h"
#include "interfaces/inner_api/ace/arkui_rect.h"
#include "interfaces/inner_api/ace/viewport_config.h"
#include "native_engine/native_reference.h"
#include "native_engine/native_value.h"

#include "adapter/ohos/entrance/ace_ability.h"
#include "adapter/ohos/entrance/platform_event_callback.h"
#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "base/view_data/ace_auto_fill_error.h"
#include "base/view_data/hint_to_type_wrap.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "base/view_data/view_data_wrap.h"
#include "core/common/ace_view.h"
#include "core/common/container.h"
#include "core/common/display_info.h"
#include "core/common/font_manager.h"
#include "core/common/js_message_dispatcher.h"
#include "core/common/render_boundary_manager.h"
#include "core/common/resource/resource_configuration.h"
#include "core/common/router_recover_record.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Accessibility {
class AccessibilityElementInfo;
}

namespace OHOS::Ace {
class FontManager;
}

namespace OHOS::Ace::Platform {
#ifdef ACE_ENABLE_VK
namespace {
class HighContrastObserver;
}
#endif

using UIEnvCallback = std::function<void(const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context)>;
using SharePanelCallback = std::function<void(const std::string& bundleName, const std::string& abilityName)>;
using AbilityOnQueryCallback = std::function<void(const std::string& queryWord)>;
using DataHandlerErr = OHOS::Rosen::DataHandlerErr;
using SubSystemId = OHOS::Rosen::SubSystemId;
using DataConsumeCallback = OHOS::Rosen::DataConsumeCallback;

struct ParsedConfig {
    std::string colorMode;
    std::string deviceAccess;
    std::string languageTag;
    std::string direction;
    std::string densitydpi;
    std::string themeTag;
    std::string fontFamily;
    std::string fontScale;
    std::string fontWeightScale;
    std::string colorModeIsSetByApp;
    std::string mcc;
    std::string mnc;
    std::string preferredLanguage;
    std::string fontId;
    bool IsValid() const
    {
        return !(colorMode.empty() && deviceAccess.empty() && languageTag.empty() && direction.empty() &&
                 densitydpi.empty() && themeTag.empty() && fontScale.empty() && fontWeightScale.empty() &&
                 colorModeIsSetByApp.empty() && mcc.empty() && mnc.empty() && fontFamily.empty() &&
                 preferredLanguage.empty() && fontId.empty());
    }
};

struct SingleHandTransform {
    SingleHandTransform() = default;
    SingleHandTransform(float x, float y, float scaleX, float scaleY)
        : x_(x), y_(y), scaleX_(scaleX), scaleY_(scaleY) {}

    float x_ = 0.0f;
    float y_ = 0.0f;
    float scaleX_ = 1.0f;
    float scaleY_ = 1.0f;
};

using ConfigurationChangedCallback = std::function<void(const ParsedConfig& config, const std::string& configuration)>;

class ACE_FORCE_EXPORT AceContainer : public Container, public JsMessageDispatcher {
    DECLARE_ACE_TYPE(AceContainer, Container, JsMessageDispatcher);

public:
    AceContainer(int32_t instanceId, FrontendType type, std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility,
        std::unique_ptr<PlatformEventCallback> callback, bool useCurrentEventRunner = false,
        bool useNewPipeline = false);
    AceContainer(int32_t instanceId, FrontendType type, std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
        std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
        bool useCurrentEventRunner = false, bool isSubContainer = false, bool useNewPipeline = false);

    AceContainer(int32_t instanceId, FrontendType type, std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
        std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
        std::shared_ptr<TaskWrapper> taskWrapper, bool useCurrentEventRunner = false, bool isSubContainer = false,
        bool useNewPipeline = false);

    AceContainer(int32_t instanceId, FrontendType type);

    ~AceContainer() override;

    bool UpdatePopupUIExtension(const RefPtr<NG::FrameNode>& node,
        uint32_t autoFillSessionId, bool isNative = true) override;

    bool ClosePopupUIExtension(uint32_t autoFillSessionId) override;

    void Initialize() override;

    void Destroy() override;

    bool IsKeyboard() override;

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
        std::lock_guard<std::mutex> lock(frontendMutex_);
        return frontend_;
    }

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
        std::lock_guard<std::mutex> lock(pipelineMutex_);
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

    RefPtr<AceView> GetAceView() const override
    {
        std::lock_guard<std::mutex> lock(viewMutex_);
        return aceView_;
    }

    void* GetView() const override
    {
        std::lock_guard<std::mutex> lock(viewMutex_);
        return static_cast<void*>(AceType::RawPtr(aceView_));
    }

    void SetWindowModal(WindowModal windowModal)
    {
        windowModal_ = windowModal;
    }

    void SetInstallationFree(bool installationFree)
    {
        installationFree_ = installationFree;
    }

    void SetSharePanelCallback(SharePanelCallback&& callback)
    {
        sharePanelCallback_ = std::move(callback);
    }

    void SetColorScheme(ColorScheme colorScheme)
    {
        colorScheme_ = colorScheme;
    }

    ResourceConfiguration GetResourceConfiguration() const override
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

    std::string GetHapPath() const override
    {
        return resourceInfo_.GetHapPath();
    }

    const ResourceInfo& GetResourceInfo() const
    {
        return resourceInfo_;
    }

    std::shared_ptr<Framework::JsValue> GetJsContext();
    void SetJsContext(const std::shared_ptr<Framework::JsValue>& jsContext);
    std::shared_ptr<OHOS::AbilityRuntime::Context> GetAbilityContext();

    void SetOrientation(Orientation orientation) override
    {
        CHECK_NULL_VOID(uiWindow_);
        auto dmOrientation = static_cast<Rosen::Orientation>(static_cast<uint32_t>(orientation));
        uiWindow_->SetRequestedOrientation(dmOrientation);
    }

    RefPtr<PageViewportConfig> GetCurrentViewportConfig() const override;
    RefPtr<PageViewportConfig> GetTargetViewportConfig(Orientation orientation,
        bool enableStatusBar, bool statusBarAnimated, bool enableNavigationIndicator) override;
    void SetRequestedOrientation(Orientation orientation, bool needAnimation = true) override;
    Orientation GetRequestedOrientation() override;

    uint64_t GetDisplayId() const override
    {
        CHECK_NULL_RETURN(uiWindow_, -1);
        return uiWindow_->GetDisplayId();
    }

    Orientation GetOrientation() override
    {
        CHECK_NULL_RETURN(uiWindow_, Orientation::UNSPECIFIED);
        auto dmOrientation = uiWindow_->GetRequestedOrientation();
        return static_cast<Orientation>(static_cast<uint32_t>(dmOrientation));
    }

    void SetHapPath(const std::string& hapPath);

    void Dispatch(
        const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const override;

    void DispatchSync(
        const std::string& group, std::vector<uint8_t>&& data, uint8_t** resData, int64_t& position) const override
    {}

    void DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const override;

    bool Dump(const std::vector<std::string>& params, std::vector<std::string>& info) override;
    bool DumpCommon(
        const std::vector<std::string>& params, std::vector<std::string>& info);
    bool DumpDynamicUiContent(
        const std::vector<std::string>& params, std::vector<std::string>& info);

    bool DumpInfo(const std::vector<std::string>& params);

    bool DumpRSNodeByStringID(const std::vector<std::string>& params);

    bool OnDumpInfo(const std::vector<std::string>& params);

    void TriggerGarbageCollection() override;

    void DumpHeapSnapshot(bool isPrivate) override;

    void DestroyHeapProfiler() override;

    void ForceFullGC() override;

    void SetLocalStorage(NativeReference* storage, const std::shared_ptr<OHOS::AbilityRuntime::Context>& context);

    void CheckAndSetFontFamily() override;

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

    void OnStartAbilityOnQuery(const std::string& queryWord)
    {
        if (abilityOnQueryCallback_) {
            abilityOnQueryCallback_(queryWord);
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

    void SetSharedRuntime(void* runtime) override
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

    bool IsFormRender() const override
    {
        return isFormRender_;
    }

    void* GetSharedRuntime() override
    {
        return sharedRuntime_;
    }

    void SetParentId(int32_t parentId) override
    {
        parentId_ = parentId;
    }

    void SetWindowScale(float windowScale) override
    {
        windowScale_ = windowScale;
    }

    float GetWindowScale() const override
    {
        return windowScale_;
    }

    double GetWindowDensity() const
    {
        if (!uiWindow_) {
            return 1.0;
        }
        return static_cast<double>(uiWindow_->GetVirtualPixelRatio());
    }

    int32_t GetParentId() const override
    {
        return parentId_;
    }

    void SetFocusWindowId(uint32_t focusWindowId)
    {
        if (pipelineContext_) {
            pipelineContext_->SetFocusWindowId(focusWindowId);
        }
    }

    void SetRealHostWindowId(uint32_t realHostWindowId)
    {
        if (pipelineContext_) {
            pipelineContext_->SetRealHostWindowId(realHostWindowId);
        }
    }

    bool IsUseCustomBg() const
    {
        return isUseCustomBg_;
    }

    void SetIsUseCustomBg(bool isUseCustomBg)
    {
        isUseCustomBg_ = isUseCustomBg;
    }

    bool IsTransparentBg() const;

    void SetAbilityOnSearch(AbilityOnQueryCallback&& callback)
    {
        abilityOnQueryCallback_ = std::move(callback);
    }

    static void CreateContainer(int32_t instanceId, FrontendType type, const std::string& instanceName,
        std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility, std::unique_ptr<PlatformEventCallback> callback,
        bool useCurrentEventRunner = false, bool useNewPipeline = false);

    static void DestroyContainer(int32_t instanceId, const std::function<void()>& destroyCallback = nullptr);
    static UIContentErrorCode RunPage(
        int32_t instanceId, const std::string& content, const std::string& params, bool isNamedRouter = false);
    static UIContentErrorCode RunPage(
        int32_t instanceId, const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params);
    static bool PushPage(int32_t instanceId, const std::string& content, const std::string& params);
    static bool RunDynamicPage(
        int32_t instanceId, const std::string& content, const std::string& params, const std::string& entryPoint);
    static bool OnBackPressed(int32_t instanceId);
    static void OnShow(int32_t instanceId);
    static void OnHide(int32_t instanceId);
    static void OnActive(int32_t instanceId);
    static void OnInactive(int32_t instanceId);
    static void ActiveWindow(int32_t instanceId);
    static void UnActiveWindow(int32_t instanceId);
    static void OnNewWant(int32_t instanceId, const std::string& data);
    static bool OnStartContinuation(int32_t instanceId);
    static std::string OnSaveData(int32_t instanceId);
    static bool OnRestoreData(int32_t instanceId, const std::string& data);
    static void OnCompleteContinuation(int32_t instanceId, int result);
    static void OnRemoteTerminated(int32_t instanceId);
    static void OnConfigurationUpdated(int32_t instanceId, const std::string& configuration);
    static void OnNewRequest(int32_t instanceId, const std::string& data);
    static void AddAssetPath(int32_t instanceId, const std::string& packagePath, const std::string& hapPath,
        const std::vector<std::string>& paths);
    static void AddLibPath(int32_t instanceId, const std::vector<std::string>& libPath);
    static void SetView(const RefPtr<AceView>& view, double density, int32_t width, int32_t height,
        sptr<OHOS::Rosen::Window> rsWindow, UIEnvCallback callback = nullptr);
    static UIContentErrorCode SetViewNew(
        const RefPtr<AceView>& view, double density, float width, float height, sptr<OHOS::Rosen::Window> rsWindow);
    static void SetUIWindow(int32_t instanceId, sptr<OHOS::Rosen::Window> uiWindow);
    static sptr<OHOS::Rosen::Window> GetUIWindow(int32_t instanceId);
    static OHOS::AppExecFwk::Ability* GetAbility(int32_t instanceId);
    static OHOS::AbilityRuntime::Context* GetRuntimeContext(int32_t instanceId);
    static void SetWindowStyle(int32_t instanceId, WindowModal windowModal, ColorScheme colorScheme);
    static std::pair<RouterRecoverRecord, UIContentErrorCode> RestoreRouterStack(
        int32_t instanceId, const std::string& contentInfo, ContentInfoType type);
    static std::string GetContentInfo(int32_t instanceId, ContentInfoType type);

    static RefPtr<AceContainer> GetContainer(int32_t instanceId);
    static bool UpdatePage(int32_t instanceId, int32_t pageId, const std::string& content);
    static bool RemoveOverlayBySubwindowManager(int32_t instanceId);

    static bool CloseWindow(int32_t instanceId);
    static bool HideWindow(int32_t instanceId);

    // ArkTsCard
    static std::shared_ptr<Rosen::RSSurfaceNode> GetFormSurfaceNode(int32_t instanceId);

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

    bool WindowIsShow() const override
    {
        if (!uiWindow_) {
            return false;
        }
        return uiWindow_->GetWindowState() == Rosen::WindowState::STATE_SHOWN;
    }

    void SetWindowPos(int32_t left, int32_t top);

    void SetIsSubContainer(bool isSubContainer)
    {
        isSubContainer_ = isSubContainer;
    }

    void SetIsFormRender(bool isFormRender) override
    {
        isFormRender_ = isFormRender;
    }

    void SetAppRunningUniqueId(const std::string& uniqueId) override;

    const std::string& GetAppRunningUniqueId() const override;

    void InitializeSubContainer(int32_t parentContainerId);
    static void SetDialogCallback(int32_t instanceId, FrontendDialogCallback callback);

    std::shared_ptr<OHOS::AbilityRuntime::Context> GetAbilityContextByModule(
        const std::string& bundle, const std::string& module);

    void BuildResConfig(
        ResourceConfiguration& resConfig, ConfigurationChange& configurationChange, const ParsedConfig& parsedConfig);
    void ProcessColorModeUpdate(
        ResourceConfiguration& resConfig, ConfigurationChange& configurationChange, const ParsedConfig& parsedConfig);
    void UpdateConfiguration(
        const ParsedConfig& parsedConfig, const std::string& configuration, bool abilityLevel = false);
    void UpdateConfigurationSyncForAll(
        const ParsedConfig& parsedConfig, const std::string& configuration);

    void NotifyConfigurationChange(
        bool needReloadTransition, const ConfigurationChange& configurationChange = { false, false }) override;

    void AddOnConfigurationChange(int32_t instanceId, ConfigurationChangedCallback &&callback)
    {
        configurationChangedCallbacks_.emplace(instanceId, std::move(callback));
    }

    void RemoveOnConfigurationChange(int32_t instanceId)
    {
        configurationChangedCallbacks_.erase(instanceId);
    }

    void HotReload() override;

    bool IsUseStageModel() const override
    {
        return useStageModel_;
    }

    void GetCardFrontendMap(std::unordered_map<int64_t, WeakPtr<Frontend>>& cardFrontendMap) const override
    {
        cardFrontendMap = cardFrontendMap_;
    }

    void SetToken(sptr<IRemoteObject>& token);
    sptr<IRemoteObject> GetToken();
    void SetParentToken(sptr<IRemoteObject>& token);
    sptr<IRemoteObject> GetParentToken();
    uint32_t GetParentWindowType() const;
    uint32_t GetWindowType() const;

    std::string GetWebHapPath() const override
    {
        return webHapPath_;
    }

    NG::SafeAreaInsets GetViewSafeAreaByType(OHOS::Rosen::AvoidAreaType type,
        std::optional<NG::RectF> windowRect = std::nullopt);

    NG::SafeAreaInsets GetKeyboardSafeArea() override;

    Rosen::AvoidArea GetAvoidAreaByType(Rosen::AvoidAreaType type, int32_t apiVersion = Rosen::API_VERSION_INVALID);

    uint32_t GetStatusBarHeight();

    Rosen::WindowMode GetWindowMode() const
    {
        CHECK_NULL_RETURN(uiWindow_, Rosen::WindowMode::WINDOW_MODE_UNDEFINED);
        return uiWindow_->GetWindowMode();
    }

    // ArkTSCard
    void UpdateFormData(const std::string& data);
    void UpdateFormSharedImage(const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap);
    void UpdateResource();

    void GetNamesOfSharedImage(std::vector<std::string>& picNameArray);
    void UpdateSharedImage(std::vector<std::string>& picNameArray, std::vector<int32_t>& byteLenArray,
        std::vector<int32_t>& fileDescriptorArray);
    void GetImageDataFromAshmem(
        const std::string& picName, Ashmem& ashmem, const RefPtr<PipelineBase>& pipelineContext, int len);

    bool IsLauncherContainer() override;
    bool IsSceneBoardWindow() override;
    bool IsCrossAxisWindow() override;
    bool IsUIExtensionWindow() override;
    bool IsSceneBoardEnabled() override;
    bool IsMainWindow() const override;
    bool IsSubWindow() const override;
    bool IsDialogWindow() const override;
    bool IsSystemWindow() const override;
    bool IsHostMainWindow() const override;
    bool IsHostSubWindow() const override;
    bool IsHostDialogWindow() const override;
    bool IsHostSystemWindow() const override;
    bool IsHostSceneBoardWindow() const override;
    uint32_t GetParentMainWindowId(uint32_t currentWindowId) const override;

    void SetCurPointerEvent(const std::shared_ptr<MMI::PointerEvent>& currentEvent);
    bool GetCurPointerEventInfo(DragPointerEvent& dragPointerEvent, StopDragCallback&& stopDragCallback) override;

    bool GetCurPointerEventSourceType(int32_t& sourceType) override;

    int32_t RequestAutoFill(const RefPtr<NG::FrameNode>& node, AceAutoFillType autoFillType, bool isNewPassWord,
        bool& isPopup, uint32_t& autoFillSessionId, bool isNative = true,
        const std::function<void()>& onFinish = nullptr,
        const std::function<void()>& onUIExtNodeBindingCompleted = nullptr) override;
    bool IsNeedToCreatePopupWindow(const AceAutoFillType& autoFillType) override;
    bool RequestAutoSave(const RefPtr<NG::FrameNode>& node, const std::function<void()>& onFinish,
        const std::function<void()>& onUIExtNodeBindingCompleted, bool isNative = true,
        int32_t instanceId = -1) override;
    std::shared_ptr<NavigationController> GetNavigationController(const std::string& navigationId) override;
    void OverwritePageNodeInfo(const RefPtr<NG::FrameNode>& frameNode, AbilityBase::ViewData& viewData);
    HintToTypeWrap PlaceHolderToType(const std::string& onePlaceHolder) override;

    void SearchElementInfoByAccessibilityIdNG(
        int64_t elementId, int32_t mode, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output);

    void SearchElementInfosByTextNG(
        int64_t elementId, const std::string& text, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output);

    void FindFocusedElementInfoNG(
        int64_t elementId, int32_t focusType, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output);

    void FocusMoveSearchNG(
        int64_t elementId, int32_t direction, int64_t baseParent,
        Accessibility::AccessibilityElementInfo& output);

    bool NotifyExecuteAction(
        int64_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int64_t offset);

    void HandleAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
        int32_t eventType, int64_t timeMs);

    void TerminateUIExtension() override;
    bool UIExtensionIsHalfScreen() override;
    void SetUIExtensionSubWindow(bool isUIExtensionSubWindow)
    {
        isUIExtensionSubWindow_ = isUIExtensionSubWindow;
    }

    bool IsUIExtensionSubWindow()
    {
        return isUIExtensionSubWindow_;
    }

    void SetUIExtensionAbilityProcess(bool isUIExtensionAbilityProcess)
    {
        isUIExtensionAbilityProcess_ = isUIExtensionAbilityProcess;
    }

    bool IsUIExtensionAbilityProcess()
    {
        return isUIExtensionAbilityProcess_;
    }

    void SetUIExtensionAbilityHost(bool isUIExtensionAbilityHost)
    {
        isUIExtensionAbilityHost_ = isUIExtensionAbilityHost;
    }

    bool IsUIExtensionAbilityHost()
    {
        return isUIExtensionAbilityHost_;
    }

    void RecordResAdapter(const std::string& key)
    {
        resAdapterRecord_.emplace(key);
    }

    std::vector<Ace::RectF> GetOverlayNodePositions();

    void RegisterOverlayNodePositionsUpdateCallback(
        const std::function<void(std::vector<Ace::RectF>)>&& callback);

    OHOS::Rosen::WMError RegisterAvoidAreaChangeListener(sptr<OHOS::Rosen::IAvoidAreaChangedListener>& listener);
    OHOS::Rosen::WMError UnregisterAvoidAreaChangeListener(sptr<OHOS::Rosen::IAvoidAreaChangedListener>& listener);

    bool NeedFullUpdate(uint32_t limitKey);
    void NotifyDensityUpdate(double density);
    void NotifyDirectionUpdate();

    void SetRegisterComponents(const std::vector<std::string>& registerComponents)
    {
        registerComponents_ = registerComponents;
    }

    std::vector<std::string> GetRegisterComponents() override
    {
        return registerComponents_;
    }
    void RenderLayoutBoundary(bool isDebugBoundary);
    void AddWatchSystemParameter();
    void RemoveWatchSystemParameter();

    const std::vector<std::string>& GetUieParams() const
    {
        return paramUie_;
    }

    void UpdateResourceOrientation(int32_t orientation);
    void UpdateResourceDensity(double density, bool isUpdateResConfig);
    void SetDrawReadyEventCallback();

    bool IsFreeMultiWindow() const override
    {
        CHECK_NULL_RETURN(uiWindow_, false);
        return uiWindow_->GetFreeMultiWindowModeEnabledState();
    }

    bool IsWaterfallWindow() const override
    {
        CHECK_NULL_RETURN(uiWindow_, false);
        return uiWindow_->IsWaterfallModeEnabled();
    }

    Rect GetUIExtensionHostWindowRect(int32_t instanceId) override
    {
        CHECK_NULL_RETURN(IsUIExtensionWindow(), Rect());
        auto rect = uiWindow_->GetHostWindowRect(instanceId);
        return Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
    }
    void FireUIExtensionEventCallback(uint32_t eventId);
    void FireAccessibilityEventCallback(uint32_t eventId, int64_t parameter);

    bool IsFloatingWindow() const override
    {
        CHECK_NULL_RETURN(uiWindow_, false);
        return uiWindow_->GetWindowMode() == Rosen::WindowMode::WINDOW_MODE_FLOATING;
    }

    void SetSingleHandTransform(const SingleHandTransform& singleHandTransform)
    {
        singleHandTransform_ = singleHandTransform;
    }

    const SingleHandTransform& GetSingleHandTransform() const
    {
        return singleHandTransform_;
    }

    bool GetLastMovingPointerPosition(DragPointerEvent& dragPointerEvent) override;

    Rect GetDisplayAvailableRect() const override;

    void GetExtensionConfig(AAFwk::WantParams& want);

    void SetIsFocusActive(bool isFocusActive);

    void SetFontScaleAndWeightScale(int32_t instanceId);

    sptr<OHOS::Rosen::Window> GetUIWindowInner() const;

    void SetFoldStatusFromListener(FoldStatus foldStatus)
    {
        foldStatusFromListener_ = foldStatus;
    }

    FoldStatus GetFoldStatusFromListener() override
    {
        return foldStatusFromListener_;
    }

    void InitFoldStatusFromListener() override
    {
        foldStatusFromListener_ = GetCurrentFoldStatus();
    }

private:
    virtual bool MaybeRelease() override;
    void InitializeFrontend();
    void InitializeCallback();
    void InitializeTask(std::shared_ptr<TaskWrapper> taskWrapper = nullptr);
    void InitWindowCallback();

    void AttachView(std::shared_ptr<Window> window, const RefPtr<AceView>& view, double density, float width,
        float height, uint32_t windowId, UIEnvCallback callback = nullptr);
    void SetUIWindowInner(sptr<OHOS::Rosen::Window> uiWindow);
    std::weak_ptr<OHOS::AppExecFwk::Ability> GetAbilityInner() const;
    std::weak_ptr<OHOS::AbilityRuntime::Context> GetRuntimeContextInner() const;

    void RegisterStopDragCallback(int32_t pointerId, StopDragCallback&& stopDragCallback);
    void SetFontScaleAndWeightScale(const ParsedConfig& parsedConfig, ConfigurationChange& configurationChange);
    void ReleaseResourceAdapter();
    void FillAutoFillViewData(const RefPtr<NG::FrameNode> &node, RefPtr<ViewDataWrap> &viewDataWrap);

    void NotifyConfigToSubContainers(const ParsedConfig& parsedConfig, const std::string& configuration);
    void ProcessThemeUpdate(const ParsedConfig& parsedConfig, ConfigurationChange& configurationChange);
    DeviceOrientation ProcessDirectionUpdate(
        const ParsedConfig& parsedConfig, ConfigurationChange& configurationChange);
    void InitDragEventCallback();

    void RegisterUIExtDataConsumer();
    void UnRegisterUIExtDataConsumer();
    void DispatchUIExtDataConsume(
        NG::UIContentBusinessCode code, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply);
    void RegisterUIExtDataSendToHost();
    bool FireUIExtDataSendToHost(
        NG::UIContentBusinessCode code, const AAFwk::Want& data, NG::BusinessDataSendType type);
    bool FireUIExtDataSendToHostReply(
        NG::UIContentBusinessCode code, const AAFwk::Want& data, AAFwk::Want& reply);

    void RegisterAvoidInfoCallback();
    void RegisterAvoidInfoDataProcessCallback();

    void RegisterOrientationUpdateListener();
    void RegisterOrientationChangeListener();
    void InitSystemBarConfig();
    bool IsPcOrPadFreeMultiWindowMode() const override;
    bool IsFullScreenWindow() const override
    {
        CHECK_NULL_RETURN(uiWindow_, false);
        return uiWindow_->GetWindowMode() == Rosen::WindowMode::WINDOW_MODE_FULLSCREEN;
    }
    bool SetSystemBarEnabled(SystemBarType type, bool enable, bool animation) override;

    int32_t instanceId_ = 0;
    RefPtr<AceView> aceView_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<PlatformResRegister> resRegister_;
    RefPtr<PipelineBase> pipelineContext_;
    RefPtr<Frontend> frontend_;
    std::unordered_map<int64_t, WeakPtr<Frontend>> cardFrontendMap_;
    std::unordered_map<int64_t, WeakPtr<PipelineBase>> cardPipelineMap_;

    FrontendType type_ = FrontendType::JS;
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
    float windowScale_ = 1.0f;
    sptr<IRemoteObject> token_;
    sptr<IRemoteObject> parentToken_;
    FoldStatus foldStatusFromListener_ = FoldStatus::UNKNOWN;

    bool isSubContainer_ = false;
    bool isFormRender_ = false;
    int32_t parentId_ = 0;
    bool useStageModel_ = false;
    bool isUIExtensionSubWindow_ = false;
    bool isUIExtensionAbilityProcess_ = false;
    bool isUIExtensionAbilityHost_ = false;
    bool isUseCustomBg_ = false;

    DeviceOrientation orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;

    // for other AceContainer subscribe configuration from host AceContaier
    // key is instanceId, value is callback function
    std::unordered_map<int32_t, ConfigurationChangedCallback> configurationChangedCallbacks_;
    std::vector<std::string> registerComponents_;

    std::unordered_set<std::string> resAdapterRecord_;

    mutable std::mutex frontendMutex_;
    mutable std::mutex pipelineMutex_;
    mutable std::mutex destructMutex_;
    mutable std::mutex viewMutex_;

    mutable std::mutex cardFrontMutex_;
    mutable std::mutex cardPipelineMutex_;
    mutable std::mutex cardTokensMutex_;

    std::string webHapPath_;

    bool installationFree_ = false;
    SharePanelCallback sharePanelCallback_ = nullptr;
    AbilityOnQueryCallback abilityOnQueryCallback_ = nullptr;

    std::atomic_flag isDumping_ = ATOMIC_FLAG_INIT;

    std::string uniqueId_;

    // For custom drag event
    std::mutex pointerEventMutex_;
    std::shared_ptr<MMI::PointerEvent> currentPointerEvent_;
    std::unordered_map<int32_t, std::list<StopDragCallback>> stopDragCallbackMap_;
    std::map<int32_t, std::shared_ptr<MMI::PointerEvent>> currentEvents_;
    friend class WindowFreeContainer;
    ACE_DISALLOW_COPY_AND_MOVE(AceContainer);
    RefPtr<RenderBoundaryManager> renderBoundaryManager_ = Referenced::MakeRefPtr<RenderBoundaryManager>();

    // for Ui Extension dump param get
    std::vector<std::string> paramUie_;

    SingleHandTransform singleHandTransform_;

#ifdef ACE_ENABLE_VK
    void SubscribeHighContrastChange();
    void UnsubscribeHighContrastChange();
    std::shared_ptr<HighContrastObserver> highContrastObserver_ = nullptr;
#endif
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_ACE_CONTAINER_H
