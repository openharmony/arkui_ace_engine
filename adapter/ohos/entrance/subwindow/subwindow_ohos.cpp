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

#include "adapter/ohos/entrance/subwindow/subwindow_ohos.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
#include "adapter/ohos/entrance/ace_rosen_sync_task.h"
#endif
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/dialog_container.h"
#include "adapter/ohos/entrance/flutter_ace_view.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/log/frame_report.h"
#include "base/utils/system_properties.h"
#include "core/common/connect_server_manager.h"
#include "core/common/container_scope.h"
#include "core/common/flutter/flutter_task_executor.h"
#include "core/common/frontend.h"
#include "core/common/hdc_register.h"
#include "core/common/text_field_manager.h"
#include "core/components/bubble/bubble_component.h"
#include "core/components/popup/popup_component.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "dm/display_manager.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/declarative_frontend.h"
#include "interfaces/inner_api/ace/viewport_config.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include <atomic>

namespace OHOS::Ace {

int32_t SubwindowOhos::id_ = 0;
static std::atomic<int32_t> gToastDialogId = 0;
RefPtr<Subwindow> Subwindow::CreateSubwindow(int32_t instanceId)
{
    LOGI("Create Subwindow, parent container id is %{public}d", instanceId);
    return AceType::MakeRefPtr<SubwindowOhos>(instanceId);
}

SubwindowOhos::SubwindowOhos(int32_t instanceId) : windowId_(id_), parentContainerId_(instanceId)
{
    SetSubwindowId(windowId_);
    id_++;
}

void SubwindowOhos::InitContainer()
{
    LOGI("Subwindow start initialize container");
    if (!window_) {
        LOGI("Window is null, need create a new window");
        OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
        auto parentWindowName = Platform::AceContainer::GetContainer(parentContainerId_)->GetWindowName();
        auto parentWindowId = Platform::AceContainer::GetContainer(parentContainerId_)->GetWindowId();
        auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
        sptr<OHOS::Rosen::Window> parentWindow = OHOS::Rosen::Window::Find(parentWindowName);
        if (parentWindow == nullptr) {
            return;
        }
        auto windowType = parentWindow->GetType();
        if (windowType == Rosen::WindowType::WINDOW_TYPE_DESKTOP) {
            windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_FLOAT);
        } else {
            windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_APP_SUB_WINDOW);
            windowOption->SetParentId(parentWindowId);
        }
        windowOption->SetWindowRect({ 0, 0, defaultDisplay->GetWidth(), defaultDisplay->GetHeight() });
        windowOption->SetWindowMode(Rosen::WindowMode::WINDOW_MODE_FLOATING);
        window_ = OHOS::Rosen::Window::Create(
            "ARK_APP_SUBWINDOW_" + parentWindowName + std::to_string(windowId_), windowOption);
        if (window_ == nullptr) {
            LOGI("create window error return");
            return;
        }
    }
    std::string url = "";
    window_->SetUIContent(url, nullptr, nullptr, false);
    childContainerId_ = SubwindowManager::GetInstance()->GetContainerId(window_->GetWindowId());
    SubwindowManager::GetInstance()->AddParentContainerId(childContainerId_, parentContainerId_);
    auto parentContainer = Platform::AceContainer::GetContainer(parentContainerId_);
    if (!parentContainer) {
        LOGE("Get container failed, container is null");
        return;
    }

    auto container = Platform::AceContainer::GetContainer(childContainerId_);
    if (!container) {
        LOGE("Get container failed, container is null");
        return;
    }

    container->SetParentId(parentContainerId_);
    container->GetSettings().SetUsingSharedRuntime(true);
    container->SetSharedRuntime(parentContainer->GetSharedRuntime());
    container->Initialize();
    container->SetAssetManager(parentContainer->GetAssetManager());
    container->SetResourceConfiguration(parentContainer->GetResourceConfiguration());
    container->SetPackagePathStr(parentContainer->GetPackagePathStr());
    container->SetHapPath(parentContainer->GetHapPath());
    container->SetIsSubContainer(true);
    container->InitializeSubContainer(parentContainerId_);
    ViewportConfig config;
    // create ace_view
    auto flutterAceView =
        Platform::FlutterAceView::CreateView(childContainerId_, false, container->GetSettings().usePlatformAsUIThread);
    Platform::FlutterAceView::SurfaceCreated(flutterAceView, window_);

    int32_t width = static_cast<int32_t>(window_->GetRequestRect().width_);
    int32_t height = static_cast<int32_t>(window_->GetRequestRect().height_);
    LOGI("UIContent Initialize: width: %{public}d, height: %{public}d", width, height);

    Ace::Platform::UIEnvCallback callback = nullptr;
    // set view
    Platform::AceContainer::SetView(flutterAceView, config.Density(), width, height, window_, callback);
    Platform::FlutterAceView::SurfaceChanged(flutterAceView, width, height, config.Orientation());

