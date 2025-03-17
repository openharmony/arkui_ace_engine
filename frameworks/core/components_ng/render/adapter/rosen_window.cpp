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

#include "core/components_ng/render/adapter/rosen_window.h"

#include "base/log/ace_performance_monitor.h"
#include "base/log/event_report.h"
#include "base/log/frame_report.h"
#include "base/log/jank_frame_report.h"
#include "core/common/container.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
constexpr int32_t IDLE_TASK_DELAY_MILLISECOND = 51;
constexpr float ONE_SECOND_IN_NANO = 1000000000.0f;
#ifdef VSYNC_TIMEOUT_CHECK
constexpr int32_t VSYNC_TASK_DELAY_MILLISECOND = 3000;
#endif

#ifdef PREVIEW
constexpr float PREVIEW_REFRESH_RATE = 30.0f;
#endif
} // namespace

namespace OHOS::Ace::NG {

RosenWindow::RosenWindow(const OHOS::sptr<OHOS::Rosen::Window>& window, RefPtr<TaskExecutor> taskExecutor, int32_t id)
    : rsWindow_(window), taskExecutor_(taskExecutor), id_(id)
{
    vsyncCallback_ = std::make_shared<OHOS::Rosen::VsyncCallback>();
    vsyncCallback_->onCallback = [weakTask = taskExecutor_, id = id_](int64_t timeStampNanos, int64_t frameCount) {
        auto taskExecutor = weakTask.Upgrade();
        auto onVsync = [id, timeStampNanos, frameCount] {
            int64_t ts = GetSysTimestamp();
            ArkUIPerfMonitor::GetPerfMonitor(id)->StartPerf();
            if (FrameReport::GetInstance().GetEnable()) {
                FrameReport::GetInstance().FlushBegin();
            }
            ContainerScope scope(id);
            // use container to get window can make sure the window is valid
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto window = container->GetWindow();
            CHECK_NULL_VOID(window);
            int64_t refreshPeriod = window->GetVSyncPeriod();
            window->OnVsync(static_cast<uint64_t>(timeStampNanos), static_cast<uint64_t>(frameCount));
            ArkUIPerfMonitor::GetPerfMonitor(id)->FinishPerf();
            auto pipeline = container->GetPipelineContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->OnIdle(std::min(ts, timeStampNanos) + refreshPeriod);
            JankFrameReport::GetInstance().JankFrameRecord(timeStampNanos, window->GetWindowName());
            if (FrameReport::GetInstance().GetEnable()) {
                FrameReport::GetInstance().FlushEnd();
            }
            window->SetLastVsyncEndTimestamp(GetSysTimestamp());
        };
        auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            onVsync();
            return;
        }
        uiTaskRunner.PostTask([callback = std::move(onVsync)]() { callback(); }, "ArkUIRosenWindowVsync");
    };
    rsUIDirector_ = OHOS::Rosen::RSUIDirector::Create();
    if (window && window->GetSurfaceNode()) {
        rsUIDirector_->SetRSSurfaceNode(window->GetSurfaceNode());
    }
    rsUIDirector_->SetCacheDir(AceApplicationInfo::GetInstance().GetDataFileDirPath());
    rsUIDirector_->Init();
    rsUIDirector_->SetUITaskRunner(
        [taskExecutor, id](const std::function<void()>& task, uint32_t delay) {
            ContainerScope scope(id);
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostDelayedTask(
                task, TaskExecutor::TaskType::UI, delay, "ArkUIRosenWindowRenderServiceTask", PriorityType::HIGH);
        },
        id);
}

void RosenWindow::Init()
{
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->SetRequestVsyncCallback([weak = weak_from_this()]() {
        auto self = weak.lock();
        CHECK_NULL_VOID(self);
        self->RequestFrame();
    });
}

void RosenWindow::InitArkUI_X()
{
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    CHECK_NULL_VOID(rsWindow_);
    auto surfaceNode = rsWindow_->GetSurfaceNode();
    if (rsUIDirector_ && surfaceNode) {
        rsUIDirector_->SetRSSurfaceNode(surfaceNode);
    }
#endif
}

void RosenWindow::FlushFrameRate(int32_t rate, int32_t animatorExpectedFrameRate, int32_t rateType)
{
    if (!rsWindow_ || rate < 0) {
        return;
    }
    rsWindow_->FlushFrameRate(rate, animatorExpectedFrameRate, rateType);
}

void RosenWindow::SetUiDvsyncSwitch(bool dvsyncSwitch)
{
    if (!rsWindow_) {
        return;
    }
    if (dvsyncSwitch) {
        ACE_SCOPED_TRACE("enable dvsync");
    } else {
        ACE_SCOPED_TRACE("disable dvsync");
    }
    rsWindow_->SetUiDvsyncSwitch(dvsyncSwitch);
}

bool RosenWindow::GetIsRequestFrame()
{
    return isRequestVsync_;
}

