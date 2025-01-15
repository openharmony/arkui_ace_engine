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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_UI_CONTENT_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_UI_CONTENT_IMPL_H

#include <list>

#include "ability_info.h"
#include "display_manager.h"
#include "dm/display_manager.h"
#include "interfaces/inner_api/ace/arkui_rect.h"
#include "interfaces/inner_api/ace/ui_content.h"
#include "interfaces/inner_api/ace/viewport_config.h"
#include "interfaces/inner_api/ui_session/ui_content_stub_impl.h"
#include "key_event.h"
#include "native_engine/native_engine.h"
#include "native_engine/native_value.h"
#include "wm/window.h"

#include "adapter/ohos/entrance/distributed_ui_manager.h"
#include "adapter/ohos/entrance/ace_viewport_config.h"
#include "base/thread/task_executor.h"
#include "base/view_data/view_data_wrap.h"
#include "core/common/asset_manager_impl.h"
#include "core/common/update_config_manager.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/popup_param.h"

namespace OHOS::Accessibility {
class AccessibilityElementInfo;
}

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UIContentImpl : public UIContent {
public:
    UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime);
    UIContentImpl(OHOS::AppExecFwk::Ability* ability);
    UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime, bool isCard);
    ~UIContentImpl()
    {
        UnSubscribeEventsPassThroughMode();
        ProcessDestructCallbacks();
        DestroyUIDirector();
        DestroyCallback();
    }

    // UI content lifeCycles
    UIContentErrorCode Initialize(OHOS::Rosen::Window* window, const std::string& url, napi_value storage) override;
    UIContentErrorCode Initialize(
        OHOS::Rosen::Window* window, const std::shared_ptr<std::vector<uint8_t>>& content, napi_value storage) override;
    UIContentErrorCode Initialize(OHOS::Rosen::Window* window, const std::shared_ptr<std::vector<uint8_t>>& content,
        napi_value storage, const std::string& contentName) override;
    UIContentErrorCode InitializeByName(
        OHOS::Rosen::Window* window, const std::string& name, napi_value storage) override;
    void InitializeByName(OHOS::Rosen::Window *window,
        const std::string &name, napi_value storage, uint32_t focusWindowId) override;
    void InitializeDynamic(int32_t hostInstanceId, const std::string& hapPath, const std::string& abcPath,
        const std::string& entryPoint, const std::vector<std::string>& registerComponents) override;
    void Initialize(
        OHOS::Rosen::Window* window, const std::string& url, napi_value storage, uint32_t focusWindowId) override;
    void Foreground() override;
    void Background() override;
    void Focus() override;
    void UnFocus() override;
    void Destroy() override;
    void OnNewWant(const OHOS::AAFwk::Want& want) override;

    // restore
    UIContentErrorCode Restore(OHOS::Rosen::Window* window, const std::string& contentInfo,
        napi_value storage, ContentInfoType type) override;
    std::string GetContentInfo(ContentInfoType type) const override;
    void DestroyUIDirector() override;
    void SetUIContentType(UIContentType uIContentType) override;
    void UpdateFontScale(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);

    // UI content event process
    bool ProcessBackPressed() override;
    void UpdateDialogResourceConfiguration(RefPtr<Container>& container,
        const std::shared_ptr<OHOS::AbilityRuntime::Context>& context);
    bool ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) override;
    bool ProcessPointerEventWithCallback(
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void()>& callback) override;
    bool ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme) override;
    bool ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) override;
    bool ProcessVsyncEvent(uint64_t timeStampNanos) override;
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) override;
    void UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr,
        const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas = {}) override;
    void UpdateViewportConfigWithAnimation(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
        AnimationOption animationOpt, const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr,
        const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas = {});
    void UIExtensionUpdateViewportConfig(const ViewportConfig& config);
    void UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDecor = true) override;
    void NotifyWindowMode(OHOS::Rosen::WindowMode mode) override;
    void UpdateDecorVisible(bool visible, bool hasDecor) override;
    void UpdateWindowBlur();
    void HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) override;
    void SetIgnoreViewSafeArea(bool ignoreViewSafeArea) override;
    void UpdateMaximizeMode(OHOS::Rosen::MaximizeMode mode) override;
    void ProcessFormVisibleChange(bool isVisible) override;
    void UpdateTitleInTargetPos(bool isShow, int32_t height) override;
    void NotifyRotationAnimationEnd() override;

    void ChangeSensitiveNodes(bool isSensitive) override;

    // Window color
    uint32_t GetBackgroundColor() override;
    void SetBackgroundColor(uint32_t color) override;
    void SetWindowContainerColor(uint32_t activeColor, uint32_t inactiveColor) override;

    bool NeedSoftKeyboard() override;

    void SetOnWindowFocused(const std::function<void()>& callback) override;

    // Current paintSize of window
    void GetAppPaintSize(OHOS::Rosen::Rect& paintrect) override;

    // Get paintSize of window by calculating
    void GetWindowPaintSize(OHOS::Rosen::Rect& paintrect) override;

    void DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override;

    // Set UIContent callback for custom window animation
    void SetNextFrameLayoutCallback(std::function<void()>&& callback) override;

    // Set UIContent callback after layout finish
    void SetFrameLayoutFinishCallback(std::function<void()>&& callback) override;

    // Receive memory level notification
    void NotifyMemoryLevel(int32_t level) override;

    void SetAppWindowTitle(const std::string& title) override;
    void SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap) override;

    // ArkTS Form
    void PreInitializeForm(OHOS::Rosen::Window* window, const std::string& url, napi_value storage) override;
    void RunFormPage() override;
    std::shared_ptr<Rosen::RSSurfaceNode> GetFormRootNode() override;
    void UpdateFormData(const std::string& data) override;
    void UpdateFormSharedImage(const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap) override;
    void ReloadForm(const std::string& url) override;

    void SetFormWidth(float width) override
    {
        formWidth_ = width;
    }
    void SetFormHeight(float height) override
    {
        formHeight_ = height;
    }
    float GetFormWidth() override
    {
        return formWidth_;
    }
    float GetFormHeight() override
    {
        return formHeight_;
    }

    void SetActionEventHandler(std::function<void(const std::string& action)>&& actionCallback) override;
    void SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback) override;
    void SetFormLinkInfoUpdateHandler(std::function<void(const std::vector<std::string>&)>&& callback) override;

    void OnFormSurfaceChange(float width, float height,
        OHOS::Rosen::WindowSizeChangeReason type = static_cast<OHOS::Rosen::WindowSizeChangeReason>(0),
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr) override;

    void SetFormBackgroundColor(const std::string& color) override;

    void RegisterAccessibilityChildTree(
        uint32_t parentWindowId, int32_t parentTreeId, int64_t parentElementId) override;
    void SetAccessibilityGetParentRectHandler(std::function<void(int32_t&, int32_t&)>&& callback) override;
    void SetAccessibilityGetParentRectHandler(
        std::function<void(AccessibilityParentRectInfo&)>&& callback) override;
    void DeregisterAccessibilityChildTree() override;
    void AccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override;

    void SetFontScaleFollowSystem(const bool fontScaleFollowSystem) override;

    SerializeableObjectArray DumpUITree() override
    {
        CHECK_NULL_RETURN(uiManager_, SerializeableObjectArray());
        return uiManager_->DumpUITree();
    }
    void SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate) override
    {
        CHECK_NULL_VOID(uiManager_);
        return uiManager_->SubscribeUpdate(onUpdate);
    }
    void UnSubscribeUpdate() override
    {
        CHECK_NULL_VOID(uiManager_);
        uiManager_->UnSubscribeUpdate();
    }
    void ProcessSerializeableInputEvent(const SerializeableObjectArray& array) override
    {
        CHECK_NULL_VOID(uiManager_);
        uiManager_->ProcessSerializeableInputEvent(array);
    }
    void RestoreUITree(const SerializeableObjectArray& array) override
    {
        CHECK_NULL_VOID(uiManager_);
        uiManager_->RestoreUITree(array);
    }
    void UpdateUITree(const SerializeableObjectArray& array) override
    {
        CHECK_NULL_VOID(uiManager_);
        uiManager_->UpdateUITree(array);
    }
    void SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent) override
    {
        CHECK_NULL_VOID(uiManager_);
        uiManager_->SubscribeInputEventProcess(onEvent);
    }
    void UnSubscribeInputEventProcess() override
    {
        CHECK_NULL_VOID(uiManager_);
        uiManager_->UnSubscribeInputEventProcess();
    }
    void GetResourcePaths(std::vector<std::string>& resourcesPaths, std::string& assetRootPath,
        std::vector<std::string>& assetBasePaths, std::string& resFolderName) override;
    void SetResourcePaths(const std::vector<std::string>& resourcesPaths, const std::string& assetRootPath,
        const std::vector<std::string>& assetBasePaths) override;

    napi_value GetUINapiContext() override;
    void SetIsFocusActive(bool isFocusActive) override;

    void UpdateResource() override;

    int32_t CreateModalUIExtension(const AAFwk::Want& want,
        const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config) override;
    void CloseModalUIExtension(int32_t sessionId) override;
    void UpdateModalUIExtensionConfig(
        int32_t sessionId, const ModalUIExtensionAllowedUpdateConfig& config) override;

    void SetParentToken(sptr<IRemoteObject> token) override;
    sptr<IRemoteObject> GetParentToken() override;
    AbilityBase::AutoFillType ViewDataToType(const AbilityBase::ViewData& viewData);
    bool DumpViewData(AbilityBase::ViewData& viewData, AbilityBase::AutoFillType& type) override;
    bool CheckNeedAutoSave() override;
    bool DumpViewData(const RefPtr<NG::FrameNode>& node, RefPtr<ViewDataWrap> viewDataWrap,
        bool skipSubAutoFillContainer = false, bool needsRecordData = false);

    void SearchElementInfoByAccessibilityId(
        int64_t elementId, int32_t mode,
        int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) override;

    void SearchElementInfosByText(
        int64_t elementId, const std::string& text, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) override;

    void FindFocusedElementInfo(
        int64_t elementId, int32_t focusType,
        int64_t baseParent, Accessibility::AccessibilityElementInfo& output) override;

    void FocusMoveSearch(
        int64_t elementId, int32_t direction,
        int64_t baseParent, Accessibility::AccessibilityElementInfo& output) override;

    bool NotifyExecuteAction(int64_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int64_t offset) override;

    void HandleAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
        int32_t eventType, int64_t timeMs) override;

    int32_t GetInstanceId() override
    {
        return instanceId_;
    }

    std::string RecycleForm() override;

    void RecoverForm(const std::string& statusData) override;
    Shadow GetPopupShadow();

    int32_t CreateCustomPopupUIExtension(const AAFwk::Want& want,
        const ModalUIExtensionCallbacks& callbacks, const CustomPopupUIExtensionConfig& config) override;
    bool GetTargetNode(
        int32_t& nodeIdLabel, RefPtr<NG::FrameNode>& targetNode, const CustomPopupUIExtensionConfig& config);
    void DestroyCustomPopupUIExtension(int32_t nodeId) override;
    void UpdateCustomPopupUIExtension(const CustomPopupUIExtensionConfig& config) override;

    void SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow) override;
    void SetContainerModalTitleHeight(int32_t height) override;
    void SetContainerButtonStyle(const Rosen::DecorButtonStyle& buttonStyle) override;
    int32_t GetContainerModalTitleHeight() override;
    bool GetContainerModalButtonsRect(Rosen::Rect& containerModal, Rosen::Rect& buttons) override;
    void SubscribeContainerModalButtonsRectChange(
        std::function<void(Rosen::Rect& containerModal, Rosen::Rect& buttons)>&& callback) override;
    void UpdateTransform(const OHOS::Rosen::Transform& transform) override;

    SerializedGesture GetFormSerializedGesture() override;

    void SetUIExtensionSubWindow(bool isUIExtensionSubWindow) override
    {
        isUIExtensionSubWindow_ = isUIExtensionSubWindow;
    }

    bool IsUIExtensionSubWindow() override
    {
        return isUIExtensionSubWindow_;
    }

    void SetUIExtensionAbilityProcess(bool isUIExtensionAbilityProcess) override
    {
        isUIExtensionAbilityProcess_ = isUIExtensionAbilityProcess;
    }

    bool IsUIExtensionAbilityProcess() override
    {
        return isUIExtensionAbilityProcess_;
    }

    void SetUIExtensionAbilityHost(bool isUIExtensionAbilityHost) override
    {
        isUIExtensionAbilityHost_ = isUIExtensionAbilityHost;
    }

    bool IsUIExtensionAbilityHost() override
    {
        return isUIExtensionAbilityHost_;
    }

    std::vector<Ace::RectF> GetOverlayNodePositions() const override;

    void RegisterOverlayNodePositionsUpdateCallback(
        const std::function<void(std::vector<Ace::RectF>)>& callback) const override;

    void SetFormRenderingMode(int8_t renderMode) override;

    void SetContentNodeGrayScale(float grayscale) override;

    void PreLayout() override;

    sptr<IRemoteObject> GetRemoteObj() override
    {
        return instance_;
    }

    void SetStatusBarItemColor(uint32_t color) override;

    void SetFontScaleAndWeightScale(const RefPtr<Platform::AceContainer>& container, int32_t instanceId);

    void SetForceSplitEnable(bool isForceSplit, const std::string& homePage) override;

    void UpdateDialogContainerConfig(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);

    void AddDestructCallback(void* key, const std::function<void()>& callback)
    {
        destructCallbacks_.emplace(key, callback);
    }

    void RemoveDestructCallback(void* key)
    {
        destructCallbacks_.erase(key);
    }

    void EnableContainerModalGesture(bool isEnable) override;

    bool GetContainerFloatingTitleVisible() override;

    bool GetContainerCustomTitleVisible() override;

    bool GetContainerControlButtonVisible() override;

    void OnContainerModalEvent(const std::string& name, const std::string& value) override;
    void UpdateConfigurationSyncForAll(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) override;

    int32_t AddFocusActiveChangeCallback(const std::function<void(bool isFocusAvtive)>& callback) override;
    void RemoveFocusActiveChangeCallback(int32_t handler) override;

    bool ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent,
        const std::function<void(bool)>& callback) override;

    bool ConfigCustomWindowMask(bool enable) override;
    void UpdateSingleHandTransform(const OHOS::Rosen::SingleHandTransform& transform) override;

    std::shared_ptr<Rosen::RSNode> GetRSNodeByStringID(const std::string& stringId) override;
