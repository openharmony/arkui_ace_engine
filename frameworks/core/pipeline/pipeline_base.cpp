/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/pipeline/pipeline_base.h"

#include <cinttypes>

#include "base/log/ace_tracker.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/frontend.h"
#include "core/common/manager_interface.h"
#include "core/common/thread_checker.h"
#include "core/common/window.h"
#include "core/components/custom_paint/render_custom_paint.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/image/image_provider.h"

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif

namespace OHOS::Ace {

constexpr int32_t DEFAULT_VIEW_SCALE = 1;

PipelineBase::PipelineBase(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId)
    : window_(window), taskExecutor_(std::move(taskExecutor)), assetManager_(std::move(assetManager)),
      weakFrontend_(frontend), instanceId_(instanceId)
{
    CHECK_NULL_VOID(frontend);
    frontendType_ = frontend->GetType();
    eventManager_ = AceType::MakeRefPtr<EventManager>();
    windowManager_ = AceType::MakeRefPtr<WindowManager>();
    eventManager_->SetInstanceId(instanceId);
    imageCache_ = ImageCache::Create();
    fontManager_ = FontManager::Create();
    auto&& vsyncCallback = [weak = AceType::WeakClaim(this), instanceId](
                               const uint64_t nanoTimestamp, const uint32_t frameCount) {
        ContainerScope scope(instanceId);
        auto context = weak.Upgrade();
        if (context) {
            context->OnVsyncEvent(nanoTimestamp, frameCount);
        }
    };
    ACE_DCHECK(window_);
    window_->SetVsyncCallback(vsyncCallback);
}

PipelineBase::PipelineBase(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId,
    RefPtr<PlatformResRegister> platformResRegister)
    : window_(window), taskExecutor_(std::move(taskExecutor)), assetManager_(std::move(assetManager)),
      weakFrontend_(frontend), instanceId_(instanceId), platformResRegister_(std::move(platformResRegister))
{
    CHECK_NULL_VOID(frontend);
    frontendType_ = frontend->GetType();
    eventManager_ = AceType::MakeRefPtr<EventManager>();
    windowManager_ = AceType::MakeRefPtr<WindowManager>();
    eventManager_->SetInstanceId(instanceId);
    imageCache_ = ImageCache::Create();
    fontManager_ = FontManager::Create();
    auto&& vsyncCallback = [weak = AceType::WeakClaim(this), instanceId](
                               const uint64_t nanoTimestamp, const uint32_t frameCount) {
        ContainerScope scope(instanceId);
        auto context = weak.Upgrade();
        if (context) {
            context->OnVsyncEvent(nanoTimestamp, frameCount);
        }
    };
    ACE_DCHECK(window_);
    window_->SetVsyncCallback(vsyncCallback);
}

PipelineBase::~PipelineBase()
{
    LOG_DESTROY();
}

RefPtr<PipelineBase> PipelineBase::GetCurrentContext()
{
    auto currentContainer = Container::Current();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    return currentContainer->GetPipelineContext();
}

RefPtr<ThemeManager> PipelineBase::CurrentThemeManager()
{
    auto pipelineContext = OHOS::Ace::PipelineBase::GetCurrentContext();
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
        auto pluginContainer = PluginManager::GetInstance().GetPluginSubContainer(Container::CurrentId());
        CHECK_NULL_RETURN(pluginContainer, nullptr);
        pipelineContext = pluginContainer->GetPipelineContext();
    }
#endif
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    return pipelineContext->GetThemeManager();
}

uint64_t PipelineBase::GetTimeFromExternalTimer()
{
    static const int64_t secToNanosec = 1000000000;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * secToNanosec + ts.tv_nsec);
}

void PipelineBase::RequestFrame()
{
    window_->RequestFrame();
}

RefPtr<Frontend> PipelineBase::GetFrontend() const
{
    return weakFrontend_.Upgrade();
}

void PipelineBase::ClearImageCache()
{
    if (imageCache_) {
        imageCache_->Clear();
    }
}

void PipelineBase::SetImageCache(const RefPtr<ImageCache>& imageChache)
{
    std::lock_guard<std::shared_mutex> lock(imageMtx_);
    if (imageChache) {
        imageCache_ = imageChache;
    }
}

RefPtr<ImageCache> PipelineBase::GetImageCache() const
{
    std::shared_lock<std::shared_mutex> lock(imageMtx_);
    return imageCache_;
}

