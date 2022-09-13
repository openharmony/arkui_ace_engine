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

#include "core/pipeline/pipeline_base.h"

#include <fstream>

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/font_manager.h"
#include "core/common/frontend.h"
#include "core/common/manager_interface.h"
#include "core/common/thread_checker.h"
#include "core/common/window.h"
#include "core/components/custom_paint/render_custom_paint.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/image/image_provider.h"

namespace OHOS::Ace {

constexpr int32_t DEFAULT_VIEW_SCALE = 1;

PipelineBase::PipelineBase(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId)
    : window_(std::move(window)), taskExecutor_(std::move(taskExecutor)), assetManager_(std::move(assetManager)),
      weakFrontend_(frontend), instanceId_(instanceId)
{
    eventManager_ = AceType::MakeRefPtr<EventManager>();
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

RefPtr<ImageCache> PipelineBase::GetImageCache() const
{
    return imageCache_;
}

void PipelineBase::SetRootSize(double density, int32_t width, int32_t height)
{
    ACE_SCOPED_TRACE("SetRootSize(%lf, %d, %d)", density, width, height);

    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), density, width, height]() {
            auto context = weak.Upgrade();
            if (!context) {
                return;
            }
            context->density_ = density;
            context->SetRootRect(width, height);
        },
        TaskExecutor::TaskType::UI);
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
    for (auto& iterDispatchTouchEventHander : dispatchTouchEventHandler_) {
        if (iterDispatchTouchEventHander) {
            iterDispatchTouchEventHander(event);
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

void PipelineBase::DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info) const
{
    auto result = false;
    if (!SystemProperties::GetDebugEnabled()) {
        std::unique_ptr<std::ostream> ss = std::make_unique<std::ostringstream>();
        DumpLog::GetInstance().SetDumpFile(std::move(ss));
        result = Dump(params);
        const auto& infoFile = DumpLog::GetInstance().GetDumpFile();
        auto* ostringstream = static_cast<std::ostringstream*>(infoFile.get());
        info.emplace_back(ostringstream->str().substr(0, DumpLog::MAX_DUMP_LENGTH));
        DumpLog::GetInstance().Reset();
    } else {
        auto dumpFilePath = AceApplicationInfo::GetInstance().GetDataFileDirPath() + "/arkui.dump";
        std::unique_ptr<std::ostream> ss = std::make_unique<std::ofstream>(dumpFilePath);
        DumpLog::GetInstance().SetDumpFile(std::move(ss));
        result = Dump(params);
        info.emplace_back("dumpFilePath: " + dumpFilePath);
        DumpLog::GetInstance().Reset();
    }
    if (!result) {
        DumpLog::ShowDumpHelp(info);
    }
}

bool PipelineBase::Dump(const std::vector<std::string>& params) const
{
    if (params.empty()) {
        LOGW("the params is empty");
        return false;
    }
    // the first param is the key word of dump.
#ifdef ACE_MEMORY_MONITOR
    if (params[0] == "-memory") {
        MemoryMonitor::GetInstance().Dump();
        return true;
    }
#endif
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
    return OnDumpInfo(params);
}

void PipelineBase::ForceLayoutForImplicitAnimation()
{
    if (!pendingImplicitLayout_.empty()) {
        pendingImplicitLayout_.top() = true;
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
    if (!SystemProperties::GetRosenBackendEnabled()) {
        LOGE("rosen backend is disabled");
        return;
    }

    // initialize false for implicit animation layout pending flag
    pendingImplicitLayout_.push(false);
    FlushUITasks();
#endif
}

void PipelineBase::PrepareCloseImplicitAnimation()
{
#ifdef ENABLE_ROSEN_BACKEND
    if (!SystemProperties::GetRosenBackendEnabled()) {
        LOGE("rosen backend is disabled!");
        return;
    }

    if (pendingImplicitLayout_.empty()) {
        LOGE("close implicit animation failed, need to open implicit animation first!");
        return;
    }

    // layout the views immediately to animate all related views, if layout updates are pending in the animation closure
    if (pendingImplicitLayout_.top()) {
        FlushUITasks();
    }
    pendingImplicitLayout_.pop();
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
            [finishCallback]() {
                if (finishCallback) {
                    finishCallback();
                }
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

} // namespace OHOS::Ace
