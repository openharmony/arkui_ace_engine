/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ui_dialog_impl.h"

#include "axis_event.h"
#include "dialog_callback_proxy.h"
#include "init_data.h"
#include "key_event.h"
#include "locale_config.h"
#include "pointer_event.h"
#include "res_config.h"
#include "runtime.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/flutter_ace_view.h"
#include "base/log/log.h"
#include "core/components/theme/app_theme.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

namespace OHOS::Ace {
extern "C" ACE_EXPORT void* OHOS_ACE_CreateDialog()
{
    return new UIDialogImpl();
}

class UIMgrServiceWindowChangeListener : public Rosen::IWindowChangeListener {
public:
    explicit UIMgrServiceWindowChangeListener(WeakPtr<Platform::AceContainer> container)
    {
        container_ = container;
    }
    void OnSizeChange(OHOS::Rosen::Rect rect, OHOS::Rosen::WindowSizeChangeReason reason) override
    {
        LOGI("UIMgrServiceWindowChangeListener size change");
        auto container = container_.Upgrade();
        if (container) {
            container->SetWindowPos(rect.posX_, rect.posY_);
            auto taskExecutor = container->GetTaskExecutor();
            if (!taskExecutor) {
                LOGE("OnSizeChange: taskExecutor is null.");
                return;
            }
            taskExecutor->PostTask(
                [rect, reason, container]() {
                    auto flutterAceView = static_cast<Platform::FlutterAceView*>(container->GetView());
                    if (!flutterAceView) {
                        LOGE("OnSizeChange: flutterAceView is null.");
                        return;
                    }
                    Platform::FlutterAceView::SurfaceChanged(flutterAceView, rect.width_, rect.height_,
                        rect.height_ >= rect.width_ ? 0 : 1, static_cast<WindowSizeChangeReason>(reason));
                },
                TaskExecutor::TaskType::PLATFORM);
        }
    }
    void OnModeChange(OHOS::Rosen::WindowMode mode) override
    {
        LOGI("UIMgrServiceWindowChangeListener mode change");
    }

private:
    WeakPtr<Platform::AceContainer> container_;
};

class UIMgrServiceInputEventConsumer : public Rosen::IInputEventConsumer {
public:
    explicit UIMgrServiceInputEventConsumer(Ace::Platform::FlutterAceView* flutterAceView)
    {
        flutterAceView_ = flutterAceView;
    }
    ~UIMgrServiceInputEventConsumer() override = default;

    bool OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const override
    {
        if (flutterAceView_ != nullptr) {
            flutterAceView_->DispatchTouchEvent(flutterAceView_, pointerEvent);
            return true;
        }
        return false;
    }

    bool OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const override
    {
        // do nothing
        return false;
    }