void PipelineBase::SetRootSize(double density, int32_t width, int32_t height)
{
    ACE_SCOPED_TRACE("SetRootSize(%lf, %d, %d)", density, width, height);
    density_ = density;
    auto task = [weak = AceType::WeakClaim(this), density, width, height]() {
        auto context = weak.Upgrade();
        if (!context) {
            return;
        }
        context->SetRootRect(width, height);
    };
#ifdef NG_BUILD
    if (taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        task();
    } else {
        taskExecutor_->PostTask(task, TaskExecutor::TaskType::UI);
    }
#else
    taskExecutor_->PostTask(task, TaskExecutor::TaskType::UI);
#endif
}

void PipelineBase::SetFontScale(float fontScale)
{
    const static float CARD_MAX_FONT_SCALE = 1.3f;
    if (!NearEqual(fontScale_, fontScale)) {
        fontScale_ = fontScale;
        if (isJsCard_ && GreatOrEqual(fontScale_, CARD_MAX_FONT_SCALE)) {
            fontScale_ = CARD_MAX_FONT_SCALE;
        }
        fontManager_->RebuildFontNode();
    }
}

double PipelineBase::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    } else if (dimension.Unit() == DimensionUnit::LPX) {
        return (dimension.Value() * designWidthScale_);
    }
    return dimension.Value();
}

double PipelineBase::ConvertPxToVp(const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX) {
        return dimension.Value() / dipScale_;
    }
    return dimension.Value();
}

void PipelineBase::UpdateFontWeightScale()
{
    if (fontManager_) {
        fontManager_->UpdateFontWeightScale();
    }
}

void PipelineBase::SetTextFieldManager(const RefPtr<ManagerInterface>& manager)
{
    textFieldManager_ = manager;
}

void PipelineBase::RegisterFont(const std::string& familyName, const std::string& familySrc)
{
    if (fontManager_) {
        fontManager_->RegisterFont(familyName, familySrc, AceType::Claim(this));
    }
}

void PipelineBase::GetSystemFontList(std::vector<std::string>& fontList)
{
    if (fontManager_) {
        fontManager_->GetSystemFontList(fontList);
    }
}

bool PipelineBase::GetSystemFont(const std::string& fontName, FontInfo& fontInfo)
{
    if (fontManager_) {
        return fontManager_->GetSystemFont(fontName, fontInfo);
    }
    return false;
}

void PipelineBase::HyperlinkStartAbility(const std::string& address) const
{
    CHECK_RUN_ON(UI);
    if (startAbilityHandler_) {
        startAbilityHandler_(address);
    } else {
        LOGE("Hyperlink fail to start ability due to handler is nullptr");
    }
}

void PipelineBase::NotifyStatusBarBgColor(const Color& color) const
{
    CHECK_RUN_ON(UI);
    LOGD("Notify StatusBar BgColor, color: %{public}x", color.GetValue());
    if (statusBarBgColorEventHandler_) {
        statusBarBgColorEventHandler_(color);
    } else {
        LOGE("fail to finish current context due to handler is nullptr");
    }
}

void PipelineBase::NotifyPopupDismiss() const
{
    CHECK_RUN_ON(UI);
    if (popupEventHandler_) {
        popupEventHandler_();
    }
}

void PipelineBase::NotifyMenuDismiss() const
{
    CHECK_RUN_ON(UI);
    if (menuEventHandler_) {
        menuEventHandler_();
    }
}

void PipelineBase::NotifyContextMenuDismiss() const
{
    CHECK_RUN_ON(UI);
    if (contextMenuEventHandler_) {
        contextMenuEventHandler_();
    }
}

void PipelineBase::NotifyRouterBackDismiss() const
{
    CHECK_RUN_ON(UI);
    if (routerBackEventHandler_) {
        routerBackEventHandler_();
    }
}

void PipelineBase::NotifyPopPageSuccessDismiss(const std::string& pageUrl, const int32_t pageId) const
{
    CHECK_RUN_ON(UI);
    for (auto& iterPopSuccessHander : popPageSuccessEventHandler_) {
        if (iterPopSuccessHander) {
            iterPopSuccessHander(pageUrl, pageId);
        }
    }
}