#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled()) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        if (rsUiDirector != nullptr) {
            rsUiDirector->SetRSSurfaceNode(window_->GetSurfaceNode());
            rsUiDirector->SetUITaskRunner(
                [taskExecutor = container->GetTaskExecutor()](
                    const std::function<void()>& task) { taskExecutor->PostTask(task, TaskExecutor::TaskType::UI); });
            auto context = DynamicCast<PipelineContext>(container->GetPipelineContext());
            if (context != nullptr) {
                LOGI("Init RSUIDirector");
                context->SetRSUIDirector(rsUiDirector);
            }
            rsUiDirector->Init();
            LOGI("UIContent Init Rosen Backend");
        }
    }
#endif
    auto subPipelineContext =
        DynamicCast<PipelineContext>(Platform::AceContainer::GetContainer(childContainerId_)->GetPipelineContext());
    if (!subPipelineContext) {
        LOGE("Get SubPipelineContext failed, pipelineContext is null");
        return;
    }
    subPipelineContext->SetParentPipeline(parentContainer->GetPipelineContext());
    subPipelineContext->SetupSubRootElement();
}

void SubwindowOhos::ShowPopup(const RefPtr<Component>& newComponent, bool disableTouchEvent)
{
    ShowWindow();
    auto stack = GetStack();
    if (!stack) {
        LOGE("Get stack failed, it is null");
        return;
    }
    auto popup = AceType::DynamicCast<TweenComponent>(newComponent);
    if (!popup) {
        LOGE("Add menu failed, this is not a popup component.");
        return;
    }
    stack->PopPopup(popup->GetId());
    stack->PushComponent(newComponent, disableTouchEvent);
    auto bubble = AceType::DynamicCast<BubbleComponent>(popup->GetChild());
    if (bubble) {
        bubble->SetWeakStack(WeakClaim(RawPtr(stack)));
    }
}

bool SubwindowOhos::CancelPopup(const std::string& id)
{
    auto stack = GetStack();
    if (!stack) {
        return false;
    }
    stack->PopPopup(id);
    auto context = stack->GetContext().Upgrade();
    if (!context) {
        return false;
    }
    context->FlushPipelineImmediately();
    HideWindow();
    return true;
}

void SubwindowOhos::ShowWindow()
{
    LOGI("Show the subwindow");
    if (!window_) {
        LOGE("Show window failed, window is null");
        return;
    }

    OHOS::Rosen::WMError ret = window_->Show();

    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("Show window failed with errCode: %{public}d", static_cast<int32_t>(ret));
        return;
    }
    LOGI("Show the subwindow successfully.");
    SubwindowManager::GetInstance()->SetCurrentSubwindow(AceType::Claim(this));
}

void SubwindowOhos::HideWindow()
{
    LOGI("Hide the subwindow");
    if (!window_) {
        LOGE("Hide window failed, window is null");
        return;
    }

    OHOS::Rosen::WMError ret = window_->Hide();

    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("Hide window failed with errCode: %{public}d", static_cast<int32_t>(ret));
        return;
    }
    LOGI("Hide the subwindow successfully.");
}

void SubwindowOhos::AddMenu(const RefPtr<Component>& newComponent)
{
    LOGI("Subwindow push new component start.");
    auto stack = GetStack();
    if (!stack) {
        LOGE("Get stack failed, it is null");
        return;
    }
    // Push the component
    stack->PopMenu();
    stack->PushComponent(newComponent);
    popup_ = AceType::DynamicCast<SelectPopupComponent>(newComponent);
    if (!popup_) {
        LOGE("Add menu failed, this is not a popup component.");
    }
    LOGI("Subwindow push new component end.");
}

