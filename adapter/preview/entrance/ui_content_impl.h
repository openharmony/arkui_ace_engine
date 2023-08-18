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
#include "native_engine/native_engine.h"
#include "native_engine/native_value.h"
#include "previewer/include/window.h"

#include "adapter/preview/entrance/ace_run_args.h"
#include "adapter/preview/external/ability/context.h"
#include "adapter/preview/external/ability/fa/fa_context.h"
#include "adapter/preview/external/ability/stage/stage_context.h"

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
    void Initialize(OHOS::Rosen::Window* window, const std::string& url, NativeValue* storage) override;
    void Initialize(
        OHOS::Rosen::Window* window, const std::string& url, NativeValue* storage, uint32_t focusWindowId) override {}
    void Foreground() override {}
    void Background() override {}
    void Focus() override {}
    void UnFocus() override {}
    void Destroy() override;
    void OnNewWant(const OHOS::AAFwk::Want& want) override {}

    // distribute
    void Restore(OHOS::Rosen::Window* window, const std::string& contentInfo, NativeValue* storage) override {}
    std::string GetContentInfo() const override;
    void DestroyUIDirector() override;

    // UI content event process
    bool ProcessBackPressed() override;
    bool ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) override;
    bool ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent) override;
    bool ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) override;
    bool ProcessVsyncEvent(uint64_t timeStampNanos) override;
    void SetIsFocusActive(bool isFocusActive) override {}
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) override;
    void UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr) override;
    void UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDeco = true) override {}
    void HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize) override {}
    void SetIgnoreViewSafeArea(bool ignoreViewSafeArea) override {}

    // Window color
    uint32_t GetBackgroundColor() override;
    void SetBackgroundColor(uint32_t color) override;

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
    void OnFormSurfaceChange(float width, float height) override {}
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

    int32_t CreateModalUIExtension(const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks) override;
    void CloseModalUIExtension(int32_t sessionId) override;

private:
    void CommonInitialize(OHOS::Rosen::Window* window, const std::string& contentInfo, NativeValue* storage);
    void DestroyCallback() const;

private:
    int32_t instanceId_ = -1;
    void* runtime_ = nullptr;
    // All parameters that need to be passed.
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

    std::string bundleName_;
    std::string moduleName_;
    std::string compileMode_;
    std::string pageProfile_;
    int32_t compatibleVersion_ = 0;
    bool installationFree_ = false;
    uint32_t labelId_ = 0;
    bool useNewPipeline_ = true;

    sptr<OHOS::Rosen::Window> rsWindow_;
    // ITouchOutsideListener is used for touching out of hot areas of window.
    OHOS::sptr<OHOS::Rosen::ITouchOutsideListener> touchOutsideListener_ = nullptr;
    OHOS::sptr<OHOS::Rosen::IWindowDragListener> dragWindowListener_ = nullptr;
    // ArkTS Form
    bool isFormRender_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_UI_CONTENT_IMPL_H