void RosenWindow::RequestFrame()
{
    CHECK_NULL_VOID(onShow_);
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(!isRequestVsync_);
    auto taskExecutor = taskExecutor_.Upgrade();
    if (rsWindow_) {
        isRequestVsync_ = true;
        if (isFirstRequestVsync_) {
            isFirstRequestVsync_ = false;
            LOGI("ArkUI requests first Vsync.");
        }
        rsWindow_->RequestVsync(vsyncCallback_);
        lastRequestVsyncTime_ = static_cast<uint64_t>(GetSysTimestamp());
#ifdef VSYNC_TIMEOUT_CHECK
        if (taskExecutor) {
            auto windowId = rsWindow_->GetWindowId();
            auto instanceId = Container::CurrentIdSafely();
            auto task = [windowId, instanceId, timeStamp = lastRequestVsyncTime_]() {
                LOGE("ArkUI request vsync,but no vsync was received within 3 seconds");
                EventReport::SendVsyncException(VsyncExcepType::UI_VSYNC_TIMEOUT, windowId, instanceId, timeStamp);
            };
            taskExecutor->PostDelayedTaskWithoutTraceId(task, TaskExecutor::TaskType::JS,
                VSYNC_TASK_DELAY_MILLISECOND, "ArkUIVsyncTimeoutCheck");
        }
#endif
    }
    if (taskExecutor) {
        taskExecutor->PostDelayedTask(
            [id = id_]() {
                ContainerScope scope(id);
                auto container = Container::Current();
                CHECK_NULL_VOID(container);
                auto pipeline = container->GetPipelineContext();
                CHECK_NULL_VOID(pipeline);
                pipeline->OnIdle(0);
            },
            TaskExecutor::TaskType::UI, IDLE_TASK_DELAY_MILLISECOND, "ArkUIIdleTask");
    }
}

void RosenWindow::OnShow()
{
    Window::OnShow();
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->GoForeground();
}

void RosenWindow::OnHide()
{
    Window::OnHide();
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->GoBackground();
    rsUIDirector_->SendMessages();
}

void RosenWindow::Destroy()
{
    LOGI("RosenWindow destroyed");
    rsWindow_ = nullptr;
    vsyncCallback_.reset();
    rsUIDirector_->Destroy();
    rsUIDirector_.reset();
    callbacks_.clear();
}

void RosenWindow::SetDrawTextAsBitmap(bool useBitmap)
{
    Rosen::RSSystemProperties::SetDrawTextAsBitmap(useBitmap);
}

void RosenWindow::SetRootFrameNode(const RefPtr<NG::FrameNode>& root)
{
    LOGI("Rosenwindow set root frame node");
    CHECK_NULL_VOID(root);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(root->GetRenderContext());
    CHECK_NULL_VOID(rosenRenderContext);
    if (rosenRenderContext->GetRSNode()) {
        CHECK_NULL_VOID(rsUIDirector_);
        rsUIDirector_->SetRoot(rosenRenderContext->GetRSNode()->GetId());
    }
}

void RosenWindow::RecordFrameTime(uint64_t timeStamp, const std::string& name)
{
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->SetTimeStamp(timeStamp, name);
}

void RosenWindow::FlushTasks()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->SendMessages();
    JankFrameReport::GetInstance().JsAnimationToRsRecord();
}

void RosenWindow::FlushLayoutSize(int32_t width, int32_t height)
{
    CHECK_NULL_VOID(rsWindow_);
    rsWindow_->FlushLayoutSize(width, height);
}

float RosenWindow::GetRefreshRate() const
{
#ifdef PREVIEW
    return PREVIEW_REFRESH_RATE;
#else
    return ONE_SECOND_IN_NANO / rsWindow_->GetVSyncPeriod();
#endif
}

void RosenWindow::SetKeepScreenOn(bool keepScreenOn)
{
#ifdef OHOS_PLATFORM
    if (rsWindow_) {
        rsWindow_->SetKeepScreenOn(keepScreenOn);
    } else {
        LOGE("SetKeepScreenOn Rosenwindow is null");
    }
#else
#endif
}

int64_t RosenWindow::GetVSyncPeriod() const
{
#ifdef PREVIEW
    return static_cast<int64_t>(ONE_SECOND_IN_NANO / PREVIEW_REFRESH_RATE);
#else
    return rsWindow_->GetVSyncPeriod();
#endif
}

std::string RosenWindow::GetWindowName() const
{
    std::string windowName;
    if (rsWindow_) {
        windowName = rsWindow_->GetWindowName();
    }
    return windowName;
}

void RosenWindow::OnVsync(uint64_t nanoTimestamp, uint32_t frameCount)
{
    Window::OnVsync(nanoTimestamp, frameCount);
    auto taskExecutor = taskExecutor_.Upgrade();
#ifdef VSYNC_TIMEOUT_CHECK
        if (taskExecutor) {
            taskExecutor->RemoveTask(TaskExecutor::TaskType::JS, "ArkUIVsyncTimeoutCheck");
        }
#endif
}

uint32_t RosenWindow::GetStatusBarHeight() const
{
#ifndef PREVIEW
    if (rsWindow_) {
        return rsWindow_->GetStatusBarHeight();
    } else {
        return 0;
    }
#else
    return 0;
#endif
}

void RosenWindow::NotifyExtensionTimeout(int32_t errorCode)
{
    CHECK_NULL_VOID(rsWindow_);
    rsWindow_->NotifyExtensionTimeout(errorCode);
}
bool RosenWindow::GetIsRequestVsync()
{
    return isRequestVsync_;
}

} // namespace OHOS::Ace::NG
