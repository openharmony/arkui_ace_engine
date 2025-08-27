/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_UI_CONTENT_IMPL_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_UI_CONTENT_IMPL_H

#include "interfaces/inner_api/ace/ui_content.h"
#include "interfaces/inner_api/ace/viewport_config.h"
#include "previewer/include/window.h"

#include "adapter/preview/entrance/ace_run_args.h"
#include "adapter/preview/external/ability/context.h"
#include "adapter/preview/external/ability/fa/fa_context.h"
#include "adapter/preview/external/ability/stage/stage_context.h"
#include "frameworks/core/common/window_animation_config.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UIContentImpl : public UIContent {
public:
    UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime);
    UIContentImpl(OHOS::AppExecFwk::Ability* ability);
    UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime, bool isCard);
    ~UIContentImpl()
    {
        DestroyUIDirector();
        DestroyCallback();
    }

    // UI content lifeCycles
    UIContentErrorCode Initialize(OHOS::Rosen::Window* window, const std::string& url, napi_value storage) override;
    UIContentErrorCode Initialize(OHOS::Rosen::Window* window,
        const std::shared_ptr<std::vector<uint8_t>>& content, napi_value storage) override {
        return UIContentErrorCode::NO_ERRORS;
    }
    UIContentErrorCode InitializeByName(OHOS::Rosen::Window *window, const std::string &name,
        napi_value storage) override;
    void InitializeDynamic(const DynamicInitialConfig& config) override {}
    void Initialize(
        OHOS::Rosen::Window* window, const std::string& url, napi_value storage, uint32_t focusWindowId) override {}
    void Foreground() override {}
    void Background() override {}
    void Focus() override {}
    void UnFocus() override {}
    void Destroy() override;
    void OnNewWant(const OHOS::AAFwk::Want& want) override {}

    // restore
    UIContentErrorCode Restore(OHOS::Rosen::Window* window, const std::string& contentInfo,
        napi_value storage, ContentInfoType type) override {
        return UIContentErrorCode::NO_ERRORS;
    }
    std::string GetContentInfo(ContentInfoType type) const override;
    void DestroyUIDirector() override;

    void OnConfigurationChanged(const DeviceConfig& newConfig);
    void SurfaceChanged(
        const DeviceOrientation& orientation, const double& resolution, int32_t& width, int32_t& height,
        WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED);
    void LoadDocument(const std::string& url, const std::string& componentName,
        Platform::SystemParams& systemParams) override;
    std::string GetJSONTree() override;
    bool OperateComponent(const std::string& attrsJson) override;
    // UI content event process
    bool ProcessBackPressed() override;
    bool ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) override;
    bool ProcessPointerEventWithCallback(
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void()>& callback) override;
    bool ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme) override;
    bool ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) override;
    bool ProcessVsyncEvent(uint64_t timeStampNanos) override;
    void SetIsFocusActive(bool isFocusActive) override {}
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) override;
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config,
        const std::shared_ptr<Global::Resource::ResourceManager>& resourceManager) override;
    void UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr,
        const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas = {},
        const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info = nullptr) override;
    void UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDeco = true) override {}
    void UpdateDecorVisible(bool visible, bool hasDeco = true) override {};
    void HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) override {}
    void SetIgnoreViewSafeArea(bool ignoreViewSafeArea) override {}
    void UpdateTitleInTargetPos(bool isShow, int32_t height) override {}

    // Window color
    uint32_t GetBackgroundColor() override;
    void SetBackgroundColor(uint32_t color) override;
    void SetWindowContainerColor(uint32_t activeColor, uint32_t inactiveColor) override;

    void DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override;

    // Set UIContent callback for custom window animation
    void SetNextFrameLayoutCallback(std::function<void()>&& callback) override;

    // Receive memory level notification
    void NotifyMemoryLevel(int32_t level) override;

    void SetAppWindowTitle(const std::string& title) override {}
    void SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap) override {}
    void SetActionEventHandler(std::function<void(const std::string& action)>&& actionCallback) override {}
    void SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback) override {}
    void SetFormLinkInfoUpdateHandler(std::function<void(const std::vector<std::string>&)>&& callback) override {}

    // ArkTS Form
    void PreInitializeForm(OHOS::Rosen::Window* window, const std::string& url, napi_value storage) override {}
    void RunFormPage() override {}
    void OnFormSurfaceChange(float width, float height,
        OHOS::Rosen::WindowSizeChangeReason type = static_cast<OHOS::Rosen::WindowSizeChangeReason>(0),
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr) override {}
    void UpdateFormData(const std::string& data) override {}
    void UpdateFormSharedImage(const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap) override
    {}
    void SetFormWidth(float width) override {}
    void SetFormHeight(float height) override {}
    float GetFormWidth() override
    {
        return 0.0;
    }
    float GetFormHeight() override
    {
        return 0.0;
    }
    std::shared_ptr<Rosen::RSSurfaceNode> GetFormRootNode() override
    {
        return nullptr;
    }

    int32_t CreateModalUIExtension(const AAFwk::Want& want,
        const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config) override;
    void CloseModalUIExtension(int32_t sessionId) override;

    void SetParentToken(sptr<IRemoteObject> token) override {}
    sptr<IRemoteObject> GetParentToken() override
    {
        return nullptr;
    }

    SerializedGesture GetFormSerializedGesture() override
    {
        return SerializedGesture();
    }

    void UpdateTransform(const OHOS::Rosen::Transform& transform) override {};

    void SetContentNodeGrayScale(float grayscale) override {};

    void PreLayout() override {};

    void SetStatusBarItemColor(uint32_t color) override;

    void SetForceSplitEnable(bool isForceSplit, const std::string& homePage,
        bool isRouter = true, bool ignoreOrientation = false) override {}

    void EnableContainerModalGesture(bool isEnable) override {};

    bool GetContainerFloatingTitleVisible() override
    {
        return false;
    }

    bool GetContainerCustomTitleVisible() override
    {
        return false;
    }

    bool GetContainerControlButtonVisible() override
    {
        return false;
    }

    void UpdateSingleHandTransform(const OHOS::Rosen::SingleHandTransform& transform) override {};