void SubwindowOhos::ClearMenu()
{
    LOGI("Subwindow Clear menu start.");
    auto stack = GetStack();
    if (!stack) {
        LOGE("Get stack failed, it is null");
        return;
    }
    // Pop the component
    stack->PopMenu();
    auto context = stack->GetContext().Upgrade();
    if (!context) {
        LOGE("Get context failed, it is null");
        return;
    }
    context->FlushPipelineImmediately();
    HideWindow();
    LOGI("Subwindow clear menu end.");
}

void SubwindowOhos::ShowMenu(const RefPtr<Component>& newComponent)
{
    LOGI("Show the menu");
    ShowWindow();
    AddMenu(newComponent);
}

void SubwindowOhos::CloseMenu()
{
    LOGI("Close the menu");
    if (popup_) {
        popup_->CloseContextMenu();
    }
}

RefPtr<StackElement> SubwindowOhos::GetStack()
{
    auto aceContainer = Platform::AceContainer::GetContainer(childContainerId_);
    if (!aceContainer) {
        LOGE("Get container failed, it is null");
        return nullptr;
    }

    auto context = DynamicCast<PipelineContext>(aceContainer->GetPipelineContext());
    if (!context) {
        LOGE("Get context failed, it is null");
        return nullptr;
    }
    return context->GetLastStack();
}

void SubwindowOhos::SetHotAreas(const std::vector<Rect>& rects)
{
    LOGI("Set hot areas for window.");
    if (!window_) {
        LOGE("Set hot areas failed, window is null");
        return;
    }

    std::vector<Rosen::Rect> hotAreas;
    Rosen::Rect rosenRect;
    for (const auto& rect : rects) {
        RectConverter(rect, rosenRect);
        hotAreas.emplace_back(rosenRect);
    }

    OHOS::Rosen::WMError ret = window_->SetTouchHotAreas(hotAreas);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("Set hot areas failed with errCode: %{public}d", static_cast<int32_t>(ret));
        return;
    }
    LOGI("Set hot areas successfully.");
}

void SubwindowOhos::RectConverter(const Rect& rect, Rosen::Rect& rosenRect)
{
    rosenRect.posX_ = static_cast<int>(rect.GetOffset().GetX());
    rosenRect.posY_ = static_cast<int>(rect.GetOffset().GetY());
    rosenRect.width_ = static_cast<uint32_t>(rect.GetSize().Width());
    rosenRect.height_ = static_cast<uint32_t>(rect.GetSize().Height());
    LOGI("Convert rect to rosenRect, x is %{public}d, y is %{public}d, width is %{public}d, height is %{public}d",
        rosenRect.posX_, rosenRect.posY_, rosenRect.width_, rosenRect.height_);
}

void SubwindowOhos::GetToastDialogWindowProperty(
    int32_t& width, int32_t& height, int32_t& posX, int32_t& posY, float& density) const
{
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
    }
    auto mainWindow = Platform::AceContainer::GetUIWindow(parentContainerId_);
    if (!mainWindow) {
        LOGE("mainWindow is nullptr");
        if (defaultDisplay) {
            posX = 0;
            posY = 0;
            width = defaultDisplay->GetWidth();
            height = defaultDisplay->GetHeight();
        }
    } else {
        posX = static_cast<int32_t>(mainWindow->GetRect().posX_);
        posY = static_cast<int32_t>(mainWindow->GetRect().posY_);
        width = static_cast<int32_t>(mainWindow->GetRect().width_);
        height = static_cast<int32_t>(mainWindow->GetRect().height_);
    }
    LOGI("Toast posX: %{public}d, posY: %{public}d, width: %{public}d, height: %{public}d, density: %{public}f",
        posX, posY, width, height, density);
}

bool SubwindowOhos::InitToastDialogWindow(int32_t width, int32_t height, int32_t posX, int32_t posY)
{
    OHOS::sptr<OHOS::Rosen::WindowOption> windowOption = new OHOS::Rosen::WindowOption();
    windowOption->SetWindowType(Rosen::WindowType::WINDOW_TYPE_APP_MAIN_WINDOW);
    windowOption->SetWindowRect({ posX, posY, width, height });
    windowOption->SetWindowMode(Rosen::WindowMode::WINDOW_MODE_FLOATING);
    int32_t dialogId = gToastDialogId.fetch_add(1, std::memory_order_relaxed);
    std::string windowName = "ARK_APP_SUBWINDOW_TOAST_DIALOG_" + std::to_string(dialogId);
    dialogWindow_ = OHOS::Rosen::Window::Create(windowName, windowOption);
    if (dialogWindow_ == nullptr) {
        LOGI("create window error return");
        return false;
    }
    LOGI("SubwindowOhos::InitToastDialogWindow end");
    return true;
}