void PipelineBase::NotifyIsPagePathInvalidDismiss(bool isPageInvalid) const
{
    CHECK_RUN_ON(UI);
    for (auto& iterPathInvalidHandler : isPagePathInvalidEventHandler_) {
        if (iterPathInvalidHandler) {
            iterPathInvalidHandler(isPageInvalid);
        }
    }
}

void PipelineBase::NotifyDestroyEventDismiss() const
{
    CHECK_RUN_ON(UI);
    for (auto& iterDestroyEventHander : destroyEventHandler_) {
        if (iterDestroyEventHander) {
            iterDestroyEventHander();
        }
    }
}

void PipelineBase::NotifyDispatchTouchEventDismiss(const TouchEvent& event) const
{
    CHECK_RUN_ON(UI);
    for (auto& iterDispatchTouchEventHandler : dispatchTouchEventHandler_) {
        if (iterDispatchTouchEventHandler) {
            iterDispatchTouchEventHandler(event);
        }
    }
}

void PipelineBase::OnActionEvent(const std::string& action)
{
    CHECK_RUN_ON(UI);
    if (actionEventHandler_) {
        actionEventHandler_(action);
    } else {
        LOGE("the action event handler is null");
    }
}

void PipelineBase::onRouterChange(const std::string& url)
{
    if (onRouterChangeCallback_ != nullptr) {
        onRouterChangeCallback_(url);
    }
}

void PipelineBase::TryLoadImageInfo(const std::string& src, std::function<void(bool, int32_t, int32_t)>&& loadCallback)
{
    ImageProvider::TryLoadImageInfo(AceType::Claim(this), src, std::move(loadCallback));
}

RefPtr<OffscreenCanvas> PipelineBase::CreateOffscreenCanvas(int32_t width, int32_t height)
{
    return RenderOffscreenCanvas::Create(AceType::WeakClaim(this), width, height);
}

void PipelineBase::PostAsyncEvent(TaskExecutor::Task&& task, TaskExecutor::TaskType type)
{
    if (taskExecutor_) {
        taskExecutor_->PostTask(std::move(task), type);
    } else {
        LOGE("the task executor is nullptr");
    }
}

void PipelineBase::PostAsyncEvent(const TaskExecutor::Task& task, TaskExecutor::TaskType type)
{
    if (taskExecutor_) {
        taskExecutor_->PostTask(task, type);
    } else {
        LOGE("the task executor is nullptr");
    }
}

void PipelineBase::PostSyncEvent(const TaskExecutor::Task& task, TaskExecutor::TaskType type)
{
    if (taskExecutor_) {
        taskExecutor_->PostSyncTask(task, type);
    } else {
        LOGE("the task executor is nullptr");
    }
}

void PipelineBase::UpdateRootSizeAndScale(int32_t width, int32_t height)
{
    auto frontend = weakFrontend_.Upgrade();
    CHECK_NULL_VOID(frontend);
    auto& windowConfig = frontend->GetWindowConfig();
    if (windowConfig.designWidth <= 0) {
        LOGE("the frontend design width <= 0");
        return;
    }
    if (GetIsDeclarative()) {
        viewScale_ = DEFAULT_VIEW_SCALE;
        designWidthScale_ = static_cast<double>(width) / windowConfig.designWidth;
        windowConfig.designWidthScale = designWidthScale_;
    } else {
        viewScale_ = windowConfig.autoDesignWidth ? density_ : static_cast<double>(width) / windowConfig.designWidth;
    }
    if (NearZero(viewScale_)) {
        LOGW("the view scale is zero");
        return;
    }
    dipScale_ = density_ / viewScale_;
    rootHeight_ = height / viewScale_;
    rootWidth_ = width / viewScale_;
}

void PipelineBase::DumpFrontend() const
{
    auto frontend = weakFrontend_.Upgrade();
    if (frontend) {
        frontend->DumpFrontend();
    }
}

bool PipelineBase::Dump(const std::vector<std::string>& params) const
{
    if (params.empty()) {
        LOGW("the params is empty");
        return false;
    }
    // the first param is the key word of dump.
    if (params[0] == "-memory") {
        MemoryMonitor::GetInstance().Dump();
        return true;
    }
    if (params[0] == "-jscrash") {
        EventReport::JsErrReport(
            AceApplicationInfo::GetInstance().GetPackageName(), "js crash reason", "js crash summary");
        return true;
    }
    // hiview report dump will provide three params .
    if (params[0] == "-hiviewreport" && params.size() >= 3) {
        DumpLog::GetInstance().Print("Report hiview event. EventType: " + params[1] + ", error type: " + params[2]);
        EventInfo eventInfo = { .eventType = params[1], .errorType = StringUtils::StringToInt(params[2]) };
        EventReport::SendEvent(eventInfo);
        return true;
    }
    ContainerScope scope(instanceId_);
    if (params[0] == "-frontend") {
        DumpFrontend();
        return true;
    }
    return OnDumpInfo(params);
}