private:
    UIContentErrorCode InitializeInner(
        OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, bool isNamedRouter);
    UIContentErrorCode CommonInitialize(OHOS::Rosen::Window* window, const std::string& contentInfo,
        napi_value storage);
    void DestroyCallback() const;

private:
    int32_t instanceId_ = -1;
    void* runtime_ = nullptr;
    // All parameters that need to be passed.
    std::string startUrl_;
    std::string assetPath_;
    std::string systemResourcesPath_;
    std::string appResourcesPath_;
    std::string containerSdkPath_;
    std::string language_;
    std::string region_;
    std::string script_;
    uint32_t themeId_ = 0;
    int32_t deviceWidth_ = 0;
    int32_t deviceHeight_ = 0;
    bool isRound_ = false;
    Platform::SendCurrentRouterCallback onRouterChange_;
    DeviceConfig deviceConfig_;
    Platform::AceRunArgs runArgs_;
    Platform::ConfigChanges configChanges_;

    std::string bundleName_;
    std::string moduleName_;
    std::string compileMode_;
    std::string pageProfile_;
    int32_t compatibleVersion_ = 0;
    int32_t targetVersion_ = 0;
    bool installationFree_ = false;
    bool isComponentMode_ = false;
    uint32_t labelId_ = 0;
    bool useNewPipeline_ = true;
    std::weak_ptr<OHOS::AbilityRuntime::Context> context_;

    sptr<OHOS::Rosen::Window> rsWindow_;
    // ITouchOutsideListener is used for touching out of hot areas of window.
    OHOS::sptr<OHOS::Rosen::ITouchOutsideListener> touchOutsideListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::IWindowDragListener> dragWindowListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::IAvoidAreaChangedListener> avoidAreaChangedListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::IIgnoreViewSafeAreaListener> ignoreViewSafeAreaListener_ = nullptr;
    // ArkTS Form
    bool isFormRender_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_UI_CONTENT_IMPL_H