    bool OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const override
    {
        // do nothing
        return false;
    }

private:
    Ace::Platform::FlutterAceView* flutterAceView_ = nullptr;
};

static void SetDialogBackgroundColor(const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context)
{
    auto themeManager = context->GetThemeManager();
    if (themeManager) {
        auto appTheme = themeManager->GetTheme<AppTheme>();
        if (appTheme) {
            LOGI("set bg color TRANSPARENT");
            appTheme->SetBackgroundColor(Color::TRANSPARENT);
        }
    }
}

std::shared_ptr<OHOS::AppExecFwk::Ability> UIDialogImpl::CreateAbility()
{
    auto ability = OHOS::AppExecFwk::Ability::Create(nullptr);
    if (ability == nullptr) {
        LOGE("create ability failed");
        return nullptr;
    }

    auto deal = std::make_shared<OHOS::AppExecFwk::ContextDeal>();
    if (deal == nullptr) {
        LOGE("create deal failed");
        delete ability;
        return nullptr;
    }

    deal->initResourceManager(resourceManager_);
    ability->AttachBaseContext(deal);
    std::shared_ptr<OHOS::AppExecFwk::Ability> sharedAbility(ability);
    return sharedAbility;
}

void UIDialogImpl::InitResourceManager()
{
    std::shared_ptr<Global::Resource::ResourceManager> resourceManager(Global::Resource::CreateResourceManager());
    if (resourceManager == nullptr) {
        LOGE("InitResourceManager create resourceManager failed");
        return;
    }

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    UErrorCode status = U_ZERO_ERROR;
    icu::Locale locale = icu::Locale::forLanguageTag(Global::I18n::LocaleConfig::GetSystemLanguage(), status);
    resConfig->SetLocaleInfo(locale);
    if (resConfig->GetLocaleInfo() != nullptr) {
        LOGD("InitResourceManager language: %{public}s, script: %{public}s, region: %{public}s,",
            resConfig->GetLocaleInfo()->getLanguage(), resConfig->GetLocaleInfo()->getScript(),
            resConfig->GetLocaleInfo()->getCountry());
    } else {
        LOGE("InitResourceManager language: GetLocaleInfo is null.");
    }
    resourceManager->UpdateResConfig(*resConfig);
    resourceManager_ = resourceManager;
}

void UIDialogImpl::ShowDialog(const std::string& name, const std::string& params, uint32_t windowType, int x, int y,
    int width, int height, const std::function<void(int32_t, const std::string&, const std::string&)>& dialogCallback,
    int32_t dialogId)
{
    LOGI("UIDialogImpl Show dialog start %{public}d", dialogId);

    SetHwIcuDirectory();
    InitResourceManager();

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    if (resourceManager_ != nullptr) {
        resourceManager_->GetResConfig(*resConfig);
        auto localeInfo = resConfig->GetLocaleInfo();
        Ace::Platform::AceApplicationInfoImpl::GetInstance().SetResourceManager(resourceManager_);
        if (localeInfo != nullptr) {
            auto language = localeInfo->getLanguage();
            auto region = localeInfo->getCountry();
            auto script = localeInfo->getScript();
            Ace::AceApplicationInfo::GetInstance().SetLocale((language == nullptr) ? "" : language,
                (region == nullptr) ? "" : region, (script == nullptr) ? "" : script, "");
        }
    }

    std::string resPath;
    // create container
    auto ability = CreateAbility();
    Ace::Platform::AceContainer::CreateContainer(
        dialogId, Ace::FrontendType::JS, false, "", ability, nullptr, true);
    abilityMaps_[dialogId] = ability;
    auto container = Ace::Platform::AceContainer::GetContainer(dialogId);
    if (!container) {
        LOGE("container is null, set configuration failed.");
        return;
    }
    auto aceResCfg = container->GetResourceConfiguration();
    aceResCfg.SetOrientation(Ace::SystemProperties::GetDeviceOrientation());
    aceResCfg.SetDensity(Ace::SystemProperties::GetResolution());
    aceResCfg.SetDeviceType(Ace::SystemProperties::GetDeviceType());
    container->SetResourceConfiguration(aceResCfg);
    container->SetPackagePathStr(resPath);

    Ace::Platform::AceContainer::SetDialogCallback(
        dialogId, [callback = dialogCallback, id = dialogId](const std::string& event, const std::string& params) {
            LOGI("Dialog callback from ace container");
            callback(id, event, params);
        });

    // create view.
    auto flutterAceView = Ace::Platform::FlutterAceView::CreateView(dialogId, true);

    sptr<OHOS::Rosen::WindowOption> option = new OHOS::Rosen::WindowOption();
    LOGI("Show dialog: windowConfig: x: %{public}d, y: %{public}d, width: %{public}d, height: %{public}d", x, y, width,
        height);
    option->SetWindowRect({ x, y, width, height });
    option->SetWindowType(static_cast<OHOS::Rosen::WindowType>(windowType));
    option->SetMainHandlerAvailable(false);
    std::string windowName = "system_dialog_window";
    windowName += std::to_string(dialogId);
    auto dialogWindow = OHOS::Rosen::Window::Create(windowName, option);
    if (dialogWindow == nullptr) {
        LOGE("Create window failed");
        return;
    }

    // register surface change callback
    OHOS::sptr<OHOS::Rosen::IWindowChangeListener> listener =
        new UIMgrServiceWindowChangeListener(AceType::WeakClaim(AceType::RawPtr(container)));
    dialogWindow->RegisterWindowChangeListener(listener);

    std::shared_ptr<Rosen::IInputEventConsumer> inputEventListener =
        std::make_shared<UIMgrServiceInputEventConsumer>(flutterAceView);
    dialogWindow->SetInputEventConsumer(inputEventListener);

    Ace::Platform::FlutterAceView::SurfaceCreated(flutterAceView, dialogWindow);

    // set metrics
    flutter::ViewportMetrics metrics;
    metrics.physical_width = width;
    metrics.physical_height = height;
    metrics.device_pixel_ratio = density_;
    Ace::Platform::FlutterAceView::SetViewportMetrics(flutterAceView, metrics);

    std::string packagePathStr = "/system/etc/SADialog/";
    std::vector<std::string> assetBasePathStr = { name + "/" };
    Ace::Platform::AceContainer::AddAssetPath(dialogId, packagePathStr, assetBasePathStr);

    Ace::Platform::UIEnvCallback callback = nullptr;
    callback =
#ifdef ENABLE_ROSEN_BACKEND
        [dialogWindow, listener, dialogId](const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context) mutable {
            if (SystemProperties::GetRosenBackendEnabled()) {
                auto rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
                if (rsUiDirector != nullptr) {
                    rsUiDirector->SetRSSurfaceNode(dialogWindow->GetSurfaceNode());
                    dialogWindow->RegisterWindowChangeListener(listener);

                    rsUiDirector->SetUITaskRunner(
                        [taskExecutor = Ace::Platform::AceContainer::GetContainer(dialogId)->GetTaskExecutor()](
                            const std::function<void()>& task) {
                            taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
                        });
                    if (context != nullptr) {
                        context->SetRSUIDirector(rsUiDirector);
                    }
                    rsUiDirector->Init();
                    LOGI("Init Rosen Backend");
                }
            } else {
                LOGI("not Init Rosen Backend");
            }
            SetDialogBackgroundColor(context);
        };
#else
        [](const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context) { SetDialogBackgroundColor(context); }
#endif

    // set view
    Ace::Platform::AceContainer::SetView(
        flutterAceView, density_, width, height, dialogWindow, callback);
    Ace::Platform::AceContainer::SetUIWindow(dialogId, dialogWindow);
    Ace::Platform::FlutterAceView::SurfaceChanged(flutterAceView, width, height, 0);
    container->SetWindowPos(x, y);

    // run page.
    Ace::Platform::AceContainer::RunPage(
        dialogId, Ace::Platform::AceContainer::GetContainer(dialogId)->GeneratePageId(), "", params);

    dialogWindow->Show();
    dialogWindow->MoveTo(x, y);
    dialogWindow->Resize(width, height);

    LOGI("Show dialog in service end");
}

void UIDialogImpl::CancelDialog(int32_t id, const std::function<void()>& destroyCallback)
{
    LOGI("UIDialogImpl Cancel dialog id: %{public}d", id);
    int ret = abilityMaps_.erase(id);
    if (ret == 0) {
        LOGE("Cancel dialog failed: no such dialog(%{public}d)", id);
        return;
    }
    auto container = Platform::AceContainer::GetContainer(id);
    if (!container) {
        LOGE("Container(%{public}d) not found.", id);
        return;
    }
    auto dialogWindow = Platform::AceContainer::GetUIWindow(id);
    if (dialogWindow) {
        dialogWindow->Destroy();
    }
#ifdef ENABLE_ROSEN_BACKEND
    auto taskExecutor = Platform::AceContainer::GetContainer(id)->GetTaskExecutor();
    taskExecutor->PostTask(
        [id]() {
            if (auto context = AceType::DynamicCast<PipelineContext>(
                    Ace::Platform::AceContainer::GetContainer(id)->GetPipelineContext())) {
                context->SetRSUIDirector(nullptr);
            }
        },
        TaskExecutor::TaskType::UI);
#endif
    Platform::AceContainer::DestroyContainer(id, destroyCallback);
}

void UIDialogImpl::UpdateDialog(int id, const std::string& data)
{
    LOGI("UIDialogImpl Update dialog id: %{public}d", id);
    auto container = Platform::AceContainer::GetContainer(id);
    if (!container) {
        LOGE("Container(%{public}d) not found.", id);
        return;
    }
    Platform::AceContainer::OnDialogUpdated(id, data);
}
} // namespace OHOS::Ace