void PipelineBase::ForceLayoutForImplicitAnimation()
{
    if (!pendingImplicitLayout_.empty()) {
        pendingImplicitLayout_.top() = true;
    }
}

void PipelineBase::ForceRenderForImplicitAnimation()
{
    if (!pendingImplicitRender_.empty()) {
        pendingImplicitRender_.top() = true;
    }
}

bool PipelineBase::Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& propertyCallback, const std::function<void()>& finishCallback)
{
    if (!propertyCallback) {
        LOGE("failed to create animation, property callback is null!");
        return false;
    }

    OpenImplicitAnimation(option, curve, finishCallback);
    propertyCallback();
    return CloseImplicitAnimation();
}

void PipelineBase::PrepareOpenImplicitAnimation()
{
#ifdef ENABLE_ROSEN_BACKEND
    // initialize false for implicit animation layout and render pending flag
    pendingImplicitLayout_.push(false);
    pendingImplicitRender_.push(false);

    // flush ui tasks before open implict animation
    if (!isReloading_) {
        FlushUITasks();
    }
#endif
}

void PipelineBase::PrepareCloseImplicitAnimation()
{
#ifdef ENABLE_ROSEN_BACKEND
    if (pendingImplicitLayout_.empty() && pendingImplicitRender_.empty()) {
        LOGE("close implicit animation failed, need to open implicit animation first!");
        return;
    }

    // layout or render the views immediately to animate all related views, if layout or render updates are pending in
    // the animation closure
    if (pendingImplicitLayout_.top() || pendingImplicitRender_.top()) {
        if (!isReloading_) {
            FlushUITasks();
        }
    }
    if (!pendingImplicitLayout_.empty()) {
        pendingImplicitLayout_.pop();
    }
    if (!pendingImplicitRender_.empty()) {
        pendingImplicitRender_.pop();
    }
#endif
}

void PipelineBase::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback)
{
#ifdef ENABLE_ROSEN_BACKEND
    PrepareOpenImplicitAnimation();

    auto wrapFinishCallback = [weak = AceType::WeakClaim(this), finishCallback]() {
        auto context = weak.Upgrade();
        if (!context) {
            return;
        }
        context->GetTaskExecutor()->PostTask(
            [finishCallback, weak]() {
                auto context = weak.Upgrade();
                CHECK_NULL_VOID(context);
                CHECK_NULL_VOID_NOLOG(finishCallback);
                if (context->IsFormRender()) {
                    context->SetEnableImplicitAnimation(false);
                    finishCallback();
                    context->FlushBuild();
                    context->SetEnableImplicitAnimation(true);
                    return;
                }
                finishCallback();
            },
            TaskExecutor::TaskType::UI);
    };
    AnimationUtils::OpenImplicitAnimation(option, curve, wrapFinishCallback);
#endif
}

bool PipelineBase::CloseImplicitAnimation()
{
#ifdef ENABLE_ROSEN_BACKEND
    PrepareCloseImplicitAnimation();
    return AnimationUtils::CloseImplicitAnimation();
#else
    return false;
#endif
}

void PipelineBase::OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount)
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("OnVsyncEvent now:%" PRIu64 "", nanoTimestamp);

    for (auto& callback : subWindowVsyncCallbacks_) {
        callback.second(nanoTimestamp, frameCount);
    }

    if (onVsyncProfiler_) {
        AceTracker::Start();
    }

    if (gsVsyncCallback_) {
        gsVsyncCallback_();
    }

    FlushVsync(nanoTimestamp, frameCount);
    if (onVsyncProfiler_) {
        onVsyncProfiler_(AceTracker::Stop());
    }
}

void PipelineBase::SetTouchPipeline(const WeakPtr<PipelineBase>& context)
{
    auto result = std::find(touchPluginPipelineContext_.begin(), touchPluginPipelineContext_.end(), context);
    if (result == touchPluginPipelineContext_.end()) {
        touchPluginPipelineContext_.emplace_back(context);
    }
}