bool SubwindowOhos::InitToastDialogView(int32_t width, int32_t height, float density)
{
    LOGI("SubwindowOhos::InitToastDialogView begin");
    dialogWindow_->SetUIContent("", nullptr, nullptr, false);
    childContainerId_ = SubwindowManager::GetInstance()->GetContainerId(dialogWindow_->GetWindowId());
    SubwindowManager::GetInstance()->AddParentContainerId(childContainerId_, parentContainerId_);

    auto container = Platform::DialogContainer::GetContainer(childContainerId_);
    if (!container) {
        LOGE("Get container failed, container is null");
        return false;
    }
    // create ace_view
    auto* flutterAceView = Platform::FlutterAceView::CreateView(childContainerId_, true, true);
    Platform::FlutterAceView::SurfaceCreated(flutterAceView, dialogWindow_);
    // set view
    Platform::DialogContainer::SetView(flutterAceView, density, width, height, dialogWindow_);
    Ace::Platform::DialogContainer::SetUIWindow(childContainerId_, dialogWindow_);
    flutter::ViewportMetrics metrics;
    metrics.physical_width = width;
    metrics.physical_height = height;
    metrics.device_pixel_ratio = density;
    Platform::FlutterAceView::SetViewportMetrics(flutterAceView, metrics);
    Platform::FlutterAceView::SurfaceChanged(flutterAceView, width, height, 0);

#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled()) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        if (rsUiDirector != nullptr) {
            rsUiDirector->SetRSSurfaceNode(dialogWindow_->GetSurfaceNode());
            rsUiDirector->SetUITaskRunner(
                [taskExecutor = container->GetTaskExecutor()](
                    const std::function<void()>& task) { taskExecutor->PostTask(task, TaskExecutor::TaskType::UI); });
            auto context = DynamicCast<PipelineContext>(container->GetPipelineContext());
            if (context != nullptr) {
                LOGI("Init RSUIDirector");
                context->SetRSUIDirector(rsUiDirector);
            }
            rsUiDirector->Init();
            LOGI("UIContent Init Rosen Backend");
        }
    }
#endif

    auto pipelineContext = DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        LOGE("Get pipelineContext failed, pipelineContext is null");
        return false;
    }
    pipelineContext->SetupRootElement();
    LOGI("SubwindowOhos::InitToastDialogView end");
    return true;
}

bool SubwindowOhos::CreateEventRunner()
{
    if (!eventLoop_) {
        eventLoop_ = AppExecFwk::EventRunner::Create("Subwindow_Toast_Dialog");
        if (eventLoop_ == nullptr) {
            return false;
        }

        handler_ = std::make_shared<AppExecFwk::EventHandler>(eventLoop_);
        if (handler_ == nullptr) {
            return false;
        }
    }
    return true;
}

void SubwindowOhos::ShowToast(const std::string& message, int32_t duration, const std::string& bottom)
{
    LOGI("SubwindowOhos::ShowToast begin");
    bool ret = CreateEventRunner();
    if (!ret) {
        return;
    }

    SubwindowManager::GetInstance()->SetCurrentSubwindow(AceType::Claim(this));
    auto showDialogCallback = [message, duration, bottom]() {
        int32_t posX = 0;
        int32_t posY = 0;
        int32_t width = 0;
        int32_t height = 0;
        float density = 1.0f;
        auto subwindowOhos = AceType::DynamicCast<SubwindowOhos>(SubwindowManager::GetInstance()->GetCurrentWindow());
        CHECK_NULL_VOID(subwindowOhos);
        subwindowOhos->GetToastDialogWindowProperty(width, height, posX, posY, density);
        auto childContainerId = subwindowOhos->GetChildContainerId();
        auto window = Platform::DialogContainer::GetUIWindow(childContainerId);
        auto dialogWindow = subwindowOhos->GetDialogWindow();
        if (!dialogWindow || !window) {
            bool ret = subwindowOhos->InitToastDialogWindow(width, height, posX, posY);
            if (!ret) {
                return;
            }
            ret = subwindowOhos->InitToastDialogView(width, height, density);
            if (!ret) {
                return;
            }
        }
        childContainerId = subwindowOhos->GetChildContainerId();
        Platform::DialogContainer::ShowToastDialogWindow(childContainerId, posX, posY, width, height, true);
        Platform::DialogContainer::ShowToast(childContainerId, message, duration, bottom);
    };
    if (!handler_->PostTask(showDialogCallback)) {
        LOGE("Post sync task error");
        return;
    }
    LOGI("SubwindowOhos::ShowToast end");
}