private:
    UIContentErrorCode InitializeInner(
        OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, bool isNamedRouter);
    UIContentErrorCode CommonInitialize(
        OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, uint32_t focusWindowId = 0);
    UIContentErrorCode CommonInitializeForm(
        OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage);
    void InitializeSubWindow(OHOS::Rosen::Window* window, bool isDialog = false);
    void DestroyCallback() const;
    void ProcessDestructCallbacks();
    void SetConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);

    void InitializeSafeArea(const RefPtr<Platform::AceContainer>& container);
    void InitializeDisplayAvailableRect(const RefPtr<Platform::AceContainer>& container);

    void InitDragSummaryMap(const RefPtr<Platform::AceContainer>& container);

    RefPtr<PopupParam> CreateCustomPopupParam(bool isShow, const CustomPopupUIExtensionConfig& config);
    void OnPopupStateChange(const std::string& event, const CustomPopupUIExtensionConfig& config, int32_t nodeId);
    void SetCustomPopupConfig(int32_t nodeId, const CustomPopupUIExtensionConfig& config, int32_t popupId);

    void AddWatchSystemParameter();
    void StoreConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);
    void UnregisterDisplayManagerCallback();
    void RegisterLinkJumpCallback();
    void ExecuteUITask(std::function<void()> task, const std::string& name);
    void SubscribeEventsPassThroughMode();
    void UnSubscribeEventsPassThroughMode();
    bool GetWindowSizeChangeReason(OHOS::Rosen::WindowSizeChangeReason lastReason,
        OHOS::Rosen::WindowSizeChangeReason reason);
    std::weak_ptr<OHOS::AbilityRuntime::Context> context_;
    void* runtime_ = nullptr;
    OHOS::Rosen::Window* window_ = nullptr;
    std::string startUrl_;
    int32_t instanceId_ = -1;
    OHOS::sptr<OHOS::Rosen::IWindowDragListener> dragWindowListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::IOccupiedAreaChangeListener> occupiedAreaChangeListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::IAvoidAreaChangedListener> avoidAreaChangedListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::DisplayManager::IFoldStatusListener> foldStatusListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::DisplayManager::IDisplayModeListener> foldDisplayModeListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::DisplayManager::IAvailableAreaListener> availableAreaChangedListener_ = nullptr;

    // ITouchOutsideListener is used for touching out of hot areas of window.
    OHOS::sptr<OHOS::Rosen::ITouchOutsideListener> touchOutsideListener_ = nullptr;

    // ArkTS Form
    bool isFormRender_ = false;
    bool isFormRenderInit_ = false;
    std::string bundleName_;
    std::string moduleName_;
    std::string hapPath_;
    bool isBundle_ = false;
    float formWidth_ = 0.0;
    float formHeight_ = 0.0;
    std::string formData_;
    bool fontScaleFollowSystem_ = true;
    std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>> formImageDataMap_;
    std::unordered_map<int32_t, CustomPopupUIExtensionConfig> customPopupConfigMap_;
    std::unordered_map<int32_t, int32_t> popupUIExtensionRecords_;
    std::unique_ptr<DistributedUIManager> uiManager_;

    bool isDynamicRender_ = false;
    int32_t hostInstanceId_ = -1;
    UIContentType uIContentType_ = UIContentType::UNDEFINED;
    std::shared_ptr<TaskWrapper> taskWrapper_;
    std::vector<std::string> registerComponents_;

    sptr<IRemoteObject> parentToken_ = nullptr;
    sptr<IRemoteObject> instance_ = new (std::nothrow) UIContentServiceStubImpl();
    bool isUIExtensionSubWindow_ = false;
    bool isUIExtensionAbilityProcess_ = false;
    bool isUIExtensionAbilityHost_ = false;
    RefPtr<UpdateConfigManager<AceViewportConfig>> viewportConfigMgr_ =
        Referenced::MakeRefPtr<UpdateConfigManager<AceViewportConfig>>();
    std::unordered_map<void*, std::function<void()>> destructCallbacks_;

    SingleTaskExecutor::CancelableTask updateDecorVisibleTask_;
    std::mutex updateDecorVisibleMutex_;
    SingleTaskExecutor::CancelableTask setAppWindowIconTask_;
    std::mutex setAppWindowIconMutex_;
    uint64_t listenedDisplayId_ = 0;
    OHOS::Rosen::WindowSizeChangeReason lastReason_ = OHOS::Rosen::WindowSizeChangeReason::UNDEFINED;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_ACE_UI_CONTENT_IMPL_H