void PipelineBase::RemoveTouchPipeline(const WeakPtr<PipelineBase>& context)
{
    auto result = std::find(touchPluginPipelineContext_.begin(), touchPluginPipelineContext_.end(), context);
    if (result != touchPluginPipelineContext_.end()) {
        touchPluginPipelineContext_.erase(result);
    }
}

void PipelineBase::OnVirtualKeyboardAreaChange(
    Rect keyboardArea, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    auto currentContainer = Container::Current();
    if (!currentContainer->IsSubContainer()) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(currentContainer->GetInstanceId());
        if (subwindow && subwindow->GetShown()) {
            // subwindow is shown, main window no need to handle the keyboard event
            return;
        }
    }
    double keyboardHeight = keyboardArea.Height();
    if (windowManager_ && windowManager_->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        keyboardHeight = ModifyKeyboardHeight(keyboardHeight);
    }
    if (NotifyVirtualKeyBoard(rootWidth_, rootHeight_, keyboardHeight)) {
        return;
    }
    OnVirtualKeyboardHeightChange(keyboardHeight, rsTransaction);
}

double PipelineBase::ModifyKeyboardHeight(double keyboardHeight) const
{
    auto windowRect = GetCurrentWindowRect();
    auto deviceHeight = SystemProperties::GetDeviceHeight();
    return keyboardHeight - (deviceHeight - windowRect.Bottom()) > 0.0
               ? keyboardHeight - (deviceHeight - windowRect.Bottom())
               : 0.0;
}

void PipelineBase::SetGetWindowRectImpl(std::function<Rect()>&& callback)
{
    if (window_) {
        window_->SetGetWindowRectImpl(std::move(callback));
    }
}

Rect PipelineBase::GetCurrentWindowRect() const
{
    if (window_) {
        return window_->GetCurrentWindowRect();
    }
    return {};
}

RefPtr<AccessibilityManager> PipelineBase::GetAccessibilityManager() const
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("frontend is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return nullptr;
    }
    return frontend->GetAccessibilityManager();
}

void PipelineBase::SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager || !AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        return;
    }
    accessibilityManager->SendAccessibilityAsyncEvent(accessibilityEvent);
}

void PipelineBase::SetSubWindowVsyncCallback(AceVsyncCallback&& callback, int32_t subWindowId)
{
    if (callback) {
        subWindowVsyncCallbacks_.try_emplace(subWindowId, std::move(callback));
    }
}

void PipelineBase::AddEtsCardTouchEventCallback(int32_t pointId, EtsCardTouchEventCallback&& callback)
{
    if (!callback || pointId < 0) {
        return;
    }

    etsCardTouchEventCallback_[pointId] = std::move(callback);
}

void PipelineBase::HandleEtsCardTouchEvent(const TouchEvent& point)
{
    if (point.id < 0) {
        return;
    }

    auto iter = etsCardTouchEventCallback_.find(point.id);
    if (iter == etsCardTouchEventCallback_.end()) {
        return;
    }

    if (iter->second) {
        iter->second(point);
    }
}

void PipelineBase::RemoveEtsCardTouchEventCallback(int32_t pointId)
{
    if (pointId < 0) {
        return;
    }

    auto iter = etsCardTouchEventCallback_.find(pointId);
    if (iter == etsCardTouchEventCallback_.end()) {
        return;
    }

    etsCardTouchEventCallback_.erase(iter);
}

void PipelineBase::RemoveSubWindowVsyncCallback(int32_t subWindowId)
{
    subWindowVsyncCallbacks_.erase(subWindowId);
}

void PipelineBase::Destroy()
{
    CHECK_RUN_ON(UI);
    LOGI("PipelineBase::Destroy begin.");
    ClearImageCache();
    platformResRegister_.Reset();
    drawDelegate_.reset();
    eventManager_->ClearResults();
    {
        std::unique_lock<std::shared_mutex> lock(imageMtx_);
        imageCache_.Reset();
    }
    {
        std::unique_lock<std::shared_mutex> lock(themeMtx_);
        themeManager_.Reset();
    }
    fontManager_.Reset();
    window_->Destroy();
    touchPluginPipelineContext_.clear();
    virtualKeyBoardCallback_.clear();
    etsCardTouchEventCallback_.clear();
    LOGI("PipelineBase::Destroy end.");
}
} // namespace OHOS::Ace