void SubwindowOhos::ShowDialog(const std::string& title, const std::string& message,
    const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    LOGI("SubwindowOhos::ShowDialog begin");
    bool ret = CreateEventRunner();
    if (!ret) {
        return;
    }

    SubwindowManager::GetInstance()->SetCurrentSubwindow(AceType::Claim(this));
    auto showDialogCallback = [
        title, message, &buttons, autoCancel, callbackParam = std::move(callback), &callbacks]() {
        int32_t posX = 0;
        int32_t posY = 0;
        int32_t width = 0;
        int32_t height = 0;
        float density = 1.0f;
        auto subwindowOhos = AceType::DynamicCast<SubwindowOhos>(SubwindowManager::GetInstance()->GetCurrentWindow());
        CHECK_NULL_VOID(subwindowOhos);
        subwindowOhos->GetToastDialogWindowProperty(width, height, posX, posY, density);
        bool ret = subwindowOhos->InitToastDialogWindow(width, height, posX, posY);
        if (!ret) {
            return;
        }
        ret = subwindowOhos->InitToastDialogView(width, height, density);
        if (!ret) {
            return;
        }
        auto childContainerId = subwindowOhos->GetChildContainerId();
        Platform::DialogContainer::ShowToastDialogWindow(childContainerId, posX, posY, width, height);
        Platform::DialogContainer::ShowDialog(childContainerId, title, message, buttons, autoCancel,
            std::move(const_cast<std::function<void(int32_t, int32_t)>&&>(callbackParam)), callbacks);
    };
    if (!handler_->PostTask(showDialogCallback)) {
        LOGE("Post sync task error");
        return;
    }
    LOGI("SubwindowOhos::ShowDialog end");
}

void SubwindowOhos::ShowActionMenu(const std::string& title,
    const std::vector<ButtonInfo>& button, std::function<void(int32_t, int32_t)>&& callback)
{
    LOGI("SubwindowOhos::ShowActionMenu begin");
    bool ret = CreateEventRunner();
    if (!ret) {
        return;
    }

    SubwindowManager::GetInstance()->SetCurrentSubwindow(AceType::Claim(this));
    auto showDialogCallback = [title, &button, callbackParam = std::move(callback)]() {
        int32_t posX = 0;
        int32_t posY = 0;
        int32_t width = 0;
        int32_t height = 0;
        float density = 1.0f;
        auto subwindowOhos = AceType::DynamicCast<SubwindowOhos>(SubwindowManager::GetInstance()->GetCurrentWindow());
        CHECK_NULL_VOID(subwindowOhos);
        subwindowOhos->GetToastDialogWindowProperty(width, height, posX, posY, density);
        bool ret = subwindowOhos->InitToastDialogWindow(width, height, posX, posY);
        if (!ret) {
            return;
        }
        ret = subwindowOhos->InitToastDialogView(width, height, density);
        if (!ret) {
            return;
        }
        auto childContainerId = subwindowOhos->GetChildContainerId();
        Platform::DialogContainer::ShowToastDialogWindow(childContainerId, posX, posY, width, height);
        Platform::DialogContainer::ShowActionMenu(childContainerId, title, button,
            std::move(const_cast<std::function<void(int32_t, int32_t)>&&>(callbackParam)));
    };
    if (!handler_->PostTask(showDialogCallback)) {
        LOGE("Post sync task error");
        return;
    }
    LOGI("SubwindowOhos::ShowActionMenu end");
}
} // namespace OHOS::Ace
